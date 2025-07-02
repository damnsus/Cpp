#include <stdint.h>

#include <iostream>
#include <vector>

const int kBytes = 256;
const int kByteSize = 8;
const int kByte = 0xFF;

void RadixSortLSD(std::vector<uint64_t>& arr) {
  int len = arr.size();
  std::vector<uint64_t> output;
  output.resize(len);
  for (int byte = 0; byte < kByteSize; ++byte) {
    std::vector<int> count(kBytes, 0);
    for (int i = 0; i < len; ++i) {
      int byte_value = (arr[i] >> (byte * kByteSize)) & kByte;
      count[byte_value]++;
    }
    for (int i = 1; i < kBytes; ++i) {
      count[i] += count[i - 1];
    }
    for (int i = len - 1; i >= 0; --i) {
      int byte_value = (arr[i] >> (byte * kByteSize)) & kByte;
      output[--count[byte_value]] = arr[i];
    }
    arr = output;
  }
}

int main() {
  int num;
  std::cin >> num;
  std::vector<uint64_t> arr;
  arr.resize(num);
  for (int i = 0; i < num; ++i) {
    std::cin >> arr[i];
  }
  RadixSortLSD(arr);
  for (uint64_t num : arr) {
    std::cout << num << "\n";
  }
  return 0;
}

