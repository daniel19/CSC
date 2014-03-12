#include "chatPerson.h"
int chatPerson::total = 0;
//Constructors
chatPerson::chatPerson(string n, int s){
    name = n;
    clientSocket = s;
    total++;
}
chatPerson::chatPerson(){
    total++;
}

//Getter Methods
int chatPerson::getSocket(){
    return clientSocket;
}

string chatPerson::getName(){
    return name;
}

//Setter Methods
void chatPerson::setSocket(int s){
    clientSocket = s;
}

void chatPerson::setName(string n){
    name = n;
}
