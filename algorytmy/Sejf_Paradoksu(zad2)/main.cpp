#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    unsigned int t;
    int n;
    std::cin >> t;

    while (t--) {
        std::cin >> n;
        std::string arrayIndex[n];
        int arrayM[n];
        long sum = 0;
        long result = 0;

        for(int i = 0; i < n; i++) {
            std::cin >> arrayIndex[i] >> arrayM[i];
        }


        int temp;
        std::string tempS;
        int j;

        for(int i = 1; i < n; i++) {
            if(arrayM[i] < arrayM[i - 1]) {
                temp = arrayM[i];
                tempS = arrayIndex[i];

                for(j = i - 1; j >= 0 && arrayM[j] > temp; j--){
                    arrayM[j + 1] = arrayM[j];
                    arrayIndex[j + 1] = arrayIndex[j];
                }
                arrayM[j + 1] = temp;
                arrayIndex[j + 1] = tempS;
            }
        }



        // SHELL SORT
        // for(int part = n / 2; part > 0; part /= 2) {
        //     for(int i = part; i < n; i++) {
        //         int temp = arrayM[i];
        //         std::string tempS = arrayIndex[i];
        //
        //         int j = i;
        //         while(j >= part && arrayM[j - part] > temp) {
        //             arrayM[j] = arrayM[j - part];
        //             arrayIndex[j] = arrayIndex[j - part];
        //
        //             j -= part;
        //         }
        //
        //         arrayM[j] = temp;
        //         arrayIndex[j] = tempS;
        //     }
        // }

        // BUBBLE SORT
        // for(int i = 0; i < n-1; ++i) {
        //     for(int j = 0; j < n - i - 1; ++j) {
        //         if(arrayM[j] > arrayM[j + 1]) {
        //             int temp = arrayM[j];
        //             arrayM[j] = arrayM[j + 1];
        //             arrayM[j + 1] = temp;
        //
        //             std::string tempS = arrayIndex[j];
        //             arrayIndex[j] = arrayIndex[j + 1];
        //             arrayIndex[j + 1] = tempS;
        //         }
        //     }
        // }

        for(int i = 0; i < n; i++) {
            sum += arrayM[i];
            result += sum;
        }
        std::cout << result << "\n";
        for(int i = 0; i < n; i++) {
            std::cout << arrayIndex[i] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}


// 2
// 5
// rower_elektryczny-1453 12
// smartfon-1890 1
// dron_z_kamera-2000pne 4
// przenosna_lodowka-753 8
// teleporter_do_kawy-2024 4
// 3
// skaner_mysli-1984 7
// teletransporter-3210pne 133
// noktowizor-1410 1