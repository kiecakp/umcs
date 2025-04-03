#include <iostream>
#include <cfloat>
#include <iomanip>

using namespace std;

struct Backet {
    float min;
    float max;
    bool isEmpty;

    Backet() {
        min = FLT_MAX;
        max = FLT_MIN;
        isEmpty = true;
    }
};

void backetSort(float arr[], float range, int n, float min) {
    Backet backets[n];

    for(int i = 0; i < n; i++) {
        int index = (arr[i] - min) / range;

        if (index >= n) {
            index = n - 1;
        }

        if(backets[index].isEmpty == true) {
            backets[index].min = arr[i];
            backets[index].max = arr[i];
            backets[index].isEmpty = false;
        }else {
            if(arr[i] < backets[index].min) {
                backets[index].min = arr[i];
            }else if(arr[i] > backets[index].max) {
                backets[index].max = arr[i];
            }
        }
    }

    float result = FLT_MIN;
    float temp;
    float previousMax = min;

    for(int i = 0; i < n; i++) {
        if(backets[i].isEmpty == false) {
            temp = backets[i].min - previousMax;
            if(temp > result) {
                result = temp;
            }

            previousMax = backets[i].max;
        }
    }

    cout << fixed << setprecision(4) << result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n;
    cin >> n;
    float arr[n];
    float maxValue = FLT_MIN;
    float minValue = FLT_MAX;

    for(int i = 0; i < n; i++) {
        cin >> arr[i];
        if(arr[i] < minValue) {
            minValue = arr[i];
        }else if(arr[i] > maxValue) {
            maxValue = arr[i];
        }
    }

    float range = (maxValue - minValue) / (n - 1);

    backetSort(arr, range, n, minValue);

    return 0;
}