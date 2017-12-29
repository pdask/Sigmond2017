/* 
 * File:   main.cpp
 * Author: petros
 *
 * Created on December 24, 2017, 2:50 PM
 */
#include <fstream>

#include "Trie.h"

void start(char ** argv) {
    ifstream file1, file2;

    file1.open("small.init");
    file2.open("small.work");


    Text *text = new Text((char*) "-");

    TrieNode *trie = new TrieNode(text, 0);

    delete text;

    string input;

    while (1) {
        if (!getline(file1, input))break;

        //cout << input << endl;
        text = new Text(input.c_str());
        trie->add(text, 0);
        //text->print();
        delete text;
    }
    cout << "END\n";

    while (1) {
        if (!getline(file2, input))break;
        //cout << input << endl;
        switch (input[0]) {
            case 'Q':
                //cout << "Q\n";
                //getline(cin, input);
                text = new Text(input.c_str() + 2);
                trie->query_all(text);
                break;
            case 'A':
                //getline(cin, input);
                text = new Text(input.c_str() + 2);
                trie->add(text, 0);
                delete text;
                break;
            case 'D':
                //getline(cin, input);
                text = new Text(input.c_str() + 2);
                trie->del(text, 0);
                break;
        }
    }

    return;
}

int main(int argc, char** argv) {

    start(argv);
    return 0;

    Text *text = new Text((char*) "-");

    TrieNode *trie = new TrieNode(text, 0);

    Text *t = new Text("a");
    trie->add(t, 0);
    t = new Text("a b");
    trie->add(t, 0);
    t = new Text("a c");
    trie->add(t, 0);
    t = new Text("a b c");
    trie->add(t, 0);

    TrieNode *tn = trie->next[0][0];

    //cout << tn->key->size << endl;
    //tn->key->print();
    //for (int i = 0; i < tn->key->size; i++)
    //cout << ((size_t) tn->leaf[i]) << endl;
    t = new Text("a c");
    trie->query(t, 0, string(""));

    return 0;
}

