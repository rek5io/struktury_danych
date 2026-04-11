#pragma once

#include "icollection.hpp"
#include <cstddef>
#include <optional>
#include <functional>
#include <utility>

template<typename T>
struct SNode {
    SNode<T> *next;
    T value;
};

template<typename T>
class SingleList: public ICollection<T> {
    private:
        SNode<T> *head;

        SingleList() {}

        auto get_node_ptr(size_t idx) -> SNode<T>* {
            auto node = head;
            while (node && idx--) {
                node = node->next;
            }
            return node;
        }

    public:
        SingleList& operator=(const SingleList<T>&) = delete;
        SingleList(SingleList<T>&&) noexcept = default;
        SingleList& operator=(SingleList<T>&&) noexcept = default;

        static auto init() -> SingleList<T> {
            SingleList<T> l;
            
            l.head = nullptr;

            return l;
        }

        SingleList clone() {
            SingleList result;

            if (!head) {
                result.head = nullptr;
                return result;
            }

            result.head = new SNode<T>;
            result.head->value = head->value;
            result.head->next = nullptr;

            SNode<T>* curr_old = head->next;
            SNode<T>* curr_new = result.head;

            while (curr_old) {
                curr_new->next = new SNode<T>;
                curr_new = curr_new->next;

                curr_new->value = curr_old->value;
                curr_new->next = nullptr;

                curr_old = curr_old->next;
            }

            return result;
        }

        auto get_len() -> size_t {
            SNode<T>* node = this->head;
            size_t len = 0;

            while (node) {
                node = node->next;
                len++;
            }

            return len;
        }

        auto is_empty() -> bool {
            return get_len() == 0;
        }

        auto push_back(T value) -> void {
            auto node = new SNode<T>();
            node->next = nullptr;
            node->value = std::move(value);

            if (!this->head) {
                this->head = node;
                return;
            }

            auto current = this->head;
            while (current->next) {
                current = current->next;
            }

            current->next = node;
        }

        auto push_front(T value) -> void {
            auto node = new SNode<T>();
            node->next = nullptr;
            node->value = std::move(value);

            if (this->head == nullptr) {
                this->head = node;
            } else {
                node->next = this->head;
                this->head = node;
            }
        }

        auto pop_back() -> std::optional<T> {
            if (!this->head) {
                return std::nullopt;
            }

            if (!head->next) {
                T v = std::move(head->value);
                delete head;
                head = nullptr;
                return v;
            }

            auto prev = head;
            auto current = head->next;

            while (current->next) {
                prev = current;
                current = current->next;
            }

            T v = std::move(current->value);
            delete current;
            prev->next = nullptr;

            return v;
        }

        auto pop_front() -> std::optional<T> {
           return this->remove(0); 
        }

        auto get_ref_back() -> std::optional<std::reference_wrapper<T>> {
            auto current = this->head;

            if (!current) {
                return std::nullopt;
            }

            while (current->next) {
                current = current->next;
            }

            return std::ref(current->value);
        }

        auto get_ref_front() -> std::optional<std::reference_wrapper<T>> {
            if (this->head == nullptr) {
                return std::nullopt;
            }

            return std::ref(this->head->value);
        }

        auto get_ref(size_t idx) -> std::optional<std::reference_wrapper<T>> {
            auto node = this->get_node_ptr(idx);
            if (node == nullptr) {
                return std::nullopt;
            }

            return std::ref(node->value);
        } 

        auto remove(size_t idx) -> std::optional<T> {
            if (!this->head) {
                return std::nullopt;
            }

            if (idx == 0) {
                auto tmp = this->head;
                this->head = this->head->next;

                T v = std::move(tmp->value);
                delete tmp;

                return v;
            }

            auto prev = this->head;
            auto node = this->head->next;

            for (size_t i = 1; i < idx && node; i++) {
                prev = node;
                node = node->next;
            }

            if (!node) {
                return std::nullopt;
            }

            prev->next = node->next;

            T v = std::move(node->value);
            delete node;

            return v;
        }

        auto insert(size_t idx, T value) -> std::optional<T> {
            if (idx == 0 || !this->head) {
                this->push_front(std::move(value));
                return std::nullopt;
            }

            auto prev = this->head;
            auto node = this->head->next;

            for (size_t i = 1; i < idx && node; i++) {
                prev = node;
                node = node->next;
            }

            auto new_node = new SNode<T>();
            new_node->next = node;
            new_node->value = std::move(value);
            prev->next = new_node;

            return std::nullopt;
        }

        auto swap(size_t idx, T& swap) -> bool {
            auto node = this->get_node_ptr(idx);
            if (node == nullptr) {
                return false;
            }

            std::swap(swap, node->value);
            return true;
        }

        auto search(std::function<bool(T&)> predicate) -> std::optional<size_t> {
            size_t idx = 0;
            auto current = this->head;

            while (current != nullptr) {
                if (predicate(current->value)) {
                    return idx; 
                }

                current = current->next;
                idx++;
            }

            return std::nullopt;
        }

        auto clear() -> void {
            auto current = this->head;
            while (current != nullptr) {
                auto next = current->next;
                delete current;
                current = next;
            }

            this->head = nullptr;
        }

        ~SingleList() {
            this->clear();
        }
};
