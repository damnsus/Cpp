#include <utility>

int myAbs(int n) {
  if (n >= 0) {
    return n;
  } else {
    return -n;
  }
}

std::pair<int, const int*> Range(int from, int to, int step) {
  if ((to - from >= 0 && step <= 0) || (to - from <= 0 && step >= 0)) {
    return {0, nullptr};
  }
  const unsigned num = (myAbs(to - from) - 1) / myAbs(step) + 1;
  int* arr = new int[num];
  if (from <= to && step > 0) {
    for (unsigned i = 0; from < to; ++i) {
      arr[i] = from;
      from += step;
    }
  }
  if (from > to && step < 0) {
    for (unsigned i = 0; from > to; ++i) {
      arr[i] = from;
      from += step;
    }
  }
  return {num, arr};
}