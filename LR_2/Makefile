CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra
CPP_SRC := $(wildcard cpp/*.cpp) LR-1/cpp/stack.cpp LR-1/cpp/array.cpp LR-1/cpp/queue.cpp LR-1/cpp/doubly_list.cpp
.PHONY: all cpp go clean
all: cpp go
cpp:
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(CPP_SRC) -o bin/lr2-cpp
go:
	mkdir -p bin
	cd go && go build -o ../bin/lr2-go .
clean:
	rm -rf bin
