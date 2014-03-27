#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <fstream>

using namespace std;
//Function Prototypes
void interface(char messeage[1024], int sockfd);

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
	// Check for correct commandline input.
/*	if(argc < 3) 
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

    cout << "Connecting to your Chat Server....." << endl;
    //Start interface 
    interface(message,sockfd);




    //keep waiting on user commands then close socket. 
    close(sockfd);

    
}


 

//Funtion that handles all the user controls after socket
//has conncted.
void interface(char message[1024], int sockfd){
   bool stopWorking = false;
   char output[1024]; // Output message from server.
    int msgSize;
   //Display Main Menu
    cout << "-----------------------------------\n";
    cout << "| Use commands to interact with    |\n";
    cout << "| chat server.                     |\n";
    cout << "-----------------------------------\n";
    
    cout << "Type 'README' after entering your name to access readme file. " << endl;
   cout << "socket: " << sockfd << endl; 

    cout << endl << "PLEASE ENTER YOUR NAME." << endl;
    string name = "";
    getline(cin,name);

    //Send name to server
    name.insert(0,"name:");
    char* sendName = const_cast<char*>(name.c_str());
    if(( msgSize = send(sockfd, sendName, strlen(sendName), 0)) < 0) {
            cerr << "Initial Error" << endl;
    }
 
    if((recv(sockfd, output, 1024, 0)<0)){
        cerr << "Error Connecting" << endl;
    }else{
        cout <<  output << endl;
        memset(output,'\0',sizeof(output));
    }

   while(!stopWorking){
     cout << "________Ready for commands________"<< endl;
       
       
     string input ="";
    
     getline(cin,input);

     if(input == "README"){
         //Get README file 
         char file[10] = "README.md";
         ifstream localFile; 
         localFile.open(file, ifstream::in);

         char c = localFile.get();

         while(localFile.good()){
            cout << c;
            c = localFile.get();
         }
      
         localFile.close();
     }
   
     //cin.clear();
     //getline(cin, input);
     //Process Commands   
     string command = input.substr(0,5);
     
       if(command == "list:"){
           char* sendCommand = const_cast<char*>(command.c_str());
           //Request available chat list
           if(( msgSize = send(sockfd, sendCommand,  strlen(sendCommand), 0)) < 0){
                   cerr << "Request Error" << endl;
           }
        //cout << msgSize << endl;
           cout << "List of present chatters:" <<endl;
           //cout << "socket in list: " << sockfd << endl;
            if((recv(sockfd, output, 1024, 0)<0)){
                cerr << "Error Connecting" << endl;
            }else{
                cout <<  output << endl;
            }       

           
           
       }else if(command == "whis:"){
            //Whisper to one client. 
       }else if(command == "send:"){
           //send to main chat list
       }else if(command == "upda:"){
            //request update of current chat

       }else if(command == "QUIT"){
		//quit on anything else
		stopWorking = true;	
	}else{
        cerr << "Command Not Found" << endl << endl;
   }
   } 
   
}