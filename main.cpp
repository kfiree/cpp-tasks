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


int boardOperations(){
    u_int row, col, d, length;
    int keep;
    string post;
    Direction dir;
    static ariel::Board board;
    	
    int operation;
    cin >> operation;
    switch (operation)  {
        case 1:
            cout <<"enter row:"<< endl;
            cin >> row;
            cout << endl <<"enter collumn:";
            cin >> col;
            cout << endl <<"for horizontal post enter 1, else enter 0:";
            cin >> d;
            dir = d == 1? Direction::Horizontal : Direction::Vertical; 
            cout << endl <<"write your post:";
            cin >> post;
            board.post(row, col, dir, post);
            cout << "post was added seccssfully!!";
            usleep(3000000);
            keep = 1;
            break;
    
        case 2:
            cout <<"enter row:"<< endl;
            cin >> row;
            cout << endl <<"enter collumn:";
            cin >> col;
            cout << endl <<"for horizontal post enter 1, else enter 0:";
            cin >> d;
            dir = d == 1? Direction::Horizontal : Direction::Vertical; 
            cout<<"how much do you want to read? :" << endl;
            cin >> length;
            cout << board.read(row, col, dir, length) << endl;
            keep = 1;
            break;
        case 3:
            board.show();
            keep = 1;
            break;
            
        case 0:
            keep = 0;
            break;
            
        default:
            cout <<"illegal operation code. please try again";
            keep = 1;
            break;
    }
    return keep;
}

void drawSnowMan(){
            std::array<std::string, 4> hatsTop= {"     ", " ___ ","  _  ", " ___ "},
     hatsBot={"_===_", ".....", " /_\\ ", "(_*_)"},
     eyes = {".", "o", "O", "-"},
     noses = {",", ".", "_"," "},
     lArmsTop = {" ", "\\", " ",  " "},
     lArmsBot = {"<", " ", "/",  " "},
     rArmsTop = {" ", "/", " ",  " "},
     rArmsBot = {">", " ", "\\",  " "},
     torsos = {" : ", "] [", "> <", "   "},
     bases = {" : ", "\" \"", "___",  "   "};
    
    cout << "      " << hatsTop.at(0) << std::endl
            << "      " << hatsBot.at(0) << std::endl
            <<"     "<< lArmsTop.at(1) << "(" << eyes.at(2) << noses.at(0) << eyes.at(1) << ")" << rArmsTop.at(1) << std::endl
            <<"     "<< lArmsBot.at(1) << "(" << torsos.at(1) << ")" << rArmsBot.at(1) << std::endl
            << "      (" << bases.at(2) << ") ";
}

int main() { 

    // static ariel::Board board;
    //         Direction dir = 1 == 1? Direction::Horizontal : Direction::Vertical; 
    //         board.post(0, 1, Direction::Horizontal, "12313dsfdsfd");
    //         board.post(2, 5, Direction::Vertical, "gfdgf");
    //         board.post(0, 1, Direction::Horizontal, "aba");
    //         board.post(10, 12, Direction::Horizontal, "34");
    //         board.post(3, 7, Direction::Vertical, "12313dsfdsfd");
    //         board.post(1, 1, Direction::Horizontal, "12313dsfdsfd");

    //         board.show();

    int keepGoing=1;
	while(keepGoing)
    {
        drawSnowMan();
        cout<< "\n\nWellcome to the post board program!,\n choose what operation you want to do:" << endl
	    << " 1) add a post. \n 2) read from board. \n 3) show all post board.\n \n 0) EXIT."<<endl;
        keepGoing = boardOperations();
	}
	return 0;
}

