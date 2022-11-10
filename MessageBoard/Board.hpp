#pragma once

#include "Direction.hpp"
#include <map> 
#include <vector>
#include <string>
#include <sys/types.h>
#include <inaddr.h>

namespace ariel{
    class Board 
    {
        private:
            u_int minR, minC, maxR, maxC;
            std::map<u_int, std::map<u_int, char>> postMap;

            /**
                posts format =>  map< row, <column ,post>>

                all post saved as horizental posts. 
                for example vertical "aa" at (0,0) will be saved as two posts 
                "a" in (0,0) and "a"(1,0)
            */


        public:
            /** CONSTRUCTORS */
            Board();
            ~Board(){};


            /**
             * Post a message on post board.
             *
             * @param row Message location.
             * @param column Message location.
             * @param dir Message direction.
             * @param txt Message to post.
             */
            void post(u_int row, u_int column, Direction dir, std::string txt);

            /**
             * Read a message from post board.
             *
             * @param row Message location.
             * @param column Message location.
             * @param dir Message direction.
             * @param len Length to read.
             * @return
             */
            std::string read(u_int row, u_int column, Direction dir, u_int len);

            /**
             * show all board messages.
             */
            void show();
    };
}