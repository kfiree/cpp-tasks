//
// Created by user on 02/05/2021.
//

#include "Scientist.hpp"

namespace pandemic
{
    string Scientist::role(){
        return this->_role;
    }

     Player& Scientist::discover_cure(Color color){

        //check if city is cured already
        if(_board.isCured(color)){
            return *this;
        }

        // check if research station is built
        if(!_board.isBuilt(this->_currCity)){
            throw std::invalid_argument("Error! can't cure a city that dont have research station");
        }

        // check if player have 5 cards with city's color
        set<City> coloredCities = this->_cardsByColor.at(color);
        if(coloredCities.size() < this->n){
            throw std::invalid_argument("Error! can't cure because player dont have enough cards with city's color");
        }

        // delete five cards in order to cure
        set<City>::iterator itr = coloredCities.begin();
        for(int i = 0; i< this->n; i++){
            eraseCard(*itr);
            itr++;
        }

        // mark color as cure
        this->_board.cure(color);

         return *this;
    }
}