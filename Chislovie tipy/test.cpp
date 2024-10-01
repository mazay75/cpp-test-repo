

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

enum class RequestType {
    ADD,
    REMOVE,
    NEGATE
};

void ProcessRequest(
        set<int>& numbers,
        RequestType request_type,
        int request_data) {
    if (request_type == RequestType::ADD) {
        numbers.insert(request_data);
    } else if (request_type == RequestType::REMOVE) {
        numbers.erase(request_data);
    } else if (request_type == RequestType::NEGATE) {
        if (numbers.count(request_data) == 1) {
            numbers.erase(request_data);
            numbers.insert(-request_data);
        }
    }
}


int main () {
    set<int> numbers={3,4,5, -8};
ProcessRequest(numbers, RequestType::ADD, 8);
for (const auto& entry: numbers) {
    cout<< entry<<" "s;
}
cout<< endl;
ProcessRequest(numbers, RequestType::NEGATE, 8);
for (const auto& entry: numbers) {
    cout<< entry<<" "s;
}
cout<< endl;
ProcessRequest(numbers, RequestType::REMOVE, -8); 
for (const auto& entry: numbers) {
    cout<< entry<<" "s;
}
cout<< endl;

}