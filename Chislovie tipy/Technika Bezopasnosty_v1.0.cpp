/*Спринт 4/19: 2 спринт → Тема 2/7: Числовые типы → Урок 6/10
Техника безопасности
Задание
Напишите функцию PrintDocuments, принимающую вектор документов и два числа: skip_start и skip_finish. 
Пусть функция сортирует документы по убыванию рейтинга и выводит документы в таком порядке, пропустив
 skip_start документов с наибольшим рейтингом и skip_finish с наименьшим. Считайте, что рейтинги не повторяются.
Числа на входе функции могут быть сколь угодно большими: ваша программа должна обрабатывать их корректно
 и не падать. Если требуется пропустить все документы или даже больше, не выводите ничего. Вектор документов
  может быть пустым, skip_start и skip_finish не обязательно меньше размера вектора. 
  Формат вывода документов — в примере:
Пример
PrintDocuments(
    {
        {100, 5},
        {101, 7},
        {102, -4},
        {103, 9},
        {104, 1}
    },
    1,
    2
); 
Вывод
{ id = 101, rating = 7 }
{ id = 100, rating = 5 } 

Объявите индекс в цикле типа size_t и не вычитайте из documents.size(). Cтоит проверить, что не происходит переполнения, 
когда числа на входе PrintDocuments оказываются предельно большими.
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

using namespace std;

struct Document {
    int id;
    int rating;
};

void PrintDocuments(vector<Document> documents, size_t skip_start, size_t skip_finish) {
    // отсортировать документы и вывести не все
     sort(documents.begin(), documents.end(),
        [](const Document& lhs, const Document& rhs) { 
            return lhs.rating > rhs.rating;
        });
        for (const auto& [id, rating]: documents) {
            cout<<id<<"-"<<rating<<endl;  
        }
            cout<<"\n";

     if (static_cast <uint64_t> (skip_start) > static_cast <uint64_t> (documents.size()) ||
        static_cast <uint64_t> (skip_finish) > static_cast <uint64_t> (documents.size())) {
            skip_start = documents.size();
            skip_finish = documents.size();
        } 

    for (uint64_t i=0; i < static_cast<uint64_t> (skip_start); ++i ) {
            documents.erase(documents.begin() + i);
    }
    for (const auto& [id, rating]: documents) {
            cout<<id<<"-"<<rating<<endl;
    }
         cout<<"\n";

    for (uint64_t i=0; i < static_cast<uint64_t> (skip_finish); ++i ) {
            documents.erase(documents.end() - i);
    }
    for (const auto& [id, rating]: documents) {
            cout<<id<<"-"<<rating<<endl;
     }
        cout<<"\n";
        
    
}

int main() {
    PrintDocuments({{100, 5}, {101, 7}, {102, -4}, {103, 9}, {104, 1}}, 1, 10);
}
