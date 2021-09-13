SRC := $(shell find src -iname "*.c")
OBJS := $(patsubst src/%.c,out/%.o,$(SRC))

CC := gcc
CFLAGS := --std=c99 -Wall -Werror -ggdb -Iinclude
LDFLAGS := -lm

release: app.exe

app.exe: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJS): out/%.o: src/%.c
	mkdir -p out && $(CC) -o $@ $(CFLAGS) -c $^

clean:
	rm -rf out app.exe
