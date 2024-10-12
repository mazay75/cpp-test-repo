/*Спринт 4/19: 2 спринт → Тема 2/7: Числовые типы → Урок 9/10
Задание
Научитесь работать с перечислимым типом, объявленным внутри класса. Для этого перенесите объявление
 DocumentStatus в публичную секцию класса SearchServer, 
а в функции main выведите численное значение статуса BANNED.

Используйте двойное двоеточие дважды: SearchServer::DocumentStatus::BANNED. Не забудьте о static_cast.
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



class SearchServer {
private:
    // перенесите сюда DocumentStatus

     enum class DocumentStatus {
    ACTUAL = 1,
    IRRELEVANT = 2,
    BANNED = 3,
    REMOVED = 4,
  };
};

int main() {
    // выведите численное значение статуса BANNED
    //SearchServer::DocumentStatus document_status;

int document_code;
cin >> document_code;
auto request_document = static_cast <SearchServer::DocumentStatus> (document_code);

cout<< document_code<<endl;
if (request_document == SearchServer::DocumentStatus::BANNED) {
  cout<<"zabanneno"s<<endl;
}
else cout << "drugoye"s<<endl;

    return 0;
}