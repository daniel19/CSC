server: server.o chat.o
	g++ -g -O0 server.o chat.o -o server

chat.o:chatPerson.cpp chatPerson.h
	g++ -c -g -O0 chatPerson.cpp -o chat.o

server.o: server.cpp
	g++ -c -g -O0 server.cpp -o server.o

clean:
	rm *.o

