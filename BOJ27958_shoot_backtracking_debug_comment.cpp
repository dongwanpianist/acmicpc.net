#include <iostream>
using namespace std;

bool _DEBUG = false;

typedef unsigned short int num; // 16비트 (0~65535)
typedef struct target {
    num current_hp;
    num max_hp;
} target;
typedef target map_t[8][8];
map_t mymap;
num mygun[5];
num max_map, max_shot, max_score = 0;

void print_map(map_t* m, num nth_shot) { // 디버그용 출력
    for (num i = 0; i < max_map; ++i) {
        for (num nth = 0; nth < nth_shot; ++nth) cout << '\t';
        for (num j = 0; j < max_map; ++j) {
            cout << '[' << (*m)[i][j].current_hp << '/' << (*m)[i][j].max_hp << ']' << '\t';
        }
        cout << '\n';
    }
}

void copy_map(map_t* m1, map_t* m2) {
    for (num i = 0; i < max_map; ++i)
    for (num j = 0; j < max_map; ++j)
        (*m2)[i][j] = (*m1)[i][j];
}

void shot_recursive(num nth_shot, map_t* current_map, num current_max_score) {
    // 이번 턴의 공격력: mygun[nth_shot]
    // 모든 행을 쐈을 경우 완전탐색
    for (num row = 0; row < max_map; ++row) {
        // parameter로 받은 current_map을 수정하면 안 되고
        // 각 행을 선택하는 모든 경우의 수마다 각각 맵을 복사해서 사용해야 함
        // (재귀하는 동안에는 메모리에 잘 남아있으니 포인터 걱정X)
        map_t new_map;
        copy_map(current_map, &new_map);
        num new_max_score = current_max_score;

        // 한발 쏘세요! (선택한 행의 왼쪽에서 오른쪽으로 총알이 나가며, 0이 아닌 최초의 칸 하나를 loop으로 찾아 current_hp를 깎는다.)
        for (num col = 0; col < max_map; ++col) {
            if (new_map[row][col].current_hp > 0) { // 맞았어요!
                // 보너스 표적: current_hp 무시하고 즉시사망 & 새로운 과녁을 퍼뜨리지도 않음
                if (new_map[row][col].max_hp >= 10) { 
                    new_max_score += new_map[row][col].max_hp;
                    new_map[row][col].current_hp = new_map[row][col].max_hp = 0;
                }
                // 일반 표적: 체력을 깎아서 1이상 남는지 0이 되는지 판정 (unsigned 변수라서 음수로 underflow되지 않게 조심)
                else if (new_map[row][col].current_hp > mygun[nth_shot]) {
                    new_map[row][col].current_hp -= mygun[nth_shot]; // hp만 깎고 종료
                } else {
                    // max_hp를 0으로 만들기 전에,
                    // max_hp/4 > 0인 경우에
                    // 사방으로 (hp가 0인 경우에만) max_hp/4를 퍼뜨리고 (current_hp와 max_hp를 동시에 갱신하고) 종료
                    if (new_map[row][col].max_hp / 4 > 0) {
                        if (row > 0)         if (new_map[row-1][col].current_hp == 0) new_map[row-1][col].current_hp = new_map[row-1][col].max_hp = (new_map[row][col].max_hp / 4);
                        if (col > 0)         if (new_map[row][col-1].current_hp == 0) new_map[row][col-1].current_hp = new_map[row][col-1].max_hp = (new_map[row][col].max_hp / 4);
                        if (row < max_map-1) if (new_map[row+1][col].current_hp == 0) new_map[row+1][col].current_hp = new_map[row+1][col].max_hp = (new_map[row][col].max_hp / 4);
                        if (col < max_map-1) if (new_map[row][col+1].current_hp == 0) new_map[row][col+1].current_hp = new_map[row][col+1].max_hp = (new_map[row][col].max_hp / 4);
                    }

                    // max_hp를 0으로 만들기 전에,
                    // 현재 턴의 시뮬레이션 최고점수를 더한다
                    new_max_score += new_map[row][col].max_hp;

                    // 과녁 죽음처리
                    new_map[row][col].current_hp = new_map[row][col].max_hp = 0;
                }
                // 과녁을 하나라도 맞추면 즉시 한발쏘세요loop 종료
                break;
            }
        }

        // debug: 쏘세요 결과 출력
        if (_DEBUG) {
            for (num nth = 0; nth < nth_shot; ++nth) cout << '\t';
            cout << "after shot " << nth_shot+1 << '/' << max_shot << " (power: " << mygun[nth_shot] << ") at row " << row+1 << ":\n";
            for (num nth = 0; nth < nth_shot; ++nth) cout << '\t';
            cout << "current score: " << new_max_score << '\n';
            print_map(&new_map, nth_shot);
        }

        if (nth_shot < max_shot - 1) {
            // 마지막 턴이 아닌 경우, 다음 턴 시뮬레이션을 이어서 진행 (재귀)
            shot_recursive(nth_shot + 1, &new_map, new_max_score);
        } else {
            // 마지막 턴인 경우, 재귀호출 대신에 최고기록 갱신을 시도
            if (max_score < new_max_score) max_score = new_max_score;
            // 여기서 return썼더니 마지막 샷에서 0번 row 이후의 모든 row가 연산되지 않음! for loop은 다 마쳐야 함.
        }
    }
}

int main() {
    // 입력
    cin >> max_map >> max_shot;
    num buf;
    for (num i = 0; i < max_map; ++i)
    for (num j = 0; j < max_map; ++j) {
        cin >> buf;
        mymap[i][j].max_hp = mymap[i][j].current_hp = buf;
    }
    for (num i = 0; i < max_shot; ++i) cin >> mygun[i];

    // debug: 입력에 대한 검사
    if (_DEBUG) {
        cout << "current input:\n";
        print_map(&mymap, 0);
    }

    // 계산
    shot_recursive(0, &mymap, 0);

    // 출력
    cout << max_score;
}
