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




void Podschet(vector<string> words){
    map <string, int> temp;
for ( auto& word: words){
    ++temp[word];
}

 for (const auto& [word, freq] : temp) {
        cout << word << "\t" << freq << endl;    
    }
  
}



int main() {
    vector <string> words1 ={"DOG"s,"CAT"s,"DOG"s,"ELEFANT"s,"CAT"s,"LION"s,"JKL"s,"FGHK"s,"TUIKKHG"s};
   Podschet (words1);
} 



 
