#include <iostream>
#include <string.h>
#include <cstring>
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
{
    int clientSocket, port;
    struct sockaddr_in server_address;
    struct hostent *hent;

    if(argc< 3){
        cerr << "Usage: ./client [server name] [port]" << endl;
        exit(1);

    }

    port = atoi(argv[2]);//Convert character argument to integer
    if(port < 15000){
        cerr << "Port # must be greater/equal to 15000" << endl;
    }

    if((hent = gethostbyname(argv[1])) == NULL){
        cerr << "Invalid hostname" << endl;
    }
    
    if((clientSocket = socket(AF_INET, SOCK_STREAM,0)) < 0){
            cerr << "Socket creation error" << endl;
    }

    memset((void*) &server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr = *((struct in_addr *)hent->h_addr);
    server_address.sin_port = htons(port);

    if((connect(clientSocket, (struct sockaddr*) &server_address, sizeof(server_address)) <0)){
        cerr << "Error connecting to server" << endl;
        exit(1);
        }
    char message[1024];
    interface(message, clientSocket);

    
}


 

//Funtion that handles all the user controls after socket
//has conncted.
void interface(char message[1024], int sockfd){
   bool stopWorking = false;
   char output[1024]; // Output message from server.
   memset(message,'\0',sizeof(message));
   memset(output, '\0', sizeof(output));
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

     //open readme file in current directory
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
       
           cout << "List of present chatters:" <<endl;
      
            if((recv(sockfd, output, 1024, 0)<0)){
                cerr << "Error Connecting" << endl;
            }else{
                cout <<  output << endl;
            }       

           
           
       }else if(command == "whis:"){
            //Whisper to one client.
            string receiverName;
            cout << "Enter in the single client name:";
            getline(cin,receiverName);

            string message;
            cout << endl << "Enter in the message:";
            getline(cin, message);

            char* sendCommand = const_cast<char*>(command.c_str());
            receiverName.insert(receiverName.length(),":");
            strcpy(sendCommand,receiverName.c_str());
            strcpy(sendCommand, message.c_str());

            send(sockfd, sendCommand, strlen(sendCommand),0);
            recv(sockfd, output, 1024,0);

            cout << output << endl;
            memset(output,'\0',sizeof(output));

       }else if(command == "send:"){
          cout << endl<< "Enter in desired Message:"; 
          string message; 
          getline(cin, message);
          
           command.append(message);
           //send to main chat list
          char* sendCommand = const_cast<char*>(command.c_str());
          //strcpy(sendCommand, message.c_str());
           cout << "Sending stringCommand: " << sendCommand << endl;
          send(sockfd, sendCommand, strlen(sendCommand),0);
          recv(sockfd, output, 1024, 0);
          cout << endl << output << endl;

          memset(output,'\0', sizeof(output));
       }else if(command == "upda:"){
            //request update of current chat
            char* sendCommand = const_cast<char*>(command.c_str());
            send(sockfd, sendCommand, strlen(sendCommand),0);
            recv(sockfd, output, 1024,0);
            cout << output << endl;

            memset(output,'\0',sizeof(output));
       }else if(command == "QUIT"){
		//quit on anything else
		stopWorking = true;
        char* sendCommand = const_cast<char*>(command.c_str());

        //send quit to server
        send(sockfd, sendCommand, strlen(sendCommand), 0);

        //send user to quit session
       // send(sockfd, sendName, strlen(sendNam),0);
        recv(sockfd, output, 1024, 0);
        cout << output << endl;
        
	}else{
        cerr << "Command Not Found" << endl << endl;
   }
   } 
   
}
