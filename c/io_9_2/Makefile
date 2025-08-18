TARGET_EXEC := Odenbach_Ilian_9_2.o

BUILD_DIR := ./build
SRC_DIRS := ./src

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
FLAGS := $(INC_FLAGS) -Wall -Wextra -Wpedantic -Werror -Wshadow -Wstrict-overflow -Wconversion -fno-strict-aliasing -Wno-missing-field-initializers -march=native -MMD -MP


$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

.PHONY: run
run: $(BUILD_DIR)/$(TARGET_EXEC)
	@echo "Running $(TARGET_EXEC)"
	$<

-include $(DEPS)
