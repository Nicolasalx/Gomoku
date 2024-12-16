##
## EPITECH PROJECT, 2024
## B-AIA-500-PAR-5-1-gomoku-thibaud.cathala
## File description:
## Makefile
##

BUILD_DIR	=	build/

NAME		=	pbrain-gomoku-ai

all:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=release ..
	@$(MAKE) -C $(BUILD_DIR)
	@mv build/$(NAME) ./

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(shell find src/ -name "*.o")
	rm -f $(shell find src/ -name "*.gcno")
	rm -f $(shell find src/ -name "*.gcda")
	rm -f *.gcno *.gcda gmon.out

fclean: clean
	rm -f $(NAME)

re: clean all

debug: fclean
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=debug ..
	@$(MAKE) -C $(BUILD_DIR)
	@mv build/$(NAME) ./

compilation_database: clean
	bear -- make

code_analyse: compilation_database
	clang-tidy --config-file=.clang-tidy \
		-header-filter=.* --use-color $(shell find src/ -name "*.cpp")

.PHONY: all clean fclean re debug compilation_database code_analyse
