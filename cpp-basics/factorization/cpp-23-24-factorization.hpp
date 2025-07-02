#pragma once
#include <vector>

std::vector<int> Factorize(int num) {
  std::vector<int> vec;
  std::size_t primeNumber = 2;
  while (num > 1) {
    while (num % primeNumber == 0) {
      num /= primeNumber;
      vec.push_back(primeNumber);
    }
    if (primeNumber == 2) {
      ++primeNumber;
    } else {
      primeNumber += 2;
    }
  }
  return vec;
}