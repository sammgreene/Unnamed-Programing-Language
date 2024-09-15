COMPILER=clang
FLAGS=-g -std=c++17 -pedantic -Wall
COMPILE=$(COMPILER) $(FLAGS)
BUILD=build

a.out: main.cpp $(BUILD)/token_stream.o $(BUILD)/parser.o
	$(COMPILE) $^

$(BUILD)/token_stream.o: src/token_stream.cpp includes/token_stream.h
	$(COMPILE) -c $< -o $@
$(BUILD)/parser.o: src/parser.cpp includes/parser.h
	$(COMPILE) -c $< -o $@

clean:
	rm -rf build/*
