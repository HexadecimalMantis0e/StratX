CXX=g++
CXXFLAGS=-std=c++20 -pedantic -Wall
EXE=StratX

all: $(EXE)

$(EXE): StratX.cpp StratWad.cpp Util.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ -static

clean:
	rm -f $(EXE)
