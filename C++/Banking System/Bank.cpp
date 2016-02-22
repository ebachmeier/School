/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 1
 * CS3307 Object-Oriented Design and Analysis
 * Western University
 * Nazim H. Madhavji
 * September 25, 2015
 *
 * This program is a Banking System for an unspecified number of clients that stores their bank
 * accounts. The program allows them to deposit, withdraw, transfer, and even make transactions.
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <stdio.h>
#include <time.h> 
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>
#include "Client.h"
#include "Maintenance.h"
#include "Manager.h"
#define ON true
#define OFF false

using namespace std;

/////////////////////// function prototypes ///////////////////////////
// functions for client menu system
void clientMenu(Client& c, vector<Client>& cList);
void printClientMenu(Client c, bool che, bool sav);
void purchaseMenu(Client& c);
void savePurchases(vector<Client>&cList);
void viewPurchases(Client c);
void saveTransaction(Client c, double price);
void deposit(Client& c);
void withdraw(Client& c);
void withdrawChequing(Client& c);
void withdrawSavings(Client c);
void transfer(Client& c);
void transferChequing(Client& c);
void transferSavings(Client& c);
void chequing(Client& c, bool che, bool sav);
void savings(Client& c, bool sav, bool che);
void updateMonth(vector<Client>&cList);
void payFullAmount(Client& c);
void writeFailedTransaction(Client& c);


// functions for manager menu system
void managerMenu(vector<Client>&cList);
bool openAccount(vector<Client>&cList, int accID, int p, string firstName, string lastName);
bool deleteAccount(vector<Client>&cList, int accID);
void printManagerMenu(void);

// functions for maintenance menu system
void maintenanceMenu(void);
void toggleExecutionTrace(void);
void writeTrace(string str);
void displayTrace(void);
void clearTraceLog(void);
void saveBankData(Manager m, Maintenance s);

// other methods to aid the benking system and menus
int getNumber();
double getDouble();
void saveClients(vector<Client>&cList);
int getAccountIndex(vector<Client>&cList, int targetAccNum, int low, int high);
bool compareAccountLastName(Client a, Client b);
bool compareAccountNums(Client a, Client b);
bool isDB(vector<Client>&cList, int t);
void sortNumber(vector<Client>&cList);
vector<Client> sortName(vector<Client>cList);
bool fee(Client c, double amount);
const string currentDateTime();

///////////////// variable declarations //////////////////////////
// variable to toggle the execution trace on and off
bool trace;
// string where the trace gets logged and written to throughout execution of the program
stringstream e;
// the end of the coming credit month for all users
int endOfMonth;

/*
 * main method
 * Author: Eric Bachmeier
 * Created: September 25, 2015
 * Purpose: This method initializes the Banking System text interface as well as the program tracing through its execution
 * Input Parameters: None
 * Output: The menu for the Banking System
 */
int main()
{
    // 2 digit precision for trace
    cout.precision(2);
    // random number sequence initiation, do not call again in main()
    srand(time(NULL));
    
    // initializing the execution trace
    // the trace is set to on from the prevous program run if the first line is 1, otherwise the trace has been set to off
    ifstream traceLog("executionTrace.txt");
    if (traceLog.is_open()) {
        // read in the previous trace switch ON(1) or OFF(0)
        string traceVal;
        getline(traceLog, traceVal);
        // set tracing to ON if the value read in is 1
        if (traceVal.compare("1") == 0) {
            trace = ON;
        }
        // set tracing to OFF if the value read in is 0
        else if (traceVal.compare("0") == 0) {
            trace = OFF;
        }
        // error message if no previous trace value has been read in
        else {
            trace = OFF;
            cout << "Error: Execution traces are off because no previous preference has been found.\n";
        }
    }
    else {
        trace = OFF;
        cout << "Error: Could not open the existing execution traces. Please try again.\n";
    }
    
    // initialize everything else
    // this will be am array of existing bank clients
    vector<Client> cList;
    // these will be used for the client and manager id numbers as well as the clients custom pin#
    int id, getId, pin;
    // declare and initialize counter i for stepping through the clients
    int i = 0;
    // these variables will be used to store the chequings and savings sum, credit limit, credit amount, the account limit, and money owed
    double chequings, savings;
    double credLimit, cred, limit, owed;
    // these string variables are for the line being read in, the clients full name, the status of the account, the position of the id number, and the amount choice being paid (full or not)
    string line, first, last, freeze, pos, full;
    // this will point to the current client being read in
    Client *temp;
    // this will be the link stream to the clients database file
    ifstream DB("clientDB.txt");
    
    // read clients information in line by line to the array existing called cList
    if (DB.is_open()){
        while (getline(DB, line)) {
            // read line by line until all clients have been read in
            stringstream ss(line);
            // split the string into appropriate variables
            ss >> id >> chequings >> savings >> first >> last >> pin >> freeze >> limit >> full >> owed;
            // create a new client object
            temp = new Client;
            // give the temp client some attributes from the text file
            temp->setId(id);
            temp->setFirstName(first);
            temp->setLastName(last);
            temp->setChequing(chequings);
            temp->setSavings(savings);
            temp->setPin(pin);
            temp->setCredLimit(limit);
            // if the account is frozen, set that attrubite
            if (freeze == "frozen")
                temp->setFrozen(true);
            // otherwise, set this boolean to false
            else
                temp->setFrozen(false);
            // if the user pays in full amount, set that attribute to true
            if (full == "full")
                temp->setFull(true);
            // otherwise have this attribute read into false boolean
            else
                temp->setFull(false);
            temp->setInterest(owed);
            // adds new element back to the end of cList
            cList.push_back(*temp);
            // increment i to the next client
            i++;
        }
        // close the file stream
        DB.close();
    }
    else {
        cout << "Error: The client database could not be located.\n";
    }
    
    // set counter i to 0 for loading in client purchases for each existing customer
    i = 0;
    // initialize x variable for each item purchased by clients
    double x;
    ifstream trans("clientTransaction.txt");
    // read client purchases in line by line to the array existing called cList
    if (trans.is_open()) {
        while (getline(trans, line)) {
            // read line by line until all client purchases have been read in
            istringstream ss(line);
            ss >> first;
            do {
                double x = 0;
                ss >> x;
                // add the purchase to the client object if it is not a null value of 0
                if (x != 0)
                    cList[i].purchase(x);
            } while (ss);
            // increment the counter for clients
            i++;
        }
        // close the transaction file stream
        trans.close();
    }
    else {
        cout << "Error: The client purchases file was not found.\n";
    }
    
    // initialize object for the maintenance person
    Maintenance s;
    // initialize object for the system manager
    Manager m;
    // create a file stream for the bank data
    ifstream bankData("bankData.txt");
    
    // read the bank data in from the text file
    if (bankData.is_open()) {
        // read the id of the system maintenance person
        getline(bankData, line);
        stringstream ss(line);
        ss >> pos >> id;
        s.setID(id);
        
        // read the id of the system manager
        getline(bankData, line);
        stringstream stream2(line);
        stream2 >> pos >> id;
        m.setID(id);
        
        // read the day of the month from the file
        getline(bankData, line);
        stringstream stream3(line);
        stream3 >> pos >> id;
        endOfMonth = id;
        
        // close the file stream
        bankData.close();
    }
    else {
        cout << "Error: The data file for manager codes was not found.\n";
    }
    
    // if there are no days left in the momth paying period, all clients must pay
    if (endOfMonth == 0) {
        // write the end of month to execution trace
        e << currentDateTime() << "End of the monthly pay period\n";
        writeTrace(e.str());
        e.str("");
        // update the month to the list of clients
        updateMonth(cList);
        // reset for the next month with 30 days
        endOfMonth = 30;
        // save the updated clients with their purchases to text file
        saveClients(cList);
        savePurchases(cList);
    }
    e << currentDateTime() << endOfMonth << " days left in month to pay\n";
    writeTrace(e.str());
    e.str("");
    // subtract a day from the month counter per program run
    endOfMonth--;
    // save the updated bank data
    saveBankData(m, s);
    
    // header line to the bank program run
    cout << endl << "Welcome to my Banking System\n\n" << "By: Eric Bachmeier\n\n" << "0 - MAINTENANCE PERSON\n1 - MANAGER\n";
    
    while (true) {
        // initialize and declare boolan variable for location of a client
        bool loc = false;
        // loop until a user is located
        while (!loc) {
            cout << endl << "Enter a valid login ID (9 to quit): ";
            // get the integer ID from the user
            getId = getNumber();
            // program quit
            if (getId == 9) {
                cout << endl << "Thank you for your business. See you soon!\n\n";
                e << currentDateTime() << "User safely quit program session\n";
                writeTrace(e.str());
                e.str("");
                exit(0);
            }
            // manager menu
            else if (getId == m.getID()) {
                managerMenu(cList);
                loc = true;
            }
            // systems maintenance menu
            else if (getId == s.getID()) {
                maintenanceMenu();
                loc = true;
            }
            // client menu with their ID account
            else if (isDB(cList, getId)) {
                int user = getAccountIndex(cList, getId, 0, cList.size() - 1);
                clientMenu(cList[user], cList);
                loc = true;
            }
            if (!loc) cout << endl << "Sorry, that login ID does not exist yet.\n";
        }
    }
    // return 0 for end of main
    return 0;
}

