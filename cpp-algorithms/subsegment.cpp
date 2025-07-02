#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    int N;
    std::cout << std::fixed << std::setprecision(10);
    std::cin >> N;
    double arr[N];
    double n;
    int i = 0;
    while (std::cin >> n) {
        if (i == 0) {
            arr[i] = std::log(n);
        } else {
            arr[i] = arr[i - 1] + std::log(n);
        }
        ++i;
        if (i == N) {
            break;
        }
    }
    int Q;
    std::cin >> Q;
    int l;
    int r;
    double ans = 0.0;
    const double e = exp(1);
    for (int i = 0; i < Q; ++i) {
        std::cin >> l >> r;
        if (l == 0) {
            ans = arr[r];
        } else {
            ans = arr[r] - arr[l - 1];
        }
        std::cout << std::pow(e, ans * (1.0 / (r - l + 1))) << std::endl;
        ans = 0.0;
    }
    return 0;
}
