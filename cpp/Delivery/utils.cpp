#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>

#include "utils.hpp"

int totalPackages = 0;
double totalWeight = 0.0;
double depotMoney = 0.0;

std::string menu = "=== Delivery Depot ===\n\n1. Next Day\n2. Assign Packages\n3. Buy Vehicle\n4. View Packages\n5. View Vehicles\n6. View Depot Statistics\n7. Exit\n\n> ";
std::string menuChoice;
std::string destinations[] = {"Florida", "New York"};

std::size_t get_random_index(size_t size) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<size_t> distribution(0, size - 1);

    return distribution(generator);
}
double get_random_double(double minimum, double maximum) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(minimum, maximum);
    return distribution(generator);
}
int get_random_int(int minimum, int maximum) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<size_t> distribution(minimum, maximum);

    return distribution(generator);
}
std::string get_random_string(size_t length) {
    const std::string pool = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                             "0123456789";
    std::string result;
    result.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        size_t random_index = get_random_index(pool.size());
        result += pool[random_index];
    }

    return result;
}
std::string remove_char(std::string str, char character) {
    str.erase(std::remove(str.begin(), str.end(), character), str.end());

    return str;
}
std::string uppercase(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::toupper(c);
    });

    return str;
}
std::string toFixed(double fixed) {
    std::ostringstream fixedNumber;
    fixedNumber << std::fixed << std::setprecision(1)
                << fixed;

    return fixedNumber.str();
}