///////////// methods /////////////////////////////////////////////////

// function for getting the current time stamp in a formatted string
const string currentDateTime() {
    time_t n = time(0);
    struct tm t;
    char o[80];
    t = *localtime(&n);
    strftime(o, sizeof(o), "%m/%d/%Y %X --- ", &t);
    return o;
}

// brings user to the client menu of options
void clientMenu(Client& c, vector<Client>& cList) {
	e << currentDateTime() << "Logged in as " << c.getId() << "\n";
    writeTrace(e.str());
    e.str("");
	cout << endl << "Welcome, " << c.getFirstName() << "!\n";
    // initialize boolean variables for chequings, savings, and log status
	bool che, sav, logout = false;
    // loop while the user is logged in
	while (!logout){
        // check if a chequing account exists
		if (c.getChequing() == 0) {
            che = false;
        }
		else {
            che = true;
        }
        // check if a savings account exists
		if (c.getSavings() == 0) {
            sav = false;
        }
		else {
            sav = true;
        }
        
        // print the client menu system to the user screen
		printClientMenu(c, che, sav);

        // get the user input number choice
		switch (getNumber()) {
        // case for cheqing
		case 1:
			e << currentDateTime() << c.getId() << " selected chequing\n";
            writeTrace(e.str());
            e.str("");
			chequing(c, che, sav);
			saveClients(cList);
			break;
        // case for savings
		case 2:
			e << currentDateTime() << c.getId() << " selected savings\n";
            writeTrace(e.str());
            e.str("");
			savings(c, sav, che);
			saveClients(cList);
			break;
        // case for money deposit
		case 3:
			e << currentDateTime() << c.getId() << " selected deposit\n";
            writeTrace(e.str());
            e.str("");
			deposit(c);
			saveClients(cList);
			break;
        // case for money withdrawal
		case 4:
			e << currentDateTime() << c.getId() << " selected withdrawal\n";
            writeTrace(e.str());
            e.str("");
			withdraw(c);
			saveClients(cList);
			break;
        // case for account balance
		case 5:
			e << currentDateTime() << c.getId() << " selected account balances\n";
            writeTrace(e.str());
            e.str("");
            // show chequing balance if the account exists
            cout << "------------------------------------------";
			if (che) {
				cout << endl << "Chequing Balance is $" << fixed << c.getChequing() << "\n";
			}
            // show saving balance if the account exists
            if (sav) {
				cout << endl << "Savings Balance is $" << fixed << c.getSavings() << "\n";
			}
            // show message if there are no open accounts
			if (!che && !sav) {
				cout << endl << "There are no open accounts to show.\n";
			}
            cout << "------------------------------------------\n";
			break;
        // case for money trasnfer
		case 6:
			e << currentDateTime() << c.getId() << " selected transfer\n";
            writeTrace(e.str());
            e.str("");
			transfer(c);
			saveClients(cList);
			break;
        // case for an item purchase
		case 7:
			e << currentDateTime() << c.getId() << " selected item purchase\n";
            writeTrace(e.str());
            e.str("");
			if (c.isFrozen()){
				e << currentDateTime() << c.getId() << " alerted account frozen\n";
                writeTrace(e.str());
                e.str("");
				cout << endl << "Option not available while account is frozen.\n";
			}
			else {
				purchaseMenu(c);
				savePurchases(cList);
				saveClients(cList);
			}
			saveClients(cList);
			break;
        // case for viewing transaction
		case 8:
			e << currentDateTime() << c.getId() << " selected view transactions\n";
            writeTrace(e.str());
            e.str("");
			viewPurchases(c);
			break;
        // case for the full payment option
		case 9:
			e << currentDateTime() << c.getId() << " selected full payment option\n";
            writeTrace(e.str());
            e.str("");
			payFullAmount(c);
			saveClients(cList);
			break;
        // case for client logout
		case 10:
			e << currentDateTime() << c.getId() << " selected to logout\n";
            writeTrace(e.str());
            e.str("");
			logout = true;
			break;
		default:
			e << currentDateTime() << c.getId() << " entered an invalid option\n";
            writeTrace(e.str());
            e.str("");
			cout << "That is not a valid option, please try again.\n";
		}
	}
}

// function for putting through a customer transaction of an item
void purchaseMenu(Client& c){
    // declare and initialize a random price for said item
	double price = rand() % 10000 + 1;
	price /= 100.00;
    // boolean to see if the transaction is successful and complete
	bool d = false;
	bool f = false;
    // loop until transaction is complete
	while (!d) {
		cout << endl << "Purchase will be $" << fixed << price << ", OK?\n";
		cout << "0 - No" << endl;
		cout << "1 - Yes\n" << endl;
        // get the user response
		switch (getNumber()) {
        // case for cancel
		case 0:
			e << currentDateTime() << c.getId() << " cancelled a purchase\n";
            writeTrace(e.str());
            e.str("");
			d = true;
			break;
        // case for a confirmed purchase
		case 1:
			e << currentDateTime() << c.getId() << " accepted a purchase\n";
            writeTrace(e.str());
            e.str("");
			cout << "Enter PIN:       (1 to cancel)\n";
			// while the pin transaction is not finished, loop
			while (!f){
                // get the user input for the PIN
				int t = getNumber();
                // if user just entered 1, cancel the transaction
				if (t == 1) {
					e << currentDateTime() << c.getId() << " cancelled the pin transaction\n";
                    writeTrace(e.str());
                    e.str("");
					f = true;
				}
				else if (t == c.getPin()) {
					e << currentDateTime() << c.getId() << " entered correct PIN\n";
                    writeTrace(e.str());
                    e.str("");
                    e << currentDateTime() << c.getId() << " confirmed a purchase of $" << price << "\n";
                    writeTrace(e.str());
                    e.str("");
                    cout << endl << "Purchase complete!\n";
                    c.purchase(price);
                    saveTransaction(c, price);
                    f = true;
				}
				else {
					e << currentDateTime() << " entered incorrect PIN\n";
                    writeTrace(e.str());
                    e.str("");
					cout << "Incorrect PIN, please try again.\n";
				}
			}
			d = true;
			break;
		default:
                e << currentDateTime() << c.getId() << " entered an invalid option\n";
                writeTrace(e.str());
                e.str("");
                cout << "That is not a valid option, please try again.\n";
		}
	}
}

// function to write failed transactions to text file
void writeFailedTransaction(Client& c){
	e << currentDateTime() << "Failed payment was tracked in the saved log\n";
    writeTrace(e.str());
    e.str("");
    // create an output stream for the failed transactions
	ofstream ff;
	ff.open("failedTransaction.txt", ios_base::app);
	ff << c.getId() << " " << fixed << c.getAmountOwing()/10 << endl;
}

