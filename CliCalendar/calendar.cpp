#include <iostream>
#include <conio.h> // For _getch()
#include <ctime>   // For time functions
#include <array>   // For std::array
#include <string>  // For std::string
#include <fstream> // For file operations
#include <sstream> // For std::istringstream
#include <cstdlib> // For system("cls")
#include <vector>  // For std::vector
#include "event.cpp"

void clearScreen() {
    // Clears the console screen
    system("cls");
}
int write_to_calendar(int year, int month, int day, const std::string& event) {
    // Open the file in append mode
    std::ofstream file("calendar.txt", std::ios::app);
    if (!file) {
        std::cerr << "Error opening file for writing.\n";
        return 1;
    }

    // Write the date to the file
    file << year << " " << month << " " << day << " " << event << "\n";

    // Close the file
    file.close();
    return 0;
}
int read_from_calendar(std::vector<Event>& events) {
    std::ifstream file("calendar.txt");
    if (!file) {
        std::cerr << "Error opening file for reading.\n";
        return 1;
    }

    std::string line;
    int year, month, day;
    std::string event;
    Event e;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (!(iss >> e.year >> e.month >> e.day>>e.event)) {
            std::cerr << "Error reading date from file.\n";
            continue; // Skip this line if it can't be read
        }else{
            events.push_back(e); // Add the event to the vector
            
        }

        
       
    }

    file.close();
    while(true) {
        char key = _getch(); // Wait for user input
        if (key == 'q') {
            break; // Quit the program
        }
    }
    return 0;
}

int get_starting_day_of_week(int year, int month) {
    std::tm time_in = {0, 0, 0, 1, month - 1, year - 1900}; // Set to the 1st day of the given month
    std::mktime(&time_in); // Normalize the tm structure
    return time_in.tm_wday; // Return the day of the week (0 = Sunday, ..., 6 = Saturday)
}
int get_last_day_of_month(int year, int month) {
    std::tm time_in = {0, 0, 0, 1, month, year - 1900}; // Set to the 1st day of the next month
    std::mktime(&time_in); // Normalize the tm structure
    time_in.tm_mday = 0; // Set to the last day of the previous month
    std::mktime(&time_in); // Normalize again
    return time_in.tm_mday; // Return the last day of the month
}

void print_calendar(int currentDay, int year, int month, std::string event = "",bool writeMode = false, std::vector<Event> events = {}) {
    clearScreen();
    std::array<std::string, 12> month_names = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    std::cout << "Calendar - " << year << "-" << month_names[month-1] << "\n";

    std::cout << "----------------------------|----------------------------|\n";
    std::cout << " Sun Mon Tue Wed Thu Fri Sat|------------Event-----------|\n";
    std::cout << "----------------------------|----------------------------|\n";

    int starting_day = get_starting_day_of_week(year, month);
    int days_in_month = 31; // Default to 31 days (adjust for specific months if needed)

    // Adjust for months with fewer days
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        days_in_month = 30;
    } else if (month == 2) {
        // Check for leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            days_in_month = 29;
        } else {
            days_in_month = 28;
        }
    }

    // Print leading spaces for the first week
    for (int i = 0; i < starting_day; ++i) {
        std::cout << "    ";
    }

    // Print the days of the month
    for (int day = 1; day <= days_in_month; ++day) {
        if (day == currentDay) {
            std::cout << "[" << (day < 10 ? " " : "") << day << "]"; // Highlight the current day
        } else {
            std::cout << " " << (day < 10 ? " " : "") << day << " ";
        }
        
        if ((starting_day + day) % 7 == 0) {
            if (writeMode) {
                std::cout << "|";
                for (int i = (int((starting_day + day)/7)-1)*28; i < (int((starting_day + day)/7))*28; ++i) {
                    if(i < event.length()) {
                        std::cout << event[i]; // Print the event if it exists
                    } else {
                        std::cout << " "; // Fill in the rest of the week with spaces
                    }
                }
                std::cout << "|\n";
            } else {
                bool eventFound = false;
                for (const auto& e : events) {
                    if (e.year == year && e.month == month && e.day == currentDay) {
                        std::cout << "|";
                        for (int i = (int((starting_day + day)/7)-1)*28; i < (int((starting_day + day)/7))*28; ++i) {
                            if(i < e.event.length()) {
                                std::cout << e.event[i]; // Print the event if it exists
                            }
                            else {
                                std::cout << " "; // Fill in the rest of the week with spaces
                            }
                        }
                        std::cout << "|\n"; // End the line
                        eventFound = true;
                        break;
                    }
                }
                if (!eventFound) {
                    std::cout << "|"; // End the line
                    for (int i = 0; i < 28; ++i) {
                        std::cout << " "; // Fill in the rest of the week with spaces
                    }
                    std::cout << "|\n"; // End the line
                }

                
                
                
            }
            
        }
    }
    if ((starting_day + days_in_month) % 7 != 0) {
        for (int i = (starting_day + days_in_month) % 7; i < 7; ++i) {
            std::cout << "    "; // Fill in the rest of the week with spaces
        }

            std::cout << "|"; // End the line
            for (int i = 0; i < 28; ++i) {
                std::cout << "-"; // Fill in the rest of the week with spaces
            }
            std::cout << "|\n"; // End the line
    }
    

    std::cout << "----------------------------|----------------------------|\n";
    std::cout << "Use arrow keys to navigate. Press 'q' to quit.\n";
}

