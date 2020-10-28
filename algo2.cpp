// Implementation of the Rabin-Karp algorithm

#include <iostream>
#include <vector>
#include <cstring>
#include <map>
using namespace std;
#define base  256                 //Size of the ASCII alphabet

vector<int> RabinKarp(string pattern, string text) {
    vector<int> occurrences;      //Stores all occurrences(first index) of the pattern in the text
    int mod;                      //Modulus for the hashing function
    int pattern_hash = 0;         //Hash value for pattern
    int text_hash = 0;            //Hash value for text


    //Chose a modulus in the range 0-100
    mod = 277;

    //The modulus has to be relatively prime to the base, which is 256 = 2^5
    if(mod % 2 == 0)
        mod++;

    //Compute the length of the strings
    int pattern_length = pattern.length();
    int text_length = text.length();

    //Determine the initial hash value for the pattern,
    // as well as for the first pattern_length chars in the text
    for (int i = 0; i < pattern_length; i++) {
        pattern_hash = (base * pattern_hash + pattern[i]) % mod;
        text_hash = (base * text_hash + text[i]) % mod;
    }

    //Base expression used to recalculate hash
    int exp = 1;
    for(int k=1; k < pattern_length; k++) {
        exp = (exp * base) % mod;
    }

    // The pattern moves in a "window" through the text
    for (int i = 0; i <= text_length - pattern_length; i++) {

        // If there is a match in the hash values, check its validity
        //by doing a naive comparison of characters
        if ( pattern_hash == text_hash ){
            int j = 0;
            while(j < pattern_length && text[i+j] == pattern[j]) {
                j++;
            }
            //If pattern_length characters matched, we found a valid match
            //The first matching index from thr text is saved in occurrences
            if (j == pattern_length){
                occurrences.push_back(i);
            }
        }

        //Advance one character in the text and recompute the text_hash value
        //We do not recalculate the entire hash, but only perform basic addition and subtraction
        //for the first window character and the last new window character
        if ( i < text_length - pattern_length)
        {
            //Formula: base * (old_hash - first_char * base^(pattern_length - 1) + next_char) % modulus

            text_hash = (base * (text_hash - text[i] * exp) + text[i + pattern_length]) % mod;

            //A negative modulus  result is converted to positive by adding mod
            if (text_hash < 0) {
                text_hash += mod;
            }
        }
    }
    return occurrences;
}
