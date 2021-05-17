//
// Created by user on 02/05/2021.
//

#pragma once

#include <map>
#include <string>

using std::map;
using std::string;

enum Color{ 
    Black, 
    Blue,
    Yellow,
    Red 
};

static map<string, Color> colorEnumMap{
        {"Blue", Color::Blue},
        {"Black", Color::Black},
        {"Red", Color::Red},
        { "Yellow", Color::Yellow }
};

