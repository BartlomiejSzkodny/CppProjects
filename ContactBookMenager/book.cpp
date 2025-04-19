#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
class book
{
private:
    std::string filename = "book_data.txt";
    std::vector<std::string> contacts;
public:
    void addContact(const std::string& contact)
    {
        contacts.push_back(contact);
    }
    void viewContacts()
    {
        for(const auto& contact : contacts)
        {
            std::cout << contact << std::endl;
        }
    }
    int searchContact(const std::string& name)
    {
        std::cout<<"looking for"<<name<<std::endl;
        for(const auto& contact : contacts)
        {
            if(contact.find(name) != std::string::npos)
            {
                return 1;
            }
        }
        return 0;
    }
    void deleteContact(const std::string& name)
    {
        contacts.erase(std::remove_if(contacts.begin(), contacts.end(),
            [&name](const std::string& contact) { return contact.find(name) != std::string::npos; }),
            contacts.end());
    }
    void saveContacts() const
    {
        std::ofstream file1(filename, std::ios::app);
        std::ofstream file2(filename, std::ios::trunc);
        if(file2.is_open())
        {
            file2.close();
        }
        else
        {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
        if(file1.is_open())
        {
            for(const auto& contact : contacts)
            {
                file1 << contact << std::endl;
            }
            file1.close();
        }
        else
        {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }
    void loadContacts()
    {
        std::ifstream file(filename);
        
        if(file.is_open())
        {
            std::string line;
            while(std::getline(file, line))
            {
                contacts.push_back(line);
            }
            file.close();
        }
        else
        {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }
    void clearContacts()
    {
        contacts.clear();
        std::ofstream file(filename, std::ios::trunc);
        if(file.is_open())
        {
            file.close();
        }
        else
        {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }
    void updateContact(const std::string& oldContact, const std::string& newContact)
    {
        for(auto& contact : contacts)
        {
            if(contact == oldContact)
            {
                contact = newContact;
                break;
            }
        }
    }
    void sortContacts()
    {
        std::sort(contacts.begin(), contacts.end());
    }
};

