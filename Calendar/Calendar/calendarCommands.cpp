#include "calendarCommands.hpp"
#include "BusyHours.hpp"

//commands specific for calendar project realised here as well as some utilities

void swap (Appointment &app, Appointment &other) //swaps two appointments
{
    Appointment saver = app ;
    app = other ;
    other = saver ;
    
}

void swap (BusyHours &hours, BusyHours &other) //swaps busy days
{
    BusyHours saver = hours ;
    hours = other ;
    other = saver ;
}

const int maxAppointments = 100 ;
int curAppointment = 0 ;

char* splitCommand(const char* command,const char* delimiter) //splits command from other words
{
    char* expression = new char [strlen (command) + 1] ;
    strcpy (expression, command) ;
    char* com = strtok (expression, delimiter) ;
    delete [] expression ;
    return com ;
}

BusyHours busynessFactor [maxAppointments] ; //a helping structure in order to sort days by busyness
Appointment app[maxAppointments] ; //a class containing all the appointments for the current calendar
void CalendarAppointments::setAppointment (Appointment& other) //adds an appointment
{
    app[curAppointment] = other ;
    ++curAppointment ;
}
Appointment CalendarAppointments::getAppointment(int curApp) //returns an appointment
{
        return app[curApp] ;
}

void Calendar::holiday (const char* command) 
{
    char* com = splitCommand(command);
    const char* delimiter = " ,-" ;
    char* date = strtok (NULL, delimiter) ;
    const char* note = "is a holiday" ;
    Appointment app (date, "", "", "", note) ;
    CalendarAppointments::setAppointment(app) ;
    calendar << date << "" << "" << "" << note ;
}

void Calendar::book(const char* command) 
{
    char* com = splitCommand(command) ;
    const char* delimiter = " ,-" ;
    const char* nameDelimiter = " ,-:" ;
    const char* noteDelimiter = "" ;
    char* date = strtok (NULL, delimiter) ;
    char* startTime = strtok (NULL, delimiter);
    char* endTime = strtok (NULL, delimiter);
    char* name = strtok (NULL, nameDelimiter) ;
    char* familyName = strtok (NULL, nameDelimiter) ;
    char* fullName = new char [strlen(name) + strlen(familyName) + 2] ;
    strcpy (fullName, name) ;
    strcat (fullName, " ") ;
    strcat (fullName, familyName) ;
    char* note = strtok (NULL, noteDelimiter) ;
    if (date != NULL && startTime != NULL && endTime != NULL && fullName != NULL && note != NULL )
    {
        Appointment app(date,startTime,endTime,fullName,note) ;
        CalendarAppointments::setAppointment (app) ;
        std::cout << "Succesfully booked appointment \n" ;
        calendar << date << " " << startTime << " " << endTime << " " << fullName << " " << note << std::endl ;
    }
    
}

void Calendar::findslot(const char* command) 
{
    char* com = splitCommand(command) ;
    char* fromdate = strtok (NULL, " ") ;
    char* hours = strtok (NULL, " ") ;
    char* minutes = strtok (NULL, ":") ;
    for (int i = 0 ; i < curAppointment ; ++i)
    {
        if(strcmp(app[i].getDate(), fromdate) >= 0 || strcmp(app[i].getNote(), "is holiday") != 0)
        {
            for (int j = 0 ; j < curAppointment ; ++j)
            {
                if (strcmp (app[i].getDate(), busynessFactor[j].fDate) == 0)
                {
                    if (busynessFactor[j].fBusyHours >= 5400 || 5400 - busynessFactor[j].fBusyHours < 100 * atoi(hours) + atoi (minutes))
                    {
                        std::cout << "This day is unavailable for such an appointment \n" ;
                    }
                    else
                    {
                        std::cout << "This date is available for such an appointment \n" ;
                    }
                }
                else
                {
                    std::cout << "This date is available for such and appointment \n" ;
                }
            }
        }
    }
}

