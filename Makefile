COMPILER = g++
CPPFLAGS  = -g -Wall -std=c++11

# Build target.
TARGET = sokoban

# BEGIN MAKE
all: $(TARGET)

$(TARGET): $(TARGET).cc
	$(COMPILER) $(CPPFLAGS) -O1 -o $(TARGET).bin $(TARGET).cc

clean:
	$(RM) $(TARGET)