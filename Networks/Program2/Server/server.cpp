#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <unistd.h>
#include <fstream>
#include <vector>

#include "chatPerson.h"

using namespace std;

//Protoypes
void parseMessage(char* buffer, int clisock);
void setupClient(char* buffer, int clisock);    

//Global Variables
vector<chatPerson> chatList;
vector<string> messageList;

void handleConnection(int clisock) 
{
	
	int msgSize;
	char buffer[1016]; // 
	memset(buffer, '\0', 1016); // Clear the buffer.
	
	if((msgSize = recv(clisock, buffer, 1015, 0)) < 0) 
	{
		cerr << "Receive error." << endl;
	}
   
    parseMessage(buffer, clisock); 
    
	
	close(clisock);
}


int main(int argc, char* argv[]) 
{
	
	// Set up the socket.
	
	int sockfd, newsockfd;
	unsigned int clilen;
	
	// Structures for client and server addresses.
	struct sockaddr_in server_addr, cli_addr;
	
	// Create the server socket.
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		cerr << "Socket error." << endl;
		exit(1);
	}
	
	memset((void *) &server_addr, 0, sizeof(server_addr)); // Clear the server address structure.
	
	// Set up the server address structure.
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(15000);
	
	// Bind the socket to the server address and port.
	if(bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
	{
		cerr << "Bind error.";
		exit(1);
	}
	
	// Listen on the socket, queue 5 incoming connections.
	listen(sockfd, 10);
	
	// Loop forever, handling connections.
	bool keepRunning = true;
    while(keepRunning) 
	{
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if(newsockfd < 0) 
		{
			cerr << "Accept error." << endl;
			exit(1);
		}
		handleConnection(newsockfd);
	}
	
}

void parseMessage(char* buffer, int clisock)
{
    int msgSize;
    const int maxCommands = 6;
    char name[maxCommands] = "name:";
    char update[maxCommands] = "upda:";
    char sendChar[maxCommands] = "send:";
    char whisper[maxCommands] = "whis:";
    char list[maxCommands] = "list:";
    char read[maxCommands] = "read:";
    
    char* pch;
    pch = strchr(buffer,':');
    int position = 0;
    position = pch-buffer+1;
    

    char command[5];
//    char *commandS = const_cast<char*>(s.c_str());
    for(int j=0;j< 5;j++){
        command[j] = buffer[j];
	    if(j == 4){
		    command[j+1] = '\0';
	    }
    }
	
   
  //Perform actions based on the command sent by client. 
  if (!strcmp(command, name)){
      //name command sent
      setupClient(buffer,clisock); 
         
   
  }else if(!strcmp(command,whisper)){
      //whisper command sent
  }else if (!strcmp(command,read)){
      //read command sent
  }else if (!strcmp(command,list)){    
      //list command sent
  }else if (!strcmp(command, update)){
      //update command sent 
  }else if (!strcmp(command, sendChar)){
      //send command sent
  }else{
      //remove sender from chat     
  }

}

void setupClient(char* buffer, int clisock){
    int msgSize;
    //colon at position 4
    char name[1024];
    for(int i = 5; i<strlen(buffer); i++){
        name[i-5] = buffer[i]; 
    }
    
    string chatName(name);

    chatPerson client(chatName, clisock);
    
    chatList.push_back(client);
    
    string response = "You are now connected to the chat server.";
      char* rep = const_cast<char*>(response.c_str());

      if((msgSize = send(clisock,rep,strlen(rep),0))<0){
          cerr << "Send error" << endl;
      }else{
          cout << msgSize << endl;
          cout << "Client:" << client.getName() << " has connected."<<endl;
      }
      
}