void Calendar::findslotwith(const char* command) 
{
    char* com = splitCommand(command) ;
    char* fromdate = strtok (NULL, " ") ;
    char* hours = strtok (NULL, " ") ;
    char* minutes = strtok (NULL, ": ") ;
    char* calendar = strtok (NULL, " ") ;
    std::ifstream otherCalendar ;
    otherCalendar.open (calendar) ;
    Appointment otherApps[maxAppointments] ;
    char* date = new char[11] ;
    char* startTime = new char [6] ;
    char* endTime = new char [6] ;
    char* name = new char [36] ;
    char* note = new char[91] ;
    int j = 0 ;
    while (!otherCalendar.eof())
    {
        otherCalendar >> date ;
        otherApps[j].setDate(date) ;
        otherCalendar >> startTime ;
        otherApps[j].setStartTime (startTime) ;
        otherCalendar >> endTime ;
        otherApps[j].setEndTime(endTime) ;
        otherCalendar >> name ;
        otherApps[j].setName(name) ;
        otherCalendar >> note ;
        otherApps[j].setNote(note) ;
        ++j ;
    }
    for (int i = 0 ; i < curAppointment ; ++i)
    {
        if((strcmp(app[i].getDate(), fromdate) >= 0 && strcmp (otherApps[i].getDate(), fromdate) >= 0) || strcmp(app[i].getNote(), "is holiday") != 0 || strcmp(otherApps[i].getNote(), "is holiday"))
        {
            for (int k = 0 ; k < curAppointment ; ++k)
            {
                if (strcmp (app[i].getDate(), busynessFactor[k].fDate) == 0 && strcmp(otherApps[i].getDate(),busynessFactor[k].fDate))
                {
                    if (busynessFactor[k].fBusyHours >= 5400 || 5400 - busynessFactor[j].fBusyHours < 100 * atoi(hours) + atoi (minutes))
                    {
                        std::cout << "This day is unavailable for such an appointment \n" ;
                    }
                    else
                    {
                        std::cout << "This date is available for such an appointment \n" ;
                    }
                }
            }
        }
    }
}

void Calendar::agenda()
{
    Appointment inArr[maxAppointments] ;
    int i, j, minIndex ;
    for (i = 0 ; i < curAppointment-1 ; ++i)
    {
        minIndex = i ;
        for (j = i+1; j < curAppointment ; ++j)
        {
            if (strcmp(app[j].getDate(), app[minIndex].getDate()) > 0 )
            {
                minIndex = j ;
                swap (app[minIndex], app[i]) ;
            }
        }
    }
    for (int i = 0 ; i < curAppointment ; ++i)
    {
        std::cout << "Chronologically sorted dates:" << app[i].getDate() << " " << app[i].getStartTime() << " " << app[i].getEndTime() << " " << app[i].getName() << " " << app[i].getNote() << std::endl ;
    }
}

