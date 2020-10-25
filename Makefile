CC          := clang
CFLAGS      := -Wall -Werror -Wextra -Wpedantic
DBG_CFLAGS  := -O0 -g
RLS_CFLAGS  := -O2
LDFLAGS     :=
TARGET      := main

SRC_DIR     := ./src
BUILD_DIR   := ./build
SRCS        := $(shell find $(SRC_DIR) -name "*.c" | grep -v $(TARGET))
OBJS        := $(subst $(SRC_DIR),$(BUILD_DIR),$(SRCS))
OBJS        := $(OBJS:.c=.o)

.PHONY : debug release all clean

debug : CFLAGS += $(DBG_CFLAGS)
debug : all

release : CFLAGS += $(RLS_CFLAGS)
release : all

all : $(TARGET)

$(TARGET) : $(SRC_DIR)/$(TARGET).c $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) $< -c $(CFLAGS) -o $@

clean :
	rm -rf $(TARGET) $(OBJS)
