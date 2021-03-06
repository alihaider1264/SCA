#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct account {
	string fName, lName, streetName, streetNumber, city, state, userID, zip;
	double balChecking, balSaving;
	int custline;
} user, search; //Struct for all account variables

//functions are somewhat all over the place, but reorganizing them might break things so I'm not going to out of fear

void initializeUser(string &login)			//Writes info from file into struct after logging in
{
	ifstream accounts;
	accounts.open("customers.txt");
	int currentline = 0;
	while (!accounts.eof())
	{
		getline(accounts, user.userID, ' ');//Reads up to the first space to find user ID
		if (login == user.userID)			//Compares what it read to user input. If true, initializes user struct
		{
			user.custline = currentline;
			getline(accounts, user.fName, ' ');								//All this stuff initializes the user struct
			getline(accounts, user.lName, ' ');
			getline(accounts, user.streetNumber, ' ');
			getline(accounts, user.streetName, ' ');
			getline(accounts, user.city, ' ');
			getline(accounts, user.zip, ' ');
			getline(accounts, user.state, ' ');
			accounts >> user.balChecking >> user.balSaving;
		}
		else {
			currentline++;
			accounts.ignore(numeric_limits<streamsize>::max(), '\n');	//Skips to the next line for next loop
		}

	}
	user.userID = login;
}

void searchUser(string &login, bool &found)			//Finds a user and writes all info into a struct
{
	ifstream accounts;
	accounts.open("customers.txt");
	int currentline = 0;
	cout << "Enter the 4 digit ID of the user you would like to search for." << endl;
	cin >> login;
	while (!accounts.eof())
	{
		getline(accounts, search.userID, ' ');//Reads up to the first space to find user ID
		if (login == search.userID)			//Compares what it read to user input. If true, initializes search struct
		{
			search.custline = currentline;
			getline(accounts, search.fName, ' ');								//All this stuff initializes the search struct
			getline(accounts, search.lName, ' ');
			getline(accounts, search.streetNumber, ' ');
			getline(accounts, search.streetName, ' ');
			getline(accounts, search.city, ' ');
			getline(accounts, search.zip, ' ');
			getline(accounts, search.state, ' ');
			accounts >> search.balChecking >> search.balSaving;
			found = true;
		}
		else {
			currentline++;
			accounts.ignore(numeric_limits<streamsize>::max(), '\n');	//Skips to the next line for next loop
		}

	}
	if (found == true)
		search.userID = login;
}

void writeFile()
{
	fstream accounts("customers.txt");
	ofstream nAccounts;
	fstream newAccounts("tempfile.txt");
	string line;
	for (int i = 0; i < user.custline; i++) //Writes line-by-line until custline into a temp file from the original customer file
	{
		getline(accounts, line, '\n');
		newAccounts << line << '\n';
	}
	newAccounts << user.userID << " " << user.fName << " " << user.lName << " " << user.streetNumber << " "		//Stops at the line the user's info would have been and writes the new info
		<< user.streetName << " " << user.city << " " << user.zip << " " << user.state << " " << user.balChecking << " " << user.balSaving << '\n';
	accounts.ignore(numeric_limits<streamsize>::max(), '\n');
	while (!accounts.eof())				//Continues writing the rest of the file
	{
		getline(accounts, line, '\n');
		if (line.empty())
			;
		else
			newAccounts << line << '\n';
	}
	newAccounts.seekg(0);
	accounts.close();
	nAccounts.open("customers.txt", ofstream::out | ofstream::trunc);  //This and the next line clear customers.txt
	nAccounts.close();
	nAccounts.open("customers.txt");
	for (int i = 0; !newAccounts.eof(); i++)		//Writes content of the tempfile to customers.txt
	{
		getline(newAccounts, line, '\n');
		if (line.empty())
			;
		else {
			nAccounts << line << '\n';
		}
	}
	ofstream temp; //Clears temporary file
	temp.open("tempfile.txt", ofstream::out | ofstream::trunc);
	temp.close();
}

bool logIn(string &login, bool found)		//Compares user login to customers.txt to find if it's a valid login
{
	fstream accounts;
	accounts.open("customers.txt");
	while (!accounts.eof())
	{
		getline(accounts, user.userID, ' ');//Reads up to the first space to find user ID
		if (login == user.userID)			//Compares what it read to user input
		{
			found = true;
			accounts.close();
			return true;					//Returns true
		}
		else
			accounts.ignore(numeric_limits<streamsize>::max(), '\n');	//Skips to the next line for next loop

	}
	if (!found) {								//Returns false if it couldn't find a matching ID
		accounts.close();
		return false;
	}
	return false;
}

