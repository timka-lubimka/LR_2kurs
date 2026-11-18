#include "array.h"
#include <iostream>

void growArray(Array& array) {
    int newCapacity = array.capacity == 0 ? 4 : array.capacity * 2;
    std::string* newData = new std::string[newCapacity];

    for (int i = 0; i < array.size; i++) {
        newData[i] = array.data[i];
    }

    delete[] array.data;
    array.data = newData;
    array.capacity = newCapacity;
}

void addArrayEnd(Array& array, std::string value) {
    if (array.size == array.capacity) {
        growArray(array);
    }
    array.data[array.size] = value;
    array.size++;
}

bool insertArrayAt(Array& array, int index, std::string value) {
    if (index < 0 || index > array.size) {
        return false;
    }
    if (array.size == array.capacity) {
        growArray(array);
    }

    for (int i = array.size; i > index; i--) {
        array.data[i] = array.data[i - 1];
    }

    array.data[index] = value;
    array.size++;
    return true;
}

bool getArrayAt(const Array& array, int index, std::string& value) {
    if (index < 0 || index >= array.size) {
        return false;
    }
    value = array.data[index];
    return true;
}

bool replaceArrayAt(Array& array, int index, std::string value) {
    if (index < 0 || index >= array.size) {
        return false;
    }
    array.data[index] = value;
    return true;
}

bool deleteArrayAt(Array& array, int index) {
    if (index < 0 || index >= array.size) {
        return false;
    }

    for (int i = index; i < array.size - 1; i++) {
        array.data[i] = array.data[i + 1];
    }

    array.size--;
    return true;
}

void printArray(const Array& array) {
    for (int i = 0; i < array.size; i++) {
        std::cout << array.data[i] << ' ';
    }
    std::cout << '\n';
}
