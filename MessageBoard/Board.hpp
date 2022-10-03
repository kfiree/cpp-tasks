#pragma once

#include "Direction.hpp"
#include <map> 
#include <vector>
#include <string>

namespace ariel{
// z
    class Board 
    {
        private:
            // bounds of board
            u_int minR, minC, maxR, maxC;

            // posts map
            std::map<u_int, std::map<u_int, char>> postMap; 
            /* 
                posts format =>  map< row, <column ,post>>

                all post saved as horizental posts. 
                for example vertical "aa" at (0,0) will be saved as two posts 
                "a" in (0,0) and "a"(1,0)
            */


        public:
            // constructor
            Board();
            ~Board(){};

            // post massage (given text, direction and location)
            void post(u_int row, u_int column, Direction dir, std::string txt);

            // read massage (given length, direction and location)
            std::string read(u_int row, u_int column, Direction dir, u_int len);

            void show();
    };
}