#pragma once

#include "solution.hpp"
#include <unordered_map>

class Day8 : public Solution<Day8> {
public:
    Day8() : Solution<Day8>(8) {}

    int part1() {
        process();
        int res = 0;

        for (auto const& [c, locs] : nodes) {
            // all pairs of locs
            for (auto [x1, y1] : locs) {
                for (auto [x2, y2] : locs) {

                    if (x1 == x2 && y1 == y2) continue;

                    int diff_x = x2 - x1;
                    int diff_y = y2 - y1;

                    int anti_x1 = x2 + diff_x;
                    int anti_y1 = y2 + diff_y;
                    int anti_x2 = x1 - diff_x;
                    int anti_y2 = y1 - diff_y;

                    if (anti_x1 >= 0 && anti_x1 < M && anti_y1 >= 0 && anti_y1 < N && grid[anti_x1][anti_y1] != '#') {
                        ++res;
                        grid[anti_x1][anti_y1] = '#';
                    }
                    if (anti_x2 >= 0 && anti_x2 < M && anti_y2 >= 0 && anti_y2 < N && grid[anti_x2][anti_y2] != '#') {
                        ++res;
                        grid[anti_x2][anti_y2] = '#';
                    }
                }
            }
        }


        return res;
    }

    int part2() {
        process();
        int res = 0;

        for (auto const& [c, locs] : nodes) {
            // all pairs of locs
            for (auto [x1, y1] : locs) {
                for (auto [x2, y2] : locs) {

                    if (x1 == x2 && y1 == y2) continue;

                    int diff_x = x2 - x1;
                    int diff_y = y2 - y1;

                    int anti_x = x2;
                    int anti_y = y2;

                    while(anti_x >= 0 && anti_x < M && anti_y >= 0 && anti_y < N){
                        if (grid[anti_x][anti_y] != '#') {
                            ++res;
                            grid[anti_x][anti_y] = '#';
                        }
                        anti_x += diff_x;
                        anti_y += diff_y;
                    }

                    anti_x = x1;
                    anti_y = y1;

                    while(anti_x >= 0 && anti_x < M && anti_y >= 0 && anti_y < N){
                        if (grid[anti_x][anti_y] != '#') {
                            ++res;
                            grid[anti_x][anti_y] = '#';
                        }
                        anti_x -= diff_x;
                        anti_y -= diff_y;
                    }
                }
            }
        }

        return res;
    }

private:

    std::vector<std::vector<char>> grid;
    std::unordered_map<char, std::vector<std::pair<int, int>>> nodes;
    int M;
    int N;

    void process() {
        grid.clear();
        nodes.clear();
        auto istream = get_input();
        for (std::string line; std::getline(istream, line);) {
            grid.emplace_back(line.begin(), line.end());

            size_t i = grid.size() - 1;
            for (size_t j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] != '.') {
                    nodes[grid[i][j]].emplace_back(i, j);
                }
            }
        }

        M = grid.size();
        N = grid[0].size();
    }
};

