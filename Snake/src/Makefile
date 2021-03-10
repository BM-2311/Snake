snake: main.o snake.o
	$(CXX) main.o snake.o -o snake -lncurses

main.o: main.cpp
	$(CXX) -c main.cpp

snake.o: snake.cpp snake.h
	$(CXX) -c snake.cpp

clean:
	rm *.o snake