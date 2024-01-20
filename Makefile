
CC = clang
CFLAGS = -std=c99 -fPIC -Wall -Wextra -pedantic \
		 -Wfloat-equal -Wshadow -Wno-unused-parameter \
		 -Werror=switch-enum -Wcast-qual -Wnull-dereference -Wunused-result
INCLUDES = -I src/ -isystem lib/tree-sitter/lib/src/ -isystem lib/tree-sitter/lib/include/
LIBS = -lm

BIN = bin/native/
TARGET = cup

SRC = src/cup.c \
	  lib/tree-sitter/lib/src/lib.c \
	  lib/tree-sitter-cup/src/parser.c
OBJ = $(addprefix $(BIN),$(SRC:.c=.o))

.PHONY: all clean

all: $(TARGET)

$(BIN)lib/%.o: CFLAGS += -w

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

$(BIN)%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BIN) $(TARGET)

