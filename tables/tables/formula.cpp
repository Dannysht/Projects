//
//  formula.cpp
//  tables
//
//  Created by Daniel Shterev on 30.03.20.
//  Copyright © 2020 Daniel Shterev. All rights reserved.
//

#include "formula.hpp"

double operate (double firstNum, double secondNum, char operation)
{
    switch (operation)
    {
        case '+':
            return firstNum + secondNum ;
        case '-':
            return firstNum - secondNum ;
        case '*':
            return firstNum * secondNum ;
        case '/':
            if (secondNum == 0)
            {
                std::cout << "ERROR \n" ;
                return 0 ;
            }
            else
            {
            return firstNum / secondNum ;
            }
        default:
            std::cout << "Invalid action \n" ;
            return 0 ;
    }
}

int getCol (char* Arg)
{
    int col = 0 ;
    int currentExpon = 0 ;
    for (int i = strlen(Arg); i > 0 ; --i )
    {
        if (Arg[i]>= '0' && Arg[i+1] <= '9')
        {
            ++currentExpon ;
        }
        if (Arg[i] == 'C')
        {
            int j = 0 ;
            while (currentExpon > 0)
            {
                col += pow(10,j)* (int)Arg[i+currentExpon] ;
                ++j ;
                --currentExpon ;
            }
        }
    }
    return col ;
}

int getRow (char* Arg)
{
    int row = 0 ;
    int currentExpon = 0 ;
    for (int i = strlen(Arg); i > 0 ; --i )
    {
        if (Arg[i]>= '0' && Arg[i+1] <= '9')
        {
            ++currentExpon ;
        }
        if (Arg[i] == 'R')
        {
            int j = 0 ;
            while (currentExpon > 0)
            {
                row += pow(10,j) * (int)(Arg[i+currentExpon]) ;
                ++j ;
                --currentExpon ;
            }
        }
    }
    return row ;
}


