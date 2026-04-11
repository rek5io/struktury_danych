#pragma once

#include "icollection.hpp"
#include <cstddef>
#include <optional>
#include <functional>
#include <utility>

template<typename T>
struct Node {
    Node<T> *next;
    Node<T> *prev;
    T value;
};

template<typename T>
class LinkedList: public ICollection<T> {
    private:
        Node<T> *head;
        Node<T> *tail;
        size_t len;

        LinkedList() {}

        auto get_node_ptr(size_t idx) -> Node<T>* {
            Node<T>* node = nullptr;

            if (idx == 0) {
                return this->head;
            }

            if (idx >= this->len) {
                return node;
            }

            if (idx == (this->len - 1)) {
                return this->tail;
            }

            if (idx < this->len / 2) {
                node = this->head;

                for (size_t i = 0; i < idx; i++) {
                    node = node->next;
                }
            } else {
                node = this->tail;

                for (size_t i = len - 1; i > idx; i--) {
                    node = node->prev;
                }
            }

            return node;
        }

    public:
        LinkedList& operator=(const LinkedList<T>&) = delete;
        LinkedList(LinkedList<T>&&) noexcept = default;
        LinkedList& operator=(LinkedList<T>&&) noexcept = default;

        static auto init() -> LinkedList<T> {
            LinkedList<T> l;
            
            l.head = nullptr;
            l.tail = nullptr;
            l.len = 0;

            return l;
        }

        LinkedList clone() {
            LinkedList result;

            if (!head) {
                result.head = nullptr;
                result.tail = nullptr;
                result.len = 0;
                return result;
            }

            result.head = new Node<T>;
            result.head->value = head->value;
            result.head->prev = nullptr;
            result.head->next = nullptr;

            Node<T>* curr_old = head->next;
            Node<T>* curr_new = result.head;

            result.len = 1;

            while (curr_old) {
                Node<T>* new_node = new Node<T>;

                new_node->value = curr_old->value;
                new_node->next = nullptr;
                new_node->prev = curr_new;

                curr_new->next = new_node;

                curr_new = new_node;
                curr_old = curr_old->next;

                result.len++;
            }

            result.tail = curr_new;

            return result;
        }

        auto get_len() -> size_t {
            return this->len;
        }

        auto is_empty() -> bool {
            return this->len == 0;
        }

        auto push_back(T value) -> void {
            auto node = new Node<T>();
            node->next = nullptr;
            node->prev = nullptr;
            node->value = std::move(value);

            if (this->tail == nullptr) {
                this->tail = node;
                this->head = node;
            } else {
                node->prev = this->tail;
                this->tail->next = node;
                this->tail = node;
            }

            this->len++;
        }

        auto push_front(T value) -> void {
            auto node = new Node<T>();
            node->next = nullptr;
            node->prev = nullptr;
            node->value = std::move(value);

            if (this->head == nullptr) {
                this->tail = node;
                this->head = node;
            } else {
                node->next = this->head;
                this->head->prev = node;
                this->head = node;
            }

            this->len++;
        }

        auto pop_back() -> std::optional<T> {
            if (this->len == 0) {
                return std::nullopt;
            }

            return this->remove(this->len - 1);
        }

        auto pop_front() -> std::optional<T> {
           return this->remove(0); 
        }

        auto get_ref_back() -> std::optional<std::reference_wrapper<T>> {
            if (this->tail == nullptr) {
                return std::nullopt;
            }

            return std::ref(this->tail->value);
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
            auto node = this->get_node_ptr(idx);
            if (node == nullptr) {
                return std::nullopt;
            }

            T value = std::move(node->value);

            if (node->next != nullptr) {
                node->next->prev = node->prev;
            } else {
                this->tail = node->prev;
            }

            if (node->prev != nullptr) {
                node->prev->next = node->next;
            } else {
                this->head = node->next;
            }
            
            this->len--;
            delete node;
            return value;
        }

        auto insert(size_t idx, T value) -> std::optional<T> {
            if (this->len == 0) {
                this->push_back(value);
                return std::nullopt;
            }

            auto node = this->get_node_ptr(idx);
            if (node == nullptr) {
                return value;
            }

            auto new_node = new Node<T>();
            new_node->next = node;
            new_node->prev = node->prev;

            if (node->prev == nullptr) {
                this->head = new_node;
            } else {
                node->prev->next = new_node;
            }

            node->prev = new_node; 
            new_node->value = std::move(value);
            
            this->len++;
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

            this->len = 0;
            this->head = nullptr;
            this->tail = nullptr;
        }

        ~LinkedList() {
            this->clear();
        }
};
