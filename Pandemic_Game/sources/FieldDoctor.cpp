//
// Created by user on 02/05/2021.
//

#include "FieldDoctor.hpp"

namespace pandemic
{

    string FieldDoctor::role(){
        return this->_role;
    }

    Player& FieldDoctor::treat(City city){
        //check if city == _currCity
        if (this->_currCity == city){
            Player::treat(city);
            return *this;
        }

        if(!this->_board.adjacent(this->_currCity, city)){
            throw std::invalid_argument("ERROR! player can't treat a distant city");
        }

        // check if infected
        if (this->_board.getInfectionLvl(city) == 0){
            throw std::invalid_argument("ERROR! can't treat, city is not infected");
        }

        // cured -> set 0, not cured -> set += -1
        if(this->_board.isCured(_board.getCityColor(city)) ){
            _board.setInfectionLvl(city, true);
        }else{
            _board.setInfectionLvl(city, false);
        }

        return *this;
    }
}
