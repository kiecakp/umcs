#include <iostream>

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n;
    cin >> n;

    int board[n][n];
    int dp[n][n];
    int result = 0;

    // tworzymy tablice board
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> board[i][j];
        }
    }

    // tworzymy tablice dp
    dp[0][0] = board[0][0];

    for(int i = 1; i < n; i++){
        dp[i][0] = dp[i - 1][0] + board[i][0];
    }
    for(int j = 1; j < n; j++){
        dp[0][j] = dp[0][j - 1] + board[0][j];
    }
    for(int i = 1; i < n; i++){
        for(int j = 1; j < n; j++){
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + board[i][j];
        }
    }

    result += dp[n - 1][n - 1];

    // zerujemy tablilce board
    int i = n - 1;
    int j = n - 1;

    while(i > 0 || j > 0) {
        board[i][j] = 0;
        if(i > 0 && j > 0) {
            if(dp[i-1][j] < dp[i][j-1]) {
                j--;
            } else {
                i--;
            }
        } else if(i > 0) {
            i--;
        } else {
            j--;
        }
    }
    board[0][0] = 0;

    // liczymy ponownie tablice dp
    dp[0][0] = 0;

    for(int i = 1; i < n; i++){
        dp[i][0] = dp[i - 1][0] + board[i][0];
    }
    for(int j = 1; j < n; j++){
        dp[0][j] = dp[0][j - 1] + board[0][j];
    }
    for(int i = 1; i < n; i++){
        for(int j = 1; j < n; j++){
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + board[i][j];
        }
    }

    result += dp[n - 1][n - 1];

    cout << result;

    return 0;
}