void dsavings();
void dchecking();
void wsavings();
void wchecking();
void getinfo();
void deleteAccount();
void withdraw();
void deposit();
void transfer();
void transactionHistory();
void clearHistory();

int main()
{
	int choice;
	string login;
	int i = 0;
	bool found = false;

	cout << "****** Welcome to C++ bank! ******" << endl;
	cout << "Are you a new or returning user?" << endl << "1. New" << endl << "2. Returning" << endl;
	cin >> choice;								//Choose between New or Returning
	cout << endl;
	while (choice != 1 && choice != 2 && i <= 3) //If they choose neither
	{
		cout << "Invalid input, try again. " << 3 - i << " attempt(s) left." << endl;
		i++;
		cin >> choice;
	}
	if (choice == 1)							//If they choose New, prompts them to create a new account
		getinfo();

	i = 0;										//After creating account OR selecting returning, will prompt login
	do {
		cout << "Enter your 4-digit user ID: ";
		cin >> login;							//Enter login ID
		cout << endl;
		found = logIn(login, found);			//Compares input with existing accounts, returns true if matched and false if it doesn't exist
		if (found == true)
			cout << "Successfully logged in as " << login << "." << endl;
		else {
			i++;
			cout << "Failed to log in, " << 3 - i << " attempt(s) remaining." << endl;
			if (i == 3)
				return 0;						//Exits program if failed 3 attempts
		}
	} while (i < 3 && found == false);

	initializeUser(login);						//Writes in data to user struct from customers.txt

	do {										//Menu displaying options, chosen by user
		cout << "****Welcome " << user.fName << " " << user.lName << "!****" << endl;
		cout << "Please choose a service from the list below" << endl;
		cout << "1: Create a new account" << endl;
		cout << "2: Withdraw from an existing account" << endl;
		cout << "3: Deposit into an existing account" << endl;
		cout << "4: Display account information" << endl;
		cout << "5: Display transaction history" << endl;
		cout << "6: Delete account" << endl;
		cout << "7: Search for account information" << endl;
		cout << "8: Transfer funds" << endl;
		cout << "9: Complete transaction" << endl;

		cin >> choice;

		switch (choice) {
		case 1: {
			cout << "Creating a new account will log you out. Continue?" << endl << "1. Yes" << "2. No" << endl;
			cin >> choice;
			if (choice == 1) {
				transactionHistory();
				clearHistory();
				writeFile();	//Saves all changes before logging into the new user
				getinfo();		//Creates a new account
			}
			cout << "Enter 1 to return to menu." << endl;
			cin >> choice;
			break; }
		case 2: {
			withdraw();		//Withdraws money from checkings or savings
			cout << "Enter 1 to return to menu." << endl;
			cin >> choice;
			break; }
		case 3: {
			deposit();		//Deposits money into checkings or savings
			cout << "Enter 1 to return to menu." << endl;
			cin >> choice;
			break; }
		case 4: {			//Outputs current user's information
			cout << user.userID << " " << user.fName << " " << user.lName << " " << user.streetNumber << " " << user.streetName
				<< " " << user.city << " " << user.zip << " " << user.state << endl << "Checking balance: $" << user.balChecking << " Savings balance: $" << user.balSaving << endl;
			cout << "Enter 1 to return to menu." << endl;
			cin >> choice;
			break; }
		case 5: {
			transactionHistory(); //Lists all transactions made during current session
			cout << "Enter 1 to return to menu." << endl;
			cin >> choice;
			break; }
		case 6: {
			cout << "Are you certain you want to delete your account? Type your user ID to confirm: ";
			cin >> login;
			if (login == user.userID) {
				deleteAccount();			//Deletes current user's account
				cout << "Successfuly deleted account.";
				clearHistory();
				return 0;
			}
			else {
				cout << "Enter 1 to return to menu." << endl;
				cin >> choice;
				break;
			}
		}
		case 7: {
			searchUser(login, found);	//Searches for a user by ID and displays their information
			if (found == true)
				cout << search.userID << " " << search.fName << " " << search.lName << " " << search.streetNumber << " " << search.streetName
				<< " " << search.city << " " << search.zip << " " << search.state << endl << "Checking balance: $" << search.balChecking << " Savings balance: $" << search.balSaving << endl;
			else
				cout << "User not found." << endl;
			cout << "Enter 1 to return to menu." << endl;
			cin >> choice;
			break; }
		case 8: {
			transfer();
			cout << "Enter 1 to return to menu." << endl;
			cin >> choice;
			break; }
		case 9: {
			transactionHistory();
			clearHistory();
			writeFile();
			return 0; }
		default: {
			cout << "Invalid option." << endl;
			cout << "Enter 1 to return to menu." << endl;
			cin >> choice;
			break; }
		}

	} while (choice != 9);
	return 0;
}

