/* 
 * File:   main.cpp
 * Author: petros
 *
 * Created on December 24, 2017, 2:50 PM
 */
#include "Trie.h"

/*
 * 
 */
int main(int argc, char** argv) {

    TrieNode *trie = new TrieNode;
    trie->key = "";
    trie->leaf = false;

    string input;
    char *buffer = new char[4096];

    while (1) {
        getline(cin, input);
        if (input == "S")
            break;
        strcpy(buffer, input.c_str());
        add(trie, buffer);
    }

    while (1) {
        switch (getchar()) {
            case 'Q':
                break;
            case 'A':
                break;
            case 'D':
                break;
        }
    }

    while (1) {
        cout << "Enter ngram: ";
        getline(cin, input);
        if (input == "end")
            break;
        strcpy(buffer, input.c_str());
        add(trie, buffer);
    }
    cout << "Your Trie:\n";
    print(trie, "");
    cout << endl;

    while (1) {
        cout << "Enter query: ";
        getline(cin, input);
        if (input == "end")
            break;
        strcpy(buffer, input.c_str());
        query_all(trie, buffer);
    }

    return 0;
}

