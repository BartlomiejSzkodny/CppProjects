//add atm
#include "atm.cpp"




int main(){
    ATM atm;
    int choice, amount;

    do {
        std::cout << "ATM Menu:\n";
        std::cout << "1. Deposit\n";
        std::cout << "2. Withdraw\n";
        std::cout << "3. Check Balance\n";
        std::cout << "4. Reset ATM\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter amount to deposit:";
                std::cin >> amount;
                atm.deposit(amount);
                break;
            case 2:
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amount;
                atm.withdraw(amount);
                break;
            case 3:
                atm.checkBalance();
                break;
            case 4:
                atm.reset();
                break;
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);
    return 0;

}