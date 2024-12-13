#pragma once

#include "solution.hpp"

class Day12 : public Solution<Day12> {
public:
    Day12() : Solution<Day12>(12) {}

    int part1() {
        process();

        int sum = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] != VISITED) {
                    auto [shape, _] = bfs(i, j);

                    int perimeter = 0;
                    for (auto const& [x, y]: shape) {
                        for (auto const& [dx, dy]: DIRECTIONS) {
                            int new_x = x + dx;
                            int new_y = y + dy;
                            if (!shape.contains({new_x, new_y})) {
                                ++perimeter;
                            }
                        }
                    }

                    sum += static_cast<int>(shape.size()) * perimeter;
                }
            }
        }

        return sum;
    }

    long part2() {
        process();

        long sum = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] != VISITED) {
                    auto [shape, border2] = bfs(i, j);

                    int area = static_cast<int>(shape.size());
                    int num_sides = 0;

                    auto expand_vertical = [this](PointSet& p) {
                        int res = 0;
                        while (!p.empty()) {
                            auto it = p.begin();
                            auto [x, y] = *it;
                            p.erase(it);

                            // expand up
                            for (int nx = x - 1; nx >= 0; --nx) {
                                auto maybe_neighbor = p.find({nx, y});
                                if (maybe_neighbor == p.end()) {
                                    break;
                                }
                                p.erase(maybe_neighbor);
                            }

                            // expand down
                            for (int nx = x + 1; nx < M; ++nx) {
                                auto maybe_neighbor = p.find({nx, y});
                                if (maybe_neighbor == p.end()) {
                                    break;
                                }
                                p.erase(maybe_neighbor);
                            }

                            ++res;
                        }
                        return res;
                    };

                    auto expand_horizontal = [this](PointSet& p) {
                        int res = 0;
                        while (!p.empty()) {
                            auto it = p.begin();
                            auto [x, y] = *it;
                            p.erase(it);
                            ++res;

                            // expand left
                            for (int ny = y - 1; ny >= 0; --ny) {
                                auto maybe_neighbor = p.find({x, ny});
                                if (maybe_neighbor == p.end()) {
                                    break;
                                }
                                p.erase(maybe_neighbor);
                            }

                            if (p.empty()) {
                                break;
                            }

                            // expand right
                            for (int ny = y + 1; ny < N; ++ny) {
                                auto maybe_neighbor = p.find({x, ny});
                                if (maybe_neighbor == p.end()) {
                                    break;
                                }
                                p.erase(maybe_neighbor);
                            }

                        }
                        return res;
                    };

                    num_sides += expand_horizontal(border2[UP]);
                    num_sides += expand_horizontal(border2[DOWN]);
                    num_sides += expand_vertical(border2[LEFT]);
                    num_sides += expand_vertical(border2[RIGHT]);


                    sum += area * num_sides;
                }
            }
        }

        return sum;
    }

private:
    struct PairHash {
        static constexpr size_t operator()(const std::pair<int, int>& p) {
            return static_cast<size_t>(p.first) << 32 | static_cast<size_t>(p.second);
        }
    };

    using PointSet = std::unordered_set<std::pair<int, int>, PairHash>;
    using Borders = std::array<PointSet, 4>;

    std::vector<std::vector<char>> grid;
    int N;
    int M;

    std::vector<std::vector<char>> original;

    void process() {
        grid.clear();
        auto istream = get_input();
        for (std::string line; std::getline(istream, line);) {

            std::vector<char> row;
            row.push_back('.');
            row.insert(row.end(), line.begin(), line.end());
            row.push_back('.');

            grid.push_back(std::move(row));
        }
        N = grid[0].size();
        grid.insert(grid.begin(), std::vector<char>(N, '.'));
        grid.emplace_back(N, '.');
        M = grid.size();
        original = grid;
    }

    static constexpr int DIRECTIONS[4][2] = {
            {-1, 0},
            {1,  0},
            {0,  -1},
            {0,  1}
    };

    enum DirEnum {
        UP = 0,
        DOWN,
        LEFT,
        RIGHT
    };

    static constexpr char VISITED = '.';

    std::pair<PointSet, Borders> bfs(int i, int j) {
        char c = grid[i][j];

        std::queue<std::pair<int, int>> q;
        q.emplace(i, j);
        PointSet shape;
        Borders borders;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            if (grid[x][y] != VISITED && !shape.contains({x, y})) {
                shape.emplace(x, y);
                grid[x][y] = VISITED;
                for (const auto idx : {UP, DOWN, LEFT, RIGHT}) {
                    int new_x = x + DIRECTIONS[idx][0];
                    int new_y = y + DIRECTIONS[idx][1];
                    if (new_x >= 0 && new_y >= 0 && new_x < M && new_y < N) {
                        if (original[new_x][new_y] == c){
                            q.emplace(new_x, new_y);
                        } else {
                            borders[idx].emplace(new_x, new_y);
                        }
                    }
                }
            }
        }

        return {shape, borders};
    }

};

