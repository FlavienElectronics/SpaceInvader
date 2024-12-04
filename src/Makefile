NAME = SpaceInvader
CC = g++ -std=c++11
LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -pthread -lboost_system -lboost_thread
CPPFLAGS = -Wall -Wno-reorder -g

SRC_DIR = ./
SRC = main.cpp main_function.cpp Explosion.cpp Monster.cpp Point.cpp Projectile.cpp SpaceShip.cpp MonsterLine.cpp GameOver.cpp YouWon.cpp LetterGroup.cpp ESP.cpp

TPP =
OBJ_DIR = ./obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

# Initialisation
TOTAL := $(words $(SRC))
COUNT = 0

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@echo "Compiling program:"
	@$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME) $(LIBFLAGS)
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

install:
	@if [ "$$(id -u)" -ne 0 ]; then \
		echo "\e[31mYou must use <sudo make install> to proceed the installation !\e[0m"; \
		echo "Installation failed."; \
		exit 1; \
	else \
		echo "Installing the graphic library..."; \
		apt -y install libsfml-dev; \
		echo "Installing the USB library..."; \
		apt -y install libboost-all-dev; \
		echo "Setting udev rule..."; \
		echo 'SUBSYSTEM=="tty", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="ea60", MODE="0666", SYMLINK+="port_ESP8266"' | tee /etc/udev/rules.d/99-usb-access.rules; \
		udevadm control --reload-rules; \
		udevadm trigger; \
		echo "udev rule installed. You can now access the device without sudo via /dev/port_ESP8266."; \
		echo "\e[32m\nThe game is installed!\e[0m"; \
		echo "\e[35mWrite <make r> to run the game, have fun !!\e[0m"; \
	fi
