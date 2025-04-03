#include <iostream>
#include <climits>

using namespace std;

int minSum = INT_MAX;
int* result = NULL;

void findPath(int col, int **arr, int size, int path[], bool visited[], int sum) {
    if(sum >= minSum) {
        return;
    }

    if(col == size) {
        minSum = sum;

        for (int i = 0; i < size; i++) {
            result[i] = path[i];
        }

        return;
    }

    for(int i = 0; i < size; i++) {
        if(visited[i] == false) {
            visited[i] = true;
            path[col] = i;

            findPath(col + 1, arr, size, path, visited, sum + arr[i][col]);

            visited[i] = false;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

// inicjalizacja zmiennych/tablic
    int n;
    cin >> n;

    int** arr = new int*[n];
    for(int i = 0; i < n; i++) {
        arr[i] = new int[n];
    }

    int* path = new int[n];
    bool* visited = new bool[n];

    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }

    result = new int[n];

// wywolanie funkcji
    findPath(0, arr, n, path, visited, 0);

    for(int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }

    delete[] result;
    delete[] visited;
    delete[] path;
    for(int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
}