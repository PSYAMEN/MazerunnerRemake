all: ./bin/Mazerunner

./bin/Mazerunner: ./obj/Maze.o ./obj/IHM.o ./obj/Player.o ./obj/main.o
	g++ $^ -o $@ ./lib/linux/libraylib.a

./obj/main.o: ./src/main.cpp ./src/IHM.hpp ./src/IHM.cpp ./src/Maze.hpp ./src/Maze.cpp ./src/Player.hpp ./src/Player.cpp
	g++ -c ./src/main.cpp -o ./obj/main.o -Wall -O2 -static-libgcc -static-libstdc++

./obj/IHM.o: ./src/IHM.hpp ./src/IHM.cpp ./src/Maze.hpp ./src/Maze.cpp ./src/Player.hpp ./src/Player.cpp 
	g++ -c ./src/IHM.cpp -o ./obj/IHM.o -Wall -O2 -static-libgcc -static-libstdc++

./obj/Maze.o: ./src/Maze.hpp ./src/Maze.cpp ./src/Player.hpp ./src/Player.cpp 
	g++ -c ./src/Maze.cpp -o ./obj/Maze.o -Wall -O2 -static-libgcc -static-libstdc++

./obj/Player.o: ./src/Player.hpp ./src/Player.cpp
	g++ -c ./src/Player.cpp -o ./obj/Player.o -Wall -O2 -static-libgcc -static-libstdc++

clean:
	rm -f ./obj/*.o

clear:
	rm -f ./obj/*.o ./bin/*
