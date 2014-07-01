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


//Main function
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
        
        do {//Asks for user's cylinder radius
            cout << "Please enter in the cylinders radius: ";
            string userInput ="";
            getline(cin, userInput);
            
            if(validDouble(userInput)){//error check the user's input radius
                validRadius = true;
                char *pend;
                userRadius = strtod(userInput.c_str(), &pend);
            }else{//Incorrect value found try again
                cerr << "Invalid input." << endl;
                cin.clear();
            }
        } while (!validRadius);
        
        do {//Ask for user's cyclinder height
            cout << "Please enter in cylinders height: ";
            string userInput ="";
            getline(cin, userInput);
            
            if(validDouble(userInput)){//error check the user's input height
                validHeight = true;
                char *pend;
                userHeight = strtod(userInput.c_str(), &pend);
            }else{//Incorrect value found try again
                cerr << "Invalid input." << endl;
                cin.clear();
            }
        } while (!validHeight);
        
        
        
        //Setup cylinder
        Cylinder userCylinder = *new Cylinder(userHeight, userRadius);
        
        cout << "Cylinder height: " << userCylinder.getHeight() << " Cylinder radius: " << userCylinder.getRadius()  << endl;
        cout << "The volume of your cylinder is " << userCylinder.calculateVolume() << "." << endl;
        
        cout << "TESTING OUTPUT: " << userCylinder.getRadius() <<  endl;        
        
        cout << "Create new Cylinder?(y|n): ";
        string userContinue;
        getline(cin,userContinue);
        
        if (userContinue == "n") {//Quit program here if true
            keepRunning = false;
        }//Start over if userContinue is not 'n'
        cout << endl << endl;
        
    }
    return 0;
}


/***
 * Function validDouble checks the users's input for valid nurmerical characters to store
 *  as a floating point number of type double.
 *  
 *  @param s - user's string input
 *  @return bool - result is a boolean variable if input is valid return true; else return false
 */

bool validDouble(string s){
    for (int i =0; i < s.size(); i++) {//check every character in user's input
        
        if((ispunct(s[i]) && s[i] != '.') || isblank(s[i]) || isalpha(s[i])){
            return false;//a incorrect character is found
        }
    }
    
    return true; //a valid double is found
}
