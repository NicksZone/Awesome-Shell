CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-parameter -I.

BIN_DIR = bin
SHELL_SRC = shell
CMD_SRC = commands

SHELL_SRCS = $(wildcard $(SHELL_SRC)/*.c)
CMD_SRCS   = $(wildcard $(CMD_SRC)/*.c)

SHELL_TARGET = $(BIN_DIR)/lsh
CMD_TARGETS  = $(patsubst $(CMD_SRC)/%.c,$(BIN_DIR)/%,$(CMD_SRCS))

all: $(SHELL_TARGET) $(CMD_TARGETS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Shell build
$(SHELL_TARGET): $(SHELL_SRCS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(SHELL_SRCS) -o $@

# Commands build (one rule for all)
$(BIN_DIR)/%: $(CMD_SRC)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR)