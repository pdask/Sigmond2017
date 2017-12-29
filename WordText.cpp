#include "Trie.h"

Word::Word(char *word) {
    len = strlen(word);
    data = new char[len + 1];
    strcpy(data, word);
}

Word::~Word() {
    delete data;
}

Text::Text(const char* text) {

    len = strlen(text);
    data = new char[len + 1];
    memcpy(data, text, len + 1);

    size = 1;
    while (*text) {
        if (*text == ' ')
            size++;
        text++;
    }

    index = new size_t[size];
    index[0] = 0;
    int j = 1;

    index[0] = 0;
    for (int i = 0; len > i; i++) {
        if (data[i] == ' ') {
            data[i] = '\0';
            index[j++] = i + 1;
        }
    }
}

Text::Text(Text *text, size_t start = 0) {
    len = text->len - text->index[start];
    data = new char[len + 1];
    memcpy(data, text->data + text->index[start], len + 1);

    size = text->size - start;
    index = new size_t[size];
    for (int i = 0; size > i; i++)
        index[i] = text->index[i + start] - text->index[start];

}

Text::~Text() {
    delete data;
    delete index;
}

void Text::expand(Text *text, size_t start = 0) {
    data = (char *) realloc(data, len + 1 + (text->len + 1 - text->index[start]));
    memcpy(data + len + 1, &(text->data[text->index[start]]), text->len + 1 - text->index[start]);

    index = (size_t *) realloc(index, sizeof (size_t)*(size + text->size - start));
    for (int i = 0; i < (text->size - start); i++) {
        index[size + i] = text->index[i + start] - text->index[start] + len + 1;
    }

    len += (text->len + 1 - text->index[start]);
    size += text->size - start;
}

void Text::print() {
    for (int i = 0; size > i; i++) {
        cout << '[' << &(data[ index[i] ]) << ']';
        cout.flush();
    }
    cout << endl;
    cout.flush();
}

bool Text::isSubtext(Text *text) {
    if (text->size > size || text->len > len)
        return false;

    for (int i = 0; size > i; i++) {
        if (strcmp(&(data[index[i]]), &(text->data[index[i]])))
            return false;
    }
    return true;
}

size_t Text::common(Text *text) {
    for (int i = 0; size > i && text->size > i; i++) {
        if (strcmp(&(data[index[i]]), &(text->data[index[i]])))
            return i;
    }
}
