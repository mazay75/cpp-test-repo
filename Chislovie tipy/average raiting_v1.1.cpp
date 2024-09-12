/*Спринт 4/19: 2 спринт → Тема 2/7: Числовые типы → Урок 2/10
Средний рейтинг

Задание 1
Вы написали код поисковой системы. Теперь каждый документ на входе имеет набор оценок пользователей. Первая цифра — это количество оценок.
 Считайте их, передайте в AddDocument в виде вектора целых чисел и вычислите средний рейтинг документа, разделив суммарный рейтинг на количество
  оценок. Рейтинг документа, не имеющего оценок, равен нулю. Рейтинг может быть отрицательным.
Средний рейтинг — это целое число. Его нужно выводить в ответе для каждого документа.
Добавьте поле rating типа int в структуру Document.
При выполнении задачи, обратите внимание на порядок вычислений. Рассмотрим конструкцию:
Foo(Bar(), Baz()); 
Она может вести себя по-разному: вначале может вызваться функция Baz, а может Bar. Если порядок вызова Bar и Baz важен, предварительно
 сохраните их результат в переменную,
auto bar_result = Bar();
auto baz_result = Baz();
Foo(bar_result, baz_result); 
В этой задаче такое возможно при вызове функции AddDocument. Поэтому избегайте такой конструкции.
Код вычисления среднего рейтинга поместите в функцию ComputeAverageRating. Сигнатура этой функции представлена ниже. Используйте эту функцию,
 чтобы вычислить средний рейтинг документа в методе AddDocument.
int ComputeAverageRating(const vector<int>& ratings) {
    ...
} 
Ограничения
Программа не должна вызывать несколько функций внутри вызова AddDocument.
Пример ввода
и в на
3
белый кот и модный ошейник
2 8 -3
пушистый кот пушистый хвост
4 7 2 7 1
ухоженный пёс выразительные глаза
3 5 -12 2
пушистый ухоженный кот 
Пример вывода
{ document_id = 1, relevance = 0.650672, rating = 4 }
{ document_id = 2, relevance = 0.274653, rating = -1 }
{ document_id = 0, relevance = 0.101366, rating = 2 } 
На первой строке программе подаются стоп-слова, далее – количество документов. Каждый документ состоит из двух строк: текст документа, 
его рейтинг. Первая цифра сообщает сколько оценок есть у документа и не используется в самом рейтинге.
Например, у документа с id 0 есть 2 оценки: 8 и -3. Среднее вычисляется путём сложения всех чисел и последующим делением их на
 количество суммированных чисел: (8 + -3) / 2 = 2.5. Целочисленный тип отбросил дробную часть и поэтому ответ 2.

1. Добавьте в SearchServer поле document_ratings_ типа map<int, int>. Ключом в этом словаре будет id документа, а значением — его рейтинг.
2. Добавьте в метод AddDocument ещё один параметр — вектор оценок. При добавлении документа вычислите средний рейтинг и положите его 
в словарь document_ratings_.
3. В методе Find достаньте рейтинг найденного документа и запишите его в поле rating структуры Document.
4. Среди значений рейтинга могут быть отрицательные числа. При делении отрицательного числа на ratings.size() в коде возможны проблемы,
 поэтому перед вычислением рейтинга положите размер вектора в переменную типа int.
5. Чтобы избежать сюрпризов, не вызывайте функции чтения текста документа и рейтинга внутри вызова другой функции: создайте отдельные 
переменные для прочитанного текста документа и рейтинга, затем передайте переменные в AddDocument. Это связано с порядком вычисления 
выражений в C++.
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
#include <cmath>

using namespace std;

const int MAX_RESULT_DOCUMENT_COUNT = 5;

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result;
    cin >> result;
    ReadLine();
    return result;
}

 vector<int> SplitIntoRatings( string& textRatings) {
    vector<int> raitings;
    string rating
    ;
    getline(cin, textRatings);
    for (const auto& c : textRatings) {
        if (c == ' ') {
            if (!rating
            .empty()) {
                raitings.push_back(stoi (rating
                ));
                rating
                .clear();
            }
        } else {
            rating
             += c;
        }
    }
    if (!rating
    .empty()) {
       raitings.push_back(stoi (rating
       ));
    }
      raitings.erase(raitings.begin());   
    return raitings;
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

struct Document {
    int id;
    double relevance;
    int rating;
};

class SearchServer {

public:
    void SetStopWords(const string& text) {
        for (const string& word : SplitIntoWords(text)) {
            stop_words_.insert(word);
        }
    }

    void AddDocument(int document_id, const string& document, const vector<int>& raitings) {
        ++document_count_;
        const vector<string> words = SplitIntoWordsNoStop(document);
        const double inv_word_count = 1.0 / words.size();
        for (const string& word : words) {
            word_to_document_freqs_[word][document_id] += inv_word_count;
            document_ratings_[document_id] = ComputeAverageRating(raitings);
        }
    }

    vector<Document> FindTopDocuments(const string& raw_query) const {
        const Query query = ParseQuery(raw_query);
        auto matched_documents = FindAllDocuments(query);

        sort(matched_documents.begin(), matched_documents.end(),
             [](const Document& lhs, const Document& rhs) {
                 return lhs.relevance > rhs.relevance;
             });
        if (matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
            matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
        }
        return matched_documents;
    }

    int ComputeAverageRating(const vector<int>& ratings) {
        int rezAverage = accumulate(ratings.begin(), ratings.end(), 0)/ratings.size();
        return rezAverage;
    }

private:
    int document_count_ = 0;
    set<string> stop_words_;
    map<string, map<int, double>> word_to_document_freqs_;
    map<int, int> document_ratings_;

    bool IsStopWord(const string& word) const {
        return stop_words_.count(word) > 0;
    }

    vector<string> SplitIntoWordsNoStop(const string& text) const {
        vector<string> words;
        for (const string& word : SplitIntoWords(text)) {
            if (!IsStopWord(word)) {
                words.push_back(word);
            }
        }
        return words;
    }

    struct QueryWord {
        string data;
        bool is_minus;
        bool is_stop;
    };

    QueryWord ParseQueryWord(string text) const {
        bool is_minus = false;
        // Word shouldn't be empty
        if (text[0] == '-') {
            is_minus = true;
            text = text.substr(1);
        }
        return {text, is_minus, IsStopWord(text)};
    }

    struct Query {
        set<string> plus_words;
        set<string> minus_words;
    };

    Query ParseQuery(const string& text) const {
        Query query;
        for (const string& word : SplitIntoWords(text)) {
            const QueryWord query_word = ParseQueryWord(word);
            if (!query_word.is_stop) {
                if (query_word.is_minus) {
                    query.minus_words.insert(query_word.data);
                } else {
                    query.plus_words.insert(query_word.data);
                }
            }
        }
        return query;
    }

    // Existence required
    double ComputeWordInverseDocumentFreq(const string& word) const {
        return log(document_count_ * 1.0 / word_to_document_freqs_.at(word).size());
    }

    vector<Document> FindAllDocuments(const Query& query) const {
        map<int, double> document_to_relevance;
        map<int, int> document_ratings_;
        for (const string& word : query.plus_words) {
            if (word_to_document_freqs_.count(word) == 0) {
                continue;
            }
            const double inverse_document_freq = ComputeWordInverseDocumentFreq(word);
            for (const auto &[document_id, term_freq] : word_to_document_freqs_.at(word)) {
                document_to_relevance[document_id] += term_freq * inverse_document_freq;
            }
        }

        for (const string& word : query.minus_words) {
            if (word_to_document_freqs_.count(word) == 0) {
                continue;
            }
            for (const auto &[document_id, _] : word_to_document_freqs_.at(word)) {
                document_to_relevance.erase(document_id);
            }
        }

        vector<Document> matched_documents;
        for (const auto &[document_id, relevance] : document_to_relevance) {
            matched_documents.push_back({document_id, relevance, document_ratings_[document_id]});
        }
        return matched_documents;
    }
};

    


SearchServer CreateSearchServer() {
    SearchServer search_server;
    search_server.SetStopWords(ReadLine());

    const int document_count = ReadLineWithNumber();
    string textRaiting;
    const vector<int> raitings=SplitIntoRatings(textRaiting);
    for (int document_id = 0; document_id < document_count; ++document_id) {
        search_server.AddDocument(document_id, ReadLine(),raitings);
    }

    return search_server;
}

int main() {
    const SearchServer search_server = CreateSearchServer();

    const string query = ReadLine();
    for (auto [document_id, relevance, rating] : search_server.FindTopDocuments(query)) {
        cout << "{ document_id = "s << document_id << ", "s
             << "relevance = "s << relevance << ", "s
             <<"rating="s<<rating<<" }"s << endl;
    }
}