CFLAGS = -Wall -ggdb

all : client

client: client_kit.o
	$(CC) $^ $(CFLAGS) client.c -o client

client_kit.o:
	$(CC) $(CFLAGS) -c client_kit.c -o client_kit.o

clean:
	rm -f client *.o
