#include "doctest.h"
#include "snowman.hpp"
using namespace ariel;
#include <array>
#include <string>
#include <algorithm>
using namespace std;

TEST_CASE("good input") {
    CHECK_NOTHROW(snowman(12312323));
    CHECK_NOTHROW(snowman(11111111));
    CHECK_NOTHROW(snowman(22222222));
    CHECK_NOTHROW(snowman(33333333));
    CHECK_NOTHROW(snowman(10101010));
    CHECK_NOTHROW(snowman(01010101));
    CHECK_NOTHROW(snowman(33333333));
}


// === bad input ===

TEST_CASE("Bad input - one digit out of bound") {
    CHECK_THROWS(snowman(11111115));
    CHECK_THROWS(snowman(11111151));
    CHECK_THROWS(snowman(11111511));
    CHECK_THROWS(snowman(11151111));
    CHECK_THROWS(snowman(11511111));
    CHECK_THROWS(snowman(15111111));
    CHECK_THROWS(snowman(51111111));
}

TEST_CASE("Bad input- not enough digits") {
    CHECK_THROWS(snowman(0000000));
    CHECK_THROWS(snowman(000000));
    CHECK_THROWS(snowman(00000));
    CHECK_THROWS(snowman(0000));
    CHECK_THROWS(snowman(000));
    CHECK_THROWS(snowman(00));
    CHECK_THROWS(snowman(0));
}

TEST_CASE("Bad input- two much digits") {
   CHECK_THROWS(snowman(0000000000));
    
}

