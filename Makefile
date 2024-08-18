yarl:
	gcc src/main.c --std=c11 -o build/yarl

run: yarl
	./build/yarl

