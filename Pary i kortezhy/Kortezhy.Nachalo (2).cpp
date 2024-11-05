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

/*Задание 2
Копирование кода — это зло. В компараторе продублирована половина кода — создание кортежа по объекту.
 Когда такой код написан для lhs, велик соблазн его скопировать и исправить lhs на rhs. Но исправляя,
  можем что-то упустить в одном из параметров. Вынесите создание кортежа в отдельный метод MakeKey 
  структуры Document.
MakeKey должен возвращать кортеж, который можно сравнивать вместо исходных объектов — так, 
чтобы компаратор выглядел просто как return lhs.MakeKey() < rhs.MakeKey();

Явно указывать возвращаемый тип для нового метода не нужно. Укажите вместо него auto, 
а в теле метода верните tuple(...) — компилятор сам поймёт, о каком типе речь.
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
    auto  MakeKey () const {
         return tuple(status, rating * (-1), relevance * (-1));
        };
};

void SortDocuments(vector<Document>& matched_documents) {
    sort(matched_documents.begin(), matched_documents.end(),
         []( const Document& lhs, const Document& rhs) {
            return lhs.MakeKey() < rhs.MakeKey();
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