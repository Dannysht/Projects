#include "Calendar.hpp"

const int maxCommandSize = 150 ;
char* currentName = "calendar.txt" ;

void Calendar::open (const char* command)
{
    if (calendar.is_open())
    {
        std::cout << "You already have an opened calendar \n" ;
        return;
    }
    const char* delimiter = " ";
    char* expression = new char [strlen(command) + 1];
    strcpy (expression, command) ;
    char* com;
    char* path ;
    com = strtok (expression, delimiter) ;
    path = strtok (NULL, delimiter) ;
    if (path == NULL)
    {
        calendar.open("calendar.txt", std::fstream::in | std::fstream::out ); // opens an existing preset calendar calendar.txt
        char* date = new char[11] ;
        char* startTime = new char [6] ;
        char* endTime = new char [6] ;
        char* name = new char [36] ;
        char* note = new char[91] ;
        if (calendar.is_open())
        {
                do
                {
                    calendar >> date ;
                    calendar >> startTime ;
                    calendar >> endTime ;
                    calendar >> name ;
                    calendar >> note ;
                    Appointment app (date, startTime, endTime, name, note) ;
                    CalendarAppointments::setAppointment(app) ;
                }
                while(!calendar.eof());
            delete [] date ;
            delete [] startTime ;
            delete [] endTime ;
            delete [] name ;
            delete [] note ;
            std::cout << "Calendar succesfully opened \n" ;
        }
        else
        {
            calendar.open("calendar.txt", std::fstream::in | std::fstream::out | std::fstream::trunc)  ; //creates a calendar with preset name of calendar.txt
            if (calendar.is_open())
            {
                std::cout << "Calendar succesfully opened \n" ;
            }
            else
            {
                std::cout << "Error opening calendar \n" ;
            }
        }
    }
    else
    {
        calendar.open (path, std::fstream::in | std::fstream::out) ; // opens a custom named calendar
        char* date = new char[11] ;
        char* startTime = new char [6] ;
        char* endTime = new char [6] ;
        char* name = new char [36] ;
        char* note = new char[91] ;
        if (calendar.is_open())
        {
            currentName = path ;
                do
                {
                    calendar >> date ;
                    calendar >> startTime ;
                    calendar >> endTime ;
                    calendar >> name ;
                    calendar >> note ;
                    Appointment app (date, startTime, endTime, name, note) ;
                    CalendarAppointments::setAppointment(app) ;
                }
                while(!calendar.eof());
                std::cout << "Calendar succesfully opened \n" ;
        }
        else
        {
            calendar.open (path, std::fstream::in | std::fstream::out | std::fstream::trunc) ; // creates a caledar with custom name
            if (calendar.is_open())
            {
                std::cout << "Calendar succesfully opened \n" ;
            }
            else
            {
                std::cout << "Error opening calendar \n" ;
            }
        }
    }
}


void Calendar::close (const char* command)
{
    if (calendar.is_open())
        {
            calendar.close();
            std::cout << "Calendar closed succesfully \n" ;
        }
    else
        {
            std::cout << "Nothing to close \n" ;
            
        }
}

void Calendar::help (const char* command)
{
    if (strcmp (command,"help") == 0)
    {
        std::cout << "The following commands are supported: \n\n";
        
        std::cout << "open <file> \t opens <file> \n\n" ;
        
        std::cout << "close \t closes currently opened file \n\n" ;
        
        std::cout << "save \t saves the currently open file \n\n" ;
        
        std::cout << "saveas <file> \t saves the currently open file in <file> \n\n";
        
        std::cout << "help \t prints this information \n\n" ;
        
        std::cout << "book <date> <starttime> <endtime> <name> <note> \t books an appointment with <name> on <date> with starting time <starttime> ending at <endtime> \n\n" ;
        
        std::cout << "unbook <date> <starttime> <endtime> \t cancels appointment on <date> starting at <starttime> ending at <endtime> \n\n" ;
        
        std::cout << "agenda <date> \t shows a chronological list of appointments and events for the day <date> \n\n" ;
        
        std::cout << "change <date> <starttime> <option> <newvalue> \t <option> should be one of date, starttime, enddate, name, note. \n sets a new value <newvalue> in the event at date <date> starting at <starttime>, if a date or hours are changed a verification is made to check if they are valid and free \n\n" ;
        
        std::cout << "find <string> \t searches for an appointment: shows data about all appointments in which names or notes <string> is included \n\n";
        
        std::cout << "holiday <date> \t  sets the date <date> as a holiday \n\n" ;
        
        std::cout << "busydays <from> <to> \t Shows statistics of workload: with starting date <from> to ending date <to> a list of days of the week is shown sorted by 'number of busy hours' \n\n" ;
        
        std::cout << "findslot <fromdate> <hours> \t finds a free time for an appointment: by given date <fromdate> and desired duration <hours> of the meeting, looks only for a date at which such an     appointment is possible, only in workdays, not before 8 o'clock and not after 17 o'clock \n\n" ;
        
        std::cout << "merge <calendar> \t transfers all the appointments of <calendar>, in current calendar, transfer happens in a dialogue mode so if a conflict between them happens user can pick which one to move to a different date and time.\n Example : user has signed up for Sports classes and has recieved a file which has a calendar that has all the practice and sports events schedules on, they want to transfer all the sports events to their calendar \n\n" ;
    }
}

