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

  vector<int> SplitIntoRatings( string& textRatings) {
    vector<int> raitings;
    string raiting;
    getline(cin, textRatings);
    for (const auto& c : textRatings) {
        if (c == ' ') {
            if (!raiting.empty()) {
                raitings.push_back(stoi (raiting));
                raiting.clear();
            }
        } else {
            raiting += c;
        }
    }
    if (!raiting.empty()) {
       raitings.push_back(stoi (raiting));
    }
      raitings.erase(raitings.begin());   
    return raitings;
}

   
   

int main(){
    
   string text1;
   getline(cin, text1);
   vector<int> words1 = SplitIntoWords(text1);
   for (auto raiting: words1) {
      cout<<raiting<<endl;
   }  

   int rez = accumulate(words1.begin(), words1.end(), 0)/words1.size();
   cout << rez<<endl;
}



 
