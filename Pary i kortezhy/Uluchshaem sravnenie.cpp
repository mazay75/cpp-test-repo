/*Спринт 4/19: 2 спринт → Тема 3/7: Пары и кортежи → Урок 2/8
Задание
Вы сортировали найденные поисковой системой документы по убыванию релевантности. Не меняя данной функции, исправьте компаратор так, чтобы он 
сортировал по убыванию рейтинга. А при одинаковом рейтинге — по убыванию релевантности.
Код из тренажёра должен вывести следующее:
102 0.3 5
101 1.2 4
100 0.5 4 

Когда рейтинг первого параметра больше рейтинга второго — результат компаратора точно true.
 Иначе такой результат можно получить лишь при равном рейтинге и большей релевантности первого документа.
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
    double relevance;
    int rating;
};

void SortDocuments(vector<Document>& matched_documents) {
    sort(matched_documents.begin(), matched_documents.end(),
         [](const Document& lhs, const Document& rhs) {
             return lhs.rating > rhs.rating
                    || (lhs.rating == rhs.rating && lhs.relevance > rhs.relevance);
            
         });
    }

           
int main() {
    vector<Document> documents = {{100, 0.5, 4}, {101, 1.2, 4}, {102, 0.3, 5}};
    SortDocuments(documents);
    for (const Document& document : documents) {
        cout << document.id << ' ' << document.relevance << ' ' << document.rating << endl;
    }

    return 0;
}