.PHONY: clean

search-cli: main.o search.o stats.o mylib.o
	gcc -o search-cli main.o search.o stats.o mylib.o

main.o: main.c search.h stats.h draw.h mylib.h
	gcc -c main.c
	
search.o: search.c search.h stats.h mylib.h
	gcc -c search.c
	
stats.o: stats.c stats.h mylib.h
	gcc -c stats.c
	
mylib.o: mylib.c mylib.h
	gcc -c mylib.c
	

clean:
	rm -f search.o stats.o main.o mylib.o search-cli

