a.out: main.cpp build/error.o build/tokenstream.o build/parser_nodes.o build/parser.o
	$(CXX) -g main.cpp build/error.o build/tokenstream.o build/parser_nodes.o build/parser.o -o build/a.out

build/error.o: src/error.cpp
	$(CXX) -Wall -g -c src/error.cpp -o build/error.o
build/tokenstream.o: src/tokenstream.cpp
	$(CXX) -Wall -g -c src/tokenstream.cpp -o build/tokenstream.o
build/parser.o: src/parser.cpp
	$(CXX) -Wall -g -c src/parser.cpp -o build/parser.o
build/parser_nodes.o: src/parser_nodes.cpp
	$(CXX) -Wall -g -c src/parser_nodes.cpp -o build/parser_nodes.o

run:
	make
	#==============================#
	cat example.upl | ./build/a.out
	#==============================#
clean:
	rm ./build/*
	make