// function to open and deal with the clients chequing account
void chequing(Client& c, bool che, bool sav) {
    // initialize and declare a boolean for being done with the chequing account
	bool d = false;
	double chequing = c.getChequing();
    // loop until the client has been through all the options for this account
	while (!d){
		d = true;
        // open a chequing account if one does not exist
		if (che == false) {
            e << currentDateTime() << c.getId() << " is opening a chequing account\n";
            writeTrace(e.str());
            e.str("");
			cout << endl << "A chequing account has been opened in your name.";
			cout << " " << "How much money would you like to deposit?\n";
			double x = getDouble();
			c.setChequing(x);
			e << currentDateTime() << c.getId() << " opened a chequing account with $" << x << "\n";
            writeTrace(e.str());
            e.str("");
			cout << endl << "$" << fixed << x << " was successfully deposited to your chequing.\n";
		}
		else {
			e << currentDateTime() << c.getId() << " is closing their chequing account\n";
            writeTrace(e.str());
            e.str("");
			cout << endl << "Your chequing account has been closed.\n";
            // option to transfer remaining money to savings, if it exists
			if (sav) {
				cout << endl << "Would you like to transfer the remaining balance to your savings account?\n";
				cout << "1 - Yes\n";
				cout << "2 - No\n\n";
                // get the user choice from cin
				switch (getNumber()){
                // if yes, trasnfer the money
				case 1:
					e << currentDateTime() << c.getId() << " selected to transfer to savings\n";
                    writeTrace(e.str());
                    e.str("");
					c.setSavings(chequing + c.getSavings());
					cout << endl << "$" << fixed << chequing << " was successfully transferred to your savings.\n";
					break;
                // if no, user chose to cancel the transfer
				case 2:
					e << currentDateTime() << c.getId() << " selected to not transfer to savings\n";
                    writeTrace(e.str());
                    e.str("");
					break;
				default:
					e << currentDateTime() << c.getId() << " entered an invalid option\n";
                    writeTrace(e.str());
                    e.str("");
					cout << endl << "That is not a valid option, please try again.\n";
					d = false;
				}
			}
			cout << "\n";
            // clear the chequing account out after the transfer
			c.setChequing(0);
			e << currentDateTime() << c.getId() << " had their chequing account set to $0\n";
            writeTrace(e.str());
            e.str("");
		}
	}
}

// function to open and deal with the clients savings account
void savings(Client& c, bool sav, bool che) {
    // initialize and declare a boolean for being done with the savings account
	bool d = false;
	double saving = c.getSavings();
    // loop until a final decision has been made by the user
	while (!d) {
		d = true;
        // if the client does not have an open savings account
		if (sav == false) {
			e << currentDateTime() << c.getId() << " is opening a savings account\n";
            writeTrace(e.str());
            e.str("");
			cout << endl << "A savings account has been opened in your name.";
			cout << " How much money would you like to deposit?\n";
			double x = getDouble();
			c.setSavings(x);
            e << currentDateTime() << c.getId() << " opened a savings account with $" << x << "\n";
            writeTrace(e.str());
            e.str("");
            cout << endl << "$" << fixed << x << " was successfully deposited to your savings.\n";
		}
        // if a savings account already exists and is open
		else {
			e << currentDateTime() << c.getId() << " is closing their savings account\n";
            writeTrace(e.str());
            e.str("");
			cout << endl << "Your savings account has been closed.\n";
            // option to transfer money into chequing, if it exists
			if (che) {
				cout << endl << "Would you like to transfer the remaining balance to your chequing account?\n";
				cout << "1 - Yes\n";
				cout << "2 - No\n\n";
                // get the user choice from cin
				switch (getNumber()){
                // case where the user wishes to make the transfer
				case 1:
					e << currentDateTime() << c.getId() << " selected to transfer to chequing\n";
                    writeTrace(e.str());
                    e.str("");
					c.setChequing(saving + c.getChequing());
					cout << endl << "$" << fixed << saving << " was successfully transferred to your chequing.\n";
					break;
                // case where user chose not to transfer
				case 2:
					e << currentDateTime() << c.getId() << " selected to not transfer to chequing\n";
                    writeTrace(e.str());
                    e.str("");
					break;
				default:
                    e << currentDateTime() << c.getId() << " entered an invalid option\n";
                    writeTrace(e.str());
                    e.str("");
                    cout << endl << "That is not a valid option, please try again.\n";
                    d = false;
				}
			}
            cout << "\n";
            // clear the savings account out after the transfer
            c.setSavings(0);
            e << currentDateTime() << c.getId() << " had their savings account set to $0\n";
            writeTrace(e.str());
            e.str("");
		}
	}
}

// function to transfer money from one account one of the users open accounts
void transfer(Client& c) {
	bool d = false;
    // loop until the user makes a valid choice
	while (!d) {
		cout << endl << "Which account would you like to transfer money from? (3 to cancel)\n";
		cout << "1 - Chequing\n";
		cout << "2 - Savings\n\n";
        // get the users choice from cin
		switch (getNumber()) {
        // case for a transfer from chequing
		case 1:
			e << currentDateTime() << c.getId() << " selected to transfer funds from their chequing account\n";
            writeTrace(e.str());
            e.str("");
			transferChequing(c);
			return;
        // case for a transfer from savings
		case 2:
			e << currentDateTime() << c.getId() << " selected to transfer funds from their savings account\n";
            writeTrace(e.str());
            e.str("");
			transferSavings(c);
			return;
        // case where user cancels the transfer operation
		case 3:
			e << currentDateTime() << c.getId() << " selected to cancel the transfer operation\n";
            writeTrace(e.str());
            e.str("");
			return;
		default:
                e << currentDateTime() << c.getId() << " entered an invalid option\n";
                writeTrace(e.str());
                e.str("");
                cout << endl << "That is not a valid option, please try again.\n";
		}
	}
}

// function to deposit money into one of the clients open accounts
void deposit(Client& c){
	bool d = false;
	double x;
    // loop until the user selects a valid choice
	while (!d) {
		d = true;
		cout << endl << "Which account would you ike to deposit funds into? (3 to cancel)\n";
		cout << "1 - Chequing\n";
		cout << "2 - Savings\n\n";
        // get the users choice from cin
		switch (getNumber()){
        // case where user deposits into their chequing
		case 1:
			e << currentDateTime() << c.getId() << " selected to deposit into their chequing account\n";
            writeTrace(e.str());
            e.str("");
			cout << endl << "How much money do you wish to deposit?\n";
			x = getDouble();
			c.setChequing(x + c.getChequing());
			cout << endl << "$" << fixed << x << " was successfully deposited to your chequing account.\n";
			e << currentDateTime() << c.getId() << " deposited $" << fixed << x << " into their chequing account\n";
            writeTrace(e.str());
            e.str("");
            // check if the user account was frozen before deposit
			if (c.isFrozen() == true) {
                // check if they can unfreeze the account with the new money
				if (c.getChequing() > (c.getAmountOwing()/10)) {
					c.setFrozen(false);
					cout << endl << "Your bank account is no longer frozen.\n";
					e << currentDateTime() << c.getId() << " has had their account unfrozen after a deposit\n";
                    writeTrace(e.str());
                    e.str("");
				}
			}
			break;
        // case where the user deposits into their savings
		case 2:
			e << currentDateTime() << c.getId() << " selected to deposit into their savings account\n";
            writeTrace(e.str());
            e.str("");
			cout << endl << "How much money do you wish to deposit?\n";
			x = getDouble();
			c.setSavings(x + c.getSavings());
            cout << endl << "$" << fixed << x << " was successfully deposited to your savings account.\n";
            e << currentDateTime() << c.getId() << " deposited $" << fixed << x << " into their savings account\n";
            writeTrace(e.str());
            e.str("");
			break;
		case 3:
			e << currentDateTime() << c.getId() << " selected to cancel the deposit operation\n";
            writeTrace(e.str());
            e.str("");
			return;
		default:
                e << currentDateTime() << c.getId() << " entered an invalid option\n";
                writeTrace(e.str());
                e.str("");
                cout << endl << "That is not a valid option, please try again.\n";
			d = false;
		}
	}
}

// function to withdraw money from client accounts
void withdraw(Client& c) {
    bool d = false;
    // loop until the user has made a valid decision
	while (!d) {
		cout << endl << "Which account would you like to withdraw funds from? (3 to cancel)\n";
		cout << "1 - Chequing\n";
		cout << "2 - Savings\n\n";
        // get the users choice from cin
		switch (getNumber()) {
        // case where the user withdraws from their chequing account
		case 1:
			e << currentDateTime() << c.getId() << " selected to withdraw from their chequing account\n";
            writeTrace(e.str());
            e.str("");
			withdrawChequing(c);
			return;
        // case where user withdraws from their savings account
		case 2:
			e << currentDateTime() << c.getId() << " selected to withdraw from their savings account\n";
            writeTrace(e.str());
            e.str("");
			withdrawSavings(c);
			return;
        // case where user chose to cancel the withdraw operation
		case 3:
			e << currentDateTime() << c.getId() << " selected to cancel the withdraw operation\n";
            writeTrace(e.str());
            e.str("");
			return;
		default:
                e << currentDateTime() << c.getId() << " entered an invalid option\n";
                writeTrace(e.str());
                e.str("");
                cout << endl << "That is not a valid option, please try again.\n";
		}
	}
}

