/*Спринт 4/22: 2 спринт → Тема 4/7: Шаблоны функций  → Урок 2/8


Задание
Реализуйте простую функцию, которая вычисляет частоту строк из данного вектора. В этом примере частота — это число вхождений уникальных строк в векторе.

Посчитайте, сколько раз встречается каждый элемент вектора. Для этого проитерируйтесь по ним и прибавьте
 единицу к соответствующему значению в словаре, применив оператор ++.
*/

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

uusing namespace std;

map<string, int> ComputeTermFreqs(const vector<string>& terms) { 
    // реализуйте функцию
}

int main() {
    const vector<string> terms = {"first"s, "time"s, "first"s, "class"s};
    for (const auto& [term, freq] : ComputeTermFreqs(terms)) {
        cout << term << " x "s << freq << endl;
    }
    // вывод:
    // class x 1
    // first x 2
    // time x 1
}
