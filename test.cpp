#include <algorithm>// Содержит функцию lexicographical_compare
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <cctype> // содержит функцию tolower.
#include <numeric>
#include <sstream>
#include <map>

using namespace std;


int main() {
    map<string, int> legs_count = {{"rabbit"s, 4}, {"dog"s, 4}, {"chicken"s, 2}};
    const set<string> names = {"dog"s, "cat"s, "elephant"s};
    for (const string& name : names) {
        cout << name << " - "s << legs_count[name] << endl;
    }
     vector<int> prices = {100, 235, 333};
    cout << prices.at(3) << endl;
} 