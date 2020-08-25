//
//  table.cpp
//  tables
//
//  Created by Daniel Shterev on 30.03.20.
//  Copyright © 2020 Daniel Shterev. All rights reserved.
//

#include "table.hpp"

void Table::print()
{
    for (int i = 0 ; i < maxNewContent ; ++i)
    {
        if (fContent[i] == ',')
        {
            std::cout << "|" ;
        }
        else if (fContent[i] == '\n')
        {
            std::cout << std::endl ;
            break ;
        }
        else
        {
            std::cout << fContent[i] ;
        }
    }
}

void Table::setContent(char* content)
{
    fContent = content ;
}

void Table::edit()
{
    char* newContent = new char [maxNewContent] ;
    std::cin.getline(newContent, maxNewContent) ;
    fContent = newContent ;
}

char* Table::getContent()
{
    return fContent ;
}
Table::Table (const char* content)
{
    
    fContent = new char [strlen(content)+1] ;
    strcpy (fContent, content) ;
}

Table::Table (const Table& table) :Table()
{
    if(this != &table)
    {
        copy(table) ;
    }
}

Table::~Table()
{
    delete []fContent ;
}

Table& Table::operator= (const Table& table)
{
    if(this != &table)
    {
        delete [] fContent ;
        copy(table) ;
    }
    return *this ;
}

void Table::copy (const Table& table)
{
    fContent= new char [strlen(table.fContent)+1] ;
    strcpy (fContent, table.fContent) ;
}

double Table::getNum (char* Arg,Table** table)
{
    double number = 0 ;
    if (Arg[0] == 'R' && (Arg[1] >= '0' && Arg[1] <= '9'))
    {
        for (int i = 0 ; i < strlen(Arg-1); ++i)
        {
            if (Arg[i] != 'C' && (Arg[i] != '.' && (Arg[i] < '0' || Arg[i] > 9) ) )
            {
                number = 0 ;
            }
            if (Arg[i] == 'C' && (Arg[i+1] >= '0' && Arg[1] <= '9'))
            {
                number = atof (table[getRow(Arg)][getCol(Arg)].fContent);
            }
        }
    }
    else
    {
        for (int i = strlen (Arg) ; i > 0 ; --i)
        {
            if (Arg[i] != '.' && (Arg[i] < '0' || Arg[i] > '9'))
            {
                number = 0 ;
            }
            else if (Arg[i] >= '0' || Arg[i] <= '9')
            {
                number = atof (Arg) ;
            }
        }
    }
    return number ;
}
    void Table::checkFormula (Table** table)
    {
        if (strncmp(fContent, "=", 1) == 0)
        {
            double calculation = calculateFormula(fContent, table) ;
            std::cout << calculation ;
        }
    }
    
    double Table::calculateFormula(const char* formula, Table** table)
    {
        const char* delimiter = " ";
        char* expr = new char [strlen(formula)+1] ;
        char* formulaBeg = expr ;
        strcpy (expr,formula) ;
        char* firstArg;
        char* secondArg ;
        char* operation ;
        firstArg = strtok(expr, delimiter) ;
        operation = strtok (NULL, delimiter) ;
        secondArg= strtok(NULL, delimiter);
        double firstNum = getNum(firstArg,table) ;
        double secondNum = getNum(secondArg,table) ;
        double result ;
        result= operate (firstNum, secondNum, operation[0]) ;
        return result ;
    }



                



    

