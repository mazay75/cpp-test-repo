/*Спринт 4/19: 2 спринт → Тема 3/7: Пары и кортежи → Урок 4/8


Задание 1
Перепишите компаратор из предыдущего урока, применив кортежи.
Код должен вывести следующее:

104 0 0.3 5
102 0 1.2 4
100 0 0.5 4
101 1 0.5 4
103 2 1.2 4 

Документы нужно упорядочить сначала по возрастанию статусов, а при их равенстве — по убыванию рейтинга, 
затем по убыванию релевантности. Но при сравнении кортежей все компоненты сравниваются одинаково.
 Поэтому при создании кортежа удобно умножить рейтинг и релевантность на −1.
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

enum class Status { ACTUAL, EXPIRED, DELETED };

struct Document {
    int id;
    Status status;
    double relevance;
    int rating;
};

void SortDocuments(vector<Document>& matched_documents) {
    sort(matched_documents.begin(), matched_documents.end(),
         [](const Document& lhs, const Document& rhs) {
            return tuple(lhs.status, lhs.rating * (-1),lhs.relevance * (-1))
                    < tuple(rhs.status, rhs.rating * (-1), rhs.relevance * (-1)); 
         });
}

int main() {
    vector<Document> documents = {
        {100, Status::ACTUAL, 0.5, 4}, {101, Status::EXPIRED, 0.5, 4},
        {102, Status::ACTUAL, 1.2, 4}, {103, Status::DELETED, 1.2, 4},
        {104, Status::ACTUAL, 0.3, 5},
    };
    SortDocuments(documents);
    for (const Document& document : documents) {
        cout << document.id << ' ' << static_cast<int>(document.status) << ' ' << document.relevance
             << ' ' << document.rating << endl;
    }

    return 0;
}