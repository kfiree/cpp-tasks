#pragma once
#include "Color.hpp"
#include "City.hpp"
#include "Board.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>


using std::string;
using std::vector;
using std::set;
using std::map;


namespace pandemic
{
    const int fiveCards = 5;

    class Player{

        protected:
            Board& _board;
            City _currCity;
            set<City> _cards;
            std::array<set<City>,colorSize> _cardsByColor;

        public:
            
            /*     |/\/\/\ CONSTRUCTOR /\/\/|    */

            Player(Board& board, City city):_board(board), _currCity(city){}

            /*     |/\/\/\ GETTERS /\/\/|    */

             virtual set<City> getCards();

            virtual City getCity();

            virtual string role() = 0;

            Player& discover_cure(Color color);

            /*     |/\/\/\ OPERATIONS /\/\/|    */

            Player& take_card(City city);

            virtual Player& build();

            virtual Player& treat(City city);

            void remove_cards();
            

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

