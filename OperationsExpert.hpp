//
// Created by user on 02/05/2021.
//

#pragma once

#include "Player.hpp"
#include "Board.hpp"
#include "City.hpp"

namespace pandemic
{
    class OperationsExpert: public Player 
    {
        public:
            OperationsExpert(Board b, City c); 
    };

}

