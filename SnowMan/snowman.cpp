#include <iostream>
#include <cmath>
#include <sstream>
#include "snowman.hpp"
#include <array>


struct worngInput : std::exception { 
    const char* what() const noexcept override
    { 
        return "invalid input."; 
    } 
}; 

std::array<std::string, 4> hatsTop= {"     ", " ___ ","  _  ", " ___ "},
     hatsBot={"_===_", ".....", " /_\\ ", "(_*_)"},
     eyes = {".", "o", "O", "-"},
     noses = {",", ".", "_"," "},
     lArmsTop = {" ", "\\", " ",  " "},
     lArmsBot = {"<", " ", "/",  " "},
     rArmsTop = {" ", "/", " ",  " "},
     rArmsBot = {">", " ", "\\",  " "},
     torsos = {" : ", "] [", "> <", "   "},
     bases = {" : ", "\" \"", "___",  "   "};

const int ten = 10, H = 7, N = 6, L= 5, R= 4, X= 3, Y = 2, T = 1, B =  0;
const int botBound = 11111111, topBound = 44444444;

//return the nth digit -1 if in bound
int get(int snowCode, int digit)
{
    int n = int (pow(ten, digit));
    int codeNum = ((snowCode/n)%ten)-1;

    // check if 1 <= digit <= 4 
    if(codeNum >3 || codeNum < 0){
        throw worngInput();
    }
    return codeNum;
}

void checkLen(int snowCode)
{
    //check for legal input
    if(snowCode < botBound || snowCode > topBound)
    {
        throw worngInput();
    }
    
}

namespace ariel
{
    std::string snowman(int snowCode)
    {
        // check if input in bound
        checkLen(snowCode);
        
                /* snowman format => HNLRXYTB 
                        HHHHH 
                        HHHHH
                       X(LNR)Y
                       X(TTT)Y
                        (BBB)
                */

        // build snowman string

        //get indexes for parts (super ugly because i had to adjust it to your tidy format - no multiple delcaraiton in a single line)
        int h = 0;
        int n = 0;
        int l = 0;
        int r = 0;
        int x = 0;
        int y = 0;
        int t = 0;
        int b = 0;
        h = get(snowCode, H);
        n = get(snowCode, N);
        l = get(snowCode, L);
        r = get(snowCode, R);
        x = get(snowCode, X);
        y = get(snowCode, Y);
        t = get(snowCode, T);
        b = get(snowCode, B);

        std::ostringstream draw;
        draw << " " << hatsTop.at(h) << std::endl
             << " " << hatsBot.at(h) << std::endl
             << lArmsTop.at(x) << "(" << eyes.at(l) << noses.at(n) << eyes.at(r) << ")" << rArmsTop.at(y) << std::endl
             << lArmsBot.at(x) << "(" << torsos.at(t) << ")" << rArmsBot.at(y) << std::endl
             << " (" << bases.at(b) << ") ";

        return draw.str();
    }
}
