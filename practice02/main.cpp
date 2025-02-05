//added a way to reset balance because I accidentally set it to a runwritable number. 
#include <iostream>
#include <fstream>
#include <iomanip>

const std::string FILENAME = "account_balance.text";

double readBalance() {
    std::ifstream file(FILENAME);
    double balance;
    if (file) {
        file >> balance;
    } else {
        balance = 100.00;
        std::ofstream outFile(FILENAME);
        outFile << std::fixed << std::setprecision(2) << balance;
    }
    return balance;
}

void writeBalance(double balance) {
    std::ofstream file(FILENAME);
    if (file) {
        file << std::fixed << std::setprecision(2) << balance;
    } else {
        std::cerr << "Error: Unable to update balance file." << std::endl;
        exit(1);
    }
}

void displayMenu() {
    std::cout << "\nMenu:" << std::endl;
    std::cout << "1. Check Balance" << std::endl;
    std::cout << "2. Desposit Money" << std::endl;
    std::cout << "3. Withdraw Money" << std::endl;
    std::cout << "4. Reset Balance" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    double balance = readBalance();
    int choice;

    std::cout << "Welcome to Your Bank Account!" << std::endl;
    std::cout << "Initializing account with $" << balance << std::endl;

    while (true) {
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 4." << std::endl;
            continue;
        }

        switch (choice) {
        case 1:
            std::cout << "Your current balance is: $" << std::fixed << std::setprecision(2) << balance << std::endl;
            break;
        case 2: {
            double deposit;
            std::cout << "Enter deposit amount: ";
            std::cin >> deposit;
            if (deposit <= 0) {
                std::cout << "Error: Deposit amount must be positive." << std::endl;
            } else {
                balance += deposit;
                writeBalance(balance);
                std::cout << "Deposit successful. Your new balance is: $" << balance << std::endl;
            }
            break;
        }
        case 3: {
            double withdrawal;
            std::cout << "Enter withdrawal amount: ";
            std::cin >> withdrawal;
            if (withdrawal <= 0) {
                std::cout << "Error: Withdrawl amount must be positive." << std::endl;
            } else if (withdrawal > balance){
                std::cout << "Error: Insufficient funds. Your balance is $" << balance << std::endl;
            } else {
                balance -= withdrawal;
                writeBalance(balance);
                std::cout << "Withdrawal successful. Your new balance is: $" << balance << std::endl;
            }
            break;
        }
        case 4: 
            balance = 100.00;
            writeBalance(balance);
            std::cout << "Balance has been reset to 100.00." << std::endl;
            break;
        case 5:
            std::cout << "Thank you for using your Bank Account. Goodbye!" << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Please select a valid option." << std::endl;
        }
    }

    return 0;
}
