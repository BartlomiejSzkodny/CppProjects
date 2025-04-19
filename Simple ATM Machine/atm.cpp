#include <iostream>
#include <fstream>
#include <string>
#include <regex>

class ATM {
private:
    int balance =0;
    std::string filename = "atm_data.txt";
public:

    void deposit(int amount)
    {
        std::ofstream file(filename, std::ios::app);
        checkBalance(); // Update balance before deposit
        if(file.is_open())
        {
            file << "Deposited: " << amount << std::endl;
            file.close();
        }
    }
    void withdraw(int amount){
        if(amount > balance)
        {
            std::cout << "Insufficient funds!" << std::endl;
        }else{
            checkBalance(); // Update balance before withdrawal
            balance -= amount;
            std::ofstream file(filename, std::ios::app);
            if(file.is_open())
            {
                file << "Withdrawn: " << amount << std::endl;
                file.close();
            }
            std::cout << "Withdrawn: " << amount << std::endl;
        }
    }
    void checkBalance()
    {
        std::ifstream file(filename);
        if(file.is_open())
        {
            std::string line;
            balance = 0; // Reset balance before calculating
            while(std::getline (file, line))
            {
                std::regex e("(Deposited|Withdrawn): ([0-9]+)");
                std::smatch match;
                if(std::regex_search(line, match, e))
                {
                    std::string action = match[1].str();
                    int amount = std::stoi(match[2].str());
                    if(action == "Deposited")
                    {
                        balance += amount;
                    }
                    else if(action == "Withdrawn")
                    {
                        balance -= amount;
                    }
                }
            }
            file.close();
            std::cout << "Current balance: " << balance << std::endl;
        }
    }
    void reset()
    {
        balance = 0;
        std::ofstream file(filename, std::ios::trunc);
        if(file.is_open())
        {
            file.close();
        }
        
        std::cout << "ATM reset. Balance is now 0." << std::endl;

    }
};

