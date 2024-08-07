//Сортируем строки без учёта регистра
//Спринт 2/22: Спринт 1 → Тема 3/9: Лямбда-функции → Урок 3/12

/*Задание
В стандартном потоке дана одна строка, которая состоит из числа N и следующего за ним набора S из N слов. Число отделено от слов пробелом.
Отсортируйте набор слов S в алфавитном порядке по возрастанию, игнорируя регистр букв. Выведите их в стандартный поток вывода через пробел. 
При сравнении слов цифры должны предшествовать буквам: слово «R2D2» находится после слова «R259», так как цифра 5 предшествует любой из букв.
После последнего слова также выведите пробел, а затем перевод строки.
Ознакомьтесь с функцией tolower и алгоритмом lexicographical_compare, чтобы отсортировать слова в алфавитном порядке без учета регистра символов.
Как будет тестироваться ваш код
Гарантируется, что входные данные программы удовлетворяют следующим условиям:
0 <= N <= 1000;
1 <= |S[i]| <= 15;
каждое слово S[i] содержит только цифры, заглавные и строчные буквы английского алфавита;
в наборе слов S нет слов, которые отличаются только регистром символов, например: «apple» и «Apple».
Пример
Ввод
8 quantity AMOUNT Selection Search 4ever music Mickey market 
Вывод 
4ever AMOUNT market Mickey music quantity Search Selection */

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

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

/*int ReadLineWithNumber() {
    int result = 0;
    cin >> result;
    ReadLine();
    return result;
}*/


vector<string> SplitIntoWords(const string& text) {//раскидывает текстовую строку на слова  и делает вектор слов
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    
    return words;
}

string ToLowerCase(string s) {
    for (char& ch : s) {
        ch = tolower(static_cast<unsigned char>(ch));
    }
    return s;
}

int main() {
    
         const string query = ReadLine();
         vector <string> query_vector=SplitIntoWords(query);
         string S=query_vector[0];
         int N=stoi(S);
        query_vector.erase(query_vector.begin());
        query_vector.resize(N);

          sort(query_vector.begin(), query_vector.end(), [](const string left, const string right) {
            return ToLowerCase(left)<ToLowerCase(right);
          });
    for (const string& entry : query_vector) {
        cout << entry << ' ';
    }
cout<<endl;
     return 0;
}