#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <iterator>
#include <algorithm>
#include <string>
#include <algorithm>
#include <vector>


using namespace ariel;
using namespace std;


namespace ariel
{
    NumberWithUnits::NumberWithUnits(double num, string const &unit){

        try{
            _ratioMap.at(unit);
        }catch(const std::out_of_range& e) {
            throw ("Illegal operation. cant use unknown unit");
        }

        this->_val=num;
        this->_unit=unit;
    }

    void updateMap(double firstVal, string const &firstUnit, double secondVal, string const &secondUnit){
        // set left unit's ratio
        if(_ratioMap.find(firstUnit) == _ratioMap.end()){
            _ratioMap[firstUnit] = Ratio{"", 0, secondUnit, (secondVal/firstVal)};
        } else {
            _ratioMap[firstUnit] = Ratio{_ratioMap[firstUnit].incUnit, _ratioMap[firstUnit].inc, secondUnit, (secondVal/firstVal)};
        }

        // set right unit's ratio
        if(_ratioMap.find(secondUnit) == _ratioMap.end()){
            _ratioMap[secondUnit] = Ratio{ firstUnit, (firstVal/secondVal), "", 0};
        } else {
            _ratioMap[secondUnit] = Ratio{ firstUnit, (firstVal/secondVal), _ratioMap[secondUnit].decUnit, _ratioMap[secondUnit].dec};
        }
    }

    void setDupUnit(double dupVal, string dupUnit, double otherVal, string const &otherUnit){
        Ratio r = _ratioMap[dupUnit];

        while(!r.incUnit.empty()){
            dupVal *= _ratioMap[dupUnit].inc;
            dupUnit = _ratioMap[dupUnit].incUnit;
            r = _ratioMap[dupUnit];
        }
        updateMap(otherVal, otherUnit, dupVal, dupUnit);
    }


    void ariel::NumberWithUnits::read_units(ifstream& file){

        string word, leftUnit, rightUnit, equal;
        double leftVal{}, rightVal{};

        while (file >> leftVal >> leftUnit >> equal >> rightVal>> rightUnit){

            if(_ratioMap.find(leftUnit) != _ratioMap.end() && !_ratioMap[leftUnit].decUnit.empty()){
                setDupUnit(leftVal, leftUnit, rightVal, rightUnit);
            }else if(_ratioMap.find(rightUnit) != _ratioMap.end() && !_ratioMap[rightUnit].incUnit.empty()){
                setDupUnit( rightVal, rightUnit, leftVal, leftUnit);
            }else{
                updateMap(leftVal, leftUnit, rightVal, rightUnit);
            }

        }
        ratioMap::iterator ptr;
        int j = 0;
        for (ptr = _ratioMap.begin(); ptr != _ratioMap.end(); ptr++) {
            cout << ++j<<") " << ptr->first << " =: "<< ptr->second.inc << "*"<< ptr->second.incUnit << "  ||  " << ptr->second.dec << "*"<< ptr->second.decUnit<<endl;
        }
    }




    /**
         Incompatible type => 0
         compatible   else => relations
    **/
    double NumberWithUnits::getRelation(string const &otherUnit) const {

        if(otherUnit == this->_unit){
            return 1;
        }

        // start recursive call
        double ratio = getRelationIncOrDec(otherUnit, true) + getRelationIncOrDec(otherUnit, false);

        // return conversation ratio if found
        if(ratio!=0.0){
            return ratio;
        }

        // incompatible type error
        throw invalid_argument("Units do not match - [" + otherUnit + "] cannot be converted to [" + _unit + "]");

    }

    double NumberWithUnits::getRelationIncOrDec(string const &otherUnit, bool converUp) const {
        Ratio r = _ratioMap.at(otherUnit);

        string unit = converUp? r.incUnit : r.decUnit;
        double val = converUp? r.inc : r.dec;

        // stop condition 1 => unit found
        if(unit == this->_unit){
            return val;
        }

        // stop condition 2 => unit not found
        if(unit.empty()){
            return 0;
        }

        return  val * getRelationIncOrDec(unit, converUp);
    }

    /**
         __________________________________
        |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\|
        |/\/\/\ operator overloading \/\/\/|
        |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\|
        -----------------------------------
    **/

    //       ==== UNARY OPERATORS ====

    NumberWithUnits NumberWithUnits::operator-() const{
        return NumberWithUnits(this->_val*-1, this->_unit);
    }

    NumberWithUnits NumberWithUnits::operator+() const{
        return NumberWithUnits(this->_val, this->_unit);
    }

    //     ==== ARITHMETICS OPERATORS ====
    NumberWithUnits NumberWithUnits::operator*(const double mult) const{
        return NumberWithUnits(_val*mult, _unit);
    }

    NumberWithUnits operator*(double mult, const NumberWithUnits& other){
        return other*mult;
    }

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& other) const{
        double relation = getRelation(other._unit);
        return NumberWithUnits(this->_val+(other._val*relation), this->_unit);
    }

    NumberWithUnits NumberWithUnits::operator+=(const NumberWithUnits& other){
        double relation = getRelation(other._unit);
        this->_val+=(other._val*relation);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& other) const{
        double relation = getRelation(other._unit);

        return NumberWithUnits(this->_val-(other._val*relation), this->_unit);
    }

    NumberWithUnits NumberWithUnits::operator-=(const NumberWithUnits& other){
        double relation = getRelation(other._unit);
        this->_val-=(other._val*relation);
        return *this;
    }

    NumberWithUnits& NumberWithUnits::operator++(){
        ++_val;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int){
        NumberWithUnits temp = *this;
        ++*this;
        return temp;
    }


    NumberWithUnits NumberWithUnits::operator--(int){
        NumberWithUnits temp = *this;
        --*this;
        return temp;
    }

    NumberWithUnits& NumberWithUnits::operator--(){
        --_val;
        return *this;
    }


    // compering operators
    bool NumberWithUnits::operator==(const NumberWithUnits& other) const{
        double diff = this->_val - other._val*getRelation(other._unit);
        return  diff < EPS && -diff < EPS;
    }

    bool NumberWithUnits::operator<(const NumberWithUnits& other) const{
        return this->_val + EPS < other._val*getRelation(other._unit);
    }

    bool NumberWithUnits::operator>(const NumberWithUnits& other) const{
        return this->_val > EPS+other._val*getRelation(other._unit);
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits& other) const{
        double diff = this->_val - other._val*getRelation(other._unit);
        return (diff < EPS && -diff < EPS) || this->_val + EPS < other._val*getRelation(other._unit);
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits& other) const{
        double diff = this->_val - other._val*getRelation(other._unit);
        return (diff < EPS && -diff < EPS) || this->_val > EPS+other._val*getRelation(other._unit);
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits& other) const{
        double diff = this->_val - other._val*getRelation(other._unit);
        return  !(diff < EPS && -diff < EPS);
    }


    // ostream operators
    ostream& operator<< (ostream& out, const NumberWithUnits& num){
        out << num._val << "[" << num._unit << "]";
        return out;
    }


    istream& operator>> (istream& input, NumberWithUnits& num) {

        double val{};
        string unit;
        char garbageStr{};

        input >> val >> garbageStr >> unit;

        if(unit.find(']')<unit.length()){
            unit = unit.substr(0,unit.find(']'));
        }else{
            input >> garbageStr;
        }

        try{
            _ratioMap.at(unit);
        }catch(const std::out_of_range& e) {
            throw ("Illegal operation. cant use unknown unit");
        }

        num._val = val;
        num._unit = unit;

        return input;
    }
}

