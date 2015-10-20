#include "Client.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <stdio.h>

using namespace std;

// constructor
Client::Client() {
	id = 0;
	chequingAcc = 0.0;
	savingsAcc = 0.0;
	first = " ";
	last = " ";
	limit = 0.0;
	cred = 0.0;
    pin = 0000;
	frozen = false;
	full = false;
}

// setter methods
void Client::setChequing(double che){ chequingAcc = che; }
void Client::setSavings(double sav){ savingsAcc = sav; }
void Client::setId(int cid){ id = cid; }
void Client::setFirstName(string name){ first = name; }
void Client::setLastName(string name){ last = name; }
void Client::setCredLimit(double lim){ limit = lim; }
void Client::setCred(double cre){ cred = cre; }
void Client::setPin(int PIN){ pin = PIN; }
void Client::setFrozen(bool setit){ frozen=setit; }
void Client::setFull(bool set){ full = set; }
void Client::setInterest(double inter){ interest = inter; }

// getter methods
double Client::getSavings(){ return savingsAcc; }
double Client::getChequing(){ return chequingAcc; }
int Client::getId(){ return id; }
string Client::getFirstName(){ return first; }
string Client::getLastName(){ return last; }
double Client::getCredLimit(){ return limit; }
double Client::getCred(){ return cred; }
int  Client::getPin(){ return pin; }
bool Client::isFrozen(){ return frozen; }
int Client::getSizeOfPurchases(){ return purchases.size(); }
bool Client::getFull(){ return full; }
double Client::getInterest(){ return interest; }

// client purchases
void Client::purchase(double amount) {
    purchases.push_back(amount);
}

double Client::getPurchase(int i) {
    return purchases[i];
}

// function for making payments at end of month with interest calculated
double Client::payDay() {
	double sum = 0;
	for (int i = 0; i < purchases.size(); i++) {
		sum += purchases[i];
	}
	purchases.clear();
	if (sum > 0) {
		if (full == true) {
			sum += interest;
			return sum;
		}
		else {
			interest += (sum * 0.9);
			interest += (interest * 0.02);
			return sum * 0.10;
		}
	}
    else {
		return 0;
    }
}

// function to return the amount of money owed for a client
double Client::getAmountOwed() {
	double sum = 0;
	for (int i = 0; i < purchases.size(); i++) {
		sum += purchases[i];
	}
	return sum;
}

double Client::getAmountOwing(){
    return interest;
}
