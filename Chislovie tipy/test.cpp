

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
 /* vector <string> some_vector = {"one"s, "two"s, "three"s, "for"s, "five"s} ;
    for ( int i =0; i < static_cast <int> (some_vector.size()); ++i) {
        if (i == static_cast <int> (some_vector.size() - 1)) {
            cout<<some_vector.at(some_vector.size()-1);
        }
        else cout<<some_vector.at(i)<<", ";
        }
    cout<<endl;*/

/*    bool is_first = true;
vector <string> some_vector = {"one"s, "two"s, "three"s, "for"s, "five"s} ;
for (string s : some_vector) {
    if (!is_first) {
        cout << ", "s;
    }
    is_first = false;
    cout << s;
}

cout << endl;
*/

vector <int> some_vector = {2, 4, 5, 6, 7, 8, 9, 10};
int k = 0;
for (int number: some_vector) {
    if (number % 2  == 0) {
        k += 1;
    }    
}
cout<<k<<endl;
}