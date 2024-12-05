#pragma once

#include "solution.hpp"

class Day4 : public Solution<Day4> {
public:
    Day4() : Solution<Day4>(4) {}

    void process() {
        auto istream = get_input();
        std::string line;
        while (std::getline(istream, line)) {
            grid.emplace_back(line.begin(), line.end());
        }
        M = grid.size();
        N = grid[0].size();
    }

    int part1() {

        int sum = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                sum += search(i, j);
            }
        }

        return sum;
    }

    int part2() {
        int sum = 0;

        for (int i = 0; i + 2 < M; ++i) {
            for (int j = 0; j + 2 < N; ++j) {


                bool left = (grid[i][j] == 'M'
                             && grid[i + 1][j + 1] == 'A'
                             && grid[i + 2][j + 2] == 'S') ||
                            (grid[i][j] == 'S'
                             && grid[i + 1][j + 1] == 'A'
                             && grid[i + 2][j + 2] == 'M');
                bool right = (grid[i][j + 2] == 'M'
                              && grid[i + 1][j + 1] == 'A'
                              && grid[i + 2][j] == 'S') ||
                             (grid[i][j + 2] == 'S'
                              && grid[i + 1][j + 1] == 'A'
                              && grid[i + 2][j] == 'M');

                if (left && right) ++sum;
            }
        }
        return sum;
    }

private:
    std::vector<std::vector<char>> grid;
    size_t M; // num rows
    size_t N; // num cols

    constexpr static std::string_view XMAS = "XMAS";

    std::vector<std::pair<int, int>> directions = {
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {0,  -1},
            {0,  1},
            {1,  -1},
            {1,  0},
            {1,  1},
    };

    int search(int m, int n) {
        int count = 0;
        for (const auto& dir: directions) {
            int i = m;
            int j = n;
            bool match = [&]() {
                for (int pos = 0; pos < 4; ++pos) {
                    if (i < 0 || j < 0 || i >= M || j >= N) {
                        return false;
                    }
                    if (grid[i][j] != XMAS[pos]) {
                        return false;
                    }
                    i += dir.first;
                    j += dir.second;
                }
                return true;
            }();
            if (match) ++count;
        }
        return count;
    }
};

