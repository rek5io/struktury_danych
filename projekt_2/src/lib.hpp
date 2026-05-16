#pragma once

#include <optional>
#include <print>

template<typename T>
struct Element {
    T value;
    int priority;
};

template<typename T>
class IPriorityQueue {
public:
    virtual auto size() -> size_t = 0;
    virtual auto empty() -> bool = 0;
    virtual auto insert(Element<T> value) -> void = 0;
    virtual auto peek() -> std::optional<std::reference_wrapper<Element<T>>> = 0;
    virtual auto remove() -> std::optional<Element<T>> = 0;
    virtual auto change_priority(size_t idx, int new_priority) -> bool = 0;
    virtual ~IPriorityQueue() = default;
};
