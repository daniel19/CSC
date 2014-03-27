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
#include <sys/poll.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "chatPerson.h"

using namespace std;

//Protoypes
void parseMessage(char* buffer, int clisock);
void setupClient(char* buffer, int clisock);    

//Global Variables
vector<chatPerson> chatList;
vector<string> messageList;
#define MAX_CONNECTIONS 5



bool handleConnection(int clisock) 
{
	
	int msgSize;
	char buffer[1016]; // 
	memset(buffer, '\0', 1016); // Clear the buffer.

	if((msgSize = recv(clisock, buffer, 1015, 0)) < 0) 
	{
        if(errno != EWOULDBLOCK){
            perror(" main recv failed");
            return false;
        }
       
	}
     
   // if(!strcmp(buffer, "QUIT")){return false;}

    parseMessage(buffer, clisock); 
    return true;
	
	//close(clisock);
}


int main(int argc, char* argv[]) 
{
	
    struct pollfd ufds[MAX_CONNECTIONS];

    // Set up the socket.

    int sockfd =-1, newsockfd = -1,socketDescriptor =-1;
	unsigned int clilen;
    int on = 1;
   // int listen_sd = -1;
	
	// Structures for client and server addresses.
	struct sockaddr_in server_addr, cli_addr;
	
        // Create the server socket.
	    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	    {
		    cerr << "Socket error." << endl;
		    exit(1);
	    }
        fcntl(sockfd, F_SETFL, O_NONBLOCK); 
        /*if(socketDescriptor = setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,
                    (char*)&on,sizeof(on))<0)
        {
            perror("setsockopt failed");
            close(sockfd);
        }
    cout << "Here we are TOO MUCH" << endl;
        if(socketDescriptor = ioctl(sockfd, FIONBIO,(char*)on)<0){
           cout << "sockfd:" << sockfd << " sockDes:" << socketDescriptor << endl;
            perror("ioctl failed");
          //  close(sockfd);
          //  exit(1);
        }*/

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
    
    //Setup poll structure
    memset(ufds,0, sizeof(ufds));
    ufds[0].fd = sockfd;
    ufds[0].events = POLLIN;



    /*use poll here to manage multiple connections*/
	// Loop forever, handling connections.
    bool keepRunning = true;
    bool acceptClients = true;
   /*	 while(acceptClients) 
	{
				while(keepRunning){
         keepRunning = handleConnection(newsockfd);
        }
      }*/

    do{
        if(poll(ufds,chatList.size()+1,3*60)<0){
            perror("poll error");
            break;
        }
        for(int i =0; i < chatList.size()+1; i++){
            if(ufds[i].events == 0){
                continue;
            }
            if(ufds[i].events != POLLIN){
                cout << "Error in do while.--!=POLLIN" << endl;
               keepRunning = false;
               break;
            }
            if(ufds[i].fd == sockfd){
                //Accept to all incoming connections that are queued
                do{
                    clilen = sizeof(cli_addr);
		            newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	            	if(newsockfd < 0) 
		            {
			            if(errno != EWOULDBLOCK){
                            perror("accept() failed.");
			                keepRunning = false;
                        }
                        break; 
		            }           
                    
                    ufds[chatList.size() +1].fd = newsockfd;
                    ufds[chatList.size() +1].events = POLLIN;

                    if(newsockfd == -1){
                        acceptClients =false;
                    }
                }while(acceptClients);
            }else{
                //recieve incoming on current socket
                bool handling = true;
                while(handling){
                    handling = handleConnection(ufds[i].fd);
                }
           }

        }
    }while(keepRunning);
	
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
      //grab whats in buffer;
      char* pch2;
      pch2 = strchr(buffer,':');
      int pos = 0;
      pos = pch2 - buffer+1;

      char *recpName;
      for(int k=0; k<position; k++){
        recpName[k] = buffer[k];
        if(k == position-1){
            recpName[k+1] == '\0';
        }
      }
    cout << recpName << endl << endl;
  }else if (!strcmp(command,read)){
      //read command sent
  }else if (!strcmp(command,list)){    
     cout << "list command sent" << endl;
      //char outputList[1024];
      string outputList;
      for(int i =0; i < chatList.size(); i++){
         outputList.append(chatList[i].getName());
         outputList.append("\0");
         //cout << outputList << endl;
      }
      char* sendList = const_cast<char*>(outputList.c_str());

      if((send(clisock, sendList, strlen(sendList),0))<0){
          cerr << "Send Error"<<endl;
      }

  }else if (!strcmp(command, update)){
      //update command sent 
      // send the user the entire message list
      string currentMessages;
      for (int i = 0; i < messageList.size(); i++){
          currentMessages.append(messageList[i]);
          currentMessages.append("\0");
      }
      char* sendMessages = const_cast<char*>(currentMessages.c_str());

      if((send(clisock, sendMessages, strlen(sendMessages),0)) < 0){
          cerr << "Send Error-update" << endl;
      }


  }else if (!strcmp(command, sendChar)){
      //send command was sent
      //compare clisock to socket in chatPerson vector 
      string typingPerson; 
      for(int i=0; i < chatList.size(); i++){
          if(clisock == chatList[i].getSocket()){
            typingPerson = chatList[i].getName();
          }
      }
    char message[1024];
    for(int i = 5; i<strlen(buffer); i++){
        message[i-5] = buffer[i];
    }
    string myMessage(message);
    typingPerson.append(":");
    typingPerson.append(myMessage);
    
    cout << "--------Incoming Message--------" << endl;
    cout << typingPerson << endl << endl;


  }else{

      //clean up ufds struct and close socket

      //remove sender from chat   
        for(int i = 0; i< chatList.size(); i++){
            if(clisock == chatList[i].getSocket()){
                cout << "Client:" << chatList[i].getName() << " has disconnected." << endl;
                chatList.erase(chatList.begin() + i-1);
            }
        }

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
      
      //  cout << clisock << endl;
      if((msgSize = send(clisock,rep,strlen(rep),0))<0){
          cerr << "Send error" << endl;
      }else{
     //     cout << msgSize << endl;
          cout << "Client:" << client.getName() << " has connected."<<endl;
          cout << "Chat lobby count:" << chatList.size() << endl;
      }
      
}