/*
 *  ClassFruit.cpp
 *  
 *
 *  Created by Daniel Brown on 6/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
using namespace std;

class fruit {

public: // access specifier
	float price, weight; //attributes
	float cost(); //action
};

float fruit::cost(){
	return (price * weight);
}

int main()
{
	fruit apple, orange; //object declaration
	cout << "Enter an apple price per pound. " <<flush;
	cin >> apple.price;
	cout << "Enter in the weight. "flush;
	cin >> apple.weight;
	
	cout << "Enter in the price of the oranges. "<< flush;
	cin >> orange.price;
		cout << "Enter in the weight. "<<flush;
	cin >> orange.weight;
	
	cout << "The cost of apples is $" << apple.cost()<<endl;
	cout << "The cost of oranges is $" << orange.cost();
}