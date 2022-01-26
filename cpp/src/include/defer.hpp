#ifndef AOC_DEFER_HPP
#define AOC_DEFER_HPP

template<typename Function>
struct defer
{
    explicit defer(Function function)
        : function_{ function }
    {}
    ~defer() { function_(); }

  private:
    Function function_;
};

#endif
