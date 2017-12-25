#include "Trie.h"

void add(TrieNode2 *node, char *setence) {
    char *word = strtok(setence, " \n");

    if (NULL == word) {//should never happen
        node->leaf = true;
        return;
    }

    while (1) {
        list<TrieNode2 *>::iterator i;
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
        TrieNode2 *newNode = new TrieNode2();
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

void query(TrieNode2 *node, char *setence) {
    char *word = strtok(setence, " \n");
    string w = word;

    if (NULL == word) {//should never happen
        if (node->leaf == true)
            cout << w << endl;
    }

    while (1) {
        list<TrieNode2 *>::iterator i;
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

void query_all(TrieNode2 *node, char *setence) {
    while (1) {
        query(node, setence);
        while (*setence != ' ' && *setence)
            setence++;
        if (*setence == 0)
            return;
        setence++;
    }
}