// function for transferring money and dealing with the transaction from the chequing account
void transferChequing(Client& c) {
start:
	cout << endl << "How much money do you wish to transfer from chequing? (0 to cancel)\n";
	double x = getDouble();
    // if user cancelled the transfer
	if (x == 0) {
		e << currentDateTime() << c.getId() << " selected to cancel the transfer operation\n";
        writeTrace(e.str());
        e.str("");
		return;
	}
    // insufficient funds
	else if (x > c.getChequing()) {
		e << currentDateTime() << c.getId() << " had insufficient funds for transfer from chequing\n";
        writeTrace(e.str());
        e.str("");
		cout << endl << "Error: Insufficient funds, you only have $" << fixed << c.getChequing() << " in your chequing account.\n";
        // go back to start of transfer call method
		goto start;
	}
	else {
		e << currentDateTime() << c.getId() << " entered a valid transfer amount\n";
        writeTrace(e.str());
        e.str("");
		// apply the fee if the chequing account is put under the $1000 threshold
		if (fee(c, x)) {
			e << currentDateTime() << c.getId() << " is charged a $2.00 fee for the transfer\n";
            writeTrace(e.str());
            e.str("");
		warningmsg:
			// warning message for user to continue with the withdrawel
			cout << endl << "There will be a $2.00 fee for the transfer, do you wish to continue?\n";
			cout << "1 - Yes\n";
			cout << "2 - No\n\n";
            // get the users response from cin
			switch (getNumber()) {
            // case where the user accepts the fee
			case 1:
				e << currentDateTime() << c.getId() << " accepted the $2.00 fee\n";
                writeTrace(e.str());
                e.str("");
                // complete the transaction, ensuring the account wont drop below $0
				if (c.getChequing() - x - 2.00 < 0) {
					e << currentDateTime() << c.getId() << " can not afford the bank fee\n";
                    writeTrace(e.str());
                    e.str("");
					cout << endl << "Error: Insufficient funds, you only have $" << fixed << c.getChequing() << " in your chequing account.\n";
					goto start;
				}
				else {
					// complete the transaction without worrying about the fee
					c.setChequing(c.getChequing() - x - 2.00);
					c.setSavings(x + c.getSavings());
					cout << "$" << fixed << x <<" was successfully transferred from your chequing account.\n";
                    cout << "Your new balances are as follows: \n";
					cout << "Chequing $" << fixed << c.getChequing() << endl;
					cout << "Savings $" << fixed << c.getSavings() << endl;
					e << currentDateTime() << c.getId() << " successfully transferred $" << fixed << x << " with a $2.00 fee\n";
                    writeTrace(e.str());
                    e.str("");
					return;
				}
				break;
            // case where the user cancels the transaction fully
			case 2:
				e << currentDateTime() << c.getId() << " cancelled the withdrawel from chequing\n";
                writeTrace(e.str());
                e.str("");
                cout << "Transfer was cancelled with no charges to your account.\n";
				return;
			default:
                    e << currentDateTime() << c.getId() << " entered an invalid option\n";
                    writeTrace(e.str());
                    e.str("");
                    cout << endl << "That is not a valid option, please try again.\n";
				goto warningmsg;
			}
		}
		else {
            // case for a transfer with no fee (above $1000)
			c.setChequing(c.getChequing() - x);
			c.setSavings(x + c.getSavings());
            cout << "$" << fixed << x <<" was successfully transferred from your chequing account.\n";
            cout << "Your new balances are as follows: \n";
            cout << "Chequing $" << fixed << c.getChequing() << endl;
            cout << "Savings $" << fixed << c.getSavings() << endl;
			e << currentDateTime() << c.getId() << " successfully transferred $" << fixed << x << " without a fee\n";
            writeTrace(e.str());
            e.str("");
		}

	}
}

// function for transferring money and dealing with the transaction from the savings account
void transferSavings(Client& c) {
    cout << endl << "How much money do you wish to transfer from savings? (0 to cancel)\n";
	double amount;
	amount = getDouble();
    // if user cancels the transfer
	if (amount == 0) {
        e << currentDateTime() << c.getId() << " selected to cancel the transfer operation\n";
        writeTrace(e.str());
        e.str("");
		return;
	}
	else if (amount > c.getSavings()) {
        e << currentDateTime() << c.getId() << " had insufficient funds for transfer from savings\n";
        writeTrace(e.str());
        e.str("");
        cout << endl << "Error: Insufficient funds, you only have $" << fixed << c.getSavings() << " in your savings account.\n";
		return;
	}
	c.setChequing(amount + c.getChequing());
	c.setSavings(c.getSavings() - amount);
    cout << "$" << fixed << amount <<" was successfully transferred from your savings account.\n";
    cout << "Your new balances are as follows: \n";
    cout << "Chequing $" << fixed << c.getChequing() << endl;
    cout << "Savings $" << fixed << c.getSavings() << endl;
    e << currentDateTime() << c.getId() << " successfully transferred $" << fixed << amount << " from savings\n";
    writeTrace(e.str());
    e.str("");
    // check if we can unfreeze the account now
	if (c.isFrozen() == true){
		if (c.getChequing() > (c.getAmountOwing()/10)) {
			c.setFrozen(false);
            cout << endl << "Your bank account is no longer frozen.\n";
            e << currentDateTime() << c.getId() << " has had their account unfrozen after a transfer to chequing from savings\n";
            writeTrace(e.str());
            e.str("");
		}
	}
}

// function for a withdrawel from chequing account
void withdrawChequing(Client& c) {
start:
	cout << endl << "How much money do you wish to withdraw from your chequing account? (0 to cancel)\n";
    double x = getDouble();
    // if client cancels the withdraw operation
	if (x == 0) {
		e << currentDateTime() << c.getId() << " selected to cancel the withdraw operation\n";
        writeTrace(e.str());
        e.str("");
		return;
	}
    // check if there are enough funds to withdraw
	else if (x > c.getChequing()) {
        e << currentDateTime() << c.getId() << " had insufficient funds for a withdrawel from chequing\n";
        writeTrace(e.str());
        e.str("");
        cout << endl << "Error: Insufficient funds, you only have $" << fixed << c.getChequing() << " in your chequing account.\n";
		goto start;
	}
	else {
		// check if the fee will need to be applied for the chequing account
		if (fee(c, x)) {
            e << currentDateTime() << c.getId() << " is charged a $2.00 fee for the withdrawel\n";
            writeTrace(e.str());
            e.str("");
		warningmsg:
			// warn the user of the fee for this withdrawel
            // warning message for user to continue with the withdrawel
            cout << endl << "There will be a $2.00 fee for the withdrawel, do you wish to continue?\n";
            cout << "1 - Yes\n";
            cout << "2 - No\n\n";
            // get the response from the user
			switch (getNumber()) {
			case 1:
				e << currentDateTime() << c.getId() << " accepted the $2.00 fee\n";
                writeTrace(e.str());
                e.str("");
                if (c.getChequing() - x - 2.00 < 0) {
					e << currentDateTime() << c.getId() << " could not afford the bank fee\n";
                    writeTrace(e.str());
                    e.str("");
					cout << endl << "Error: Insufficient funds, you only have $" << fixed << c.getChequing() << " in your chequing account.\n";
					goto start;
				}
				else {
					// complete the transaction
					c.setChequing(c.getChequing() - x - 2.00);
					cout << endl << "$" << fixed << x <<" was successfully withdrawn from your chequing account with the bank fee.\n";
					cout << "Your chequing balance is now $" << fixed << c.getChequing();
					e << currentDateTime() << c.getId() << " successfully withdrew $" << fixed << x << " with a fee\n";
                writeTrace(e.str());
                e.str("");
					return;
				}
				break;
            // case where client cancels the withdraw operation
			case 2:
				e << currentDateTime() << c.getId() << " selected to cancel the withdraw operation\n"; writeTrace(e.str()); e.str("");
				cout << "Withdraw was cancelled with no charges to your account.\n";
				return;
			default:
                    e << currentDateTime() << c.getId() << " entered an invalid option\n";
                    writeTrace(e.str());
                    e.str("");
                    cout << endl << "That is not a valid option, please try again.\n";
				goto warningmsg;
			}
		}
        // otherwise, no fee for the withdrawel
		else {
			c.setChequing(c.getChequing() - x);
            cout << endl << "$" << fixed << x <<" was successfully withdrawn from your chequing account.\n";
            cout << "Your chequing balance is now $" << fixed << c.getChequing();
            e << currentDateTime() << c.getId() << " successfully withdrew $" << fixed << x << " with no fee\n";
            writeTrace(e.str());
            e.str("");
		}
	}
}