void Calendar::busydays (const char* command) 
{
    char* com = splitCommand(command) ;
    char* startDate = strtok (NULL, " ") ;
    char* endDate = strtok (NULL, " ") ;
    char* startHours = new char [3];
    char* startMinutes = new char [3] ;
    char* endHours = new char [3];
    char* endMinutes = new char [3] ;
    int businessCounter = 0 ;
    Appointment inApp[maxAppointments] ;
    int maxBusinessSize = curAppointment ;
    for (int i = 0 ; i < curAppointment ; ++i)
    {
        inApp[i] = app[i] ;
    }
    int l = 0 ;
    for (int i = 0 ; i < maxBusinessSize ; ++i)
    {
        do
        {
            busynessFactor[businessCounter].fDate = app[l].getDate() ;
            ++l;
        }
        while (strcmp (busynessFactor[businessCounter].fDate,startDate) <= 0 || strcmp(busynessFactor[businessCounter].fDate, endDate) >= 0) ;
        startHours = strtok(app[i].getStartTime(), ":") ;
        startMinutes = strtok (NULL, ":") ;
        endHours = strtok(app[i].getEndTime(), ":") ;
        endMinutes = strtok(NULL, ":") ;
        busynessFactor[i].fBusyHours += 100 * atoi(endHours) + atoi(endMinutes) - (100 * atoi (startHours) + atoi(endMinutes)) ;
        for (int j = 0 ; j < maxBusinessSize ; ++j)
        {
            if ( i>= j && strcmp(busynessFactor[i].fDate, inApp[j].getDate()) == 0)
            {
                startHours = strtok(inApp[j].getStartTime(), ":") ;
                startMinutes = strtok (NULL, ":") ;
                endHours = strtok(inApp[j].getEndTime(), ":") ;
                endMinutes = strtok(NULL, ":") ;
                busynessFactor[i].fBusyHours += 100 * atoi(endHours) + atoi(endMinutes) - (100 * atoi (startHours) + atoi(endMinutes)) ;
                if (j < curAppointment)
                {
                    --maxBusinessSize ;
                }
                for (int k = j; k < curAppointment ; ++k)
                {
                    inApp[j] = inApp[j+1] ;
                }
            }
        }
    }
    delete [] startHours ;
    delete [] startMinutes ;
    delete [] endHours ;
    delete [] endMinutes ;
    int i, j, minIndex;
    for (i = 0 ; i < maxBusinessSize - 1; ++i)
    {
        minIndex = i ;
        for (j = i+1 ; j < maxBusinessSize ; ++j )
        {
            if (busynessFactor[j].fBusyHours < busynessFactor[minIndex].fBusyHours)
            {
                minIndex = j ;
            }
            swap (busynessFactor[minIndex], busynessFactor[i]) ;
        }
    }
    for (int i = 0 ; i < maxBusinessSize ; ++i)
    {
        std::cout << "Sorted by least busiest day to busiest day:" << busynessFactor[i].fDate << std::endl ;
    }
}


