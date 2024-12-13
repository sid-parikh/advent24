#pragma once

#include "solution.hpp"

#include <cmath>

class Day11 : public Solution<Day11> {
public:
    Day11() : Solution<Day11>(11) {}

    size_t part1() {
        process();

        unsigned long result = 0;
        for (auto stone: stones) {
            result += number_of_stones(stone, 25);
        }

        return result;
    }

    size_t part2() {

        unsigned long result = 0;
        for (auto stone: stones) {
            result += number_of_stones(stone, 75);
        }

        return result;
    }

private:
    std::vector<unsigned long> stones = {4189,413,82070,61,655813,7478611,0,8};

    void process() {
        for (auto& m: memo) {
            m.reserve(10000);
        }
    }

    constexpr static unsigned long PRIME = 10e9 + 7;

    class hash {
    public:
        size_t operator()(unsigned long const& n) const {
            return n;
        };
    };

    std::unordered_map<unsigned long, unsigned long, hash> memo[76];

    std::unordered_map<unsigned long, std::pair<unsigned long, unsigned long>> stone_splits;

    unsigned long number_of_stones(unsigned long stone, int iter) {

        if (iter == 0) {
            return 1;
        }

        auto it = memo[iter].find(stone);
        if (it != memo[iter].end()) {
            return it->second;
        }

        unsigned long output;

        if (stone == 0) {
            output = number_of_stones(1, iter - 1);
        } else {

            auto it2 = stone_splits.find(stone);
            if (it2 != stone_splits.end()) {
                output = number_of_stones(it2->second.first, iter - 1) + number_of_stones(it2->second.second, iter - 1);
            } else {
                unsigned long num_digits = static_cast<unsigned long>(log10(stone)) + 1;
                if (num_digits % 2 == 0) {
                    // split
                    auto divisor = static_cast<unsigned int>(std::pow(10, num_digits / 2));
                    unsigned long first_num = stone / divisor;
                    unsigned long second_num = stone % divisor;
                    stone_splits[stone] = {first_num, second_num};
                    output = number_of_stones(first_num, iter - 1) + number_of_stones(second_num, iter - 1);

                } else {
                    output = number_of_stones(stone * 2024, iter - 1);
                }
            }

        }

        memo[iter][stone] = output;
        return output;
    }
};

