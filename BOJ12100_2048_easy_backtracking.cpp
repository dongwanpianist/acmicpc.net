// https://www.acmicpc.net/problem/12100
// dongwanpianist

#include <iostream>
#include <queue>

#define MAX_SIZE 20
template <typename Unit_Type>
struct coordinate {
    union { Unit_Type h, r, y; }; // call by anything you prefer!
    union { Unit_Type w, c, x; };
};

template <typename Data_Type>
class map2d {
protected:
    Data_Type           _data[MAX_SIZE][MAX_SIZE];
public:
    struct size {
        map2d* _; // parent
        union {
            coordinate<size_t> __; // raw coordinate
            struct {
                union { size_t h, r, y; }; // call by anything you prefer!
                union { size_t w, c, x; };
            };
        };
        operator coordinate<size_t>&() { return __; }
        explicit operator bool() const { return ((h > 0) && (w > 0)); }
        size& operator=(coordinate<size_t> s) { __ = s; return *this; }
        friend std::istream& operator>>(std::istream& ist, map2d::size& s) { return ist >> s.h >> s.w; }
        friend std::ostream& operator<<(std::ostream& ost, map2d::size& s) { return ost << '[' << s.h << " x " << s.w << ']'; }
    } size;
    struct size_square {
        map2d* _; // parent
        operator size_t&() { return min(_->size.h, _->size.w); }
        size_square& operator=(const size_t& s) { _->size.h = _->size.w = s; return *this; }
        friend std::istream& operator>>(std::istream& ist, map2d::size_square& s) { ist >> s._->size.h; s._->size.w = s._->size.h; return ist; }
        friend std::ostream& operator<<(std::ostream& ost, map2d::size_square& s) { return ost << min(s._->size.h, s._->size.w); }
    } size_square;
    struct empty_error : public std::runtime_error {
        empty_error(const size_t& h, const size_t& w) : std::runtime_error("map2d is empty (size: " + std::to_string(h) + " x " + std::to_string(w) + ")") { }
        empty_error(const coordinate<size_t>& hw) : std::runtime_error("map2d is empty (size: " + std::to_string(hw.h) + " x " + std::to_string(hw.w) + ")") { }
    };
    map2d() { size.__ = {0, 0}; size._ = size_square._ = this; }
    map2d(const size_t& HW) { resize(HW); }
    map2d(const size_t& H, const size_t& W) { resize(H, W); }
    map2d(const coordinate<size_t>& C) { resize(C); }
    map2d& resize(const size_t& HW) { size.h = size.w = HW; return *this; }
    map2d& resize(const size_t& H, const size_t& W) { size.h = H; size.w = W; return *this; }
    map2d& resize(const coordinate<size_t>& C) { size = C; return *this; }
    inline bool empty() { return ((size.h == 0) || (size.w == 0));}
    friend std::istream& operator>>(std::istream& ist, map2d& m) {
        if (m.empty()) throw empty_error(m.size);
        for (size_t h = 0; h < m.size.h; ++h)
        for (size_t w = 0; w < m.size.w; ++w)
            ist >> m._data[h][w];
        return ist;
    }
    map2d& operator=(const map2d& copier) {
        size.__ = copier.size.__;
        size._ = this; // reset reference at copy assignment
        size_square._ = this; // reset reference at copy assignment
        for (size_t h = 0; h < size.h; ++h)
        for (size_t w = 0; w < size.w; ++w)
            _data[h][w] = copier._data[h][w];
    }
    Data_Type* operator[](const size_t& row_index) { return _data[row_index]; }
    Data_Type& operator[](const coordinate<size_t>& cursor) { return _data[cursor.h][cursor.w]; }
    Data_Type max() {
        if (empty()) throw empty_error(size);
        Data_Type maxvalue = _data[0][0];
        for (size_t h = 0; h < size.h; ++h)
        for (size_t w = 0; w < size.w; ++w)
            if (maxvalue < _data[h][w])
                maxvalue = _data[h][w];
        return maxvalue;
    }
};

