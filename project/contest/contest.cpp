#include <iostream>
#include <stack>

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

public:
  binary_tree() {}
  ~binary_tree();
  
  void insert(element_type value);

  template<class Pred>
  void traverse_pre_order(Pred pred);

  template<class Pred>
  void recursive_pre_order(Pred pred);

private:
  template<class Pred>
  void _traverse(const node_type* node, Pred pred);

private:
  node_type* _root = nullptr;
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

  std::stack<node_type*> stack;
  stack.push(_root);
  while (!stack.empty()) {
    auto node = stack.top();
    pred(node);
    stack.pop();
    if (node->right != nullptr)
      stack.push(node->right);

    if (node->left != nullptr)
      stack.push(node->left);
  }
}


template<class T, class Compare>
template<class Pred>
void binary_tree<T, Compare>::recursive_pre_order(Pred pred) {
  _traverse(_root, pred);
}

template<class T, class Compare>
template<class Pred>
void binary_tree<T, Compare>::_traverse(const node_type* node, Pred pred) {
  pred(node);
  if (node->left != nullptr) _traverse(node->left, pred);
  if (node->right != nullptr) _traverse(node->right, pred);
}

int main(void) {
  size_t number_count = 0;
  std::cin >> number_count;

  binary_tree<int> bt;
  for (size_t i = 0; i < number_count; ++i) {
    int number = 0;
    std::cin >> number;
    bt.insert(number);
  }

  bt.traverse_pre_order([](auto node){
    std::cout << node->value << std::endl;
  });

  return EXIT_SUCCESS;
}
