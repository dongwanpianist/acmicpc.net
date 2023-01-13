#include <iostream>
#include <queue>
#include <string>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 모든 연산을 알아서 해줄 기특한 C++ STL queue 소환!
    // -1을 출력하는 부분 만큼은 stl에 없으므로, 직접 구현하기
    queue<int> myq;
    int N, _input, _output;
    string _in;

    cin >> N;
    while (N--) {
        cin >> _in;
        if (_in == "push") {
            cin >> _input;
            myq.push(_input);
            continue; // 출력안함
        } else if (_in == "pop") {
            if (myq.empty()) _output = -1;
            else {
                _output = myq.front();
                myq.pop();
            }
        } else if (_in == "size") {
            _output = myq.size();
        } else if (_in == "empty") {
            _output = myq.empty();
        } else if (_in == "front") {
            if (myq.empty()) _output = -1;
            else _output = myq.front();
        } else if (_in == "back") {
            if (myq.empty()) _output = -1;
            else _output = myq.back();
        }
        cout << _output << "\n";
    }
}