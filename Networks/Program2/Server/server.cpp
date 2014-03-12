#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <unistd.h>
#include <fstream>

using namespace std;

//Protoypes
void parseMessage(char* buffer, int clisock);
    
    
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
    
	cout << "Message received from client: " << buffer<<endl;
	char response[1024];
//	sprintf(response, "Server: I received the following message:  %s", buffer);
	
	if((msgSize = send(clisock, response, strlen(response), 0)) < 0) 
	{
		cerr << "Send error." << endl;
	}
	
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
    const int maxCommands = 6;
    string commands[maxCommands]={ "whis:", "read:", 
                                   "list:", "udpa:",
                                   "send:", "quit"};

    for(int i=0; i < maxCommands; i++){
        commands[i] = const_cast<char*>(commands[i].c_str());
    }
    
    char* pch;
    pch = strchr(buffer,':');
    int position = 0;
    position = pch-buffer+1;
    

    char command[5];
//    string s = "list:";
//    char *commandS = const_cast<char*>(s.c_str());
    for(int j=0;j< 5;j++){
        command[j] = buffer[j];
	    if(j == 4){
		    command[j+1] = '\0';
	    }
    }
	
  //Perform actions based on the command sent by client. 
  if(strcmp(command,commands[0])){
      //whisper command sent
  }else if (strcmp(command,commands[1])){
      //read command sent
  }else if (strcmp(command,commands[2])){    
      //list command sent
  }else if (strcmp(command, commands[3])){
      //update command sent 
  }else if (strcmp(command, commands[4])){
      //send command sent
  }else{
      //remove sender from chat     
  }

}

