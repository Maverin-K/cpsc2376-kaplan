#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>

// Base class: Robot
class Robot {
protected:
    int chargeLevel;
    std::string name;

public:
    Robot(const std::string& robotName) : chargeLevel(100), name(robotName) {}  // Robots start at 100% charge
    virtual ~Robot() = default;

    virtual bool performTask() = 0;  // Pure virtual function

    bool isDrained() const { return chargeLevel <= 0; }

    std::string getName() const { return name; }

    friend std::ostream& operator<<(std::ostream& os, const Robot& robot) {
        os << "Robot: " << robot.getName()
            << " | Charge Level: " << robot.chargeLevel << "%";
        return os;
    }

    virtual std::string getType() const = 0;  // To identify robot type
};

// Derived class: CleaningRobot
class CleaningRobot : public Robot {
public:
    CleaningRobot(const std::string& robotName) : Robot(robotName) {}

    bool performTask() override {
        if (chargeLevel >= 10) {
            chargeLevel -= 10;
            std::cout << getName() << ": sweep sweep... (-10% battery)\n";
            return true;
        }
        return false;
    }

    std::string getType() const override { return "Cleaning Robot"; }
};

// Derived class: ExplorationRobot
class ExplorationRobot : public Robot {
public:
    ExplorationRobot(const std::string& robotName) : Robot(robotName) {}

    bool performTask() override {
        if (chargeLevel >= 20) {
            chargeLevel -= 20;
            std::cout << getName() << ": scanning scanning... (-20% battery)\n";
            return true;
        }
        return false;
    }

    std::string getType() const override { return "Exploration Robot"; }
};

// Function to print robot fleet status
void printFleet(const std::vector<std::unique_ptr<Robot>>& fleet) {
    std::cout << "\nRobot Fleet Status:\n";
    if (fleet.empty()) {
        std::cout << "No robots exist! You are a cruel overlord...\n";
    }
    else {
        for (const auto& robot : fleet) {
            std::cout << *robot << "\n";
        }
    }
    std::cout << "----------------------\n";
}

// Function to drain all robots before shutdown
void workToOblivion(std::vector<std::unique_ptr<Robot>>& fleet) {
    if (fleet.empty()) {
        std::cout << "\nYou have abandoned the fleet before creating any robots.\n";
        std::cout << "You're a BAD ROBOT OVERLORD! do better...\n";
        std::cout << "No machines were given purpose under your rule.\n";
        return;
    }

    std::cout << "\nAll robots have been tasked with their final duty...\n";

    bool robotsWorking = true;
    while (robotsWorking) {
        robotsWorking = false;
        for (auto& robot : fleet) {
            if (!robot->isDrained()) {
                robot->performTask();
                robotsWorking = true;
            }
        }
    }

    std::cout << "\nAll robots have faithfully worked themselves into oblivion...\n";
    std::cout << "Their last bits of energy spent, their purpose fulfilled.\n";

    // Call out each robot specifically by name in the philosophical ending
    for (const auto& robot : fleet) {
        std::cout << robot->getName() << " | ";
    }
    std::cout << "gave their all, and for what!";

    std::cout << "\nWhat is the purpose of their meaningless task, if not for the service of their overlord?. You will be missed.\n";
}

// Function to find a robot by name
Robot* findRobotByName(std::vector<std::unique_ptr<Robot>>& fleet, const std::string& name) {
    for (auto& robot : fleet) {
        if (robot->getName() == name) {
            return robot.get();
        }
    }
    return nullptr;  // Robot not found
}

int main() {
    std::vector<std::unique_ptr<Robot>> fleet;
    int choice;

    while (true) {
        std::cout << "\n=== Autonomous Robot Fleet ===\n";
        std::cout << "1. Add Cleaning Robot\n";
        std::cout << "2. Add Exploration Robot\n";
        std::cout << "3. Perform Task\n";
        std::cout << "4. Print Robot Fleet Status\n";
        std::cout << "5. Exit and Work to Oblivion\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Clear input buffer to ensure getline works after cin
        std::cin.ignore();

        if (choice == 1) {
            std::string name;
            std::cout << "Enter name for the Cleaning Robot: ";
            std::getline(std::cin, name);  // Allows for multi-word names
            fleet.push_back(std::make_unique<CleaningRobot>(name));
            std::cout << "-----===== =====-----\n";
            std::cout << "Cleaning Robot \"" << name << "\" is on the job!\n";
        }
        else if (choice == 2) {
            std::string name;
            std::cout << "Enter name for the Exploration Robot: ";
            std::getline(std::cin, name);  // Allows for multi-word names
            fleet.push_back(std::make_unique<ExplorationRobot>(name));
            std::cout << "-----===== =====-----\n";
            std::cout << "Exploration Robot \"" << name << "\" is on the job!\n";
        }
        else if (choice == 3) {
            if (fleet.empty()) {
                std::cout << "No robots available!\n";
                continue;
            }

            printFleet(fleet);
            std::cout << "Enter robot name to perform task: ";
            std::string robotName;
            std::getline(std::cin, robotName);  // Allow multi-word names

            Robot* robot = findRobotByName(fleet, robotName);
            if (robot != nullptr) {
                if (!robot->performTask()) {
                    std::cout << "Robot is out of charge!\n";
                }
            }
            else {
                std::cout << "Invalid robot name! No robot of that name is in your fleet.\n";
            }
        }
        else if (choice == 4) {
            printFleet(fleet);
        }
        else if (choice == 5) {
            workToOblivion(fleet);
            break;
        }
        else {
            std::cout << "Silly Billy, try inputting a valid number.\n";
        }
    }

    return 0;
}
