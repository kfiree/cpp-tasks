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
        private:
            const string _role = "Researcher";

        public:
            Researcher(Board& board, City city):Player(board, city){}

            string role();

            Player& discover_cure(Color color);

    };
}


