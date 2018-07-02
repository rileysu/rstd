src = $(wildcard src/*.c)
tests  =$(wildcard tests/*.c)
headers = $(wildcard src/*.h)
obj = $(patsubst src/%.c,bin/%.o,$(wildcard src/*.c))

CFLAGS = -gdwarf-2 -Wall

all: $(obj)

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

tests: $(obj)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(obj) all
