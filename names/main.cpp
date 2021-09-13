#include <iostream>
#include <string>
#include <map>

using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        name_history[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        surname_history[year] = last_name;
    }
    string GetFullName(int year) {
        string name = "Incognito";

        for (const auto& item : name_history) {
            if (item.first > year)
                break;
            else
                name = item.second;
        }

        string surname = "Incognito";

        for (const auto& item : surname_history) {
            if (item.first > year)
                break;
            else
                surname = item.second;
        }

        if (name != "Incognito") {
            string result = name + ' ';
            result += (surname != "Incognito") ? surname : "with unknown last name";

            return result;
        }
        else if (surname != "Incognito") {
            return surname + " with unknown first name";
        }
        else {
            return "Incognito";
        }
    }
private:
    map<int, string> name_history;
    map<int, string> surname_history;
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}

