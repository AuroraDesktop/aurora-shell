# Compiler
CC      := gcc
LIBS	:= `pkg-config --libs gtk+-3.0` `pkg-config --libs glib-2.0`
CFLAGS  := -Wno-deprecated -Wno-deprecated-declarations -pedantic `pkg-config --cflags gtk+-3.0`

# Directories
SRCDIR  := src
OBJDIR  := obj
INCDIR  := include
BINDIR  := bin

# Files
SRC     := $(wildcard $(SRCDIR)/*/*.c) $(wildcard $(SRCDIR)/*.c)
SRC     := $(filter-out $(SRCDIR)/main.c, $(SRC))
SRC     += $(SRCDIR)/main.c
OBJ     := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
INC     := -I $(INCDIR)

# Prefix
PREFIX  := /usr/local

# Main target
TARGET  := $(BINDIR)/aurora-shell

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGET)

# Create directories if they don't exist
$(OBJDIR) $(INCDIR) $(BINDIR):
	@echo MKDIR $@
	@mkdir -p $@

# Object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) $(INCDIR)
	@mkdir -p $(dir $@)
	@echo CC $<
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# GResource binary
resources.c: resources.xml
	@echo GEN $<
	@glib-compile-resources $< --target=$@ --generate-source

# Target
$(TARGET): $(BINDIR) resources.c $(OBJ)
	@echo LINK $<
	@$(CC) $(CFLAGS) $(OBJ) resources.c -o $@ $(LIBS)

# Clean
clean:
	@echo "Cleaning up root"
	@rm -rf $(OBJDIR) $(BINDIR) resources.c resources.h

# Format
format:
	@echo "Formatting files using clang-format"
	@clang-format --style="{BasedOnStyle: llvm, IndentWidth: 4}" -i `find . -name "*.h"`
	@clang-format --style="{BasedOnStyle: llvm, IndentWidth: 4}" -i `find . -name "*.c"`
	@echo "Done!"

# Install
install: $(TARGET)
	@echo "Installing aurora-shell at $(PREFIX)/bin"
	@install -Dvm755 $(TARGET) $(PREFIX)/bin/
