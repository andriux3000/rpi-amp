# Compiler
CC = g++
MAKEFLAGS += --no-print-directory
SRC = src

#Flags
LDFLAGS = -lbcm2835 -lrpidisplaygl -lpigpio -lrt -lasound
CFLAGS = -Iinclude/ -c -Wall -Wextra -std=c++20 -g

#Build directories and output
MD = mkdir
BUILD=Build
BIN=Bin
TARGET = $(BIN)/test.out

#Project directory structure
SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp, $(BUILD)/%.o, $(SRCS))

.PHONY: all
all: build

$(TARGET): $(OBJS) $(BUILD)
	@echo 'Make EXE file'
	$(MD) -vp $(BIN)
	$(MD) -vp $(BUILD)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo 'Done!'

$(BUILD)/%.o : $(SRC)/%.cpp $(BUILD)
	@echo 'MAKE OBJECT FILE'
	$(CXX) $(CFLAGS) $< -o $@

.PHONY: build
build:
	@echo 'Building: ' $(SRC)
	$(MD) -vp $(BUILD)
	$(MD) -vp $(BIN)
	$(MAKE) $(TARGET)
	@echo '*********************'

.PHONY: clean
clean:
	@echo 'Cleanup!'
	rm -rvf $(BUILD)
	rm -rvf $(BIN)
	@echo '*********************'

.PHONY: run
run:
	sudo $(TARGET)

.PHONY: help
help:
	@echo 'HELP!'
	@echo '*********************'
