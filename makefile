all: bin/Python-Snake
  
bin/Python-Snake: build/Main.o build/Menu.o build/Snake.o
	g++ -std=c++11 -Wall -Werror build/Main.o build/Menu.o build/Snake.o -o bin/Python-Snake -lsfml-graphics -lsfml-window -lsfml-system

build/Main.o: src/Main.cpp
	g++ -std=c++11 -Wall -Werror -c src/Main.cpp -o build/Main.o 

build/Snake.o: src/snake.cpp
	g++ -std=c++11 -Wall -Werror -c src/snake.cpp -o build/Snake.o 

build/Menu.o: src/Menu.cpp
	g++ -std=c++11 -Wall -Werror -c src/Menu.cpp -o build/Menu.o 

.PHONY: clean

clean:
	rm -rf build/*.o bin/Python-Snake
