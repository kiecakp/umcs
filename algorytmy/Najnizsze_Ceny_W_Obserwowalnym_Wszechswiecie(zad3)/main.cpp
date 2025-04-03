#include <iostream>
#include <climits>

struct Client {
    long time;
    Client* next;

    Client(long time) {
        this->time = time;
        next = nullptr;
    }
};

class Queue {
public:
    Client* head;
    Client* tail;
    long clients;
    long totalTime;
    bool isOpen;

    Queue() {
        head = nullptr;
        tail = nullptr;
        clients = 0;
        totalTime = 0;
        isOpen = false;
    }

    bool isempty() {
        return clients == 0;
    }

    void addClient(long time) {
        Client* newClient = new Client(time);

        if(isempty()) {
            head = newClient;
            tail = newClient;
        } else {
            tail->next = newClient;
            tail = newClient;
        }
        clients++;
        totalTime += time;
    }

    void popClient() {
        if(!isempty()) {
            Client* temp = head;
            head = head->next;
            delete temp;
            clients--;
        }
    }

    void setf(bool f) {
        this->isOpen = f;
    }

    void scanProucts(long p) {
        if(!isOpen) {
            return;
        }
        while(p > 0 && !isempty()) {
            long decrement = std::min(p, head->time);
            p -= decrement;
            totalTime -= decrement;
            head->time -= decrement;
            if(head->time <= 0) {
                popClient();
                if(isempty()) {
                    break;
                }
            }
        }
    }
};

long fastestQueue(Queue* queues, long size) {
    long index = -1;
    long minTime = INT_MAX;
    for(int i = 0; i < size; i++) {
        if(queues[i].totalTime < minTime && queues[i].isOpen) {
            minTime = queues[i].totalTime;
            index = i;
        }
    }
    return index;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    long t, l, s, z;
    std::cin >> t >> l >> s >> z;
    Queue shop[l];

    while(t > 0) {
        char f;
        std::cin >> f;

        if(f == 'o') {
            long a;
            std::cin >> a;
            shop[a].setf(true);

        } else if(f == 'z') {
            long a;
            std::cin >> a;
            shop[a].setf(false);
            shop[a].popClient();

            while (shop[a].clients > 0) {
                Client* temp = shop[a].head;
                long index = fastestQueue(shop, l);
                shop[index].addClient(temp->time);
                shop[a].popClient();
            }
            shop[a].totalTime = 0;

        } else if(f == 'k') {
            long p, r;
            std::cin >> p >> r;
            bool lastLoop = false;
            if(p > t) {
                p = t;
                lastLoop = true;
            }
            for(int i = 0; i < l; i++) {
                shop[i].scanProucts(p);
            }
            if(lastLoop) {
                break;
            }
            long index = fastestQueue(shop, l);
            shop[index].addClient(z + (r * s));
            t -= p;

        }
    }

    for(int i = 0; i < l; i++) {
        if(i != l - 1) {
            if(shop[i].isOpen) {
                std::cout << "K" << i << ": " << shop[i].clients << "o " << shop[i].totalTime << "s, ";
            } else if(!shop[i].isOpen) {
                std::cout << "K" << i << ": z, ";
            }
        } else {
            if(shop[i].isOpen) {
                std::cout << "K" << i << ": " << shop[i].clients << "o " << shop[i].totalTime << "s";
            } else if(!shop[i].isOpen) {
                std::cout << "K" << i << ": z";
            }
        }


    }

    return 0;
}