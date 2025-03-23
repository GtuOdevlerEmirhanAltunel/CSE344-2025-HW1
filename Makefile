
INCLUDE_DIRS = -I./inc
SRC_DIRS = src
OBJ_DIR = obj

SOURCE_FILES = $(wildcard $(SRC_DIRS)/*.c)
OBJECT_FILES = $(patsubst $(SRC_DIRS)/%.c, $(OBJ_DIR)/%.o, $(SOURCE_FILES))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -g $(INCLUDE_DIRS)

TARGET = main
ARBITRARY = $(TARGET).zip $(TARGET).tar.gz *.txt test_folder test_file

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

$(TARGET).zip: Makefile inc src README.md README.pdf
	@zip -r $(TARGET).zip Makefile inc src
	@if [ -f README.md ]; then zip -r $(TARGET).zip README.md; fi
	@if [ -f README.pdf ]; then zip -r $(TARGET).zip README.pdf; fi

$(TARGET).tar.gz: Makefile inc src README.md README.pdf
	@tar -czvf $(TARGET).tar.gz Makefile inc src
	@if [ -f README.md ]; then tar -czvf $(TARGET).tar.gz README.md; fi
	@if [ -f README.pdf ]; then tar -czvf $(TARGET).tar.gz README.pdf; fi

pack: $(TARGET).zip $(TARGET).tar.gz

.PHONY: all clean fclean re pack
