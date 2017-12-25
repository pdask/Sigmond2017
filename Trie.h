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

#define DELETE  0
#define IGNORE  1
#define IS_LEAF 2

using namespace std;

struct TrieNode {
    char *key;
    bool leaf;
    list<TrieNode *> next;
};

void add(TrieNode *, char *);
void query(TrieNode *, char *);
void query_all(TrieNode *, char *);
void print(TrieNode *, string);
bool del(TrieNode *, char *);


struct TrieNode2 {
    size_t key;
    size_t size;
    bool leaf;
    list<TrieNode *> next;
};

void add(TrieNode2 *, char *);
void query(TrieNode2 *, char *);
void query_all(TrieNode2 *, char *);



#endif /* TRIE_H */

