// QuickSort algorithm was taken from GeeksForGeeks
// https://www.geeksforgeeks.org/cpp-program-for-quicksort/

#include <iostream>
#include <vector>
#include <utility>

int partition(std::vector<int> &v, int begin, int end) {
    int pivot = v[end];
    int i = begin - 1;
    for (int j = begin; j < end; ++j) {
        if (v[j] <= pivot) {
            ++i;
            std::swap(v[i], v[j]);
        }
    }
    std::swap(v[i + 1], v[end]);
    return (i + 1);
}

void QSort(std::vector<int> &v, int begin, int end) {
    if (begin < end) {
        int p = partition(v, begin, end);
        QSort(v, begin, p - 1);
        QSort(v, p + 1, end);
    }
}

bool CheckLength(std::vector<int> v, int k, int length) {
    int end = v[0] + length;
    k--;
    for (int i = 0; i < v.size(); i++){
        if (end < v[i]){
            k--;
            end = v[i] + length;
            if (k < 0) return false;
        }
    }
    return true;
}

int Search(std::vector<int> v, int k) {
    int min = 0; 
    int max = v[v.size() - 1] - v[0];
    while(min != max)
    {
        int mid = min + (max - min) / 2;
        if (mid == max || mid == min) return max;

        if (CheckLength(v, k, mid)) max = mid;
        else min = mid;
    }
    
    return max;
}

int main() {
    int n;
    int k;
    std::cin >> n >> k;
    if (k == n) {
        std::cout << 0;
        return 0;
    }
    std::vector<int> vec(n, 0);
    int a;
    for (int i = 0; i < n; ++i) {
        std::cin >> a;
        vec[i] = a;
    }
    QSort(vec, 0, n - 1);
    std::cout << Search(vec, k);
    return 0;
}