//
// Created by user on 02/05/2021.
//

#include "Medic.hpp"

namespace pandemic
{
    string Medic::role(){
        return this->_role;
    }

    Player& Medic::drive(City city){
        checkDest(city);

        if(!this->_board.adjacent(this->_currCity, city)){
            throw std::invalid_argument("ERROR! cant do 'drive' because destination city and current city are not adjacent");
        }

        this->_currCity = city;

        cureCity(city);

        return *this;
    }

    Player& Medic::fly_direct(City city){
        checkDest(city);

        checkInCards(city);

        eraseCard(city);

        this->_currCity = city;

        cureCity(city);

        return *this;
    }

    Player& Medic::fly_charter(City city){
        checkDest(city);

        checkInCards(this->_currCity);

        eraseCard(this->_currCity);

        this->_currCity = city;

        cureCity(city);

        return *this;
    }

    Player& Medic::fly_shuttle(City city){
        checkDest(city);

        if(!this->_board.isBuilt(this->_currCity)){
            throw std::invalid_argument("can't 'fly_shuttle', current city do not have research station");
        }

        if(!this->_board.isBuilt(city)){
            throw std::invalid_argument("can't 'fly_shuttle', destination city do not have research station");
        }

        this->_currCity = city;

        cureCity(city);

        return *this;

    }

    Player& Medic::treat(City city){
        //check if city == _currCity
        if (this->_currCity != city){
            throw std::invalid_argument("ERROR! player can't treat a distant city");
        }

        // check if infected
        if (this->_board.getInfectionLvl(city) == 0){
            throw std::invalid_argument("ERROR! can't treat, city is not infected");
        }

        //  set 0
        _board.setInfectionLvl(this->_currCity, true);

        return *this;
    }
    void Medic::cureCity(City city) {
        if (this->_board.isCured(_board.getCityColor(city))) {
            _board.setInfectionLvl(this->_currCity, true);
        }
    }

}