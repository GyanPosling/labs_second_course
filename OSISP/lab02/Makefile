CC = cc
BUILD_DIR = build
CPPFLAGS = -Iinclude
CFLAGS = -W -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic

PARENT_SOURCES = src/parent/main.c src/environment.c
CHILD_SOURCES = src/child/main.c src/environment.c

.PHONY: all clean

all: $(BUILD_DIR)/parent $(BUILD_DIR)/child

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/parent: $(PARENT_SOURCES) include/environment.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(PARENT_SOURCES) -o $@

$(BUILD_DIR)/child: $(CHILD_SOURCES) include/environment.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(CHILD_SOURCES) -o $@

clean:
	rm -rf $(BUILD_DIR)
