#pragma once

#include "solution.hpp"
#include <functional>

class Day7 : public Solution<Day7> {
public:
    Day7() : Solution<Day7>(7) {}

    long part1() {
        process();

        long res = 0;
        for (size_t i = 0; i < targets.size(); ++i) {
            if (possible(targets[i], 0, 0, rows[i])) {
                res += targets[i];
            }
        }

        return res;
    }

    long part2() {
        long res = 0;
        for (size_t i = 0; i < targets.size(); ++i) {
            if (possible2(targets[i], 0, 0, rows[i])) {
                res += targets[i];
            }
        }

        return res;
    }

private:
    std::vector<long> targets {};
    std::vector<std::vector<long>> rows {};

    void process() {
        auto istream = get_input();
        std::string line;
        while (std::getline(istream, line)) {
            auto splt = split(line);
            std::vector<long> row;
            row.reserve(splt.size() - 1);
            targets.push_back(std::stol(splt[0].substr(0, splt[0].size() - 1)));
            for (size_t i = 1; i < splt.size(); ++i) {
                row.push_back(std::stol(splt[i]));
            }
            rows.push_back(row);
        }
    }

    static bool possible(long target, long curr_tot, size_t i, std::vector<long>& nums) {
        if (i == nums.size()) return (target == curr_tot);

        if (curr_tot + nums[i] <= target) {
            if (possible(target, curr_tot + nums[i], i + 1, nums)) {
                return true;
            }
        }

        if (curr_tot * nums[i] <= target) {
            if (possible(target, curr_tot * nums[i], i + 1, nums)) {
                return true;
            }
        }

        return false;
    }

    static long concat(long a, long b) {
        return std::stol(std::format("{}{}", a, b));
    }

    static bool possible2(long target, long curr_tot, size_t i, std::vector<long>& nums) {
        if (i == nums.size()) return (target == curr_tot);

        if (curr_tot + nums[i] <= target) {
            if (possible2(target, curr_tot + nums[i], i + 1, nums)) {
                return true;
            }
        }

        if (curr_tot * nums[i] <= target) {
            if (possible2(target, curr_tot * nums[i], i + 1, nums)) {
                return true;
            }
        }

        long c = concat(curr_tot, nums[i]);
        if (c <= target) {
            if (possible2(target, c, i + 1, nums)) {
                return true;
            }
        }

        return false;
    }
};

