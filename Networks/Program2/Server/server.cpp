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




int main(int argc, char* argv[]) 
{
    int success, on=1, serverSocket=-1, newSocket=1;
    int compress=0, closeConnection;
    int timeout, nfds=1, end=0, currentSize=0, i, j, port;
    char inputBuffer[1024], outputBuffer[1024];
    struct sockaddr_in addr;
    struct pollfd fds[200];

    if(argc<2){
        cerr << "Usuage: ./server [port]" << endl;
        exit(1);
    }

    port = atoi(argv[1]);
    if(port < 15000){
        cerr << "Port should be greater than 15000."<<endl;
        exit(1);
    }

    serverSocket = socket(AF_INET, SOCK_STREAM,0);

    if(serverSocket<0){
        cerr << "Error Creating the server socket connection." << endl;
        exit(1);
    }

    success = setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
    if(success < 0){
        cerr << "Error making socket reusable." << endl;
        exit(1);
    }

    success = ioctl(serverSocket, FIONBIO, (char *)&on);
    if (success < 0){
        cerr << "Error setting socket to non blocking." << endl;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    bind(serverSocket, (struct sockaddr *)&addr, sizeof(addr));

    success = listen(serverSocket, 32);
    if (success < 0){
        cerr << "Error listening on socket." << endl;
    }

    memset(fds, 0, sizeof(fds));

    fds[0].fd = serverSocket;
    fds[0].events = POLLIN;

    timeout = 1000;

    while(end == 0){
        memset(inputBuffer, '\0',sizeof(inputBuffer));
        memset(outputBuffer, '\0', sizeof(outputBuffer));

        success = poll(fds, nfds, timeout);

        if(success <0){
            cerr <<"Error polling sockets" << endl;
            break;
        }else if (success == 0){
            continue;
        }else{
            currentSize = nfds;
            for(i = 0; i < currentSize; i++){
                if(fds[i].revents ==0)
                    continue;
                if(fds[i].revents != POLLIN){
                    cerr << "Error on client socket: " << fds[i].revents;
                    end = 1;
                    break;
                }else if(fds[i].fd == serverSocket){
                    while(1){
                        newSocket = accept(serverSocket, NULL, NULL);
                        if(newSocket <0){
                            if(errno != EWOULDBLOCK){
                                cerr << "Error in accepting connection" <<endl;
                                end = 1;
                            }
                            break;

                        }
                
                        fds[nfds].fd = newSocket;
                        fds[nfds].events = POLLIN;
                        nfds++;
                    }
                }else{
                    closeConnection = 0;

                    while(true){
                        success = recv(fds[i].fd, inputBuffer, sizeof(inputBuffer),0);
                        if(success < 0){
                            if(errno != EWOULDBLOCK){
                                cerr << "Receive failed." << endl;
                                closeConnection = 1;
                            }
                            break;
                        }else{
                            //send data to parese function
                            parseMessage(inputBuffer, fds[i].fd);
                        }
                
                    }

                    if(closeConnection){
                        close(fds[i].fd);
                        fds[i].fd = -1;
                        compress = 1;

                }

             }  
    
        }
        if(compress){
            compress = 0;
            for(i=0; i <nfds; i++){
                if(fds[i].fd == -1){
                    for(j=i; j<nfds; j++){
                        fds[j].fd = fds[j+1].fd;
                    }
                    nfds--;
                }
            }

        }

        for(i=0; i<nfds; i++){
            if(fds[i].fd >=0){
                close(fds[i].fd);
            }
        }
       }
    }
    return 0;
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
