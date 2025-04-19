#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "book.cpp"

int main(){
    
    int choice =0;
    std::string contact;
    book myBook; // Create an instance of the book class
    myBook.loadContacts();
    while (choice!=5){
    std::cout << "Choose an option:\n";
    std::cout << "1. Add Contact\n";
    std::cout << "2. View Contacts\n";
    std::cout << "3. Search Contact\n";
    std::cout << "4. Delete Contact\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore(); // Ignore newline character left in the buffer

    
    switch (choice)
    {
        case 1:
            std::cout << "Enter contact name: ";
            std::getline(std::cin, contact);
            myBook.addContact(contact);
            break;
        case 2:
            myBook.viewContacts();
            break;
        case 3:
            std::cout << "Enter name to search: ";
            std::getline(std::cin, contact);
            int ret;
            ret=myBook.searchContact(contact);
            if(ret==1)
            std::cout<<"found!!"<<std::endl;
            else
            std::cout<<"not found!!"<<std::endl;\
            break;
        case 4:
            std::cout << "Enter name to delete: ";
            std::getline(std::cin, contact);
            myBook.deleteContact(contact);
            break;
        case 5:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice! Please try again.\n";
    }
    myBook.saveContacts(); // Save contacts to file before exiting

    }
    
    return 0;


}