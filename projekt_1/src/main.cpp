#include <print>
#include "lib.hpp"
#include <chrono>
#include <random>

auto randgen(int min, int max) -> int {
    static std::mt19937 rnd(time(nullptr));
    return std::uniform_int_distribution<>(min, max)(rnd);
}

namespace tests {
    auto sl_test() -> void {
        std::println("==[sl test]============");

        auto list = SingleList<int>::init();
        
        list.push_back(10);
        list.push_back(20);
        list.push_back(30);

        list.push_front(5);
        list.push_front(1);
        list.push_front(6);

        list.insert(0, 69);
        list.insert(2, 42);

        int i = 33;
        std::println("pre swap: {} {}", i, list.get_ref_front()->get()); 
        list.swap(0, i);
        std::println("after swap: {} {}", i, list.get_ref_front()->get());

        std::println("ref front: {}", list.get_ref_front()->get());
        std::println("ref back: {}", list.get_ref_back()->get());

        std::println("front: {}", list.pop_front().value());
        std::println("back: {}", list.pop_back().value());

        std::println("rm 3: {}", list.remove(3).value());

        for (size_t i = 0; i < list.get_len(); ++i) {
            if (auto val = list.get_ref(i)) {
                std::println("idx {}: {}", i, val->get());
            }
        }

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 10000; i++) {
            list.push_back(i);
        }

        auto end = std::chrono::high_resolution_clock::now();

        auto took = std::chrono::duration<double, std::milli>(end - start).count();
        std::println("adding back 10000 elements took: {} ms", took);

        start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 10000; i++) {
            list.push_front(i);
        }

        end = std::chrono::high_resolution_clock::now();

        took = std::chrono::duration<double, std::milli>(end - start).count();
        std::println("adding front 10000 elements took: {} ms", took);

        std::println("=======================");
    }

    auto ll_test() -> void {
        std::println("==[ll test]============");

        auto list = LinkedList<int>::init();
        
        list.push_back(10);
        list.push_back(20);
        list.push_back(30);

        list.push_front(5);
        list.push_front(1);
        list.push_front(6);

        list.insert(0, 69);
        list.insert(2, 42);

        int i = 33;
        std::println("pre swap: {} {}", i, list.get_ref_front()->get()); 
        list.swap(0, i);
        std::println("after swap: {} {}", i, list.get_ref_front()->get());

        std::println("ref front: {}", list.get_ref_front()->get());
        std::println("ref back: {}", list.get_ref_back()->get());

        std::println("front: {}", list.pop_front().value());
        std::println("back: {}", list.pop_back().value());

        std::println("rm 3: {}", list.remove(3).value());

        for (size_t i = 0; i < list.get_len(); ++i) {
            if (auto val = list.get_ref(i)) {
                std::println("idx {}: {}", i, val->get());
            }
        }

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 1000000; i++) {
            list.push_back(i);
        }

        auto end = std::chrono::high_resolution_clock::now();

        auto took = std::chrono::duration<double, std::milli>(end - start).count();
        std::println("adding back 1000000 elements took: {} ms", took);

        start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 1000000; i++) {
            list.push_front(i);
        }

        end = std::chrono::high_resolution_clock::now();

        took = std::chrono::duration<double, std::milli>(end - start).count();
        std::println("adding front 1000000 elements took: {} ms", took);

        std::println("=======================");
    }

    auto vec_test() -> void {
        std::println("==[vec test]===========");

        auto vec = Vec<int>::init();

        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);

        vec.push_front(5);
        vec.push_front(1);
        vec.push_front(6);

        vec.insert(0, 69);
        vec.insert(2, 42);

        int i = 33;
        std::println("pre swap: {} {}", i, vec.get_ref_front()->get()); 
        vec.swap(0, i);
        std::println("after swap: {} {}", i, vec.get_ref_front()->get());

        std::println("ref front: {}", vec.get_ref_front()->get());
        std::println("ref back: {}", vec.get_ref_back()->get());

        std::println("front: {}", vec.pop_front().value());
        std::println("back: {}", vec.pop_back().value());

        std::println("rm 3: {}", vec.remove(3).value());

        for (size_t i = 0; i < vec.get_len(); ++i) {
            if (auto val = vec.get_ref(i)) {
                std::println("idx {}: {}", i, val->get());
            }
        }

        vec.clear();

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 1000000; i++) {
            vec.push_back(i);
        }

        std::println("69 at {}", vec.search([](int& x) { return x == 69; }).value());

        auto end = std::chrono::high_resolution_clock::now();

        auto took = std::chrono::duration<double, std::milli>(end - start).count();
        std::println("adding back 1000000 elements took: {} ms", took);

        
        start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 1000000; i++) {
            vec.insert(vec.get_len() - 1, i);
        }

        end = std::chrono::high_resolution_clock::now();

        took = std::chrono::duration<double, std::milli>(end - start).count();
        std::println("insert at len - 1 1000000 elements took: {} ms", took);

        start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 1000; i++) {
            vec.push_front(i);
        }

        end = std::chrono::high_resolution_clock::now();

        took = std::chrono::duration<double, std::milli>(end - start).count();

        std::println("adding front 1000 elements took: {} ms", took);

        start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 1000; i++) {
            vec.insert(0, i);
        }

        end = std::chrono::high_resolution_clock::now();

        took = std::chrono::duration<double, std::milli>(end - start).count();
        std::println("insert at 0 1000 elements took: {} ms", took);

        std::println("=======================");
    }
}

