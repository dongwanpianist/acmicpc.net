bool debug = true;
#include <iostream>
#include <cmath>
#include <vector>
#include <deque>
#include <queue>
using namespace std;
const uint32_t _inf = 0xFFFFFFFFU;

// 백준 15638, 1978 풀면서 구현한 소수배열 생성 클래스
class primechecker {
private:
    vector<bool> isprime;
    size_t _max;
public:
    vector<size_t> arr;
    primechecker(size_t max, bool initarray = false) {
        _max = max;
        isprime.resize(max+1, true);
        isprime[0] = isprime[1] = false;
        size_t n, m;
        for (n = 2; n < (max/2)+1; ++n) {
            if (isprime[n] == false) continue;
            for (m = n * 2 ; m <= max; m += n) isprime[m] = false;
        }
        if (initarray) makearray(2, max);
    }
    vector<size_t>& makearray() { return
                    makearray(2, _max); }
    vector<size_t>& makearray(size_t min, size_t max) {
        arr.clear();
        if (max > _max) max = _max;
        for (size_t n = min; n <= max; ++n) if (isprime[n]) arr.push_back(n);
        return arr;
    }
    bool operator[](size_t index) { 
        if (index > _max) primechecker(index, false); // data보다 더 큰 수가 입력되면 확장한다.
        return isprime[index];
    }
};

// 좌표, 마을사이의 길, 마을의 정보를 담은 struct 정의
typedef struct coordinate {
    int16_t h;
    int16_t w;
    inline friend istream &operator>>(istream &ist, coordinate &location) {
        ist >> location.h >> location.w;
        return ist;
    }
} coordinate;
inline uint32_t operator<=>(const coordinate &A, const coordinate &B) { // distance
    return uint32_t(sqrt(pow(double(A.h)-double(B.h), 2) + pow(double(A.w)-double(B.w), 2)));
}
typedef uint16_t townindex;
typedef struct route {
    townindex destination;
    uint32_t distance;
} route;
typedef struct town {
    coordinate location;
    uint32_t totaldistance /* distance from start*/ = _inf; 
    vector<route> routes;
} routes;

inline void prime_distance_add_routes(vector<town> &towns, uint16_t i, primechecker &prime) {
    for (uint16_t ii = 0; ii < i; ++ii) { // 이미 입력된 자표들과 거리비교 후 조건충족(소수)시 양방향 route 추가
        uint32_t dist = towns[i].location <=> towns[ii].location;
        if (prime[dist]) {
            towns[i].routes.push_back({ii, dist});
            towns[ii].routes.push_back({i, dist});
        }
    }
}
inline int notfound() {
    cout << "-1" << endl;
    return 0;
}

// priority_queue를 사용한 Dijkstra algorithm :
// 닿을 수 있는 모든 route에 대해 시작점부터의 totaldistance를 최소값으로 갱신
typedef struct Qdata {
    townindex itown;
    uint32_t totaldistance;
} Qdata;
struct Qcompare {
    bool operator()(const Qdata &A, const Qdata &B) {
        return (A.totaldistance > B.totaldistance);
    }
};
void dijkstra(vector<town> &towns) {
    priority_queue<Qdata, deque<Qdata>, Qcompare> Q;
    Q.push({1, 0});
    while (!Q.empty()) {
        Qdata currentQ = Q.top();
        Q.pop();
        if (currentQ.itown == 0) {
            cout << currentQ.totaldistance << endl;
            return;
        }
        if (towns[currentQ.itown].totaldistance < currentQ.totaldistance) continue; // Q연산의 결과가 기존 town의 totaldistance보다 크면 삽질했으니 날려버림
        for (townindex i = 0; i < towns[currentQ.itown].routes.size(); ++i) { // 이 마을에서 뻗어나가는 모든 길들에 대해 newtotaldistance를 연산
            route &iroute = towns[currentQ.itown].routes[i];
            uint32_t newtotaldistance = currentQ.totaldistance + iroute.distance;
            townindex &targetindex = iroute.destination;
            town &targettown = towns[targetindex];
            if (newtotaldistance < targettown.totaldistance) { // 계산된 거리가 없을 경우 + 기존에 계산된 거리보다 더 짧은 거리로 계산된 경우
                targettown.totaldistance = newtotaldistance;
                Q.push({targetindex, newtotaldistance}); // 해당 target부터 뻗어나가는 길들을 모두 새로 계산해야 함
            }
        }
    }
    notfound();
}
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
inline void debug_print(vector<town> &towns, bool after_dijkstra) {
    cout << "=======================\n";
    cout << (after_dijkstra ? "After Dijkstra calculation:\n" : "Input data:\n");
    for (uint16_t i = 1; i < towns.size(); ++i) {
        cout << " - " << (i==1 ? cyan("Start #1") : "Town #" + to_string(i)) << " (" << towns[i].location.h << ", " << towns[i].location.w << "):\t";
        if (after_dijkstra) cout << "shortest distance from start: " << (i==1 ? cyan(to_string(towns[1].totaldistance)) : to_string(towns[i].totaldistance)) << " \t";
        cout << "{ ";
        for (uint16_t ii = 0; ii < towns[i].routes.size(); ++ii) {
            if (towns[i].routes[ii].destination == 1)
                cout << cyan("[" + to_string(towns[i].routes[ii].destination) + "](" + to_string(towns[i].routes[ii].distance) + ") ");
            else if (towns[i].routes[ii].destination == 0)
                cout << magenta("[" + to_string(towns[i].routes[ii].destination) + "](" + to_string(towns[i].routes[ii].distance) + ") ");
            else
                cout << "[" + to_string(towns[i].routes[ii].destination) + "](" + to_string(towns[i].routes[ii].distance) + ") ";
        }
        cout << "}\n";
    }
    cout << " - " << magenta("Goal #0") << " (" << towns[0].location.h << ", " << towns[0].location.w << "):\t";
    if (after_dijkstra) cout << "shortest distance from start: " << magenta(to_string(towns[0].totaldistance)) << "\n";
    else {
        cout << "{ ";
        for (uint16_t ii = 0; ii < towns[0].routes.size(); ++ii) {
            if (towns[0].routes[ii].destination == 1)
                cout << cyan("[" + to_string(towns[0].routes[ii].destination) + "](" + to_string(towns[0].routes[ii].distance) + ") ");
            else
                cout << "[" + to_string(towns[0].routes[ii].destination) + "](" + to_string(towns[0].routes[ii].distance) + ") ";
        }
        cout << "}\n";
    }
    cout << "=======================\n";
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    primechecker prime(8500, true); // 최대 좌표 거리 6000x6000의 빗변인 8485까지 포함한 소수확인기
    coordinate start, goal; uint16_t N;
    cin >> start >> goal >> N;
    vector<town> towns(N+2);
    towns[0] = {goal, 0xFFFFFFFFU, {}};
    towns[1] = {start, 0, {}};
    prime_distance_add_routes(towns, 1, prime);
    ++N;
    for (uint16_t i = 2; i <= N; ++i) {
        cin >> towns[i].location;
        prime_distance_add_routes(towns, i, prime);
    }
    if (debug) debug_print(towns, false);
    if (towns[0].routes.empty()) return notfound();
    if (towns[1].routes.empty()) return notfound();
    towns[0].routes.clear(); // goal에서부터 뻗어나가는 길은 연산하지 않도록 제거 (goal로 향하는 일방향 길만 남음)
    dijkstra(towns);
    if (debug) debug_print(towns, true);
}
