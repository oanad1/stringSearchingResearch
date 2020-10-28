using namespace std;
#include <bits/stdc++.h>
#include "algo.h"

//Problem: Search for occurrences a pattern inside a text
//Solution: Apply KMP/ Rabin-Karp
vector<int> singlePatternSearch(string pattern, string text, string alg){
    if(alg == "KMP"){
        return KMP(pattern, text);
    } else {
        return RabinKarp(pattern,text);
    }
}

//Problem: Search for occurrences of multiple patterns inside a text
//Solution: Apply Aho-Corasick/ apply KMP and RK repeatedly for each pattern
map<int,vector<int>> multiplePatternSearch(vector<string> pattern_array, string text, string alg){

    if(alg == "AC"){
        return AhoCorasick(pattern_array,text);
    }

    map<int, vector<int>> occurrencesMap;
    vector<int> occurrences;

    for(unsigned int i=0; i< pattern_array.size(); i++){

        if(alg == "KMP") {
            occurrences = KMP(pattern_array[i], text);
        } else {
            occurrences = RabinKarp(pattern_array[i], text);
        }

        if(!occurrences.empty()) {
            occurrencesMap.insert(pair<int, vector<int>>(i, occurrences));
        }
    }
    return occurrencesMap;
}

//Problem: Determine if a given substring is a suffix and a prefix for another string - RK vs KMP
//Solution: Search for occurences and compare to the first index and the last index that fits substr into str
bool checkSuffixPrefix(string str, string substr, string alg) {
    vector <int> occurrences;

    if(alg == "KMP") {
        occurrences = KMP(substr, str);
        return (unsigned int)occurrences[0]==0 && (unsigned int)occurrences[occurrences.size()-1]==str.length()-substr.length();
    } else {
        occurrences = RabinKarp(substr, str);
        return (unsigned int)occurrences[0]==0 && (unsigned int)occurrences[occurrences.size()-1]==str.length()-substr.length();
    }
}

//Problem: Determine if a string is a rotation of another string - RK vs KMP
//Solution: Concatenate the first string to itself and search for the second string inside the result
bool checkIfRotation(string str1, string str2, string alg){
    vector <int> occurrences;
    string concat = str1;
    concat.append(str1);

    if(alg == "KMP"){
        occurrences = KMP(str2, concat);
    } else {
        occurrences = RabinKarp(str2, concat);
    }

    return !occurrences.empty();
}
