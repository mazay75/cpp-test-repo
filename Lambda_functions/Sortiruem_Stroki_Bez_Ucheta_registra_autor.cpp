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

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    
    int n = 0;
    
    string val;
    
    vector<string> v;
    
    cin >> n;
    
    v.reserve(n);
    
    for (int i = 0; i < n; ++i) {
        
        cin >> val;
        
        v.push_back(val);
    }
    
    sort(begin(v), end(v), [](const string& l, const string& r) {
            return lexicographical_compare(
                begin(l), end(l),
                begin(r), end(r),
                
                [](char cl, char cr) { return tolower(cl) < tolower(cr); }
            );
        }
    );
    
    for (int i = 0; i < static_cast<int> (v.size()); ++i) {
        
        cout << v[i] << ' ';
    }
    
    cout << endl;
}