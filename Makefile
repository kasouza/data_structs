OBJS := main.o array.o

all: data_structs

data_structs: $(OBJS)
	cc -o $@ $^

main.o: main.c array.h
array.o: array.c array.h
