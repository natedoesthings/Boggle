#include <iostream>
#include "TrieNode.h"

//The constructor. Takes a character for the node, and a bool
//indicating whether it represents the end of a word. Note, there is no
//default ctor.
TrieNode::TrieNode(char c, bool b): value(c), flag(b), alphabet(){

}

//The copy constructor
TrieNode::TrieNode(const TrieNode &rhs): value(rhs.value), flag(rhs.flag), alphabet(){
    for(size_t i = 0; i < SIZE; i++) {
        if(rhs.alphabet[i] != nullptr) {
            alphabet[i] = new TrieNode(*rhs.alphabet[i]);

        }
        else {
            alphabet[i] = nullptr;
        }


    }

}

//The destructor
TrieNode::~TrieNode() {
    for(size_t i = 0; i < SIZE; i++) {
        delete alphabet[i];
        alphabet[i] = nullptr;
    }



}

//Assignment operator
const TrieNode &TrieNode::operator=(const TrieNode &rhs) {
    if(this != &rhs) {
        TrieNode tmp(rhs);
        std::swap(value, tmp.value);
        std::swap(flag, tmp.flag);
        std::swap(alphabet, tmp.alphabet);
    }

    return *this;
}

//Insert str starting with the given TrieNode. Create new TrieNodes
//as needed and be sure to set the boolean flag on the last node to
//true
void TrieNode::insert(const std::string &str) {
    if(str.length() == 0) {
        flag = true;
    }
    else {
        size_t i = str[0] - 'a';

        if(alphabet[i] == nullptr) {
            //create a new node, if the node is empty at i
            alphabet[i] = new TrieNode(str[0], false);

        }
        alphabet[i]->insert(str.substr(1)); //continue to the next letter in the str

    }

}

//Returns true if str is in the sub-Trie starting at the given TrieNode,
//else returns false
bool TrieNode::isWord(const std::string &str) const {
    if(str.length() == 0) {
        return false;
    }

    size_t i = str[0] - 'a';

    if(alphabet[i] != nullptr) {
        if(str.length() == 1) {
            //once the end of the string is reached, return if the flag is true to determine isWord
            return alphabet[i]->flag;
        }
        return alphabet[i]->isWord(str.substr(1)); //continue to the next letter in the str

    }

    return false;


}

//Returns true if pre is a prefix of a word in the sub-Trie starting at
//the given TrieNode, else returns false
bool TrieNode::isPrefix(const std::string &pre) const {
    if(pre.length() == 0) {
        return true;
    }

    size_t i = pre[0] - 'a';

    //checks if the letter exists in the trie, if not return false
    if(alphabet[i] != nullptr) {
        return alphabet[i]->isPrefix(pre.substr(1));
    }

    return false;


}

//Prints all words starting at the given TrieNode. The parameter
//string str stores the letters of all previous TrieNode objects up to
//the node currently being processed.
void TrieNode::print(const std::string &str) const{

    if(flag && value != ' ') {
        std::cout << str << std::endl; //print str when it reaches end of the word
    }

    for(size_t i = 0; i < SIZE; i++) {
        if(alphabet[i] != nullptr) {
            alphabet[i]->print(str + alphabet[i]->value); //add to the str string all the letters
        }

    }

}

//Returns a count all the nodes in the sub-Trie that end a word.
size_t TrieNode::wordCount() const {

    size_t count = 0;

    for(size_t i = 0; i < SIZE; i++) {
        if(alphabet[i] != nullptr) {
            if(alphabet[i]->flag) {
                count++; //count up all the letters that end a word
            }
            count += alphabet[i]->wordCount(); //add that to the next alphabet array child
        }

    }

    return count;
}


