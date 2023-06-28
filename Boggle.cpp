#include <fstream>
#include "Boggle.h"

//Default constructor initialzing the Trie member lexicon, with all the words in the wordFile, and initializies
//the board 2d-array structure with the boardFile,
Boggle::Boggle() : generated(){
    lexicon.loadFromFile(DICTIONARY);

    std::ifstream infile;
    std::string boardFile = BOARDFILE;
    infile.open(boardFile.c_str());

    // Do error checking here
    if (infile.fail()) {
        throw std::invalid_argument("failed to open" + boardFile);
    }

    char inserted;
    size_t row = 0, col = 0;

    while(infile >> inserted) {
        board[row][col].value = inserted;
        board[row][col].visited = false;
        col++;

        if(col == COL) {
            row++;
            col = 0;
        }

    }



}

//generates words by calling checkAdjacent on each character in the board, then inserts those words in the
//private member generated
Trie Boggle::generatedWords(const Trie &user) {
    for(size_t row = 0; row < ROW; row++) {
        for(size_t col = 0; col < COL; col++) {
            std::string str = "";
            str += board[row][col].value;
            checkAdjacent(row, col, str, user);

        }
    }

    return generated;
}

//Extra Credit #1
//returns the trie containing the dictionary of words
Trie Boggle::returnLexicon() const {
    return lexicon;
}

//Extra Credit #1
//returns a string representation of the board
std::string Boggle::printBoard() const {
    std::string printed = "";
    std::string space = " ";
    for(size_t row = 0; row < ROW; row++) {
        for(size_t col = 0; col < COL; col++) {
            printed += space + board[row][col].value;

        }

        printed += "\n";
    }

    return printed;
}

//bool, checks whether the entered position at board[row][col] is within
//the bounds of the ROWxCOL array
bool Boggle::inBounds(int row, int col) const {
    return !(row < 0 || col < 0 || row > (int) (ROW - 1) || col > (int) (COL - 1));

}

//uses recursive backtracking by checking all the adjacent letters and going through
//each path to figure out wether there are any valid words from the dictionary. does the backtracking when
//no adjacent letters that have not been visited already have been found
void Boggle::checkAdjacent(int row, int col, std::string &str, const Trie &user) {

    //conditions on inserting a word, last condition is for the extra credit #1
    //word length has to be at least 4
    //word has to be in the lexicon
    //word is not already in the generated trie
    //word can not be a user inputted word
    if(str.length() >= WORDLENGTH && lexicon.isWord(str) && !generated.isWord(str) && !user.isWord(str)) {
        generated.insert(str);
    }

    board[row][col].visited = true; //set the visited flag to true

    //visit all adjacents

    for(int row1 = row -1; row1 <= row + 1; row1++) {
        for(int col1 = col -1; col1 <= col + 1; col1++) {
            visitAdjacent(row1, col1, str, user);
        }
    }


//    visitAdjacent(row + 1, col - 1, str, user);
//
//    visitAdjacent(row + 1, col, str, user);
//
//    visitAdjacent(row + 1, col + 1, str, user);
//
//    visitAdjacent(row + 1, col - 1, str, user);
//
//    visitAdjacent(row, col + 1, str, user);
//
//    visitAdjacent(row - 1, col + 1, str, user);
//
//    visitAdjacent(row + 1, col - 1, str, user);
//
//    visitAdjacent(row - 1, col, str, user);
//
//    visitAdjacent(row + 1, col - 1, str, user);
//
//    visitAdjacent(row - 1, col - 1, str, user);
//
//    visitAdjacent(row, col - 1, str, user);

    str = str.substr(0,str.length() - 1);
    board[row][col].visited = false; //then set it back to false once all the adjacent paths have been checked

}

//helper method
//checks if the row and col are in bounds, then checks if the character has been visited, if not
//check if the str plus that character is a prefix, if so call the checkAdjacent algo on that adjacent character
//with the str being updated with the addition of the adjacent character
void Boggle::visitAdjacent(int row, int col, std::string &str, const Trie &user) {

    if(inBounds(row, col)) {
        if(!board[row][col].visited) {
            if(lexicon.isPrefix(str + board[row][col].value)) {
                str += board[row][col].value;
                checkAdjacent(row, col, str, user);
            }

        }

    }
}


