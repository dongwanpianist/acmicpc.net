#include <iostream>
#include <string>
#include <stack>
using namespace std;
int main() {
    string input, output;
    stack<char> stacker;
    char topc;
    cin >> input;
    for (char &c : input) {
        if (c == '(') stacker.push(c);
        else if (c == ')') {
            while (!stacker.empty() && (topc = stacker.top(), topc != '(')) output += topc, stacker.pop();
            stacker.pop();
        } else if ((c == '*') || (c == '/')) {
            while (!stacker.empty() && (topc = stacker.top(), (topc == '*') || (topc == '/'))) output += topc, stacker.pop();
            stacker.push(c);
        } else if ((c == '+') || (c == '-')) {
            while (!stacker.empty() && (topc = stacker.top(), topc != '(')) output += topc, stacker.pop();
            stacker.push(c);
        } else output += c;
    }
    while (!stacker.empty()) output += stacker.top(), stacker.pop();
    cout << output << endl;
}