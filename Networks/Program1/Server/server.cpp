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

//TODO: Clean up code by adding proper inline comments and header comments

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
    char* pch;
    pch = strchr(buffer,':');
    const int position = pch-buffer+1;
    int position2 = position; 

    char command[4];
    const char *commandS = "GET:"; 
    for(int j=0;j< 4;j++){
        command[j] = buffer[j];
        if(j == 3){
            command[j+1] = '\0';
        }
    }
   
    cout <<"Position Two: " << position2 << endl; 
    if(!strcmp(commandS, command)){
        //Get command recieved
        cout << "Get command received" <<endl;
		
        //char filename[strlen(buffer)-position];
        string filename;
        for(int j=0; j < strlen(buffer); j++){
           if(j >= position){
               filename += buffer[j];
           }
        }
        //send file to client
        char* file = const_cast<char*>(filename.c_str());
        ifstream localFile(file);
        localFile.seekg(0,localFile.end);
        long size = localFile.tellg();
        localFile.seekg(0);

        char* buffer = new char[size];

        if(localFile.failbit){
           localFile.read(buffer,size);
        }else{
            cout << "Unable to open file"<<endl;
            return;
        }
        //Append filename in front of buffer
        char* msgOne = new char[strlen(file)+1];
        memcpy(msgOne,file,strlen(file)+1);

        char* fullMsg = new char[strlen(msgOne) + strlen(buffer)+1];
        strcat(fullMsg,msgOne);
        strcat(fullMsg,":");
        strcat(fullMsg,buffer);
        //send msg to server for file.
        //Send command message
            
        int msgSize;
        if((msgSize = send(clisock, fullMsg, strlen(fullMsg), 0)) < 0) 
        {
            cerr << "Send error." << endl;
        }
    }else{
        char filename[position];

        for(int i = 0; i< position-1;i++){
            filename[i] = buffer[i];
           if(i == position-2){
                filename[i+1] = '\0';
           }           
        }
        cout << "filename: " << filename << endl;
        //create file to put on server
        ofstream outputFile(filename);
        for(int i =0;i<strlen(buffer)-1;i++){
          if(i >= position && i < strlen(buffer)){
               outputFile << buffer[i];
          }
        }
    }
}

