#pragma once

#include "solution.hpp"

class Day10 : public Solution<Day10> {
public:
    Day10() : Solution<Day10>(10) {}

    int part1() {
        build_grid();

        int sum = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == 0) {
                    auto copy{grid};
                    sum += bfs(i, j);
                    grid = copy;
                }
            }
        }

        return sum;
    }

    int part2() {
        build_grid();

        int sum = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == 0) {
                    auto copy{grid};
                    sum += backtrack(i, j, 0);
                    grid = copy;
                }
            }
        }

        return sum;
    }

private:
    std::vector<std::vector<int>> grid;
    int M;
    int N;

    void build_grid() {
        grid.clear();
        auto istream = get_input();
        for (std::string line; std::getline(istream, line);) {
            grid.emplace_back();
            for (char c: line) {
                grid.back().push_back(c - '0');
            }
        }
        M = grid.size();
        N = grid[0].size();
    }

    static constexpr std::pair<int, int> directions[4] = {
        {0, -1},
        {0, 1},
        {-1, 0},
        {1, 0}
    };

    int bfs(int i, int j) {
        // add all neighboring 1s

        std::queue<std::pair<int, int>> q{};
        q.emplace(i, j);
        for (int val = 1; val <= 9; ++val) {

            for (size_t sz = q.size(); sz > 0; --sz) {
                auto [x, y] = q.front();
                q.pop();
                for (auto& [dx, dy] : directions) {
                    int new_x = x + dx;
                    int new_y = y + dy;
                    if (new_x >= 0 && new_y >= 0 && new_x < M && new_y < N && grid[new_x][new_y] == val) {
                        q.emplace(new_x, new_y);
                        grid[new_x][new_y] = -1;
                    }
                }
            }

        }

        return static_cast<int>(q.size());
    }

    int backtrack(int i, int j, int val) {
        if (i < 0 || j < 0 || i >= M || j >= N || grid[i][j] != val) {
            return 0;
        }

        if (val == 9) {
            return 1;
        }

        int sum = 0;
        for (auto const& [dx, dy] : directions) {
            int new_x = i + dx;
            int new_y = j + dy;
            if (new_x >= 0 && new_y >= 0 && new_x < M && new_y < N) {
                grid[i][j] = -1;
                sum += backtrack(new_x, new_y, val + 1);
                grid[i][j] = val;
            }
        }

        return sum;
    }

};

