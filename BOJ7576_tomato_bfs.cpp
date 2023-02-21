bool _debug = false;
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef uint16_t boxindex;
typedef struct coordinate { boxindex h, w; } coordinate;
class tomatocontainer {
private:
    vector<vector<char>> tomato;
    queue<coordinate> q;
    coordinate size;
    bool anythingchanged;
    inline void q_push(boxindex h, boxindex w) {
        if (tomato[h][w] == 0) {
            anythingchanged = tomato[h][w] = 1;
            q.push({h, w});
        }
    }
    inline void check_anythingleft() {
        for (size_t h = 0; h < size.h; ++h)
        for (size_t w = 0; w < size.w; ++w)
            if (tomato[h][w] == 0) { anythingleft = true; return; }
        anythingleft = false;
    }
public:
    bool anythingleft = false;
    int32_t daycount = 0;
    tomatocontainer() {}
    tomatocontainer& inputsize(bool reverse = true) {
        if (reverse) cin >> size.w >> size.h;
        else cin >> size.h >> size.w;
        tomato.resize(size.h, vector<char>(size.w));
        return *this;
    }
    tomatocontainer& inputtomato() {
        boxindex h, w;
        int16_t buf;
        for (h = 0; h < size.h; ++h)
        for (w = 0; w < size.w; ++w) {
            cin >> buf;
            tomato[h][w] = char(buf);
            if (buf == 1) q.push({h, w});
            else if (buf == 0) anythingleft = true;
        }
        return *this;
    }
    tomatocontainer& spread() {
        size_t i;
        coordinate t;
        if (anythingleft) while ((i = q.size())) {
            anythingchanged = false;
            while (i--) {
                t = q.front(); q.pop();
                if (0 < t.h) q_push(t.h-1, t.w);
                if (0 < t.w) q_push(t.h, t.w-1);
                if (t.h < size.h-1) q_push(t.h+1, t.w);
                if (t.w < size.w-1) q_push(t.h, t.w+1);
            }
            if (anythingchanged) {
                ++daycount;
                if (_debug) print();
            } else break;
        }
        check_anythingleft();
        return *this;
    }
    void print() {
        cout << "========= DAY " << daycount << " =========\n";
        cout << " - num of Q left for next turn: " << q.size() << "\n";
        for (size_t h = 0; h < size.h; ++h) {
            for (size_t w = 0; w < size.w; ++w) cout << int16_t(tomato[h][w]) << " ";
            cout << "\n";
        }
    }
};
int main() {
    tomatocontainer mybox;
    mybox.inputsize().inputtomato().spread();
    cout << (mybox.anythingleft ? -1 : mybox.daycount) << endl;
}