#pragma once
#include <string>

struct Array {
    std::string* data = nullptr;
    int size = 0;
    int capacity = 0;
};

void growArray(Array& array);
void addArrayEnd(Array& array, std::string value);
bool insertArrayAt(Array& array, int index, std::string value);
bool getArrayAt(const Array& array, int index, std::string& value);
bool replaceArrayAt(Array& array, int index, std::string value);
bool deleteArrayAt(Array& array, int index);
void printArray(const Array& array);