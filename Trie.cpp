#include "Trie.h"

void add(TrieNode *node, char *setence) {
    char *word = strtok(setence, " \n");

    if (NULL == word) {//should never happen
        node->leaf = true;
        return;
    }

    while (1) {
        list<TrieNode *>::iterator i;
        for (i = node->next.begin(); i != node->next.end(); i++) {
            if (!strcmp((*i)->key, word)) {
                //move to the next word
                if (NULL == (word = strtok(NULL, " \n"))) {
                    (*i)->leaf = true;
                    return;
                }
                node = *i;
                break;
            }
        }
        if (i == node->next.end())
            break;
    }

    while (word != NULL) {
        TrieNode *newNode = new TrieNode();
        newNode->key = new char[strlen(word) + 1];
        strcpy(newNode->key, word);
        newNode->leaf = false;
        node->next.push_back(newNode);
        node = newNode;
        word = strtok(NULL, " \n");
    }
    cout << endl;
    node->leaf = true;

}

void print(TrieNode *node, string prefix = "") {
    if (node->leaf == true) {
        cout << prefix << ' ' << node->key << endl;
    }
    string new_prefix = string("\t");
    new_prefix += prefix;
    for (list<TrieNode*>::iterator i = node->next.begin(); i != node->next.end(); i++) {
        print(*i, new_prefix);
    }
}

void query(TrieNode *node, char *setence) {
    char *word = strtok(setence, " \n");
    string w = word;

    if (NULL == word) {//should never happen
        if (node->leaf == true)
            cout << w << endl;
    }

    while (1) {
        list<TrieNode *>::iterator i;
        for (i = node->next.begin(); i != node->next.end(); i++) {
            if (!strcmp((*i)->key, word)) {
                //move to the next word
                if ((*i)->leaf == true)
                    cout << w << endl;
                node = *i;
                break;
            }
        }
        if (NULL == (word = strtok(NULL, " \n"))) {
            return;
        }
        w += " ";
        w += word;
        if (i == node->next.end())
            break;
    }

    return;
}

void query_all(TrieNode *node, char *setence) {
    while (1) {
        query(node, setence);
        while (*setence != ' ' && *setence)
            setence++;
        if (*setence == 0)
            return;
        setence++;
    }
}

bool del(TrieNode *node, char *sentence) {
    char *word = strtok(sentence, " \n");

    if (NULL == word) {
        return true;
    }

    list<TrieNode *>::iterator i;
    for (i = node->next.begin(); i != node->next.end(); i++) {
        if (!strcmp((*i)->key, word)) {
            if (del(*i, sentence) == true && (*i)->leaf == true) {
                (*i)->leaf = false;
            }
        }
    }

    return false;
}
