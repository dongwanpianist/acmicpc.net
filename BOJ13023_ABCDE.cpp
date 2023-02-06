#include <iostream>
#include <vector>
using namespace std;
typedef uint16_t human;
typedef vector<human> relationlist;
vector<relationlist> mylist;
bool fivebridges(human A){
    for (human B : mylist[A]) {
        for (human C : mylist[B]) {
            if (C==A) continue;
            for (human D : mylist[C]) {
                if (D==A) continue;
                if (D==B) continue;
                for (human E : mylist[D]) {
                    if (E==A) continue;
                    if (E==B) continue;
                    if (E==C) continue;
                    return true;
                }
            }
        }
    }
    return false;
}
int main() {
    size_t N, M, rfrom, rto;
    cin >> N >> M;
    mylist.resize(N);

    while (M--) {
        cin >> rfrom >> rto;
        mylist[rfrom].push_back(rto);
        mylist[rto].push_back(rfrom);
    }

    for (human i = 0; i < N; ++i){
        if (fivebridges(i)) {
            cout << '1' << endl;
            return 0;
        }
    }
    cout << '0' << endl;
}