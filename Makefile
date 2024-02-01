PROG = main.exe
TESTPROG = test.exe
SRC = main.cpp user.cpp crack.cpp
TESTSRC = test.cpp user.cpp crack.cpp
CFLAGS = -g -std=c++20
LIBS = -L"/Program Files/OpenSSL-Win64/lib" -Wl,-Bstatic -lssl -lcrypto -Wl,-Bdynamic
CC=g++ -lssl -lcrypto
GTEST = gtest
LIBGTEST = C:\msys64\mingw64\lib\libgtest_main.a C:\msys64\mingw64\lib\libgtest.a

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC) $(LIBS) 

$(TESTPROG): $(TESTSRC)
	$(CC) -o $@ $^  -I $(GTEST)  $(LIBGTEST) $(LIBS)

test: $(TESTPROG)
	./$(TESTPROG)

clean:
	rm -f $(PROG)

.PHONY: all clean