//
// Created by user on 02/05/2021.
//

#include "Researcher.hpp"

namespace pandemic
{
    string Researcher::role(){
        return this->_role;
    }

    Player& Researcher::discover_cure(Color color){
        //check if city is cured already
        if(_board.isCured(color)){
            return *this;
        }

        // check if player have 5 cards with city's color
        set<City> coloredCities = this->_cardsByColor.at(color);
        if(coloredCities.size() < fiveCards){
            throw std::invalid_argument("Error! can't cure because player dont have enough cards with city's color");
        }

        // delete five cards in order to cure
        set<City>::iterator itr = this->_cards.begin();
        set<City> toRemove;
        for(int i = 0; i< fiveCards; i++){
            toRemove.insert(*itr);
            itr++;
        }
        for(City city: toRemove){
            eraseCard(city);
        }

        // mark color as cure
        this->_board.cure(color);

        return *this;
    }
}