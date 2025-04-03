#include <iostream>
using namespace std;

// testy
// int arr[] = {-101, 25};
// int pos = 0;
//
// void next_test() {};
//
// int time_jump(unsigned int i) {
//     pos = (pos + i) % 2;
//     return arr[pos];
// }

// ------ KOD DO ZADANIA --------

bool isOverN(int A, int B, int C) {
    int cycles = 0;
    cycles = (A > B) + (A > C) + (B > C);
    return cycles % 2 != 0;
}

bool findMinMax(int &low, int &high) {
    int interval = 2;
    int a, b, c;
    a = time_jump(0);
    b = time_jump(interval / 2);
    c = time_jump(interval / 2);

    while(!isOverN(a, b, c)) {
        interval *= 2;
        a = time_jump(0);
        b = time_jump(interval / 2);
        c = time_jump(interval / 2);

        high = interval;
        low = interval / 2;

        if(a == c) {
            return true;
        }
    }

    return false;
}

int binarySearch(int low, int high) {
    int mid = (low + high) / 2;
    int a = time_jump(0);
    int b = time_jump(mid / 2);
    int c = time_jump(mid / 2);

    if(isOverN(a, b, c)) {
        if(low + 2 == high || a == c) {
            return mid;
        }else {
            return binarySearch(low, mid);
        }
    }else {
        if(low + 2 == high || a == c) {
            return mid;
        }else {
            return binarySearch(mid, high);
        }
    }
}

int main() {
    int low, high;
    int n;

    cin >> n;

    while(n--) {
        if(time_jump(0) == time_jump(1)) {
            cout << "1" << " ";
        }else if(time_jump(0) == time_jump(2)) {
            cout << "2" << " ";
        }else {
            if(!findMinMax(low, high)) {
                cout << binarySearch(low, high) << " ";
            }else {
                cout << high << " ";
            }
        }
        next_test();
    }

    // if(time_jump(0) == time_jump(1)) {
    //     cout << "1" << " ";
    // }else if(time_jump(0) == time_jump(2)) {
    //     cout << "2" << " ";
    // }else {
    //     if(!findMinMax(low, high)) {
    //         cout << binarySearch(low, high) << " ";
    //     }else {
    //         cout << high << " ";
    //     }
    // }

    return 0;
}