#include <iostream>
#include <vector>
using namespace std;
class binarytree {
private:
    uint32_t size;
    typedef struct NODE {
        uint32_t id;
        NODE* child_left;
        NODE* child_right;
    } NODE;
    vector<NODE> nodes;
    NODE* topnode;
    vector<uint32_t> preorder, inorder, postorder, temporder;
public:
    binarytree() {
        size = 0;
    }
    inline binarytree& inputsize() {
        cin >> size;
        nodes.resize(size+1);
        for (uint32_t i = 0; i <= size; ++i) nodes[i].id = i;
        preorder.reserve(size);
        inorder.resize(size);
        postorder.resize(size);
        temporder.resize(size+1);
        return *this;
    }
    inline binarytree& inputdata() {
        for (uint32_t i = 0; i < size; ++i) cin >> inorder[i], temporder[inorder[i]] = i;
        for (uint32_t i = 0; i < size; ++i) cin >> postorder[i];
        topnode = &nodes[postorder.back()];
        return *this;
    }
    binarytree& print_preorder() { return print_preorder(topnode); }
    //binarytree& print_preorder() { for (uint32_t i = 0; i < size; ++i) cout << preorder[i] << ' '; return *this; }
    binarytree& print_preorder(NODE* cursor) {
        if (cursor == NULL) return *this;
        cout << cursor->id << ' ';
        print_preorder(cursor->child_left);
        print_preorder(cursor->child_right);
        return *this;
    }
    binarytree& print_inorder() { return print_inorder(topnode); }
    binarytree& print_inorder(NODE* cursor) {
        if (cursor == NULL) return *this;
        print_inorder(cursor->child_left);
        cout << cursor->id << ' ';
        print_inorder(cursor->child_right);
        return *this;
    }
    binarytree& print_postorder() { return print_postorder(topnode); }
    binarytree& print_postorder(NODE* cursor) {
        if (cursor == NULL) return *this;
        print_postorder(cursor->child_left);
        print_postorder(cursor->child_right);
        cout << cursor->id << ' ';
        return *this;
    }
    binarytree& calc_preorder() { return calc_preorder(0, size-1, 0, size-1, 0, 0xFFFFFFFF); }
    binarytree& calc_preorder(int inbegin, int inend, int postbegin, int postend, bool side, uint32_t parent) {
        if (inbegin > inend || postbegin > postend) return *this;
        uint32_t &root = postorder[postend];
        if (parent != 0xFFFFFFFF) {
            if (side == 0) nodes[parent].child_left = &nodes[postorder[postend]];
            else nodes[parent].child_right = &nodes[postorder[postend]];
        }
        preorder.push_back(root);
        int index = temporder[root];
        int length = index - inbegin;
        calc_preorder(inbegin, index-1, postbegin, postbegin+length-1, 0, root);
        calc_preorder(index+1, inend, postbegin+length, postend-1, 1, root);
        return *this;
    }
};
int main() {
    cin.tie(0)->sync_with_stdio(0);
    binarytree mytree;
    mytree.inputsize().inputdata().calc_preorder().print_preorder();
}