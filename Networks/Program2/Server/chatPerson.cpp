#include "chatPerson.h"

//Constructors
void chatPerson::chatPerson(string n, int s){
    name = n;
    clientSocket = s;
    total++;
}
void chatPerson::chatPerosn(){
    total++;
}

//Getter Methods
int getSocket(){
    return clientSocket;
}

string getName(){
    return name;
}

//Setter Methods
void setSocket(int s){
    clientSocket = s;
}

void setName(string n){
    name = n;
}
