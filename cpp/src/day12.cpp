#include "day12.hpp"

#include "print.hpp"

#include <sstream>
#include <string>

namespace day12 {
using ::operator<<;

cave::cave(std::string name)
    : name_{ std::move(name) }
{}

void cave::add_connection(const std::string& destination)
{
    connected_caves_.insert(destination);
}

auto cave::name() const -> std::string
{
    return name_;
}

auto cave::is_big_cave() const -> bool
{
    return isupper(name_[0]);
}

auto cave::is_small_cave() const -> bool
{
    return !is_big_cave();
}

auto cave::connected_caves() const -> const std::set<std::string>&
{
    return connected_caves_;
}

std::ostream& operator<<(std::ostream& out, const cave& cave)
{
    return out << "cave { " << cave.name_ << ", " << cave.connected_caves_
               << " }";
}

path::path(std::vector<std::string> path)
    : path_{ std::move(path) }
{}

auto path::contains(const std::string& name) const -> bool
{
    return std::find(path_.begin(), path_.end(), name) != path_.end();
}

void path::add(const std::string& name)
{
    path_.push_back(name);
}

std::ostream& operator<<(std::ostream& out, const path& path)
{
    return out << "path { " << path.path_ << " }";
}

void cave_system::add_connection(const std::string& from, const std::string& to)
{
    const auto add_cave = [&](auto name, auto connected) {
        auto it = caves_.find(name);
        if (it == caves_.end()) {
            it = caves_.insert(it, { name, cave{ name } });
        }
        it->second.add_connection(connected);
    };

    add_cave(from, to);
    add_cave(to, from);
}

void cave_system::find_paths(
    std::vector<path>& all,
    path& current,
    const cave& cave,
    bool revisit) const
{
    if (cave.is_small_cave() && current.contains(cave.name())) {
        if (!revisit || cave.name() == "start") {
            return;
        }
        revisit = false;
    }
    path new_path = current;
    new_path.add(cave.name());
    if (cave.name() == "end") {
        all.push_back(new_path);
        return;
    }
    for (const auto& n : cave.connected_caves()) {
        find_paths(all, new_path, caves_.find(n)->second, revisit);
    }
}

auto cave_system::paths(bool revisit) const -> std::vector<path>
{
    std::vector<path> paths;
    path path{ {} };
    const auto& start = caves_.find("start")->second;
    find_paths(paths, path, start, revisit);
    return paths;
}

std::ostream& operator<<(std::ostream& out, const cave_system& cave_system)
{
    return out << "cave_system { " << cave_system.caves_ << " }";
}

auto parse(std::string_view input) -> cave_system
{
    cave_system result;
    std::istringstream iss{ std::string{ input } };
    std::string line;
    while (std::getline(iss, line)) {
        std::istringstream lss{ line };
        std::string from, to;
        std::getline(lss, from, '-');
        std::getline(lss, to, '-');
        result.add_connection(from, to);
    }
    return result;
}

auto part1(std::string_view input) -> uint64_t
{
    return parse(input).paths().size();
}

auto part2(std::string_view input) -> uint64_t
{
    return parse(input).paths(true).size();
}

} // namespace day12
