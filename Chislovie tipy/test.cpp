

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
#include <cmath>
#include <cstdint>
#include <limits>


using namespace std;

int main() {
    vector <int> some_vector = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int& number1: some_vector) {
        for (int number2: some_vector) {
            cout<<(number2 = number2 * number1)<<" "s;
        }
    cout<<endl;
    }
}