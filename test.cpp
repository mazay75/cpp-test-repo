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




void Podschet(const vector<string>& words){
for (const auto& word: words){
    int i;
    vector <string> temp;
    auto it=find(words.begin(),words.end(), word);
    if (it!=words.end()) {
        temp.push_back
    



    else cout <<"не совпало"<<endl;
}
}


int main() {
    vector <string> words1 ={"dog"s,"cat"s,"dog"s,"vfg"s,"cat"s,"uyh"s,"jkl"s,"fghk"s,"tuikkhg"s};
   Podschet (words1);
} 