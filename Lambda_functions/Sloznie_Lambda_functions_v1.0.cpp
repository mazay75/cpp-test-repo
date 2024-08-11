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

vector<int> ReadNumbers() {
    int count;
    cin >> count;

    vector<int> numbers;
    for (int i = 0; i < count; ++i) {
        int number;
        cin >> number;
        numbers.push_back(number);
    }

    return numbers;
}

void PrintNumbers(const vector<int>& numbers) {
    for (auto number : numbers) {
        cout << number << " "s;
    }
}

int main() {
    vector<int> numbers = ReadNumbers();

        /*
           Напишите тело лямбда-функции самостоятельно.
           Сначала должны располагаться чётные числа в порядке возрастания,
           а следом за ними — нечётные числа в порядке убывания
        */
     sort(numbers.begin(), numbers.end(), [](int n1, int n2) -> bool {
        if (n1%2==0 && n2%2==0){
            return n1<n2;
        } 
            else if (n1%2==0 && n2%2!=0) {
                return true;
            }

            else if (n1%2!=0 && n2%2!=0) {
            return n1>n2;
        }
        else {return false;}
        
       
    });

    PrintNumbers(numbers);
    return 0;
}