SRCS := $(shell find . -maxdepth 1 -type f -name '*.c' -exec basename {} \;)
OBJS := $(SRCS:%.c=%.o)
DEPS := $(OBJS:%.o=%.d)
FLGS := -std=c2x -g -O0 -Wall -Wextra -pedantic -MMD -MP
CC   := gcc
EXE  := mbm

.PHONY: all bin clean

all: bin

bin: $(OBJS)
	$(CC) $(FLGS) -o $(EXE) $(OBJS) `./lib/bin/sdl2-config --libs` -lm -lSDL2_ttf -lSDL2_mixer

%.o: %.c
# this target deletes the implicit rule for generating .o
# files--we only want to use the target from the next line

$(OBJS): %.o: %.c
# compile any .c file into the corresponding .o file
	$(CC) $(FLGS) -c $< -o $@ `./lib/bin/sdl2-config --cflags`

-include $(DEPS)

clean:
	-rm -f *.o *.d $(EXE)
