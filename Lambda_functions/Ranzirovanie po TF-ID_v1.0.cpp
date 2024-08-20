/*Спринт 3/19: 1 спринт → Тема 3/5: Лямбда-функции → Урок 10/12
Задание
Это задание — итоговый проект спринта. Сдавать проект на проверку вы будете через репозиторий на GitHub. Не забудьте сохранить верное решение.
Переведите вычисление релевантности на формулу TF-IDF. От англ. term frequency, «частота термина», inverse document frequency,
 «обратная частота документа» — мера важности слова в документе из коллекции документов. Выступает критерием релевантности 
 документа поисковому запросу.
Будьте внимательны с повторами: теперь они важны и кратно увеличивают релевантность по соответствующему слову. Повторение 
слова в документе увеличивает TF.
Чтобы вычислить IDF, в поисковой системе должно храниться количество документов. Для этого заведите в классе поле document_count_ типа int 
и по умолчанию проинициализируйте нулём при объявлении: int document_count_ = 0.
Измените у поля relevance структуры Document тип с int на double. Теперь релевантность — вещественное число, вычисляемое по формуле TF-IDF.
 В остальном использование поисковой системы не должно поменяться.
Если слово встречается во всех документах, то его наличие не должно добавлять релевантности документу. IDF такого слова будет равно нулю.
 Теоретически могут найтись документы с нулевой релевантностью, если каждое слово в них обладает этим свойством. Эти документы всё равно
  нужно включить в выдачу, поскольку в них есть плюс-слова запроса. Отрицательный IDF получится не может, поскольку документов с определённым 
  словом не может быть больше, чем всего документов в базе.
Как будет тестироваться ваша программа
Методика проверки не меняется по сравнению с предыдущей задачей. Будет дополнительно проверено, что релевантность теперь имеет тип double.

Пример входных и выходных данных
Ввод
Входные данные передаются в таком же формате, как и в предыдущих задачах.
is are was a an in the with near at
3
a colorful parrot with green wings and red tail is lost
a grey hound with black ears is found at the railway station
a white cat with long furry tail is found near the red square
white cat long tail 
Вывод
В выходных данных по сравнению с предыдущими задачами меняется тип релевантности.
{ document_id = 2, relevance = 0.462663 }
{ document_id = 0, relevance = 0.0506831 } 
Требования
При выводе чисел double не меняйте формат их отображения.
Поиск не должен стать существенно медленнее. При поиске документов нужно использовать реверсивный индекс, а не перебирать их все.
TF слов в документе должен вычиляться при добавлении документа. Решение будет недостаточно эффективным, если вы будете вычислять
 его каждый раз при поиске.
Создание сервера и добавление документов также должно быть эффективным.
Не меняйте ввод данных и запросов. По сравнению с предыдущей задачей он не изменился.

Теперь недостаточно для каждого слова хранить список документов, в которых оно встречается. Вместе с каждым документом нужно 
хранить TF соответствующего слова в этом документе. Эту проблему можно решить, если заменить словарь «слово → документы» на 
более сложную структуру map<string, map<int, double>> word_to_document_freqs_, которая сопоставляет каждому слову словарь
 «документ → TF».
При добавлении документа нужно вычислить TF каждого входящего слова. Это нужно делать в методе AddDocument. Можно пройтись
 циклом по всему документу, увеличивая TF каждого встречаемого слова на величину 1 / N, где N — общее количество слов в документе.
  Если слово встретилось K раз, то вы столько же раз прибавите к его TF величину 1 / N и получите K / N. Использование ещё одного
   цикла или алгоритма count окажется намного медленнее, чем этот способ.
TF вычисляется при добавлении документа, IDF — при поиске по запросу. Подумайте, как с имеющимися данными быстро вычислять IDF.
При делении чисел убедитесь, что они представлены типом double, иначе произойдёт округление. Используйте литерал с точкой. 
Например, 1. / 2 == 0.5, а 1 / 2 == 0.
Если понадобится преобразовать целое число к double, то можно использовать static_cast.
Как и раньше, для поиска документов и вычисления их релевантности хватит двойной вложенности циклов for: внешний — по словам запроса,
 внутренний — по документам, где это слово встречается.
Будьте внимательны при работе со словарями. Не забывайте, что с константным словарём нельзя использовать операцию [], а при
использовании метода at обязательно проверять наличие ключей. Всё сказанное относится как к самому словарю 
word_to_document_freqs_, так и к каждому словарю, хранящемуся в нём.
Для вычисления IDF достаточно иметь плюс-слово, чтобы найти количество документов, в которых это слово есть. 
Считайте IDF во внешнем цикле, чтобы не высчитывать его снова и снова.
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
