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

void chatPerson::addWhisper(string w){
    whisperVector.push_back(w);    
}

char* chatPerson::readWhisper(){
    string whisperMessages;
    for(int i =0; i < whisperVector.size(); i++){
        whisperMessages.append(whisperVector[i]);
        whisperMessages.append("\0");
    }
    char* sendWhisper = const_cast<char*>(whisperMessages.c_str());
    return sendWhisper;
}