class map2048 : public map2d<uint16_t> {
public:
    enum direction: uint8_t { up, down, left, right };
    map2048& swipe(const uint8_t& d) { if ((d >= 0) && (d <= 3)) return swipe(direction(d)); else return *this; }
    map2048& swipe(const direction& d) {
        if (empty()) return *this;
        bool stacked;
        size_t moveto;
        /// swipe = align -> merge (only once) -> align
        if (d == map2048::up) {
            for (size_t w = 0; w < size.w; ++w) {
                stacked = false, moveto = 0;
                for (size_t h = 0; h < size.h; ++h) if (_data[h][w] != 0) {
                    if (!stacked) stacked = true; else ++moveto;
                    if (moveto != h) _data[moveto][w] = _data[h][w],  _data[h][w] = 0;
                }
                for (size_t h = 0; h < size.h - 1; ++h)
                    if (_data[h][w] == _data[h+1][w])
                        _data[h][w] <<= 1, _data[h+1][w] = 0;
                stacked = false, moveto = 0;
                for (size_t h = 0; h < size.h; ++h) if (_data[h][w] != 0) {
                    if (!stacked) stacked = true; else ++moveto;
                    if (moveto != h) _data[moveto][w] = _data[h][w],  _data[h][w] = 0;
                }
            }
        } else if (d == map2048::down) {
            for (size_t w = 0; w < size.w; ++w) {
                stacked = false, moveto = size.h - 1;
                for (size_t h = size.h; h-- > 0;) if (_data[h][w] != 0) {
                    if (!stacked) stacked = true; else --moveto;
                    if (moveto != h) _data[moveto][w] = _data[h][w],  _data[h][w] = 0;
                }
                for (size_t h = size.h; h-- > 1;)
                    if (_data[h][w] == _data[h-1][w])
                        _data[h][w] <<= 1, _data[h-1][w] = 0;
                stacked = false, moveto = size.h - 1;
                for (size_t h = size.h; h-- > 0;) if (_data[h][w] != 0) {
                    if (!stacked) stacked = true; else --moveto;
                    if (moveto != h) _data[moveto][w] = _data[h][w],  _data[h][w] = 0;
                }
            }
        } else if (d == map2048::left) {
            for (size_t h = 0; h < size.h; ++h) {
                stacked = false, moveto = 0;
                for (size_t w = 0; w < size.w; ++w) if (_data[h][w] != 0) {
                    if (!stacked) stacked = true; else ++moveto;
                    if (moveto != w) _data[h][moveto] = _data[h][w],  _data[h][w] = 0;
                }
                for (size_t w = 0; w < size.w - 1; ++w)
                    if (_data[h][w] == _data[h][w+1])
                        _data[h][w] <<= 1, _data[h][w+1] = 0;
                stacked = false, moveto = 0;
                for (size_t w = 0; w < size.w; ++w) if (_data[h][w] != 0) {
                    if (!stacked) stacked = true; else ++moveto;
                    if (moveto != w) _data[h][moveto] = _data[h][w],  _data[h][w] = 0;
                }
            }
        } else { // right (and any other erroneous values)
            for (size_t h = 0; h < size.h; ++h) {
                stacked = false, moveto = size.w - 1;
                for (size_t w = size.w; w-- > 0;) if (_data[h][w] != 0) {
                    if (!stacked) stacked = true; else --moveto;
                    if (moveto != w) _data[h][moveto] = _data[h][w],  _data[h][w] = 0;
                }
                for (size_t w = size.w; w-- > 1;)
                    if (_data[h][w] == _data[h][w-1])
                        _data[h][w] <<= 1, _data[h][w-1] = 0;
                stacked = false, moveto = size.w - 1;
                for (size_t w = size.w; w-- > 0;) if (_data[h][w] != 0) {
                    if (!stacked) stacked = true; else --moveto;
                    if (moveto != w) _data[h][moveto] = _data[h][w],  _data[h][w] = 0;
                }
            }
        }
        return *this;
    }
};

using namespace std;
int main() {
    map2048 mymap;
    cin >> mymap.size_square >> mymap;
    /* // test simulation
    cout << "Map Size: " << mymap.size << '\n';
    while (1) {
        cout << "Command > ";
        char instruction;
        cin >> instruction;
        if (instruction >= 'A' && instruction <= 'Z') instruction -= ('A'-'a');
        if (instruction == 'u') mymap.swipe(0);
        if (instruction == 'd') mymap.swipe(1);
        if (instruction == 'l') mymap.swipe(2);
        if (instruction == 'r') mymap.swipe(3);
        if (instruction == 'x') break;
        if (instruction == 'q') break;
        cout << "==================\n";
        for (int i = 0; i < mymap.size.h; ++i) {
            for (int j = 0; j < mymap.size.w; ++j)
                cout << mymap[i][j] << ' ';
            cout << '\n';
        }
        cout << "Max value: " << mymap.max();
        cout << "\n==================\n";
    }
    */
    // backtracking simulation
    uint16_t max_score = 0;
    struct simulation_data { uint8_t steps; map2048 map; };
    queue<simulation_data> simulations;
    simulations.push({0, mymap});
    while (simulations.size()) {
        simulation_data simul = simulations.front();
        simulations.pop();
        if (simul.steps < 5) {
            ++simul.steps;
            for (uint8_t direction = 0; direction < 4; ++direction) {
                map2048 newmap = simul.map;
                newmap.swipe(direction);
                simulations.push({simul.steps, newmap});
            }
        } else {
            max_score = max(max_score, simul.map.max());
        }
    }
    cout << max_score;
}