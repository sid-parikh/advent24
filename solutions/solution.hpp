#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include <sstream>

std::vector<std::string> split(const std::string& s, char delim = ' ') {
    std::istringstream iss{s};
    std::string token;
    std::vector<std::string> out{};
    while (std::getline(iss, token, delim)) {
        if (!token.empty()) {
            out.push_back(token);
        }
    }
    return out;
}

template<class Derived>
class Solution {
public:
    void run() {
        std::cout << "\n\nDay " << day << "\n";
        std::cout << "--------------------------------------\n";
        std::cout << "Part 1:\n";
        std::cout << (static_cast<Derived*>(this)->part1());
        std::cout << "\n\nPart 2:\n";
        std::cout << (static_cast<Derived*>(this)->part2());
    }

protected:
    Solution(int day) : day{day} {}

    std::ifstream get_input() {
        std::ifstream input{std::format("./input/day{:02}", day)};

        if (!input) {
            throw std::runtime_error{std::format("Warning: could not find input file for day {}", day)};
        }

        return input;
    }

private:
    int day;
};
