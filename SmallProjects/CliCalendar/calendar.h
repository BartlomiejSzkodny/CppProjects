#ifndef CALENDAR_H
#define CALENDAR_H

void print_calendar(int year, int month);
void calendar_loop(void);
int write_to_calendar(int year, int month, int day, const std::string& event);
int read_from_calendar(void);
int get_last_day_of_month(int year, int month);
int get_starting_day(int year, int month);

#endif // CALENDAR_H

