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

using namespace std;

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
    double relevance;
};

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


void AddDocument( int document_id, const string& document) {// Метод AddDocument передаёт текст документа в функцию SplitIntoWordsNoStop
        //добавляет документ в поисковый индекс
        const vector<string> words = SplitIntoWordsNoStop(document);
        double one_TF= 1.0/static_cast <double> (words.size());
        for (const string& word: words){
             word_to_document_freqs_[word][document_id] += one_TF;
        }   
        for (int i=0; i<static_cast <int> (word_to_document_freqs_.size()); ++i){
            if (document_count_ <=document_id) {++i; document_count_=i;}
        }
    }

    int document_count_ = 0;


int main() {
    
    

    const string query = ReadLine();
    for (const auto& [document_id, relevance] : FindTopDocuments(query)) {
        cout << "{ document_id = "s << document_id << ", "
             << "relevance = "s << relevance << " }"s << endl;
    }
    return 0;
}



 
