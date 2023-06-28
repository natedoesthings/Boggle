#include <iostream>
#include "Boggle.h"


void printResults(const Trie &data, std::string &player);

int main() {

    Boggle board;

    Trie lexicon = board.returnLexicon(); //trie containing all the words in the dictionary

    std::cout << "Here is the Boggle board:\n" << std::endl;

    std::cout << board.printBoard() << std::endl; //prints the board

    std::cout << "Enter as many words as you can find, one word per line.\n"
                 "Signal the end of your list by entering the letter Q or q.\n"
                 "You can take as long as you want." << std::endl;

    Trie userTrie; //trie that will be used to store all the user valid words

    std::string userWord;
    std::cin >> userWord;

    while(userWord != "Q" and userWord != "q") {
        bool validWord = true;

        //conditions that constitute an invalid word
        if(userWord.length() < 4) {
            std::cout << "Sorry, your words must be at least 4 characters long." << std::endl;
            validWord = false;
        }
        else if(!lexicon.isWord(userWord)) {
            std::cout << "Don't try to cheat! " << userWord << " is not a valid word." << std::endl;
            validWord = false;
        }
        else if(userTrie.isWord(userWord)) {
            std::cout << "You already found the word " << userWord << "." << std::endl;
            validWord = false;
        }

        //if none of the previous conditions were met, then insert the word
        if(validWord) {
            std::cout << "Okay, you found the word " << userWord << "." << std::endl;
            userTrie.insert(userWord);
        }

        //enter another word
        std::cin >> userWord;


    }

    //computer generated words after the user gets the "advantage"
    Trie computerTrie = board.generatedWords(userTrie);


    //prints the results for both the user and computer
    std::string you = "You";
    printResults(userTrie, you);

    std::string computer = "The computer";
    printResults(computerTrie, computer);

    return 0;
}

void printResults(const Trie &data, std::string &player) {

    std::cout << std::endl;

    std::cout  <<player<<" found the following words:\n"
                 "============" << std::endl;

    data.print();

    std::cout << "============\n"
                 <<player<<" found "<< data.wordCount() <<" words." << std::endl;

}



