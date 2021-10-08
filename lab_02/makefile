CC := gcc
CFLAGS := -std=gnu99 -Wall -pedantic -Iinclude

SRCS := $(shell find src -name "*.c")
OBJS := $(SRCS:src/%.c=out/%.o)

N := 10

.PHONY: clean data sort_res.csv

all: app.exe
	./app.exe

data:
	@python datagen.py $(N) > data.txt && echo data has been generated!

sorts: sort_res.csv
	@python sort_graph.py sort_res.csv

sort_res.csv: app.exe
	@./sort_extracter.sh $@

app.exe: $(OBJS)
	$(CC) -o $@ $^

$(OBJS): out/%.o: src/%.c
	mkdir -p $(dir $@) && $(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf out app.exe
