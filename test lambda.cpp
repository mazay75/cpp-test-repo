#include <algorithm>// Содержит функцию lexicographical_compare
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <cctype> // содержит функцию tolower.
#include <numeric>
using namespace std;

int main() {
    
    // Лексикографически сравниваем векторы чисел
    vector<int> v1 = {3, 14, 15, 92};
    vector<int> v2 = {3, 14, 24};
    bool v1_precedes_v2 = lexicographical_compare(
        v1.begin(), v1.end(), // Первый диапазон
        v2.begin(), v2.end()  // Второй диапазон 
    );
// Ожидается, что v1_precedes_v2 == true
cout<<v1_precedes_v2<<endl;

    // Можно сравнивать и строки. Они рассматриваются как диапазоны символов
    string s1 = "cat"s;
    string s2 = "cafeteria"s;

    bool s1_precedes_s2  = lexicographical_compare(
        s1.begin(), s1.end(),
        s2.begin(), s2.end()
    );
    // Ожидается, что s1_precedes_s2 == false
    cout<<s1_precedes_s2<<endl;
} 