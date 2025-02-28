CXX = g++
CXXFLAGS = -Wall -Wextra -O2
SRC = interpreter.cpp
OBJ = interpreter.o
EXE = interpreter

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJ)

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC)

clean:
	rm -f $(OBJ) $(EXE)
