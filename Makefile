CC = g++ -std=c++11 main.cpp -o a.out -Wall

all: compile tests

compile:
	g++ -std=c++11 main.cpp -o a.out -Wall

tests:
	@echo -e "MOA REPORT - 15 PUZZLE A* TESTS"

	@echo -e "CASE 1"
	time ./a.out 2 3 4 8 5 1 6 7 10 11 12 15 0 9 13 14

	@echo -e "CASE 2"
	time ./a.out 8 7 6 5 2 3 1 15 4 12 13 0 10 11 9 14

	@echo -e "CASE 3"
	time ./a.out 7 0 6 5 8 2 3 1 12 13 9 15 4 10 14 11

	@echo -e "CASE 4"
	time ./a.out 3 9 5 1 6 2 13 11 7 8 12 14 0 4 10 15

	@echo -e "CASE 5"
	time ./a.out 9 2 1 11 3 8 5 14 6 4 13 15 7 10 12 0
	
	@echo -e "CASE 6"
	time ./a.out 0 2 1 11 9 3 8 5 7 6 4 14 10 12 15 13

	@echo -e "CASE 7"
	time ./a.out 2 3 11 5 9 6 1 14 7 12 8 13 10 15 4 0

	@echo -e "CASE 8"
	time ./a.out 3 11 5 0 2 6 1 14 9 12 8 13 7 10 15 4

	@echo -e "CASE 9"
	time ./a.out 3 11 5 14 0 2 6 1 12 8 4 13 9 7 10 15

	@echo -e "CASE 10"
	time ./a.out 11 5 14 1 3 2 6 13 0 8 4 15 12 9 7 10
