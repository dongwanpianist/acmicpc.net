bool _debug = false;

#include <string>
inline std::string magenta(std::string str) {
#if defined __unix__ || defined __APPLE__
    return "\033[1;35m" + str + "\033[0m";
#else
    return str;
#endif
}
inline std::string cyan(std::string str) {
#if defined __unix__ || defined __APPLE__
    return "\033[1;36m" + str + "\033[0m";
#else
    return str;
#endif
}
//=========================================

#include <iostream>
#include <vector>
using namespace std;

typedef uint32_t altitude;
vector<altitude> mymap;
int32_t inventory;

uint32_t answer_mintime = 0xFFFFFFFFU;
altitude answer_mintimemaxheight = 0;

void height_check(altitude height) {
    if (_debug) cout << " - Checking height '" << height << "'...\n";
    int32_t needpopdown = 0, needaddup = 0;
    for (altitude &height_map : mymap) {
        if (height_map > height) {
            needpopdown += (height_map - height);
            if (_debug) cout << "   - it is higher (" << height_map << " > " << height << "), needpopdown: " << needpopdown << "\n";
        } else if (height_map < height) {
            needaddup += (height - height_map);
            if (_debug) cout << "   - it is lower (" << height_map << " < " << height << "), needaddup: " << needaddup << "\n";
        } else {
            if (_debug) cout << "   - it is the same (" << height << ")\n";
        }
    }
    if (inventory + needpopdown - needaddup < 0) { // 높이기 위해 블록을 가져올 인벤토리 수량이 부족하기 때문에, 이 높이는 불가능
        if(_debug) cout << magenta("     - Not enough inventory! Making the height '") << height << magenta("' is NOT possibile.\n");
        return; 
    }
    int32_t time = needaddup + (needpopdown * 2);
    if (_debug) cout << cyan("     - Checking successful at height '") << height << cyan("', requied time: ") << time;
    if (answer_mintime > time) {
        if (_debug) cout << cyan(" << new minimum time!!");
        answer_mintime = time;
        answer_mintimemaxheight = height;
    }
    if (_debug) cout << "\n";
}
inline bool isflat() {
    for (uint32_t i = 1; i < mymap.size(); ++i)
        if (mymap[i] != mymap[i-1]) return false;
    return true;
}
inline void printarray() { cout << " - Current array: { "; for (altitude a : mymap) cout << a << " "; cout << "}\n"; }
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    uint32_t len, len2;
    cin >> len >> len2 >> inventory;
    len *= len2;
    mymap.resize(len);
    altitude bottom = 0xFFFFFFFFU, top = 0;
    while (len--) {
        cin >> mymap[len];
        if (bottom > mymap[len]) bottom = mymap[len];
        if (top < mymap[len]) top = mymap[len];
    }
    if (_debug) printarray();
    if (_debug) cout << " - Checking flatness...\n";
    if (isflat()) {
        if (_debug) cout << "  - Already flat!\n";
        answer_mintime = 0;
        answer_mintimemaxheight = mymap[0];
    } else {
        if (_debug) cout << "   - Not flat!\n - Lowest height(bottom): " << bottom << " / highest height(top): " << top << "\n";
        for (altitude candidate = top; candidate >= bottom; --candidate) {
            height_check(candidate);
            if (candidate == bottom) break;
        }
    }
    cout << answer_mintime << " " << answer_mintimemaxheight << endl;
}
/*
3 4 99
0 0 0 0 0 0 0 0 0 0 0 1
답: 2 0
오답: 11 1

3 4 0
0 0 0 0 0 0 0 0 0 0 0 5
답: 10 0

3 4 0
64 64 64 64 64 64 64 64 64 64 64 63
답: 22 63

3 4 8
64 64 64 64 64 64 64 64 64 64 64 50
답: 35 63

3 4 12
64 50 50 50 50 50 50 50 50 50 50 50
답: 28 50

3 4 0
64 64 64 64 64 64 64 64 64 64 64 0
답: 190 58
*/