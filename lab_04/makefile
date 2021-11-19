CC := gcc
CFLAGS := -std=c99 -Wall -pedantic -ggdb -Iinclude -O0

SRCS := $(shell find src -name "*.c")
OBJS := $(SRCS:src/%.c=out/%.o)

.PHONY: clean data

# all: app.exe
# 	./app.exe

app.exe: $(OBJS)
	$(CC) -o $@ $^

$(OBJS): out/%.o: src/%.c
	mkdir -p $(dir $@) && $(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf out app.exe