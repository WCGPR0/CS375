CXX      = g++
CPPFLAGS = -g -Wall -std=c++11
LD_FLAGS =

SOURCES  = victor_wu_C++.cpp
OBJECTS  = $(SOURCES:.cpp=.o)
EXE      = subl

all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(LD_FLAGS) $(OBJECTS) -o $@

clean:
	rm $(OBJECTS) $(EXE)
