bool _debug = false;

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef uint64_t lan;
typedef uint64_t numoflan;
// 임의의 숫자(자르는 랜선길이)가 주어졌을 때, 잘라진 랜선의 개수를 세고 충분하면 true
bool cutcheck(vector<lan> &mylan, numoflan &desirednum, lan testcut) {
    numoflan cutsum = 0, div;
    for (lan l : mylan) {
        // 모든 원소를 해당길이로 나눠서, 총 몇 가닥이 나오나 cutsum에 더해보자
        div = l / testcut;

        // 내림차순 정렬이 되었는데 0이 나오면 그 배열은 이미 가망없으니 중단 (너무 큰 길이를 대입함)
        if (div == 0) return false;
        cutsum += div;

        // 루프가 끝나기 전 언제라도 원하는 수치에 도달하면 Yes
        // (한 치수 더 길게 검사해서 No라면 정답 적중인데, 그것은 binarysearch가 해줄 것이므로 여기선 검사하지 말자)
        if (cutsum >= desirednum) return true; 
    }
    // 모든 랜선을 잘랐는데도 원하는 개수에 도달하지 못했을 경우 No (결국엔 정답보다 큰 길이를 대입함)
    return false;
}
//1 ~ 10000000000 (최대값 1000000 * 최대개수 10000) 이라는 범위 안에서 이분 탐색을 하면 최대 30회 안에 원하는 숫자를 찾을 수 있다.
uint16_t binarysearchcount = 0;
numoflan binarysearch(vector<lan> &mylan, numoflan &desirednum, lan from, lan to) {
    if (_debug) cout << "#" << ++binarysearchcount << " binary search \"" << desirednum << "\" in range (" << from << "~" << to << ")\n";
    if (_debug) cout << " - upper value first: " << to << " == answer? ";

    // 상한값을 조사해보자
    if (cutcheck(mylan, desirednum, to))
        if (!cutcheck(mylan, desirednum, to+1))
            return to; // 하나 큰 숫자가 나누기 실패하면, 이 숫자가 정답!
    if (_debug) cout << "...nope!\n";

    if (to == 2) return 1; // 0으로 나누기 방지
    lan mid = (from+to)/2;

    if (_debug) cout << " - and the middle of (" << from << "~" << to << "): " << mid << " == answer? ";
    // 중간값을 조사해보자
    if (cutcheck(mylan, desirednum, mid)) {
        if (!cutcheck(mylan, desirednum, mid+1)) return mid; // 하나 큰 숫자가 나누기 실패하면, 이 숫자가 정답!
        //상반 탐색
        if (_debug) cout << "...nope!\n   - narrowing down to the upper half ⬆ \n";
        return binarysearch(mylan, desirednum, mid+1, to-1);
    } else {
        //하반 탐색
        if (_debug) cout << "...nope!\n   - narrowing down to the lower half ⬇ \n";
        if (mid == 2) return 1; // 0으로 나누기 방지
        return binarysearch(mylan, desirednum, from, mid-1);
    }
}

int main() {
    numoflan currentnum, desirednum;
    cin >> currentnum >> desirednum;

    vector<lan> mylan;
    mylan.reserve(currentnum);
    lan buf, sumlan = 0; // 입력받으면서 총합도 덩달아 계산 (82, 89번줄에 사용)
    for (size_t i = 0; i < currentnum; ++i) {
        cin >> buf;
        mylan.push_back(buf);
        sumlan += buf;
    }
    // 내림차순 (큰수부터 자르기 시작하다가 어느순간 작은수에서 끊기는 식으로 진행하면 효율적이므로... cutcheck() 참조)
    sort(mylan.begin(), mylan.end(), greater<lan>{});

    if (_debug) cout << "mylan sorted: { ";
    if (_debug) for (auto m : mylan) cout << m << " ";
    if (_debug) cout << "} \n";

    lan maxlan = mylan[0];
    // 정답이 확실한 특별한 경우부터 빠르게 뱉기
    if (desirednum == 1) {
        cout << maxlan << endl; return 0; // 제일 큰 길이 하나만 선택
    } else if (currentnum == 1) {
        cout << maxlan / desirednum << endl; return 0; // 하나만 가지고 있으면 그대로 나누기
    } else if (desirednum == sumlan) {
        cout << 1 << endl; return 0; // 총합과 같이 나누면 길이가 1인 선들만 생김
    }

    // 답이 될 수 있는 상한선(sumlan / desirednum) 안에서 이분탐색한 결과를 뱉는다.
    // (반드시 1 이상의 값이 나오므로 탐색실패는 없다.)
    if (_debug) cout << "Max length: " << maxlan << "\nSum of lans: " << sumlan << "\nMaxcut candidate from: " << sumlan / desirednum << "\n";
    cout << binarysearch(mylan, desirednum, 0, sumlan / desirednum) << endl;
    /*
    //선형탐색ver: (수가 커지면 굉장히 오래 걸린다.)
    lan candidatenum = sumlan / desirednum;
    for (; candidatenum > 1; --candidatenum) {
        numoflan checkresult = cutcheck(mylan, candidatenum, desirednum);
        if (_debug) cout << "Checking length " << candidatenum << ": " << checkresult << " (" << (checkresult == desirednum? "Yes)" : "No)") << endl;
        if (chechresult) break;
    }
    cout << candidatenum << endl;
    */
}
/*
9 9
1 1 1 1 999999 1 1 1 1
111111

10 10
99999 99999 99999 99999 1000000 99999 99999 99999 99999 99999
100000

10 10
100001 100001 100001 100001 1000000 100001 100001 100001 100001 100001
100001
*/