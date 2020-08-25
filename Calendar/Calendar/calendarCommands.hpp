#ifndef calendarCommands_hpp
#define calendarCommands_hpp

#include <iostream>
#include <fstream>
#include <cstring>

#include "Calendar.hpp"
#include "Appointment.hpp"

namespace CalendarAppointments
{
    void setAppointment (Appointment& other) ;
    Appointment getAppointment (int currentApp) ;
}
#endif /* calendarCommands_hpp */
