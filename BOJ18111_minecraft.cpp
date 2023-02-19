#include <iostream>
#include <vector>
using namespace std;
typedef uint32_t altitude;
vector<altitude> mymap;
int32_t inventory;
uint32_t answer_mintime = 0xFFFFFFFFU;
altitude answer_mintimemaxheight = 0;

void height_check(altitude height) {
    int32_t needpopdown = 0, needaddup = 0;
    for (altitude &height_map : mymap) {
        if (height_map > height) needpopdown += (height_map - height);
        else if (height_map < height) needaddup += (height - height_map);
    }
    if (inventory + needpopdown - needaddup < 0) return; // 높이기 위해 블록을 가져올 인벤토리 수량이 부족하기 때문에, 이 높이는 불가능
    uint32_t time = needaddup + (needpopdown * 2);
    if (answer_mintime > time) { // 최소시간일 경우 갱신 (최고높이에서 낮춰가며 탐색하기 때문에, 동일시간의 최대높이는 추가로 비교할 필요가 없다.)
        answer_mintime = time;
        answer_mintimemaxheight = height;
    }
}
inline bool isflat() {
    for (uint32_t i = 1; i < mymap.size(); ++i) if (mymap[i] != mymap[i-1]) return false;
    return true;
}
int main() {
    cin.tie(NULL)->sync_with_stdio(false);
    uint32_t len, len2;
    cin >> len >> len2 >> inventory;
    len *= len2;
    mymap.resize(len);
    altitude bottom = 0xFFFFFFFFU, top = 0;
    while (len--) {
        cin >> mymap[len]; // 1차원 배열에 때려넣으며 최고높이 최저높이도 기록 (brute-force 탐색범위를 줄이기)
        if (bottom > mymap[len]) bottom = mymap[len];
        if (top < mymap[len]) top = mymap[len];
    }
    if (isflat()) {
        answer_mintime = 0;
        answer_mintimemaxheight = mymap[0];
    } else {
        for (altitude candidate = top; candidate >= bottom; --candidate) { // 최고 256회 brute-force 탐색
            height_check(candidate); // 최고 500x500=250000셀을 기준높이와 모두 비교
            if (candidate == bottom) break; // candidate 높이가 0일때 언더플로 방지
        }
    }
    cout << answer_mintime << " " << answer_mintimemaxheight << endl;
}