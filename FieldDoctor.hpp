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
    class FieldDoctor : public Player
    {
        public:
            FieldDoctor(Board board, City city);
    };
}


