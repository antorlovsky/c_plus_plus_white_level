#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

string FindForYear(int year, const map<int, string>& names) {
    string result;

    for (const auto& item : names) {
        if (item.first <= year)
            result = item.second;
        else
            break;
    }

    return result;
}

vector<string> FindForYearWithHistory(int year, const map<int, string>& names) {
    vector<string> result;

    string prev_name = "";

    for (const auto& item : names) {
        if (item.first <= year) {
            if (prev_name != item.second) {
                result.push_back(item.second);
                prev_name = item.second;
            }
        }
        else {
            break;
        }
    }

    return result;
}

string GetHistory(const vector<string>& history) {
    int history_length = history.size();
    string result = history[history_length - 1];

    if (history_length == 1)
        return result;

    result += " (";

    for (int i = history_length - 2; i >= 0; --i) {
        result += history[i];
        result += i > 0 ? ", " : ")";
    }

    return result;
}

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        name_history[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        surname_history[year] = last_name;
    }
    string GetFullName(int year) {
        string name = FindForYear(year, name_history);
        string surname = FindForYear(year, surname_history);

        bool has_name = !name.empty();
        bool has_surname = !surname.empty();

        if (has_name) {
            string result = name + ' ';
            result += has_surname ? surname : "with unknown last name";

            return result;
        }
        else if (has_surname) {
            return surname + " with unknown first name";
        }
        else {
            return "Incognito";
        }
    }
    string GetFullNameWithHistory(int year) {
        vector<string> names = FindForYearWithHistory(year, name_history);
        vector<string> surnames = FindForYearWithHistory(year, surname_history);

        bool has_names = !names.empty();
        bool has_surnames = !surnames.empty();

        if (has_names) {
            string result = GetHistory(names) + ' ';
            result += has_surnames ? GetHistory(surnames) : "with unknown last name";

            return result;
        }
        else if (has_surnames) {
            return GetHistory(surnames) + " with unknown first name";
        }
        else {
            return "Incognito";
        }
    }
private:
    map<int, string> name_history;
    map<int, string> surname_history;
};