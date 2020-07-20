CC=gcc

main.o : driver.c process.c banker.c
	$(CC) driver.c process.c banker.c util.c -lpthread -o banker

clean:
	rm -f main