#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>

// Function to read numbers from a file into a vector
std::vector<int> readNumbersFromFile(const std::string& filename) {
    std::vector<int> numbers;
    std::ifstream file(filename);

    if (!file) {
        throw std::runtime_error("Error: Could not open file " + filename);
    }

    int number;
    while (file >> number) { // Read integers from the file
        numbers.push_back(number);
    }

    if (numbers.empty()) {
        throw std::runtime_error("Error: No numbers found in the file.");
    }

    return numbers;
}

// Templated function to find the largest number in any numeric vector
template <typename T>
T findLargest(const std::vector<T>& numbers) {
    if (numbers.empty()) {
        throw std::runtime_error("Cannot determine the largest number in an empty vector.");
    }

    T largest = *numbers.begin(); // Initialize with first element
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (*it > largest) {
            largest = *it;
        }
    }
    return largest;
}

int main() {
    std::string filename;

    // Ask user for the filename
    std::cout << "Enter the filename containing numbers: ";
    std::cin >> filename;

    try {
        // Read numbers from file
        std::vector<int> numbers = readNumbersFromFile(filename);

        // Display the numbers
        std::cout << "Numbers from file: ";
        for (auto it = numbers.begin(); it != numbers.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "\n";

        // Find the largest number using the templated function
        int largest = findLargest(numbers);
        std::cout << "The largest number is: " << largest << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

