CXX      = g++
CPPFLAGS = -Wall -std=c++11
LD_FLAGS =

SOURCES  = victor_wu_C++.cpp
OBJECTS  = $(SOURCES:.cpp=.o)
EXE      = submission

all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(LD_FLAGS) $(OBJECTS) -o $@
