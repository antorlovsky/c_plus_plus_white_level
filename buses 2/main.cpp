#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

int main() {
    int Q;
    cin >> Q;

    map<vector<string>, int> routes;

    while (Q > 0) {
        int N;
        cin >> N;

        vector<string> stops(N);

        for (auto& s : stops)
            cin >> s;

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
