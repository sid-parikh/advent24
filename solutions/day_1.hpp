#pragma once
#include "solution.hpp"
#include <algorithm>
#include <unordered_map>

class Day1 : public Solution<Day1>{
public:
    Day1() : Solution<Day1>(1) {
        process();
    }

    int part1()
    {
        std::sort(list1.begin(), list1.end());
        std::sort(list2.begin(), list2.end());

        int answer = 0;
        for (size_t i = 0; i < list1.size(); ++i)
        {
            answer += std::abs(list1[i] - list2[i]);
        }

        return answer;
    }

    int part2()
    {
        std::unordered_map<int, int> freq {};
        for (int n : list2)
        {
            ++freq[n];
        }
        int score = 0;
        for (int n : list1)
        {
            score += n * freq[n];
        }
        return score;
    }

private:
    std::vector<int> list1;
    std::vector<int> list2;

    void process()
    {
        std::string line;
        auto istream = get_input();
        while (std::getline(istream, line))
        {
            auto words = split(line);
            list1.push_back(std::stoi(words[0]));
            list2.push_back(std::stoi(words[1]));
        }
    }
};
