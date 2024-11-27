# Optimize, turn on additional warnings
CFLAGS = -O3 -g 
WFLAGS =-Wall -Wextra -Wpedantic
CC = gcc
.PHONY: all
all: main
SOURCE =  main.c header.h svg.c  z_curve_at.c  z_curve_at_V1.c  z_curve.c  z_curve_pos.c  z_curve_pos_V1.c  z_curve_pos_V2.c  z_curve_V1.c  z_curve_V2.c  z_curve_V3.c
main: ;
	$(CC) $(SOURCE) $(CFLAGS) $(WFLAGS) -o $@ $^ -lm

.PHONY: clean
clean:
	rm -f main 3
#address sanitizer
asan: ;
	$(CC) $(SOURCE) -o $@.out $(CFLAGS) $(WFLAGS) -fsanitize=address -lm

#undefined behavior sanitizer
ubsan: ;
	$(CC) $(SOURCE) -o $@.out $(CFLAGS) $(WFLAGS) -fsanitize=undefined -lm

#memory leak sanitizer
lsan: ;
	$(CC) $(SOURCE) -o $@.out $(CFLAGS) $(WFLAGS) -fsanitize=leak -lm