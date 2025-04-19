AS ?= as
LD ?= ld

OBJS = week_1_taks.o

# LINKER ?= linker.ld

TARGET ?= main.a

.PHONY: all clean build launch

all: clean build

clean:
	rm $(OBJS) $(TARGET)

build: $(TARGET)

launch: $(TARGET)
	./$(TARGET)

%.o: %.s
	$(AS) -o $@ $<

$(TARGET): $(OBJS)
	$(LD) -o $@ -t $^
