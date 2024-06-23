/*По закону Неверландии кандидаты в парламент сообщают только своё имя и возраст. В избирательном бюллетене предпочтение отдаётся возрасту: старшие кандидаты идут первыми. Кандидаты одного возраста сортируются в бюллетене по алфавиту, но опять же в обратном порядке.
В стандартном вводе будет информация о кандидатах в нужном объёме — их имена и возрасты. Ваша задача напечатать в cout избирательный бюллетень, который содержит только имена кандидатов в нужном порядке.*/

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>


using namespace std;

int main() {
    int count;
     vector <pair<int, string>> kand1;
    cin >> count;
    for (int i = 0; i < count; ++i) {
        string name;
        int age;
        cin >> name >> age;
        // сохраните в вектор пар
       
        kand1.push_back({age, name});  
    }

  sort(kand1.begin(), kand1.end());
  reverse(kand1.begin(), kand1.end());  
    for(const auto& empty:kand1){
        cout<<empty.second<<endl;
    }
    return 0;
    
}

