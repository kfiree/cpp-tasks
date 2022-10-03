//
// Created by user on 02/05/2021.
//

#include "OperationsExpert.hpp"

namespace pandemic
{
    string OperationsExpert::role(){
        return this->_role;
    }

    Player& OperationsExpert::build(){
        //TODO add checks
        this->_board.build(this->_currCity);
        return *this;
    }
}