#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define T unsigned short
typedef struct      circular_list_node      circular_list_node;
typedef struct      circular_list           circular_list;
typedef struct      circular_list__iterator circular_list__iterator;
void                circular_list__init  (circular_list* _this);
unsigned long long  circular_list__size  ();
bool                circular_list__empty ();
circular_list_node* circular_list__front ();
circular_list_node* circular_list__end   ();
void                circular_list__push  (T new_value);
T                   circular_list__pop   ();
circular_list_node* circular_list__iterator__cursor ();
circular_list_node* circular_list__iterator__assign (circular_list_node* new_position);
T                   circular_list__iterator__value  ();
circular_list_node* circular_list__iterator__prev   ();
circular_list_node* circular_list__iterator__next   ();
circular_list* this = NULL;

struct circular_list_node { // bi-directional 목적으로 prev, next 둘다 마련
    T                   value;
    circular_list_node* prev;
    circular_list_node* next;
};
struct circular_list__iterator {
  /* private: */ struct {
    circular_list_node*     cursor;
  } _;
    circular_list_node*     (*cursor) ();
    circular_list_node*     (*assign) (circular_list_node*);
    T                       (*value)  ();
    circular_list_node*     (*prev)   ();
    circular_list_node*     (*next)   ();
};
struct circular_list {
  /* private: */ struct {
    unsigned long long          size;
    circular_list_node*         tail; // 고정된 끝을 가리킴 = circular가 아닌 척을 할 수 있음
  } _;
    circular_list__iterator     iterator; // 중간부분도 탐색이 가능한 포인터 도우미(반복자) = circular의 특징을 살림
    void                        (*init)  (circular_list*);
    unsigned long long          (*size)  ();
    bool                        (*empty) ();
    circular_list_node*         (*front) ();
    circular_list_node*         (*end)   ();
    void                        (*push)  (T);
    T                           (*pop)   ();
};

void circular_list__init(circular_list* _this) {
    this = _this;
    this->_.size            = 0;
    this->_.tail            = NULL;
    this->init              = circular_list__init;
    this->size              = circular_list__size;
    this->empty             = circular_list__empty;
    this->front             = circular_list__front;
    this->end               = circular_list__end;
    this->push              = circular_list__push;
    this->pop               = circular_list__pop;
    this->iterator._.cursor = NULL;
    this->iterator.cursor   = circular_list__iterator__cursor;
    this->iterator.assign   = circular_list__iterator__assign;
    this->iterator.value    = circular_list__iterator__value;
    this->iterator.prev     = circular_list__iterator__prev;
    this->iterator.next     = circular_list__iterator__next;
}
unsigned long long  circular_list__size  () { if (this == NULL) return 0; return this->_.size; }
bool                circular_list__empty () { if (this == NULL) return 0; return (this->_.size == 0); }
circular_list_node* circular_list__front () { if (this == NULL) return NULL; return this->_.tail->next; }
circular_list_node* circular_list__end   () { if (this == NULL) return NULL; return this->_.tail; }
void circular_list__push(unsigned short newvalue) {
    if (this == NULL) return;
    circular_list_node* newnode = (circular_list_node*)malloc(sizeof(circular_list_node));
    newnode->value = newvalue;
    if (this->_.size == 0) newnode->prev = newnode->next = this->iterator._.cursor = this->_.tail = newnode;
    else { // end와 end->next의 사이, 혹은 iterator.cursor와 iterator.next의 사이에 삽입
        newnode->prev = this->iterator._.cursor;
        newnode->next = this->iterator._.cursor->next;
        newnode->prev->next = newnode->next->prev = newnode;
        if (this->iterator._.cursor == this->_.tail) this->iterator._.cursor = this->_.tail = newnode;
        else this->iterator._.cursor = newnode;
    }
    ++(this->_.size);
}
unsigned short circular_list__pop() {
    if (this == NULL) return 0; 
    if (this->_.size == 0) return 0; // exception
    circular_list_node* popping_node = this->iterator._.cursor;
    unsigned short popped_value = popping_node->value;
    popping_node->next->prev = popping_node->prev;
    popping_node->prev->next = popping_node->next;
    if (this->_.size == 0) this->_.tail = this->iterator._.cursor = NULL;
    else {
        this->iterator._.cursor = popping_node->prev;
        if (this->_.tail == popping_node) this->_.tail = popping_node->prev;
    }
    --(this->_.size);
    free(popping_node);
    return popped_value;
}
circular_list_node* circular_list__iterator__cursor () { if (this == NULL) return NULL; return this->iterator._.cursor; }
circular_list_node* circular_list__iterator__assign (circular_list_node* new_position) { if (this == NULL) return NULL; this->iterator._.cursor = new_position; return this->iterator._.cursor; }
unsigned short      circular_list__iterator__value  () { if (this == NULL) return 0; if (this->iterator._.cursor == NULL) return 0; return this->iterator._.cursor->value; }
circular_list_node* circular_list__iterator__prev   () { if (this == NULL) return NULL; if (this->iterator._.cursor == NULL) return NULL; this->iterator._.cursor = this->iterator._.cursor->prev; return this->iterator._.cursor; }
circular_list_node* circular_list__iterator__next   () { if (this == NULL) return NULL; if (this->iterator._.cursor == NULL) return NULL; this->iterator._.cursor = this->iterator._.cursor->next; return this->iterator._.cursor; }

int main() {
    circular_list circle;
    circle.init = circular_list__init;
    circle.init(&circle);
    unsigned short N, K, i;
    scanf("%hu %hu", &N, &K);
    for (i = 1; i <= N; ++i) circle.push(i);
    printf("<");
    while (!circle.empty()) {
        for(i = 1; i <= K; ++i) circle.iterator.next();
        unsigned short cursor = circle.pop();
        printf("%hu", cursor);
        if (!circle.empty()) printf(", ");
    }
    printf(">");
    return 0;
}