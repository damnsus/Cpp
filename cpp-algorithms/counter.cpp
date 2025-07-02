#include <iostream>
#include <vector>

int Counter(std::vector<int> &v, int pos) {
    int pivot = v[pos];
    int i = 0;
    for (int j = pos + 1; j < v.size(); ++j) {
        if (v[j] < pivot) {
            ++i;
        }
    }
    v[pos] = i;
    return (i + 1);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n, 0);
    int a;
    for (int i = 0; i < n; ++i) {
        std::cin >> a;
        vec[i] = a;
    }
    for (int i = 0; i < n; ++i) {
        Counter(vec, i);
        std::cout << vec[i] << " ";
    }
}