#pragma once

#include "lib.hpp"
#include "vec.hpp"

template<typename T>
class PriorityQueueHeap: public IPriorityQueue<T> {
private:
    Vec<Element<T>> vec;

    size_t parent(size_t i) {
        return (i - 1) / 2;
    }

    size_t left(size_t i) {
        return 2 * i + 1;
    }

    size_t right(size_t i) {
        return 2 * i + 2;
    }

    void swap_nodes(size_t i, size_t j) {
        Element<T> temp = vec.get_ref(i)->get();
        vec.swap(i, vec.get_ref(j)->get());
        vec.get_ref(j)->get() = temp;
    }

    void heapify_up(size_t i) {
        while (i > 0) {
            size_t p = parent(i);

            auto curr = vec.get_ref(i)->get();
            auto par  = vec.get_ref(p)->get();

            if (curr.priority <= par.priority) {
                break;
            }

            swap_nodes(i, p);
            i = p;
        }
    }

    void heapify_down(size_t i) {
        size_t n = vec.get_len();

        while (true) {
            size_t l = left(i);
            size_t r = right(i);
            size_t best = i;

            if (
                l < n &&
                vec.get_ref(l)->get().priority >
                vec.get_ref(best)->get().priority) {
                best = l;
            }

            if (
                r < n &&
                vec.get_ref(r)->get().priority >
                vec.get_ref(best)->get().priority) {
                best = r;
            }

            if (best == i) {
                break;
            }

            swap_nodes(i, best);
            i = best;
        }
    }

    PriorityQueueHeap(Vec<Element<T>> v)
        : vec(std::move(v))
    {}

public:
    PriorityQueueHeap()
        : vec(Vec<Element<T>>::init())
    {}

    auto size() -> size_t {
        return vec.get_len();
    }

    auto empty() -> bool {
        return vec.get_len() == 0;
    }

    auto clone() -> PriorityQueueHeap {
        return PriorityQueueHeap(this->vec.clone());
    }

    auto insert(Element<T> value) -> void {
        vec.push_back(value);
        heapify_up(vec.get_len() - 1);
    }

    auto peek() -> std::optional<std::reference_wrapper<Element<T>>> {
        if (vec.get_len() == 0) {
            return std::nullopt;
        }

        return vec.get_ref(0);
    }

    auto remove() -> std::optional<Element<T>> {
        if (vec.get_len() == 0) {
            return std::nullopt;
        }

        Element<T> root = vec.get_ref(0)->get();

        swap_nodes(0, vec.get_len() - 1);
        vec.pop_back();

        if (vec.get_len() != 0) {
            heapify_down(0);
        }

        return root;
    }

    auto change_priority(size_t idx, int new_priority) -> bool {
        if (idx >= vec.get_len()) {
            return false;
        }

        auto elem = vec.get_ref(idx);
        if (!elem) {
            return false;
        }

        int old = elem->get().priority;
        elem->get().priority = new_priority;

        if (new_priority > old) {
            heapify_up(idx);
        } else {
            heapify_down(idx);
        }

        return true;
    }
};
