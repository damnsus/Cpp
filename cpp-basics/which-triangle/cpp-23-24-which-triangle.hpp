#include <iostream>

size_t Max(int a, int b, int c) {
  size_t max = 0;
  if (a > b && a > c) {
    max = a;
  }
  if (b > a && b > c) {
    max = b;
  }
  if (c > b && c > a) {
    max = c;
  }
  return max;
}

int WhichTriangle(int a, int b, int c) {
  const int64_t kSide1 = a;
  const int64_t kSide2 = b;
  const int64_t kSide3 = c;
  const int64_t kMaxSide = Max(a, b, c);
  if (kMaxSide > kSide1 + kSide2 + kSide3 - kMaxSide) {
    return 0;
  }
  if (kSide1 + kSide2 + kSide3 - 2 * kMaxSide == 0) {
    return 1;
  }
  if (kSide1 * kSide1 + kSide2 * kSide2 + kSide3 * kSide3 -
          2 * kMaxSide * kMaxSide >
      0) {
    return 2;
  }
  if (kSide1 * kSide1 + kSide2 * kSide2 + kSide3 * kSide3 -
          2 * kMaxSide * kMaxSide ==
      0) {
    return 3;
  }
  return 4;
}