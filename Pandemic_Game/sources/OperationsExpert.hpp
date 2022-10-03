//
// Created by user on 02/05/2021.
//

#pragma once

#include "Player.hpp"
#include "Board.hpp"
#include "City.hpp"
#include <string>

//using std::

namespace pandemic
{
    class OperationsExpert: public Player 
    {
        private:
            string const _role = "OperationsExpert";//TODO add to constructor?
        public:
            OperationsExpert(Board& board, City city): Player(board, city){};

            string role();

            Player& build();
    };

}

