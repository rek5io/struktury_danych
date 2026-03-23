#include <print>
#include "lib.hpp"
#include <chrono>
#include <random>

auto randgen(int min, int max) -> int {
    static std::mt19937 rnd(time(nullptr));
    return std::uniform_int_distribution<>(min, max)(rnd);
}

namespace tests {
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

        int v = 69;
        std::println("69 at {}", vec.find(v).value());

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

    auto bench_ll() -> void {
        for (size_t s = 0; s < 20; s++) { 
            size_t size = SIZES[s];

            std::println("\n");
            std::print("ll pshb run of {} elements got times = {{", size);

            for (size_t c = 0; c < runs_count; c++) {
                auto ll = LinkedList<int>::init();

                for (size_t i = 0; i < size; i++) {
                    ll.push_back(i); 
                }

                auto start = std::chrono::high_resolution_clock::now();
                ll.push_back(42); 
                auto end = std::chrono::high_resolution_clock::now();

                auto took = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::print("{}, ", took);
            }

            std::print("}}");
        }

        for (size_t s = 0; s < 20; s++) { 
            size_t size = SIZES[s];

            std::println("\n");
            std::print("ll pshf run of {} elements got times = {{", size);

            for (size_t c = 0; c < runs_count; c++) {
                auto ll = LinkedList<int>::init();

                for (size_t i = 0; i < size; i++) {
                    ll.push_back(i); 
                }

                auto start = std::chrono::high_resolution_clock::now();
                ll.push_front(69); 
                auto end = std::chrono::high_resolution_clock::now();

                auto took = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::print("{}, ", took);
            }

            std::print("}}");
        }

        for (size_t s = 0; s < 20; s++) { 
            size_t size = SIZES[s];

            std::println("\n");
            std::print("ll popb run of {} elements got times = {{", size);

            for (size_t c = 0; c < runs_count; c++) {
                auto ll = LinkedList<int>::init();

                for (size_t i = 0; i < size; i++) {
                    ll.push_back(i); 
                }

                auto start = std::chrono::high_resolution_clock::now();
                ll.pop_back(); 
                auto end = std::chrono::high_resolution_clock::now();

                auto took = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::print("{}, ", took);
            }

            std::print("}}");
        }

        for (size_t s = 0; s < 20; s++) { 
            size_t size = SIZES[s];

            std::println("\n");
            std::print("ll popf run of {} elements got times = {{", size);

            for (size_t c = 0; c < runs_count; c++) {
                auto ll = LinkedList<int>::init();

                for (size_t i = 0; i < size; i++) {
                    ll.push_back(i); 
                }

                auto start = std::chrono::high_resolution_clock::now();
                ll.pop_front(); 
                auto end = std::chrono::high_resolution_clock::now();

                auto took = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::print("{}, ", took);
            }

            std::print("}}");
        }

        for (size_t s = 0; s < 20; s++) { 
            size_t size = SIZES[s];

            std::println("\n");
            std::print("ll insert run of {} elements got times = {{", size);

            for (size_t c = 0; c < runs_count; c++) {
                auto ll = LinkedList<int>::init();

                for (size_t i = 0; i < size; i++) {
                    ll.push_back(i); 
                }

                auto start = std::chrono::high_resolution_clock::now();
                ll.insert(randgen(0, size - 1), 42);
                auto end = std::chrono::high_resolution_clock::now();

                auto took = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::print("{}, ", took);
            }

            std::print("}}");
        }

        for (size_t s = 0; s < 20; s++) { 
            size_t size = SIZES[s];

            std::println("\n");
            std::print("ll remove run of {} elements got times = {{", size);

            for (size_t c = 0; c < runs_count; c++) {
                auto ll = LinkedList<int>::init();

                for (size_t i = 0; i < size; i++) {
                    ll.push_back(i); 
                }

                auto start = std::chrono::high_resolution_clock::now();
                ll.remove(randgen(0, size - 1));
                auto end = std::chrono::high_resolution_clock::now();

                auto took = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                std::print("{}, ", took);
            }

            std::print("}}");
        }

        std::println();
    }
}

auto main() -> int {
    //tests::ll_test();
    //tests::vec_test();
    
    benchmark::bench_ll();

    return 0;
}
