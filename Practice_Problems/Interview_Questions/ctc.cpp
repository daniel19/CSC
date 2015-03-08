#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include "FileIO.h"

using namespace std;

void shredded(string filename, string delimeter){
    FileIO *reader = new FileIO(filename, delimeter);
    vector<string> tokenList = reader->getTokens();    
    cout << "Token array size: " <<  tokenList.size() << endl;
    for(int i=0; i < tokenList.size(); i++){
        cout << tokenList[i] << endl;
    }
}

void printFile(string filename){
    FileIO *reader = new FileIO(filename, FileIO::FOR_READING);
    while(!reader->endOfFile)
        cout << reader->readLine() << endl;
}

string convertToBinary(int number){
    string result;
    for(int bit=0; bit < sizeof(int)*3; ++bit){
        int bit_val = 1 & number;
        result = (bit_val ? "1":"0") + result;
        number = number >> 1;     
    }
    return result;
}

bool isUniqueChars(string str){
    int checker =0;
    //effectively an iteration
    transform(str.begin(), str.end(), str.begin(), ::tolower);//converts input string to lowercase
    for(int i=0; i < str.length(); i++){
        int val = str[i] - 'a';
        if((checker & (1 << val)) >0) 
            return false;
        checker |= (1 << val);
    }
    return true;
}

bool runDisplay(){
    cout << "What operation would you like to run." << endl;
    cout << "1)UniqueChars\n2)String ops\n3)FileIO" << endl;
    
    int choice = 0;
    cin >> choice;
    switch(choice){
        case 1:
        {    
            cout << "Please enter in your word."<< endl;
            string input ="";
            getline(cin.ignore(), input);
            if(isUniqueChars(input)){
                cout << "Input has unique characters." << endl;
            }else{
                cout << "Input has no unique characters." << endl;
            }
            break;
        }
        case 2:
        {
            bool running = true;
            while(running){
                cout << "Select which string operation you want to run" << endl;
            }
            break;
        }
        case 3:
        {
            cout << "Please enter filename/location: ";
            string filename;
            getline(cin.ignore(), filename);
            printFile(filename);
            shredded(filename, "|");
        }
    }
    
    cout << endl << "Do you want to continue?(y/n)" << endl;
    char response; 
    cin >> response;
    if(response == 'y' || response == 'Y'){
        return true;
    }
    return false;
}

int main(){
    //Generate display
    bool running = true;
    while(running){
        running = runDisplay();
    }
    return 0;
}
