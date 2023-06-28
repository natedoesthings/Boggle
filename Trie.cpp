#include <stdexcept>
#include <fstream>
#include <iostream>
#include "Trie.h"
#include "TrieNode.h"

//The default constructor
Trie::Trie() : root(' ', false){

}

//Insert the parameter word into the Trie
void Trie::insert(const std::string &word) {
    root.insert(word);
}

//Insert all words in the specified file into the Trie. Throws a
//std::invalid_argument exception if the specified file cannot be
//opened.
void Trie::loadFromFile(const std::string &filename) {
    std::ifstream infile;
    infile.open(filename.c_str());

    // Do error checking here
    if (infile.fail()) {
        throw std::invalid_argument("failed to open " + filename);
    }

    std::string inserted;
    while(infile >> inserted) {
        insert(inserted);
    }


}

//Returns true if word is in the Trie, else returns false
bool Trie::isWord(const std::string &word) const {
    return root.isWord(word);
}

//Returns true if pre is a prefix of a word in the Trie, else returns false
bool Trie::isPrefix(const std::string &pre) const {
    return root.isPrefix(pre);
}

//Print all words in the Trie, one per line. Print in alphabetical order.
void Trie::print() const {
    root.print("");
}

//Returns a count all the words in the Trie
size_t Trie::wordCount() const {
    return root.wordCount();
}
