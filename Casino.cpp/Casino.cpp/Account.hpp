#include <iostream>
#include <fstream>
#include <string>

#include "Casino.hpp"

using std::ifstream;
using std::fstream;
using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::getline;
using std::ofstream;

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account : public Casino
{
public:
	Account();
	
	void setName(string name); // Set user name
	void setPassword(string password); // Set user password
	void initialBalance(double balance); // Set user's initial balance

	void verifyUser(string name, string password, int option, bool &verified); // Check user credentials to verify they are a member
	bool checkUser(string name);
	void checkPassword(string password);
	string getName();
	void verifyUser(string name);
	bool createAccount(string name,string password);
	bool loadDeposit(double deposit);
	
	~Account();

private:
	string name;
	string password;
	double balance;
	bool accountFlag;
	bool passwordFlag;
};


#endif