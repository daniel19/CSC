#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <unistd.h>

using namespace std;

//Protoypes
void receivingFile();
void sendingFile();

void handleConnection(int clisock) 
{
	
	int msgSize;
	char buffer[1016]; // 
	memset(buffer, '\0', 1016); // Clear the buffer.
	
	if((msgSize = recv(clisock, buffer, 1015, 0)) < 0) 
	{
		cerr << "Receive error." << endl;
	}
    
    if(buffer == "GET"){
        //send repsonse for sending file
       sendingFile(); 
    }else if (buffer == "PUT"){
        //send response for awaiting file
        receivingFile();
    }else{
    }
   
    /*
	cout << "Message received from client: " << buffer<<endl;
	char response[1024];
	sprintf(response, "Server: I received the following message:  %s", buffer);
	
	if((msgSize = send(clisock, response, strlen(response), 0)) < 0) 
	{
		cerr << "Send error." << endl;
	}
	*/
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

/*
 * Send File
 */
void sendingFile(){
    
}

/*
 * ReceivingFile
 */
void receivingFile(){
 int bytes_read = 1;
 int bytesSent;

}
