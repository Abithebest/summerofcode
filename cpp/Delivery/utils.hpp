#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <vector>

extern int totalPackages;
extern double totalWeight;
extern double depotMoney;

extern std::string menu;
extern std::string menuChoice;
extern std::string destinations[];

std::size_t get_random_index(size_t size);
double get_random_double(double minimum, double maximum);
int get_random_int(int minimum, int maximum);
std::string get_random_string(size_t length);
std::string remove_char(std::string str, char character);
std::string uppercase(std::string str);
std::string toFixed(double fixed);

#endif