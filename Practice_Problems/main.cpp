/**
 * Lockheed Martin - CDL Systems USA Technical Question
 * main.cpp
 * Purpose: Asks for user input to calcualte the volume of a right circular cylinder.
 * Commisionioned by: Chelle Fritz
 *
 * @author Daniel Brown
 * @version 1.0 4/24/2014
 *
 */


#include <iostream>
#include <string>
#include <stdlib.h>
#include "Cylinder.cpp"

using namespace std;


//Prototypes
bool validDouble(string s);

int main(){
    double userRadius =0;
    double userHeight =0;
    
    bool keepRunning = true;
    while (keepRunning) { 
    
        cout << "----------------------------------------------------------" << endl;
        cout << "| Calcualte the volume of a right circular cyclinder.    |" << endl;
        cout << "----------------------------------------------------------" << endl;
    
    
        bool validRadius = false;
        bool validHeight = false;
        
        do {
            cout << "Please enter in the cylinders radius: ";
            string userInput ="";
            getline(cin, userInput);
            
            if(validDouble(userInput)){
                validRadius = true;
                char *pend;
                userRadius = strtod(userInput.c_str(), &pend);
            }else{
                cerr << "Invalid input." << endl;
                cin.clear();
            }
        } while (!validRadius);
        
        do {
            cout << "Please enter in cylinders height: ";
            string userInput ="";
            getline(cin, userInput);
            
            if(validDouble(userInput)){
                validHeight = true;
                char *pend;
                userHeight = strtod(userInput.c_str(), &pend);
            }else{
                cerr << "Invalid input." << endl;
                cin.clear();
            }
        } while (!validHeight);
        
        
        
        //Setup cylinder
        Cylinder userCylinder = *new Cylinder(userHeight, userRadius);
        
        cout << "Cylinder height: " << userCylinder.getHeight() << " Cylinder radius: " << userCylinder.getRadius()  << endl;
        cout << "The volume of your cylinder is " << userCylinder.getVolume() << "." << endl;
        
        
        cout << "Create new Cylinder?(y|n): ";
        string userContinue;
        getline(cin,userContinue);
        
        if (userContinue == "n") {
            keepRunning = false;
        }
        cout << endl << endl;
        
    }
    return 0;
}


bool validDouble(string s){
    for (int i =0; i < s.size(); i++) {
        
        if((ispunct(s[i]) && s[i] != '.') || isblank(s[i])){
            cout << "interation: " << i <<  endl << endl;
            return false;
        }
           }
    
    return true; //a valid double is found
}