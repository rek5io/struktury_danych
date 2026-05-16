#include "lib.hpp"
#include "unsorted.hpp"
#include "sorted.hpp"
#include "heap.hpp"

#include <chrono>
#include <cstddef>
#include <optional>
#include <vector>
#include <random>

auto randgen(int min, int max) -> int {
    static std::mt19937 rnd(time(nullptr));
    return std::uniform_int_distribution<>(min, max)(rnd);
}

auto randint() -> int {
    return randgen(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

template<typename PQ>
void test_priority_queue(const char* name) {
    std::println("\n====================");
    std::println("TEST: {}", name);
    std::println("====================");

    PQ pq;

    std::println("\n== INSERT + PEEK ==");
    pq.insert({1, 10});
    pq.insert({2, 30});
    pq.insert({3, 20});

    auto top = pq.peek();

    if (top && top->get().priority == 30) {
        std::println("[OK] peek works");
    } else {
        std::println("[FAIL] peek wrong");
    }

    std::println("\n== REMOVE ORDER ==");

    pq.insert({4, 50});
    pq.insert({5, 40});

    int last = 100000;
    bool ok = true;

    while (!pq.empty()) {
        auto x = pq.remove();
        std::println("{}", x->priority);

        if (x->priority > last) {
            ok = false;
        }

        last = x->priority;
    }

    if (ok) {
        std::println("[OK] remove order correct");
    } else {
        std::println("[FAIL] order broken");
    }

    std::println("\n== CHANGE PRIORITY ==");

    pq.insert({1, 10});
    pq.insert({2, 20});
    pq.insert({3, 30});

    pq.change_priority(0, 100);

    if (pq.peek()->get().priority == 100) {
        std::println("[OK] change_priority works");
    } else {
        std::println("[FAIL] change_priority broken");
    }

    std::println("\n== STRESS TEST ==");

    PQ stress;

    for (int i = 0; i < 100; i++) {
        stress.insert({i, rand() % 1000});
    }

    last = 100000;
    ok = true;

    while (!stress.empty()) {
        auto x = stress.remove();

        if (x->priority > last) {
            ok = false;
        }

        last = x->priority;
    }

    if (ok) {
        std::println("[OK] stress test passed");
    } else {
        std::println("[FAIL] stress test broken");
    }
}


namespace benchmark {
    template<template<typename> class T>
    auto bench(size_t *sizes, size_t sizes_count, size_t runs_count) -> void {
        long took = 0;

        for (size_t s = 0; s < sizes_count; s++) {
            int size = sizes[s];

            auto q = T<int>();

            for (int i = 0; i < size; i++) {
                q.insert(Element{i, randint()});
            }

            int priority = size / 2;
            int value = priority;

            for (size_t c = 0; c < runs_count; c++) {
                auto q2 = q.clone();
                auto start = std::chrono::high_resolution_clock::now();
                q2.insert(Element{value, priority});
                auto end = std::chrono::high_resolution_clock::now();

                took += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }

            std::println("insert {} {}", size, took / runs_count);
            took = 0;
        }

        for (size_t s = 0; s < sizes_count; s++) {
            int size = sizes[s];

            auto q = T<int>();

            for (int i = 0; i < size; i++) {
                q.insert(Element{i, randint()});
            }

            int v = 0;

            for (size_t c = 0; c < runs_count; c++) {
                auto q2 = q.clone();
                auto start = std::chrono::high_resolution_clock::now();
                v = q2.remove().value().priority;
                auto end = std::chrono::high_resolution_clock::now();

                took += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }

            std::println("remove {} {}, pri: {}", size, took / runs_count, v);
            took = 0;
        }

        for (size_t s = 0; s < sizes_count; s++) {
            int size = sizes[s];

            auto q = T<int>();

            for (int i = 0; i < size; i++) {
                q.insert(Element{i, randint()});
            }

            int p = 0;

            for (size_t c = 0; c < runs_count; c++) {
                auto q2 = q.clone();
                auto start = std::chrono::high_resolution_clock::now();
                p = q2.peek().value().get().priority;
                auto end = std::chrono::high_resolution_clock::now();

                took += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }

            std::println("peek {} {} pri: {}", size, took / runs_count, p);
            took = 0;
        }

        for (size_t s = 0; s < sizes_count; s++) {
            int size = sizes[s];

            auto q = T<int>();

            for (int i = 0; i < size; i++) {
                q.insert(Element{i, randint()});
            }

            int t_pri = std::numeric_limits<int>::min();

            for (size_t c = 0; c < runs_count; c++) {
                auto q2 = q.clone();
                auto start = std::chrono::high_resolution_clock::now();
                q2.change_priority(size - 1, t_pri);
                auto end = std::chrono::high_resolution_clock::now();

                took += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }

            std::println("change {} {}", size, took / runs_count);
            took = 0;
        }
    }
}

auto main() -> int {
    //test_priority_queue<PriorityQueueUnsorted<int>>("UNSORTED");
    //test_priority_queue<PriorityQueueSorted<int>>("SORTED");
    //test_priority_queue<PriorityQueueHeap<int>>("HEAP");

    static size_t SIZES[] = {
        5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000,
        45000, 50000, 55000, 60000, 65000, 70000, 75000, 80000,
        85000, 90000, 95000, 100000
    };

    static size_t SIZES_HEAP[] = {
        500000, 1000000, 1500000, 2000000, 2500000, 3000000, 3500000, 4000000,
        4500000, 5000000, 5500000, 6000000, 6500000, 7000000, 7500000, 8000000,
        8500000, 9000000, 9500000, 10000000
    };

    static size_t runs_count = 100;
    static size_t sizes_count = 20;

   std::println("[UNSORTED]");
   benchmark::bench<PriorityQueueUnsorted>(SIZES, sizes_count, runs_count);

   std::println("\n\n[SORTED]");
   benchmark::bench<PriorityQueueSorted>(SIZES, sizes_count, runs_count);

    std::println("\n\n[HEAP]");
    benchmark::bench<PriorityQueueHeap>(SIZES_HEAP, sizes_count, runs_count);

    return 0;
}
