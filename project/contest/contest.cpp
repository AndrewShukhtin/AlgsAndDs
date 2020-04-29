#include <functional>
#include <vector>
#include <iostream>

#define TASK_RECOMMENDED_SIZE 8
#define DEFAULT_LOAD_FACTOR 0.0f
#define MAX_LOAD_FACTOR 0.75f

template<class T>
struct hash_table_node {
  enum class state {
    free,
    busy,
    deleted
  };
  T key = {};
  state st = state::free;
};

template<class T, class Hash = std::hash<T>, class Equal = std::equal_to<T>>
class hash_table {
  using key_type = T;
  using node_type = hash_table_node<key_type>;
  using container_type = std::vector<node_type>;

private:
  container_type _data;
  float _load_factor;
  Hash _hash;
  Equal _equal;

public:
  hash_table();

  bool insert(const key_type& key);
  bool has(const key_type& key) const;
  bool remove(const key_type& key);

private:
  // Double hashers
  size_t _first_hash(const key_type& key) const {
    return _hash(key);
  }

  size_t _second_hash(const key_type& key) const {
    return (_hash(key) >> 2) | 01;
  }

private:
  void _rehash();
  size_t _find_insert_index(const container_type& data, const key_type& key) const;
};

template<class T, class Hash, class Equal>
hash_table<T, Hash, Equal>::hash_table() :
_data{TASK_RECOMMENDED_SIZE}, _load_factor{DEFAULT_LOAD_FACTOR}, _hash{}, _equal{} {}

template<class T, class Hash, class Equal>
bool hash_table<T, Hash, Equal>::insert(const key_type& key) {
  if (_load_factor >= MAX_LOAD_FACTOR) {
    _rehash();
  }

  size_t first_hash = _first_hash(key);
  size_t second_hash = _second_hash(key);
  for (size_t i = 0; i < _data.size(); ++i) {
    size_t index = (first_hash + i * second_hash) % _data.size();
    auto& node = _data[index];
    if (node.st == node_type::state::free) {
      node.key = key;
      node.st = node_type::state::busy;
      _load_factor += 1.0 / _data.size();
      return true;
    }
    if (node.st == node_type::state::deleted) {
      if (has(key)) {
        return false;
      }
      node.key = key;
      node.st = node_type::state::busy;
      return true;
    }
    if (node.st == node_type::state::busy && _equal(node.key, key)) {
      return false;
    }
  }

  return false;
}

template<class T, class Hash, class Equal>
bool hash_table<T, Hash, Equal>::has(const key_type& key) const {
  size_t first_hash = _first_hash(key);
  size_t second_hash = _second_hash(key);
  for (size_t i = 0; i < _data.size(); ++i) {
    size_t index = (first_hash + i * second_hash) % _data.size();
    const auto& node = _data[index];
    if (node.st == node_type::state::free) {
      return false;
    }
    if (node.st != node_type::state::free && _equal(node.key, key)) {
      return node.st == node_type::state::busy;
    }
  }

  return false;
}

template<class T, class Hash, class Equal>
bool hash_table<T, Hash, Equal>::remove(const key_type& key) {
  size_t first_hash = _first_hash(key);
  size_t second_hash = _second_hash(key);
  for (size_t i = 0; i < _data.size(); ++i) {
    size_t index = (first_hash + i * second_hash) % _data.size();
    auto& node = _data[index];
    if (node.st == node_type::state::free) {
      return false;
    }
    if (node.st == node_type::state::busy && _equal(node.key, key)) {
      node.st = node_type::state::deleted;
      return true;
    }
    if (node.st == node_type::state::deleted && _equal(node.key, key)) {
      return false;
    }
  }

   return false;
}

template<class T, class Hash, class Equal>
void hash_table<T, Hash, Equal>::_rehash() {
  size_t busy_count = 0;
  container_type new_data(2 * _data.size());
  for (size_t i = 0; i < _data.size(); ++i) {
    auto node = std::move(_data[i]);
    if (node.st == node_type::state::busy) {
      ++busy_count;

      size_t index = _find_insert_index(new_data, node.key);
      new_data[index] = std::move(node);
    }
  }

  _data = std::move(new_data);
  _load_factor = static_cast<float>(busy_count) / _data.size();
}

template<class T, class Hash, class Equal>
size_t hash_table<T, Hash, Equal>::_find_insert_index(const container_type& data, const key_type& key) const {
  size_t first_hash = _first_hash(key);
  size_t second_hash = _second_hash(key);

  size_t index = 0;
  for (size_t i = 0; i < data.size(); ++i) {
    index = (first_hash + i * second_hash) % data.size();

    const auto& node = data[index];
    if (node.st == node_type::state::free) {
      break;
    }
  }

  return index;
}

#undef TASK_RECOMMENDED_SIZE
#undef DEFAULT_LOAD_FACTOR
#undef INVALID_INDEX
#undef MAX_LOAD_FACTOR

class task_hasher {
public:
  size_t operator()(const std::string& str) const {
    static constexpr size_t kDefaultPolynomialHashValue = 7;
    size_t hash = 0;
    for (const auto& c : str)
      hash = hash * kDefaultPolynomialHashValue + c;
    
    return hash;
  }
};

int main(void) {
  auto decision = [](bool res) {
    if (res) {
      std::cout << "OK" << std::endl;
    } else {
      std::cout << "FAIL" << std::endl;
    }
  };

  hash_table<std::string, task_hasher> ht;

  char operation = 0;
  std::string key;
  while (std::cin >> operation >> key) {
    switch (operation) {
    case '+':
      decision(ht.insert(key));
      break;

    case '-':
      decision(ht.remove(key));
      break;

    case '?':
      decision(ht.has(key));
      break;

    default:
      break;
    }
  }

  return EXIT_SUCCESS;
}
