/**
 * simple program for message-board exercise.
 * 
 */

#include "Board.hpp"
#include "Direction.hpp"

using ariel::Direction;

#include <unistd.h>
#include <iostream>
#include <stdexcept>

using namespace std;

static ariel::Board board;

int postOnBoard() {
    u_int row, col, d;
    Direction dir;
    string post;

    cout << "enter row:" << endl;
    cin >> row;
    cout << endl << "enter collumn:";
    cin >> col;
    cout << endl << "for horizontal post enter 1, else enter 0:";
    cin >> d;
    dir = d == 1 ? Direction::Horizontal : Direction::Vertical;
    cout << endl << "write your post:";
    cin >> post;
    board.post(row, col, dir, post);
    cout << "post was added seccssfully!!";
    usleep(3000000);

    return 1;
}

int readFromBoard() {
    u_int row, col, d, length;
    Direction dir;

    string post;

    cout << "enter row:" << endl;
    cin >> row;
    cout << endl << "enter column:";
    cin >> col;
    cout << endl << "for horizontal post enter 1, else enter 0:";
    cin >> d;
    dir = d == 1 ? Direction::Horizontal : Direction::Vertical;
    cout << "how much do you want to read? :" << endl;
    cin >> length;
    cout << board.read(row, col, dir, length) << endl;
    return 1;
}

int showBoard()
{
    board.show();
    return 1;
}

int boardOperations() {

    int keepRuning;
    string post;


    int operation;
    cin >> operation;
    switch (operation) {
        case 1:
            keepRuning = postOnBoard();
            break;
        case 2:
            keepRuning = readFromBoard();
            break;
        case 3:
            keepRuning = showBoard();
            break;
        case 0:
            keepRuning = 0;
            break;

        default:
            cout << "illegal operation code. please try again";
            keepRuning = 1;
            break;
    }
    return keepRuning;
}

void drawSnowMan() {
    std::array<std::string, 4> hatsTop = {"     ", " ___ ", "  _  ", " ___ "},
            hatsBot = {"_===_", ".....", " /_\\ ", "(_*_)"},
            eyes = {".", "o", "O", "-"},
            noses = {",", ".", "_", " "},
            lArmsTop = {" ", "\\", " ", " "},
            lArmsBot = {"<", " ", "/", " "},
            rArmsTop = {" ", "/", " ", " "},
            rArmsBot = {">", " ", "\\", " "},
            torsos = {" : ", "] [", "> <", "   "},
            bases = {" : ", "\" \"", "___", "   "};

    cout << "      " << hatsTop.at(0) << std::endl
         << "      " << hatsBot.at(0) << std::endl
         << "     " << lArmsTop.at(1) << "(" << eyes.at(2) << noses.at(0) << eyes.at(1) << ")" << rArmsTop.at(1)
         << std::endl
         << "     " << lArmsBot.at(1) << "(" << torsos.at(1) << ")" << rArmsBot.at(1) << std::endl
         << "      (" << bases.at(2) << ") ";
}

void runBoard(){
    board.post(0,0,Direction::Horizontal, "hello world");
    board.post(2,0,Direction::Horizontal, "second row");
    board.post(1,3,Direction::Vertical, "vertical msg");

    board.post(5,10,Direction::Horizontal, "sup dude? how you doing??");

    board.show();
}

int main() {
//    runBoard();
    int keepGoing;

    do{
        drawSnowMan();
        cout << "\n\nWellcome to the post board program!,\n choose what operation you want to do:" << endl
             << " 1) add a post. \n 2) read from board. \n 3) show all post board.\n \n 0) EXIT." << endl;
        keepGoing = boardOperations();
    }while(keepGoing);

    return 0;
}

