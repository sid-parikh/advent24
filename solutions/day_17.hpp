#pragma once

#include "solution.hpp"

class Day17 : public Solution<Day17> {
public:
    Day17() : Solution<Day17>(17) {}

    std::string part1() {

        while (comp.ip + 1 < PROGRAM.size()) {
            int opcode = PROGRAM[comp.ip];
            int operand = PROGRAM[comp.ip + 1];
            comp.ip += 2;
            ops[opcode](operand);
        }

        return format_output();
    }

    static long part2() {
        std::vector<long> possible_a = {
                0, 1, 2, 3, 4, 5, 6, 7
        };
        for (int i = 15; i >= 0; --i) {
            std::vector<long> new_pa;
            for (long a : possible_a) {
                long min = a * 8;
                long max = (a + 1) * 8;

                for (long n = min; n < max; ++n) {
                    // program
                    long b = n % 8;
                    b ^= 1lu;
                    long c = n / (1 << b);
                    b ^= c;
                    b ^= 6lu;

                    if ((b % 8) == PROGRAM[i]) {
                        new_pa.push_back(n);
                    }
                }
            }
            possible_a = new_pa;
            if (possible_a.empty()) {
                throw std::runtime_error{std::format("no solution found for i {}", i)};
            }
        }

        long result = *std::min(possible_a.begin(), possible_a.end());
        return result;
    }

private:


    static constexpr std::array<int, 16> PROGRAM = {
            2, 4, 1, 1, 7, 5, 0, 3, 4, 3, 1, 6, 5, 5, 3, 0
    };

    struct {
        long a = 18427963;
        long b = 0;
        long c = 0;
        long ip = 0;
        std::vector<int> out;
    } comp;

    [[nodiscard]] long combo(int op) const {
        switch (op) {
            case 4:
                return comp.a;
            case 5:
                return comp.b;
            case 6:
                return comp.c;
            default:
                return op;
        }
    }

    void adv(int op) {
        comp.a /= static_cast<long>(std::pow(2, combo(op)));
    }

    void bxl(int op) {
        comp.b ^= op; // literal op
    }

    void bst(int op) {
        comp.b = combo(op) % 8;
    }

    void jnz(int op) {
        if (comp.a != 0) {
            comp.ip = op;
        }
    }

    void bxc([[maybe_unused]] int op) {
        comp.b = comp.b ^ comp.c;
    }

    void out(int op) {
        comp.out.push_back(static_cast<int>(combo(op) % 8));
    }

    void bdv(int op) {
        comp.b = comp.a / static_cast<long>(std::pow(2, combo(op)));
    }

    void cdv(int op) {
        comp.c = comp.a / static_cast<long>(std::pow(2, combo(op)));
    }

    const std::function<void(long)> ops[8] = {
            [this](int op) { adv(op); },
            [this](int op) { bxl(op); },
            [this](int op) { bst(op); },
            [this](int op) { jnz(op); },
            [this](int op) { bxc(op); },
            [this](int op) { out(op); },
            [this](int op) { bdv(op); },
            [this](int op) { cdv(op); }
    };

    std::string format_output() {
        std::ostringstream ss;
        ss << comp.out[0];
        for (int i = 1; i < comp.out.size(); ++i) {
            ss << ',' << comp.out[i];
        }
        return ss.str();
    }

};

