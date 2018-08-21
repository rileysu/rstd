src = $(wildcard src/*.c)
testsrc  =$(wildcard tests/*.c)
tests =$(patsubst tests/%.c,tests/%,$(testsrc))
headers = $(wildcard src/*.h)
obj = $(patsubst src/%.c,bin/%.o,$(wildcard src/*.c))

CFLAGS = -gdwarf-2 -Wall

all: $(obj) tests

tests: $(patsubst tests/%.c,tests/%,$(testsrc))

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

tests/%: $(obj)
	$(CC) $(CFLAGS) $(patsubst tests/%test,bin/%.o,$@) $(patsubst %,%.c,$@) -Isrc -o $@

clean:
	rm -f $(obj) all
