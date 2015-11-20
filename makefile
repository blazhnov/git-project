CC=gcc
CFLAGS= -o
LIBS=-lsocket -lnsl
LIST=loop.c transport.c errorhandling.c

all:server client

server: $(LIST)
#	$(CC) $(LIBS) $(CFLAGS) server $(LIST)
	$(CC) $(LIBS) $(CFLAGS) server $^
	@echo "building server: ${CC} ${LIBS} ${CFLAGS} server ${LIST}" 
 


client: echoclient.c
	$(CC) $(LIBS) $(CFLAGS) client echoclient.c
	@echo "target client ${CC}"


clean:
	rm -rf *.o server client
	@echo "Successfully cleared"
	 


# -r - remove directories and their contents recursively
# -f - ignore nonexistent files and arguments
	
