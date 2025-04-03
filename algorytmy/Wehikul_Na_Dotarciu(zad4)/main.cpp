#include <iostream>
#include <string>

struct Data {
    int hz;
    int l;
    int counter = 1;
    Data* left;
    Data* right;
};

class DataTree {
    Data* root;

    Data* clearTree(Data* newData) {
        if(newData == NULL) {
            return NULL;
        }

        clearTree(newData->left);
        clearTree(newData->right);
        delete newData;

        return NULL;
    }

    Data* insert(int hz, int l, Data* newData) {
        if(newData == NULL) {
            newData = new Data;

            newData->hz = hz;
            newData->l = l;

            newData->left = newData->right = NULL;
        } else if(hz < newData->hz) {
            newData->left = insert(hz, l, newData->left);
        } else if(hz > newData->hz) {
            newData->right = insert(hz, l, newData->right);
        } else  {
            if(l < newData->l) {
                newData->left = insert(hz, l, newData->left);
            } else if(l > newData->l) {
                newData->right = insert(hz, l, newData->right);
            } else {
                newData->counter++;
            }
        }

        return newData;
    }

    void inorder(Data* newData) {
        if(newData == NULL) {
            return;
        }

        inorder(newData->left);

        for(int i = 0; i < newData->counter; i++) {
            std::cout << "(" << newData->hz << "," << newData->l << ") ";
        }

        inorder(newData->right);
    }

public:
    DataTree() {
        root = NULL;
    }

    ~DataTree() {
        root = clearTree(root);
    }

    void insert(int hz, int l) {
        root = insert(hz, l, root);
    }

    void printTree() {
        inorder(root);
    }
};

struct Node {
    int year;
    DataTree data;
    Node* left;
    Node* right;
};

class BTS {
    Node* root;

    Node* clearTree(Node* newYear) {
        if(newYear == NULL) {
            return NULL;
        }

        clearTree(newYear->left);
        clearTree(newYear->right);
        delete newYear;

        return NULL;
    }

    Node* insert(int year, int hz, int l, Node* newYear){
        if(newYear == NULL){
            newYear = new Node;

            newYear->year = year;

            newYear->data.insert(hz, l);

            newYear->left = newYear->right = NULL;
        } else if(year < newYear->year) {
            newYear->left = insert(year, hz, l, newYear->left);
        } else if(year > newYear->year) {
            newYear->right = insert(year, hz, l, newYear->right);
        } else {
            newYear->data.insert(hz, l);
        }

        return newYear;
    }


    void inorder(Node* newYear) {
        if(newYear == NULL) {
            return;
        }

        inorder(newYear->left);



        std::cout << newYear->year << ": ";
        newYear->data.printTree();
        std::cout << "\n";

        inorder(newYear->right);
    }

public:
    BTS() {
        root = NULL;
    }

    ~BTS() {
        root = clearTree(root);
    }

    void insert(int year, int hz, int l) {
        root = insert(year, hz, l, root);
    }

    void printTree() {
        inorder(root);
    }

    bool isEmpty() {
        return root == NULL;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    BTS tree;

    int n;
    int y, f, l;    // rok, czestotliowsc, dlugosc
    std::string result = "TAK";
    bool change = true;

    std::cin >> n;

    while(n--) {
        std::cin >> y >> f >> l;

        if(f <= 20000 && f >= 20) {

            float lInM = l / 100.0;
            float v = f * lInM;

            if(v <= 350 && v >= 313) {
                tree.insert(y, f, l);
                if(change == true && f > 325 || f < 275) {
                    result = "NIE";
                    change = false;
                }
            }
        }

    }

    if(tree.isEmpty()) {
        result = "NIE";
    }

    tree.printTree();
    std::cout << result;

    return 0;
}


//   WYJSCIE
// 234: (3000,11)
// 728: (300,108)
// 834: (109,300) (299,108) (299,109)
// 1073: (302,107)
// 1993: (30,1080) (300,108)
// 2222: (150,214) (302,107) (302,107)
// 2789: (29,1090)
// NIE