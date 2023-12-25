CC = g++
CFLAGS = -std=c++2a -I.

all: $(addprefix bin/, $(addsuffix .out, $(basename $(wildcard *.cpp))))

bin/%.out: %.cpp
	mkdir -p $(@D)
	$(CC) -o $@ $^ $(CFLAGS)