// function for a withdrawel from savings account
void withdrawSavings(Client c){
start:
	cout << endl << "How much money do you wish to withdraw from your savings account? (0 to cancel)\n";
	double x = getDouble();
    // if user cancels operation
	if (x == 0) {
        e << currentDateTime() << c.getId() << " selected to cancel the withdraw operation\n";
        writeTrace(e.str());
        e.str("");
		return;
	}
    // check if there are enough funds to withdraw
	else if (x > c.getSavings()) {
        e << currentDateTime() << c.getId() << " had insufficient funds for a withdrawel from savings\n";
        writeTrace(e.str());
        e.str("");
        cout << endl << "Error: Insufficient funds, you only have $" << fixed << c.getSavings() << " in your savings account.\n";
		goto start;
	}
    // complete the transaction
	else {
		c.setSavings(c.getSavings() - x);
        cout << endl << "$" << fixed << x <<" was successfully withdrawn from your savings account.\n";
        cout << "Your savings balance is now $" << fixed << c.getSavings();
        e << currentDateTime() << c.getId() << " successfully withdrew $" << fixed << x << " from their savings account\n";
        writeTrace(e.str());
        e.str("");
	}
}

// function to save the current clients to the text file database
void saveClients(vector<Client>& cList){
	// sort the clients list by account ID number
	sortNumber(cList);
    // output stream for the clients database
	ofstream outDB("clientDB.txt");
    // loop through the clients
	for (int i = 0; i < cList.size(); i++) {
		outDB << cList[i].getId() << " " << fixed << cList[i].getChequing() << " " << fixed << cList[i].getSavings() << " " << cList[i].getFirstName() << " " << cList[i].getLastName() << " " << cList[i].getPin();
        // output the state of the account on the same line
		if (cList[i].isFrozen() == true) {
			outDB << " frozen ";
		}
        else {
			outDB << " clear ";
		}
		outDB << fixed << cList[i].getCredLimit();
        // output the payment option in the same out line
		if (cList[i].getFull() == true) {
			outDB << " full ";
		}
		else {
			outDB << " part ";
		}
        // output the interest owing for the account
		outDB << cList[i].getInterest() << endl;
	}
    // close the output stream
	outDB.close();
}

// function to save the client purchases of items
void savePurchases(vector<Client>& cList){
	// sort the clients list by account number
	sortNumber(cList);
    // create an output stream for the transactions
	ofstream outDB("clientTransaction.txt");
	e << currentDateTime() << "All client transactions are being saved\n";
    writeTrace(e.str());
    e.str("");
    // loop through all of the clients
	for (int i = 0; i < cList.size(); i++) {
		outDB << cList[i].getId();
        // loop through each clients purchasee list
		for (int x = 0; x < cList[i].getSizeOfPurchases(); x++) {
			outDB << " " << cList[i].getPurchase(x);
		}
		outDB << "\n";
	}
    // close the outfile stream
	outDB.close();
}

// function for saving an individal transaction of an "item" for a client purchase
void saveTransaction(Client c, double price) {
	e << currentDateTime() << c.getId() << " has their purchase(s) being saved\n";
    writeTrace(e.str());
    e.str("");
	ofstream buy;
    // open the stream to save purchase to
	buy.open("purchaseLog.txt", ios_base::app);
    // write the individual purchase line to file
	buy << c.getId() << " " << fixed << price << endl;
}

// save the bank data storing the users login for management and days in month
void saveBankData(Manager m, Maintenance s) {
	ofstream outDB("bankData.txt");
	outDB << "Maintenance " << s.getID() << endl;
	outDB << "Manager " << m.getID() << endl;
	outDB << "EndOfMonth " << endOfMonth;
	outDB.close();
}

// function to view the list of purchases for a specific client
void viewPurchases(Client c) {
	e << currentDateTime() << "Viewing purchases for " << c.getId() << "\n";
    writeTrace(e.str());
    e.str("");
    // initialize and declare variables for the sum and purchase number for the client
	double sum = 0;
	int p = 1;
	cout << "Client purchases for this month...\n";
	for (int i = 0; i < c.getSizeOfPurchases(); i++) {
		cout << p << ". $" << fixed << c.getPurchase(i) << endl;
        // add to the counting sum of all purchases
		sum += c.getPurchase(i);
		p++;
	}
    
	cout << endl << "These purchases above total $" << fixed << sum << endl;
    
	if ((0.50* c.getChequing()) < sum) {
		cout << endl << "Warning: You have spent over half of your chequing balance.\n";
		cout << "You have $" << fixed << c.getChequing() << " remaining in your chequing account.\n";
		e << currentDateTime() << c.getId() << " has spent more than 50% of their chequing account\n";
        writeTrace(e.str());
        e.str("");
	}
}

// option to toggle the full payment option
void payFullAmount(Client& c){
    // initialize a boolean for being finished the operation here
    bool d = false;
    // loop while a decision has not been completed
    while (!d) {
        if (c.getFull() == true){
            cout << endl << "Your account is set to make a full payment in " << endOfMonth << " days.\n";
            cout << "Would you like to change this option to a smaller payment?\n";
        }
        else {
            cout << endl << "Your account is set to make a minimum payment in " << endOfMonth << " days.\n";
            cout << "Would you like to change this option to a full payment?\n";
        }
        cout << "1 - Yes\n";
        cout << "2 - No\n\n";
        
        // get the users yes or no answer
        switch (getNumber()){
                // case for yes
            case 1:
                e << currentDateTime() << c.getId() << " toggled full payment option\n";
                writeTrace(e.str());
                e.str("");
                if (c.getFull() == true) c.setFull(false);
                else c.setFull(true);
                d = true;
                break;
                // case for no
            case 2:
                e << currentDateTime() << c.getId() << " cancelled the toggle operation\n";
                writeTrace(e.str());
                e.str("");
                d = true;
                break;
            default:
                e << currentDateTime() << c.getId() << " entered an invalid option\n";
                writeTrace(e.str());
                e.str("");
                cout << "That is not a valid option, please try again.\n";
        }
    }
}

// function to update to the next monthly payment period for all bank users
void updateMonth(vector<Client>& cList){
	e << currentDateTime() << "Clients are making end of month payments to credit\n";
    writeTrace(e.str());
    e.str("");
    // loop through the list of users
	for (int i = 0; i < cList.size(); i++) {
        // get the amount in the chequing account
        double che = cList[i].getChequing();
        // check if the client has valid chequing
		if (che > 0) {
            // get the amount that the client owes
            double owe = cList[i].payDay();
            // check how their payment plan is set up
			bool full = cList[i].getFull();
            // client does not have enough to actually pay amount owed in full
            if (full == true && owe > che) {
                // check if client can at least make a minimum payment
				if (owe/10 > che) {
                    // freeze the client account until they can
                    cList[i].setFrozen(true);
                    // append the client interest
					cList[i].setInterest(cList[i].getInterest() + owe);
					cList[i].setInterest(cList[i].getInterest() * 1.02);
                    // write to file
					writeFailedTransaction(cList[i]);
					e << currentDateTime() << cList[i].getId() << " failed to make at least a minimum payment - their account has been frozen\n";
                    writeTrace(e.str());
                    e.str("");
				}
				else {
                    // client makes a minimum payment if they have sufficient funds
					double oweReal = (owe * 0.9);
					owe *= 0.1;
					cList[i].setInterest(cList[i].getInterest() + oweReal);
					cList[i].setInterest(cList[i].getInterest() * 1.02);
                    // take the payment from the clients chequing account
					cList[i].setChequing(che - owe);
                    e << currentDateTime() << cList[i].getId() << " made a minimum payment successfully\n";
                    writeTrace(e.str());
                    e.str("");
				}
			}
            // if the client does not have enough for a minimum payment
			else if (full == false && owe > che) {
                // freeze the clients account
				cList[i].setFrozen(true);
				cList[i].setInterest(cList[i].getInterest() + (owe * 1.02));
				writeFailedTransaction(cList[i]);
                e << currentDateTime() << cList[i].getId() << " failed to make at least a minimum payment - their account has been frozen\n";
                writeTrace(e.str());
                e.str("");
			}
            // if the client can successfully make the full payment
			else if (full == true && owe < che) {
				cList[i].setChequing(che - owe);
				cList[i].setInterest(0.0);
                e << currentDateTime() << cList[i].getId() << " has made a full payment and is no longer in debt\n";
                writeTrace(e.str());
                e.str("");
			}
            else if (full == false && owe < che) {
				cList[i].setChequing(che - owe);
                e << currentDateTime() << cList[i].getId() << " has made a minimum payment towards their debt\n";
                writeTrace(e.str());
                e.str("");
			}
		}
	}
	saveClients(cList);
}

