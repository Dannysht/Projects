#include "Appointment.hpp"

//realisations for big 4, setters and getters

Appointment::Appointment()
{
    fDate = new char [1] ;
    strcpy(fDate, "") ;
    fStartTime = new char [1] ;
    strcpy(fStartTime, "") ;
    fEndTime = new char [1] ;
    strcpy(fEndTime, "") ;
    fName = new char [1] ;
    strcpy(fName, "") ;
    fNote = new char [1] ;
    strcpy(fNote, "") ;
}

Appointment::Appointment (const char* date, const char* startTime, const char* endTime,
                          const char* name, const char* note)
{
    fDate = new char [strlen(date)+1] ;
    strcpy (fDate, date) ;
    fStartTime = new char [strlen(startTime)+1] ;
    strcpy (fStartTime, startTime) ;
    fEndTime = new char [strlen(endTime)+1] ;
    strcpy (fEndTime, endTime) ;
    fName = new char [strlen(name)+1] ;
    strcpy (fName, name) ;
    fNote = new char [strlen(note)+1] ;
    strcpy (fNote, date) ;
}
Appointment::Appointment (const Appointment& app) :Appointment()
{
    if(this != &app)
    {
        copy(app) ;
    }
}
Appointment::~Appointment()
{
    delete[]fDate ;
    delete[]fStartTime ;
    delete[]fEndTime ;
    delete[]fName ;
    delete[]fNote ;
}
Appointment& Appointment::operator= (const Appointment& app)
{
    if(this != &app)
    {
        delete [] fDate ;
        delete [] fStartTime;
        delete [] fEndTime ;
        delete [] fName ;
        delete [] fNote ;
        copy(app) ;
    }
    return *this ;
}

void Appointment::copy (const Appointment& app)
{
    fDate = new char [strlen(app.fDate)+1] ;
    strcpy (fDate, app.fDate) ;
    fStartTime = new char [strlen(app.fStartTime)+1] ;
    strcpy (fStartTime, app.fStartTime) ;
    fEndTime = new char [strlen(app.fEndTime)+1] ;
    strcpy (fEndTime, app.fEndTime) ;
    fName = new char [strlen(app.fName)+1] ;
    strcpy (fName, app.fName) ;
    fNote = new char [strlen(app.fNote)+1] ;
    strcpy (fNote, app.fNote) ;
}

char* Appointment::getDate ()
{
    return fDate ;
}

char*  Appointment::getStartTime ()
{
    return fStartTime ;
}

char* Appointment::getEndTime()
{
    return fEndTime ;
}

char* Appointment::getName()
{
    return fName ;
}

char* Appointment::getNote()
{
    return fNote ;
}

void Appointment::setDate(char* newValue)
{
    fDate = newValue ;
}

void Appointment::setStartTime(char* newValue)
{
    fStartTime = newValue ;
}

void Appointment::setName(char* newValue)
{
    fName = newValue ;
}

void Appointment::setNote(char* newValue)
{
    fNote = newValue ;
}

void Appointment::setEndTime(char* newValue)
{
    fName = newValue ;
}

bool Appointment::checkAppointment(const char* date, const char* startTime)
{
    if (strcmp(fDate,date) == 0)
    {
        if (strncmp(fStartTime, startTime, 2) <= 0)
        {
            return false ;
        }
    }
    return true;
}
