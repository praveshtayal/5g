clean:
	rm -f *.o 5g

5g: main.cpp rrc.cpp
	g++ -o 5g -std=c++11 main.cpp rrc.cpp
