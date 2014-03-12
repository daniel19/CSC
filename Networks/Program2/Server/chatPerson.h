#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>


using namespace std;

class chatPerson{
    protected:
        string name;
        int clientSocket;
    public:
        static int total;
        
        //Constructuors
        chatPerson(string, int);
        chatPerson();

        //Getter Functions
        string getName();
        int getSocket();

        //Setter Functions
        void setName(string n);
        void setSocket(int s);
};

