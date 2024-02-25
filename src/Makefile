BUILD_PATH=../bin/
CC=gcc
CFLAGS=-g -Wall -Wextra -Werror -std=c11
EXTRAFLAGS=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector 

all: check rebuild

build: clean

rebuild: clean_all determinant invert solve_linear_equations sort clean

determinant: determinant.c matrix_common.c
	$(CC) $(CFLAGS) determinant.c matrix_common.c -o  $(BUILD_PATH)determinant  -lm
	$(CC) $(CFLAGS) $(EXTRAFLAGS) determinant.c matrix_common.c -o  $(BUILD_PATH)determinant_extra  -lm

invert: invert.c matrix_common.c
	$(CC) $(CFLAGS) invert.c matrix_common.c -o  $(BUILD_PATH)invert  -lm 
	$(CC) $(CFLAGS) $(EXTRAFLAGS) invert.c matrix_common.c -o  $(BUILD_PATH)invert_extra -lm
	
solve_linear_equations: solve_linear_equations.c matrix_common.c
	$(CC) $(CFLAGS) solve_linear_equations.c matrix_common.c -o  $(BUILD_PATH)solve_linear_equations -lm
	$(CC) $(CFLAGS) $(EXTRAFLAGS) solve_linear_equations.c matrix_common.c -o  $(BUILD_PATH)solve_linear_equations_extra -lm
	
sort: sort.c matrix_common.c
	$(CC) $(CFLAGS) sort.c matrix_common.c -o  $(BUILD_PATH)sort -lm
	$(CC) $(CFLAGS) $(EXTRAFLAGS) sort.c matrix_common.c -o  $(BUILD_PATH)sort_extra -lm

clean_all:
	rm -rf *.o *.a *.so $(BUILD_PATH)Quest* $(BUILD_PATH)*.so
	
clean:
	rm -rf *.o *.a

check:
	clang-format -n *.c
	clang-format -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

run:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)determinant
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)invert
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)solve_linear_equations
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)sort

run_no_valgrind:
	$(BUILD_PATH)determinant
	$(BUILD_PATH)invert
	$(BUILD_PATH)solve_linear_equations
	$(BUILD_PATH)sort