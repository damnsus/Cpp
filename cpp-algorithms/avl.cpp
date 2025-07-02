#include <iostream>

const int kVal = 1000000000;

struct Node {
  int key = 0;
  int height = 0;
  Node* left = nullptr;
  Node* right = nullptr;
  Node(int keyval) : key(keyval), height(1), left(nullptr), right(nullptr) {}
  ~Node() {
    delete left;
    delete right;
  }
};

int GetHeight(Node* node) {
  int height;
  if (node != nullptr) {
    height = node->height;
  } else {
    height = 0;
  }
  return height;
}

int GetBalance(Node* node) {
  int balance;
  if (node != nullptr) {
    balance = GetHeight(node->left) - GetHeight(node->right);
  } else {
    balance = 0;
  }
  return balance;
}

void UpdateHeight(Node* node) {
  if (node != nullptr) {
    node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
  }
}

Node* RotateRight(Node* node) {
  Node* cp = node->left;
  Node* tmp = cp->right;
  cp->right = node;
  node->left = tmp;
  UpdateHeight(node);
  UpdateHeight(cp);
  return cp;
}

Node* RotateLeft(Node* node) {
  Node* cp = node->right;
  Node* tmp = cp->left;
  cp->left = node;
  node->right = tmp;
  UpdateHeight(node);
  UpdateHeight(cp);
  return cp;
}

Node* Balance(Node* node) {
  UpdateHeight(node);
  int balance_factor = GetBalance(node);
  if (balance_factor > 1) {
    if (GetBalance(node->left) < 0) {
      node->left = RotateLeft(node->left);
    }
    return RotateRight(node);
  }
  if (balance_factor < -1) {
    if (GetBalance(node->right) > 0) {
      node->right = RotateRight(node->right);
    }
    return RotateLeft(node);
  }
  return node;
}

Node* Insert(Node* root, int key) {
  if (root == nullptr) {
    return new Node(key);
  }
  if (key < root->key) {
    root->left = Insert(root->left, key);
  } else if (key > root->key) {
    root->right = Insert(root->right, key);
  }
  return Balance(root);
}

Node* FindMin(Node* root) {
  Node* tmp = nullptr;
  if (root->left != nullptr) {
    tmp = FindMin(root->left);
  } else {
    tmp = root;
  }
  return tmp;
}

Node* Next(Node* root, int key) {
  Node* res = nullptr;
  while (root != nullptr) {
    if (root->key >= key) {
      res = root;
      root = root->left;
    } else {
      root = root->right;
    }
  }
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int num;
  std::cin >> num;
  Node* root = nullptr;
  int last_result = 0;
  while (num > 0) {
    char type;
    int value;
    std::cin >> type >> value;
    if (type == '+') {
      int adjusted_value;
      if (last_result > 0) {
        adjusted_value = (value + last_result) % kVal;
      } else {
        adjusted_value = value;
      }
      root = Insert(root, adjusted_value);
      last_result = 0;
    } else if (type == '?') {
      Node* res = Next(root, value);
      if (res != nullptr) {
        std::cout << res->key << "\n";
        last_result = res->key;
      } else {
        std::cout << -1 << "\n";
        last_result = -1;
      }
    }
    --num;
  }
  delete root;
  return 0;
}

