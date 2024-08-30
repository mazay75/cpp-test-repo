//Спринт 3/19: 1 спринт → Тема 3/5: Лямбда-функции → Урок 10/12


#include <algorithm>// Содержит функцию lexicographical_compare
#include <cctype> // содержит функцию tolower
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

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

//раскидывает текстовую строку на слова  и делает вектор слов
vector<string> SplitIntoWords(const string& text) {
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
    double relevance; 
};

class SearchServer {

public:

// делает набор стоп-слов из текстовой строки
    void SetStopWords(const string& text) {
        for (const string& word : SplitIntoWords(text)) {
            stop_words_.insert(word);
        }
    }

// Метод AddDocument передаёт текст документа в функцию SplitIntoWordsNoStop
//добавляет документ в поисковый индекс
    void AddDocument( int document_id, const string& document) {
        const vector<string> words = SplitIntoWordsNoStop(document);
        double one_TF= 1.0/static_cast <double> (words.size());
        for (const string& word: words){
             word_to_document_freqs_[word][document_id] += one_TF;
        }   
        ++document_count_;
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

    int document_count_ = 0;
    map<string, map<int, double>> word_to_document_freqs_; 
    set<string> stop_words_;

    bool IsStopWord(const string& word) const {
        return stop_words_.count(word) > 0;
    }

//разбивает текст на слова, исключая из них слова из стоп-списка,
// и возвращает то, что осталось. Разобранный на слова документ добавляется в вектор documents_
    vector<string> SplitIntoWordsNoStop(const string& text) const {
    
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

// разбивает текст на слова с учётом стоп-слов. стоп-слова не учитываются
    Query ParseQuery(const string& text) const {
        Query query_words;
        for (const string& word : SplitIntoWordsNoStop(text)) {
            if (word[0] == '-') {
                string stripped = word.substr(1); //если слово с минусом, то минус убираем и записываем в strtipped
                if (!IsStopWord(stripped)) { 
                    query_words.words_minus.insert(stripped);
                }
                    else {
                        query_words.words_plus.insert(word); // а если это плюс-слово, то в words_plus
                    }
            }
        return query_words;//слова запроса без стоп-слов, но уже с минус словами
    }


double ComputeIdf(const string& word_plus) const {
    return  log(static_cast <double> (document_count_)/static_cast <double> (word_to_document_freqs_.at(word_plus).size()));

}
     vector<Document> FindAllDocuments(const Query& query_words) const {// Для каждого документа возвращает его релевантность и id
        vector<Document> matched_documents;
         map <int, double> document_to_relevance; //В ней ключ — id найденного документа, а значение — релевантность соответствующего 
                                             //документа. Она равна количеству плюс-слов, найденных в нём
                                                             
        for ( const string& word_plus: query_words.words_plus){
            if (word_to_document_freqs_.count(word_plus)) { 
                for (const auto&[document_id, TF]: word_to_document_freqs_.at(word_plus)){
                document_to_relevance[document_id]+=TF*ComputeIdf(word_plus);
                }
   
            }
        }
        for (const string& word: query_words.words_minus){
            if (word_to_document_freqs_.count(word)) {
                for (const auto&[document_id, TF]: word_to_document_freqs_.at(word)){
                   if (document_to_relevance.count(document_id)) {
                     document_to_relevance.erase(document_id);
                   }
                   
                    
                }
             }
        }
         for (const auto& [document_id, relevance] : document_to_relevance) {
          
                matched_documents.push_back({document_id, relevance});
               
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

