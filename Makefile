CC = g++ -std=c++11 main.cpp -o a.out -Wall

runcodes: compile_runcodes rcodes

report: compile_runcodes tests

compile_normal:
	g++ -std=c++11 main.cpp -o a.out -Wall

compile_runcodes:
	g++ -std=c++11 run_codes_submission.cpp -o a.out -Wall

tests:
	@echo "MOA REPORT - 15 PUZZLE A* TESTS"
	@echo
	@echo "CASE 1 ------------------------- EXPECTED 21"
	@echo -n "answer = "
	@time ./a.out  2 3 4 8 5 1 6 7 10 11 12 15 0 9 13 14
	@echo
	@echo "CASE 2 ------------------------- EXPECTED 53"
	@echo -n "answer = "
	@time ./a.out 8 7 6 5 2 3 1 15 4 12 13 0 10 11 9 14
	@echo
	@echo "CASE 3 ------------------------- EXPECTED 53"
	@echo -n "answer = "
	@time ./a.out 7 0 6 5 8 2 3 1 12 13 9 15 4 10 14 11
	@echo
	@echo "CASE 4 ------------------------- EXPECTED 53"
	@echo -n "answer = "
	@time ./a.out 3 9 5 1 6 2 13 11 7 8 12 14 0 4 10 15
	@echo
	@echo "CASE 5 ------------------------- EXPECTED 50"
	@echo -n "answer = "
	@time ./a.out 9 2 1 11 3 8 5 14 6 4 13 15 7 10 12 0
	@echo
	@echo "CASE 6 ------------------------- EXPECTED ?"
	@echo -n "answer = "
	@time ./a.out 0 2 1 11 9 3 8 5 7 6 4 14 10 12 15 13
	@echo
	@echo "CASE 7 ------------------------- EXPECTED 50"
	@echo -n "answer = "
	@time ./a.out 2 3 11 5 9 6 1 14 7 12 8 13 10 15 4 0
	@echo
	@echo "CASE 8 ------------------------- EXPECTED ?"
	@echo -n "answer = "
	@time ./a.out 3 11 5 0 2 6 1 14 9 12 8 13 7 10 15 4
	@echo
	@echo "CASE 9 ------------------------- EXPECTED 53"
	@echo -n "answer = "
	@time ./a.out 3 11 5 14 0 2 6 1 12 8 4 13 9 7 10 15
	@echo
	@echo "CASE 10 ------------------------- EXPECTED ?"
	@echo -n "answer = "
	@time ./a.out 11 5 14 1 3 2 6 13 0 8 4 15 12 9 7 10

rcodes:
	@echo "MOA RUN_CODES - 15 PUZZLE A* TESTS"
	@echo
	@echo "CASE 1 ------------------------- EXPECTED 7"
	@echo -n "answer = "
	@time ./a.out 5 1 2 3 0 6 7 4 9 10 11 8 13 14 15 12
	@echo
	@echo "CASE 2 ------------------------- EXPECTED 16"
	@echo -n "answer = "
	@time ./a.out 5 1 2 3 6 7 11 4 13 9 10 8 14 15 12 0
	@echo
	@echo "CASE 3 ------------------------- EXPECTED 23"
	@echo -n "answer = "
	@time ./a.out 6 5 1 2 0 7 11 3 13 9 10 4 14 15 12 8
	@echo
	@echo "CASE 4 ------------------------- EXPECTED 31"
	@echo -n "answer = "
	@time ./a.out 6 5 1 2 13 7 11 3 9 10 4 8 0 14 15 12
	@echo
	@echo "CASE 5 ------------------------- EXPECTED 44"
	@echo -n "answer = "
	@time ./a.out 9 5 11 3 13 15 7 0 1 10 2 4 6 12 8 14
	@echo
	@echo "CASE 6 ------------------------- EXPECTED 41"
	@echo -n "answer = "
	@time ./a.out 9 5 7 11 1 13 15 3 10 0 2 4 6 12 8 14
