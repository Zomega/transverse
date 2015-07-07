all: main.o filter.o lint

lint:
	python cpplint.py --root=src *.h *.cc

main.o: *.h *.cc
	g++ -std=c++11 -I /usr/local/include main.cc bbox.cc rtree.cc naive_rstore.cc -o main.o

filter.o: *.h *.cc
	g++ -std=c++11 -I /usr/local/include filter.cc -o filter.o

scratch.o: *.h *.cc
	g++ -std=c++11 -I /usr/local/include scratch.cc edge.cc intersect.cc bbox.cc shape.cc -o scratch.o
