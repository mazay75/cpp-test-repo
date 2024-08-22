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
for (auto& word: words){
   // int i=0;
    vector <string> temp;
    auto it=find(words.begin(),words.end(), word);
    if (it==words.end()) {cout<<"не совпало"<<endl;}
    else cout<<words.at(it)<<endl;
    //if (it==word) {
     //   ++i;
       // cout<<"совпало"<<i<<endl;
      
    }
   // else cout <<"не совпало"<<endl;
}
//}


int main() {
    vector <string> words1 ={"dog"s,"cat"s,"dog"s,"vfg"s,"cat"s,"uyh"s,"jkl"s,"fghk"s,"tuikkhg"s};
   Podschet (words1);
} 