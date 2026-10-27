# Compile code run tests check coverage and memory leaks

CXX = g++
LCOV = lcov
GENHTML = genhtml
VALGRIND = valgrind

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = include
TESTS_DIR = tests
TESTS_SRC_DIR = $(TESTS_DIR)/src
TESTS_OBJ_DIR = $(TESTS_DIR)/obj
TESTS_BIN_DIR = $(TESTS_DIR)/bin
TESTS_HTMLCOV_DIR = $(TESTS_DIR)/htmlcov
TESTS_HTMLCONV_DIR = $(TESTS_DIR)/htmlconv

COVERAGE_INFO_FILE = $(TESTS_HTMLCOV_DIR)/lcov.info

CPPFLAGS = -I$(INC_DIR) -I$(TESTS_SRC_DIR)
CXXFLAGS = -O0 -std=c++20 -g
TEST_CXXFLAGS = $(CXXFLAGS) --coverage
TEST_LDLIBS = -lgtest -lgtest_main -pthread


IMPLEMENTATION_CPP = $(filter-out $(SRC_DIR)/makefriends.cpp,$(wildcard $(SRC_DIR)/*.cpp))
IMPLEMENTATION_OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(IMPLEMENTATION_CPP))
TEST_IMPLEMENTATION_OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(TESTS_OBJ_DIR)/%.o,$(IMPLEMENTATION_CPP))


UNION_TEST_CPP = $(wildcard $(TESTS_SRC_DIR)/*UnionFind*Test.cpp)
MAP_TEST_CPP = $(wildcard $(TESTS_SRC_DIR)/*Map*Test.cpp)
FRIEND_TEST_CPP = $(wildcard $(TESTS_SRC_DIR)/*FriendGroups*Test.cpp)

UNION_TEST_OBJ = $(patsubst $(TESTS_SRC_DIR)/%.cpp,$(TESTS_OBJ_DIR)/%.o,$(UNION_TEST_CPP))
MAP_TEST_OBJ = $(patsubst $(TESTS_SRC_DIR)/%.cpp,$(TESTS_OBJ_DIR)/%.o,$(MAP_TEST_CPP))
FRIEND_TEST_OBJ = $(patsubst $(TESTS_SRC_DIR)/%.cpp,$(TESTS_OBJ_DIR)/%.o,$(FRIEND_TEST_CPP))

MAKEFRIENDS = $(BIN_DIR)/makefriends
TEST_UNION_FIND = $(TESTS_BIN_DIR)/testunionfind
TEST_MAP = $(TESTS_BIN_DIR)/testmap
TEST_FRIENDS = $(TESTS_BIN_DIR)/testfriendgroups

.DEFAULT_GOAL := all

.PHONY: all make_directories tests run_testunionfind run_testmap run_testfriendgroups coverage valgrind run_data clean

all: run_data


make_directories:
	mkdir -p $(BIN_DIR) $(OBJ_DIR) $(TESTS_BIN_DIR) $(TESTS_OBJ_DIR) $(TESTS_HTMLCOV_DIR) $(TESTS_HTMLCONV_DIR)

$(BIN_DIR) $(OBJ_DIR) $(TESTS_BIN_DIR) $(TESTS_OBJ_DIR) $(TESTS_HTMLCOV_DIR) $(TESTS_HTMLCONV_DIR):
	mkdir -p $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


$(TESTS_OBJ_DIR)/%.o: $(TESTS_SRC_DIR)/%.cpp | $(TESTS_OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(TEST_CXXFLAGS) -c $< -o $@

$(TESTS_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(TESTS_OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(TEST_CXXFLAGS) -c $< -o $@


$(TEST_UNION_FIND): $(UNION_TEST_OBJ) $(TEST_IMPLEMENTATION_OBJ) | $(TESTS_BIN_DIR)
	$(CXX) $(TEST_CXXFLAGS) $^ --coverage $(TEST_LDLIBS) -o $@


$(TEST_MAP): $(MAP_TEST_OBJ) $(TEST_IMPLEMENTATION_OBJ) | $(TESTS_BIN_DIR)
	$(CXX) $(TEST_CXXFLAGS) $^ --coverage $(TEST_LDLIBS) -o $@


$(TEST_FRIENDS): $(FRIEND_TEST_OBJ) $(TEST_IMPLEMENTATION_OBJ) | $(TESTS_BIN_DIR)
	$(CXX) $(TEST_CXXFLAGS) $^ --coverage $(TEST_LDLIBS) -o $@


$(MAKEFRIENDS): $(OBJ_DIR)/makefriends.o $(IMPLEMENTATION_OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@


run_testunionfind: $(TEST_UNION_FIND)
	$(TEST_UNION_FIND)

run_testmap: $(TEST_MAP)
	$(TEST_MAP)

run_testfriendgroups: $(TEST_FRIENDS)
	$(TEST_FRIENDS)

tests: run_testunionfind run_testmap run_testfriendgroups


coverage: tests | $(TESTS_HTMLCOV_DIR) $(TESTS_HTMLCONV_DIR)
	$(LCOV) --capture --directory . --output-file $(COVERAGE_INFO_FILE) --ignore-errors inconsistent,source
	$(LCOV) --remove $(COVERAGE_INFO_FILE) '/usr/*' '*/tests/src/*' --output-file $(COVERAGE_INFO_FILE)
	$(GENHTML) $(COVERAGE_INFO_FILE) --output-directory $(TESTS_HTMLCOV_DIR)


valgrind: coverage $(MAKEFRIENDS)
	$(VALGRIND) --leak-check=full --errors-for-leak-kinds=definite,indirect --error-exitcode=1 $(MAKEFRIENDS) -f data/friendsmed.csv -v > /dev/null


run_data: valgrind
	@set -e; for file in data/friends1.csv data/friendssm.csv data/friendsmed.csv data/friendslg.csv; do \
		echo "Running $$file"; \
		$(MAKEFRIENDS) -f "$$file" -v > /dev/null; \
	done
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(TESTS_BIN_DIR) $(TESTS_OBJ_DIR) $(TESTS_HTMLCOV_DIR) $(TESTS_HTMLCONV_DIR)