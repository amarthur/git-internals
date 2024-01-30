CXX = clang++
CXXFLAGS = -Wall -std=c++20 -O2 -pedantic

LIBS = -lcryptopp
INCLUDES = -I./include

SRC = src
BUILD = build

.PHONY: build

build: $(SRC)/cli.cpp $(SRC)/data.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $(BUILD)/ugit $(LIBS)

clean:
	rm $(BUILD)/*.
