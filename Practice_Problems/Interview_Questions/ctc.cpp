#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

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
    for(int i=0; i < str.length(); i++){
        int val = str[i] - 'a';
        cout << "String: " << str[i] << endl;
        cout << "Value: " << val << endl;
        cout << "Bits: " << convertToBinary(val) << endl;
        if((checker & (1 << val)) >0) return false;
        checker |= (1 << val);
    }
    return true;
}

bool runDisplay(){
    cout << "What operation would you like to run." << endl;
    cout << "1)UniqueChars\n" << endl;
    
    int choice = 0;
    cin >> choice;
    switch(choice){
        case 1:
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

    cout << endl << "Do you want to continue?(y/n)" << endl;
    char response; 
    cin >> response;
    if(response == 'y'){
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
