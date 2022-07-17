# HW3_MinHeap and A* Search Jeffrey Liu

In this program, I mainly construct three files: MinHeap.h and doublet.cpp, Makefile

For MinHeap.h, I make a d-ary MinHeap - meaning each node with d children
This file contain a template class 

For doublet.cpp, I achieve following functions:
1. Read words from file and extract every word into a vector for storage
2. Construct a Map to link every word with a struct Node that contains multiple information like priority, position, length_word, heuristics; 
    * priority = the priority of each string
    * position = steps from the first string 
    * length_word = the length of each string
    * heuristics = approximate needed steps from the word to the last_word

3. Use MinHeap<string> when using one of the function AStarSearch

Important Functions in doublet.cpp:
1.  void Make_Graph(vector<string> &words, map<string, Node*> &match)
Connect the nodes of the string

2.  void AStarSearch(string first_word, map<string, Node*> &match, string last_word)
Find the shortest path to the last word and print out the number for expansions

Besides the files, I also created the Makefile to compile MinHeap.h and doublet.cpp, producing the executable **doublet**
