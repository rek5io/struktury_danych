#pragma once

#include "lib.hpp"
#include "vec.hpp"

template<typename T>
class PriorityQueueUnsorted: public IPriorityQueue<T> {
private:
    Vec<Element<T>> vec;

    PriorityQueueUnsorted(Vec<Element<T>> v)
        : vec(std::move(v))
    {}

public:
    PriorityQueueUnsorted()
        : vec(Vec<Element<T>>::init())
    {}

    auto size() -> size_t {
        return vec.get_len();
    }

    auto empty() -> bool {
        return vec.get_len() == 0;
    }

    auto clone() -> PriorityQueueUnsorted {
        return PriorityQueueUnsorted(this->vec.clone());
    }

    auto insert(Element<T> value) -> void{
        vec.push_back(value);
    }

    auto peek() -> std::optional<std::reference_wrapper<Element<T>>> {
        if (vec.get_len() == 0) {
            return std::nullopt;
        }

        size_t best_idx = 0;
        auto best = vec.get_ref(0)->get().priority;

        for (size_t i = 1; i < vec.get_len(); i++) {
            auto curr = vec.get_ref(i)->get();

            if (curr.priority > best) {
                best = curr.priority;
                best_idx = i;
            }
        }

        return vec.get_ref(best_idx);
    }

    auto remove() -> std::optional<Element<T>> {
        if (vec.get_len() == 0) {
            return std::nullopt;
        }

        size_t best_idx = 0;
        int best_priority = vec.get_ref(0)->get().priority;

        for (size_t i = 1; i < vec.get_len(); i++) {
            auto curr = vec.get_ref(i)->get();

            if (curr.priority > best_priority) {
                best_priority = curr.priority;
                best_idx = i;
            }
        }

        return vec.remove(best_idx);
    }

    auto change_priority(size_t idx, int new_priority) -> bool {
        if (idx >= vec.get_len()) {
            return false;
        }

        auto elem = vec.get_ref(idx);
        if (!elem) {
            return false;
        }

        elem->get().priority = new_priority;
        return true;
    }
};
