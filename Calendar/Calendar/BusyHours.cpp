//
//  BusyHours.cpp
//  Calendar
//
//  Created by Daniel Shterev on 14.06.20.
//  Copyright © 2020 Daniel Shterev. All rights reserved.
//

#include "BusyHours.hpp"

//realisations for big 4

void BusyHours::copy (const BusyHours& busy)
{
    fDate = new char [strlen(busy.fDate)+1] ;
    strcpy (fDate, busy.fDate) ;
    fBusyHours = busy.fBusyHours ;
}
BusyHours& BusyHours::operator= (const BusyHours& busy)
{
    if(this != &busy)
    {
        delete [] fDate ;
        copy(busy) ;
    }
    return* this ;
}

BusyHours::~BusyHours()
{
    delete[]fDate ;
}

BusyHours::BusyHours (const BusyHours& busy) :BusyHours()
{
    if(this != &busy)
    {
        copy(busy) ;
    }
}

BusyHours::BusyHours (const char* date, int busyHours)
{
    fDate = new char [strlen(date) + 1] ;
    strcpy (fDate ,date) ;
    fBusyHours = busyHours ;
}

BusyHours::BusyHours()
{
    fDate = new char [1] ;
    strcpy(fDate, "") ;
    fBusyHours = 0 ;
}
