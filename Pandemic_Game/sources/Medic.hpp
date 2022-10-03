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
    class Medic : public Player
    {
        private:
            const string _role = "Medic";
        public:
        Medic(Board& board, City city):Player(board, city){}

        string role();

        Player& drive(City city);

        Player& fly_direct(City city);

        Player& fly_charter(City city);

        Player& fly_shuttle(City city);

        Player& treat(City city);

        void cureCity(City city);

    };
}


