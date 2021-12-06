CC := gcc
SRCS := $(shell find src -name *.c)
OBJS := $(SRCS:src/%.c=out/%.o)
CFLAGS := -std=c99 -Wall -Werror -pedantic -Iinc -Wno-unused-function
LDFLAGS := -lm

.PHONY: clean

app.exe: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJS): out/%.o : src/%.c
	mkdir -p $(dir $@) && $(CC) $(CFLAGS) -o $@ -c $^

clean:
	rm -rf *.exe out