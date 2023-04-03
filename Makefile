.PHONY: main

main:
	gcc src/main.c -o main -lm -O3 -Wno-unused-result
