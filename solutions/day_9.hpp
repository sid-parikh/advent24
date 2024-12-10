#pragma once

#include "solution.hpp"
#include <list>
#include <map>
#include <ranges>

class Day9 : public Solution<Day9> {
public:
    Day9() : Solution<Day9>(9) {}

    long part1() {
        build_fs();
        reorder_fs();
        return checksum();
    }

    long part2() {
        build_fs();
        for (auto & file : std::ranges::reverse_view(files_list)) {

            for (auto& [loc, free_space] : free_list) {

                if (loc > file.loc) {
                    break;
                }

                if (free_space.size > file.size) {

                    for (int i = 0; i < file.size; ++i) {
                        fs[file.loc + i] = -1;
                        fs[loc + i] = file.id;
                    }


                    int new_loc = loc + file.size;
                    int new_size = free_space.size - file.size;

                    free_list.erase(loc);
                    free_list[new_loc] = {new_size};

                    break;
                } else if (free_space.size == file.size) {

                    for (int i = 0; i < file.size; ++i) {
                        fs[file.loc + i] = -1;
                        fs[loc + i] = file.id;
                    }

                    free_list.erase(loc);
                    break;
                }
            }
        }

        return checksum();
    }

private:
    std::string input;
    std::vector<int> fs;

    struct free_item {
        int size;
    };

    struct file {
        int id;
        int size;
        int loc;
    };

    std::map<int, free_item> free_list;
    std::vector<file> files_list;

    void build_fs() {
        fs.clear();
        free_list.clear();
        files_list.clear();

        auto istream = get_input();
        std::getline(istream, input);

        fs.reserve(5 * input.size());
        int id = 0;
        for (size_t i = 0; i < input.size(); i++) {
            if (i % 2 == 0) {
                // file
                int file_size = input[i] - '0';

                files_list.push_back({id, file_size, static_cast<int>(fs.size())});

                for (; file_size > 0; --file_size) {
                    fs.push_back(id);
                }
                ++id;

            } else {
                // free space
                int free_size = input[i] - '0';
                free_list[fs.size()] = {free_size};
                for (; free_size > 0; --free_size) {
                    fs.push_back(-1);
                }
            }
        }
    }

    void print_fs() {
        for (int n: fs) {
            if (n == -1) {
                std::cout << '.';
            } else {
                std::cout << n;
            }
        }
        std::cout << std::endl;
    }

    void reorder_fs() {
        size_t l = 0;
        size_t r = fs.size() - 1;

        while (l < r) {
            while (l < r && fs[r] == -1) {
                --r;
            }

            while (l < r && fs[l] != -1) {
                ++l;
            }

            std::swap(fs[l], fs[r]);
            ++l;
            --r;
        }
    }

    long checksum() {
        long res = 0;
        for (int i = 0; i < fs.size(); ++i) {
            int n = fs[i];
            if (n == -1) continue;

            res += n * i;
        }

        return res;
    }
};
