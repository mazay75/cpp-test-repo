

/*Спринт 3/19: 1 спринт → Тема 3/5: Лямбда-функции → Урок 9/12

Задание
Внедрите в класс SearchServer поиск по инвертированному индексу документов из теории. Для этого внесите в класс следующие изменения:
Удалите структуру DocumentContent — она вам больше не понадобится.
Замените контейнер vector<DocumentContent> на контейнер map<string, set<int>>. Ключи этого контейнера — слова из добавленных документов,
 а значения — id документов, в которых это слово встречается.
В методе AddDocument переберите слова документа, кроме стоп-слов. В множество документов, соответствующих очередному слову, 
вставьте id текущего документа.
В методе FindAllDocuments сначала вычислите релевантность документов, в которые входят плюс-слова запроса. Для этого 
используйте map<int, int>, где ключ — id документа, а значение — количество плюс-слов, которые в этом документе встречаются. 
Затем исключите из получившегося map те документы, в которых встретилось хотя бы одно минус-слово. Оставшиеся элементы map скопируйте
 в результирующий vector<Document>.
Возвращённый вектор документов будет отсортирован по убыванию релевантности в методе FindTopDocuments. Эта часть у вас уже реализована.
Метод MatchDocument больше не будет использоваться в FindAllDocuments. Поскольку он приватный и других использований его внутри класса нет,
 этот метод можно смело удалить.
Обратите внимание, что теперь поисковый сервер не будет хранить содержимое документов. Если бы понадобилось получить список слов 
определённого документа, то это было бы не так просто. Однако, это и не нужно.
Это задача на улучшение проекта, а не на применение лямбда-функций. Используйте лямбда-функции при необходимости, но в задаче они 
необязательны. Функциональность программы в этом задании изменяться не должна. 
Формат ввода и вывода
В первой строке ввода содержатся стоп-слова, разделённые пробелами. Вторая строка ввода содержит целое число N, задающее количество документов. 
В каждой из последующих N строк — текст документа, в котором слова разделяются одним пробелом. Последняя строка ввода содержит 
текст поискового запроса, в котором слова разделяются одним пробелом.
Программа должна вывести id и релевантность пяти самых релевантных документов, отсортированных от наиболее релевантного к наименее
 релевантному, как это показано ниже.
Пример ввода:
is are was a an in the with near at
3
a colorful parrot with green wings and red tail is lost
a grey hound with black ears is found at the railway station
a white cat with long furry tail is found near the red square
white cat long tail 
Пример вывода:
{ document_id = 2, relevance = 4 }
{ document_id = 0, relevance = 1 } 
Как будет тестироваться ваш код
Тренажёр передаст вашей программе входные данные через стандартный поток ввода и сравнит результат её работы с ожидаемым.
Чтобы измерить эффективность поиска, тренажёр заменит вашу функцию main на нашу. В ней будет создан экземпляр класса SearchServer,
 в который добавятся десятки тысяч документов. Документы содержат от 10 до 100 слов.
При добавлении будет измеряться время поиска по базе документов. У вас в коде есть инвертированный индекс, поэтому поиск среди десятков 
тысяч документов займёт не намного больше времени, чем поиск среди сотен.

1. Вместо vector<DocumentContent> documents_ объявите поле map<string, set<int>> word_to_documents_. В нём будет храниться инвертированный
 индекс документов. Структуру DocumentContent удалите.
2. В методе AddDocument переберите в цикле все слова документа, кроме стоп-слов. При этом нужно модицифировать word_to_documents_: для каждого 
слова добавлять id документа в словарь, соответствующий этому слову.
3. Метод MatchDocument вам больше не нужен, его можно удалить. FindAllDocuments будет работать по другому принципу.
4. В методе FindAllDocuments объявите переменную document_to_relevance типа map<int, int>. В ней ключ — id найденного документа, а
 значение — релевантность соответствующего документа. Она равна количеству плюс-слов, найденных в нём.
5. В методе FindAllDocuments переберите в цикле все плюс-слова поискового запроса. Если в word_to_documents_ есть плюс-слово, увеличьте 
в document_to_relevance релевантности всех документов, где это слово найдено. Так вы соберёте все документы, которые содержат плюс-слова запроса.
6. Исключите из результатов поиска все документы, в которых есть минус-слова. В методе FindAllDocuments переберите в цикле все минус-слова 
поискового запроса. Если в word_to_documents_ есть минус-слово, удалите из document_to_relevance все документы с этим минус-словом. Так в 
document_to_relevance останутся только подходящие документы.
7. Перенесите id и релевантности документов из document_to_relevance в vector<Document> и верните результирующий вектор. Для переноса можно
 использовать цикл, в котором будут конструироваться документы по id и релевантности.
8. Будьте внимательны и в нужных местах проверяйте наличия ключа в словаре перед обращением к нему.
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

using namespace std;

const int MAX_RESULT_DOCUMENT_COUNT = 5;

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result = 0;
    cin >> result;
    ReadLine();
    return result;
}

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

struct Document {
    int id;
    int relevance;
};



class SearchServer {
public:
    void SetStopWords(const string& text) {// делает набор стоп-слов из текстовой строки
        for (const string& word : SplitIntoWords(text)) {
            stop_words_.insert(word);
        }
    }

    void AddDocument( int document_id, const string& document) {// Метод AddDocument передаёт текст документа в функцию SplitIntoWordsNoStop
        //добавляет документ в поисковый индекс
    
        const vector<string> words = SplitIntoWordsNoStop(document);
    
        for (const string& word: words){

            word_to_documents_[word].insert(document_id);

        }
        

        
    }

    // Возвращает самые релевантные документы в виде вектора пар {id, релевантность} (по началу так было)
//documents-хранит идентификаторы и содержимое документов,
//stop_words-множество стоп-слов,
//raw_query-сам запрос
    vector<Document> FindTopDocuments(const string& raw_query) const {
        const Query query_words = ParseQuery(raw_query);
        auto matched_documents = FindAllDocuments(query_words);

        sort(matched_documents.begin(), matched_documents.end(),
             [](const Document& lhs, const Document& rhs) {
                 return lhs.relevance > rhs.relevance;
             });
        if (matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
            matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
        }
        return matched_documents;
    }

private:
    
    map<string, set<int>> word_to_documents_; //Ключи этого контейнера — слова из добавленных документов,а значения — id документов, в которых это слово встречается

    set<string> stop_words_;

    bool IsStopWord(const string& word) const {
        return stop_words_.count(word) > 0;
    }

    vector<string> SplitIntoWordsNoStop(const string& text) const {//разбивает текст на слова, исключая из них слова из стоп-списка,
    // и возвращает то, что осталось. Разобранный на слова документ добавляется в вектор documents_
        vector<string> words;
        for (const string& word : SplitIntoWords(text)) {
            if (!IsStopWord(word)) {
                words.push_back(word);
            }
        }
        return words;
    }

    struct Query {
    set<string> words_plus;
    set<string> words_minus;

};

    Query ParseQuery(const string& text) const {// разбивает текст на слова с учётом стоп-слов. стоп-слова не учитываются
        Query query_words;
        for (const string& word : SplitIntoWordsNoStop(text)) {
            if (word[0] == '-') {string stripped = word.substr(1); //если слово с минусом, то минус убираем и записываем в strtipped
                                    if (!IsStopWord(stripped)) { query_words.words_minus.insert(stripped);}//если это слово 
                                    //не является стоп-словом, то определяем его в множество words_minus структуры query_words
                                }
            else {query_words.words_plus.insert(word);}// а если это плюс-слово, то в words_plus
        }
        return query_words;//слова запроса без стоп-слов, но уже с минус словами
    }
/*В методе FindAllDocuments переберите в цикле все плюс-слова поискового запроса. Если в word_to_documents_ есть плюс-слово, увеличьте 
в document_to_relevance релевантности всех документов, где это слово найдено. Так вы соберёте все документы, которые содержат плюс-слова запроса.*/
/*6. Исключите из результатов поиска все документы, в которых есть минус-слова. В методе FindAllDocuments переберите в цикле все минус-слова 
поискового запроса. Если в word_to_documents_ есть минус-слово, удалите из document_to_relevance все документы с этим минус-словом. Так в 
document_to_relevance останутся только подходящие документы.*/


    vector<Document> FindAllDocuments(const Query& query_words) const {// Для каждого документа возвращает его релевантность и id
        vector<Document> matched_documents;
         map <int, int> document_to_relevance; //В ней ключ — id найденного документа, а значение — релевантность соответствующего 
                                             //документа. Она равна количеству плюс-слов, найденных в нём
        for (const string& word: query_words.words_plus){
            if (word_to_documents_.count(word)) { 
                for (int document_id: word_to_documents_.at(word)){
                     ++document_to_relevance[document_id];
                }  
                
            }
        }
        for (const string& word: query_words.words_minus){
            if (word_to_documents_.count(word)) {
                for (int document_id: word_to_documents_.at(word)){
                    document_to_relevance.erase(document_id);
                }
             }
        }
         for (const auto& [document_id, relevance] : document_to_relevance) {
            if (relevance> 0) {
                matched_documents.push_back({document_id, relevance});
               }
             }
        return matched_documents;
        
    
    }
};
    

SearchServer CreateSearchServer() {// считывает из cin стоп-слова и документ и возвращает настроенный экземпляр поисковой системы
    SearchServer search_server;
    search_server.SetStopWords(ReadLine());

    const int document_count = ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id) {
        search_server.AddDocument( document_id, ReadLine());
    }

    return search_server;
}

int main() {
    const SearchServer search_server = CreateSearchServer();

    const string query = ReadLine();
    for (const auto& [document_id, relevance] : search_server.FindTopDocuments(query)) {
        cout << "{ document_id = "s << document_id << ", "
             << "relevance = "s << relevance << " }"s << endl;
    }
    return 0;
}
