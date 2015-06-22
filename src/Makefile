all: main.o filter.o
	python cpplint.py *.cpp *.h *.cc

main.o: main.cpp
	g++ -std=c++11 main.cpp -o main.o

filter.o: filter.cpp
	g++ -std=c++11 filter.cpp -o filter.o
