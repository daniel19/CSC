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
#include <sstream>
#include "chatPerson.h"

using namespace std;

//Protoypes
bool parseMessage(char* buffer, int clisock);
void setupClient(char* buffer, int clisock);    

//Global Variables
vector<chatPerson> chatList;
vector<string> messageList;




int main(int argc, char* argv[]) 
{
    int success, on=1, serverSoc=-1, newSoc=-1;
	int compressArray=0, closeConnection;
	int timeout, nfds=1, end = 0, currentSize=0, i, j, port;
	char receiveBuff[10000], sendBuff[10000];
	struct sockaddr_in addr;
	struct pollfd fds[200];
	//initilize the variables
	
	//check that the proper number of args were supplied
	if(argc < 2){
		cerr << "Usage: ./server [port]" << endl;
		exit(1);
		//error check the main, and if there is an error. close the server
	}
	
	//get the port number
	port = atoi(argv[1]);
	
	//error check the port number
	if(port < 15000){
		cerr << "Port must be greater than or equal to 15000!" << endl;
		exit(1);
	}
	
	//create socket to receive connections
	serverSoc = socket(AF_INET, SOCK_STREAM, 0);
	//get the socket ready
	if(serverSoc < 0){
		//error check the socket 
		cout << "Error creating server socket." << endl;
		exit(1);
		//close if there is an error with it
	}
	
	//make socket reusable
	success = setsockopt(serverSoc, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
	if(success < 0){
		cout << "Error making socket resuable." << endl;
		exit(1);
	}
	
	//set socket to be non-blocking
	success = ioctl(serverSoc, FIONBIO, (char *)&on);
	if(success < 0){
		cout << "Error setting socket to non-blocking." << endl;
		exit(1);
	}
	
	//bind the server socket
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	bind(serverSoc, (struct sockaddr *)&addr, sizeof(addr));
	//standard bind like the first program
	
	//listen on the non-blocking server socket
	success = listen(serverSoc, 32);
	if(success < 0){
		cout << "Error listening on the socket." << endl;
		exit(1);
	}
	
	//init pollfd struct
	memset(fds, 0, sizeof(fds));
	
	//setup initial listening soc
	fds[0].fd = serverSoc;
	fds[0].events=POLLIN;
	
	//set the timeout
	timeout = 1000;
	
	while(end == 0){
		//reset the buffers
		memset(sendBuff, '\0', 10000);
		memset(receiveBuff, '\0', 10000);
		
		success = poll(fds, nfds, timeout);
		
		if(success < 0){
			//error in poll
			cerr << "Error polling the sockets, program closing" << endl;
			break;
		}
		else if(success == 0){
			//poll timed out
			continue;
		}
		else{
			currentSize = nfds;
			for(i=0; i<currentSize; i++){

				if(fds[i].revents == 0){
					//timed out
					continue;
				}
				
				if(fds[i].revents != POLLIN){
					//error has occcured on the socket
					//socket needs to be closed
					cerr << "Error on client socket, revents = " << fds[i].revents;
					cerr << "Server closing" << endl;
					end = 1;
					break;
				}
				else if(fds[i].fd == serverSoc){
					//the listening socket is the server socket so it is clients trying
					//to make a connection to the server
					while(true){
						newSoc = accept(serverSoc, NULL, NULL);
						if(newSoc < 0){
							if(errno != EWOULDBLOCK){
								cerr << "Error in accept(), server closing" << endl;
								end = 1;
							}
							break;
						}
						//set the fd and events 
						fds[nfds].fd = newSoc;
						fds[nfds].events = POLLIN;
						nfds++;
					}
				}
				else{
					//the listening socket is not the server socket so it is one of the
					//connected sockets trying to send chat data and commands to the server
					closeConnection = 0;
					
					while(true){
						//iterate over all the connected sockets to get
						//data
						success = recv(fds[i].fd, receiveBuff, sizeof(receiveBuff), 0);
						
						//check for receive success
						if(success < 0){
							if(errno != EWOULDBLOCK){
								cerr << "Receive from client failed." << endl;
								cerr << "Closing client socket." << endl;
								closeConnection = 1;
							}
							break;
						}
						//check for closing of socket
						else if(success == 0){
							cerr << "Connection was closed by the client." << endl;
							closeConnection = 1;
							break;
						}
						else{
							//parseMessage
                            bool result;
                            result = parseMessage(receiveBuff, fds[i].fd);
                            
                            if (result)
                                //do nothing
                                closeConnection = 0;
                            else
                                closeConnection = 1; //quit was sent
                            
						}//end else
					}//end while
                    //close the connection
					if(closeConnection){
						close(fds[i].fd);
						fds[i].fd = -1;
						compressArray = 1;
					}
				}//end else
			}//end for
			
			//compress the array of file descriptors
			if(compressArray){
				compressArray = 0;
				for(i=0; i<nfds; i++){
					if(fds[i].fd == -1){
						for(j=i; j<nfds; j++){
							fds[j].fd=fds[j+1].fd;
						}
						nfds--;
					}
				}
			}
		}//end else
	}//end poll() while loop
	
	//make sure to close any open sockets on server closing
	for(i=0; i<nfds; i++){
		if(fds[i].fd >= 0){
			close(fds[i].fd);
		}
	}
	
	return 0;
}
bool parseMessage(char* buffer, int clisock)
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
    for(int j=0;j< 5;j++){
        command[j] = buffer[j];
	    if(j == 4){
		    command[j+1] = '\0';
	    }
    }
    
    cout << "Command Received: " << command << endl;
	
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

      char *recpName = nullptr;
      for(int k=0; k<position; k++){
        recpName[k] = buffer[k];
        if(k == position-1){
            recpName[k+1] = '\0';
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
          stringstream ss;
          ss << i+1;
          
          outputList.append(ss.str());
          outputList.append(":");
         outputList.append(chatList[i].getName());
         outputList.append("\n");
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

      
      cout << "Sending updated list: " << sendMessages << endl;
      
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
      
      
      messageList.push_back(typingPerson);
    
    cout << "--------Incoming Message--------" << endl;
    cout << typingPerson << endl << endl;
    
      char out[20] = "Message Received";
      send(clisock, out, strlen(out),0 );

  }else{

      //clean up ufds struct and close socket

      //remove sender from chat   
        for(int i = 0; i< chatList.size(); i++){
            if(clisock == chatList[i].getSocket()){
                cout << "Client:" << chatList[i].getName() << " has disconnected." << endl;
                chatList.erase(chatList.begin() + i-1);
                return false;
            }
        }

  }
    return true;

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
