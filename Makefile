
INCLUDE_DIRS = -I./inc
SRC_DIRS = src
OBJ_DIR = obj

SOURCE_FILES = $(wildcard $(SRC_DIRS)/*.c)
OBJECT_FILES = $(patsubst $(SRC_DIRS)/%.c, $(OBJ_DIR)/%.o, $(SOURCE_FILES))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -g $(INCLUDE_DIRS)

TARGET = main
ARBITRARY = $(AUTHOR).zip $(AUTHOR).tar.gz *.txt test_folder test_file
AUTHOR = "Emirhan_Altunel_200104004035"

all: $(TARGET).out

$(TARGET).out: $(OBJECT_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDE_DIRS)

$(OBJ_DIR)/%.o: $(SRC_DIRS)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE_DIRS)

clean:
	rm -f $(TARGET).out

fclean: clean
	rm -f $(OBJECT_FILES)
	rm -rf $(OBJ_DIR)
	rm -rf $(ARBITRARY)

re: fclean all

$(AUTHOR).zip: Makefile inc src README.md README.pdf
	@zip -r $(AUTHOR).zip Makefile inc src
	@if [ -f README.md ]; then zip -r $(AUTHOR).zip README.md; fi
	@if [ -f README.pdf ]; then zip -r $(AUTHOR).zip README.pdf; fi

$(AUTHOR).tar.gz: Makefile inc src README.md README.pdf
	@tar -czvf $(AUTHOR).tar.gz Makefile inc src
	@if [ -f README.md ]; then tar -czvf $(AUTHOR).tar.gz README.md; fi
	@if [ -f README.pdf ]; then tar -czvf $(AUTHOR).tar.gz README.pdf; fi

pack: $(AUTHOR).zip $(AUTHOR).tar.gz

.PHONY: all clean fclean re pack
