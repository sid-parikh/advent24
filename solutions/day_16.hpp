#pragma once

#include "solution.hpp"
#include <unordered_set>

class Day16 : public Solution<Day16> {
public:
    Day16() : Solution<Day16>(16) {}

    int part1() {
        process();

        auto [s_i, s_j] = start;
        auto [e_i, e_j] = end;

        auto [cost, _] = dijkstras(s_i, s_j, EAST);

        auto& target = cost[e_i][e_j];
        int res = *std::min(target.begin(), target.end());
        max_cost = res;

        return res;
    }

    size_t part2() {
        auto [s_i, s_j] = start;
        auto [e_i, e_j] = end;

        auto [startCost, _4] = dijkstras(s_i, s_j, EAST);
        auto [endCost1, _0] = dijkstras(e_i, e_j, WEST, true);
        auto [endCost2, _1] = dijkstras(e_i, e_j, SOUTH, true);
        auto [endCost3, _2] = dijkstras(e_i, e_j, NORTH, true);
        auto [endCost4, _3] = dijkstras(e_i, e_j, EAST, true);

        std::vector<std::vector<bool>> seen(ROWS, std::vector<bool>(COLS, false));

        int res = 0;
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                for (int k = 0; k < 4; ++k) {
                    long sc = startCost[i][j][k];
                    long ec = std::min(std::min(endCost1[i][j][k], endCost2[i][j][k]),
                                      std::min(endCost3[i][j][k], endCost4[i][j][k]));

                    if (sc + ec <= max_cost) {
                        if (!seen[i][j]) {
                            ++res;
                            grid[i][j] = 'O';
                            seen[i][j] = true;
                        }
                    }
                }
            }
        }

        return 1+res;
    }

private:
    std::vector<std::string> grid;
    std::pair<int, int> start;
    std::pair<int, int> end;
    int ROWS;
    int COLS;
    int max_cost;

    enum Direction {
        NORTH = 0, EAST, SOUTH, WEST
    };

    static constexpr Direction RIGHT[] = {
            // clockwise 90-degrees
            EAST, // north
            SOUTH, // east
            WEST, // south
            NORTH, // west
    };

    static constexpr Direction LEFT[] = {
            // counter-clockwise 90-degrees
            WEST, // north
            NORTH, // east
            EAST, // east
            SOUTH, // west
    };

    static constexpr int DIRS[4][2] = {{-1, 0}, // north
                                       {0,  1}, // east
                                       {1,  0}, // south
                                       {0,  -1} // west
    };

    void process() {
        grid.clear();
        auto istream = get_input();
        for (std::string line; std::getline(istream, line);) {
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == 'S') {
                    start = {grid.size(), i};
                } else if (line[i] == 'E') {
                    end = {grid.size(), i};
                }
            }
            grid.push_back(std::move(line));
        }
        ROWS = static_cast<int>(grid.size());
        COLS = static_cast<int>(grid[0].size());
    }

    struct queue_entry {
        int cost;
        int r;
        int c;
        Direction d;
    };

    struct queue_entry_compare {
        static bool operator()(queue_entry const& a, queue_entry const& b) {
            return a.cost > b.cost;
        }
    };

    static std::vector<queue_entry> get_neighbors(queue_entry const& node, bool flip = false) {
        return {{node.cost + 1,    node.r + (flip ? -1 : 1) * DIRS[node.d][0], node.c + (flip ? -1 : 1) * DIRS[node.d][1], node.d},
                {node.cost + 1000, node.r,                   node.c,                   RIGHT[node.d]},
                {node.cost + 1000, node.r,                   node.c,                   LEFT[node.d]}};
    }

    using Point = std::tuple<int, int, Direction>;
    using CostGrid = std::vector<std::vector<std::vector<int>>>;
    using PrevGrid = std::vector<std::vector<std::vector<Point>>>;

    std::pair<CostGrid, PrevGrid> dijkstras(int r, int c, Direction d, bool flip = false) {
        std::priority_queue<queue_entry, std::vector<queue_entry>, queue_entry_compare> q;
        q.push({0, r, c, d});

        int INFTY = std::numeric_limits<int>::max();
        CostGrid cost(ROWS, std::vector<std::vector<int>>(COLS, std::vector<int>(4, INFTY)));
        PrevGrid prev(ROWS, std::vector<std::vector<Point>>(COLS, std::vector<Point>(4, {-1, -1, EAST})));
        std::vector<std::vector<std::vector<bool>>> seen(ROWS, std::vector<std::vector<bool>>(COLS, std::vector<bool>(4,
                                                                                                                      false)));

        while (!q.empty()) {
            auto node = q.top();
            q.pop();

            for (auto const& n: get_neighbors(node, flip)) {
                if (!seen[n.r][n.c][n.d] && n.cost < cost[n.r][n.c][n.d] && grid[n.r][n.c] != '#') {
                    q.push(n);
                    cost[n.r][n.c][n.d] = n.cost;
                    prev[n.r][n.c][n.d] = {n.r, n.d, n.d};
                }
            }
        }

        return {cost, prev};
    }

};

