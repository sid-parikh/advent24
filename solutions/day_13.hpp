#pragma once

#include "solution.hpp"
#include <regex>
#include <cmath>

class Day13 : public Solution<Day13> {
public:
    Day13() : Solution<Day13>(13) {}

    long part1() {
        process();
        long sum = 0;
        for (auto const& m : machines) {
            auto [a_times, b_times] = solve_system(m);
            if (a_times >= 0 && b_times >= 0) {
                sum += 3 * a_times + 1 * b_times;
            }
        }
        return sum;
    }

    long part2() {
        long sum = 0;
        for (auto& m : machines) {
            m.prize.first += 10000000000000;
            m.prize.second += 10000000000000;
            auto [a_times, b_times] = solve_system(m);
            if (a_times >= 0 && b_times >= 0) {
                sum += 3 * a_times + 1 * b_times;
            }
        }
        return sum;
    }

private:
    struct Machine {
        std::pair<long, long> button_a;
        std::pair<long, long> button_b;
        std::pair<long, long> prize;
    };

    std::vector<Machine> machines;

    void process() {
        auto istream = get_input();

        const std::regex base_regex(R"(.+X[+=]([0-9]+), Y[+=]([0-9]+))");
        std::smatch base_match;

        for (std::string line; std::getline(istream, line);) {
            Machine m;

            std::regex_match(line, base_match, base_regex);
            m.button_a = {std::stoi(base_match[1].str()), std::stoi(base_match[2].str())};

            std::getline(istream, line);
            std::regex_match(line, base_match, base_regex);
            m.button_b = {std::stoi(base_match[1].str()), std::stoi(base_match[2].str())};

            std::getline(istream, line);
            std::regex_match(line, base_match, base_regex);
            m.prize = {std::stoi(base_match[1].str()), std::stoi(base_match[2].str())};

            machines.push_back(std::move(m));
            std::getline(istream, line);
        }
    }

    static void print_machine(Machine const& m) {
        std::cout << std::format("Prize: ({}, {})  A: ({},{})  B:({},{})\n", m.prize.first, m.prize.second,
                                 m.button_a.first, m.button_a.second, m.button_b.first, m.button_b.second);
    }

    void print_all_machines() const {
        for (auto const& m : machines) {
            print_machine(m);
        }
    }

    static std::pair<long, long> solve_system(Machine const& m) {
        // solve this system:
        // ax + by = e
        // cx + dy = f

        // where x = number of button_a steps
        // and y = number of button_b steps

        // therefore a = button_a.first, b = button_b.first, e = prize.first (x-axis in the machine)
        // and c = button_a.second, d = button_b.second, f = prize.second (y-axis in the machine)
        // https://stackoverflow.com/questions/19619248/solve-system-of-two-equations-with-two-unknowns

        auto [a, c] = m.button_a;
        auto [b, d] = m.button_b;
        auto [e, f] = m.prize;

        double det = a*d - b*c;
        double x = (e*d - b*f)/det;
        double y = (a*f - e*c)/det;

        // check integer
        if (static_cast<long>(x) == x && static_cast<long>(y) == y) {
            long ix = static_cast<long>(x);
            long iy = static_cast<long>(y);

            // check bounds
            if (ix >= 0 && iy >= 0) {
                // try solution

                if (ix * m.button_a.first + iy * m.button_b.first == m.prize.first
                    && ix * m.button_a.second + iy * m.button_b.second == m.prize.second) {
                    return {ix, iy};
                }

            }
        }

        return {-1, -1};
    }
};

