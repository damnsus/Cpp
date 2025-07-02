#pragma once
#include <iostream>
#include <vector>

class String {
 public:
  String();
  String(unsigned size, char character);
  String(const char* str);
  String(const String& other);
  String& operator=(const String& other);
  ~String();
  void Clear();
  void PushBack(char character);
  void PopBack();
  void Resize(unsigned new_size);
  void Resize(unsigned new_size, char character);
  void Reserve(unsigned new_cap);
  void ShrinkToFit();
  void Swap(String& other);
  const char& operator[](unsigned i) const;
  char& operator[](unsigned i);
  const char& Front() const;
  char& Front();
  const char& Back() const;
  char& Back();
  bool Empty();
  unsigned Size() const;
  unsigned Capacity() const;
  const char* Data() const;
  String& operator+=(const String& str);
  String& operator*=(unsigned n);
  std::vector<String> Split(const String& delim = " ");
  String Join(const std::vector<String>& strings);

 private:
  char* str_;
  unsigned size_;
  unsigned cap_;
  String Substring(unsigned idx, unsigned step);
};

bool operator<(const String& str1, const String& str2);
bool operator>(const String& str1, const String& str2);
bool operator<=(const String& str1, const String& str2);
bool operator>=(const String& str1, const String& str2);
bool operator==(const String& str1, const String& str2);
bool operator!=(const String& str1, const String& str2);
String operator+(const String& str1, const String& str2);
String operator*(const String& str, unsigned n);
std::ostream& operator<<(std::ostream& out, const String& str);
std::istream& operator>>(std::istream& in, String& str);