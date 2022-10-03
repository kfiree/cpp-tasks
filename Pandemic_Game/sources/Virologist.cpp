//
// Created by user on 02/05/2021.
//

#include "Virologist.hpp"

namespace pandemic
{
    string Virologist::role(){
        return this->_role;
    }
    Player& Virologist::treat(City city){
        //check if city == _currCity
        if (this->_currCity == city){
            Player::treat(city);
            return *this;
        }

        checkInCards(city);

        // check if infected
        if (this->_board.getInfectionLvl(city) == 0){
            throw std::invalid_argument("ERROR! can't treat, city is not infected");
        }

        eraseCard(city);

        // cured -> set 0, not cured -> set += -1
        if(this->_board.isCured(_board.getCityColor(city)) ){
            _board.setInfectionLvl(city, true);
        }else{
            _board.setInfectionLvl(city, false);
        }

        return *this;
    }
}