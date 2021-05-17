//
// Created by user on 02/05/2021.
//

#pragma once
#include <iostream>
#include <string>

#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include <vector>

using std::string;
using std::vector;

namespace pandemic
{
    class Player{
            City _currCity;
            vector<City> _cards;

        public:
            
            Player(Board board, City city);

            vector<City> getCards();

            City getCity();

            Player& take_card(City city);

            string role();

            void discover_cure(Color color);

            Player& drive(City city);

            Player& fly_direct(City city);

            Player& fly_charter(City city);

            Player& fly_shuttle(City city);

            Player& build();

            Player& treat(City city);

    };


}

