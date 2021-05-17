#include "Board.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::istringstream;
using std::string;
using std::ifstream;
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

    bool Board::isBuilt(City city){
        return this->_citiesMap[city].reaserchStation;
    }

    bool Board::isCured(Color color)
    {
        return this->cures[color];
    }

    // int Board
    bool Board::is_clean()
    {
        return true;
    }


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
        return out;
    }
}
