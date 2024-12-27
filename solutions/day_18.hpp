#pragma once

#include "solution.hpp"

class Day18 : public Solution<Day18> {
public:
    Day18() : Solution<Day18>(18) {}

    int part1() {
        auto istream = get_input();
        for (std::string line; std::getline(istream, line);) {
            auto nums = split(line, ',');
            bytes.emplace_back(std::stoi(nums[0]), std::stoi(nums[1]));
        }
        Grid<char> grid(SIZE, SIZE, SAFE);
        for (int i = 0; i < 1024; ++i) {
            auto [x, y] = bytes[i];
            grid[y, x] = CORRUPTED;
        }

        // Dijkstras
        using Node = std::tuple<int, int, int>; // cost, r, c
        std::priority_queue < Node > q;
        q.emplace(0, 0, 0);

        Grid<int> distances(SIZE, SIZE, std::numeric_limits<int>::max());
        Grid<char> seen(SIZE, SIZE, false);
        while (!q.empty()) {
            auto [dist, r, c] = q.top();
            q.pop();

            for (auto [dr, dc]: DIRECTIONS) {
                int nr = r + dr, nc = c + dc;
                int n_dist = dist + 1;
                if (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE
                    && grid[nr, nc] == SAFE
                    && n_dist < distances[nr, nc]) {
                    q.emplace(dist + 1, nr, nc);
                    distances[nr, nc] = dist + 1;
                }
            }
        }

        return distances[SIZE-1,SIZE-1];
    }

    std::string part2() {
        Grid<char> grid(SIZE, SIZE, SAFE);
        for (int i = 0; i < 1024; ++i) {
            grid[bytes[i].first, bytes[i].second] = CORRUPTED;
        }

        auto reachable = [&]() -> bool {
            Grid<char> seen(SIZE, SIZE, false);
            std::queue<std::pair<size_t, size_t>> q;
            q.emplace(0, 0);
            seen[0,0]=true;

            while (!q.empty()) {
                auto p = q.front();
                q.pop();

                for (auto [dx, dy] : DIRECTIONS) {
                    size_t x = p.first + dx;
                    size_t y = p.second + dy;
                    if (x >= 0 && y >= 0 && x < SIZE && y < SIZE
                        && seen[x, y] == false
                        && grid[x, y] == SAFE) {
                        if (x == SIZE - 1 && y == SIZE - 1) {
                            return true;
                        }
                        q.emplace(x, y);
                        seen[x, y] = true;
                    }
                }
            }
            return false;
        };

        for (int i = 1024; i < bytes.size(); ++i) {
            grid[bytes[i].first, bytes[i].second] = CORRUPTED;
            if (!reachable()) {
                return std::format("{},{}",bytes[i].first, bytes[i].second);
            }
        }

        return "no solution";
    }

private:
    std::vector<std::pair<int, int>> bytes;

    static constexpr char SAFE{'.'};
    static constexpr char CORRUPTED{'#'};
    static constexpr std::array<std::pair<int, int>, 4> DIRECTIONS{{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};
    static constexpr size_t SIZE = 71;
};

