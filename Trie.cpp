#include "Trie.h"

/*completed -  need to be tested*/
TrieNode::TrieNode(Text *text, size_t start) {
    key = new Text(text, start);
    leaf = new unsigned char[key->size]; //make them all 0
    next = new TrieNode**[key->size];
    sizes = new size_t[key->size];

    for (int i = 0; key->size > i; i++) {
        leaf[i] = 0;
        sizes[i] = SIZE;
        next[i] = new TrieNode*[SIZE];
        for (int j = 0; SIZE > j; j++)
            next[i][j] = NULL;
    }
    leaf[key->size - 1] = 1;
}

void TrieNode::print(string prefix) {
    cout << prefix;
    key->print();
    cout << endl;
    for (int i = 0; key->size > i; i++) {
        for (int j = 0; sizes[i] > j; j++)
            if (NULL != next[i][j])
                next[i][j]->print(prefix);
    }
}

/*There are _ cases:
 * 1) the new ngram expands the node, that means
 *  we have to allocate more memory for the key and index
 * 2) the new ngram is a substring of the node so we have to set the 
 *  appropriate bool variable true
 * 3) the new ngram is partially a substring of the node so we have to find
 *  the next node to and continue from there.
 */
void TrieNode::add(Text *text, size_t offset) {
    int i;

    //find the maximum substring
    //text = [w1] [w2] [w3] [w4]
    //key  = [w1] [w2] [w3] [w5]
    //in this case we want to the first three words 
    for (i = 0; key->size > i && text->size > i + offset; i++) {
        if (strcmp(&(key->data[ key->index[i] ]),
                &(text->data[ text->index[i + offset] ]))) {
            break;
        }
    }
    //cout << "I : " << i << endl;

    /* special case where the node is identical to the new ngram */
    if (i == key->size && i + offset == text->size) {
        leaf[i] = 1;
    }

    /* case 1 */
    if (i == key->size && i + offset < text->size) {
        //  cout << "CASE 1\n";
        //allocate more memory for leaf
        leaf = (unsigned char *) realloc(leaf, sizeof (unsigned char) * (key->size + text->size - i - offset));
        for (int j = key->size; j < key->size + text->size - i - offset; j++)
            leaf[j] = 0;
        leaf[key->size + text->size - i - offset - 1] = 1;
        //allocate more memory for next and sizes
        next = (TrieNode ***) realloc(next, sizeof (TrieNode**)*(key->size + text->size - i - offset));
        sizes = (size_t *) realloc(sizes, sizeof (size_t*)*(key->size + text->size - i - offset));
        for (int j = key->size; j < key->size + text->size - i - offset; j++) {
            sizes[j] = SIZE;
            next[j] = new TrieNode*[SIZE];
            for (int k = 0; SIZE > k; k++)
                next[j][k] = NULL;
        }
        //allocate more memory for key
        key->expand(text, i + offset);
        return;
    }

    /* case 2 */
    if (i < key->size && i + offset == text->size) {
        //cout << "CASE 2\n";
        leaf[i] = 1;
    }

    /* case 3 */
    if (i < key->size && i + offset < text->size) {
        //cout << "CASE 3\n";
        //move to the next node if it exists otherwise create a new one
        int k;

        for (k = 0; sizes[i] > k; k++) {
            //next doesnt exist but there is space to create it
            if (NULL == next[i][k]) {
                //      cout << "-1\n";
                //needs to be updated
                next[i][k] = new TrieNode(text, offset + i/*needs update*/);
                //next[i][k]->add(text, offset + i);
                return;
            }
            //next does exist
            if (!strcmp(next[i][k]->key->data, &(text->data[ text->index[i] ]))) {
                //    cout << "-2\n";
                next[i][k]->add(text, offset + i);
                return;
            }
        }

        //next doesnt exist and there is no space so we have to allocate extra space
        if (k == sizes[i]) {
            //cout << "-3\n";
            next[i] = (TrieNode**) realloc(next[i], 2 * sizeof (TrieNode**) * sizes[i]);
            for (int j = 0; sizes[j] > j; j++) {
                next[i][j] = NULL;
            }
            next[i][k] = new TrieNode(text, offset);
            sizes[i] *= 2;
            next[i][k]->add(text, offset + i);
        }

    }
}

void TrieNode::del(Text *text, size_t offset) {
    int i;

    //in this case we want to the first three words 
    for (i = 0; key->size > i && text->size > i + offset; i++) {
        if (strcmp(&(key->data[ key->index[i] ]),
                &(text->data[ text->index[i + offset] ]))) {
            break;
        }
    }

    /* special case where the node is identical to the new ngram */
    if (i == key->size && i + offset == text->size) {
        if (leaf[i] == 1) {
            //this must always be true!!!!
            leaf[i] = 0;
        }
    }

    /* case 1 */
    if (i == key->size && i + offset < text->size) {
        return;
    }

    /* case 2 */
    if (i < key->size && i + offset == text->size) {
        leaf[i] = 0;
    }

    /* case 3 */
    if (i < key->size && i + offset < text->size) {
        //move to the next node if it exists otherwise create a new one
        int k;

        for (k = 0; sizes[i] > k; k++) {
            //next doesnt exist but there is space to create it
            if (NULL == next[i][k]) {
                return;
            }
            //next does exist
            if (!strcmp(next[i][k]->key->data, &(text->data[ text->index[i] ]))) {
                next[i][k]->del(text, offset + i);
                return;
            }
        }
    }
}

void TrieNode::query(Text *text, size_t offset, string prefix) {
    int i;

    for (i = 0; key->size > i && text->size > i + offset; i++) {
        if (strcmp(&(key->data[ key->index[i] ]),
                &(text->data[ text->index[i + offset] ]))) {
            break;
        } else {
            prefix += " ";
            prefix += &(key->data[ key->index[i] ]);
            if (leaf[i] == 1) {
                /*FOUND MATCH*/
                cout << "FOUND : " << prefix << endl;
            }
        }
    }
    /* special case where the node is identical to the new ngram */
    if (i == key->size && i + offset == text->size) {
        //cout << "case 0\n";
        return;
    }

    /* case 1 */
    if (i == key->size && i + offset < text->size) {
        //cout << "case 1\n";
        return;
    }

    /* case 2 */
    if (i < key->size && i + offset == text->size) {
        //cout << "case 2\n";
        return;
    }

    /* case 3 */
    if (i < key->size && i + offset < text->size) {
        //cout << "case 3\n";
        //move to the next node if it exists otherwise create a new one

        for (int k = 0; sizes[i] > k; k++) {
            //next doesnt exist but there is space to create it
            if (NULL == next[i][k]) {
                //cout << k << " WHAT?\n";
                return;
            }
            //next does exist
            //cout << "K: " << k << ' ' << next[i][k]->key->data << endl;
            if (!strcmp(next[i][k]->key->data, &(text->data[ text->index[i] ]))) {
                //cout << "fff\n";
                next[i][k]->query(text, offset + i, prefix);
                return;
            }
        }
        //cout << "fmrkf\n";
    }
}

void TrieNode::query_all(Text *text) {
    //cout << "SIZE: " << text->size << endl;
    for (int i = 0; text->size - 1 > i; i++) {
        //cout << i << endl;
        query(text, i, string(""));
    }
}

