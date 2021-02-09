ifeq ($(OS),Windows_NT)
	uname_S := Windows
	WinBuild = 1
	BFLAGS= -DWinBuild
else 
	uname_S := $(shell uname -s)
	BFLAGS= 	
endif

# Declaration of variables
CC = gcc
CC_FLAGS = -w -g


client: client.o
	$(CC) client.o -o client

### Build stuff
# To obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $(BFLAGS) $< -o $@

clean:
	rm -rf client *.o
