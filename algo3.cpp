//Implementation of the Aho-Corasick algorithm

using namespace std;
#include <bits/stdc++.h>
#include <map>

struct Node {
    map<char, int> *children = new map<char,int>;    //Character values + node indexes of children for the current node
    bool leaf = false;                               //If the node is a leaf, there is a word ending in this node
    int parent = -1;                                 //Parent node index
    char char_value;                                 //Char corresponding to the node
    int pattern_index = -1;                          //The index of the corresponding pattern, if leaf
    int end_word = -1;                               //The index of the vertex containing the maximum length word made from this prefix
    int suffix = -1;                                 //The link to a matching suffix
};

struct TrieStruct{
    Node* trie;                      //A trie constructed from all pattern characters
    int *patternsLength;             //Length of each pattern
    int size = 0;                    //Size of current trie
    int root = 0;                    //Index for root
};

//Adds a pattern to the trie
void addString(string pattern, int pattern_idx, TrieStruct* trieStruct){

    //Start from the trie root
    int current_node = trieStruct->root;
    int size = trieStruct->size;

    //Traverse the pattern char by char
    for(unsigned int i=0; i < pattern.length(); i++){

        char c = pattern[i];

        //If the trie is empty, or if a node with this edge does not exist in the trie, add the node
        if(trieStruct->trie[current_node].children == NULL || !trieStruct->trie[current_node].children->count(c)){

            //Set the current node as its parent
            trieStruct->trie[size].suffix = -1;
            trieStruct->trie[size].parent = current_node;
            trieStruct->trie[size].char_value = c;
            trieStruct->trie[current_node].children->insert(pair<char, int>(c, size));
            trieStruct->size ++;
            size ++;
        }
        //Advance to another node in the trie
        current_node = trieStruct->trie[current_node].children->at(c);
    }

    //The last node is a leaf and marks the end of the pattern
    trieStruct->trie[current_node].leaf = true;
    trieStruct->trie[current_node].pattern_index = pattern_idx;

    //Add the pattern's length in the trie structure
    trieStruct->patternsLength[pattern_idx] = pattern.length();
}

//Determines the maximum-length suffix for the current node which is a prefix for another subpattern
void calculateSuffix(int node, TrieStruct *trieStruct){

    //Neither root or root children can have a suffix
    //Case 1: Node is root
    if(node == trieStruct->root){
        trieStruct->trie[node].suffix = trieStruct->root; //0 -empty string
        trieStruct->trie[node].end_word = trieStruct->root; //0
        return;
    }

    //Case 2: Node is child of root
    if(trieStruct->trie[node].parent == trieStruct->root){

        trieStruct->trie[node].suffix = trieStruct->root; //also 0

        //If the node is a leaf, mark that the pattern ends here
        if(trieStruct->trie[node].leaf)
            trieStruct->trie[node].end_word = node;
        else
            trieStruct->trie[node].end_word =
                    trieStruct->trie[trieStruct->trie[node].suffix].end_word;
        return;
    }

    //Get the suffix link from our node's parent
    int new_node = trieStruct->trie[trieStruct->trie[node].parent].suffix;

    //Save the current character value
    char new_ch = trieStruct->trie[node].char_value;

    while (true){
        //If the parent's suffix node has a child same as our node, than the child node becomes our node's suffix
        if(trieStruct->trie[new_node].children->count(new_ch)){
            trieStruct->trie[node].suffix =
                    trieStruct->trie[new_node].children->at(new_ch);
            break;
        }
        //If the parent's suffix node is root, our node also goes to root
        if(new_node == trieStruct->root){
            trieStruct->trie[node].suffix = trieStruct->root;
            break;
        }
        new_node = trieStruct->trie[new_node].suffix;
    }

    //If the node is a leaf, mark that the pattern ends here
    if(trieStruct->trie[node].leaf)
        trieStruct->trie[node].end_word = node;
    else
        trieStruct->trie[node].end_word =
                trieStruct->trie[trieStruct->trie[node].suffix].end_word;
}

//Processes nodes using breadth-first traversal of the trie
void processTrie(TrieStruct* trieStruct){
    queue<int> node_queue;
    node_queue.push(trieStruct->root);
    while (node_queue.size() > 0){
        int current_node = node_queue.front();
        node_queue.pop();
        calculateSuffix(current_node, trieStruct);

        for( auto const& x: *trieStruct->trie[current_node].children) {
            node_queue.push(trieStruct->trie[current_node].children-> at(x.first));
        }
    }
}

map<int,vector<int>> getPatternOccurences(string text, TrieStruct* trieStruct){

    //Return the result as a map of type [initial_pattern_index]: [<array_of_its_occurrences>]
    map<int,vector<int>> occurrences;

    //Begin from the root
    int current_state = trieStruct->root;

    for(unsigned int j=0; j< text.length(); j++){
        while (true){

            //If there is an edge in the current state to character j in the text, use the edge
            if(trieStruct->trie[current_state].children->count(text[j])){
                current_state = trieStruct->trie[current_state].children->at(text[j]);
                break;
            }

            //If there isn't a direct edge, follow suffix links until finding an edge with this char or reaching root
            //When we reach root, we stop checking
            if(current_state == trieStruct->root)
                break;
            current_state = trieStruct->trie[current_state].suffix;
        }

        //Now we have a prefix and need to find all possible patterns which use it
        int other_state = current_state;

        while (true){
            //Check every state that can be reached from the current prefix
            other_state = trieStruct->trie[other_state].end_word;

            //Stop if getting to root
            if(other_state == trieStruct->root)
                break;

            //If above does not cause break, it means that we found another state representing a match
            int match_index = j + 1 - trieStruct->patternsLength[trieStruct->trie[other_state].pattern_index];

            //Put the results in the occurences map
            int idx = trieStruct->trie[other_state].pattern_index;
            if(occurrences.count(idx)){
                vector<int> v = occurrences.at(idx);
                v.push_back(match_index);
                occurrences.at(idx) = v;
            }
            else{
                vector<int> v;
                v.push_back(match_index);
                occurrences.insert(pair<int, vector<int>>(idx, v));
            }

            //Find other matched patterns of smaller length
            other_state = trieStruct->trie[other_state].suffix;
        }
    }
    return occurrences;
}

map<int, vector<int>>  AhoCorasick(vector<string> pattern_array, string text){

    //Calculate the total number of characters in the pattern_array
    int total_chars = 1;
    for(string s: pattern_array){
        total_chars += s.length();
    }

    //Initialize a trie stucture
    TrieStruct* trieStruct = new TrieStruct;

    //The size of the array used to implement the trie is equal to the total number of characters from all patterns
    trieStruct->trie = new Node[total_chars];

    //Initialize an array used to store the lengths of each pattern
    trieStruct->patternsLength = new int[pattern_array.size()];

    //The first node is a root with no actual data, so we skip it
    trieStruct->size++;

    //Add all patterns in the trie
    for(unsigned int i = 0; i < pattern_array.size(); i++){
        addString(pattern_array[i],i,trieStruct);
    }

    //Process the trie and establish links for suffixes and subpattern matches
    processTrie(trieStruct);

    //Process the text based on the trie structure and return a map of occurrences for each pattern
    map<int, vector<int>> occurrences = getPatternOccurences(text, trieStruct);
    return occurrences;
}
