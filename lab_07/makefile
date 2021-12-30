CC 		:= gcc
CFLAGS 	:= -std=c99 -Wall -Werror -pedantic -Iinc
SRCS 	:= $(shell find src -name "*.c")
OBJS	:= $(SRCS:src/%.c=out/%.o)

.PHONY: clean

app.exe: $(OBJS)
	$(CC) -o $@ $^

$(OBJS): out/%.o : src/%.c
	mkdir -p $(dir $@) && $(CC) $(CFLAGS) -o $@ -c $^

clean:
	rm -rf out *.exe
