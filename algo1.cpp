// Implementation of the Knuth–Morris–Pratt algorithm

#include <iostream>
#include <vector>
#include <map>
using namespace std;

void createPrefixArray(string pattern, int pat_length, int* prefix_array);


vector<int> KMP(string pattern, string text)
{
    vector<int> occurrences;                //Stores all occurrences(first index) of the pattern in the text
    unsigned int pat_length = pattern.length();      //Length of the pattern
    int prefix_array[pat_length];           //Indicates the longest prefix in pattern which is a suffix

    createPrefixArray(pattern, pat_length, prefix_array);

    unsigned int i = 0,           // Index for text
                 j = 0;           // Index for pattern

    while (i < text.length()) {
        //While there is a match, advance in both strings
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        //Found the pattern in the text, place its starting position in the occurrences array
        //Go back to the point after the longest prefix-suffix
        if (j == pat_length) {
            occurrences.push_back(i - j);
            j = prefix_array[j - 1];
        }

            //Mismatch occurs
        else if (i < text.length() && pattern[j] != text[i]) {

            // j is the number of matches up to this point
            if (j != 0)

                // Characters 0..prefix_array[j-1] previously had a match in the text
                // Start comparing again from prefix_array[j-1]
                j = prefix_array[j - 1];

            else
                //No previous matches, simply advance in the text
                i = i + 1;
        }
    }
    return occurrences;
}


void createPrefixArray(string pattern, int pat_length, int* prefix_array)
{
    int match_point = 0;   //The size of the prefix match found at some point in the pattern

    //First character match is set to 0
    prefix_array[0] = 0;

    //Iterate through pattern starting from index 1
    for(int i=1; i < pat_length; i++){

        //While the character in the prefix is matching the current character, store its index
        if (pattern[i] == pattern[match_point]) {

            match_point++;
            prefix_array[i] = match_point;

        } else {

            //In case of mismatch go back and test the last matching point
            if (match_point != 0) {
                match_point = prefix_array[match_point - 1];
                //Do not advance in the array
                i--;
            }
            else
            {
                //When 0 is reached, matching starts over from the first character
                prefix_array[i] = 0;
            }
        }
    }
}
