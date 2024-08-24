CFLAGS= -Wall -Wpedantic \
		--std=c11 \
		-L lib/raylib/lib -lraylib -I lib/raylib/include

yarl:
	gcc src/main.c src/map.c $(CFLAGS) -o build/yarl

run: yarl
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib/raylib/lib/ ./build/yarl

