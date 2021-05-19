#include "Board.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>

using std::istringstream;
using std::string;
using std::ifstream;
using std::find;

namespace pandemic
{
    Board::Board(){
        readCountries();
        this->cures = {false};
    }

    void Board::readCountries(){
        ifstream file("cities_map.txt");
        string row;
        string word;
        string cityStr;
        string colorStr;
        string neighbour;

        while (std::getline(file, row)) {
            istringstream iss(row);

            cityInfo cityInfo;
            iss >> cityStr;

            iss >> colorStr;
            cityInfo.color = colorEnumMap.at(colorStr);
            while(iss >> neighbour) {
                cityInfo.neighbours.push_back(cityEnumMap.at(neighbour));
            }
            cityInfo.infectionLvl = 0;
            cityInfo.reaserchStation=false;
            this->_citiesMap[cityEnumMap.at(cityStr)] = cityInfo;
        }
    }

    /*     |/\/\/\ GETTERS /\/\/|    */


    bool Board::isBuilt(City city){
        return this->_citiesMap.at(city).reaserchStation;
    }

    bool Board::isCured(Color color)
    {
        return cures.at(color);
    }

    bool Board::adjacent(City city1, City city2){ 
        vector <City> neighbours = this->_citiesMap[city1].neighbours;
        bool adj = false;
        if(find(neighbours.begin(), neighbours.end(), city2) != neighbours.end()) {
           adj =  true;
        }

        return adj;
    }

    bool Board::is_clean()
    {
        citiesMap::iterator itr;
        bool clean = true;
        for(itr = _citiesMap.begin(); itr!= _citiesMap.end(); itr++){
            if(itr->second.infectionLvl!= 0){
                clean = false;
            }
        }
        return clean;
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

    void Board::setInfectionLvl(City city, bool cured){
        if(cured){
            this->_citiesMap.at(city).infectionLvl = 0;
        }else{
            this->_citiesMap.at(city).infectionLvl-=1;
        }
    }

    void Board::cure(Color color){ 
        this->cures.at(color) = true;
    }

    void Board::remove_cures() {
        for(bool & cure : this->cures){
            cure = false;
        }
    }

    void Board::build(City city){ 
        this->_citiesMap[city].reaserchStation = true;
    }


    /*     |/\/\/\ OPERATORS OVERLOADING /\/\/|    */

    int & Board::operator[](City city){
        try{
            return this->_citiesMap.at(city).infectionLvl;
        }catch(const std::out_of_range& e) {
            _citiesMap[city].infectionLvl = 0;
            return _citiesMap.at(city).infectionLvl;
//            throw ("city doesn't exist");
        }

    }

    ostream& operator<<(ostream& out, const Board& num)
    {
        return out<<""<<std::endl;
    }
}
