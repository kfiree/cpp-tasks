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
            Board _board;
            City _currCity;
            vector<City> _cards;

        public:
            
            /*     |/\/\/\ CONSTRUCTOR /\/\/|    */

            Player(Board board, City city);

            /*     |/\/\/\ GETTERS /\/\/|    */

            virtual vector<City> getCards();

            virtual City getCity();

            virtual string role();

            void discover_cure(Color color);

            /*     |/\/\/\ SETTERS /\/\/|    */

            Player& take_card(City city);

            virtual Player& build();

            virtual Player& treat(City city);
            

            /*     |/\/\/\ TRANSPORT /\/\/|    */

            virtual Player& drive(City city);

            virtual Player& fly_direct(City city);

            virtual Player& fly_charter(City city);

            virtual Player& fly_shuttle(City city);

    };


}

