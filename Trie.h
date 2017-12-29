/* 
 * File:   Trie.h
 * Author: petros
 *
 * Created on December 24, 2017, 2:51 PM
 */

#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_set>
#include <list>
#include <string.h>

#define SIZE  128
#define IGNORE  1
#define IS_LEAF 2

using namespace std;

struct Word {
    char *data;
    size_t len;

    Word(char*);
    ~Word();
};

struct Text {
    char *data;
    size_t len;
    size_t *index;
    size_t size;

    Text(const char *);
    Text(Text *, size_t);
    ~Text();
    void expand(Text *, size_t);

    bool isSubtext(Text *);
    size_t common(Text *);
    void print();
};

struct TrieNode {
    Text *key;
    unsigned char *leaf;
    TrieNode ***next;
    size_t index;
    size_t *sizes; //size of the 2nd dimension of

    TrieNode(Text *, size_t);
    void add(Text *, size_t);
    void del(Text *, size_t);
    void query(Text *, size_t, string);
    void query_all(Text *);
    void print(string);
};

void add(TrieNode *, char *);
void query(TrieNode *, char *);
void query_all(TrieNode *, char *);
void print(TrieNode *, string);
bool del(TrieNode *, char *);



#endif /* TRIE_H */
