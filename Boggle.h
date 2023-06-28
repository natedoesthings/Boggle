#ifndef PROJECT10_BOGGLE_H
#define PROJECT10_BOGGLE_H

#include "Trie.h"

const size_t ROW = 4;
const size_t COL = 4;
const size_t WORDLENGTH = 4;
const std::string BOARDFILE = "boggle-in.txt";
const std::string DICTIONARY = "ospd.txt";

class Boggle {

private:

    struct Board{
        char value;
        bool visited;
    };

    Trie lexicon;
    Trie generated;
    Board board[ROW][COL];

    //bool, checks whether the entered position at board[row][col] is within
    //the bounds of the ROWxCOL array
    bool inBounds(int row, int col) const;

    //uses recursive backtracking by checking all the adjacent letters and going through
    //each path to figure out wether there are any valid words from the dictionary. does the backtracking when
    //no adjacent letters that have not been visited already have been found
    void checkAdjacent(int row, int col, std::string &str, const Trie &user);

    //helper method
    //checks if the row and col are in bounds, then checks if the character has been visited, if not
    //check if the str plus that character is a prefix, if so call the checkAdjacent algo on that adjacent character
    //with the str being updated with the addition of the adjacent character
    void visitAdjacent(int row, int col, std::string &str, const Trie &user);


public:

    //Default constructor initialzing the Trie member lexicon, with all the words in the wordFile, and initializies
    //the board 2d-array structure with the boardFile,
    Boggle();

    //generates words by calling checkAdjacent on each character in the board, then inserts those words in the
    //private member generated
    Trie generatedWords(const Trie &user);


    //--------------------------Extra Credit #1----------------------------
    //The following methods were used for the extra credit #1 problem

    //returns the trie containing the dictionary of words
    Trie returnLexicon() const;

    //returns a string representation of the board
    std::string printBoard() const;


};


#endif //PROJECT10_BOGGLE_H
