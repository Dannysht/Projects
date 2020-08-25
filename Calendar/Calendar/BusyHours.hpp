#ifndef BusyHours_hpp
#define BusyHours_hpp

#include <string.h>

class BusyHours
{
private:
    void copy (const BusyHours& busy) ;
public:
    BusyHours() ; //constructor
    BusyHours (const char* date, int busyHours) ; //constructor
    BusyHours (const BusyHours& busy) ; //copy constructor
    ~BusyHours() ; //destructor
    BusyHours& operator= (const BusyHours& busy) ; //operator=
public:
    char* fDate ;
    int fBusyHours ;
} ;

#endif /* BusyHours_hpp */
