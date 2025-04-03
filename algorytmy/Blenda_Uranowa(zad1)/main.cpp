#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    short int t;
    std::cin >> t;

    while(t--) {
        int n, d, m;
        std::cin >> n >> d >> m;

        int arrayC[n];
        int arrayK[n];
        int newN[n];
        for(int i = 0; i < n; i++) {
            std::cin >> arrayC[i] >> arrayK[i];
            newN[i] = arrayC[i] / arrayK[i] + 1;
        }

        int counter = 0;
        for(int i = 0; i < d; i++) {
            int days;
            std::cin >> days;

            long sum = 0;
            for(int j = 0; j < n; j++) {

                if(newN[j] <= days) {
                    sum += (2 * arrayC[j] - (newN[j] - 1) * arrayK[j]) * newN[j] / 2;
                } else {
                    sum += (2 * arrayC[j] - (days - 1) * arrayK[j]) * days / 2;
                }
            }

            if(sum >= m) {
                counter++;
            }
            std::cout << sum << " ";
        }
        std::cout << "\n" << counter << "\n";
    }
    return 0;
}

// 2 3 100      n, d, m
// 20 10        C1, K1
// 30 5         C2, K2
// 5 1 100      d1, d2, d3