int calendar_loop() {
    int currentDay = 1; // Start at day 1
    int year = 2025;    // Example year
    int month = 4;      // Example month (January)
    char key;
    bool writeMode = false; // Flag to indicate if we are in write mode
    std::string event;
    std::vector<Event> events; // Vector to store events
    read_from_calendar(events); // Read events from the calendar file
    print_calendar(currentDay, year, month,event="",false,events); // Print the initial calendar

    while (true) {
        key = _getch(); // Get user input

        if (key == 'q') {
            break; // Quit the program
        }
        else if (key== 'w'){

            //make it so that caracters dont show up on the screen, just are passed to the event string
            if(event.length() > 28*4) {
                std::cout << "Event is too long. Please limit to 28 characters.\n";
                continue; // Skip writing if the event is too long
            } else {
                std::cout << "Enter event:.\n";
            }
            
            char ch;
            event.clear(); // Clear the event string
            while (true) {
                ch = _getch(); // Read a character
                if (ch == '\r') { // Check for Enter key
                    if (event.length() > 0) {
                        write_to_calendar(year, month, currentDay, event); // Write the event to the calendar
                        std::cout << "Event saved: " << event << "\n"; // Show the saved event
                        event.clear(); // Clear the event string for next input
                        events.clear(); // Clear the events vector
                        read_from_calendar(events); // Read and display events from the calendar file
                    } else {
                        std::cout << "No event entered.\n"; // Show error message if no event was entered
                    }
                    break;
                } else if (ch == '\b') { // Handle backspace
                    if (!event.empty()) {
                        event.pop_back(); // Remove the last character
                        print_calendar(currentDay, year, month, event, true); // Update the calendar display
                    }
                } else if (ch >= 32 && ch <= 126 && (event.length()<(4*28))) { // Only process printable characters
                    event += ch; // Append the character to the event string
                    print_calendar(currentDay, year, month, event, true); // Update the calendar display
                }
                
            }


            
        } else if (key == -32) { // Arrow key prefix
            key = _getch(); // Get the specific arrow key
            if (key == 75 && currentDay > 1) { // Left arrow
                --currentDay;
            } else if (key == 77 && currentDay < 31) { // Right arrow
                ++currentDay;
            } else if (key == 72 && currentDay > 7) { // Up arrow
                currentDay -= 7;
            } else if (key == 80 && currentDay <= 24) { // Down arrow
                currentDay += 7;
            } else if (key == 72 && currentDay <= 7) { // Up arrow at the start of the month
                month -= 1; // Move to the previous month
                currentDay = get_last_day_of_month(year, month); // Set to the last day of the previous month
                if (month < 1) { // If month goes below January
                    month = 12; // Reset to December
                    year -= 1; // Move to the previous year
                }
            } else if (key == 80 && currentDay > 24) { // Down arrow at the end of the month
                month += 1; // Move to the next month
                currentDay = 1; // Reset to the first day of the next month
                if (month > 12) { // If month goes above December
                    month = 1; // Reset to January
                    year += 1; // Move to the next year
                }
            }
            
        }
        print_calendar(currentDay, year, month,event="",false,events); // Update the calendar display
    }

    return 0;
}

