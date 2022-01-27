#include "day2.hpp"

#include <sstream>
#include <string>

namespace day2 {

struct submarine
{
    virtual ~submarine() = default;
    virtual void forward(int value) = 0;
    virtual void down(int value) = 0;
    virtual void up(int value) = 0;

    [[nodiscard]] auto horizontal_position() const -> int
    {
        return horizontal_position_;
    }
    [[nodiscard]] auto depth() const -> int { return depth_; }

  protected:
    int horizontal_position_{ 0 };
    int depth_{ 0 };
};

auto run_commands(submarine& submarine, std::string_view commands) -> int
{
    std::istringstream iss{ std::string{ commands } };
    do {
        std::string command;
        int value;
        iss >> command;
        iss >> value;
        if (command == "forward") {
            submarine.forward(value);
        } else if (command == "down") {
            submarine.down(value);
        } else if (command == "up") {
            submarine.up(value);
        }
    } while (iss.good());
    return submarine.horizontal_position() * submarine.depth();
}

auto part1(std::string_view input) -> int
{
    struct submarine_part1 final : submarine
    {
        void forward(int value) override { horizontal_position_ += value; }
        void down(int value) override { depth_ += value; }
        void up(int value) override { depth_ -= value; }
    } submarine;
    return run_commands(submarine, input);
}

auto part2(std::string_view input) -> int
{
    struct submarine_part2 final : submarine
    {
        void forward(int value) override
        {
            horizontal_position_ += value;
            depth_ += aim_ * value;
        }
        void down(int value) override { aim_ += value; }
        void up(int value) override { aim_ -= value; }

      private:
        int aim_{ 0 };
    } submarine;

    return run_commands(submarine, input);
}

} // namespace day2
