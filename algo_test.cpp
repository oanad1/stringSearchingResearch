#include "algo.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>
using namespace std::chrono;
using namespace std;

void printSingleOccurrences(vector<int> occurrences, string pattern, ostream &outfile);

void printMultipleOccurrences(map <int, vector<int>> occurrencesMap, vector<string> pattern_array, ostream &outfile);

void printSPResult(vector<string> pattern_array, string text, bool check, ostream &outfile);

void printRotResult(vector<string> pattern_array, string text, bool check, ostream &outfile);

int main(int argc, char *argv[]) {

    string input_path = "./in/";
    string output_path = "./out/";
    string output_file = output_path.append(argv[1]).append(".out");

    ifstream infile(input_path.append(argv[1]).append(".in"));

    vector<string> pattern_array;          //Array of input substrings
    string text;                           //Text to search in
    char test_type = argv[argc-1][0];      //Type of problem tested
    string temp_string;

    //Load substrings into a pattern array
    while(getline(infile, temp_string)){
        if(temp_string.empty())
            break;
        pattern_array.push_back(temp_string);
    }

    //Load the text by appending each file line to a string
    getline(infile, text);
    while(getline(infile, temp_string)){

        while (temp_string.length()==0 ) {
            getline(infile, temp_string);
        }

        text.append(" ");
        text.append(temp_string);
    }
    infile.close();
    ofstream outfile(output_file);

     switch(test_type){
         case 't':
             if(pattern_array.size() == 1) {

                 vector<int> occurrences;

                 //Test single-pattern matching on KMP
                 occurrences = singlePatternSearch(pattern_array[0], text, "KMP");
                   outfile << "KMP results\n";
                   printSingleOccurrences(occurrences,pattern_array[0], outfile);

                 //Test single-pattern matching on RK
                 occurrences = singlePatternSearch(pattern_array[0], text, "RK");
                   outfile << "RK results\n";
                   printSingleOccurrences(occurrences,pattern_array[0], outfile);
                   occurrences.clear();
                 outfile.close();
                 break; }

              else {

                 map<int,vector<int>> occurrencesMap;

                 //Test multiple-pattern matching on A-C
                 occurrencesMap = multiplePatternSearch(pattern_array,text,"AC");
                 outfile << "AC results\n";
                 printMultipleOccurrences(occurrencesMap, pattern_array, outfile);

                 //Test multiple-pattern matching on RK
                 occurrencesMap = multiplePatternSearch(pattern_array,text,"RK");
                 outfile << "RK results\n";
                 printMultipleOccurrences(occurrencesMap, pattern_array, outfile);

                 //Test multiple-pattern matching on KMP
                 auto start = high_resolution_clock::now();
                 occurrencesMap = multiplePatternSearch(pattern_array,text,"KMP");
                 auto stop = high_resolution_clock::now();
                 auto duration = duration_cast<nanoseconds>(stop - start);
                 cout << duration.count() << endl;
                 outfile << "KMP results\n";
                 printMultipleOccurrences(occurrencesMap, pattern_array, outfile);
                 break;
             }

         case 's': {
             //Test problem 1, KMP vs RK: Check if a string is a prefix and suffix for another
             outfile << "KMP result\n";
             printSPResult(pattern_array, text, checkSuffixPrefix(text, pattern_array[0], "KMP"), outfile);

             outfile << "RK result\n";
             printSPResult(pattern_array, text, checkSuffixPrefix(text, pattern_array[0], "RK"), outfile);
         }
             break;

        case 'r': {
            //Test problem 2, KMP vs RK: Check if a string is a rotation of another string
            outfile << "KMP result\n";
            printRotResult(pattern_array, text, checkIfRotation(text, pattern_array[0], "KMP"), outfile);

            outfile << "RK result\n";
            printRotResult(pattern_array, text, checkIfRotation(text, pattern_array[0], "RK"), outfile);
        }
             break;
    }
}

//Functions used for outputting results in the output file

void printSingleOccurrences(vector<int> occurrences, string pattern, ostream &outfile){

    if(!occurrences.empty()){
        outfile << "Pattern '" << pattern << "' appears at: ";
        for (int pos: occurrences) {
            outfile << pos << " ";
        }
        outfile << "\n\n";
    } else {
        outfile << "No occurrence\n";
    }
}

void printMultipleOccurrences(map <int, vector<int>> occurrencesMap, vector<string> pattern_array, ostream &outfile){

    map <int, vector<int>>::iterator it;
    for ( it = occurrencesMap.begin(); it != occurrencesMap.end(); it++ ) {
        outfile << "Pattern '" << pattern_array[it->first] << "' appears at: ";

        for(int occ: occurrencesMap.at(it->first)){
            outfile << occ << " ";
        }
        outfile << "\n";
    }
    outfile << "\n";
}

void printSPResult(vector<string> pattern_array, string text, bool check, ostream &outfile) {

    if (check) {
        outfile << "The string '" << pattern_array[0] << "' is a suffix and a prefix for '" << text << "'\n";
    } else {
        outfile << "The string '" << pattern_array[0] << "' is NOT a suffix and a prefix for '" << text << "'\n";
    }
}

void printRotResult(vector<string> pattern_array, string text, bool check, ostream &outfile) {

    if (check) {
        outfile << "The string '" << pattern_array[0] << "' is a rotation for '" << text << "'\n";
    } else {
        outfile << "The string '" << pattern_array[0] << "' is NOT a rotation for '" << text << "'\n";
    }
}