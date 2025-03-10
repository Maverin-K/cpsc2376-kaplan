#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

int main() {
    // Step 1: Ask the user for input and read space-separated numbers
    std::cout << "Enter a list of space-separated numbers: ";
    std::string input;
    std::getline(std::cin, input);

    // Step 2: Store numbers in a std::vector<int>
    std::vector<int> numbers;
    std::istringstream stream(input);
    int number;
    while (stream >> number) {
        numbers.push_back(number);
    }

    // Step 3: Sort the numbers using a lambda function with custom sorting rules
    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
        // Rule 1: Odd numbers are considered larger than even numbers
        if (a % 2 != 0 && b % 2 == 0) return true;  // Odd > Even
        if (a % 2 == 0 && b % 2 != 0) return false; // Even < Odd

        // Rule 2: Among odd numbers, sort in descending order
        if (a % 2 != 0 && b % 2 != 0) return a > b;  // Descending for odd numbers

        // Rule 3: Among even numbers, sort in descending order
        if (a % 2 == 0 && b % 2 == 0) return a > b;  // Descending for even numbers

        return false;
        });

    // Step 4: Output the sorted numbers
    std::cout << "Sorted numbers: ";
    for (const int& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
