COMPILER=clang++
FLAGS=-g -Wall -Wpedantic -std=c++20
COMPILE=$(COMPILER) $(FLAGS)
BUILD=build

$(BUILD)/a.out: main.cpp $(BUILD)/token_stream.o $(BUILD)/parser.o $(BUILD)/expressions.o $(BUILD)/statements.o $(BUILD)/error.o 
	$(COMPILE) $^ -o $@

$(BUILD)/token_stream.o: src/token_stream.cpp includes/token_stream.h
	$(COMPILE) -c $< -o $@
$(BUILD)/parser.o: src/parser.cpp includes/parser.h
	$(COMPILE) -c $< -o $@
$(BUILD)/expressions.o: src/expressions.cpp includes/expressions.h
	$(COMPILE) -c $< -o $@
$(BUILD)/statements.o: src/statements.cpp includes/statements.h
	$(COMPILE) -c $< -o $@
$(BUILD)/error.o: src/error.cpp includes/error.h
	$(COMPILE) -c $< -o $@

clean:
	rm -rf build/*

run:
	$(MAKE)
	./build/a.out
