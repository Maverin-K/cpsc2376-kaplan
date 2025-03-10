#include <iostream>
#include <vector>
#include <random>
#include <limits>

// Function to generate random numbers and store them in a vector
std::vector<int> generateRandomNumbers(int count) {
    std::vector<int> numbers;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    for (int i = 0; i < count; ++i) {
        numbers.push_back(dist(gen));
    }
    return numbers;
}

// Function to calculate the sum of numbers (pass-by-const-reference)
int calculateSum(const std::vector<int>& numbers) {
    int sum = 0;
    for (int num : numbers) {
        sum += num;
    }
    return sum;
}

// Function to find minimum and maximum values (pass-by-const-reference & pass-by-reference for output)
void findMinMax(const std::vector<int>& numbers, int& min, int& max) {
    if (numbers.empty()) return;

    min = std::numeric_limits<int>::max();
    max = std::numeric_limits<int>::min();

    for (int num : numbers) {
        if (num < min) min = num;
        if (num > max) max = num;
    }
}

// Function to calculate the average (pass-by-const-reference)
double calculateAverage(const std::vector<int>& numbers) {
    if (numbers.empty()) return 0.0;
    return static_cast<double>(calculateSum(numbers)) / numbers.size();
}

int main() {
    int count;

    // Ask the user for the number of random numbers
    std::cout << "Enter the number of random numbers to generate: ";
    std::cin >> count;

    if (count <= 0) {
        std::cout << "Invalid input. Please enter a positive number.\n";
        return 1;
    }

    // Generate random numbers
    std::vector<int> numbers = generateRandomNumbers(count);

    // Display generated numbers
    std::cout << "Generated numbers: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Calculate sum
    int sum = calculateSum(numbers);

    // Find min and max
    int min, max;
    findMinMax(numbers, min, max);

    // Calculate average
    double average = calculateAverage(numbers);

    // Display results
    std::cout << "Sum: " << sum << "\n";
    std::cout << "Minimum: " << min << "\n";
    std::cout << "Maximum: " << max << "\n";
    std::cout << "Average: " << average << "\n";

    return 0;
}