void getinfo()			//Creates an account from user input
{
	ofstream outputf("customers.txt", ofstream::app);
	string login;
	bool found = false;

	cout << "Enter your first name: " << endl;
	cin >> user.fName;
	cout << "Enter your last name: " << endl;
	cin >> user.lName;
	cout << "Enter your house address number: " << endl;
	cin >> user.streetNumber;
	cout << "Enter your street name: " << endl;
	cin >> user.streetName;
	cout << "Enter your City: " << endl;
	cin >> user.city;
	cout << "Enter your State initials: " << endl;
	cin >> user.state;
	cout << "Enter your zip code: " << endl;
	cin >> user.zip;
	do {
		cout << "Create a 4-digit ID number that you will use to log in: " << endl;
		cin >> login;
		if (logIn(login, found) == true) {							//Checks if the ID is already taken and loops until user chooses a different one.
			cout << "User ID already taken." << endl;
			found = true;
		}
		else {
			user.userID = login;
			found = false;
		}
	} while (found == true);
	user.balChecking = 0;
	user.balSaving = 0;
	outputf << user.userID << " " << user.fName << " " << user.lName << " " << user.streetNumber << " " << user.streetName << " "
		<< user.city << " " << user.state << " " << user.zip << " " << user.balChecking << " " << user.balSaving << '\n'; // Writes all info into new line in customers.txt
	outputf.close();
	cout << "Login is " << login << endl;
	initializeUser(login);
	cout << "Succesfully created account under user ID " << user.userID << endl;

}

void withdraw()
{
	int choice;

	cout << "Choose an account." << endl;
	cout << "1: Savings" << endl;
	cout << "2: Checkings" << endl;
	cin >> choice;
	if (choice != 1 && choice != 2)
	{
		cout << "That is not a valid option, try again ";
		withdraw();
	}

	switch (choice)
	{
	case 1:
	{
		wsavings(); //Calls savings withdraw function
		break;
	}
	case 2:
	{
		wchecking(); //Calls checking withdraw function
		break;
	}
	}
}

void deposit()
{
	int choice;

	cout << "Choose an account." << endl;
	cout << "1: Savings" << endl;
	cout << "2: Checkings" << endl;
	cin >> choice;

	if (choice != 1 && choice != 2)
	{
		cout << "That is not a valid option, try again ";
		deposit();
	}
	switch (choice)
	{
	case 1:
	{
		dsavings(); //Calls savings deposit function
		break;
	}
	case 2:
	{
		dchecking(); //Calls checking deposit function
		break;
	}
	}
}

void transactionHistory() //Reads transaction history from current session out from "transactions.txt", which is written to at the end of deposit, withdraw, and transfer
{
	ifstream inFile("transactions.txt");
	string line;
	cout << "Transactions completed during this session: " << endl;
	while (!inFile.eof())
	{
		getline(inFile, line, '\n');
		cout << line << endl;
	}
}

void clearHistory()		//Clears "transactions.txt" for the next run
{
	ofstream clear("transactions.txt", ofstream::out | ofstream::trunc);
	clear.close();
}

void dsavings()
{
	double cashin, previous = 0;
	previous = user.balSaving;
	cout << "Your savings balance is: $" << user.balSaving << endl;
	cout << "How much would you like to deposit? $";
	cin >> cashin;
	user.balSaving = user.balSaving + cashin;
	cout << "Your new savings balance is: $" << user.balSaving << endl;
	ofstream inFile;			//Writes to "transactions.txt" a record of what happened
	inFile.open("transactions.txt", ofstream::app);
	inFile << user.fName << " " << user.lName << " deposited $" << cashin << " into savings." << endl;
	inFile.close();
}

void dchecking()
{
	double cashin, previous = 0;
	previous = user.balChecking;
	cout << "Your checkings balance is: $" << user.balChecking << endl;
	cout << "How much would you like to deposit? $";
	cin >> cashin;
	user.balChecking = user.balChecking + cashin;
	cout << "Your new checkings balance is $" << user.balChecking << endl;
	ofstream inFile;			//Writes to "transactions.txt" a record of what happened
	inFile.open("transactions.txt", ofstream::app);
	inFile << user.fName << " " << user.lName << " deposited $" << cashin << " into checkings." << endl;
	inFile.close();
}

