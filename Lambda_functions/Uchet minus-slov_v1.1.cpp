/*Спринт 3/19: 1 спринт → Тема 3/5: Лямбда-функции → Урок 8/12
Задание
Научитесь обрабатывать запросы с минус-словами. Прежние условия сохраняются:
слова в документах и запросах разделены ровно одним пробелом;
перед первым словом и после последнего пробелов нет;
Единственное нововведение: запрос может содержать минус-слова — слова с минусом в начале. В документе минус-слов быть не может.
Пример входных и выходных данных
Ввод
и в на с
3
найден белый кот . на нём модный ошейник
пушистый кот ищет хозяина . особые приметы : пушистый хвост
в парке горького найден ухоженный пёс с выразительными глазами
пушистый ухоженный кот -ошейник 
Вывод
{ document_id = 1, relevance = 2 }
{ document_id = 2, relevance = 1 } 
Примечание
Документ 0 не подходит из-за слова «ошейник», запрещённого в запросе.
С документом 1 запрос пересекается по двум словам: «пушистый» и «кот», а с документом 2 — только по слову «ухоженный».

Минус-слова запроса должны обрабатываться до плюс-слов. Каждый документ, где есть минус-слово, не должен включаться в результаты поиска,
 даже если в нём присутствуют плюс-слова.
Для хранения запроса удобно создать структуру Query с двумя множествами слов: плюс- и минус-словами. Возвращать эту структуру по строке
 запроса нужно в новом приватном методе — ParseQuery.
После сравнения первого символа с '-' не забудьте отрезать этот минус вызовом .substr(1), а затем проверить результат по словарю стоп-слов.
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

struct Query {
    vector<string> word_plus;
    vector<string> word_minus;

};

class SearchServer {
public:
    void SetStopWords(const string& text) {// делает набор стоп-слов из текстовой строки
        for (const string& word : SplitIntoWords(text)) {
            stop_words_.insert(word);
        }
    }

    void AddDocument(int document_id, const string& document) {// Метод AddDocument передаёт текст документа в функцию SplitIntoWordsNoStop
        //добавляет документ в поисковый индекс
        const vector<string> words = SplitIntoWordsNoStop(document);
        documents_.push_back({document_id, words});
    }

    // Возвращает самые релевантные документы в виде вектора пар {id, релевантность} (по началу так было)
//documents-хранит идентификаторы и содержимое документов,
//stop_words-множество стоп-слов,
//raw_query-сам запрос
    vector<Document> FindTopDocuments(const string& raw_query) const {
        const set<string> query_words = ParseQuery(raw_query);
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
    struct DocumentContent {
        int id = 0;
        vector<string> words;
    };

    vector<DocumentContent> documents_;

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

    set<string> ParseQuery(const string& text) const {
        set<string> query_words;
        for (const string& word : SplitIntoWordsNoStop(text)) {
            query_words.insert(word);
        }
        return query_words;
    }

    vector<Document> FindAllDocuments(const set<string>& query_words) const {// Для каждого документа возвращает его релевантность и id
        vector<Document> matched_documents;
        for (const auto& document : documents_) {
            const int relevance = MatchDocument(document, query_words);
            if (relevance > 0) {
                matched_documents.push_back({document.id, relevance});
            }
        }
        return matched_documents;
    }

    static int MatchDocument(const DocumentContent& content, const set<string>& query_words) {//будет возвращать релевантность документа
        if (query_words.empty()) {
            return 0;
        }
        set<string> matched_words;
        for (const string& word : content.words) {
            if (matched_words.count(word) != 0) {
                continue;
            }
            if (query_words.count(word) != 0) {
                matched_words.insert(word);
            }
        }
        return static_cast<int>(matched_words.size());
    }
};

SearchServer CreateSearchServer() {// считывает из cin стоп-слова и документ и возвращает настроенный экземпляр поисковой системы
    SearchServer search_server;
    search_server.SetStopWords(ReadLine());

    const int document_count = ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id) {
        search_server.AddDocument(document_id, ReadLine());
    }

    return search_server;
}

int main() {
     // Создаём поисковую систему
    const SearchServer search_server = CreateSearchServer();

    const string query = ReadLine();
    for (const auto& [document_id, relevance] : search_server.FindTopDocuments(query)) {
        cout << "{ document_id = "s << document_id << ", "
             << "relevance = "s << relevance << " }"s << endl;
    }
}