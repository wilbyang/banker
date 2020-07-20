CC=gcc

main.o : driver.c process.c banker.c
	$(CC) -lpthread driver.c process.c banker.c util.c -o banker

clean:
	rm -f main