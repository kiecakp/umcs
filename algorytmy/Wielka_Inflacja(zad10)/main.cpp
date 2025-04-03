#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class MinHeap {         // kopiec dla podwyzek
    vector<int> array;

    void heapify(int i) {       // funkcja ukladajaca hierarhie w kopcu
        int min = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int size = array.size();

        if (left < size && array[left] < array[min]) {
            min = left;
        }

        if (right < size && array[right] < array[min]) {
            min = right;
        }

        if (min != i) {
            swap(array[i], array[min]);
            heapify(min);
        }
    }

public:
    MinHeap() { }

    void insert(int value) {
        array.push_back(value);

        int i = array.size() - 1;

        while (i != 0 && array[(i - 1) / 2] >= array[i]) {
            swap(array[i], array[(i - 1) / 2]);

            i = (i - 1) / 2;
        }
    }

    void removeRoot() {
        if (array.empty()) {
            return;
        }

        swap(array[0], array[array.size() - 1]);

        array.pop_back();

        heapify(0);
    }

    int size() const {
        return array.size();
    }

    int getElement(int i) {
        return array[i];
    }
};

class MaxHeap {     // kopiec dla cen produktow
    vector<int> array;

    void heapify(int i) {       // funkcja dla hierarhi w kopcu
        int max = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int size = array.size();

        if (left < size && array[left] > array[max]) {
            max = left;
        }

        if (right < size && array[right] > array[max]) {
            max = right;
        }

        if (max != i) {
            swap(array[i], array[max]);
            heapify(max);
        }
    }

public:
    MaxHeap() { }

    void insert(int value) {
        array.push_back(value);

        int i = array.size() - 1;

        while (i != 0 && array[(i - 1) / 2] <= array[i]) {
            swap(array[i], array[(i - 1) / 2]);

            i = (i - 1) / 2;
        }
    }

    void changeRoot(int value) {
        if (!array.empty()) {
            if(array[0] > -value) {
                array[0] += value;
                heapify(0);
            }
        }
    }

    int size() const {
        return array.size();
    }

    void removeRoot() {
        if (array.empty()) {
            return;
        }

        swap(array[0], array[array.size() - 1]);

        array.pop_back();

        heapify(0);
    }

    int getElement(int i) {
        return array[i];
    }
};

int main() {
    MaxHeap products;          // kopiec dla cen produktow (max-heap)
    MinHeap priceIncrease;     // kopiec dla podwyzek (min-heap)

    unsigned int n;     // liczba przedsiebiorcow
    unsigned int o;     // liczba operacji do wykonania
    char flag;          // zmienna dla pobrania a (dodaj produkt) lub p (zmien cene)
    unsigned int p, t;  // cena w zl, podatek w %
    int x;              // o ile zmienic cene

    cin >> n;

    while(n--) {
        cin >> o;

        while(o--) {
            cin >> flag;

            if(flag == 'a') {
                cin >> p >> t;

                products.insert(p);
                priceIncrease.insert(t);
            } else if(flag == 'p') {
                cin >> x;
                products.changeRoot(x);
            }
        }

        int result = 0;

        while(products.size() > 0 && priceIncrease.size() > 0) {
            result += products.getElement(0) * priceIncrease.getElement(0);

            products.removeRoot();
            priceIncrease.removeRoot();
        }

        cout << result << "\n";
    }
    return 0;
}