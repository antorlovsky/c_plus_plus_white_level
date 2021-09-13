#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
    int Q;
    cin >> Q;

    map<set<string>, int> routes;

    while (Q > 0) {
        int N;
        cin >> N;

        set<string> stops;

        for (int i = 0; i < N; ++i) {
            string s;
            cin >> s;
            stops.insert(s);
        }

        if (routes.count(stops) == 0) {
            int route_number = routes.size() + 1;
            routes[stops] = route_number;

            cout << "New bus " << route_number << endl;
        }
        else {
            cout << "Already exists for " << routes[stops] << endl;
        }

        --Q;
    }
    return 0;
}