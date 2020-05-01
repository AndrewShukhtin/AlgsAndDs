#include <iostream>
#include <stack>
#include <random>
#include <queue>
#include <functional>

template<class T>
struct binary_tree_node {
  binary_tree_node(T _value) : value(_value) {}
  T value = {};
  binary_tree_node* left = nullptr;
  binary_tree_node* right = nullptr;
};

template<class T, class Compare = std::less<T>>
class binary_tree {
  using element_type = T;
  using node_type = binary_tree_node<element_type>;
  using node_ptr_type = node_type*;

public:
  binary_tree() {}
  ~binary_tree();
  
  size_t height() const;

  void insert(element_type value);

  template<class Pred>
  void traverse_pre_order(Pred pred);

private:
  node_ptr_type _root = nullptr;
  Compare _cmp;
};

template<class T, class Compare>
binary_tree<T, Compare>::~binary_tree() {
  traverse_pre_order([](auto node){
    delete node;
  });
}

template<class T, class Compare>
void binary_tree<T, Compare>::insert(element_type value) {
  if (_root == nullptr) {
    _root = new node_type(value);
    return;
  }

  auto node = _root;
  while (true) {
    if (_cmp(node->value, value)) {
      if (node->right == nullptr) {
        node->right = new node_type(value);
        break;
      } else {
        node = node->right;
      }
    } else {
      if (node->left == nullptr) {
        node->left = new node_type(value);
        break;
      } else {
        node = node->left;
      }
    }
  }

  return;
}

template<class T, class Compare>
template<class Pred>
void binary_tree<T, Compare>::traverse_pre_order(Pred pred) {
  if (_root == nullptr) {
    return;
  }

  std::stack<node_ptr_type> stack;
  stack.push(_root);
  while (!stack.empty()) {
    auto node = stack.top();
    stack.pop();
    if (node->right != nullptr)
      stack.push(node->right);

    if (node->left != nullptr)
      stack.push(node->left);

    pred(node);
  }
}

template<class T, class Compare>
size_t binary_tree<T, Compare>::height() const {
  if (_root == nullptr) {
    return 0;
  }

  std::queue<node_ptr_type> queue;
  queue.push(_root);

  size_t height = 0;
  while (true) {
    size_t node_count = queue.size();
    if (node_count == 0) {
      return height;
    }

    ++height;
    while (node_count > 0) {
      node_ptr_type node = queue.front();

      queue.pop();

      if (node->left != nullptr)
        queue.push(node->left);

      if (node->right != nullptr)
        queue.push(node->right);

      --node_count;
    }
  }
}

static constexpr size_t TASK_MAX_NUMBERS = 1000000;

template<class T>
struct treap_node {
  treap_node(const T& value, size_t priority) :
                          left(nullptr),
                          right(nullptr),
                          priority(priority),
                          value(value) {}

  treap_node* left;
  treap_node* right;
  size_t priority;
  T value;
};

template<class T, class Compare = std::less_equal<T>>
class treap {
public:
  using value_type = T;
  using node_type = treap_node<value_type>;
  using node_ptr_type = node_type*;

public:
  treap() : _root(nullptr), _cmp{} {}
  ~treap() {
    traverse_pre_order([](auto node){
      delete node;
    });
  }

  void insert(node_ptr_type& node);

  void insert(const value_type& value, size_t priority);

  size_t height() const;

  template<class Pred>
  void traverse_pre_order(Pred pred);

private:
  void _to_split_recursive_call(node_ptr_type current_node, const value_type& value, node_ptr_type& left, node_ptr_type& right) {
    if (current_node == nullptr) {
      left = nullptr;
      right = nullptr;
    } else if(_cmp(current_node->value, value)) {
      _to_split_recursive_call(current_node->right, value, current_node->right, right);
      left = current_node;
    } else {
      _to_split_recursive_call(current_node->left, value, left, current_node->left);
      right = current_node;
    }
  }

  node_ptr_type _to_merge_recursive_call(node_ptr_type left, node_ptr_type right) {
    if (left == nullptr || right == nullptr) {
     return left == nullptr ? right : left;
    }
    if (left->priority > right->priority) {
      left->right  = _to_merge_recursive_call(left->right, right);
      return left;
    } else {
      right->left = _to_merge_recursive_call(left, right->left);
      return right;
    }
  }

  void to_insert_recursive_call(node_ptr_type& current, node_ptr_type node) {
    if (current == nullptr) {
      current = node;
    } else if (node->priority > current->priority) {
      _to_split_recursive_call(current, node->value, node->left, node->right);
      current = node;
    } else {
      to_insert_recursive_call((_cmp(node->value, current->value) ? current->left : current->right), node);
    }
  }

private:
  size_t generate_random_priority();

private:
  node_ptr_type _root;
  Compare _cmp;
};

template<class T, class Compare>
size_t treap<T, Compare>::height() const {
  if (_root == nullptr) {
    return 0;
  }

  std::queue<node_ptr_type> queue;
  queue.push(_root);

  size_t height = 0;
  while (true) {
    size_t node_count = queue.size();
    if (node_count == 0) {
      return height;
    }

    ++height;
    while (node_count > 0) {
      node_ptr_type node = queue.front();

      queue.pop();

      if (node->left != nullptr)
        queue.push(node->left);

      if (node->right != nullptr)
        queue.push(node->right);

      --node_count;
    }
  }
}

template<class T, class Compare>
void treap<T, Compare>::insert(node_ptr_type& node) {
  to_insert_recursive_call(_root, node);
}
template<class T, class Compare>
void treap<T, Compare>::insert(const value_type& value, size_t priority) {
  node_ptr_type node = new node_type(value, priority);
  to_insert_recursive_call(_root, node);
}

template<class T, class Compare>
template<class Pred>
void treap<T, Compare>::traverse_pre_order(Pred pred) {
  if (_root == nullptr) {
    return;
  }

  std::stack<node_ptr_type> stack;
  stack.push(_root);
  while (!stack.empty()) {
    auto node = stack.top();
    stack.pop();
    if (node->right != nullptr)
      stack.push(node->right);

    if (node->left != nullptr)
      stack.push(node->left);

    pred(node);
  }
}

template<class T, class Compare>
size_t treap<T, Compare>::generate_random_priority() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, TASK_MAX_NUMBERS);

    return  dis(gen);
}

int main(void) {
  size_t nodes_count = 0;
  std::cin >> nodes_count;

  treap<int> trp;
  binary_tree<int> bt;
  for (size_t i = 0; i < nodes_count; ++i) {
    int value = 0;
    size_t priority = 0;
    std::cin >> value >> priority;

    bt.insert(value);
    trp.insert(value, priority);
  }

  std::cout << static_cast<int>(bt.height() - trp.height()) << std::endl;
  return EXIT_SUCCESS;
}
