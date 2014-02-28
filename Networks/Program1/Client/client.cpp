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

int main(int argc, char* argv[]) 
//int main()
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
	
 // port = 15000;
	
    // Error check the port number.
	if(port <= 10000) 
	{
		cerr << "Port > 10000 required." << endl;
		exit(1);
	}
	
	// Error check the server name.
	if((hent=gethostbyname(argv[1])) == NULL) 
	//if((hent=gethostbyname("localhost")) == NULL)
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
    interface(message,sockfd);
    /*
    cout <<"What message to send: ";
	cin.getline(message,1024);
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
void interface(char message[1024], int sockfd){
   bool stopWorking = false;
   char output[1024]; // Output message from server.
    int msgSize;
   //Display Main Menu
    cout << "-----------------------------------\n";
    cout << "| Use commands to access files from|\n";
    cout << "| the server.                      |\n";
    cout << "-----------------------------------\n";

    string input ="";
   // char buffer[1024];
   while(!stopWorking){
    getline(cin,input);
    
    //get first four characters of input
    string command = input.substr(0,4);
    
    //switch(command){
      //  case "GET:":
	if(command == "PUT:"){        
	          string filename = input.substr(4);
              char* file = const_cast<char*>(filename.c_str());
		  //call functions to retrieve file



         ifstream localFile(file);
         localFile.seekg(0,localFile.end);
         long size = localFile.tellg();
         localFile.seekg(0);

         char* buffer = new char[size];

         if(localFile.failbit){
           localFile.read(buffer,size);
         }else{
            cout << "Unable to open file"<<endl;
            break;
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
            message = fullMsg;
			if((msgSize = send(sockfd, message, strlen(message), 0)) < 0) 
         	{
        		cerr << "Send error." << endl;
        	}
	
      //      send(sockfd, buffer,strlen(buffer),0);
            /*	
        	// Wait to receive response.
        	if((msgSize = recv(sockfd, output, 1023, 0)) < 0) 
        	{
	        	cerr << "Receive error." << endl;
        	}
*/	
        
        //delete memory from buffer
        delete[] buffer;
    
    }else if (command == "GET:"){
		//string filename = input.substr(4);

        char *charInput = const_cast<char*>(input.c_str());

         if((msgSize = send(sockfd, charInput, strlen(charInput),0)) < 0){
             cerr << "Request Error" << endl;
         }
        
         if((msgSize = recv(sockfd, output, 1023, 0)) < 0){
             cerr << "Receive Error" <<endl;
         }else {
		cout << "File rceived" << endl;
	 }

       
	//write output to file

	char* pch;
    pch = strchr(output,':');
    int position = 0;
    position = pch-output+1;

	char filename[position];
        
        for(int i = 0; i< position-1;i++){
           //if(i<position){
            filename[i] = output[i];
           //}else 
           if(i == position-2){
                filename[i+1] = '\0';
           }           
        }
          //create file to put on server
                
         ofstream outputFile(filename);
          for(int i =0;i<strlen(output)-1;i++){
            if(i >= position ){
                outputFile << output[i];
            }

          }

	}else if(command == "QUIT"){
		//quit on anything else
		stopWorking = true;	
	}
	/*
                  break;
        case "PUT:":
                  string filename = input.substr(4);
                  // open and send file
                  break;
        case "QUIT":
                  stopWorking = true;
                  break;
        default:
                  break;
            
    }*/
        
   }
}
