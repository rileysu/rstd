src = $(wildcard src/*.c)
testsrc  =$(wildcard tests/*.c)
tests =$(patsubst tests/%.c,tests/%,$(testsrc))
headers = $(wildcard src/*.h)
obj = $(patsubst src/%.c,obj/%.o,$(wildcard src/*.c))

CFLAGS = -gdwarf-2 -Wall -lm

all: $(obj) tests

tests: $(patsubst tests/%.c,tests/%.out,$(testsrc))

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

tests/%.out: $(obj) $(testsrc)
	$(CC) $(CFLAGS) $(obj) $(patsubst %.out,%.c,$@) -Isrc -o $@

clean:
	rm -f $(obj) $(patsubst tests/%.c,tests/%.out,$(testsrc))
