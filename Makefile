all: compile

compile:
	  gcc -std=c11 -o brutef main.c crypwrapper.c `libgcrypt-config --cflags --libs`

rainbow:
	gcc -std=c11 -o rainb createRainbow.c crypwrapper.c `libgcrypt-config --cflags --libs`
