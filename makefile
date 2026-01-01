CC = gcc

APP_Name = Chase

INC = -I./include -I./$(SRC_DIR)
CFLAGS = $(INC) -Wall -Wextra -g

SRC_DIR = src
OUT_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)

OBJS = $(SRC:.c=.o)
TARGET	= $(OUT_DIR)/$(APP_Name)


all: $(TARGET) clean_up

$(TARGET): $(OBJS)
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $^ -o $@ 

# Compile each .c into a matching .o next to it
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean_up:
	rm -f $(OBJS)

run:
	$(TARGET)

.PHONY: all clean_up