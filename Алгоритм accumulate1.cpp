//Задание 1
//Вычислите среднее арифметическое вектора чисел. Считайте, что среднее арифметическое пустого массива равно нулю.


#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

double Average(const vector<int>& xs) {
  double rez ;
   rez= accumulate(xs.begin(), xs.end(), 0.0)/xs.size();    
    return rez;
}

int main() {
    cout << Average({1, 2, 2}) << endl;
    return 0;
}