void Calendar::change (const char* command) 
{
    char* com = splitCommand(command) ;
    const char* delimiter = " ,-" ;
    const char* nameDelimiter = ",-:" ;
    const char* noteDelimiter = "";
    char* date = strtok(NULL, delimiter) ;
    char* startTime = strtok(NULL, delimiter) ;
    char* option = strtok (NULL, delimiter) ;
    char* newValue ;
    if (strcmp (option , "name"))
    {
        newValue = strtok (NULL, nameDelimiter) ;
    }
    if (strcmp(option, "note"))
    {
        newValue = strtok (NULL, noteDelimiter) ;
    }
    else
    {
        newValue = strtok (NULL, delimiter) ;
    }
    Appointment inApp[maxAppointments] ;
    Appointment changedApp ;
    bool exists = false ;
    for (int i = 0 ; i < curAppointment ; ++i)
    {
        inApp[i] = CalendarAppointments::getAppointment(i) ;
        if (strcmp(date, inApp[i].getDate()) == 0)
        {
            if (strcmp (startTime,inApp[i].getStartTime()) == 0)
            {
                exists = true ;
                changedApp = inApp[i] ;
                break ;
            }
        }
        if (i < curAppointment)
        {
            curAppointment = curAppointment - 1 ;
            for (int j = i ; j < curAppointment ; ++j)
            {
                inApp[j] = inApp[j+1] ;
            }
        }
    }
    if (exists)
    {
        for(int i = 0 ; i < curAppointment ; ++i)
        {
            if (strcmp(option, "date") == 0)
            {
                if (strcmp(newValue, inApp[i].getDate()) == 0)
                {
                    if (strncmp (startTime, inApp[i].getStartTime(), 5) >= 0 && strncmp(startTime, inApp[i].getEndTime(), 5 ) <= 0)
                    {
                        std::cout << "You already have an appointment then \n" ;
                    }
                    else
                    {
                        changedApp.setDate(newValue) ;
                        CalendarAppointments::setAppointment(changedApp) ;
                        std::cout << "Changed date of your appointment \n" ;
                        calendar << changedApp.getDate() << " " << changedApp.getStartTime() << " "
                        << changedApp.getEndTime() << " " << changedApp.getName() << " " << changedApp.getNote() ;
                    }
                }
            }
            if (strcmp(option, "startTime") == 0)
            {
                if (strcmp(date, inApp[i].getDate()) == 0)
                {
                    if (strncmp (newValue, inApp[i].getStartTime(), 5) >= 0 && strncmp(startTime, inApp[i].getEndTime(), 5 ) <= 0)
                    {
                        std::cout << "You already have an appointment then \n" ;
                    }
                    else
                    {
                        changedApp.setStartTime(newValue) ;
                        CalendarAppointments::setAppointment(changedApp) ;
                        std::cout << "Changed start time of your appointment \n" ;
                        calendar << changedApp.getDate() << " " << changedApp.getStartTime() << " "
                        << changedApp.getEndTime() << " " << changedApp.getName() << " " << changedApp.getNote() ;
                    }
                }
            }
            if (strcmp(option, "endTime"))
            {
                if (strcmp (newValue, inApp[i].getEndTime()) == 0)
                {
                    std::cout << "The end time of that appointment is already the one you entered \n" ;
                }
                else
                {
                    changedApp.setEndTime(newValue) ;
                    CalendarAppointments::setAppointment(changedApp) ;
                    std::cout << "Changed end time of your appointment \n" ;
                    calendar << changedApp.getDate() << " " << changedApp.getStartTime() << " "
                    << changedApp.getEndTime() << " " << changedApp.getName() << " " << changedApp.getNote() ;
                }
            }
            if (strcmp(option, "name"))
                {
                    if (strcmp (changedApp.getName(), newValue) == 0 )
                    {
                        std::cout << "Your appointment is already with that person \n";
                    }
                    else
                    {
                        changedApp.setName(newValue) ;
                        CalendarAppointments::setAppointment(changedApp) ;
                        std::cout << "Changed the person met in the appointment \n" ;
                        calendar << changedApp.getDate() << " " << changedApp.getStartTime() << " "
                        << changedApp.getEndTime() << " " << changedApp.getName() << " " << changedApp.getNote() ;
                        
                    }
                }
                if (strcmp(option, "note"))
                {
                    changedApp.setNote(newValue) ;
                    CalendarAppointments::setAppointment(changedApp) ;
                    std::cout << "Changed the note to your appointment \n" ;
                    calendar << changedApp.getDate() << " " << changedApp.getStartTime() << " "
                    << changedApp.getEndTime() << " " << changedApp.getName() << " " << changedApp.getNote() ;
            }
        }
    }
}
    
void Calendar::unbook (const char* command) 
{
    char* com = splitCommand(command) ;
    const char* delimiter = " ,-" ;
    char* date = strtok(NULL, delimiter) ;
    char* startTime = strtok(NULL, delimiter) ;
    char* endTime = strtok(NULL, delimiter) ;
    Appointment inApp [maxAppointments] ;
    for (int i = 0 ; i < curAppointment; ++i)
    {
        inApp[i] = CalendarAppointments::getAppointment(i) ;
       if(strcmp(inApp[i].getDate(), date) == 0)
       {
           if(strcmp(inApp[i].getStartTime(), startTime) == 0 )
           {
               if(strcmp(inApp[i].getEndTime(),endTime) == 0)
               {
                   std::cout << "Removed event \n" ;
                   break ;
               }
           }
       }
        else
        {
            std::cout << "No such date in your calendar \n" ;
        }
        if (i < curAppointment)
        {
            curAppointment = curAppointment - 1 ;
            for (int j = i; j < curAppointment ; ++j)
            {
                inApp[j] = inApp[j+1] ;
            }
        }
    }
    int curMaxApp = curAppointment ;
    curAppointment = 0 ;
    for (int i = 0 ; i < curMaxApp ; ++i)
    {
        CalendarAppointments::setAppointment(inApp[i]) ;
        calendar << inApp[i].getDate() << " " << inApp[i].getStartTime() << " "
        << inApp[i].getEndTime() << " " << inApp[i].getName() << " " << inApp[i].getNote() ;
    }
}
    
