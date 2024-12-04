#pragma once

#include "solution.hpp"
#include <regex>

class Day3 : public Solution<Day3> {
public:
    Day3() : Solution<Day3>(3) {
        process();
    }

    long part1() {
        auto words_begin = std::sregex_iterator(input.begin(), input.end(), mul_regex);
        auto words_end = std::sregex_iterator();

        long sum = 0;
        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            const std::smatch& match = *i;
            sum += std::stol(match[1]) * std::stol(match[2]);
        }

        return sum;
    }

    long part2() {
        auto words_begin = std::sregex_iterator(input.begin(), input.end(), part2_regex);
        auto words_end = std::sregex_iterator();

        long sum = 0;
        bool enabled = true;
        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            const std::smatch& match = *i;
            if (*match[0].first == 'm' && enabled) {
                sum += std::stol(match[1]) * std::stol(match[2]);
            } else if (match[0].str().length() > 4) {
                // don't
                enabled = false;
            } else {
                enabled = true;
            }
        }

        return sum;
    }

private:
    std::regex mul_regex{"mul\\(([0-9]+),([0-9]+)\\)"};
    std::regex part2_regex{R"(mul\(([0-9]+),([0-9]+)\)|do\(\)|don't\(\))"};
    std::string input;

    void process() {
        auto istream = get_input();
        std::stringstream buf;
        buf << istream.rdbuf();
        input = buf.str();
    }
};

