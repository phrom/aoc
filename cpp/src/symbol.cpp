#include "symbol.hpp"

#include <iostream>

std::unordered_map<std::string, uint64_t> symbol::string_to_handle_;
std::vector<std::string_view> symbol::handle_to_string_;

symbol::symbol(std::string string)
{
    auto it = string_to_handle_.find(string);
    if (it == string_to_handle_.end()) {
        it = string_to_handle_.insert(
            it, { std::move(string), handle_to_string_.size() });
        handle_to_string_.push_back(it->first);
    }
    symbol_ = it->second;
}

auto symbol::to_str() const -> std::string
{
    return std::string{ handle_to_string_[symbol_] };
}

std::ostream& operator<<(std::ostream& out, const symbol& symbol)
{
    return out << symbol.to_str();
}
