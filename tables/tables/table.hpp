//
//  table.hpp
//  tables
//
//  Created by Daniel Shterev on 30.03.20.
//  Copyright © 2020 Daniel Shterev. All rights reserved.
//

#ifndef table_hpp
#define table_hpp

#include "formula.hpp"
#include <iostream>
#include <string.h>

const int maxNewContent = 100 ;
class Table
{
public:
    void edit() ;
    void print() ;
    void setContent(char* content) ;
private:
    char* fContent;
public:
    Table (const char* content = "") ;
    Table (const Table& table) ;
    ~Table() ;
    Table& operator= (const Table& table) ;
    double getNum (char* Arg,Table** table) ;
    char* getContent() ;
private:
    double calculateFormula(const char* formula, Table** table) ;
    void checkFormula (Table** table) ;
    void copy(const Table& table) ;
    
};

#endif /* table_hpp */
