#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>


using namespace std;

class chatPerson{
    private:
        string name;
        int clientSocket;
    public:
        chatPerson(string, int);
        string getName();
        int getSocket();

};
