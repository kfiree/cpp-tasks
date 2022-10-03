#include "Board.hpp"
#include "Direction.hpp"
#include <iostream> 
#include <map>
#include <algorithm>

using std::string;
using std::pair; 
using std::make_pair;
using std::min;
using std::max;
using std::cout;
using std::endl;
using ariel::Direction;

Direction h = Direction::Horizontal;
Direction v = Direction::Vertical; 

unsigned int getMaxUInt(){
    u_int O = 1;
    u_int Z = 0;
    return Z-O;
}

namespace ariel 
{
    Board::Board(){ 
        this->minR=getMaxUInt();
        this->minC=getMaxUInt();
        this->maxR=0;
        this->maxC=0;

        // posts map
        this->postMap = std::map<u_int, std::map<u_int, char>>(); 
    }

    string WriteEmpty(u_int leng){
        string str((u_int)leng, '_');
        return str;
    }
    
    
    void Board::post(u_int row, u_int col, Direction dir, string txt){
        // set min board bounds
        minR = min(minR, row);
        minC = min(minC, col);

        // add post
        for(char& c : txt) {
            postMap[row][col] = c;
            dir == h ? col++ : row++; 
        }

        // set max board bounds
        maxR = max(maxR,row);
        maxC = max(maxC, col);





        txt+=' ';
    }

    string Board::read(u_int row, u_int col, Direction dir, u_int len){
        char emptyC = '_';
        string readStr;

        // For accessing outer map
        std::map<u_int, std::map<u_int, char> >::iterator rowItr;

        // For accessing inner map
        std::map<u_int, char>::iterator colItr;


        for(u_int i = 0; i<len; i++){

            // check if row exsist
            rowItr = postMap.find(row);
            if(rowItr != postMap.end()){
                // check if col exist
                colItr = postMap[row].find(col);
                if(colItr != postMap[row].end()){
                    readStr+=colItr->second;
                    dir == h ? col++ : row++;
                    continue;
                }
            }
            dir == h ? col++ : row++;
            readStr+=emptyC;
        }
        return readStr;
    }

    // TODO make const
    void Board::show(){        
        // For accessing outer map
        std::map<u_int, std::map<u_int, char> >::iterator rowItr;
    
        // For accessing inner map
        std::map<u_int, char>::iterator colItr;

        string topNbot(maxC-minC+2, '=');
        string side = "||";
        char emptyC = '_';
        
        cout <<"  "<<topNbot<<endl;

        for(u_int row = minR; row<maxR; row++)
        {
            cout << side;
            if(postMap.find(row) == postMap.end())
            {
                cout << WriteEmpty(maxC-minC) << side << endl;
            }
            else
            {
                for(u_int col = minC; col<maxC; col++)
                {
                    colItr = postMap[row].find(col);
                    if( colItr != postMap[row].end())
                    {
                        cout << colItr->second ;
                    }else{
                        cout<<emptyC;
                    }
                }
            }

            cout<< side << endl;
        }
        
        cout <<topNbot<<endl;        
    } 
    
}
