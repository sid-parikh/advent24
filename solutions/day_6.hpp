#pragma once

#include "solution.hpp"
#include <set>

class Day6 : public Solution<Day6> {
public:
    Day6() : Solution<Day6>(6) {}

    int part1() {

        process();



        int guard_i = start_i, guard_j = start_j;
        grid[start_i][start_j] = FREE;

        std::set<std::pair<int, int>> visited;

        visited.emplace(guard_i, guard_j);
        int d = 0;
        while (guard_i >= 0 && guard_j >= 0 && guard_i < M && guard_j < N) {
            int new_i = guard_i + directions[d].first;
            int new_j = guard_j + directions[d].second;

            if (new_i < 0 || new_j < 0 ||new_i >= M || new_j >= N) {
                break;
            }

            while (grid[new_i][new_j] != FREE) {
                d = (d + 1) % 4;
                new_i = guard_i + directions[d].first;
                new_j = guard_j + directions[d].second;
                if (new_i < 0 || new_j < 0 || new_i >= M || new_j >= N) {
                    break;
                }
            }
            if (new_i < 0 || new_j < 0 || new_i >= M || new_j >= N) {
                break;
            }

            guard_i = new_i;
            guard_j = new_j;
            visited.emplace(guard_i, guard_j);
        }


        grid[start_i][start_j] = GUARD;
        return visited.size();
    }

    bool detect_cycle() {
        std::set<std::tuple<int, int, int>> visited;

        int guard_i = start_i, guard_j = start_j;
        grid[start_i][start_j] = FREE;

        visited.insert({guard_i, guard_j, 0});
        int d = 0;
        while (guard_i >= 0 && guard_j >= 0 && guard_i < M && guard_j < N) {
            int new_i = guard_i + directions[d].first;
            int new_j = guard_j + directions[d].second;

            if (new_i < 0 || new_j < 0 ||new_i >= M || new_j >= N) {
                break;
            }

            while (grid[new_i][new_j] != FREE) {
                d = (d + 1) % 4;
                new_i = guard_i + directions[d].first;
                new_j = guard_j + directions[d].second;
                if (new_i < 0 || new_j < 0 || new_i >= M || new_j >= N) {
                    break;
                }
            }
            if (new_i < 0 || new_j < 0 || new_i >= M || new_j >= N) {
                break;
            }

            guard_i = new_i;
            guard_j = new_j;
            if (visited.contains({guard_i, guard_j, d})) {
                return true;
            }
            visited.insert({guard_i, guard_j, d});

        }



        return false;
    }

    int part2() {
        process();
        int sum = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == FREE) {
                    grid[i][j] = BLOCKED;
                    if (detect_cycle()) {
                        ++sum;
                    }
                    grid[start_i][start_j] = GUARD;
                    grid[i][j] = FREE;
                }
            }
        }
        return sum;
    }

private:

    constexpr static char FREE{'.'};
    constexpr static char BLOCKED{'#'};
    constexpr static char GUARD{'^'};

    std::vector<std::pair<int, int>> directions = {
            {-1, 0},
            {0, 1},
            {1, 0},
            {0, -1}
    };

    int M;
    int N;
    int start_i;
    int start_j;

    std::vector<std::vector<char>> grid{};

    void process() {
        grid.clear();
        auto istream = get_input();
        std::string line;
        while (std::getline(istream, line)) {
            grid.emplace_back(line.begin(), line.end());
        }

        M = grid.size();
        N = grid[0].size();

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == GUARD) {
                    start_i = i;
                    start_j = j;
                }
            }
        }
    }
};

