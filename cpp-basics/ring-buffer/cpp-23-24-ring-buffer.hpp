#pragma once
#include <cstddef>
#include <vector>

class RingBuffer {
 public:
  explicit RingBuffer(size_t capacity)
      : buffer_(capacity), begin_(0), end_(capacity), size_(0) {}

  size_t Size() const { return size_; }

  bool Empty() const { return size_ == 0; }

  bool TryPush(int element) {
    bool res = size_ < buffer_.capacity();
    if (size_ < buffer_.capacity()) {
      buffer_[end_ % buffer_.capacity()] = element;
      ++end_;
      ++size_;
    }
    return res;
  }

  bool TryPop(int* element) {
    bool res = size_ != 0;
    if (size_ != 0) {
      *element = buffer_[begin_ % buffer_.capacity()];
      ++begin_;
      --size_;
    }
    return res;
  }

 private:
  std::vector<int> buffer_;
  size_t begin_;
  size_t end_;
  size_t size_;
};