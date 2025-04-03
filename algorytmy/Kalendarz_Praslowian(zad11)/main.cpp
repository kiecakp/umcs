#include <iostream>
#include <vector>

using namespace std;

vector<int> findPrimeDivisors() {
    int maxValue = 1000000;
    vector<int> divisors(maxValue + 1, 0);

    for (int i = 2; i <= maxValue; i++) {
        if (divisors[i] == 0) {
            for (int j = i; j <= maxValue; j += i) {
                divisors[j]++;
            }
        }
    }

    return divisors;
}

int quickSelect(vector<int> arr, int k){
    int pivot = arr[0];
    vector<int> A, B, C;

    for(int value : arr){
        if(value < pivot){
            A.push_back(value);
        }else if(value > pivot){
            C.push_back(value);
        }else{
            B.push_back(value);
        }
    }

    if ((k + 1) <= A.size()) {
        return quickSelect(A, k);
    } else if ((k + 1) > A.size() && (k + 1) <= (A.size() + B.size())) {
        return B[k - A.size()];
    } else {
        return quickSelect(C, k - (A.size() + B.size()));
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    vector<int> result;
    int t, n, number, k;

    vector<int> divisors = findPrimeDivisors();

    cin >> t;

    while (t--) {
        result.clear();
        cin >> n;

        while(n--){
            cin >> number;
            if (divisors[number] % 2 == 0) {
                result.push_back(number);
            }
        }

        cin >> k;
        if (k >= result.size()) {
            cout << "BRAK DANYCH\n";
        } else {
            int num = quickSelect(result, k);
            cout << num << "\n";
        }
    }
    return 0;
}