#ifndef PROJECT_9_TRIENODE_H
#define PROJECT_9_TRIENODE_H

#include <string>

const size_t SIZE = 26;

class TrieNode {



private:

    char value;
    bool flag;
    TrieNode *alphabet[SIZE];


public:

    //The constructor. Takes a character for the node, and a bool
    //indicating whether it represents the end of a word. Note, there is no
    //default ctor.
    TrieNode (char c, bool b);

    //The copy constructor
    TrieNode(const TrieNode& rhs);

    //The destructor
    ~TrieNode();

    //Assignment operator
    const TrieNode& operator= (const TrieNode& rhs);

    //Insert str starting with the given TrieNode. Create new TrieNodes
    //as needed and be sure to set the boolean flag on the last node to
    //true
    void insert (const std::string& str);

    //Returns true if str is in the sub-Trie starting at the given TrieNode,
    //else returns false
    bool isWord (const std::string& str) const;

    //Returns true if pre is a prefix of a word in the sub-Trie starting at
    //the given TrieNode, else returns false
    bool isPrefix (const std::string& pre) const;

    //Prints all words starting at the given TrieNode. The parameter
    //string str stores the letters of all previous TrieNode objects up to
    //the node currently being processed.
    void print (const std::string& str) const;

    //Returns a count all the nodes in the sub-Trie that end a word.
    size_t wordCount ( ) const;


};


#endif //PROJECT_9_TRIENODE_H
