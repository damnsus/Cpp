#include <iostream>

int GetMin(int* arr, int n, int l, int r) {
    int lmin = arr[0];
    for (int i = 0; i < l; ++i) {
        if (lmin > arr[i]) {
            lmin = arr[i];
        }
    }
    int rmin = arr[n - 1];
    for (int i = n - 1; i >= r - 1; --i) {
        if (rmin > arr[i]) {
            rmin = arr[i];
        }
    }
    if (lmin > rmin) {
        return rmin;
    } else {
        return lmin;
    }
}

int main() {
    int N;
    std::cin >> N;
    int arr[N];
    int n;
    int i = 0;
    while (std::cin >> n) {
        arr[i] = n;
        ++i;
        if (i == N) {
            break;
        }
    }
    int Q;
    std::cin >> Q;
    int l;
    int r;
    int ans;
    while (Q != 0) {
        std::cin >> l >> r;
        ans = GetMin(arr, N, l, r);
        std::cout << ans << '\n';
        --Q;
    }
    return 0;
}