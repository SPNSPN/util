SRC := src
INC := include
BLD := build

PRJ := util

GCC := g++
CFLAGS := -std=c++17 -Wall -O2 -I$(INC)
DBG := -g3 -O0

SRCS := $(wildcard $(SRC)/*.cpp)
OBJS := $(patsubst $(SRC)/%.cpp,$(BLD)/%.o,$(SRCS))

TARGET := $(BLD)/$(PRJ)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(GCC) $(CFLAGS) -o $@ $^

$(BLD)/%.o: $(SRC)/%.cpp
	$(GCC) $(CFLAGS) -c -o $@ $<

.PHONY: run
run: $(TARGET)
	$(TARGET)


.PHONY: clean
clean:
	rm $(BLD)/*

