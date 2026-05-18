CC := clang

SRC_DIR := src
OBJ_DIR := obj
BUILD_DIR := build
INCLUDE_DIR := include

CFLAGS := -g -std=c99 -O0 -Wall -I$(INCLUDE_DIR)

SRC := $(shell find $(SRC_DIR) -type f -name *.c)
OBJ := $(patsubst %.c,%.c.o,$(SRC))
OBJ := $(subst $(SRC_DIR),$(OBJ_DIR),$(OBJ))
DEP := $(patsubst %.c.o,%.c.d,$(OBJ))

-include $(DEP)

$(OBJ_DIR)/%.c.o: $(SRC_DIR)/%.c
	@echo Compiling $<
	@mkdir -p $(dir $@)
	@$(CC) -c -MMD $(CFLAGS) $< -o $@

Executable: $(OBJ)
	@echo Linking Executable.elf
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(OBJ) -o $(BUILD_DIR)/Executable.elf

.PHONY: Executable
