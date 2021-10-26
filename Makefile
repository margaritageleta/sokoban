COMPILER = g++
CPPFLAGS  = -g -Wall -std=c++11


# Build target.
TARGET = ./src/sokoban

# BEGIN MAKE
all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(COMPILER) $(CPPFLAGS) -O1 -o $(TARGET).bin $(TARGET).cpp

clean:
	$(RM) $(TARGET)