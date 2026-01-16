BUILD_DIR = build
PROGRAM_NAME = pacman

.PHONY: setup build clean run

build:
	@cmake --build $(BUILD_DIR)

clean:
	@rm -rf ./$(BUILD_DIR)/*

run:
	./$(BUILD_DIR)/bin/$(PROGRAM_NAME)
