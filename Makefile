.PHONY: setup build clean run

BUILD_DIR = build
PROGRAM_NAME = pacman

setup:
	@mkdir -p $(BUILD_DIR)
	@cmake -S . -B $(BUILD_DIR) -G "Ninja"

build:
	@cmake --build $(BUILD_DIR)

clean:
	@rm -rf ./$(BUILD_DIR)/*

run:
	./$(BUILD_DIR)/bin/$(PROGRAM_NAME)
