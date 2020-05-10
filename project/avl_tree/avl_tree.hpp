#pragma once

#include <functional>

template<class T, class Compare = std::less<T>>
class avl_tree {
  using height_type = unsigned char;
  using height_diff_type = char;
  using key_type = T;

  struct node_type {
    node_type(const key_type& key)
     : key(key),
       height(1),
       left(nullptr),
       right(nullptr)
       {}

    key_type key;
    height_type height;
    node_type* left;
    node_type* right;
  };

public:
 // NOTE: Класс поиска порядковой статистики
  class kstat_finder;
  friend class kstat_finder;

  class kstat_finder {
  public:
    kstat_finder(const avl_tree& tree) : _tree(tree) {}

    key_type operator()(size_t kstat_place) const {
      return _recursive_find_kstat(_tree._root, kstat_place);
    }

  private:
    key_type _recursive_find_kstat(node_type* node, size_t kstat_place) const {
      key_type kstat = 0;

      size_t nodes_count = _tree._recursive_nodes_count(node->left);
      if (nodes_count > kstat_place) {
        kstat = _recursive_find_kstat(node->left, kstat_place);
      } else if (nodes_count < kstat_place) {
        kstat = _recursive_find_kstat(node->right, kstat_place - nodes_count - 1);
      } else {
        kstat = node->key;
      }

      return kstat;
    }

  private:
    const avl_tree& _tree;
  };

public:
  avl_tree() : _root(nullptr), _cmp{} {}
  ~avl_tree() {
    _delete_tree(_root);
  }

  void insert(const key_type& key) {
    _root = _recursive_insert(_root, key);
  }

  void erase(const key_type& key) {
    _root = _recursive_erase(_root, key);
  }

  size_t nodes_count() const {
    return _recursive_nodes_count(_root);
  }

private:
  // NOTE: Работа с высотой узлов
  height_type _node_height(node_type* node) const{
    return node ? node->height : 0;
  }

  height_diff_type _node_balance_factor(node_type* node) const {
    return _node_height(node->right) - _node_height(node->left);
  }

  void _fix_node_height(node_type* node) {
    if (node == nullptr) {
      return;
    }

    height_diff_type left_child_height = _node_height(node->left);
    height_diff_type right_child_height = _node_height(node->right);
    node->height = (left_child_height < right_child_height ? right_child_height : left_child_height) + 1;
  }

private:
  // NOTE: Повороты относительно узла
  node_type* _rotate_right(node_type* node) {
    if (node == nullptr) {
      return nullptr;
    }
    node_type* left_child = node->left;
    node->left = left_child->right;
    left_child->right = node;

    _fix_node_height(node);
    _fix_node_height(left_child);

    return left_child;
  }

  node_type* _rotate_left(node_type* node) {
    if (node == nullptr) {
      return nullptr;
    }
    node_type* right_child = node->right;
    node->right = right_child->left;
    right_child->left = node;

    _fix_node_height(node);
    _fix_node_height(right_child);

    return right_child;
  }

private:
  // NOTE: Балансировка узла
  node_type* _node_balance(node_type* node) {
    if (node == nullptr) {
      return nullptr;
    }

    _fix_node_height(node);

    auto node_balance_factor = _node_balance_factor(node);
    if (node_balance_factor == 2) {
      if (_node_balance_factor(node->right) < 0) {
        node->right = _rotate_right(node->right);
      }

      return _rotate_left(node);
    }
    if (node_balance_factor == -2) {
      if (_node_balance_factor(node->left) > 0) {
        node->left = _rotate_left(node->left);
      }

      return _rotate_right(node);
    }

    return node;
  }

private:
 // NOTE: Рекурсивная вставка ключа
  node_type* _recursive_insert(node_type *node, const key_type& key) {
    if (node == nullptr) {
      return new node_type(key);
    }

    if (_cmp(key, node->key)) {
      node->left = _recursive_insert(node->left, key);
    } else {
      node->right = _recursive_insert(node->right, key);
    }

    return _node_balance(node);
  }

private:
  // NOTE: Рекурсивное удаление ключа
  node_type* _recursive_erase(node_type *node, const key_type& key) {
    if (node == nullptr) {
      return nullptr;
    }

    if (_cmp(key, node->key)) {
      node->left = _recursive_erase(node->left, key);
    } else if (_cmp(node->key, key)) {
      node->right = _recursive_erase(node->right, key);
    } else {
      node_type* left_child = node->left;
      node_type* right_child = node->right;
      delete node;

      if (right_child == nullptr) {
        return left_child;
      }

      node_type* min_node = _extract_min_node(right_child);
      min_node->right = right_child;
      min_node->left = left_child;

      return _node_balance(min_node);
    }

    return _node_balance(node);
  }

  node_type* _extract_min_node(node_type*& node) {
    node_type* min_node = nullptr;

    if (!node->left) {
      min_node = node;
      node = node->right;
      min_node->right = nullptr;
      return min_node;
    }

    min_node = _extract_min_node(node->left);
    node = _node_balance(node);

    return min_node;
  }

private:
  // NOTE: Делитер данных
  void _delete_tree(node_type*& node) {
    if (node == nullptr) {
      return;
    }

    _delete_tree(node->left);
    _delete_tree(node->right);
    delete node;
  }

// NOTE: Рекурсивное вычилсение количества узлов
  size_t _recursive_nodes_count(node_type* node) const {
    if (node == nullptr) {
      return 0;
    }

    size_t nodes_count = 1;
    nodes_count += _recursive_nodes_count(node->left);
    nodes_count += _recursive_nodes_count(node->right);

    return nodes_count;
  }

private:
  node_type* _root;
  Compare _cmp;
};