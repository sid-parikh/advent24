#pragma once

#include "solution.hpp"
#include <ranges>
#include <unordered_set>

class Day5 : public Solution<Day5> {
public:
    Day5() : Solution<Day5>(5) {
        process();
    }

    int part1() {
        int sum = 0;

        for (std::vector<int> const& update: updates) {
            // transform this update into an ordering

            bool is_good = [&]() {
                std::unordered_map<int, int> order;
                for (size_t i = 0; i < update.size(); ++i) {
                    order[update[i]] = i;
                }

                for (auto const& [u, v]: edge_list) {
                    if (order.contains(u) && order.contains(v) && order.at(u) > order.at(v)) {
                        return false;
                    }
                }
                return true;
            }();

            if (is_good) {
                sum += update[update.size() / 2];
            }
        }
        return sum;
    }

    int part2() {
        int sum = 0;

        for (std::vector<int> & update: updates) {
            // transform this update into an ordering

            bool is_good = [&]() {
                std::unordered_map<int, int> order;
                for (size_t i = 0; i < update.size(); ++i) {
                    order[update[i]] = i;
                }

                for (auto const& [u, v]: edge_list) {
                    if (order.contains(u) && order.contains(v) && order.at(u) > order.at(v)) {
                        return false;
                    }
                }
                return true;
            }();

            if (!is_good) {
                std::unordered_map<int, int> indegree;
                std::unordered_set<int> update_set {update.begin(), update.end()};

                for (int u : update) {
                    for (int n : adj_list[u]) {
                        if (update_set.contains(n)) {
                           ++indegree[n];
                        }
                    }
                }

                std::queue<int> q;
                std::vector<int> top;

                for (int u : update) {
                    if (indegree[u] == 0) {
                        q.push(u);
                    }
                }

                while (top.size() < update.size()) {
                    int curr = q.front();
                    q.pop();

                    for (int n : adj_list[curr]) {
                        if (update_set.contains(n)) {
                            if(--indegree[n] == 0) {
                                q.push(n);
                            }
                        }
                    }

                    top.push_back(curr);
                }

                sum += top[top.size() / 2];
            }
        }
        return sum;
    }

private:
    // A -> B means that A must happen before B
    std::unordered_map<int, std::unordered_set<int>> adj_list{};
    std::vector<std::pair<int, int>> edge_list{};

    std::vector<std::vector<int>> updates{};

    void process() {
        auto istream = get_input();
        std::string line;

        // first half of input
        while (std::getline(istream, line) && !line.empty()) {
            auto before_after = split(line, '|');
            int before = std::stoi(before_after[0]);
            int after = std::stoi(before_after[1]);

            adj_list[before].insert(after);
            edge_list.emplace_back(before, after);
        }

        // second half
        while (std::getline(istream, line)) {
            auto words = split(line, ',');
            std::vector<int> nums;
            nums.reserve(words.size());
            for (auto const& str: words) {
                nums.push_back(std::stoi(str));
            }
            updates.push_back(nums);
        }

    }
};

