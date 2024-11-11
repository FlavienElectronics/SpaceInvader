NAME = SpaceInvader
CC = g++
CPPFLAGS = -Wall

SRC_DIR = ./
SRC = *.cpp

TPP =
OBJ_DIR = ./obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

# Initialisation
TOTAL := $(words $(SRC))
COUNT = 0

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@echo "Compiling program:"
	@$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)
	@echo "[${NAME}] Successfully compiled!"

# Compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(TPP) | $(OBJ_DIR)
	$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
	@echo -n "Compiling object files: "
	@echo -n "["

	@for i in seq 1 $(COUNT); do \
		echo -n "▓"; \
	done
	@for i in seq 1 $$(($(TOTAL) - $(COUNT))); do \
		echo -n "-"; \
	done
	@echo -n "] $(shell echo $$(($(COUNT) * 100 / $(TOTAL))))%    "
	@$(CC) $(CPPFLAGS) -c $< -o $@
	@echo -n "\r"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Object files deleted."

fclean: clean
	@rm -f $(NAME)
	@echo "Program deleted."

re: fclean all

# Command to execute
r: $(NAME)
	./$(NAME)
