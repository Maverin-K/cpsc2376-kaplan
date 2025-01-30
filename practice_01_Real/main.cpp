//Practice 01 || added multiply vectors & float instead of int variables || chatgpt was used often
#include <iostream>
#include <vector>

void menu() {
    std::cout << "1. Add a vector\n";
    std::cout << "2. Display vectors\n";
    std::cout << "3. Double vectors\n";
    std::cout << "4. Add vectors\n";
    std::cout << "5. Multiply vectors\n";
    std::cout << "6. Find multiples of a given number\n";
    std::cout << "7. Exit\n";
    std::cout << "Your choice: ";
}

void displayVector(const std::vector<float>& vec) {
    std::cout << "Current Vector: ";
    if (vec.empty()) {
        std::cout << "There's no Vector.\n";
    }
    else {
        for (float num : vec) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }
}

void multiplyByTwo(std::vector<float>& vec) {
    if (vec.empty()) {
        std::cout << "Cannot multiply, vector is empty.\n";
        return;
    }
    for (float& num : vec) {
        num *= 2;
    }
    std::cout << "Vectors have been doubled.\n";
}

float multiplyVector(const std::vector<float>& vec) {
    if (vec.empty()) {
        std::cout << "Cannot multiply, please add a vector. \n";
        return 0;
    }
    float product = 1;
    for (float num : vec) {
        product *= num;
    }
    return product;
}

float sumVector(const std::vector<float>& vec) {
    if (vec.empty()) {
        std::cout << "Cannot add, vector is empty.\n";
        return 0;
    }
    float sum = 0;
    for (float num : vec) {
        sum += num;
    }
    return sum;
}

void findMultiples(const std::vector<float>& vec) {
    if (vec.empty()) {
        std::cout << "The vector is empty, please add numbers first.\n";
        return;
    }

    float divisor;
    std::cout << "Enter a number to find its multiples in the vector: ";
    std::cin >> divisor;

    if (divisor == 0) {
        std::cout << "Cannot divide by 0.\n";
        return;
    }

    std::cout << "Multiples of " << divisor << " in the vector: ";
    bool found = false;
    for (float num : vec) {
        if (static_cast<int>(num) % static_cast<int>(divisor) == 0) {
            std::cout << num << " ";
            found = true;
        }
    }

    if (!found) {
        std::cout << "None";
    }
    std::cout << "\n";
}

int main() {
    std::vector<float> numbers;
    int choice;

    do {
        menu();
        std::cin >> choice;

        switch (choice) {
        case 1: {
            float num;
            std::cout << "Enter a number to add: ";
            std::cin >> num;
            numbers.push_back(num);
            std::cout << num << " added to the vector.\n";
            break;
            }
        case 2:
            displayVector(numbers);
            break;
        case 3:
            multiplyByTwo(numbers);
            break;
        case 4: {
            float result = sumVector(numbers);
            if (!numbers.empty()) {
                std::cout << "Sum of vectors: " << result << "\n";
            }
            break;
        }
        case 5: {
            float result = multiplyVector(numbers);
            if (!numbers.empty()) {
                std::cout << "Product of all elements: " << result << "\n";
            }
            break;
        }
        case 6:
            findMultiples(numbers);
            break;
        case 7:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 6);

    return 0;
}