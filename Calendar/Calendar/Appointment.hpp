#ifndef Appointment_hpp
#define Appointment_hpp

#include <string.h>

class Appointment
{
public:
    bool checkAppointment(const char* date, const char* startTime) ;
private:
    void copy (const Appointment& app) ;
    
public:
    Appointment() ; //constructor
    Appointment (const char* date, const char* startTime, const char* endTime,
                 const char* name, const char* note) ; //constructor
    Appointment (const Appointment& app) ; //copy constructor
    ~Appointment() ; //destructor
    Appointment& operator= (const Appointment& app) ; //operator =
    //getters
    char* getDate() ;
    char* getStartTime () ;
    char* getEndTime () ;
    char* getName() ;
    char* getNote() ;
    //setters
    void setDate(char* newValue) ;
    void setStartTime (char* newValue) ;
    void setEndTime (char* newValue) ;
    void setName (char* newValue) ;
    void setNote (char* newValue) ;
    
    
private:
    char* fDate ;
    char* fStartTime;
    char* fEndTime ;
    char* fName ;
    char* fNote ;
};



#endif /* Appointment_hpp */