void Calendar::find (const char* command) 
{
    char* com = splitCommand(command) ;
    const char* delimiter = "" ;
    char* sought = strtok (NULL, delimiter) ;
    char* presence ;
    Appointment inApp [maxAppointments] ;
    for (int i = 0 ; i < curAppointment; ++i)
    {
        inApp[i] = CalendarAppointments::getAppointment(i) ;
        
        presence = strstr(inApp[i].getName(), sought) ;
        if (presence)
        {
            std::cout << inApp[i].getName() ;
        }
        else
        {
            presence = strstr(inApp[i].getNote(), sought) ;
            if (presence)
            {
                std::cout << inApp[i].getNote() ;
            }
            else
            {
                std::cout << "No such strings in your calendar \n" ;
            }
        }
    }
}

void Calendar::merge (const char* command) 
{
    char* com = splitCommand(command) ;
    char* newCalendar = strtok (NULL, " ") ;
    std::ifstream otherCalendar;
    otherCalendar.open(newCalendar) ;
    if (otherCalendar.is_open())
    {
        Appointment otherApps[maxAppointments] ;
        char* date = new char[11] ;
        char* startTime = new char [6] ;
        char* endTime = new char [6] ;
        char* name = new char [36] ;
        char* note = new char[91] ;
        int i = 0 ;
        while (!otherCalendar.eof())
        {
            otherCalendar >> date ;
            otherApps[i].setDate(date) ;
            otherCalendar >> startTime ;
            otherApps[i].setStartTime (startTime) ;
            otherCalendar >> endTime ;
            otherApps[i].setEndTime(endTime) ;
            otherCalendar >> name ;
            otherApps[i].setName(name) ;
            otherCalendar >> note ;
            otherApps[i].setNote(note) ;
            ++i ;
        }
        char* newDate = new char[11] ;
        int mergeSize = i+curAppointment ;
        Appointment inApp[mergeSize] ;
        int mergeCounter = mergeSize ;
        char* answer = new char [7] ;
        for (int j = 0; j < curAppointment ; ++j)
        {
            for (int k = 0 ; k < i ; ++k)
            {
             if (strcmp(app[j].getDate(),otherApps[k].getDate()) == 0 && strncmp(app[j].getStartTime(), otherApps[k].getStartTime(),5) >= 0 && strncmp(app[j].getEndTime(),otherApps[k].getEndTime()   , 5) <= 0)
            {
                    std::cout << "There was a conflict with some of your dates please choose which one to keep (first or second:) \n" ;
                    while (strcmp(answer, "first") != 0 || strcmp (answer, "second") != 0)
                    {
                        std::cin >> answer ;
                    }
                    if (strcmp (answer, "first") == 0)
                    {
                        inApp[j] = app[j] ;
                        std::cout << "Set different date for the other appointment:" ;
                        std:: cin >> newDate ;
                        otherApps[k].setDate(newDate) ;
                        inApp[mergeCounter] = otherApps[k] ;
                        --mergeCounter ;
                    }
                    else
                    {
                        inApp[j] = otherApps[k] ;
                        std::cout << "Set different date for the other appointment:" ;
                        std::cin >> newDate ;
                        app[j].setDate(newDate) ;
                        inApp[mergeCounter] = app[j] ;
                        --mergeCounter ;
                    }
                }
                else
                {
                 inApp[j] = app[j] ;
                 inApp[mergeCounter] = otherApps[j] ;
                 --mergeCounter ;
                }
            }
        }
    delete [] date ;
    delete [] startTime ;
    delete [] endTime ;
    delete [] name ;
    delete [] note ;
    otherCalendar.close() ;
    }
}
