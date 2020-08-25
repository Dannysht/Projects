//
//  formula.hpp
//  tables
//
//  Created by Daniel Shterev on 30.03.20.
//  Copyright © 2020 Daniel Shterev. All rights reserved.
//

#ifndef formula_hpp
#define formula_hpp

#include <iostream>
#include <string>
#include <math.h>

#include "table.hpp"

int getRow (char* Arg) ;
int getCol (char* Arg) ;
double operate (double firstNum, double secondNum, char operation);
#endif /* formula_hpp */
