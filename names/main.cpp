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

    for (const auto& item : names) {
        if (item.first <= year) {
            if (result.empty() || result.back() != item.second)
                result.push_back(item.second);
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
    Person(const string& name, const string& surname, int year) {
        name_history[year] = name;
        surname_history[year] = surname;
        birth_year = year;
    }
    void ChangeFirstName(int year, const string& first_name) {
        if (IsOlder(year))
            name_history[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        if (IsOlder(year))
            surname_history[year] = last_name;
    }
    string GetFullName(int year) const {
        if (!IsOlder(year))
            return "No person";

        return GetHistory({FindForYear(year, name_history)}) + ' ' + GetHistory({FindForYear(year, surname_history)});
    }
    string GetFullNameWithHistory(int year) const {
        if (!IsOlder(year))
            return "No person";

        return GetHistory(FindForYearWithHistory(year, name_history)) + ' ' + GetHistory(FindForYearWithHistory(year, surname_history));
    }
private:
    map<int, string> name_history;
    map<int, string> surname_history;
    int birth_year;

    bool IsOlder(int year) const {
        return year >= birth_year;
    }
};