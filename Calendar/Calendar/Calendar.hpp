#ifndef Calendar_hpp
#define Calendar_hpp

#include "calendarCommands.hpp"
#include "Appointment.hpp"


class Calendar
{
private:
        //commands specific for the calendar realisation found in calendarCommands.cpp
        void book(const char* command) ; // books an appointment
        void unbook (const char* command) ; //removes an appointment
        void agenda() ; // sorts the calendar by dates starting from the earliest
        void change(const char* command) ; // changes appointment's date/time/name/note
        void find(const char* command) ; //searches for a substring in an appointment
        void holiday(const char* command) ;  // sets the date as a holiday
        void busydays(const char* command) ; // shows how busy dates are
        void findslot(const char* command) ; // looks for free time from date in current calendar
        void findslotwith(const char* command) ;// looks for free time from date in the current calendar as well as in another calendar
        void merge(const char* command) ; //merges two calendars
    
public:
    void startProgram(); //all the commands are checked here
private:
    //usual for the project commands
    void open (const char* command); //opens a calendar
    void close (const char* command); //closes a calendar
    void help (const char* command); //displays all the commands for the calendar
    void save (const char* command); //saves the file
    void saveas(const char* command); //saves the file as
private:
    
    std::fstream calendar ;
    
};
char* splitCommand(const char* command,const char* delimiter = " ,-") ;
size_t getFileSize( std::fstream& calendar ) ; //gets a file's size

#endif /* Calendar_hpp */
