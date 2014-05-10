# Copyright 2014 Torin Cooper-Bennun
# 
# This file is part of battlecurses.
# 
# battlecurses is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# battlecurses is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with battlecurses. If not, see <http://www.gnu.org/licenses/>.

CC = gcc
RM = rm -f
CFLAGS = -O0 -g -Wall -pedantic -DUSING_NCURSES
LIBS = -lncurses -lz
OUT = proj
OBJS = main.o gui.o check.o

all: $(OUT)

clean:
	$(RM) $(OUT) $(OBJS)

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

main.o: gui.h check.h
gui.o: gui.h
check.o: check.h
