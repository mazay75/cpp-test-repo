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

struct AnimalObservation {
        string name;
        int days_ago;
        int health_level;
}; 

int main() {
 const tuple animal_info("Василий"s, 5, 4.1);

string name;
int age;
double weight;

tie(name, age, weight) = animal_info;
cout << "Пациент "s << name
    << ", "s << age << " лет"s
    << ", "s << weight << " кг"s << endl;
// Пациент Василий, 5 лет, 4.1 кг
    return 0;
}