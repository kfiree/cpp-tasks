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
        private:
            const string _role = "GeneSplicer";
        public:
            GeneSplicer(Board& board, City city):Player(board, city){}
            string role();

            Player& discover_cure(Color color);
    };
}


