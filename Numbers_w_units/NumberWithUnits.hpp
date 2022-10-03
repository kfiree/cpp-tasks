#pragma once


#include <string>
#include <iostream>
#include <fstream>
#include <map>

#define EPS 0.001

using namespace std;
//  day = 24 hours + 1/7 week
// = 24 (60 min) + 1/7(1/4 month)
// = 24( 60(60 sec)+ 1/7(1/4(1/12 year)
typedef struct{
    string incUnit;
    double inc = 0;
    string decUnit;
    double dec = 0;
}Ratio;

typedef map<string, Ratio> ratioMap;  //map<unit,ratio>

namespace ariel{
    // increase and decrease unitsMap
    static ratioMap _ratioMap = ratioMap();

    class NumberWithUnits
    {
    private:
        map<string, map<string, double>> _unitsMap;
        double _val;
        string _unit;

        double getRelation(string const &otherUnit) const;
        double getRelationIncOrDec(string const &otherUnit, bool converUp) const;

    public:
        NumberWithUnits(double num, string const &unit);
        ~NumberWithUnits(){}

        static void read_units(ifstream& file);

        // unary operators
        NumberWithUnits operator-() const;
        NumberWithUnits operator+() const;


        // arithmetics operators
        friend NumberWithUnits operator*(const double mult, const NumberWithUnits& other);
        NumberWithUnits operator*(const double mult) const;
        NumberWithUnits operator+(const NumberWithUnits& other) const;
        NumberWithUnits operator+=(const NumberWithUnits& other);
        NumberWithUnits operator-(const NumberWithUnits& other) const;
        NumberWithUnits operator-=(const NumberWithUnits& other) ;

        // prefix ( operator++() ) and postfix ( operator++(int) )
        NumberWithUnits& operator++();
        NumberWithUnits operator++(int);
        NumberWithUnits& operator--();
        NumberWithUnits operator--(int);


        // compering operators
        bool operator<(const NumberWithUnits& other) const;
        bool operator<=(const NumberWithUnits& other) const;
        bool operator>(const NumberWithUnits& other) const;
        bool operator>=(const NumberWithUnits& other) const;
        bool operator==(const NumberWithUnits& other) const;
        bool operator!=(const NumberWithUnits& other) const;

        // ostream operators
        friend ostream& operator<< (ostream& out, const NumberWithUnits& num);
        friend istream& operator>> (istream& input, NumberWithUnits& num);
    };

}

