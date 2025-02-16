.PHONY: build clean run

BUILD_DIR = build
PROGRAM_NAME = pacman

build:
	@mkdir -p $(BUILD_DIR) 
	@cmake -S . -B $(BUILD_DIR) -G "Unix Makefiles"
	@cmake --build $(BUILD_DIR)

clean:
	@rm -rf $(BUILD_DIR)

run:
	./$(BUILD_DIR)/bin/$(PROGRAM_NAME)
