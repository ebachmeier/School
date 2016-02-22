#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <stdio.h>

using namespace std;

class Client {

public:
    // constructor
	Client();
    // deconstructor
	~Client(){}
    
	// setter methods
	void setChequing(double che);
    void setSavings(double sav);
    void setId(int cid);
    void setFirstName(string name);
    void setLastName(string name);
    void setCredLimit(double lim);
    void setCred(double cre);
    void setPin(int PIN);
    void setFrozen(bool setit);
    void setFull(bool set);
    void setInterest(double inter);
    
	// getter methods
	double getSavings();
	double getChequing();
	int getId();
	string getFirstName();
	string getLastName();
	double getCredLimit();
    double getCred();
	bool isFrozen();
	int getPin();
	int getSizeOfPurchases();
	void purchase(double amount);
	double getPurchase(int i);
	double getAmountOwing();
	double payDay();
	bool getFull();
	double getInterest();
	double getAmountOwed();
    
private:
	int id, pin;
	double chequingAcc, savingsAcc, cred, limit, interest;
	string first, last;
	bool frozen, full;
	vector<double> purchases;
};
