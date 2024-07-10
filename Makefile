# Author:       pi-314159@GitHub
# License:      MIT

CXX ?= g++
DEFAULT_FLAGS := -std=c++23 -O3 -Wall
DEFAULT_CXXFLAGS := -I src/include
SOURCE_FILES = $(wildcard src/*.cpp) $(wildcard src/tools/*.cpp) $(wildcard src/actions/*.cpp)
OBJECT_FILES = $(patsubst src/%,tmp/%,$(patsubst %.cpp,%.o,$(SOURCE_FILES)))

ifndef OUT
override OUT = build/Authenticator
endif

$(info $(shell mkdir -p build tmp/tools tmp/actions))

.PHONY: all

all: $(OUT)
	$(info Done! The executable is located at $(OUT)!)

tmp/tools/%.o: src/tools/%.cpp
	$(CXX) $(DEFAULT_FLAGS) $(DEFAULT_CXXFLAGS) $(CXXFLAGS) -c $< -o $@

tmp/actions/%.o: src/actions/%.cpp
	$(CXX) $(DEFAULT_FLAGS) $(DEFAULT_CXXFLAGS) $(CXXFLAGS) -c $< -o $@

tmp/%.o: src/%.cpp
	$(CXX) $(DEFAULT_FLAGS) $(DEFAULT_CXXFLAGS) $(CXXFLAGS) -c $< -o $@

$(OUT): $(OBJECT_FILES)
	$(CXX) $(DEFAULT_FLAGS) $^ -o $@ $(LDFLAGS) -lcrypto

clean:
	rm -R tmp build
