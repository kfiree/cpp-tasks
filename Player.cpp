//
// Created by user on 02/05/2021.
//

#include "Player.hpp"


using namespace pandemic;

namespace pandemic
{

    Player::Player(Board board, City city){
        this->_currCity = city;
    }

    City Player::getCity(){
        return this->_currCity;
    }
    

    Player& Player::take_card(City city){
        return *this;
    }

    string Player::role(){ 
        return "";
    }

    vector<City> Player::getCards(){
        return this->_cards;
    }

    void Player::discover_cure(Color color){ 

    }

    Player& Player::drive(City city){
        return *this;
    }

    Player& Player::fly_direct(City city){
        return *this;
    }

    Player& Player::fly_charter(City city){
        return *this;
    }

    Player& Player::fly_shuttle(City city){
        return *this;
    }

    Player& Player::build(){ 
        return *this;
    }

    Player& Player::treat(City city){
        return *this;
    }
}