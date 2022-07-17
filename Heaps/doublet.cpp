#include "MinHeap.h"
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    // priority = f * (h+1) + h  || f = h + g
    // heuristics = heuristics how many letters the key to the final word || length_word = length of the every word
    // position = (g) how many steps away from the start node
    bool visited, already_popped;
    int priority, position, length_word, heuristics;
    vector<string> next;
};

// Self Defined Function to Change all the String into UpperCase
void Upper_String(string& low) {
    for (long unsigned int i = 0; i < low.length(); i++) {
        low[i] = toupper(low[i]);
    }
}

// Make a Graph to connect distinct nodes
void Make_Graph(vector<string>& words, map<string, Node*>& match) {
    for (long unsigned int i = 0; i < words.size(); i++) {
        string temp = words[i];
        string itself = temp;
        // loop every character of temp
        for (int k = 0; k < temp.length(); k++) {
            // loop from A to Z
            char original = temp[k];
            for (char i = 'A'; i <= 'Z'; i++) {
                string test = temp;
                // Edge Case, didn't change the word
                if (i == original)
                    continue;
                test[k] = i;
                // There exists a word with only one letter away
                if (match.count(test) > 0) {
                    match[itself]->next.push_back(test);
                }
            }
        }
    }
}

void AStarSearch(string first_word, map<string, Node*>& match, string last_word) {

    MinHeap<string> str_tree(2);
    int expansions = 0;
    bool last_word_found = false;
    // initialize first node priority and add to the tree
    match[first_word]->priority
            = (match[first_word]->position + match[first_word]->heuristics) * (match[first_word]->length_word + 1)
              + match[first_word]->heuristics;
    str_tree.add(first_word, match[first_word]->priority);

    match[first_word]->visited = true;
    while (!str_tree.isEmpty()) {
        string current = str_tree.peek();
        match[current]->already_popped = true;
        // increment the number for expansions
        if (current != last_word)
            expansions++;

        // Last Case: when the peak string is the last_word
        if (current == last_word) {
            last_word_found = true;
            cout << match[current]->position << endl;
            cout << expansions << endl;
            break;
        }
        str_tree.remove();

        for (int i = 0; i < match[current]->next.size(); i++) {
            string sub_word = match[current]->next[i];
            // calculate the priority of the nearest neighbor
            int priority_neighbor = ((match[current]->position + 1) + match[sub_word]->heuristics)
                                            * (match[sub_word]->length_word + 1)
                                    + match[sub_word]->heuristics;
            if (match[sub_word]->already_popped == false) {
                // if the sub word is not popped
                if (match[sub_word]->visited == false || priority_neighbor < match[sub_word]->priority) {
                    // visit the subnodes that has not been visited
                    if (match[sub_word]->visited == false) {
                        match[sub_word]->visited = true;
                        match[sub_word]->position = match[current]->position + 1;
                        match[sub_word]->priority = priority_neighbor;
                        str_tree.add(sub_word, match[sub_word]->priority);
                    }
                    // visit the subnodes that has been visited but the priority/ or in another way of speaking, the g
                    // value is smaller
                    else {
                        // update positions and priority
                        match[sub_word]->position = match[current]->position + 1;
                        match[sub_word]->priority = priority_neighbor;
                        str_tree.add(sub_word, match[sub_word]->priority);
                    }
                }
            }
        }
    }

    // The heap is empty and last word is not found
    if (last_word_found == false) {
        cout << "No transformation" << endl;
        cout << expansions << endl;
    }
}

int main(int argc, char* argv[]) {
    // Edge Case: not enough arguments
    if (argc < 4) {
        return 0;
    }

    ifstream word_list(argv[3]);
    // Edge Case: not a valid file
    if (word_list.fail()) {
        return 0;
    }

    int words_count = 0;
    word_list >> words_count;

    // Store all the string into a vector and map string with node for future operations
    vector<string> all_words;
    map<string, Node*> match_word;
    string first = argv[1];
    Upper_String(first);
    string last = argv[2];
    Upper_String(last);
    int length_first = first.length();
    // only iterate to words count, avoid the issue of blank lines

    // The first line have a line after the first int, use string empty to clear out the line
    string empty;
    getline(word_list, empty);

    for (int i = 0; i < words_count; i++) {
        string line;
        getline(word_list, line);
        stringstream ss(line);
        // temp is the fist word on the line in case of any potential whitespaces
        string temp;
        ss >> temp;

        // Push up all UpperCase Words
        Upper_String(temp);

        // Edge Case: the length is not enough, then skip
        if (temp.length() != length_first) {
            continue;
        }

        all_words.push_back(temp);
        match_word[temp] = new Node;
        // Initialize values for Nodes
        if (temp == first)
            match_word[temp]->position = 0;
        match_word[temp]->visited = false;
        match_word[temp]->length_word = temp.length();
        match_word[temp]->already_popped = false;
    }

    // map iterator to set the heuristics of every node
    map<string, Node*>::iterator it;
    for (it = match_word.begin(); it != match_word.end(); it++) {
        string tem = it->first;
        int difference = 0;
        for (int i = 0; i < tem.length(); i++) {
            if (tem[i] != last[i]) {
                difference++;
            }
        }
        it->second->heuristics = difference;
    }

    Make_Graph(all_words, match_word);
    AStarSearch(first, match_word, last);

    for (it = match_word.begin(); it != match_word.end(); it++) {
        delete it->second;
    }

    word_list.close();
    return 0;
}