#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using namespace std;
bool IsA_a(const string& word){
   if (word=="") {return false;}
    else if (word[0]=='A' || word[0]=='a') {return true;}
    else return false;
    }


int CountStartsWithA(const vector<string>& xs) {
    //string word1;
    return count_if(xs.begin(), xs.end(), IsA_a);
}

int main() {
   
    cout << CountStartsWithA({"And"s, "another"s, "one"s, "gone"s, "another"s,
                              "one"s
                              "bites"s,
                              "the"s, "dust"s});

}

//будут считаться слова, которые начинаются на "А" или "а"