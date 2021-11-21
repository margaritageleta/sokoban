CXX = g++
#CXXFLAGS  = -Wall -Wextra -std=c++11 -Ofast -march=native -flto -mtune=native
CXXFLAGS = -Wall -Wextra -std=c++11 -Ofast -march=native -mtune=native -funroll-loops -frename-registers
DEBUGFLAGS = -g -Og -Wall -Wextra -DDEBUG
LINKERFLAGS = 
# Build target.
SRC_FOLDER = ./src
BIN_FOLDER = ./bin
BIN = sokoban.bin
# List of all .cpp source files.
SRCS =  $(shell find $(SRC_FOLDER) -type f -name *.cpp)
# All .o files go to build dir.
OBJ = $(patsubst $(SRC_FOLDER)/%,$(BIN_FOLDER)/%,$(SRCS:.cpp=.o))

# BEGIN MAKE
all: $(BIN)

# Default target named after the binary.
# Create build directories - same structure as sources.
# Link all the object files.
$(BIN): $(OBJ)
	@echo "CPP files: $(SRCS)"
	@echo "OBJ files: $(OBJ)"
	$(CXX)  $^ -o $@

# Build target for every single object file.
$(BIN_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# This should remove all generated files.	
clean:
	$(RM) $(BIN_FOLDER)/$(BIN) $(OBJ)
	$(RM) $(BIN)