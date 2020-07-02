.PHONY: clean

search-cli: main.o search.o stats.o
	gcc -o search-cli main.o search.o stats.o

main.o: main.c search.h stats.h
	gcc -c main.c
	
search.o: search.c search.h
	gcc -c search.c
	
stats.o: stats.c stats.h
	gcc -c stats.c

clean:
	rm -f search.o stats.o main.o search-cli

