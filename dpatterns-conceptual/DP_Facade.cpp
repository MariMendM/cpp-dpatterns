//============================================================================
// Name        : DP_Facade.cpp
// Author      : Mariane
// Version     :
// Copyright   : Your copyright notice
// Description : Facade Design Pattern in C++, Ansi-style
//============================================================================
//- When you create a simplified interface that performs many other actions
//  behind the scenes
//- Example: withdrawal R$50 from the bank:
//-- Account is valid?
//-- Secure code is valid?
//-- Funds are available?
//-- OK, then we go!
//============================================================================

#include <iostream>
using namespace std;

class WelcomeToBank{
	public:
		WelcomeToBank () {cout << "Welcome! Show me your money and let's go!" << endl;}
};
class AccountNumberCheck{
	private:
		int accountNumber = 12345678;
	public:
		int getAccountNumber() { return accountNumber; }
		//void setAccountNumber (int accNbr) { accountNumber = accNbr; }
		bool accountValid (int accNbr) { return (accNbr == accountNumber); }
};
class SecurityCodeCheck {
	private:
		string secCode = "password";
	public:
		string getSecurityCode() { return secCode; }
		//void setSecurityCode (string pwd) { secCode = pwd; }
		bool securityCodeValid (string pwd) { return (pwd == secCode); }
};
class FundsCheck {
	private:
		double cashStored = 90.00;
	public:
		int getFunds() { return cashStored; }
		//void setFunds (double cash) { cashStored = cash; }
		void decreaseCash (double cashWithdrw) { cashStored -= cashWithdrw; }
		void increaseCash (double cashDeposit) { cashStored += cashDeposit; }
		bool haveFunds (double cashWithdrw) { return (cashStored >= cashWithdrw); }
};

class BankAccountFacade {
	private:
		int accountNumber;
		string securityCode;
		WelcomeToBank *bank = new WelcomeToBank();
		AccountNumberCheck *accNbr = new AccountNumberCheck();
		SecurityCodeCheck *secCode = new SecurityCodeCheck();
		FundsCheck *funds = new FundsCheck();

	public:
		BankAccountFacade(int accNbr, string pwd) : accountNumber(accNbr), securityCode(pwd) {}
		~BankAccountFacade () { delete bank; delete accNbr; delete secCode; delete funds; }
		bool withdrawCash(double cashQtd) {
			if (! accNbr->accountValid(accountNumber)) {
				cout << "\tAccount invalid!" << endl;
				return false;
			}
			if (! secCode->securityCodeValid(securityCode)) {
				cout << "\tSecurity Code invalid!" << endl;
				return false;
			}
			if (! funds->haveFunds(cashQtd)) {
				cout << "\tNot enough funds! You have " << funds->getFunds() << endl;
				return false;
			}
			funds->decreaseCash(cashQtd);
			cout << "\tRemaining funds = " << funds->getFunds() << endl;
			return true;
		}
		bool depositCash(double cashQtd) {
			if (! accNbr->accountValid(accountNumber)) {
				cout << "\tAccount invalid!" << endl;
				return false;
			}
			if (! secCode->securityCodeValid(securityCode)) {
				cout << "\tSecurity Code invalid!" << endl;
				return false;
			}
			funds->increaseCash(cashQtd);
			cout << "\tNew funds = " << funds->getFunds() << endl;
			return true;
		}
};

int main() {

	//cind << accountNumber;
	int accountNumber = 12345678;
	//cin << pwd;
	string pwd = "password"; //Oh my god! Never!

	BankAccountFacade *acessBank = new BankAccountFacade(accountNumber, pwd);
	cout << "\nWithdrawing 50:" << endl;
	if (acessBank->withdrawCash(50.00))
		cout << "Transaction completed!" << endl;

	cout << "\nWithdrawing 50:" << endl;
	if (acessBank->withdrawCash(50.00))
		cout << "Transaction completed!" << endl;

	cout << "\nDepositing 100:" << endl;
	if (acessBank->depositCash(100.00))
		cout << "Transaction completed!" << endl;

	cout << "END OF PROGRAM" << endl; // prints END OF PROGRAM
	return 0;
}
