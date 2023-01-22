CC = g++

SRC_DIR = src
OBJ_DIR = build

TARGET = life

CFLAGS = -Wall -std=c++17
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/$@ $^ $(SFML_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
