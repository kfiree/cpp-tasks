//
// Created by user on 02/05/2021.
//

#pragma once

#include <stdio.h>
#include "Player.hpp"
#include "Board.hpp"
#include "City.hpp"


namespace pandemic
{
    class GeneSplicer : public Player
    {
        public:
            GeneSplicer(Board board, City city);
    };
}


