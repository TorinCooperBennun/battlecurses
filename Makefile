CC = gcc
RM = rm -f
CFLAGS = -O0 -g -Wall -pedantic
LIBS = -lncurses
OUT = proj
OBJS = main.o gui.o

all: $(OUT)

clean:
	$(RM) $(OUT) $(OBJS)

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

main.o: gui.h
gui.o: gui.h
