UNAME :=$(shell uname -s)
CCFLAGS := g++ -std=c++11 -g -Wall 
DEBUG := gdb

ifeq ($(UNAME), Darwin)
	LIBFLAGS := -I/usr/local/lib
	BOOSTFLAGS:= -I/usr/local/include/ -I/usr/local/Cellar/boost/*
	CCFLAGS := g++ $(BOOSTFLAGS) $(LIBFLAGS)  -std=c++11 -g -Wall 
	DEBUG := lldb
endif

Hello.o: main.cpp HackerRank.cpp
	$(CCFLAGS) main.cpp -o Hello.exe

run:
	./Hello.exe

clean:
	rm -rv Hello.* *.o

debug:
	$(DEBUG) Hello
