#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

int main(int argc, char* argv[]) 
{
	int sockfd;
	struct sockaddr_in server_addr;
	int msgSize, port;
	char message[1024];
	char output[1024]; // Output message from server.
	struct hostent* hent;
	memset(output, '\0', 1024); // Clear the buffer.

	// Check for correct commandline input.
	if(argc < 3) 
	{
		cerr << "Usage: ./client [server name] [port]" << endl;
		exit(1);
	}
	
	port = atoi(argv[2]);
	
	// Error check the port number.
	if(port <= 10000) 
	{
		cerr << "Port > 10000 required." << endl;
		exit(1);
	}
	
	// Error check the server name.
	if((hent=gethostbyname(argv[1])) == NULL) 
	{
		cerr << "Invalid host name." << endl;
		exit(1);
	}
	
	// Create the client socket.
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		cerr << "Socket error." << endl;
		exit(1);
	}
	
	memset((void *) &server_addr, 0, sizeof(server_addr)); // Clear the server address structure.
	
	// Set up the server address structure.
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr = *((struct in_addr *)hent->h_addr);
	server_addr.sin_port = htons(port);

	if(connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
	{
		cerr << "Connect error." << endl;
		exit(1);
	}
	cout <<"What message to send: ";
	cin.getline(message,1024);
	if((msgSize = send(sockfd, message, strlen(message), 0)) < 0) 
	{
		cerr << "Send error." << endl;
	}
		
	// Wait to receive response.
	if((msgSize = recv(sockfd, output, 1023, 0)) < 0) 
	{
		cerr << "Receive error." << endl;
	}
	
	cout << output << endl;		
	close(sockfd);
}

