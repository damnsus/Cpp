int** MakeSpiral(unsigned n) {
  int** arr = new int*[n];
  for (unsigned i = 0; i < n; ++i) {
    arr[i] = new int[n];
  }
  unsigned num = 0;
  unsigned loopcounter = 1;
  unsigned raw = 0;
  unsigned column = 0;
  for (; loopcounter <= n / 2; ++loopcounter) {
    for (; column < n - loopcounter;) {
      arr[raw][column++] = ++num;
    }
    for (; raw < n - loopcounter;) {
      arr[raw++][column] = ++num;
    }
    for (; column > loopcounter - 1;) {
      arr[raw][column--] = ++num;
    }
    for (; raw > loopcounter - 1;) {
      arr[raw--][column] = ++num;
    }
    ++raw;
    ++column;
  }
  if (n % 2 == 1) {
    arr[n / 2][n / 2] = ++num;
  }
  return arr;
}