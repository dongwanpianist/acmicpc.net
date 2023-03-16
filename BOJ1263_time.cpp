#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef struct task { uint32_t duration, deadline; } task;
bool operator<(const task &A, const task &B) {
    if (A.deadline > B.deadline) return true;
    if (A.deadline < B.deadline) return false;
    if (A.duration > B.duration) return true;
    return false;
}
int main() {
    uint16_t tasksize;
    cin >> tasksize;
    vector<task> tasks(tasksize);
    while (tasksize--) cin >> tasks[tasksize].duration >> tasks[tasksize].deadline;
    sort(tasks.begin(), tasks.end());
    uint32_t wakeuptime = tasks[0].deadline;
    for (task &t : tasks) {
        if (wakeuptime > t.deadline) wakeuptime = t.deadline;
        if (wakeuptime < t.duration) { cout << "-1"; return 0; }
        wakeuptime -= t.duration;
    }
    cout << wakeuptime;
}