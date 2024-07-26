#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;


int main() {
    vector<string> animals{ "Zebra"s, "Apple"s, "cat"s, "dog", "crocodile"s, "tiger"s };
    sort(animals.begin(), animals.end());
    for (const string& animal : animals) {
        cout << animal << ' ';
    }
} 