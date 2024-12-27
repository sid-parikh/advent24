#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include <sstream>
#include "utils.hpp"

template<class Derived>
class Solution {
public:
    void run() {
        std::cout << "\n===============================";
        std::cout << "\n\nDay " << day << "\n";
        std::cout << "----------\n";
        std::cout << "Part 1:\n";
        std::cout << (static_cast<Derived*>(this)->part1());
        std::cout << "\n\nPart 2:\n";
        std::cout << (static_cast<Derived*>(this)->part2());
    }

protected:
    explicit Solution(int day) : day{day} {}

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
