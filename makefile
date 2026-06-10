SRC_DIR := src

SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d

all:
	g++ $(SRC_DIR)/main.cpp $(SRC_DIR)/fighter.cpp $(SRC_DIR)/characterselect.cpp -o mortal.exe $(SFML) -Iinclude

run: all
	./mortal.exe

clean:
	del /Q mortal.exe

.PHONY: all run clean