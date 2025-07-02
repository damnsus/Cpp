#include <iostream>
#include <string>

struct Node {
  std::string key;
  std::string value;
  Node* left;
  Node* right;
  Node* parent;
  Node(std::string keyval, std::string str)
      : key(keyval),
        value(str),
        left(nullptr),
        right(nullptr),
        parent(nullptr) {}
  ~Node() {
    delete left;
    delete right;
  }
};

class SplayTree {
 private:
  Node* root_;
  void RotateLeft(Node* node) {
    Node* cp = node->right;
    node->right = cp->left;
    if (cp->left != nullptr) {
      cp->left->parent = node;
    }
    cp->parent = node->parent;
    if (node->parent == nullptr) {
      root_ = cp;
    } else if (node == node->parent->left) {
      node->parent->left = cp;
    } else {
      node->parent->right = cp;
    }
    cp->left = node;
    node->parent = cp;
  }

  void RotateRight(Node* node) {
    Node* cp = node->left;
    node->left = cp->right;
    if (cp->right != nullptr) {
      cp->right->parent = node;
    }
    cp->parent = node->parent;
    if (node->parent == nullptr) {
      root_ = cp;
    } else if (node == node->parent->right) {
      node->parent->right = cp;
    } else {
      node->parent->left = cp;
    }
    cp->right = node;
    node->parent = cp;
  }

  void Splay(Node* node) {
    while (node->parent != nullptr) {
      if (node->parent->parent == nullptr) {
        if (node == node->parent->left) {
          RotateRight(node->parent);
        } else {
          RotateLeft(node->parent);
        }
      } else if (node == node->parent->left &&
                 node->parent == node->parent->parent->left) {
        RotateRight(node->parent->parent);
        RotateRight(node->parent);
      } else if (node == node->parent->right &&
                 node->parent == node->parent->parent->right) {
        RotateLeft(node->parent->parent);
        RotateLeft(node->parent);
      } else if (node == node->parent->right &&
                 node->parent == node->parent->parent->left) {
        RotateLeft(node->parent);
        RotateRight(node->parent);
      } else {
        RotateRight(node->parent);
        RotateLeft(node->parent);
      }
    }
  }

  Node* Find(const std::string& key) {
    Node* current = root_;
    while (current != nullptr) {
      if (current->key == key) {
        Splay(current);
        return current;
      }
      if (key < current->key) {
        if (current->left != nullptr) {
          current = current->left;
        } else {
          break;
        }
      } else {
        if (current->right != nullptr) {
          current = current->right;
        } else {
          break;
        }
      }
    }
    return nullptr;
  }

  void Insert(const std::string& key, const std::string& value) {
    Node* new_node = new Node(key, value);
    if (root_ == nullptr) {
      root_ = new_node;
      return;
    }
    Node* current = root_;
    while (true) {
      if (key < current->key) {
        if (current->left != nullptr) {
          current = current->left;
        } else {
          current->left = new_node;
          new_node->parent = current;
          break;
        }
      } else {
        if (current->right != nullptr) {
          current = current->right;
        } else {
          current->right = new_node;
          new_node->parent = current;
          break;
        }
      }
    }

    Splay(new_node);
  }

 public:
  SplayTree() : root_(nullptr) {}

  ~SplayTree() { delete root_; }

  void InsertPair(const std::string& key, const std::string& value) {
    Insert(key, value);
    std::string new_key = value;
    std::string new_value = key;
    Insert(new_key, new_value);
  }

  std::string FindValue(const std::string& key) {
    Node* node = Find(key);
    if (node != nullptr) {
      return node->value;
    }
    return "";
  }
};

int main() {
  int nval;
  std::cin >> nval;
  SplayTree tree;
  for (int i = 0; i < nval; ++i) {
    std::string call_sign;
    std::string car_name;
    std::cin >> call_sign >> car_name;
    tree.InsertPair(call_sign, car_name);
  }
  int qval;
  std::cin >> qval;
  for (int i = 0; i < qval; ++i) {
    std::string query;
    std::cin >> query;
    std::cout << tree.FindValue(query) << std::endl;
  }
  return 0;
}

