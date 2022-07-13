BUILD_DIR = build

EXERCISE_SRC = src/calloc.c src/mmu.c
EXERCISE_OBJ = $(addprefix $(BUILD_DIR)/, $(EXERCISE_SRC:%.c=%.o))

TEST_DIR = tests
TEST_SRC = $(wildcard $(TEST_DIR)/test_*.c)
TEST_OBJ = $(addprefix $(BUILD_DIR)/, $(TEST_SRC:%.c=%))
TEST_TARGET = $(notdir $(TEST_OBJ))
DEBUG_TARGET = $(addprefix gdb_, $(TEST_TARGET))
VALGRIND_TARGET = $(addprefix valgrind_, $(TEST_TARGET))

CC = clang
CC_FLAGS = -Wall -Wextra -g -std=c11

.PHONY: all
all: build build_tests     # Build everything but runs nothing

.PHONY: run
run: all_tests             # Run all tests (alias)

.PHONY: build
build: $(EXERCISE_OBJ)     # Build the exercise

.PHONY: build_tests
build_tests: $(TEST_OBJ)   # Build the tests

.PHONY: all_tests
all_tests: $(TEST_TARGET)  # Run all tests

.PHONY: list_tests
list_tests:
	@echo "List of all test targets"
	@echo "------------------------"
	@for test in $(TEST_TARGET) ; do \
		echo "make $$test"; \
	done

BASH_COLOR_RED = \033[0;31m
BASH_COLOR_NONE = \033[0m
BASH_COLOR_GREEN = \033[32m

.PHONY: $(TEST_TARGET)   # Run a specific test
$(TEST_TARGET): %: $(BUILD_DIR)/tests/%
	@echo ">>> Running $<"
	@./$< && echo -e "<<< $(BASH_COLOR_GREEN)OK$(BASH_COLOR_NONE)" \
		|| echo -e "<<< $(BASH_COLOR_RED)FAILED$(BASH_COLOR_NONE)"

$(EXERCISE_OBJ): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -o $@ -c $<

.PHONY: $(DEBUG_TARGET)
$(DEBUG_TARGET): gdb_%: $(BUILD_DIR)/tests/%
	gdb $<

$(BUILD_DIR)/tests/test_calloc%: tests/test_calloc%.c $(BUILD_DIR)/src/calloc.o
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -o $@ $^

$(BUILD_DIR)/tests/test_mmu%: tests/test_mmu%.c $(BUILD_DIR)/src/mmu.o
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

SUBMISSION_FILES = src/calloc.c src/mmu.c

.PHONY: pack
pack:
	tar czf submission.tar.gz $(SUBMISSION_FILES)
