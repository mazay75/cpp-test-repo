#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstddef>

using namespace std;


int ComputeAbs(int num) {
    if (num < 0) {
        num *= (-1);
    } 
    return num;
}

float ComputeAbs(float num) {
    if (num < 0) {
        num *= (-1.0f);
    } 
    return num;
}

double ComputeAbs(double num) {
    if (num < 0) {
        num *= (-1.0);
    } 
    return num;
}

vector<int> ComputeAbs(vector<int> input_data) {
    vector<int> input_data1;
    for (int x : input_data) {
        if (x < 0) {
            input_data1.push_back(x *= (-1));
        }
            else { 
                input_data1.push_back(x);
            }
        }
        return input_data1; 
    }


int main() {

cout << "|100| = "s << ComputeAbs(100) << endl;
cout << "|0| = "s << ComputeAbs(0) << endl;
cout << "|-50| = "s << ComputeAbs(-50) << endl;

cout << "|3.141592f| = "s << ComputeAbs(3.141592f) << endl;
cout << "|0.f| = "s << ComputeAbs(0.f) << endl;
cout << "|-3.141592f| = "s << ComputeAbs(-3.141592f) << endl;

cout << "|3.141592| = "s << ComputeAbs(3.141592) << endl;
cout << "|0| = "s << ComputeAbs(0) << endl;
cout << "|-3.141592| = "s << ComputeAbs(-3.141592) << endl;

// Тестируем версию vector
int idx = 0;
vector input_data = {10, 20, -30, -50, 100};
for (int x : ComputeAbs(input_data)) {
    // Операция ++ увеличивает значение целочисленной переменной на 1.
    // Результатом операции ++ становится значение до увеличения.
    cout << "|"s << input_data[idx++] << "| = "s << x << endl;
}


    return 0;
}

