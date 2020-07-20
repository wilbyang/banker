CC=gcc

main.o : driver.c process.c banker.c util.c
	$(CC) driver.c process.c banker.c util.c -lpthread -o bankers

clean:
	rm -f bankers