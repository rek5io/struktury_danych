#pragma once

#include <cstddef>
#include <optional>
#include <functional>
#include <utility>
#include <cstdlib>
#include <cstring>

template <typename T>
inline static void memory_move(T* dest, T* src, size_t n)
{
    if constexpr (std::is_trivially_copyable_v<T>) {
        memmove(dest, src, n * sizeof(T));
    } else {
        if (dest < src) {
            for (size_t i = 0; i < n; i++) {
                dest[i] = std::move(src[i]);
            }
        } else {
            for (size_t i = n; i > 0; i--) {
                dest[i-1] = std::move(src[i-1]);
            }
        }
    }
}

template<typename T>
class Vec {
    private:
        size_t cap;
        size_t len;
        T* buffer;

        Vec() : cap(0), len(0), buffer(nullptr) {}

        auto resize() -> void {
            if (this->len < this->cap) {
                return;
            }

            if (this->cap == 0) {
                this->cap = 256;
            } else {
                this->cap *= 2;
            }

            T* new_buffer = new T[this->cap];
            memory_move(new_buffer, this->buffer, this->len);
            delete[] this->buffer;
            this->buffer = new_buffer;
        }

    public:
        Vec& operator=(const Vec<T>&) = delete;
        Vec(const Vec&) = delete;

        Vec(Vec&& other) noexcept {
            this->buffer = other.buffer;
            this->len = other.len;
            this->cap = other.cap;

            other.buffer = nullptr;
            other.len = 0;
            other.cap = 0;
        }

        Vec& operator=(Vec&& other) noexcept {
            if (this != &other) {
                delete[] this->buffer;

                this->buffer = other.buffer;
                this->len = other.len;
                this->cap = other.cap;

                other.buffer = nullptr;
                other.len = 0;
                other.cap = 0;
            }

            return *this;
        }

        static auto init() -> Vec<T> {
            Vec<T> v;

            v.cap = 256;
            v.len = 0;
            v.buffer = new T[v.cap];

            return v;
        }

        Vec clone() {
            Vec result;

            result.cap = this->cap;
            result.len = this->len;

            if (result.len == 0) {
                result.cap = 256;
                result.buffer = new T[result.cap];
                return result;
            }

            result.buffer = new T[cap];
            memory_move(result.buffer, this->buffer, this->len);

            return result;
        }

        auto get_len() -> size_t {
            return this->len;
        }

        auto is_empty() -> bool {
            return this->len == 0;
        }

        auto push_back(T value) -> void {
            this->resize();
            this->buffer[this->len] = std::move(value);
            this->len++;
        }

        auto push_front(T value) -> void {
            this->resize();

            memory_move(
                this->buffer + 1,
                this->buffer,
                this->len
            );

            this->buffer[0] = std::move(value);
            this->len++;
        }

        auto pop_back() -> std::optional<T> {
            if (this->len == 0) {
                return std::nullopt;
            }

            this->len--;
            return std::move(this->buffer[this->len]);
        }

        auto pop_front() -> std::optional<T> {
            if (this->len == 0) {
                return std::nullopt;
            }

            T value = std::move(this->buffer[0]);
            this->len--;

            memory_move(
                this->buffer,
                this->buffer + 1,
                this->len
            );

            return value;
        }

        auto get_ref_back() -> std::optional<std::reference_wrapper<T>> {
            if (this->len == 0) {
                return std::nullopt;
            }

            return std::ref(this->buffer[this->len - 1]);
        }

        auto get_ref_front() -> std::optional<std::reference_wrapper<T>> {
            if (this->len == 0) {
                return std::nullopt;
            }

            return std::ref(this->buffer[0]);
        }

        auto get_ref(size_t idx) -> std::optional<std::reference_wrapper<T>> {
            if (idx >= this->len) {
                return std::nullopt;
            }

            return std::ref(this->buffer[idx]);
        }

        auto remove(size_t idx) -> std::optional<T> {
            if (idx >= this->len) {
                return std::nullopt;
            }

            T value = std::move(this->buffer[idx]);

            memory_move(
                this->buffer + idx,
                this->buffer + idx + 1,
                this->len - idx - 1
            );

            this->len--;
            return value;
        }


        auto insert(size_t idx, T value) -> void {
            if (idx > this->len) {
                idx = this->len;
            }

            this->resize();

            memory_move(
                this->buffer + idx + 1,
                this->buffer + idx,
                this->len - idx
            );

            this->buffer[idx] = std::move(value);
            this->len++;
        }

        auto swap(size_t idx, T& swap) -> bool {
            if (idx >= this->len) {
                return false;
            }

            std::swap(swap, this->buffer[idx]);
            return true;
        }

        auto search(std::function<bool(T&)> predicate) -> std::optional<size_t> {
            for (size_t i = 0; i < this->len; i++) {
                if (predicate(this->buffer[i])) {
                    return i;
                }
            }

            return std::nullopt;
        }

        auto clear() -> void {
            this->len = 0;
            delete[] this->buffer;
            this->buffer = new T[this->cap];
        }

        ~Vec() {
            delete[] this->buffer;
        }
};
