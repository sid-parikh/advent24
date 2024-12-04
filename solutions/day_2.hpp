#pragma once

#include "solution.hpp"

class Day2 : public Solution<Day2> {
public:
    Day2() : Solution<Day2>(2) {
        process();
    }

    int part1() {
        int safe = 0;

        for (std::vector<int>& report: reports) {
            if (check(report))
            {
                ++safe;
            }
        }

        return safe;
    }

    int part2() {
        int safe = 0;

        for (std::vector<int>& report: reports) {
            if (check(report)) {
                ++safe;
            } else {
                for (size_t i = 0; i < report.size(); ++i) {
                    int n = report[i];
                    report.erase(report.begin() + i);
                    if (check(report)) {
                        ++safe;
                        break;
                    }
                    report.insert(report.begin() + i, n);
                }
            }
        }

        return safe;
    }

private:
    std::vector<std::vector<int>> reports{};

    bool check(std::vector<int> & vec)
    {
        bool increasing = vec[1] > vec[0];
        for (size_t i = 1; i < vec.size(); ++i)
        {
            int diff = increasing ? vec[i] - vec[i - 1] : vec[i - 1] - vec[i];
            if (diff < 1 || diff > 3) {
                return false;
            }
        }

        return true;
    }

    void process() {
        auto istream = get_input();
        std::string line;
        while (std::getline(istream, line)) {
            std::vector<int> nums{};
            auto words = split(line);
            nums.reserve(words.size());
            for (const std::string& word: words) {
                nums.push_back(std::stoi(word));
            }
            reports.push_back(nums);
        }
    }
};

