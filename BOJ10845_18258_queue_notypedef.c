#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _NODE {
    int value;
    //_NODE* prev; // deque나 stack은 prev를 사용한다.
    _NODE* next;
} _NODE;

bool empty = true;
size_t size = 0;
_NODE* _front = NULL;
_NODE* _back = NULL;

void push(int value) {
    _NODE* newnode = (_NODE*)malloc(sizeof(_NODE));
    newnode->value = value;
    newnode->next = NULL;
    if (size == 0) { // 원소 하나짜리 배열 만들기 (front=back)
        //newnode->prev = NULL; // deque나 stack은 prev를 사용한다.
        _front = newnode;
        size = 1;
        empty = false;
    } else { // 뒤에 하나 추가하기 (back만 갱신)
        //newnode->prev = _back; // deque나 stack은 prev를 사용한다.
        _back->next = newnode;
        size++;
    }
    _back = newnode;
}
int pop() {
    if (size == 0) return -1; // 이미 비어있음
    int popped_value = _front->value;
    if (size == 1) { // 빈 배열 만들기 (front=back=NULL)
        free(_front);
        _front = NULL;
        _back = NULL;
        size = 0;
        empty = true;
    } else { // 앞에서 하나 뽑기 (front만 갱신)
        _NODE* frontnext = _front->next;
        free(_front);
        _front = frontnext;
        //_front->prev = NULL; // deque나 stack은 prev를 사용한다.
        size--;
    }
    return popped_value;
}
int front() {
    if (size == 0) return -1;
    else return _front->value;
}
int back() {
    if (size == 0) return -1;
    else return _back->value;
}

bool strcompare(char* A, const char* B) {
    size_t cursor = 0;
    while (A[cursor] != 0) {
        if (B[cursor] == 0) return false; // 범위 초과 방지
        else if (A[cursor] == B[cursor]) cursor++;
        else return false;
    }
    return true;
}

int main() {
    int N, _input, _output = 0;
    char str[7];

    scanf("%d", &N);
    while (N--) {
        scanf("%s", str);
        if (strcompare(str, "push")) {
            scanf("%d", &_input);
            push(_input);
            continue; //출력안함
        } else if (strcompare(str, "pop")) {
            _output = pop();
        } else if (strcompare(str, "size")) {
            _output = size;
        } else if (strcompare(str, "empty")) {
            _output = empty;
        } else if (strcompare(str, "front")) {
            _output = front();
        } else if (strcompare(str, "back")) {
            _output = back();
        }
        printf("%d\n", _output);
    }
    return 0;
}