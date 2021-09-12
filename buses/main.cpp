#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

void print_vector(const vector<string>& v, const string& exclude_value) {
    for (const auto& s : v) {
        if (s != exclude_value)
            cout << s << ' ';
    }

    cout << endl;
}

int main() {
    int Q;
    cin >> Q;

    map<string, vector<string>> stops_for_buses;
    map<string, vector<string>> buses_for_stops;

    while (Q > 0) {
        string command;
        cin >> command;

        if (command == "NEW_BUS") {
            string bus;
            int stop_count;
            cin >> bus >> stop_count;

            vector<string>& route = stops_for_buses[bus];
            route.resize(stop_count);

            for (auto& stop : route) {
                cin >> stop;
                buses_for_stops[stop].push_back(bus);
            }
        }
        else if (command == "BUSES_FOR_STOP") {
            string stop;
            cin >> stop;

            if (buses_for_stops.count(stop) == 0)
                cout << "No stop" << endl;
            else
                print_vector(buses_for_stops[stop], "");
        }
        else if (command == "STOPS_FOR_BUS") {
            string bus;
            cin >> bus;

            if (stops_for_buses.count(bus) == 0) {
                cout << "No bus" << endl;
            }
            else {
                for (const auto& stop : stops_for_buses[bus]) {
                    cout << "Stop " << stop << ": ";

                    if (buses_for_stops[stop].size() == 1)
                        cout << "no interchange" << endl;
                    else
                        print_vector(buses_for_stops[stop], bus);
                }
            }
        }
        else if (command == "ALL_BUSES") {
            if (stops_for_buses.empty()) {
                cout << "No buses" << endl;
            }
            else {
                for (const auto& route : stops_for_buses) {
                    cout << "Bus " << route.first << ": ";
                    print_vector(route.second, "");
                }
            }
        }

        --Q;
    }
    return 0;
}
