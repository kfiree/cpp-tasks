//
// Created by user on 02/05/2021.
//

#include "Dispatcher.hpp"

namespace pandemic
{
    string Dispatcher::role(){
        return this->_role;
    }

    Player& Dispatcher::fly_direct(City city){

        if(!this->_board.isBuilt(this->_currCity)){
            Player::fly_direct(city);
            return *this;
        }

        checkDest(city);

        this->_currCity = city;

        return *this;
    }
}