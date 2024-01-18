PROG = main.exe 
SRC = main.cpp user.cpp
CFLAGS = -g -std=c++20
LIBS = -L"/Program Files/OpenSSL-Win64/lib" -Wl,-Bstatic -lssl -lcrypto -Wl,-Bdynamic
CC=g++

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC)  $(LIBS) 

clean:
	rm -f $(PROG)

.PHONY: all clean