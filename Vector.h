#ifndef TSP_BB_VECTOR_H
#define TSP_BB_VECTOR_H
#include <iostream>

template<typename T>
class Vector {
public:
    T* data = nullptr;
    int index = 0;
    int size = 0;

    Vector() {
        resize(10);
    }

    ~Vector() {
        delete[] data;
    }

    void resize(int newSize) {
        T* newData = new T[newSize];
        if(newSize < index) index = newSize;
        for(int i = 0; i < index; i++) {
            newData[i] = data[i];
        }
        if(data!= nullptr) {
            delete[] data;
        }
        data = newData;
        size = newSize;
    }

    void push(T value) {
        if(index == size) {
            resize(size+10);
        }
        data[index++] = value;
    }

    void pop() {
        if(index <= 0) {
            std::cerr << "Nothing to be popped from vector!\n";
        } else {
            index--;
        }
    }

    T& operator[](int i) {
        if (i < 0 || i >= index) {
            std::cerr << "Index out of bounds!\n";
            exit(1);
        }
        return data[i];
    }
};
#endif //TSP_BB_VECTOR_H