void wsavings()
{
	double cashout, previous = 0;
	previous = user.balSaving;
	cout << "Your savings balance is: $" << user.balSaving << endl;
	cout << "How much would you like to withdraw? $";
	cin >> cashout;
	if (cashout > user.balSaving)
	{
		cout << "You do not have enough money in your savings account to withdraw $" << cashout << endl;
		wsavings();
	}
	else if (cashout <= user.balSaving)
	{
		user.balSaving = user.balSaving - cashout;
		cout << "Your new savings balance is: $" << user.balSaving << endl;
		ofstream inFile;
		inFile.open("transactions.txt", ofstream::app);
		inFile << user.fName << " " << user.lName << " withdrew $" << cashout << " from savings." << endl;
		inFile.close();			//Writes to "transactions.txt" a record of what happened
	}
}

void wchecking()
{
	double cashout, previous = 0;
	cout << "Your checkings balance is: $" << user.balChecking << endl;
	cout << "How much would you like to withdraw? $";
	cin >> cashout;
	if (cashout > user.balChecking)
	{
		cout << "You do not have enough money in your checking account to withdraw $" << cashout << endl;
		wchecking();
	}
	else if (cashout <= user.balChecking)
	{
		user.balChecking = user.balChecking - cashout;
		cout << "Your new checkings balance is: $" << user.balChecking << endl;
		ofstream inFile;			//Writes to "transactions.txt" a record of what happened
		inFile.open("transactions.txt", ofstream::app);
		inFile << user.fName << " " << user.lName << " withdrew $" << cashout << " from checkings." << endl;
		inFile.close();
	}
}

void transfer()
{
	double cash;
	int choice;
	cout << "Would you like to transfer from checkings to savings, or savings to checkings?" << endl;
	cout << "1. Checkings to savings." << endl;
	cout << "2. Savings to checkings." << endl;
	cout << "3. Exit" << endl;
	cin >> choice;
	if (choice == 1) {
		cout << "Your checkings balance is $" << user.balChecking << " and your savings balance is $" << user.balSaving << endl;
		cout << "How much would yo like to transfer? $";
		cin >> cash;
		if (user.balChecking - cash >= 0) {
			user.balChecking = user.balChecking - cash;
			user.balSaving = user.balSaving + cash;
			cout << "Transfered $" << cash << " from checkings to savings." << endl;
			cout << "Your checkings balance is now $" << user.balChecking << " and your savings balance is now $" << user.balSaving << endl;
			ofstream inFile;			//Writes to "transactions.txt" a record of what happened
			inFile.open("transactions.txt", ofstream::app);
			inFile << user.fName << " " << user.lName << " transferred $" << cash << " from checkings to savings." << endl;
			inFile.close();
		}
		else
			cout << "Insufficient funds." << endl;
	}
	else if (choice == 2) {
		cout << "Your checkings balance is $" << user.balChecking << " and your savings balance is $" << user.balSaving << endl;
		cout << "How much would yo like to transfer? $";
		cin >> cash;
		if (user.balSaving - cash >= 0) {
			user.balChecking = user.balChecking + cash;
			user.balSaving = user.balSaving - cash;
			cout << "Transfered $" << cash << " from savings to checkings." << endl;
			cout << "Your checkings balance is now $" << user.balChecking << " and your savings balance is now $" << user.balSaving << endl;
			ofstream inFile;			//Writes to "transactions.txt" a record of what happened
			inFile.open("transactions.txt", ofstream::app);
			inFile << user.fName << " " << user.lName << " transferred $" << cash << " from savings to checkings." << endl;
			inFile.close();
		}
		else
			cout << "Insufficient funds." << endl;
	}
}

void deleteAccount()		//Exactly what it sounds like. Works similarly to writeFile, except it skips over the user line and writes the rest of the file
{
	ifstream accounts("customers.txt");
	ofstream newAccounts;
	fstream deleteAccount("tempfile.txt");
	string line;
	for (int i = 0; i < user.custline; i++)
	{
		getline(accounts, line, '\n');
		if (i == 0)
			deleteAccount << line;
		else
			deleteAccount << '\n' << line;
	}
	accounts.ignore(numeric_limits<streamsize>::max(), '\n');
	while (!accounts.eof())
	{
		getline(accounts, line, '\n');
		deleteAccount << '\n' << line;
	}
	deleteAccount.seekg(0);
	accounts.close();
	newAccounts.open("customers.txt", ofstream::out | ofstream::trunc); //Clears customers.txt so that tempfile can overwrite it
	newAccounts.close();
	newAccounts.open("customers.txt");
	for (int i = 0; !deleteAccount.eof(); i++)
	{
		getline(deleteAccount, line, '\n');
		if (line.empty() && i == 0)
		{
			getline(deleteAccount, line, '\n');
			newAccounts << line << '\n';
		}
		else if (line.empty())
			;
		else
			newAccounts << line << '\n';
	}
	ofstream temp; //Clears temporary file
	temp.open("tempfile.txt", ofstream::out | ofstream::trunc);
	temp.close();
}