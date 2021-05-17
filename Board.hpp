 //
// Created by user on 02/05/2021.
//

#pragma once

#include "City.hpp"
#include "Color.hpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::ostream;
using std::string;
using std::map;
using std::vector;

struct cityInfo{
    int infectionLvl;
    vector<City> neighbours;
    Color color;
    bool reaserchStation;
};

typedef map<City, cityInfo> citiesMap;


namespace pandemic{

    class Board
    {
        private:
            citiesMap _citiesMap;

            void readCountries();

            bool cures[4];

        public:

            Board();

            /*     |/\/\/\ GETTERS /\/\/|    */

            bool is_clean();

            bool isBuilt(City city);

            bool isCured(Color color);

            bool adjacent(City city);

            int getInfectionLvl(City city);

            Color getColor(City city);

            Color getCityColor(City city);
            
            /*     |/\/\/\ SETTERS /\/\/|    */

            void setInfectionLvl(City city, int lvl);
            
            void cure(Color color);

            void unCure();

            void build(City city);

            void unBuild();


            /*     |/\/\/\ OPERATORS OVERLOADING /\/\/|    */

            int & operator[](City city);

            friend ostream& operator<< (ostream& out, const Board& num);

    };
}