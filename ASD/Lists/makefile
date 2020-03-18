CC = g++
CFLAGS = -std=c++11

.PHONY = all clean

all: ArrayList.x LinkedList.x CursorList.x stdList.x genList.x

%.x: %.cxx
	$(CC) $(CFLAGS) -o $@ $<

clean:
	-rm *.x *.txt
