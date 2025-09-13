/*Спринт 4/19: 2 спринт → Тема 3/7: Пары и кортежи → Урок 3/8


Задание 2
Введём статусы документов: ACTUAL (актуальные), EXPIRED (просроченные) и DELETED (удалённые). Исправьте компаратор так, чтобы после сортировки
 порядок документов был следующим: 
актуальные,
просроченные,
удалённые.
Внутри каждого статуса документы должны быть упорядочены по убыванию рейтинга, а затем по убыванию релевантности.
Код из тренажёра должен вывести следующее:
104 0 0.3 5
102 0 1.2 4
100 0 0.5 4
101 1 0.5 4
103 2 1.2 4 

Подставить все три поля в пару, к сожалению, не выйдет. 
Но можно написать логическое выражение ещё большей вложенности. 
А можно скомбинировать два подхода: самостоятельно сравнить статусы и, 
если они равны, — сравнить пары двух оставшихся характеристик.
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
            if (lhs.status == rhs.status)
             return pair(lhs.rating, lhs.relevance) > pair(rhs.rating, rhs.relevance);
             else {
                return lhs.status < rhs.status;
             }
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