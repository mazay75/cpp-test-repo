/*Чтобы не сортировать массив целиком, в реальной жизни процентили вычисляют алгоритмом nth_element. В этом задании найдите медианное значение времени ответа сервера. Для отсортированного массива это значение среднего элемента, либо полусумма двух средних элементов, если число элементов чётное:
CalcMedian({1, 2, 3, 4}) == 2.5;
CalcMedian({1, 2, 3}) == 2;
CalcMedian({1, 2, 1000}) == 2; // медиана устойчива к небольшому числу сильно отклоняющихся от нормы значений 
Напишите функцию CalcMedian, которая принимает на вход вектор времени ответа и возращает медиану этого вектора. Вектор может быть неотсортированным, а также пустым.
Формат входных и выходных данных
Программе на вход подаётся целое неотрицательное число N — размер массива. Затем подаются N чисел с плавающей запятой, разделённых пробелом — элементы массива. Программа должна вывести медианное значение элементов массива, либо строку Empty vector, если массив пустой.*/








#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

pair<bool, double> CalcMedian(vector<double> samples) {
    
    pair <bool, double> mediana;
    if (samples.empty()) {return mediana={false,0};}
    else sort(samples.begin(), samples.end());
    if (samples.size()%2 !=0) {return mediana={true, samples[samples.size()/2]};}
    else {double value1= (samples[samples.size()/2]+samples[(samples.size()/2)-1])/2;
          return mediana={true, value1};}
        return mediana;
}

int main() {
    int size;
    cin >> size;

    vector<double> samples;
    for (int i = 0; i < size; ++i) {
        double sample;
        cin >> sample;
        samples.push_back(sample);
    }

    pair<bool, double> result = CalcMedian(samples);
    if (result.first) {
        cout << result.second << endl;
    } else {
        cout << "Empty vector"s << endl;
    }
}