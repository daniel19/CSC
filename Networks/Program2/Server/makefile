server: server.o chat.o
	g++ server.o chat.o -o server

chat.o:chatPerson.cpp chatPerson.h
	g++ -c chatPerson.cpp -o chat.o

server.o: server.cpp
	g++ -c server.cpp -o server.o

client:
	g++ ../Client/client.cpp -o ../Client/client
clean:
	rm *.o

