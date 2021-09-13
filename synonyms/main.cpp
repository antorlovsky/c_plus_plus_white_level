#include <iostream>
#include <set>
#include <map>
#include <string>

using namespace std;

int main() {
    int Q;
    cin >> Q;

    map<string, set<string>> dict;

    while (Q > 0) {
        string command;
        cin >> command;

        if (command == "ADD") {
            string word1, word2;
            cin >> word1 >> word2;

            dict[word1].insert(word2);
            dict[word2].insert(word1);
        }
        else if (command == "COUNT") {
            string word;
            cin >> word;

            cout << dict[word].size() << endl;
        }
        else if (command == "CHECK") {
            string word1, word2;
            cin >> word1 >> word2;

            bool are_synonyms = false;

            if (dict.count(word1) == 1 && dict[word1].count(word2) == 1)
                are_synonyms = true;
            else if (dict.count(word2) == 1 && dict[word2].count(word1) == 1)
                are_synonyms = true;

            cout << (are_synonyms ? "YES" : "NO") << endl;
        }

        --Q;
    }

    return 0;
}
