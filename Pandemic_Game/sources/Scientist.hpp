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
    class Scientist : public Player
    {
            int n;

            string const _role = "Scientist";//TODO add to constructor?

        public:
            Scientist(Board& board, City city, int num):Player(board, city), n(num){}

            string role();

            Player& discover_cure(Color color);

    };
}


