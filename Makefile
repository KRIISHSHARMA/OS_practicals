CC = gcc
CFLAGS = -Wall -g
BIN_DIR = bin

SRCS = $(wildcard *.c)
TARGETS = $(SRCS:%.c=$(BIN_DIR)/%)

all: $(TARGETS)

$(BIN_DIR)/%: %.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean
