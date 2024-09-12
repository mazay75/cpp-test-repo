#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

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

vector<string> SplitIntoWords(const string& text) {//функция разбиения текста на слова
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

set<string> ParseStopWords(const string& text) { //функция для построения множества из стоп-слов
    set<string> stop_words;
    for (const string& word : SplitIntoWords(text)) {
        stop_words.insert(word);
    }
    return stop_words;
}

vector<string> SplitIntoWordsNoStop(const string& text, const set<string>& stop_words) {//функция для построения вектора слов без стоп-
                                                                                         //слов
    vector<string> words;
    for (const string& word : SplitIntoWords(text)) {
        if (stop_words.count(word) == 0) {
            words.push_back(word);
        }
    }
    return words;
}

void AddDocument(vector<pair<int, vector<string>>>& documents, const set<string>& stop_words, 
                 int document_id, const string& document) {                                    //функция,чтобы положить отсортированный документ
    const vector<string> words = SplitIntoWordsNoStop(document, stop_words);                   //в БД (документ будет разбит на слова; стоп-слова
    documents.push_back(pair<int, vector<string>>{document_id, words});                        //будут исключены из рассмотрения,
}                                                                                              // оставшиеся слова будут добавлены в базу данных,
                                                                                               //которую функция AddDocument принимает по ссылке



set<string> ParseQuery(const string& text, const set<string>& stop_words) {                     // Разбирает text на слова и возвращает только те из них,
    set<string> query_words;                                                                     //которые не входят в stop_words
    for (const string& word : SplitIntoWordsNoStop(text, stop_words)) {
        query_words.insert(word);
    }
    return query_words;
}

int MatchDocument(const pair<int, vector<string>>& content, const set<string>& query_words) {//будет возвращать релевантность документа
    if (query_words.empty()) {
        return 0;
    }
    set<string> matched_words;
    for (const string& word : content.second) {
        if (matched_words.count(word) != 0) {
            continue;
        }
        if (query_words.count(word) != 0) {
            matched_words.insert(word);
        }
    }

    // Преобразовываем беззнаковое число типа size_t в int используя
    // static_cast<int>
    return static_cast<int>(matched_words.size());
}

// Для каждого документа возвращает его id и релевантность
vector<pair<int, int>> FindAllDocuments(const vector<pair<int, vector<string>>>& documents,     // Для каждого документа возвращает его id и релевантность
                                     const set<string>& query_words) {
  
    vector<pair<int, int>> matched_documents;
    for (const auto& document : documents) {
        const int relevance = MatchDocument(document, query_words);
        if (relevance > 0) {
            matched_documents.push_back({document.first, relevance});
        }
    }
    return matched_documents;
}




// Возвращает топ-5 самых релевантных документов в виде пар: {id, релевантность}
vector<pair<int, int>> FindTopDocuments(const vector<pair<int, vector<string>>>& documents,
                                        const set<string>& stop_words, const string& raw_query) {
    // Напишите функцию, используя FindAllDocuments
  const set<string> query_words = ParseQuery(raw_query, stop_words);

  vector<pair<int, int>> result = FindAllDocuments(documents, query_words);
vector<pair<int,int>> result1;
    
   for (const auto& entry: result){
      result1.push_back({entry.second, entry.first});
   }
 sort(result1.begin(), result1.end());
  reverse(result1.begin(), result1.end()); 
   result1.resize(MAX_RESULT_DOCUMENT_COUNT);
    vector<pair<int,int>> result2;
    for (const auto& [id,relev]:result1){
        if (relev!=0) {result2.push_back({id, relev});}
    }
       return result2; 
        }
    


int main() {
    const string stop_words_joined = ReadLine();
    const set<string> stop_words = ParseStopWords(stop_words_joined);

    // Чтение документов
    vector<pair<int, vector<string>>> documents;
    const int document_count = ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id) {
        AddDocument(documents, stop_words, document_id, ReadLine());
    }

    const string query = ReadLine();
    // Вместо FindDocuments используйте FindTopDocuments
    for (auto [document_id,relevance] : FindTopDocuments(documents, stop_words, query)) {
        cout << "{ document_id = "s << document_id << ", relevance = "s << relevance << " }"s
             << endl;
    }
}
