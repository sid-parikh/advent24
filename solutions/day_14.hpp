#pragma once

#include "solution.hpp"
#include <numeric>

class Day14 : public Solution<Day14> {
public:
    Day14() : Solution<Day14>(14) {}

    int part1() {
        process();

        std::vector<std::vector<int>> grid(maxY, std::vector<int>(maxX, 0));
        for (Pose& r: robots) {

            Point final_pos;
            if (r.vel.x < 0) {
                r.pos.x = maxX - 1 - r.pos.x;
                r.vel.x *= -1;
                final_pos.x = (r.pos.x + 100 * r.vel.x) % maxX;
                final_pos.x = maxX - 1 - final_pos.x;
            } else {
                final_pos.x = (r.pos.x + 100 * r.vel.x) % maxX;
            }

            if (r.vel.y < 0) {
                r.pos.y = maxY - 1 - r.pos.y;
                r.vel.y *= -1;
                final_pos.y = (r.pos.y + 100 * r.vel.y) % maxY;
                final_pos.y = maxY - 1 - final_pos.y;
            } else {
                final_pos.y = (r.pos.y + 100 * r.vel.y) % maxY;
            }

            r.pos = final_pos;

            ++grid[r.pos.y][r.pos.x];
        }

        // quadrants
        int quadrants[4] = {0, 0, 0, 0};
        for (int i = 0; i < maxX / 2; ++i) {
            for (int j = 0; j < maxY / 2; ++j) {
                quadrants[0] += grid[j][i];
            }
        }
        for (int i = maxX / 2 + 1; i < maxX; ++i) {
            for (int j = 0; j < maxY / 2; ++j) {
                quadrants[1] += grid[j][i];
            }
        }
        for (int i = 0; i < maxX / 2; ++i) {
            for (int j = maxY / 2 + 1; j < maxY; ++j) {
                quadrants[2] += grid[j][i];
            }
        }
        for (int i = maxX / 2 + 1; i < maxX; ++i) {
            for (int j = maxY / 2 + 1; j < maxY; ++j) {
                quadrants[3] += grid[j][i];
            }
        }


        return quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3];
    }

    int part2() {

        process();
        std::vector<std::vector<int>> templ(maxY, std::vector<int>(maxX, 0));
        auto grid{templ};

        std::vector<std::vector<int>> result;
        int min = std::numeric_limits<int>::max();

        for (int iter = 1; iter <= maxX * maxY; ++iter) {
            grid = templ;
            for (Pose& r: robots) {
                r.pos = {
                        (r.pos.x + r.vel.x + maxX) % maxX,
                        (r.pos.y + r.vel.y + maxY) % maxY
                };

                ++grid[r.pos.y][r.pos.x];
            }

            int quadrants[4] = {0, 0, 0, 0};
            for (int i = 0; i < maxX / 2; ++i) {
                for (int j = 0; j < maxY / 2; ++j) {
                    quadrants[0] += grid[j][i];
                }
            }
            for (int i = maxX / 2 + 1; i < maxX; ++i) {
                for (int j = 0; j < maxY / 2; ++j) {
                    quadrants[1] += grid[j][i];
                }
            }
            for (int i = 0; i < maxX / 2; ++i) {
                for (int j = maxY / 2 + 1; j < maxY; ++j) {
                    quadrants[2] += grid[j][i];
                }
            }
            for (int i = maxX / 2 + 1; i < maxX; ++i) {
                for (int j = maxY / 2 + 1; j < maxY; ++j) {
                    quadrants[3] += grid[j][i];
                }
            }

            int res = quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3];
            if (res < min) {
                min = res;
                std::cout << "iter " << iter << std::endl;
                print_grid(grid);
                std::cin.get();
            }

        }

//        print_grid(result);

        return 1;
    }

private:
    struct Point {
        int x;
        int y;
    };

    struct Pose {
        Point pos;
        Point vel;
    };

    std::vector<Pose> robots;
    constexpr static int maxX = 101;
    constexpr static int maxY = 103;

    void process() {
        robots.clear();
        auto istream = get_input();
        for (std::string line; std::getline(istream, line);) {
            auto splt = split(line, ' ');
            robots.push_back({
                                     {std::stoi(splt[0]), std::stoi(splt[1])},
                                     {std::stoi(splt[2]), std::stoi(splt[3])}
                             });
        }
    }

    void print_grid(std::vector<std::vector<int>>& grid) {
        for (auto const& row: grid) {
            for (int n: row) {
                if (n == 0) std::cout << ' ';
                else std::cout << n;
            }
            std::cout << std::endl;
        }
    }

    bool equ(int a, int b) {
        constexpr double tolerance = 1.1;

        if (std::abs(a - b) < tolerance * a) {
            return true;
        }
        return false;
    }

};

