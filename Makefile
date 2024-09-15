CXX = clang
CXXFLAGS = -std=c++20 -Wall -g -stdlib=libc++ -Wpedantic

a.out: main.cpp build/error.o build/tokenstream.o build/parser_nodes.o build/parser.o
	$(CXX) $(CXXFLAGS) -lc++ main.cpp build/error.o build/tokenstream.o build/parser_nodes.o build/parser.o -o build/a.out

build/error.o: src/error.cpp
	$(CXX) $(CXXFLAGS) -c src/error.cpp -o build/error.o
build/tokenstream.o: src/tokenstream.cpp
	$(CXX) $(CXXFLAGS) -c src/tokenstream.cpp -o build/tokenstream.o
build/parser.o: src/parser.cpp
	$(CXX) $(CXXFLAGS) -c src/parser.cpp -o build/parser.o
build/parser_nodes.o: src/parser_nodes.cpp
	$(CXX) $(CXXFLAGS) -c src/parser_nodes.cpp -o build/parser_nodes.o

run:
	make
	#==============================#
	cat example.upl | ./build/a.out
	#==============================#
clean:
	rm -rf ./build/*
	make
