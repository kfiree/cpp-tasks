//
// Created by user on 02/05/2021.
//

#pragma once

#include "Player.hpp"
#include "Board.hpp"
#include "City.hpp"


namespace pandemic
{
    class Researcher : public Player
    {
        public:
            Researcher(Board board, City city);
    };
}


