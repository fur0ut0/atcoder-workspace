STD ?= 2a

CC = g++
CFLAGS = -std=c++$(STD) -I. -Wall -Wextra

all: $(addprefix bin/, $(addsuffix .out, $(basename $(wildcard *.cpp))))

bin/%.out: %.cpp
	mkdir -p $(@D)
	$(CC) -o $@ $^ $(CFLAGS)
