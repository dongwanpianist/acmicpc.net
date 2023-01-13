#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _NODE {
    int value;
    //_NODE* prev; // deque나 stack은 prev를 사용한다.
    _NODE* next;
} _NODE;

typedef struct queue queue;
struct queue {
    void (*init)(queue *this); // 초기화 함수
    void (*push)(queue *this, int value);
    int (*pop)(queue *this);
    int (*front)(queue *this);
    int (*back)(queue *this);
    bool empty;
    size_t size;
    struct _NODE* _front;
    struct _NODE* _back;
};
void queue__init(queue *this);
void queue__push(queue *this, int value);
int queue__pop(queue *this);
int queue__front(queue *this);
int queue__back(queue *this);

void queue__init(queue *this) { // 초기화 함수
    // 구조체에 나머지 함수들 연결
    this->init = queue__init;
    this->push = queue__push;
    this->pop = queue__pop;
    this->front = queue__front;
    this->back = queue__back;
    // 변수 초기화
    this->size = 0;
    this->empty = true;
    this->_front = NULL;
    this->_back = NULL;
}

void queue__push(queue *this, int value) {
    _NODE* newnode = (_NODE*)malloc(sizeof(_NODE));
    newnode->value = value;
    newnode->next = NULL;
    if (this->size == 0) { // 원소 하나짜리 배열 만들기 (front=back)
        //newnode->prev = NULL; // deque나 stack은 prev를 사용한다.
        this->_front = newnode;
        this->size = 1;
        this->empty = false;
    } else { // 뒤에 하나 추가하기 (queue니까 back만 갱신)
        //newnode->prev = this->_back; // deque나 stack은 prev를 사용한다.
        this->_back->next = newnode;
        this->size++;
    }
    this->_back = newnode;
}
int queue__pop(queue *this) {
    if (this->size == 0) return -1; // 이미 비어있음
    int popped_value = this->_front->value;
    if (this->size == 1) { // 빈 배열 만들기 (front=back=NULL)
        free(this->_front);
        this->_front = NULL;
        this->_back = NULL;
        this->size = 0;
        this->empty = true;
    } else { // 앞에서 하나 뽑기 (front만 갱신)
        _NODE* frontnext = this->_front->next;
        free(this->_front);
        this->_front = frontnext;
        //this->_front->prev = NULL; // deque나 stack은 prev를 사용한다.
        this->size--;
    }
    return popped_value;
}
int queue__front(queue *this) {
    if (this->size == 0) return -1;
    else return this->_front->value;
}
int queue__back(queue *this) {
    if (this->size == 0) return -1;
    else return this->_back->value;
}

bool strcompare(char* A, const char* B) {
    size_t cursor = 0;
    while (A[cursor] != 0) {
        if (A[cursor] == B[cursor]) cursor++;
        else return false;
    }
    return true;
}
int main() {
    queue myQ;
    queue__init(&myQ); // 초기화함수 호출 (C++ 느낌아니까)

    int N, _input, _output;
    char str[7];

    scanf("%d", &N);
    while (N--) {
        scanf("%s", str);
        if (strcompare(str, "push")) {
            scanf("%d", &_input);
            myQ.push(&myQ, _input);
            continue; // 출력안함
        } else if (strcompare(str, "pop")) {
            _output = myQ.pop(&myQ);
        } else if (strcompare(str, "size")) {
            _output = myQ.size;
        } else if (strcompare(str, "empty")) {
            _output = myQ.empty;
        } else if (strcompare(str, "front")) {
            _output = myQ.front(&myQ);
        } else if (strcompare(str, "back")) {
            _output = myQ.back(&myQ);
        }
        printf("%d\n", _output);
    }
    return 0;
}