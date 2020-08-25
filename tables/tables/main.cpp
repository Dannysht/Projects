//
//  main.cpp
//  tables
//
//  Created by Daniel Shterev on 30.03.20.
//  Copyright © 2020 Daniel Shterev. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

#include "table.hpp"

const int maxRows = 100 ;
int main()
{
    int rows = 0, cols = 1 ;
    std::ifstream fileTable ("table.txt") ;
    char* line = new char [maxNewContent] ;
    char contentLine [maxRows][maxNewContent] ;
    int maxCols = 1 ;
    while(fileTable.getline(line,maxNewContent))
    {
        for (int i = 0 ; i < strlen(line) + 1 ; ++i)
        {
            contentLine[rows][i]=line[i] ;
            if (contentLine[rows][i] == ',')
            {
                ++cols ;
            }
        }
        if (++rows)
        {
            maxCols = cols ;
            cols = 1 ;
        }
    }
    Table** table = new Table* [rows] ;
    char* content = new char [maxNewContent] ;
    for (int i = 0 ; i < rows ; ++i)
    {
        table[i] = new Table [maxCols] ;
    }
    char* delimitedContent ;
    for (int i = 0 ; i < rows ; ++i)
    {
        delimitedContent = strtok(contentLine[i], "\n") ;
        for(int j = 0 ; j < maxCols ; ++j)
        {
            table[i][j].setContent(delimitedContent) ;
        }
    }
    
    for (int i = 0 ; i < rows ; ++i )
    {
            table[i][0].print() ;
    }
    
    fileTable.close();
    delete [] content ;
    return 0;
}
