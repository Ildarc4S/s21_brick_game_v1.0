CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
NCURSES_FLAGS = -lncurses
GCOV_FLAGS = --coverage
CHECK_FLAGS = -lcheck -lm -lsubunit

SRC_DIR = brick_game/tetris
TEST_DIR = tests/tetris_tests
GUI_DIR = gui/cli
BUILD_DIR = build/tetris
OBJ_DIR = $(BUILD_DIR)/obj
COV_DIR = coverage/tetris/
LIB_DIR = lib
TETRIS_TAR = s21_tetris.tar.gz

CFILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(CFILES))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/tests/%.o,$(TEST_FILES))
BIN_DIR = bin/tetris

PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
LIBDIR = $(PREFIX)/lib
DOCDIR = $(PREFIX)/share/doc/s21_tetris
DOCS_OUTPUT_DIR = docs/tetris

LIB_PATH = $(LIB_DIR)/s21_tetris.a
LIB_NAME = s21_tetris.a
EXEC_NAME = s21_tetris_cli
TEST_EXEC = test_exec

DOCGEN = doxygen
DOXYFILE = tetris_doxy 

CLANG_FORMAT = clang-format
CLANG_FORMAT_FLAGS = --style=Google --Werror --dry-run

.PHONY: all install uninstall clean dvi dist test gcov_report rebuild valgrind_test clang_test clang_format

all: $(LIB_NAME) $(EXEC_NAME)

$(LIB_NAME): $(OBJS)
	mkdir -p $(LIB_DIR)
	ar rcs $(LIB_PATH) $^
	ranlib $(LIB_PATH)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/tests/%.o: $(TEST_DIR)/%.c
	mkdir -p $(OBJ_DIR)/tests
	$(CC) $(FLAGS) -c $< -o $@

$(EXEC_NAME): $(GUI_DIR)/*.c $(LIB_NAME)
	mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $(GUI_DIR)/*.c $(LIB_PATH) -o $(BIN_DIR)/$@ $(NCURSES_FLAGS)

test: $(TEST_EXEC)
	./$(BIN_DIR)/$<

$(TEST_EXEC): $(TEST_OBJS) $(LIB_NAME)
	mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $(TEST_OBJS) $(LIB_PATH) -o $(BIN_DIR)/$@ $(CHECK_FLAGS)

gcov_report: $(TEST_FILES) $(CFILES)
	mkdir -p $(BIN_DIR)/coverage $(COV_DIR)
	$(CC) $(FLAGS) $^ $(CHECK_FLAGS) $(GCOV_FLAGS) -o $(BIN_DIR)/coverage/gcov_exec
	./$(BIN_DIR)/coverage/gcov_exec
	lcov --capture --directory . --output-file $(COV_DIR)/coverage.info
	genhtml $(COV_DIR)/coverage.info --output-directory $(COV_DIR)

install: $(EXEC_NAME) dvi 
	mkdir -p $(BINDIR) $(LIBDIR) $(DOCDIR)
	install $(BIN_DIR)/$(EXEC_NAME) $(BINDIR)
	install $(LIB_PATH) $(LIBDIR)/$(LIB_NAME)
	@if [ -d "$(DOCS_OUTPUT_DIR)/html" ]; then \
		echo "Installing documentation..."; \
		cp -r $(DOCS_OUTPUT_DIR)/html/* $(DOCDIR)/; \
	else \
		echo "Warning: Documentation not found at $(DOCS_OUTPUT_DIR)/html"; \
	fi

uninstall:
	rm -f $(BINDIR)/$(EXEC_NAME)
	rm -f $(LIBDIR)/$(LIB_NAME)
	rm -rf $(DOCDIR)

dvi:
	mkdir -p $(DOCS_OUTPUT_DIR)
	$(DOCGEN) $(DOXYFILE)

dist: clean
	mkdir -p package
	cp -r $(SRC_DIR) $(TEST_DIR) $(GUI_DIR) Makefile tetris_readme.md package
	tar -czvf  $(TETRIS_TAR) package
	rm -rf package

clean:
	rm -rf $(COV_DIR) $(BIN_DIR) $(BUILD_DIR) $(LIB_DIR) *.gc* *.info $(DOCS_OUTPUT_DIR) $(TETRIS_TAR)

rebuild: clean all

valgrind_test: $(TEST_EXEC)
	valgrind --leak-check=full ./$(BIN_DIR)/$(TEST_EXEC)

clang_test:
	find $(SRC_DIR) brick_game/spec $(TEST_DIR) $(GUI_DIR) -name '*.c' -o -name '*.h' | xargs $(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS)

clang_format:
	find $(SRC_DIR) brick_game/spec $(TEST_DIR) $(GUI_DIR) -name '*.c' -o -name '*.h' | xargs $(CLANG_FORMAT) --style=Google -i
