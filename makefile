CC=gcc

main.o : driver.c process.c banker.c
	$(CC) -lpthread driver.c process.c banker.c -o main

clean:
	rm -f main