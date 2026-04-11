#pragma once

#include <optional>
#include <functional>
#include <utility>

template<typename T>
class ICollection {
    public:
        virtual auto get_len() -> size_t = 0;
        virtual auto is_empty() -> bool = 0;
        virtual auto push_back(T value) -> void = 0;
        virtual auto push_front(T value) -> void = 0;
        virtual auto pop_back() -> std::optional<T> = 0;
        virtual auto pop_front() -> std::optional<T> = 0;
        virtual auto get_ref_back() -> std::optional<std::reference_wrapper<T>> = 0;
        virtual auto get_ref_front() -> std::optional<std::reference_wrapper<T>> = 0;
        virtual auto get_ref(size_t idx) -> std::optional<std::reference_wrapper<T>> = 0;
        virtual auto remove(size_t idx) -> std::optional<T> = 0;
        virtual auto insert(size_t idx, T value) -> std::optional<T> = 0;
        virtual auto swap(size_t idx, T& swap) -> bool = 0;
        virtual auto search(std::function<bool(T&)> predicate) -> std::optional<size_t> = 0;
        virtual auto clear() -> void = 0;
        virtual ~ICollection() = default;
};
