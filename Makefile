CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
NCURSES_FLAGS = -lncurses
GCOV_FLAGS = --coverage
CHECK_FLAGS = -lcheck -lm -lsubunit

CFILES = brick_game/tetris/backend.c gui/cli/frontend.c
OBJS = $(CFILES:.c=.o)

TEST_FILE = test/*.c 
LIB_FILE = s21_tetris.a

FILES_REPORT = *.gcno *.gcda gcov_test coverage.info gcov_test_lcov report_gcov report_lcov

debug:
	gcc -g brick_game/tetris/*.c gui/cli/*.c -lncurses -o debug

all: $(LIB_FILE)

rebuild: clean all

run: $(LIB_FILE)
	$(CC) $(FLAGS) gui/cli/main.c -L. $(LIB_FILE) $(CHECK_FLAGS) $(NCURSES_FLAGS) -o run 
	./run

test: $(LIB_FILE)
	$(CC) $(FLAGS) $(TEST_FILE) -L. $(LIB_FILE) $(CHECK_FLAGS) -o test_exec
	./test_exec

test_valgrind: $(LIB_FILE)
	$(CC) $(FLAGS) $(TEST_FILE) -L. $(LIB_FILE) $(CHECK_FLAGS) -o test_exec
	valgrind --tool=memcheck --leak-check=yes ./test_exec

gcov_report:
	$(CC) $(FLAGS) $(TEST_FILE) $(CFILES) $(CHECK_FLAGS) $(GCOV_FLAGS) -o gcov_test_lcov
	./gcov_test_lcov
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory report_lcov

$(LIB_FILE): $(OBJS)
	ar rcs $@ $^
	ranlib $@

%.o: %.c
	$(CC) $(FLAGS) $(NCURSES_FLAGS) -c $< -o $@

clean: 
	rm -rf *.o *.a run report $(FILES_REPORT) test_exec brick_game/tetris/*.o gui/cli/*.o