void Calendar::save(const char *command)
{
    calendar.close();
    calendar.open(currentName);
    std::cout << "Saved successfully \n" ;
    
}

size_t getFileSize( std::fstream& calendar )
{
    calendar.seekg( 0, std::ios::end );
    size_t size = calendar.tellg();
    calendar.seekg( 0, std::ios::beg );

    return size;
}

void Calendar::saveas(const char* command)
{
    const char* delimiter = " ";
    const char* nameDelimiter = "/" ;
    char* com = splitCommand(command) ;
    char* path = strtok (NULL, delimiter) ;
    std::ofstream savedAs ;
    savedAs.open(path) ;
    size_t fileSize = getFileSize(calendar);
    char* calendarContent = new char[fileSize+1] ;
    calendar.read(calendarContent, fileSize) ;
    savedAs.write(calendarContent, fileSize) ;
    if (strncmp (path, "/", maxCommandSize) == 0)
    {
        char* filePath = strtok (path, nameDelimiter) ;
        if(strcmp (filePath, "/") > 0)
        {
            while (strcmp (filePath, "/") < 0 ) ;
            {
                filePath = strtok (NULL, delimiter);
            }
        }
        if (savedAs.is_open())
        {
            std::cout << "Successfully saved " << filePath << std::endl ;
            savedAs.close() ;
        }
        else
        {
            std::cout << "There was an error saving " << filePath << std::endl ;
        }
    }
    else
    {
        if (savedAs.is_open())
        {
            std::cout << "Successfully saved " << path << std::endl ;
        }
        else
        {
            std::cout << "There was an error saving " << path << std::endl ;
        }
    }
    delete [] calendarContent ;
    currentName = path ;
    calendar.close() ;
    calendar.open(currentName) ;
}

void Calendar::startProgram ()
{
    std::cout << "Welcome to your personal calendar/organizer \n" ;
    std::cout << "Format of date is DD.MM.YYYY \n" << "Format of start and end times are HH:MM \n" << "Format of the name is First name Last name \n" << "For commands list use 'help' \n" ;
    std::cout << "Please enter a command: " ;
    char command[maxCommandSize] ;
    std::cin.getline(command,maxCommandSize);
    bool beginningPass = false ;
    while ( strcmp (command,"exit") != 0)
        {
            if(strncmp (command, "open" , 4) == 0)
            {
                open(command);
            }
            else if (strcmp (command, "close") == 0)
            {
                close(command);
            }
            else if (strcmp (command, "help") == 0)
            {
                help(command);
            }
            else if (strncmp(command, "saveas ", 7) == 0)
            {
                saveas(command);
            }
            else if (strcmp (command,"save") == 0 )
            {
                save(command) ;
            }
            else if (strncmp (command, "book", 4) == 0)
            {
                book(command) ;
            }
            else if (strncmp(command, "holiday", 7) == 0)
            {
                holiday(command) ;
            }
            else if (strncmp(command, "merge", 5) == 0)
            {
                merge(command) ;
            }
            else if (strncmp(command, "unbook" , 6) == 0)
            {
                unbook(command) ;
            }
            else if (strncmp(command, "find", 4) == 0)
            {
                find (command) ;
            }
            else if (strncmp(command, "change", 6) == 0)
            {
                change(command) ;
            }
            else if (strncmp (command, "busydays", 8) == 0)
            {
                busydays(command) ;
            }
            else if (strcmp (command, "agenda" ) == 0)
            {
                agenda() ;
            }
            else if (strncmp (command, "findslot", 8))
            {
                findslot(command) ;
            }
            else if (strncmp (command, "findslotwith", 12))
            {
                findslotwith(command) ;
            }
            beginningPass = true ;
            if (beginningPass)
            {
                std::cout << "Please enter a command: " ;
            }
                std::cin.getline (command,maxCommandSize) ;
    }
    std::cout << "Exiting program...\n" ;
}