// function to print the menu for the client to the window
void printClientMenu(Client c, bool che, bool sav){
	// header alert for users account status and debt
	if (c.getChequing() > 0){
		cout << endl << "Please be advised you are $" << fixed << (c.getAmountOwing() + c.getAmountOwed()) << " in debt currently.\n";
		cout << "Your next bill will be for $" << fixed << ((c.getAmountOwing() + c.getAmountOwed()) / 10) << ".\n";
		cout << "You are set to automatically make a payment in " << endOfMonth << " days.\n";
	}
    // give the client options
	cout << endl << "What can we do for you, " << c.getFirstName() << "?\n";
    // check whether the user would want to open or close a possible chequing account
	if (!che) {
        cout << "1  - Open a chequing account\n";
    }
    else {
        cout << "1  - Close a chequing account\n";
    }
    // check whather the user would want to open or close a possible savings account
	if (!sav) {
        cout << "2  - Open a savings account\n";
    }
    else {
        cout << "2  - Close a savings account\n";
    }

	cout << "3  - Deposit\n";
	cout << "4  - Withdraw\n";
	cout << "5  - View Balances\n";
	cout << "6  - Transfer Money\n";
	cout << "7  - Make a purchase\n";
	cout << "8  - View Purchases\n";
	cout << "9  - Switch payment plan\n";
	cout << "10 - Logout\n" << endl;

}

// function to print the menu for the manager to the window
void printManagerMenu() {
	cout << endl << "What can we do for you, Manager?\n";
	cout << "1 - Create an account\n";
	cout << "2 - Delete an account\n";
	cout << "3 - Display one account\n";
	cout << "4 - Display all accounts\n";
	cout << "5 - Display failed transactions\n";
	cout << "6 - Logout\n" << endl;
}

// function to control the operations of the manager menu
void managerMenu(vector<Client>& cList) {
	cout << endl << "Welcome Manager!\n";
start:
    // declare and initialize a boolean for logging out
	bool logout = false;
	while (!logout) {
        // print the manager menu for the current manager online
		printManagerMenu();
        // get the managers response
		switch (getNumber()){
        // case to create a user account
            case 1: {
			e << currentDateTime() << "Manager selected to create an account\n";
            writeTrace(e.str());
            e.str("");
			// automatically generate the next available account number
			int rNum;
			if (cList.empty()) {
				e << currentDateTime() << "Initial account with ID 11111 has been created\n";
                writeTrace(e.str());
                e.str("");
				rNum = 11111;
			}
            // create the next key ID number by adding 1 to the previous listing
			else {
				rNum = cList[cList.size() - 1].getId() + 1;
                e << currentDateTime() << "New account number with ID " << rNum << " has been created\n";
                writeTrace(e.str());
                e.str("");
			}

			// prompt the user for their first name
			bool flag = false;
                // initialize and declare a boolean flag for the validation of the user input
			flag = false;
			string firstName;
			while (!flag) {
				cout << "New clients first name (0 to cancel)\n";
				cin >> firstName;
                // case where the manager selects to cancel the account creation
				if (firstName.compare("0") == 0) {
					e << currentDateTime() << "Manager has selected to cancel the account creation\n";
                    writeTrace(e.str());
                    e.str("");
					goto start;
				}
                // validate the first name input
				else if (firstName.size() > 0) {
					e << currentDateTime() << "Manager has entered a valid first name\n";
                    writeTrace(e.str());
                    e.str("");
					flag = true;
				}
				else {
					e << currentDateTime() << "Manager has entered an invalid first name\n";
                    writeTrace(e.str());
                    e.str("");
					cout << "Please enter a valid first name.\n";
				}
			}

			// prompt for the account last name
			flag = false;
			string lastName;
                while (!flag) {
                    cout << "New clients last name (0 to cancel)\n";
                    cin >> lastName;
                    // case where the manager selects to cancel the account creation
                    if (lastName.compare("0") == 0) {
                        e << currentDateTime() << "Manager has selected to cancel the account creation\n";
                        writeTrace(e.str());
                        e.str("");
                        // go back to the manager menu
                        goto start;
                    }
                    // validate the last name input
                    else if (lastName.size() > 0) {
                        e << currentDateTime() << "Manager has entered a valid last name\n";
                        writeTrace(e.str());
                        e.str("");
                        flag = true;
                    }
                    else {
                        e << currentDateTime() << "Manager has entered an invalid last name\n";
                        writeTrace(e.str());
                        e.str("");
                        cout << "Please enter a valid last name.\n";
                    }
                }
                
                // prompt for the account pin
                flag = false;
                int pin;
                while (!flag) {
                    cout << "New clients 4-digit pin number for verification (0 to cancel)\n";
                    cin >> pin;
                    int length = floor(log10(abs(pin))) + 1;
                    // case where the manager selects to cancel the account creation
                    if (pin == 0) {
                        e << currentDateTime() << "Manager has selected to cancel the account creation\n";
                        writeTrace(e.str());
                        e.str("");
                        // go back to the manager menu
                        goto start;
                    }
                    // validate the pin input
                    else if (length == 4 && isalpha(pin) == 0) {
                        e << currentDateTime() << "Manager has entered a valid pin\n";
                        writeTrace(e.str());
                        e.str("");
                        flag = true;
                    }
                    else {
                        e << currentDateTime() << "Manager has entered an invalid pin\n";
                        writeTrace(e.str());
                        e.str("");
                        cout << "Please enter a valid 4-digit pin.\n";
                    }
                }

			// open the account for the entered client
			bool success = openAccount(cList, rNum, pin, firstName, lastName);
			if (!success) {
				e << currentDateTime() << "Manager successfully open the new account\n";
                writeTrace(e.str());
                e.str("");
				cout << "Error: The account you attempted to open already exists.\n";
			}
			else {
				e << currentDateTime() << "Manager encountered an account error trying to open account " << rNum << "\n";
                writeTrace(e.str());
                e.str("");
				cout << "The account ending in " << rNum << " for " << firstName << " " << lastName << " was created successfully.\n";
			}
			break;
		}

		// case for manager to delete an account
		case 2:
		{
			e << currentDateTime() << "Manager selected to delete an account\n";
            writeTrace(e.str());
            e.str("");
            // initialize and declare a boolean for the account deletion check
			bool check = false;
			// get the account number from the manager
			while (!check) {
				cout << "Enter the account number to delete (0 to cancel)\n";
				int aNum = getNumber();
				if (aNum == 0) {
					e << currentDateTime() << "Manager has selected to cancel the deletion\n";
                    writeTrace(e.str());
                    e.str("");
					goto start;
				}
				// check if there is remaining balance in the account
				int x = getAccountIndex(cList, aNum, 0, cList.size()-1);
				if (x == -1) {
					cout << "The account ending in " << aNum << " could not be found in our system.\n";
				}
				else if (cList[x].getSavings() != 0 || cList[x].getChequing() != 0) {
					e << currentDateTime() << "Manager could not complete the account deletion because there was a remaining balance\n";
                    writeTrace(e.str());
                    e.str("");
					cout << "The account ending in " << aNum << " could not be deleted because there exists a remaining balance.\n";
				}
				// if there is no leftover funds, delete the account
                else {
					// confirm the deletion with the manager
					cout << endl << "Are you sure you want to delete " << cList[x].getFirstName() << " " << cList[x].getLastName() << "'s account number " << aNum << "?\n";
					cout << "1 - Yes\n";
					cout << "2 - No\n\n";
                    // get the manangers confirmation from the keyboard
					switch (getNumber()) {
                    // case where manager wishes to proceed with the operation
                        case 1: {
						e << currentDateTime() << "Manager selected to proceed with the deletion\n";
                        writeTrace(e.str());
                        e.str("");
                        // try to delete the account for good
						bool success = deleteAccount(cList, aNum);
						if (!success) {
							cout << "The account ending in " << aNum << " could not be deleted at this time.\n";
						}
						else {
							cout << "The account ending in " << aNum << " was successfully removed from the database.\n";
							check = true;
							break;
						}
                        }
                    // case where manager decides to cancel the deletion
                        case 2: {
						e << currentDateTime() << "Manager selected to cancel the operation\n";
                        writeTrace(e.str());
                        e.str("");
						cout << "Operation cancelled.\n";
						goto start;
                        }
                        default: {
                        e << currentDateTime() << "Manager entered an invalid option\n";
                        writeTrace(e.str());
                        e.str("");
                        cout << "That is not a valid option, please try again.\n";
                        }
				}
			}
            }
			break;
		}

		// display a single accounts information
		case 3:
		{
			e << currentDateTime() << "Manager selected to display a single account\n";
            writeTrace(e.str());
            e.str("");
			bool good = false;
			while (!good) {
				if (cList.size() == 0){
					cout << "There are no account in the database yet.\n";
					goto start;
				}
				cout << "Enter the account number to view (0 to cancel)\n";
				int aNum = getNumber();
                if (aNum == 0) {
                    goto start;
                }
				// check if the account exists in the database
				if (isDB(cList, aNum)) {
					// find the location of the account in the clients list of vectors
					int i = getAccountIndex(cList, aNum, 0, cList.size() - 1);
					// display the data for the individual account
					cout << "------------------------------------------" << endl;
                    cout << "Name:             " << cList[i].getFirstName() << " " << cList[i].getLastName() << endl;
					cout << "Account Number:   " << cList[i].getId() << endl;
					cout << "Chequing Balance: $" << fixed << cList[i].getChequing() << endl;
                    cout << "Savings Balance:  $" << fixed << cList[i].getSavings() << endl;
					cout << "Debt Owing:       $" << fixed << cList[i].getAmountOwing() + cList[i].getAmountOwed() << endl;
					cout << "------------------------------------------" << endl;
					good = true;
					e << currentDateTime() << "Manager successfully viewed a single account\n";
                    writeTrace(e.str());
                    e.str("");
				}
				else {
					e << currentDateTime() << "Manager has entered an account number that does not exist\n";
                    writeTrace(e.str());
                    e.str("");
					cout << "The account ending in " << aNum << " could not be found.\n";
				}
			}
			break;
		}

		// case for manager to display all the bank accounts
		case 4:
		{
			e << currentDateTime() << "Manager selected to display all of the existing bank accounts\n";
            writeTrace(e.str());
            e.str("");
			if (cList.size() == 0) {
				cout << "There are no existing bank accounts yet.\n";
			}
			else {
				e << currentDateTime() << "Manager is asked how to filter the accounts\n";
                writeTrace(e.str());
                e.str("");
				cout << "How would you like to filter the accounts? (0 to cancel)\n";
				cout << "1 - Account number\n";
				cout << "2 - Last name\n";
                switch (getNumber())
				{
                        // case for filtering all the bank accounts by account number
				case 1:
				{
					e << currentDateTime() << "Manager selected to filter the accounts by account number\n";
                    writeTrace(e.str());
                    e.str("");
					// display the accounts in order
                    for (int i = 0; i < cList.size(); i++) {
                        cout << "------------------------------------------" << endl;
                        cout << "Name:             " << cList[i].getFirstName() << " " << cList[i].getLastName() << endl;
						cout << "Account Number:   " << cList[i].getId() << endl;
                        cout << "Chequing Balance: $" << fixed << cList[i].getChequing() << endl;
						cout << "Savings Balance:  $" << fixed << cList[i].getSavings() << endl;
						cout << "Debt Owing:       $" << fixed << cList[i].getAmountOwing() + cList[i].getAmountOwed() << endl;
					}
					cout << "------------------------------------------" << endl;
					break;
				}
                // case for filtering all the bank accounts by name
				case 2:
				{
					e << currentDateTime() << "Manager selected to filter the accounts by last name\n";
                    writeTrace(e.str());
                    e.str("");
					vector<Client> alphaClients = sortName(cList);
					for (int i = 0; i < alphaClients.size(); i++) {
						cout << "------------------------------------------" << endl;
						cout << "Name:             " << alphaClients[i].getFirstName() << " " << alphaClients[i].getLastName() << endl;
                        cout << "Account Number:   " << alphaClients[i].getId() << endl;
                        cout << "Chequing Balance: $" << fixed << alphaClients[i].getChequing() << endl;
						cout << "Savings Balance:  $" << fixed << alphaClients[i].getSavings() << endl;
						cout << "Debt Owing:       $" << fixed << cList[i].getAmountOwing() + cList[i].getAmountOwed() << endl;
					}
					cout << "------------------------------------------" << endl;
					break;
				}
				case 0:
				{
					e << currentDateTime() << "Manager selected to cancel the account display\n";
                    writeTrace(e.str());
                    e.str("");
					goto start;
				}
				default:
				{
                    e << currentDateTime() << "Manager entered an invalid option\n";
                    writeTrace(e.str());
                    e.str("");
                    cout << "That is not a valid option, please try again.\n";
				}
				}

			}
			break;
		}
		// case to display the failed client payments
		case 5:
		{
			e << currentDateTime() << "Manager selected to display all of the failed payments\n";
            writeTrace(e.str());
            e.str("");
			string line;
			int id;
			double value;
			ifstream ff("failedTransaction.txt");
			cout << endl;
			if (ff.is_open()){
				while (getline(ff, line))
				{
					stringstream ss(line);
					ss >> id >> value;
					cout << "Client number " << id << " failed to pay a charge of $" << fixed << value << endl;
				}
				ff.close();
			}
			else {
				cout << "Error: The failed payments log was not found.\n";
			}
			break;
		}
		// case to log out of the system
		case 6:
		{
			e << currentDateTime() << "Manager selected to logout of the system\n";
            writeTrace(e.str());
            e.str("");
			return;
		}
		default:
                e << currentDateTime() << "Manager entered an invalid option\n";
                writeTrace(e.str());
                e.str("");
                cout << "That is not a valid option, please try again.\n";
		}
	}
}

