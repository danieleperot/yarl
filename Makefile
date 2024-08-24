CFLAGS= -Wall -Wpedantic \
		--std=c11 \
		-L lib/raylib/lib -lraylib -I lib/raylib/include

yarl:
	gcc src/main.c src/map.c $(CFLAGS) -o build/yarl

run: yarl
	./build/yarl

