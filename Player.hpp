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
#include <set>
#include <map>


using std::string;
using std::vector;
using std::set;
using std::map;


namespace pandemic
{
    const int colorSize = 4;
    const int fiveCards = 5;

    class Player{
            Board _board;
            City _currCity;
            set<City> _cards;
            set<City> _cardsByColor[colorSize];
        

        public:
            
            /*     |/\/\/\ CONSTRUCTOR /\/\/|    */

            Player(Board board, City city):_board(board), _currCity(city){}

            /*     |/\/\/\ GETTERS /\/\/|    */

             virtual set<City> getCards();

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

        /*     |/\/\/\ check legality /\/\/|    */

            void checkDest(City city);

            void checkInCards(City city);

            void eraseCard(City city);

    };


}

