bool debug = false;
#include <iostream>
#include <vector>
using namespace std;
typedef uint16_t n;
typedef struct party_t {
    bool revealtruth = false;
    vector<n> person;
} party_t;
typedef struct person_t {
    bool knowtruth = false;
    vector<n> party;
} person_t;
void print(vector<person_t>& person, vector<party_t>& party) {
    n i, j;
    cout << "< printing current data >\n";
    cout << " - person[" << person.size() << "] :\n";
    for (i = 0; i < person.size(); ++i) {
        cout << "    - person[" << i << "] :  [" << (person[i].knowtruth ? "V" : " ") << "] knowtruth\n";
        cout << "      - attending party list[" << person[i].party.size() << "] : [ ";
        for (j = 0; j < person[i].party.size(); ++j) cout << person[i].party[j] << " ";
        cout << "]\n";
    }
    cout << " - party[" << party.size() << "] :\n";
    for (i = 0; i < party.size(); ++i) {
        cout << "    - party[" << i << "] :  [" << (party[i].revealtruth ? "V" : " ") << "] revealtruth\n";
        cout << "      - attended person list[" << party[i].person.size() << "] : [ ";
        for (j = 0; j < party[i].person.size(); ++j) cout << party[i].person[j] << " ";
        cout << "]\n";
    }
}
void spread(vector<person_t>& person, vector<party_t>& party, bool init = true, n spreadingperson = 0) {
    if (init) {
        for (n iperson = 0; iperson < person.size(); ++iperson) if (person[iperson].knowtruth) spread(person, party, false, iperson);
    } else {
        person[spreadingperson].knowtruth = true;
        for (n iparty : person[spreadingperson].party) {
            party_t &p = party[iparty];
            if (!p.revealtruth) {
                p.revealtruth = true;
                for (n iperson : p.person) if (!person[iperson].knowtruth) spread(person, party, false, iperson);
            }
        }
    }
}
int main() {
    n numperson, numparty, numtruth, numattend, input, i, count_lying_party = 0;
    cin >> numperson >> numparty >> numtruth;
    vector<person_t> person(numperson);
    vector<party_t> party(numparty);
    for (i = 0; i < numtruth; ++i) {
        cin >> input; --input;
        person[input].knowtruth = true;
    }
    for (i = 0; i < numparty; ++i) {
        cin >> numattend;
        while (numattend--) {
            cin >> input; --input;
            party[i].person.push_back(input);
            person[input].party.push_back(i);
        }
    }
    if (debug) print(person, party);
    spread(person, party);
    if (debug) cout << "===== after spreading the truth =====\n";
    if (debug) print(person, party);
    if (debug) cout << "===== result output =====\n";
    for (i = 0; i < numparty; ++i) if (!party[i].revealtruth) ++count_lying_party;
    cout << count_lying_party << endl;
}