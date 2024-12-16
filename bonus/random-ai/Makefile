##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC				:=	$(shell find src/ ../../src/cmd/ -name "*.cpp") \
					../../src/BoardManager.cpp \
					../../src/Logger.cpp \
					../../src/main.cpp \
					../../src/Pos.cpp \
					../../src/SplitString.cpp \
					../../src/TrackedException.cpp

CPPFLAGS		=	--std=c++20 -Wall -Wextra -O2 \
					-I./include/ -I../../include/ \
					$(ADDITIONAL_FLAGS)

NAME			=	pbrain-random-ai

SRC_TESTS		:=	tests/tests.cpp

RUN_TEST		=	--coverage -lcriterion

NAME_TESTS		=	unit_tests

OBJ				=	$(SRC:.cpp=.o)

%.o: %.cpp
	@g++ $(CPPFLAGS) -c $< -o $@ && \
	printf "[\e[92mOK\e[0m] g++ $(CPPFLAGS) -c $< -o $@\n" || \
	printf "[\e[1;91mKO\e[0m] g++ $(CPPFLAGS) -c $< -o $@\n"

$(NAME): $(OBJ)
	@if g++ -o $(NAME) $(OBJ) $(CPPFLAGS); then\
		printf "[\e[92mCOMPILATION OK\e[0m] "; \
		printf "g++ -o $(NAME) $(OBJ) $(CPPFLAGS)\n"; \
	else \
		printf "[\e[1;91mCOMPILATION KO\e[0m] "; \
		printf "g++ -o $(NAME) $(OBJ) $(CPPFLAGS)\n"; \
		exit 1; \
	fi

all: $(NAME)

clean:
	rm -f $(OBJ) $(shell find src/ -name "*.o")
	rm -f $(shell find src/ -name "*.gcno")
	rm -f $(shell find src/ -name "*.gcda")
	rm -f *.gcno *.gcda gmon.out

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_TESTS)

re: fclean all

unit_tests: SRC := $(patsubst src/main.cpp%,%,$(SRC))
unit_tests: clean
	@if g++ -o $(NAME_TESTS) $(SRC_TESTS) $(SRC) \
	 $(CPPFLAGS) $(RUN_TEST); then \
		printf "[\e[92mCOMPILATION OK\e[0m] "; \
		printf "g++ -o $(NAME_TESTS) $(SRC_TESTS) $(SRC)"; \
		printf " $(CPPFLAGS) $(RUN_TEST)\n"; \
	else \
		printf "[\e[1;91mCOMPILATION KO\e[0m] "; \
		printf "g++ -o $(NAME_TESTS) $(SRC_TESTS) $(SRC)"; \
		printf " $(CPPFLAGS) $(RUN_TEST)\n"; \
		exit 1; \
	fi

tests_run: unit_tests
	./$(NAME_TESTS)

gcovr:
	@gcovr --sort-percentage --exclude tests/
	@gcovr --sort-percentage --exclude tests/ --branches

debug: CPPFLAGS += -g3
debug: clean all
	gdb -ex "run $(arg)" -ex "bt full" -ex "detach" -ex "quit" $(NAME)

profiling: CPPFLAGS += -pg
profiling: clean all
	@printf "\e[0m------------------------------\e[0m\n"
	./$(NAME) $(arg)
	@printf "\e[0m------------------------------\e[0m\n"
	gprof $(NAME) gmon.out

compilation_database: clean
	bear -- make

code_analyse: compilation_database
	clang-tidy --config-file=.clang-tidy \
		-header-filter=.* --use-color $(SRC)

.PHONY: all clean fclean re unit_tests tests_run gcovr \
	debug profiling compilation_database code_analyse