namespace benchmark {
    static size_t SIZES[] = {
        5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000,
        45000, 50000, 55000, 60000, 65000, 70000, 75000, 80000,
        85000, 90000, 95000, 100000
    };

    static size_t runs_count = 100;
    static size_t sizes_count = 20;

    template<template<typename> class T>
    auto bench() -> void {
        long took = 0;

        for (size_t s = 0; s < sizes_count; s++) {     
            size_t size = SIZES[s];

            auto ll = T<int>::init();

            for (size_t i = 0; i < size; i++) {
                ll.push_front(i); 
            }

            for (size_t c = 0; c < runs_count; c++) {
                auto l2 = ll.clone();
                auto start = std::chrono::high_resolution_clock::now();
                l2.push_back(42); 
                auto end = std::chrono::high_resolution_clock::now();

                took += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }

            std::println("pshb {} {}", size, took / runs_count);
            took = 0;
        }

        for (size_t s = 0; s < sizes_count; s++) {     
            size_t size = SIZES[s];

            auto ll = T<int>::init();

            for (size_t i = 0; i < size; i++) {
                ll.push_front(i); 
            }

            for (size_t c = 0; c < runs_count; c++) {
                auto l2 = ll.clone();
                auto start = std::chrono::high_resolution_clock::now();
                l2.push_front(42); 
                auto end = std::chrono::high_resolution_clock::now();

                took += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }

            std::println("pshf {} {}", size, took / runs_count);
            took = 0;
        }

        for (size_t s = 0; s < sizes_count; s++) {     
            size_t size = SIZES[s];

            auto ll = T<int>::init();

            for (size_t i = 0; i < size; i++) {
                ll.push_front(i); 
            }

            for (size_t c = 0; c < runs_count; c++) {
                auto l2 = ll.clone();
                auto start = std::chrono::high_resolution_clock::now();
                l2.pop_back(); 
                auto end = std::chrono::high_resolution_clock::now();

                took += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }

            std::println("ppob {} {}", size, took / runs_count);
            took = 0;
        }

        for (size_t s = 0; s < sizes_count; s++) {     
            size_t size = SIZES[s];

            auto ll = T<int>::init();

            for (size_t i = 0; i < size; i++) {
                ll.push_front(i); 
            }

            for (size_t c = 0; c < runs_count; c++) {
                auto l2 = ll.clone();
                auto start = std::chrono::high_resolution_clock::now();
                l2.pop_front(); 
                auto end = std::chrono::high_resolution_clock::now();

                took += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }

            std::println("ppof {} {}", size, took / runs_count);
            took = 0;
        }

        for (size_t s = 0; s < sizes_count; s++) {     
            size_t size = SIZES[s];

            auto ll = T<int>::init();

            for (size_t i = 0; i < size; i++) {
                ll.push_front(i); 
            }

            for (size_t c = 0; c < runs_count; c++) {
                auto l2 = ll.clone();
                auto start = std::chrono::high_resolution_clock::now();
                l2.insert(randgen(0, size - 1), 42); 
                auto end = std::chrono::high_resolution_clock::now();

                took += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }

            std::println("insert {} {}", size, took / runs_count);
            took = 0;
        }

        for (size_t s = 0; s < sizes_count; s++) {     
            size_t size = SIZES[s];

            auto ll = T<int>::init();

            for (size_t i = 0; i < size; i++) {
                ll.push_front(i); 
            }

            for (size_t c = 0; c < runs_count; c++) {
                auto l2 = ll.clone();
                auto start = std::chrono::high_resolution_clock::now();
                l2.remove(randgen(0, size - 1));
                auto end = std::chrono::high_resolution_clock::now();

                took += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }

            std::println("remove {} {}", size, took / runs_count);
            took = 0;
        }

        size_t t;

        for (size_t s = 0; s < sizes_count; s++) {     
            size_t size = SIZES[s];

            auto ll = T<int>::init();

            for (size_t i = 0; i < size; i++) {
                ll.push_front(i); 
            }

            for (size_t c = 0; c < runs_count; c++) {
                auto l2 = ll.clone();
                auto start = std::chrono::high_resolution_clock::now();
                t = l2.search([size](int& x) { return x == (int)size / 2; }).value();
                auto end = std::chrono::high_resolution_clock::now();

                took += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }

            std::println("search {} {} with place {}", size, took / runs_count, t);
            took = 0;
        }
    }
}

auto main() -> int {
    //tests::ll_test();
    //tests::vec_test();
    //tests::sl_test();
    
    std::println("[Single List]");
    benchmark::bench<SingleList>();
    std::println("[Linked List]");
    benchmark::bench<LinkedList>();
    std::println("[Vec]");
    benchmark::bench<Vec>();

    return 0;
}
