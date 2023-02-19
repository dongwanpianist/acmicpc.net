#include <iostream>
#include <deque>
using namespace std;
typedef unsigned int n;
class circular_queue {
private:
    deque<n> structure;
    n size;
    int findresult;
public:
    n front = 0x7FFFFFFF;
    n count_rotation = 0;
    circular_queue() {}
    circular_queue(n newsize) { resize(newsize); }
    void resize(n newsize) {
        size = newsize;
        structure.resize(size);
        for (n i = 0; i < size; ++i) {
            structure[i] = i;
        }
        front = 0;
    }
    circular_queue& pop() {
        structure.pop_front();
        front = structure.front();
        --size;
        return *this;
    }
    circular_queue& find(n number) {
        int cursor = 0x7FFFFFFF;
        for (n i = 0; i < size; ++i) if (structure[i] == number) {
            cursor = i;
            if (cursor > (size/2)) cursor = cursor - size;
            break;
        }
        findresult = cursor;
        return *this;
    }
    circular_queue& rotate() {
        if (findresult != 0x7FFFFFFF) rotate(findresult);
        return *this;
    }
    circular_queue& rotate(int distance) {
        if (distance > 0) {
            for (n i = 0; i < distance; ++i) {
                n newval = structure.front();
                structure.pop_front();
                structure.push_back(newval);
                ++count_rotation;
            }
        } else {
            distance = -distance;
            for (n i = 0; i < distance; ++i) {
                n newval = structure.back();
                structure.pop_back();
                structure.push_front(newval);
                ++count_rotation;
            }
        }
        front = structure.front();
        return *this;
    }
};
int main() {
    n qsize, popsize, popnum;
    cin >> qsize >> popsize;
    circular_queue q(qsize);
    while (popsize--) {
        cin >> popnum;
        q.find(--popnum).rotate().pop();
    }
    cout << q.count_rotation << endl;
}