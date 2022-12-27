#define DEBUGGING false
// DEBUGGING을 true로 바꿔보시면 입력횟수가 무한으로 설정되고 출력기능을 활용하여 테스트를 할 수 있습니다.
// help와 exit명령어가 추가되어 있습니다.

#include <string>
#include <iostream>
using namespace std;

typedef struct deqNODE {
    int value;
    deqNODE* prev;
    deqNODE* next;
} deqNODE;

class deq {
private:
    deqNODE* _front;
    deqNODE* _back;
    int _size;
public:
    deq() { _size = 0; _front = NULL; _back = NULL; }
    int size() { return _size; }
    bool empty() { return (_size == 0); }
    void push_back(int newvalue) {
        _size++;
        deqNODE* newNODE = (deqNODE*)malloc(sizeof(deqNODE));
        newNODE->value = newvalue;
        if (_size == 1) { // 첫 추가: front와 back을 동일하게 지정
            newNODE->prev = NULL;
            newNODE->next = NULL;
            _front = newNODE;
            _back = newNODE;
        } else { // 2번째 이상 추가: back의 next로 추가
            _back->next = newNODE;
            newNODE->prev = _back;
            newNODE->next = NULL;
            _back = newNODE;
        }
    }
    void push_front(int newvalue) {
        _size++;
        deqNODE* newNODE = (deqNODE*)malloc(sizeof(deqNODE));
        memset(newNODE, 0, sizeof(deqNODE));
        newNODE->value = newvalue;
        if (_size == 1) { // 첫 추가: front와 back을 동일하게 지정
            newNODE->prev = NULL;
            newNODE->next = NULL;
            _front = newNODE;
            _back = newNODE;
        } else { // 2번째 이상 추가: front의 prev로 추가
            _front->prev = newNODE;
            newNODE->prev = NULL;
            newNODE->next = _front;
            _front = newNODE;
        }
    }
    int pop_back() {
        if (_size == 0) return -1; // 이미 비어있는 덱이라 수행할 것이 없음
        int poppedvalue = _back->value;
        _size--;
        if (_size == 0) { // 마지막 삭제: 모두 NULL 처리
            free(_back);
            _front = NULL;
            _back = NULL;
        } else { // 그 외: 뒤에서 하나 당김
            deqNODE* nextback = _back->prev;
            free(_back);
            _back = nextback;
            _back->next = NULL;
        }
        return poppedvalue;
    }
    int pop_front() {
        if (_size == 0) return -1; // 이미 비어있는 덱이라 수행할 것이 없음
        int poppedvalue = _front->value;
        _size--;
        if (_size == 0) { // 마지막 삭제: 모두 NULL 처리
            free(_front);
            _front = NULL;
            _back = NULL;
        } else { // 그 외: 앞에서 하나 당김
            deqNODE* nextfront = _front->next;
            free(_front);
            _front = nextfront;
            _front->prev = NULL;
        }
        return poppedvalue;
    }
    int front() {
        return (_size > 0 ? _front->value : -1);
    }
    int back() {
        return (_size > 0 ? _back->value : -1);
    }
    deqNODE* frontNODE() {
        return _front;
    }
    deqNODE* backNODE() {
        return _back;
    }
};

void printdeq(deq* thedeq) {
    deqNODE* cursor = thedeq->frontNODE();
    cout << "*** Deque NODE Inspector ***\n"
         << "  Size: " << thedeq->size() << ", Empty: " << (thedeq->empty() ? "1(true)" : "0(false)")
// MAC OSX 개발환경을 위해 색상 출력
#if defined __unix__ || defined __APPLE__
         << ", Front: [\033[1;32m" << thedeq->front() << "\033[0m], Back: [\033[1;35m" << thedeq->back() << "\033[0m"
#else
         << ", Front: [" << thedeq->front() << "], Back: [" << thedeq->back()
#endif
         << "]\n  Current NODEs: [ ";
    for (int j = 1; j <= thedeq->size(); j++) {
        if (cursor == NULL) {
            break;
        }
#if defined __unix__ || defined __APPLE__
        if (j == thedeq->size()) cout << "\033[1;35m";
        else if (j == 1) cout << "\033[1;32m";
        cout << cursor->value;
        if (j == thedeq->size()) cout << "\033[0m";
        else if (j == 1) cout << "\033[0m";
#else
        cout << thedeq->cursor->value;
#endif
        cursor = cursor->next;
        if (cursor != NULL) cout << ',';
        cout << ' ';
    }
    cout << ']' << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    deq mydeq;
    string input;
    int inputvalue;
#if DEBUGGING == true
    while (printdeq(&mydeq), cout << "Command > ", cin >> input, input != "exit") {
#else
    int numcommands;
    cin >> numcommands;
    while (numcommands--) {
        cin >> input;
#endif
        if (input == "push_back") {
            cin >> inputvalue;
            mydeq.push_back(inputvalue);
        } else if (input == "push_front") {
            cin >> inputvalue;
            mydeq.push_front(inputvalue);
        } else if (input == "help") {
            cout << "Available commands:\n size\n empty\n front\n back\n push_front [int]\n pop_front\n push_back [int]\n pop_back\n help\n exit\n";
        } else {
            if (input == "pop_back") cout << mydeq.pop_back();
            else if (input == "pop_front") cout << mydeq.pop_front();
            else if (input == "size") cout << mydeq.size();
            else if (input == "empty") cout << mydeq.empty();
            else if (input == "front") cout << mydeq.front();
            else if (input == "back") cout << mydeq.back();
            cout << "\n";
        }
    }
    return 0;
}
