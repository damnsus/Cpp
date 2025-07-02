#include "cpp-23-24-string.hpp"

#include <iostream>

unsigned MYstrlen(const char* str) {
  unsigned counter = 0;
  while (str[counter] != '\0') {
    ++counter;
  }
  return counter;
}

String::String() : str_(nullptr), size_(0), cap_(0) {}

String::String(unsigned size, char character)
    : str_(new char[size + 1]), size_(size), cap_(size) {
  for (unsigned i = 0; i < size; ++i) {
    str_[i] = character;
  }
  str_[size] = '\0';
}
// программа зависает на фибоначчи стайл, если тут я
// инициализирую переменные через список инициализации
String::String(const char* str) {
  unsigned length = MYstrlen(str);
  str_ = new char[length + 1];
  for (unsigned i = 0; i < length; ++i) {
    str_[i] = str[i];
  }
  str_[length] = '\0';
  size_ = cap_ = length;
}

String::String(const String& other) {
  str_ = new char[other.cap_ + 1];
  for (unsigned i = 0; i < other.size_; ++i) {
    str_[i] = other.str_[i];
  }
  str_[other.size_] = '\0';
  size_ = other.size_;
  cap_ = other.cap_;
}

String& String::operator=(const String& other) {
  if (this != &other) {
    String temp = other;
    Swap(temp);
  }
  return *this;
}

String::~String() { delete[] str_; }

void String::Clear() {
  size_ = 0;
  str_[size_] = '\0';
}

void String::PushBack(char character) {
  if (str_ == nullptr) {
    Reserve(1);
  }
  if (size_ == cap_) {
    Reserve(2 * cap_);
  }
  str_[size_] = character;
  ++size_;
  str_[size_] = '\0';
}

void String::PopBack() {
  if (str_ != nullptr) {
    --size_;
    str_[size_] = '\0';
  }
}

void String::Resize(unsigned new_size) {
  if (cap_ < new_size) {
    Reserve(new_size);
  }
  str_[new_size] = '\0';
  size_ = new_size;
}

void String::Resize(unsigned new_size, char character) {
  if (size_ < new_size) {
    if (cap_ < new_size) {
      Reserve(new_size);
    }
    for (unsigned i = size_; i < new_size; ++i) {
      str_[i] = character;
    }
  }
  str_[new_size] = '\0';
  size_ = new_size;
}

void String::Reserve(unsigned new_cap) {
  if (new_cap > cap_) {
    char* str = new char[new_cap + 1];
    for (unsigned i = 0; i < size_; ++i) {
      str[i] = str_[i];
    }
    str[size_] = '\0';
    delete[] str_;
    str_ = str;
    cap_ = new_cap;
  }
}

void String::ShrinkToFit() {
  if (cap_ > size_) {
    String temp(str_);
    Swap(temp);
  }
}

void String::Swap(String& other) {
  std::swap(str_, other.str_);
  std::swap(size_, other.size_);
  std::swap(cap_, other.cap_);
}

const char& String::operator[](unsigned i) const { return str_[i]; }

char& String::operator[](unsigned i) { return str_[i]; }

const char& String::Front() const { return str_[0]; }

char& String::Front() { return str_[0]; }

const char& String::Back() const { return str_[size_ - 1]; }

char& String::Back() { return str_[size_ - 1]; }

bool String::Empty() { return size_ == 0; }

unsigned String::Size() const { return size_; }

unsigned String::Capacity() const { return cap_; }

const char* String::Data() const { return str_; }

bool operator<(const String& str1, const String& str2) {
  unsigned size;
  const unsigned kMinLen =
      (str1.Size() < str2.Size()) ? str1.Size() : str2.Size();
  for (unsigned i = 0; i < kMinLen; ++i) {
    if (str1[i] != str2[i]) {
      return str1[i] < str2[i];
    }
  }
  return str1.Size() < str2.Size();
}

bool operator>(const String& str1, const String& str2) {
  return !(str1 <= str2);
}

bool operator<=(const String& str1, const String& str2) {
  return (str1 < str2 || str1 == str2);
}

bool operator>=(const String& str1, const String& str2) {
  return !(str1 < str2);
}

bool operator==(const String& str1, const String& str2) {
  if (str1.Size() == str2.Size()) {
    for (unsigned i = 0; i < str1.Size(); ++i) {
      if (str1[i] != str2[i]) {
        return false;
      }
    }
  }
  return str1.Size() == str2.Size();
}

bool operator!=(const String& str1, const String& str2) {
  return !(str1 == str2);
}

String& String::operator+=(const String& str) {
  Reserve(size_ + str.size_);
  if (str_ == nullptr) {
    return *this;
  }
  for (unsigned i = 0; i < str.size_; ++i) {
    str_[size_] = str[i];
    ++size_;
  }
  str_[size_] = '\0';
  return *this;
}

String operator+(const String& str1, const String& str2) {
  String res = str1;
  res += str2;
  return res;
}

String& String::operator*=(unsigned n) {
  const String temp = *this;
  if (n == 0) {
    Clear();
  } else {
    Reserve(cap_ * n);
    for (unsigned i = 1; i < n; ++i) {
      *this += temp;
    }
  }
  return *this;
}

String operator*(const String& str, unsigned n) {
  String res = str;
  res *= n;
  return res;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
  return out << str.Data();
}

std::istream& operator>>(std::istream& in, String& str) {
  char strin;
  if (str.Data() != nullptr) {
    str.Clear();
  }
  while (in.get(strin) && strin != '\0') {
    str.PushBack(strin);
  }
  return in;
}

String String::Substring(unsigned left, unsigned right) {
  String res;
  for (; left < right; ++left) {
    res.PushBack(str_[left]);
  }
  return res;
}

std::vector<String> String::Split(const String& delim) {
  std::vector<String> words;
  String substr;
  unsigned left = 0;
  unsigned right = delim.size_;
  unsigned idx = 0;
  if (right > size_) {
    words.push_back("");
  }
  for (; right <= size_;) {
    if (Substring(left, right) == delim) {
      for (; idx < left; ++idx) {
        substr.PushBack(str_[idx]);
      }
      words.push_back(substr);
      if (substr.str_ != nullptr) {
        substr.Clear();
      }
      idx += delim.size_;
    }
    if (right == size_) {
      for (; idx < right; ++idx) {
        substr.PushBack(str_[idx]);
      }
      words.push_back(substr);
      if (substr.str_ != nullptr) {
        substr.Clear();
      }
    }
    ++right;
    ++left;
  }
  return words;
}

String String::Join(const std::vector<String>& strings) {
  String res;
  if (!(strings.empty())) {
    for (unsigned i = 0; i < strings.size() - 1; ++i) {
      res += strings[i];
      res += *this;
    }
    res += strings[strings.size() - 1];
  }
  return res;
}