// function to open a new account
bool openAccount(vector<Client>&cList, int accID, int p, string firstName, string lastName)
{
	// check if the account number already exists
	if (isDB(cList, accID)) {
		e << currentDateTime() << "This account already exists in the database\n";
        writeTrace(e.str());
        e.str("");
		return false;
	}
	else {
		// create the new client
		Client newClient = Client();
		newClient.setFirstName(firstName);
		newClient.setLastName(lastName);
		newClient.setId(accID);
        newClient.setPin(p);
		// add it to the list of client vectors
		cList.push_back(newClient);
		// add the client to the database
		saveClients(cList);
		e << currentDateTime() << "Manager has successfully opened an account\n";
        writeTrace(e.str());
        e.str("");
		return true;
	}
}

// function for deleting the desired account from the client database
bool deleteAccount(vector<Client>& cList, int accID) {
	// check if there exists a list of account vectors already
	if (cList.empty()) {
		return false;
	}
	// check that the id to delete is in fact in the database before the operation
	else if (isDB(cList, accID)) {
		// find the index value of the account in the database
		int i = getAccountIndex(cList, accID, 0, cList.size() - 1);
		// remove the account from the cList
		cList.erase(cList.begin() + i);
		// update the database of all remaining accounts
		saveClients(cList);
		e << currentDateTime() << "Manager successfully deleted account " << accID << "\n";
        writeTrace(e.str());
        e.str("");
		return true;
	}
	else {
		e << currentDateTime() << "Manager could not delete the account at this time\n";
        writeTrace(e.str());
        e.str("");
		return false;
	}
}

// function to sort the clients by account number
void sortNumber(vector<Client>&cList) {
	if (cList.empty()) {
		return;
	}
	std::sort(cList.begin(), cList.end(), compareAccountNums);
}

// function to sort the clients by last name
vector<Client> sortName(vector<Client>cList) {
	if (cList.empty()) {
		return cList;
	}
	// sort the list but do not save to database
	sort(cList.begin(), cList.end(), compareAccountLastName);
	return cList;
}

// function to check if a client exists in the database, returns boolean true if extsts
bool isDB(vector<Client>& cList, int t) {
	if (cList.empty()){
		return false;
	}
	sortNumber(cList);
	int r = getAccountIndex(cList, t, 0, cList.size() - 1);
	if (r == -1){
		return false;
	}
	else {
		return true;
	}
}

bool compareAccountLastName(Client a, Client b) {
	return (a.getLastName() < b.getLastName());
}

bool compareAccountNums(Client a, Client b) {
	return (a.getId() < b.getId()); 
}

// function to get the account index from the database
int getAccountIndex(vector<Client>& cList, int targetAccNum, int low, int high) {
    if (high < low) {
        return -1;
    }
	int mid = low + ((high - low) / 2);
	if (cList[mid].getId() > targetAccNum) {
		return getAccountIndex(cList, targetAccNum, low, mid - 1);
	}
	else if (cList[mid].getId() < targetAccNum) {
		return getAccountIndex(cList, targetAccNum, mid + 1, high);
	}
	else {
		return mid;
	}
}

