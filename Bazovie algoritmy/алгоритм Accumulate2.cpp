///**Задание 2
Напишите функцию AddStopWords, которая принимает строку-запрос и множество стоп-слов и возвращает новую строку. Новая строка состоит из запроса, к которому приписаны стоп-слова. Стоп-слова разделяются пробелами, и перед каждым стоит дефис.
Для решения задачи не используйте циклы, их заменит алгоритм accumulate.

*************************************************************************************************************************************************************/////////
#include <iostream>
#include <set>
#include <string>
#include <numeric>

using namespace std;


string Conct(string query, string word1){
    string query1;
    query1=query+" -"+word1;
    return query1;
    
}

string AddStopWords(const string& query, const set<string>& stop_words) {

     string stop_words1;
     stop_words1=accumulate(stop_words.begin(), stop_words.end(), query, Conct);
    return stop_words1;
}

int main()
{
    string q = "здрасьте мордасьте waiting ";
    set<string> words = {"in", "with", "on", "if", "and"};
    cout << AddStopWords(q, words);
    return 0;
}