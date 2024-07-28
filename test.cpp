#include <algorithm>// Содержит функцию lexicographical_compare
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <cctype> // содержит функцию tolower.

using namespace std;

// Приводит строку к нижнему регистру
string ToLowerCase (string s) {
    for (char& ch: s) {
        ch=tolower(static_cast<unsigned char>(ch));
    }
    return s;
}







int main() {
    vector<string> animals{ "Zebra"s, "Apple"s, "cat"s, "dog", "crocodile"s, "tiger"s };
    sort(animals.begin(), animals.end(), [] (const string& left, const string& right){
        return ToLowerCase(left)<ToLowerCase(right);
    });
    for (const string& animal : animals) {
        cout << animal << ' ';
    }
}