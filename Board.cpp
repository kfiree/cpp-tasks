#include "Board.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using std::istringstream;
using std::string;
using std::ifstream;
using std::find;

namespace pandemic
{
    Board::Board(){
        readCountries();
    }

    void Board::readCountries(){
        ifstream file("../cities_map.txt");
        string row;
        string word, cityStr, colorStr, neighbour;

        while (std::getline(file, row)) {
            istringstream iss(row);

            cityInfo cityInfo;
            iss >> cityStr;

            iss >> colorStr;
            cityInfo.color = colorEnumMap.at(colorStr);
            while(iss >> word) {
                iss >> neighbour;
                cityInfo.neighbours.push_back(cityEnumMap.at(neighbour));
            }
            cityInfo.infectionLvl = 0;
            this->_citiesMap[cityEnumMap.at(cityStr)] = cityInfo;
        }
    }

    /*     |/\/\/\ GETTERS /\/\/|    */

    // int Board
    bool Board::is_clean()
    {
        citiesMap::iterator itr;

        for(itr = _citiesMap.begin(); itr!= _citiesMap.end(); itr++){
            if(itr->second.infectionLvl!= 0){
                return false;
            }
            return true;
        }

    }

    bool Board::isBuilt(City city){
        return this->_citiesMap[city].reaserchStation;
    }

    bool Board::isCured(Color color)
    {
        return this->cures[color];
    }

    bool Board::adjacent(City city){ 
        vector <City> neighbours = this->_citiesMap[city].neighbours;
        if(find(neighbours.begin(), neighbours.end(), city) != neighbours.end()) {
           return true;
        }

        return false;
    }

    int Board::getInfectionLvl(City city){ 
        return this->_citiesMap[city].infectionLvl;
    }

    Color Board::getColor(City city){
        return this->_citiesMap[city].color;
    }

    Color Board::getCityColor(City city){
        return this->_citiesMap[city].color;
    }

    /*     |/\/\/\ SETTERS /\/\/|    */

    void Board::setInfectionLvl(City city, int lvl){
        this->_citiesMap[city].infectionLvl += lvl;
    }


    void Board::cure(Color color){ 
        this->cures[color] = true;
    }

    void Board::unCure(){ 
        for(int i = 0; i<4; i++){
            this->cures[i] = false;
        }
    }

    void Board::build(City city){ 
        this->_citiesMap[city].reaserchStation = true;
    }

    void Board::unBuild(){ 
        citiesMap::iterator itr;

        for(itr = _citiesMap.begin(); itr!= _citiesMap.end(); itr++){
            itr->second.reaserchStation = false;
        }
    }

    /*     |/\/\/\ OPERATORS OVERLOADING /\/\/|    */

    int & Board::operator[](City city){
        try{
            return _citiesMap.at(city).infectionLvl;
        }catch(const std::out_of_range& e) {
            _citiesMap[city].infectionLvl = 0;
            return _citiesMap.at(city).infectionLvl;
//            throw ("city dosen't exist");
        }

    }

    ostream& operator<<(ostream& out, const Board& num)
    {
        return out<<""<<std::endl;
    }
}
