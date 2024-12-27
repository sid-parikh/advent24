#pragma once

#include "solution.hpp"
#include <algorithm>

class Day15 : public Solution<Day15> {
public:
    Day15() : Solution<Day15>(15) {
        process();
    }

    size_t part1() {
        auto grid{input};

        auto robot_it = [&]() {
            for (auto const& cell: grid) {
                if (cell.value == '@') {
                    return cell;
                }
            }
            throw std::runtime_error{"no robot found"};
        }();
        size_t r = robot_it.r, c = robot_it.c;

        for (char move: moves) {

            switch (move) {
                case '^': {
                    size_t i = r - 1;
                    while (grid[i, c] == BOX)
                        --i;

                    if (grid[i, c] == WALL) {
                        continue;
                    } else {
                        // move everything up
                        for (; i < r; ++i) {
                            grid[i, c] = grid[i + 1, c];
                        }
                        grid[r, c] = FREE; // robot gone
                        --r; // robot moved up
                    }

                    break;
                }
                case '<': {
                    size_t j = c - 1;
                    while (grid[r, j] == BOX)
                        --j;

                    if (grid[r, j] == WALL) {
                        continue;
                    } else {
                        // move everything left
                        for (; j < c; ++j) {
                            grid[r, j] = grid[r, j + 1];
                        }
                        grid[r, c] = FREE; // robot gone
                        --c; // robot moved left
                    }
                    break;
                }
                case '>': {
                    size_t j = c + 1;
                    while (grid[r, j] == BOX)
                        ++j;

                    if (grid[r, j] == WALL) {
                        continue;
                    } else {
                        // move everything right
                        for (; j > c; --j) {
                            grid[r, j] = grid[r, j - 1];
                        }
                        grid[r, c] = FREE; // robot gone
                        ++c; // robot moved right
                    }
                    break;
                }
                case 'v': {
                    size_t i = r + 1;
                    while (grid[i, c] == BOX)
                        ++i;

                    if (grid[i, c] == WALL) {
                        continue;
                    } else {
                        // move everything down
                        for (; i > r; --i) {
                            grid[i, c] = grid[i - 1, c];
                        }
                        grid[r, c] = FREE; // robot gone
                        ++r; // robot moved down
                    }
                    break;
                }
                default:
                    throw std::runtime_error{"invalid move"};
            }

        }


        size_t sum = 0;
        for (auto const& cell: grid) {
            if (cell.value == BOX) {
                sum += 100 * cell.r + cell.c;
            }
        }

        return sum;
    }

    size_t part2() {
        Grid<char> grid(input.rows(), input.cols() * 2);

        size_t r, c;
        for (auto const& cell: grid) {
            char orig = input[cell.r, cell.c / 2];
            if (orig == BOX) {
                cell.value = (cell.c % 2 == 0) ? '[' : ']';
            } else if (orig == ROBOT) {
                if (cell.c % 2 == 0) {
                    r = cell.r;
                    c = cell.c;
                    cell.value = ROBOT;
                } else {
                    cell.value = FREE;
                }

            } else {
                cell.value = orig;
            }
        }


        for (char move : moves) {
            Grid<char> grid_copy{grid};
            switch (move) {
                case '^': {
                    if (tryMoveVert(r, c, -1, grid_copy)) {
                        grid = std::move(grid_copy);
                        --r;
                    }
                    break;
                }
                case '<': {
                    if (tryMoveHor(r, c, -1, grid_copy)) {
                        grid = std::move(grid_copy);
                        --c;
                    }
                    break;
                }
                case '>': {
                    if (tryMoveHor(r, c, 1, grid_copy)) {
                        grid = std::move(grid_copy);
                        ++c;
                    }
                    break;
                }
                case 'v': {
                    if (tryMoveVert(r, c, 1, grid_copy)) {
                        grid = std::move(grid_copy);
                        ++r;
                    }
                    break;
                }
                default:
                    throw std::runtime_error{"invalid move"};
            }
        }

        size_t sum = 0;
        for (auto const& cell: grid) {
            if (cell.value == '[') {
                sum += 100 * cell.r + cell.c;
            }
        }

        return sum;
    }

private:
    Grid<char> input;
    std::string moves;

    static constexpr char BOX = 'O';
    static constexpr char ROBOT = '@';
    static constexpr char WALL = '#';
    static constexpr char FREE = '.';

    void process() {
        auto istream = get_input();
        std::vector<std::string> lines;
        for (std::string line; std::getline(istream, line);) {
            if (line.empty()) break;
            input.push_row(std::vector<char>(line.begin(), line.end()));
        }
        for (std::string line; std::getline(istream, line);) {
            moves.insert(moves.end(), line.begin(), line.end());
        }
    }

    bool tryMoveVert(size_t r, size_t c, int dr, Grid<char>& grid) {
        if (grid[r, c] == FREE) {
            return true;
        }

        if (grid[r, c] == WALL) {
            return false;
        }

        if (grid[r, c] == ROBOT) {
            if (tryMoveVert(r + dr, c, dr, grid)) {
                grid[{r + dr, c}] = ROBOT;
                grid[{r, c}] = FREE;
                return true;
            } else {
                return false;
            }
        }

        if (grid[r, c] == '[') {
            if (tryMoveVert(r + dr, c, dr, grid) && tryMoveVert(r + dr, c + 1, dr, grid)) {
                grid[{r + dr, c}] = '[';
                grid[{r + dr, c + 1}] = ']';
                grid[{r, c}] = FREE;
                grid[{r, c + 1}] = FREE;
                return true;
            } else {
                return false;
            }
        }

        if (grid[r, c] == ']') {
            if (tryMoveVert(r + dr, c, dr, grid) && tryMoveVert(r + dr, c - 1, dr, grid)) {
                grid[{r + dr, c}] = ']';
                grid[{r + dr, c - 1}] = '[';
                grid[{r, c}] = FREE;
                grid[{r, c - 1}] = FREE;
                return true;
            } else {
                return false;
            }
        }

        throw std::runtime_error{"invalid square"};
    }

    bool tryMoveHor(size_t r, size_t c, int dc, Grid<char>& grid) {
        if (grid[r, c] == FREE) {
            return true;
        }

        if (grid[r, c] == WALL) {
            return false;
        }

        if (grid[r, c] == ROBOT) {
            if (tryMoveHor(r, c + dc, dc, grid)) {
                grid[{r, c + dc}] = ROBOT;
                grid[{r, c}] = FREE;
                return true;
            } else {
                return false;
            }
        }

        if (grid[r, c] == ']' || grid[r, c] == '[') {
            if (tryMoveHor(r, c + dc, dc, grid)) {
                grid[{r, c + dc}] = grid[r, c];
                grid[{r, c}] = FREE;
                return true;
            } else {
                return false;
            }
        }

        throw std::runtime_error{"invalid square"};
    }

};

