#include "doctest.h"
#include "sources/Board.hpp"
#include "sources/City.hpp"
#include "sources/Color.hpp"
#include "sources/Player.hpp"

#include "sources/Researcher.hpp"
#include "sources/Scientist.hpp"
#include "sources/FieldDoctor.hpp"
#include "sources/GeneSplicer.hpp"
#include "sources/OperationsExpert.hpp"
#include "sources/Dispatcher.hpp"
#include "sources/Medic.hpp"
#include "sources/Virologist.hpp"

using namespace pandemic;

#include <vector>
#include <iostream>
#include <stdexcept>
#include <list>
using namespace std;

Board board;

City getRndCity(){
    return static_cast<City>(rand() % Washington);
}

Color getRndColor(){
    return static_cast<Color>(rand() % Red);
}

 Player playersList[8]={
     Researcher(board , getRndCity()),
     Scientist(board , getRndCity(), 1),
     FieldDoctor(board , getRndCity()),
     GeneSplicer(board , getRndCity()),
     OperationsExpert(board , getRndCity()),
     Dispatcher(board , getRndCity()),
     Medic(board , getRndCity()),
     Virologist(board , getRndCity())

};


TEST_CASE("check operations not throw "){ // total 56 tests

    for(Player p: playersList){ // 7 test * 8 players
        CHECK_NOTHROW(p.drive(getRndCity()));
        CHECK_NOTHROW(p.fly_direct(getRndCity()));
        CHECK_NOTHROW(p.fly_shuttle(getRndCity()));
        CHECK_NOTHROW(p.fly_charter(getRndCity()));
        CHECK_NOTHROW(p.build());
        CHECK_NOTHROW(p.discover_cure(getRndColor()));
        CHECK_NOTHROW(p.treat(getRndCity()));
    }
}

TEST_CASE("check transportaion"){ // total 32 tests
    for(Player p: playersList){ // 4 test * 8 players
        City city = getRndCity();
        p.drive(city);
        CHECK(p.drive(city).getCity() == city);

        city = getRndCity();
        CHECK(p.fly_direct(city).getCity() == city);

        city = getRndCity();
        CHECK(p.fly_shuttle(city).getCity() == city);

        city = getRndCity();
        CHECK(p.fly_charter(city).getCity() == city);

    }
}

TEST_CASE(" check player methods => build, discover_cure, treat"){
    for(Player p: playersList){ // 4 test * 8 players
        // check build reaserch station
        p.build();
        CHECK(board.isBuilt(p.getCity()));

        // check discover cure card's cost
        int prevCardsSize = p.getCards().size();
        Color color = getRndColor();
        p.discover_cure(color);
        int cardsSize = p.getCards().size();
        if(board.isCured(color)){
            prevCardsSize-=5;
            CHECK(cardsSize == prevCardsSize);
            p.discover_cure(color);
        }
        CHECK(cardsSize == prevCardsSize);

        // check treat
        City city = getRndCity();
        // if(board.)
        p.treat(city);

    }
}