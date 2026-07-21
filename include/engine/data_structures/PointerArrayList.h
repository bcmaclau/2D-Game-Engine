#pragma once

#include <iostream>

namespace engine {

    template <typename T>
    class PointerArrayList {
    public:
        PointerArrayList() {
            list = (T**)malloc(32 * sizeof(T*));
            current_max = 32;
            current_size = 0;
        }

        ~PointerArrayList() {
            free(list);
        }

        unsigned int push_back(T* data) {
            // resize
            if (current_size == current_max) { grow(); }

            list[current_size] = data;
            current_size++;
            return current_size - 1;
        }

        void swap_indices(unsigned int first, unsigned int second) {
            if (first >= current_size || second >= current_size) { std::cout << "index out of bounds" << std::endl; return; }
            if (first == second) { return; }

            T* temp = list[first];
            list[first] = list[second];
            list[second] = temp;
        }

        void pop_back() {
            if (current_size == 0) {
                std::cout << "PointerList: popping with a size of 0" << std::endl;
                return;
            }
            current_size--;
        }
        void clear() { current_size = 0; }

        T* at(unsigned int index) const {
            if (index >= current_size) {
                std::cout << "PointerList: index out of bounds" << std::endl;
            }
            return list[index];
        }
        T* at(unsigned int index) {
            if (index >= current_size) {
                std::cout << "PointerList: index out of bounds" << std::endl;
            }
            return list[index];
        }

        T*& operator[](unsigned int index) {
            if (index >= current_size) {
                std::cout << "PointerList: index out of bounds" << std::endl;
            }
            return list[index];
        }
        T*& operator[](unsigned int index) const {
            if (index >= current_size) {
                std::cout << "PointerList: index out of bounds" << std::endl;
            }
            return list[index];
        }

        unsigned int size() const { return current_size; }

    private:
        T** list;
        unsigned int current_max;
        unsigned int current_size;

        void grow() {
            T** temp = (T**)malloc((current_max * 2) * sizeof(T*));
            std::copy(list, list + current_size, temp);
            free(list);
            list = temp;
            current_max *= 2;
        }
    };

}