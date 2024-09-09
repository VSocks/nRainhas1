output: nRainhas1.o
	gcc nRainhas1.o -o nRainhas1

nRainhas.o: nRainhas1.c
	gcc -c nRainhas1.c

clean:
	rm *.o nRainhas1