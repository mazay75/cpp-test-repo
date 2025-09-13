#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
// 555


using namespace std;

const int MAX_RESULT_DOCUMENT_COUNT = 5;

   struct DocumentContent {
    int id = 0;
    vector<string> words;
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

class SearchServer {
    public:
    void AddDocument(int document_id, const string& document) {// Метод AddDocument передаёт текст документа в функцию SplitIntoWordsNoStop
        //добавляет документ в поисковый индекс
          const vector<string> words = SplitIntoWordsNoStop(document, stop_words_);
    documents_.push_back({document_id, words});
    }
    
    /*set<string>*/ void SetStopWords(const string& text) {
    set<string> stop_words;
    for (const string& word : SplitIntoWords(text)) {
        stop_words.insert(word);
    }
   // return stop_words;
}
   
    private:
 
    vector<DocumentContent> documents_;
    set<string> stop_words_;
    
    vector<string> SplitIntoWordsNoStop(const string& text, const set<string>& stop_words) {//разбивает текст на слова, исключая из них слова из стоп-списка, и возвращает то, что осталось. Разобранный на слова документ добавляется в вектор documents_
    vector<string> words;
    for (const string& word : SplitIntoWords(text)) {
        if (stop_words.count(word) == 0) {
            words.push_back(word);
        }
    }
    return words;
}
    
};
  // считывает из cin стоп-слова и документ и возвращает настроенный экземпляр поисковой системы
SearchServer CreateSearchServer() {
    SearchServer result;
     const string stop_words_joined = ReadLine();
    result.SetStopWords(stop_words_joined);
    
    
   
    //const set<string> stop_words = ParseStopWords(stop_words_joined);

    // Read documents
    vector<DocumentContent> documents;
    const int document_count = ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id) {
        result.AddDocument( document_id, ReadLine());
       
    }
return result;
};


    



int main() {
    
  
    // Создаём поисковую систему
    SearchServer search_server;
    search_server.SetStopWords("a the in of an with"s);   
    // Добавляем в неё несколько документов
    search_server.AddDocument(1, "brown cat with grey hair"s);
    search_server.AddDocument(2, "green parrot with yellow feathers"s);
    
} 


/*int main() {
   
    const string query = ReadLine();
    for (auto [document_id, relevance] : FindTopDocuments(documents, stop_words, query)) {
        cout << "{ document_id = "s << document_id << ", relevance = "s << relevance << " }"s
             << endl;
    }
}*/