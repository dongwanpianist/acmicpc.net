#include <iostream>
using namespace std;
class binarytree {
private:
    uint8_t size;
    struct NODE {
        char id;
        char child_left;
        char child_right;
    } nodes[26];
public:
    binarytree() {
        size = 0;
        for (uint8_t i = 0; i < 26; ++i) {
            nodes[i].id = 'A'+i;
            nodes[i].child_left = '.';
            nodes[i].child_right = '.';
        }
    }
    inline binarytree& inputsize() {
        uint16_t input;
        cin >> input;
        size = uint8_t(input);
        return *this;
    }
    inline binarytree& inputdata() {
        char input1, input2, input3;
        for (uint8_t i = 0; i < size; ++i) {
            cin >> input1 >> input2 >> input3;
            nodes[input1-'A'].child_left  = input2;
            nodes[input1-'A'].child_right = input3;
        }
        return *this;
    }
    binarytree& print_preorder(char cursor = 'A') {
        if (cursor == '.') return *this;
        cout << nodes[cursor-'A'].id;
        print_preorder(nodes[cursor-'A'].child_left);
        print_preorder(nodes[cursor-'A'].child_right);
        return *this;
    }
    binarytree& print_inorder(char cursor = 'A') {
        if (cursor == '.') return *this;
        print_inorder(nodes[cursor-'A'].child_left);
        cout << nodes[cursor-'A'].id;
        print_inorder(nodes[cursor-'A'].child_right);
        return *this;
    }
    binarytree& print_postorder(char cursor = 'A') {
        if (cursor == '.') return *this;
        print_postorder(nodes[cursor-'A'].child_left);
        print_postorder(nodes[cursor-'A'].child_right);
        cout << nodes[cursor-'A'].id;
        return *this;
    }
    inline binarytree& ln() { cout << '\n'; return *this; }
};
int main() {
    binarytree mytree;
    mytree.inputsize().inputdata().print_preorder().ln().print_inorder().ln().print_postorder();
}