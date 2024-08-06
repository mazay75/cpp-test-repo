#include <algorithm>// Содержит функцию lexicographical_compare
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <cctype> // содержит функцию tolower.
#include <numeric>
#include <sstream>

using namespace std;

int main(){
const vector<int> v = {1, 3, 5, 2, 6, 7, 10, 2, 3};
cout << count_if(begin(v), end(v), [](int x) { return x > 5; }) << endl; 
}