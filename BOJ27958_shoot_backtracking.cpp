#include <iostream>
using namespace std;
typedef unsigned short int num;
typedef struct target { num current_hp, max_hp; } target;
typedef target map_t[8][8];
map_t mymap;
num mygun[5];
num max_map, max_shot, max_score = 0;
inline void copy_map(map_t* m1, map_t* m2) {
    for (num i = 0; i < max_map; ++i)
    for (num j = 0; j < max_map; ++j)
        (*m2)[i][j] = (*m1)[i][j];
}
void shot_recursive(num nth_shot, map_t* current_map, num current_max_score) {
    for (num row = 0; row < max_map; ++row) {
        map_t new_map;
        copy_map(current_map, &new_map);
        num new_max_score = current_max_score;
        for (num col = 0; col < max_map; ++col) {
            if (new_map[row][col].current_hp > 0) {
                if (new_map[row][col].max_hp >= 10) { 
                    new_max_score += new_map[row][col].max_hp;
                    new_map[row][col].current_hp = new_map[row][col].max_hp = 0;
                } else if (new_map[row][col].current_hp > mygun[nth_shot]) {
                    new_map[row][col].current_hp -= mygun[nth_shot];
                } else {
                    if (new_map[row][col].max_hp / 4 > 0) {
                        if (row > 0)         if (new_map[row-1][col].current_hp == 0) new_map[row-1][col].current_hp = new_map[row-1][col].max_hp = (new_map[row][col].max_hp / 4);
                        if (col > 0)         if (new_map[row][col-1].current_hp == 0) new_map[row][col-1].current_hp = new_map[row][col-1].max_hp = (new_map[row][col].max_hp / 4);
                        if (row < max_map-1) if (new_map[row+1][col].current_hp == 0) new_map[row+1][col].current_hp = new_map[row+1][col].max_hp = (new_map[row][col].max_hp / 4);
                        if (col < max_map-1) if (new_map[row][col+1].current_hp == 0) new_map[row][col+1].current_hp = new_map[row][col+1].max_hp = (new_map[row][col].max_hp / 4);
                    }
                    new_max_score += new_map[row][col].max_hp;
                    new_map[row][col].current_hp = new_map[row][col].max_hp = 0;
                }
                break;
            }
        }
        if (nth_shot < max_shot - 1)
            shot_recursive(nth_shot + 1, &new_map, new_max_score);
        else if (max_score < new_max_score)
            max_score = new_max_score;
    }
}

int main() {
    cin >> max_map >> max_shot;
    num buf;
    for (num i = 0; i < max_map; ++i)
    for (num j = 0; j < max_map; ++j) {
        cin >> buf;
        mymap[i][j].max_hp = mymap[i][j].current_hp = buf;
    }
    for (num i = 0; i < max_shot; ++i)
        cin >> mygun[i];
    shot_recursive(0, &mymap, 0);
    cout << max_score;
}