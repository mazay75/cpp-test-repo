
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int MAX_RESULT_DOCUMENT_COUNT = 5;



 struct Document{
    int id = 0;
    int relevance = 0;
    };

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
bool HasDocumentGreaterRelevance(const Document& lhs, const Document& rhs) {
    return lhs.relevance > rhs.relevance;
}



class SearchServer {
    public:
    void AddDocument(int document_id, const string& document) {// Метод AddDocument передаёт текст документа в функцию SplitIntoWordsNoStop
        //добавляет документ в поисковый индекс
          const vector<string> words = SplitIntoWordsNoStop(document, stop_words_);
    documents_.push_back({document_id, words});
    }
    
    void SetStopWords(const string& text1) {// делает набор стоп-слов из текстовой строки
    set<string> stop_words;
    for (const string& word : SplitIntoWords(text1)) {
        stop_words.insert(word);
    }
   // return stop_words;
}



// Возвращает самые релевантные документы в виде вектора пар {id, релевантность} (по началу так было)
//documents-хранит идентификаторы и содержимое документов,
//stop_words-множество стоп-слов,
//raw_query-сам запрос
vector<Document> FindTopDocuments(const string& raw_query) {
    const set<string> query_words = ParseQuery(raw_query, stop_words_);
    auto matched_documents1= FindAllDocuments(query_words);

    sort(matched_documents1.begin(), matched_documents1.end(), HasDocumentGreaterRelevance);
    if (matched_documents1.size() > MAX_RESULT_DOCUMENT_COUNT) {
        matched_documents1.resize(MAX_RESULT_DOCUMENT_COUNT);
    }
    return matched_documents1;
}
    
 private:
    struct DocumentContent{
    int id = 0;
    vector<string> words;
    };
    
    vector<DocumentContent> documents_;
    set<string> stop_words_;
    
    vector<string> SplitIntoWordsNoStop(const string& text, const set<string>& stop_words) {//разбивает текст на слова, исключая из них слова из стоп-списка,
    // и возвращает то, что осталось. Разобранный на слова документ добавляется в вектор documents_
    vector<string> words;
    for (const string& word : SplitIntoWords(text)) {
        if (stop_words.count(word) == 0) {
            words.push_back(word);
        }
    }
    return words;
}

set<string> ParseQuery(const string& text, const set<string>& stop_words) {
    set<string> query_words;
    for (const string& word : SplitIntoWordsNoStop(text, stop_words)) {
        query_words.insert(word);
    }
    return query_words;
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

vector<Document> FindAllDocuments(const set<string>& query_words) { // Для каждого документа возвращает его релевантность и id
                                  
    vector<Document> matched_documents;
    for (const auto& document : documents_) {
        const int relevance = MatchDocument(document, query_words);
        if (relevance > 0) {
            matched_documents.push_back({document.id, relevance});
        }
    }
    return matched_documents;
    }
};
  // считывает из cin стоп-слова и документ и возвращает настроенный экземпляр поисковой системы
SearchServer CreateSearchServer() {
    SearchServer search_server;
     const string stop_words_joined = ReadLine();
    search_server.SetStopWords(stop_words_joined);
    
    // Read documents
    //vector<DocumentContent> documents;
    const int document_count = ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id) {
        search_server.AddDocument( document_id, ReadLine());
       
    }
return search_server;
};


    


\
int main() {
    // Создаём поисковую систему
    SearchServer search_server = CreateSearchServer();
     const string query = ReadLine();
     
    for (auto [document_id, relevance] : search_server.FindTopDocuments( query)) {
        cout << "{ document_id = "s << document_id << ", relevance = "s << relevance << " }"s
             << endl;
    }
    return 0;
}


