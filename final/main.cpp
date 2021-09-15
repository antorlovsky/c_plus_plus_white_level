#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <iomanip>

using namespace std;

struct Year {
    Year() {
        value = 1;
    }
    explicit Year(int new_year) {
        value = new_year;
    }

    int value;
};

struct Month {
    Month() {
        value = 1;
    }
    explicit Month(int new_month) {
        if (new_month < 1 || new_month > 12)
            throw runtime_error("Month value is invalid: " + to_string(new_month));

        value = new_month;
    }

    int value;
};

struct Day {
    Day() {
        value = 1;
    }
    explicit Day(int new_day) {
        if (new_day < 1 || new_day > 31)
            throw runtime_error("Day value is invalid: " + to_string(new_day));

        value = new_day;
    }

    int value;
};

class Date {
public:
    Date() {
        year = Year(1);
        month = Month(1);
        day = Day(1);
    }
    Date(const Year& new_year, const Month& new_month, const Day& new_day) {
        year = new_year;
        month = new_month;
        day = new_day;
    }
    int GetYear() const {
        return year.value;
    }
    int GetMonth() const {
        return month.value;
    }
    int GetDay() const {
        return day.value;
    }
private:
    Year year;
    Month month;
    Day day;
};

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }

        return lhs.GetMonth() < rhs.GetMonth();
    }

    return lhs.GetYear() < rhs.GetYear();
}

istream& operator>>(istream& stream, Date& date) {
    string date_string;
    stream >> date_string;

    stringstream date_stream(date_string);

    int year, month, day;
    char dlm1, dlm2;

    date_stream >> year >> dlm1 >> month >> dlm2 >> day;

    if (!date_stream || dlm1 != '-' || dlm2 != '-' || date_stream.peek() != EOF)
        throw runtime_error("Wrong date format: " + date_string);

    date = {Year(year), Month(month), Day(day)};
    return stream;
}

ostream& operator<<(ostream& stream, const Date& date) {
    stream << setw(4) << setfill('0') << date.GetYear() << '-'
           << setw(2) << setfill('0') << date.GetMonth() << '-'
           << setw(2) << setfill('0') << date.GetDay();

    return stream;
}

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        data[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event) {
        if (data.count(date) > 0) {
            if (data[date].count(event) > 0) {
                data[date].erase(event);
                return true;
            }
        }

        return false;
    }
    int DeleteDate(const Date& date) {
        if (data.count(date) > 0) {
            int event_count = data[date].size();
            data[date].clear();

            return event_count;
        }

        return 0;
    }

    vector<string> Find(const Date& date) const {
        if (data.count(date) > 0) {
            return {begin(data.at(date)), end(data.at(date))};
        }

        return {};
    }

    void Print() const {
        for (const auto& record : data) {
            for (const string& event : record.second) {
                cout << record.first << ' ' << event << endl;
            }
        }
    }

private:
    map<Date, set<string>> data;
};

int main() {
    Database db;

    string command;
    while (getline(cin, command)) {
        stringstream command_stream(command);

        if (command_stream.eof())
            continue;

        string command_name;
        command_stream >> command_name;

        try {
            if (command_name == "Add") {
                Date date;
                command_stream >> date;

                string event;
                command_stream >> event;

                db.AddEvent(date, event);
            }
            else if (command_name == "Del") {
                Date date;
                command_stream >> date;

                if (!command_stream.eof()) {
                    string event;
                    command_stream >> event;

                    if (db.DeleteEvent(date, event))
                        cout << "Deleted successfully" << endl;
                    else
                        cout << "Event not found" << endl;
                }
                else {
                    int deleted_count = db.DeleteDate(date);
                    cout << "Deleted " << deleted_count << " events" << endl;
                }
            }
            else if (command_name == "Find") {
                Date date;
                command_stream >> date;

                vector<string> found_events = db.Find(date);
                for (const auto &event: found_events)
                    cout << event << endl;
            }
            else if (command_name == "Print") {
                db.Print();
            }
            else if (!command_name.empty()) {
                throw runtime_error("Unknown command: " + command_name);
            }
        }
        catch(const runtime_error& error) {
            cout << error.what();
            return 0;
        }
    }

    return 0;
}