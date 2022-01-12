#include "day4.hpp"

#include <set>
#include <sstream>
#include <string>

namespace day4 {

auto parse(std::string_view input) -> game
{
    game game;
    std::istringstream iss{ std::string{ input } };
    std::string line;
    std::getline(iss, line);
    std::istringstream split{ line };
    while (!split.eof()) {
        int number;
        char comma;
        split >> number >> comma;
        game.numbers.push_back(number);
    }
    do {
        game.boards.push_back({});
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                iss >> game.boards.back()[i][j];
            }
        }
    } while (!iss.eof());
    game.boards.erase(game.boards.end() - 1);
    return game;
}

auto bingo(const board& board, const std::set<int>& numbers_drawn) -> bool
{
    for (int row = 0; row < 5; ++row) {
        for (int column = 0; column < 5; ++column) {
            if (!numbers_drawn.contains(board[row][column])) {
                goto next_row;
            }
        }
        return true;
    next_row:;
    }
    for (int column = 0; column < 5; ++column) {
        for (int row = 0; row < 5; ++row) {
            if (!numbers_drawn.contains(board[row][column])) {
                goto next_column;
            }
        }
        return true;
    next_column:;
    }
    return false;
}

auto score(const board& board, const std::set<int>& numbers_drawn) -> int
{
    int score = 0;
    for (int row = 0; row < 5; ++row) {
        for (int column = 0; column < 5; ++column) {
            if (!numbers_drawn.contains(board[row][column])) {
                score += board[row][column];
            }
        }
    }
    return score;
}

auto part1(std::string_view input) -> int
{
    game game = parse(input);
    std::set<int> numbers_drawn;
    for (int number : game.numbers) {
        numbers_drawn.insert(number);
        if (numbers_drawn.size() > 5) {
            for (const auto& board : game.boards) {
                if (bingo(board, numbers_drawn)) {
                    return score(board, numbers_drawn) * number;
                }
            }
        }
    }
    return 0;
}

auto part2(std::string_view input) -> int
{
    return 0;
}

} // namespace day4
