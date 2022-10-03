//reaserchStation
// Created by user on 02/05/2021.
//

#pragma once

#include <stdio.h>
#include "Player.hpp"
#include "Board.hpp"
#include "City.hpp"


namespace pandemic
{
    class Dispatcher : public Player
    {
        private:
            string const _role = "Dispatcher";//TODO add to constructor?
        public:
            Dispatcher(Board& board, City city):Player(board, city){}

            string role();

            Player& fly_direct(City city);
    };
}


