#include <iostream>
#include <vector>

bool CanPlacePoints(std::vector<int> v, int k, int min) {
    int count = 1;
    int last_position = v[0];
    for(int i = 0; i < v.size(); ++i) {
        if (v[i] - last_position >= min) {
            count += 1;
            last_position = v[i];
        }
        if (count == k) {
            return true;
        }
    }
    return false;
}

int max_min_distance(int n, int k, std::vector<int> coordinates){
    int left = 0;
    int right = coordinates[n - 1] - coordinates[0];
    int result = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2; 
        if (CanPlacePoints(coordinates, k, mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

int main() {
    int n;
    int k;
    std::cin >> n >> k;
    std::vector<int> vec(n, 0);
    int a;
    for (int i = 0; i < n; ++i) {
        std::cin >> a;
        vec[i] = a;
    }
    std::cout << max_min_distance(n, k, vec);
}