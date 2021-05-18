//
// Created by user on 02/05/2021.
//

#include "Player.hpp"
#include <stdio.h>
#include <algorithm>
#include <vector>

using std::invalid_argument;
using namespace pandemic;

namespace pandemic
{
    /*     |/\/\/\ CONSTRUCTOR /\/\/|    */

    // Player::Player(Board board, City city){
    //     this->_board = board;
    //     this->_currCity = city;
    // }

    /*     |/\/\/\ GETTERS /\/\/|    */


     set<City> Player::getCards(){
         return this->_cards;
     }

    City Player::getCity(){
        return this->_currCity;
    }

    /*     |/\/\/\ OPERATIONS /\/\/|    */

    Player& Player::take_card(City city){
        this->_cards.insert(city);
        this->_cardsByColor[_board.getColor(city)].insert(city);
        return *this;
    }

    void Player::discover_cure(Color color){
        //check if city is cured already
        if(_board.isCured(color)){
            return;
        }

        // check if research station is built
        if(!_board.isBuilt(this->_currCity)){
            throw invalid_argument("Error! can't cure a city that dont have research station");
        }

        // check if player have 5 cards with city's color
        set<City> coloredCities = this->_cardsByColor[color];
        if(coloredCities.size() < fiveCards){
            throw invalid_argument("Error! can't cure because player dont have enough cards with city's color");
        }

        // delete five cards in order to cure
        set<City>::iterator itr = coloredCities.begin();
        for(int i = 0; i< fiveCards; i++){
            eraseCard(*itr);
            itr++;
        }

        // mark color as cure
        this->_board.cure(color);
    }

    /*     |/\/\/\ TRANSPORTATION /\/\/|    */

    Player& Player::drive(City city){

        checkDest(city);
        
        if(!this->_board.adjacent(this->_currCity, city)){
            throw std::invalid_argument("ERROR! cant do 'drive' because destination city and current city are not adjacent");
        }

        this->_currCity = city;
        
        return *this;
    }

    Player& Player::fly_direct(City city){

        checkDest(city);

        checkInCards(city);

        eraseCard(city);

        this->_currCity = city;

        return *this;
    }

    Player& Player::fly_charter(City city){
        checkDest(city);

        checkInCards(this->_currCity);

        eraseCard(this->_currCity);

        this->_currCity = city;
    }

    Player& Player::fly_shuttle(City city){
        checkDest(city);

        if(!this->_board.isBuilt(this->_currCity)){
            throw std::invalid_argument("can't 'fly_shuttle', current city do not have research station");
        }

        if(!this->_board.isBuilt(city)){
            throw std::invalid_argument("can't 'fly_shuttle', destination city do not have research station");
        }
        
        this->_currCity = city;

        return *this;
    }

    /*     |/\/\/\ OPERATIONS /\/\/|    */

    Player& Player::build(){
        //check if already built
        if(this->_board.isBuilt(this->_currCity)){
            return *this;
        }

        // check if player have card
        checkInCards(this->_currCity);

        // give up card in order to build
        eraseCard(this->_currCity);

        //build
        this->_board.build(this->_currCity);

        return *this;
    }

    Player& Player::treat(City city){
        //check if city == _currCity
        if (this->_currCity != city){
            throw std::invalid_argument("ERROR! player can't treat a distant city");
        }

        // check if infected
        if (this->_board.getInfectionLvl(city) == 0){
            throw std::invalid_argument("ERROR! can't treat, city is not infected");
        }

        // cured -> set 0, not cured -> set += -1
        if(this->_board.isCured(_board.getCityColor(city)) ){
            _board.setInfectionLvl(this->_currCity, true);
        }else{
            _board.setInfectionLvl(this->_currCity, false);
        }

        return *this;
    }

    void Player::checkDest(City city){
        if(city == getCity()){
            throw std::invalid_argument("ERROR! cant transport because player is already in destination city");
        }
    }

    void Player::checkInCards(City city){
        if(this->_cards.find(city) == this->_cards.end()){
            throw invalid_argument("ERROR! player do not possess the city's card needed for this operation.");
        }
    }

    void Player::eraseCard(City city){
        this->_cardsByColor[_board.getCityColor(city)].erase(city);
        this->_cards.erase(city);
    }

}