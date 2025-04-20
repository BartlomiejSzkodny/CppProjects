#include <iostream>
struct Event
{
    /* data */
    int year;
    int month;
    int day;
    std::string event;
    Event(int y, int m, int d, const std::string& e) : year(y), month(m), day(d), event(e) {}
    Event() : year(0), month(0), day(0), event("") {} // Default constructor
};