// function to display the maintenance options
void maintenanceMenu(void){
	cout << endl << "Welcome Maintenance Person!\n";
start:
	bool logout = false;
	while (!logout){
		cout << endl << "What can we do for you?\n";
		cout << "1 - Toggle execution trace feature\n";
		cout << "2 - Print execution trace to screen\n";
		cout << "3 - Clear all execution traces\n";
		cout << "4 - Logout\n";
        // get the maintenance persons choice
		switch (getNumber()) {
        // case where the maintenance person toggles the execution trace
		case 1: {
			e << currentDateTime() << "Maintenance selected to toggle the execution trace\n";
            writeTrace(e.str());
            e.str("");
			toggleExecutionTrace();
			break;
		}

        // case to print the execution trace to screen
		case 2: {
			e << currentDateTime() << "Maintenance selected to print the execution trace to screen\n";
            writeTrace(e.str());
            e.str("");
			displayTrace();
			break;
		}

		case 3: {
			e << currentDateTime() << "Maintenance selected to clear the trace history\n";
            writeTrace(e.str());
            e.str("");
			cout << endl << "Are you sure you want to clear all execution trace history?\n";
			cout << "1 - Yes\n";
			cout << "2 - No\n\n";
			e << currentDateTime() << "Maintenance is asked for confirmation on the log clear\n"; writeTrace(e.str()); e.str("");
			switch (getNumber()) {
            // case to proceed in deleting all execution trace history
			case 1:{
				e << currentDateTime() << "Maintenance selected to proceed in deleting all previous traces\n";
                writeTrace(e.str());
                e.str("");
				clearTraceLog();
				goto start;
			}
            // case to cancel the trace clear
			case 2:{
				e << currentDateTime() << "Maintenance selected to cancel the trace clear operation\n";
                writeTrace(e.str());
                e.str("");
				goto start;
			}
			default:{
                e << currentDateTime() << "Maintenance entered an invalid option\n";
                writeTrace(e.str());
                e.str("");
                cout << "That is not a valid option, please try again.\n";
			}
			}
			break;
		}
        // case to logout as maintance person
		case 4:{
			e << currentDateTime() << "Maintenance selected to logout\n";
            writeTrace(e.str());
            e.str("");
			return;
		}
		default:{
            e << currentDateTime() << "Maintenance entered an invalid option\n";
            writeTrace(e.str());
            e.str("");
            cout << "That is not a valid option, please try again.\n";
        }
		}
	}
}

// function for getting an int value from the user, returns the integer value
int getNumber(){
	e << currentDateTime() << "Processing integer input\n";
    writeTrace(e.str());
    e.str("");
	int amount;
    cin >> amount;
	// if the entered value is not an integer
    while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Invalid input. Please enter a number choice:\n";
		e << currentDateTime() << "An invalid input was detected\n";
        writeTrace(e.str());
        e.str("");
		cin >> amount;
	}
	e << currentDateTime() << "User entered valid number --> " << amount << " <--\n";
    writeTrace(e.str());
    e.str("");
	return amount;
}

// function for getting an double value from the user, returns the double value
double getDouble(){
	e << currentDateTime() << "Processing input as double\n";
    writeTrace(e.str());
    e.str("");
	double amount;
	cin >> amount;
	// checking validity of the user input
	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Invalid input. Please enter a number choice:\n";
		e << currentDateTime() << "An invalid input was detected\n";
        writeTrace(e.str());
        e.str("");
		cin >> amount;
	}
    e << currentDateTime() << "User entered valid double --> " << amount << " <--\n";
    writeTrace(e.str());
    e.str("");
    return amount;
}

// function to determine if a bank fee is required or not
bool fee(Client c, double amount) {
    // check if the clients chequing account will be brought under $1000 balance
	if (c.getChequing() - amount < 1000.00) {
		e << currentDateTime() << "There will be a bank fee for client number " << c.getId() << "\n";
        writeTrace(e.str());
        e.str("");
		return true;
	}
	else {
        e << currentDateTime() << "There will not be a bank fee for client number " << c.getId() << "\n";
        writeTrace(e.str());
        e.str("");
		return false;
	}
}

// function to toggle the ON and OFF for writing execution trace
void toggleExecutionTrace(){
	if (trace == ON) {
		cout << endl << "Execution trace is ON. Do you wish to toggle it OFF?\n";
		cout << "1 - Yes\n";
		cout << "2 - No\n\n";
		switch (getNumber()) {
        // case to switch off execution tracing
		case 1:{
			string line;
			trace = OFF;
			ifstream traceLog;
			traceLog.open("executionTrace.txt");
			if (traceLog.is_open()) {
                ofstream tempFile;
				tempFile.open("temp.txt");
				if (tempFile.is_open()) {
					getline(traceLog, line);
					while (getline(traceLog, line)){
						tempFile << line << endl;
					}
					tempFile.close();
					traceLog.close();
					ofstream traceLogWrite("executionTrace.txt");
					traceLogWrite << "0\n";
					ifstream tempFileRead("temp.txt");
					while (getline(tempFileRead, line)){
						traceLogWrite << line << endl;
					}
					traceLogWrite.close();
					tempFileRead.close();
                    if (remove("temp.txt") != 0) {
                        cout << "There was an unexpected error deleting the temporary logs.\n";
                    }
				}
				else {
					cout << "Error: Could not create neccesary temporary log file.\n";
					return;
				}
			}
			else {
				cout << "Error: Could not open the existing execution traces.\n";
				return;
			}
			cout << "Execution tracing is OFF.\n";
			break;
		}
		case 2:{
			cout << "Execution tracing is ON.\n";
			break;
		}
		default:{
			cout << "Invalid input. Please enter a valid number choice.\n";
		}
		}
	}
	else {
		cout << endl << "Execution trace is OFF. Do you wish to toggle it ON?\n";
		cout << "1 - Yes\n";
		cout << "2 - No\n\n";
		switch (getNumber()){

		case 1:{
			string line;
			trace = ON;
			ifstream traceLog;
			traceLog.open("executionTrace.txt");
			if (traceLog.is_open()){
                ofstream tempFile;
				tempFile.open("temp.txt");
				if (tempFile.is_open()){
					getline(traceLog, line);
					while (getline(traceLog, line)){
						tempFile << line << endl;
					}
					tempFile.close();
					traceLog.close();
					ofstream traceLogWrite("executionTrace.txt");
					traceLogWrite << "1\n";
					ifstream tempFileRead("temp.txt");
					while (getline(tempFileRead, line)) {
						traceLogWrite << line << endl;
					}
					traceLogWrite.close();
					tempFileRead.close();
                    if (remove("temp.txt") != 0) {
                        cout << "There was an unexpected error deleting the temporary logs.\n";
                    }
				}
				else{
                    cout << "Error: Could not create neccesary temporary log file.\n";
                    return;
				}

			}
			else{
                cout << "Error: Could not open the existing execution traces.\n";
                return;
			}
			cout << "Execution tracing is ON.\n";
			break;
		}

		case 2:{
			cout << "Execution tracing is OFF.\n";
			break;
		}
		default:{
			cout << "Invalid input. Please enter a valid number choice.\n";
		}
		}
	}
}

// function to write the execution trace string to a new line of the log
void writeTrace(string str) {
	// only write the trace if the toggle is set to ON
	if (trace == ON) {
		ofstream traceLog;
		// open the file to append a new line to it
		traceLog.open("executionTrace.txt", ios::app);
		if (traceLog.is_open()) {
			traceLog << str << endl;
			traceLog.close();
		}
		else {
			cout << "Error: Could not open the existing execution traces.\n";
		}
	}
	else {
		return;
	}
}

// function to display the execution trace to the screen
void displayTrace() {
	e << currentDateTime() << "Maintenance is viewing the full execution trace\n";
    writeTrace(e.str());
    e.str("");
	string line;
	ifstream traceLog;
	traceLog.open("executionTrace.txt");
	if (traceLog.is_open()) {
        // skip the trace log status line (1 or 0)
		getline(traceLog, line);
        cout << endl << "Execution Traces\n" << "------------------------------------------\n"; 
        while (getline(traceLog, line)) {
			cout << line << endl;
		}
		traceLog.close();
	}
	else {
		cout << "Error: Could not open the existing execution traces.\n";
	}
}

// function to clear all trace history
void clearTraceLog() {
	e << currentDateTime() << "Maintenance is clearing the past program traces\n";
    writeTrace(e.str());
    e.str("");
	ofstream traceLog;
	traceLog.open("executionTrace.txt");
	if (traceLog.is_open()) {
		if (trace == ON) {
			traceLog << "1\n";
		}
		else {
			traceLog << "0\n";
		}
		traceLog.close();
	}
	else {
		cout << "Error: Could not open the existing execution traces.\n";
	}
}