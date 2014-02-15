#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;
//Function Prototypes
void interface();

//int main(int argc, char* argv[]) 
int main()
{
	int sockfd;
	struct sockaddr_in server_addr;
	int msgSize, port;
	char message[1024];
	char output[1024]; // Output message from server.
	struct hostent* hent;
	memset(output, '\0', 1024); // Clear the buffer.
/*
	// Check for correct commandline input.
	if(argc < 3) 
	{
		cerr << "Usage: ./client [server name] [port]" << endl;
		exit(1);
	}
	
	port = atoi(argv[2]);
*/	
    port = 15000;
	
    // Error check the port number.
	if(port <= 10000) 
	{
		cerr << "Port > 10000 required." << endl;
		exit(1);
	}
	
	// Error check the server name.
	//if((hent=gethostbyname(argv[1])) == NULL) 
	if((hent=gethostbyname("localhost")) == NULL)
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
	 // Clear the server address structure.
    memset((void *) &server_addr, 0, sizeof(server_addr));
    
   	
	// Set up the server address structure.
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr = *((struct in_addr *)hent->h_addr);
	server_addr.sin_port = htons(port);

	if(connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
	{
		cerr << "Connect error." << endl;
		exit(1);
	}
	
    //Start interface 
    interface();
    /*
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
	*/
    //keep waiting on user commands then close socket. 
    close(sockfd);

    
}

/*
 * Protocols to send and recieve from server host endsystem.
 *
 * RECEIVING PROTOCOLS
 * CTS:<filename> --> Receiving file contents 
 * ERR:<message>  --> Error message
 * PAS:<message>  --> Transfer was sucessful
 * 
 *
 * Commands to implement
 * GET:<filename>
 * PUT:<filename>
 * QUIT
 *
 * */

//Funtion that handles all the user controls after socket
//has conncted.
void interface(){
   bool stopWorking = false;
   
   //Display Main Menu
    cout << "-----------------------------------\n";
    cout << "| Use commands to access files from|\n";
    cout << "| the server.                      |\n";
    cout << "-----------------------------------\n";

   while(!stopWorking){}
}
