#pragma once

#include "lib.hpp"
#include "vec.hpp"

template<typename T>
class PriorityQueueSorted: public IPriorityQueue<T> {
private:
    Vec<Element<T>> vec;

    PriorityQueueSorted(Vec<Element<T>> v)
        : vec(std::move(v))
    {}

public:
    PriorityQueueSorted()
        : vec(Vec<Element<T>>::init())
    {}

    auto size() -> size_t {
        return vec.get_len();
    }

    auto empty() -> bool {
        return vec.get_len() == 0;
    }

    auto clone() -> PriorityQueueSorted {
        return PriorityQueueSorted(this->vec.clone());
    }

    auto insert(Element<T> value) -> void {
        size_t i = 0;

        while (i < vec.get_len()) {
            auto curr = vec.get_ref(i)->get();

            if (value.priority < curr.priority) {
                break;
            }

            i++;
        }

        vec.insert(i, value);
    }

    auto peek() -> std::optional<std::reference_wrapper<Element<T>>> {
        if (vec.get_len() == 0) {
            return std::nullopt;
        }

        return vec.get_ref(vec.get_len() - 1);
    }

    auto remove() -> std::optional<Element<T>> {
        if (vec.get_len() == 0) {
            return std::nullopt;
        }

        return vec.remove(vec.get_len() - 1);
    }

    auto change_priority(size_t idx, int new_priority) -> bool {
        if (idx >= vec.get_len()) {
            return false;
        }

        Element<T> temp = vec.get_ref(idx)->get();
        vec.remove(idx);

        temp.priority = new_priority;
        insert(temp);

        return true;
    }
};
