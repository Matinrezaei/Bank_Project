#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Date {
protected:
	int Day;
	int Month;
	int Year;
	int kol;
};

class Loan :protected Date {
protected:
	int paymentNumber;
	int peyAccount, hesab;
	int LastPay, payed;
	int vaziatVam;
	long int mablagh;
};

class Bosses {
	string name, code;
public:
	void firstset(string, string);
	void write(ofstream& banks) { banks << name << "\n" << code << "\n"; }
	void Read(ifstream&);
	string getName() { return name; }
	string getCode() { return code; }
	Bosses* next;
};

class Massage {
	string Receiver;
	string Sender;
	string Text;
	int payAccount, LoanAccount;
	int vaziat, kindOfMassage;
	int KindOfAccount, num;
	int LoanPart, mablagh;
public:
	string getReceve() { return Receiver; }
	int getpayAcc() { return payAccount; }
	int getnum() { return num; }
	int getmablagh() { return mablagh; }
	int getLoanpart() { return LoanPart; }
	int getLoanAcc() { return LoanAccount; }
	int getvaziat() { return vaziat; }
	int getkind() { return kindOfMassage; }
	int getkindAcc() { return KindOfAccount; }
	void checked() { vaziat = 1; }
	void firstset(Massage*, string, int, int);
	void firstset(int, int, int, string, string, int, int, int);
	void firstset(string, string, string);
	void showMassage(int);
	void write(ofstream&);
	void Read(ifstream&);
	Massage* next;
};

class Account :protected Date {
	string AccountNumber;
	string bank;
	int kind, LastPay;
	long double Inventory;
public:
	string getAccnum() { return AccountNumber; }
	string getNB() { return bank; }
	void setLast(int last) { LastPay = last; }
	void showAccount();
	long long int getMoney() { return Inventory; }
	void updateMoney();
	void inventory(int k) { Inventory += k; }
	void firstset(Massage*);
	void write(ofstream&);
	int Read(ifstream&);
	Account* next;
};

class customers : protected Loan, protected Date {
	string Name, Password;
	string NationalCode;
	Account* Hesab;
	Massage* Massages;
	int MassageNumber;
	int vaziatCustomer;
public:
	customers() { MassageNumber = 0; vaziatCustomer = 1; }
	string getName() { return Name; }
	string ReturnAccName(int);
	int getvv() { return vaziatVam; }
	void reject() { vaziatCustomer = 0; }
	void firstset(string, string, string, int, int, int);
	void setLoan(Massage*);
	void Endvam() { vaziatVam = 0; }
	void Delete() { Massages = NULL; }
	int showAccount();
	void showLoan();
	void showMassage();
	void showmenu();
	void Mojoodi(int);
	void AddAccount(Massage*);
	void Moneytransfer(int, customers*, int, int);
	int searchAcc(string);
	void question(int);
	void AddMassage(Massage*);
	int check(string, string, int);
	void write(ofstream&);
	void Read(ifstream&);
	customers* next;
};

class Banks {
	string name;
	Bosses* Boss;
	Massage* Massages;
	int establishedyear;
public:
	string getname() { return name; };
	void firstset(string, int);
	void AddBoss(string, string);
	void showMassage(int);
	void Delete(int);
	void showmenu(int);
	void AddMassage(Massage*);
	void checkAccount(customers*);
	void checkLoan(customers*);
	int check(string, int);
	void write(ofstream&);
	void Read(ifstream&);
	Banks* next;
};