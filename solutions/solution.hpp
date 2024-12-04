#pragma once
#include <iostream>

template<class Derived>
class Solution {
public:
    void run() {
        std::cout << "\n\nDay " << day << ":\n";
        std::cout << "--------------------------------------\n";
        std::cout << "Part 1:\n";
        std::cout << (static_cast<Derived*>(this)->part1());
        std::cout << "Part 2:\n";
        std::cout << (static_cast<Derived*>(this)->part2());
    }

protected:
    Solution(int day) : day{day} {}
private:
    int day;
};
