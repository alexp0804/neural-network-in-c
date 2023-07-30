.PHONY: main

main:
	gcc lib/main.c -o main -lm -O3 -Wno-unused-result
