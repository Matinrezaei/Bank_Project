#include "Bank.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#pragma warning(disable: 4996)
using namespace std;
using  std::cout;

time_t t = time(NULL);
struct tm* tm = localtime(&t);

int findday(int d, int m, int y) {
	int month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int i;
	if (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0))
		month[1] = 29;
	for (i = 1900; i < y; i++)
		if (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0))
			d += 366;
		else
			d += 365;
	for (i = 0; i < m - 1; i++)
		d += month[i];
	return d;
}

void Bosses::firstset(string name_, string code_) {
	name = name_;
	code = code_;
	next = NULL;
}

void Bosses::Read(ifstream& banks) {
	getline(banks, name);
	getline(banks, code);
	next = NULL;
}

void Massage::write(ofstream& write) {
	write << Receiver << "\n" << Sender << "\n" << Text << "\n" << payAccount << " " << LoanAccount << " " << vaziat << " "
		<< kindOfMassage << " " << KindOfAccount << " " << num << " " << LoanPart << " " << mablagh;
}

void Massage::Read(ifstream& customer) {
	getline(customer, Receiver);
	getline(customer, Sender);
	getline(customer, Text);
	customer >> payAccount >> LoanAccount >> vaziat >> kindOfMassage >> KindOfAccount >> num >> LoanPart >> mablagh;
	next = NULL;
}

void Massage::firstset(Massage* payam, string Receve, int kind, int y) {
	Receiver = Receve;
	Sender = payam->Receiver;
	kindOfMassage = 3;
	vaziat = 0;
	next = NULL;
	if (kind == 2) {
		if (y == 1)
			Text = "Your Loan has been successfully verified on the ";
		else
			Text = "Your Loan was rejected on the ";
	}
	else {
		if (y == 1)
			Text = "Your account has been successfully verified on the ";
		else
			Text = "Your account was rejected on the ";
	}
	Text += to_string(tm->tm_year + 1900) += "/";
	Text += to_string(tm->tm_mon + 1) += "/";
	Text += to_string(tm->tm_mday);
	if (y == 1 && kind == 2) {
		Text += "    next installments money: ";
		Text += to_string(payam->mablagh / payam->LoanPart);
	}
}

void Massage::firstset(string send, string Receve, string text) {
	Sender = send;
	Receiver = Receve;
	Text = text;
	vaziat = 0;
	next = NULL;
}

void Massage::firstset(int money, int kind, int num_, string send, string Receve, int LAcc, int PAcc, int LP) {
	mablagh = money;
	KindOfAccount = kind;
	Sender = send;
	Receiver = Receve;
	num = num_;
	kindOfMassage = 1;
	vaziat = 0;
	next = NULL;
	if (kind == -1) {
		LoanAccount = LAcc;
		LoanPart = LP;
		payAccount = PAcc;
		kindOfMassage = 2;
	}
}

void Massage::showMassage(int kind) {
	if (vaziat == 0)
		cout << "Not checked   ";
	else if (vaziat == 1)
		cout << "  checked   ";
	if (kind == 0) {
		vaziat = 1;
		cout << Receiver << "     " << Sender << "      " << Text << "\n\n";
	}
	else if (kind == 2)
		cout << Receiver << "      " << Sender << "                    " << LoanPart << "                  " << mablagh << "\n\n";
	else if (kind == 1) {
		cout << Receiver << "        " << Sender << "          ";
		if (KindOfAccount == 1)
			cout << "Kootah Modat          ";
		else if (KindOfAccount == 2)
			cout << "Boland Modat          ";
		else if (KindOfAccount == 3)
			cout << "Special              ";
		cout << mablagh << "\n";
	}
}

void Account::firstset(Massage* payam) {
	srand(time(0));
	for (int i = 0; i < 16; AccountNumber += to_string(rand() % 10), i++);
	bank = payam->getReceve();
	Day = tm->tm_mday;
	Month = tm->tm_mon + 1;
	Year = tm->tm_year + 1900;
	kol = findday(Day, Month, Year);
	Inventory = payam->getmablagh();
	LastPay = kol;
	kind = payam->getkindAcc();
	next = NULL;
}

void Account::updateMoney() {
	int k1 = 0;
	if (kind == 1)
		k1 = 10;
	if (kind == 2)
		k1 = 30;
	if (kind == 3)
		k1 = 50;
	Inventory += (Inventory * k1) / 100;
}

void Account::write(ofstream& customer) {
	customer << bank << "\n" << AccountNumber << "\n" << Year << " " << Month << " " << Day << " " << Inventory << " "
		<< kind << " " << LastPay;
}

int Account::Read(ifstream& customer) {
	getline(customer, bank);
	getline(customer, AccountNumber);
	customer >> Year >> Month >> Day >> Inventory >> kind >> LastPay;
	next = NULL;
	int kol = findday(tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
	int x = kol - LastPay;
	LastPay = kol;
	return x;
}

void Account::showAccount() {
	cout << "         " << AccountNumber << "        ";
	if (kind == 1)
		cout << "Kootah Modat      ";
	else if (kind == 2)
		cout << "Boland Modat      ";
	else if (kind == 3)
		cout << "      Special      ";
	cout << bank;
}

void customers::firstset(string name, string code, string pass, int y, int m, int d) {
	Name = name;
	NationalCode = code;
	Password = pass;
	Date::Year = y;
	Date::Month = m;
	Date::Day = d;
	Massages = NULL;
	Hesab = NULL;
	vaziatVam = 1;
	vaziatCustomer = 1;
	next = NULL;
}

void customers::setLoan(Massage* payam) {
	Account* node2 = Hesab;
	for (int i = 0; i < payam->getLoanAcc(); node2 = node2->next, i++);
	node2->inventory(payam->getmablagh());
	paymentNumber = payam->getLoanpart();
	Loan::Day = tm->tm_mday;
	Loan::Month = tm->tm_mon + 1;
	Loan::Year = tm->tm_year + 1900;
	Loan::kol = findday(Loan::Day, Loan::Month, Loan::Year);
	mablagh = payam->getmablagh();
	LastPay = Loan::kol;
	hesab = payam->getLoanAcc();
	peyAccount = payam->getpayAcc();
	payed = 0;
	vaziatVam = 0;
}

void customers::AddAccount(Massage* payam) {
	Account* node = new Account;
	node->firstset(payam);
	if (Hesab == NULL)
		Hesab = node;
	else {
		Account* last = Hesab;
		for (; last->next != NULL; last = last->next);
		last->next = node;
	}
}

void customers::AddMassage(Massage* payam) {
	if (Massages == NULL)
		Massages = payam;
	else {
		Massage* last = Massages;
		for (; last->next != NULL; last = last->next);
		last->next = payam;
	}
}

int customers::showAccount() {
	if (vaziatCustomer == 0)
		cout << "                              Your accounts has been blocked.\n\n";
	else if (Hesab == NULL)
		cout << "                                  No account available\n\n";
	else {
		cout << "Row         Account Number           Kind             Bank          vaziat\n\n";
		Account* node = Hesab;
		for (int a = 1; node != NULL; node = node->next, a++) {
			cout << a << ".";
			node->showAccount();
			if (vaziatCustomer)
				cout << "    Free\n\n";
			else
				cout << "    Blocked\n\n";
		}
		return 1;
	}
	return 0;
}

void customers::showMassage() {
	cout << "                                                      Massages\n\n";
	if (Massages != NULL) {
		cout << "ROW      vaziat     Recever        Sender                                    Text\n\n";
		Massage* payam = Massages;
		for (int a = 1; payam != NULL; cout << a << ".      ", payam->showMassage(0), payam = payam->next, a++);
	}
	else
		cout << "  No Massage";
}

void customers::showmenu() {
	int p = 0;
	for (Massage* node3 = Massages; node3 != NULL; node3 = node3->next) {
		if (node3->getvaziat() == 0)
			p++;
	}
	cout << "\n\n  " << Name << "    " << Date::Year << "/" << Date::Month << "/" << Date::Day << "\n\n";
	cout << "  1.Money transfer\n\n  2.Inventory\n\n  3.Create Account\n\n";
	cout << "  4.Apply for a loan\n\n  5.Massages(" << p << ")\n\n  6.lock\n\n  0.exit\n\n";
}

void customers::question(int num) {
	Account* node = Hesab;
	for (int i = 0; i < num; node = node->next, i++);
	cout << "                 " << Name << "       " << node->getNB() << "\n\n";
}

int customers::searchAcc(string account) {
	Account* node = Hesab;
	for (int i = 0; node != NULL; node = node->next, i++)
		if (account == node->getAccnum())
			return i;
	return -1;
}

void customers::Moneytransfer(int num1, customers* maghsad, int num2, int money) {
	Account* node1 = Hesab;
	for (int m = 0; m < num1; node1 = node1->next, m++);
	Account* node = maghsad->Hesab;
	for (int m = 0; m < num2; node = node->next, m++);
	if (node1->getMoney() >= money) {
		node->inventory(money);
		node1->inventory(money * -1);
		cout << "                  mission accomplished\n\n";
	}
	else
		cout << "                 Your account balance is not enough\n\n";
}

void customers::write(ofstream& customer) {
	customer << Name << "\n" << Password << "\n" << NationalCode << "\n" << Date::Year << " " << Date::Month << " "
		<< Date::Day << " " << vaziatCustomer << " " << Loan::Year << " " << Loan::Month << " " << Loan::Day << " "
		<< Loan::kol << " " << paymentNumber << " " << peyAccount << " " << hesab << " " << LastPay << " " << payed << " "
		<< vaziatVam << " " << mablagh << "\n";
	int j = 0;
	for (Massage* last = Massages; last != NULL; last = last->next, j++);
	for (customer << j, j = 0; Massages != NULL; Massages->write(customer), Massages = Massages->next);
	for (Account* last = Hesab; last != NULL; last = last->next, j++);
	for (customer << '\n' << j; Hesab != NULL; Hesab->write(customer), Hesab = Hesab->next);
}

void customers::Read(ifstream& customer) {
	int x;
	getline(customer, Name);
	getline(customer, Password);
	getline(customer, NationalCode);
	customer >> Date::Year >> Date::Month >> Date::Day >> vaziatCustomer >> Loan::Year >> Loan::Month >> Loan::Day >> Loan::kol
		>> paymentNumber >> peyAccount >> hesab >> LastPay >> payed >> vaziatVam >> mablagh >> x;
	if (x == 0)
		Massages = NULL;
	else {
		Massage* last2 = Massages;
		for (int j = 0; j < x; j++) {
			Massage* node2 = new Massage;
			node2->Read(customer);
			if (j == 0) {
				Massages = node2;
				last2 = Massages;
			}
			else {
				last2->next = node2;
				last2 = last2->next;
			}
		}
	}
	customer >> x;
	if (x == 0)
		Hesab = NULL;
	else {
		Account* last1 = Hesab;
		for (int j = 0; j < x; j++) {
			Account* node1 = new Account;
			int p = node1->Read(customer);
			for (int j = 0; j < p; j++) {
				node1->updateMoney();
				Massage* node = new Massage;
				string Text = "Your account balance New deposit: ";
				Text += to_string(node1->getMoney());
				node->firstset(node1->getNB(), Name, Text);
				AddMassage(node);
			}
			if (j == 0) {
				Hesab = node1;
				last1 = Hesab;
			}
			else {
				last1->next = node1;
				last1 = last1->next;
			}
		}
	}
	if (vaziatVam == 0) {
		int kol = findday(tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
		int x = kol - LastPay;
		for (; x >= 30; LastPay += 30, x -= 30) {
			string Text;
			Massage* node = new Massage;
			Account* node1 = Hesab;
			for (int j = 0; j < peyAccount; node1 = node1->next, j++);
			int ghest = mablagh / paymentNumber;
			if (payed == paymentNumber - 1)
				ghest += mablagh % paymentNumber;
			if (node1->getMoney() > ghest) {
				node1->inventory(ghest * -1);
				payed++;
				if (payed == paymentNumber) {
					Text = "The last installment of your loan was deducted from your account ";
					vaziatVam = 1;
				}
				else {
					Text += to_string(payed) += "/";
					Text += to_string(paymentNumber);
					Text += " installment of your loan was deducted from your account ";
					Text += "   next installments money: ";
					Text += to_string(ghest);
				}
			}
			else {
				Text += "Your account balance was not enough to pay your loan installment and your accounts were blocked";
				vaziatCustomer = 0;
			}
			node->firstset(node1->getNB(), Name, Text);
			AddMassage(node);
		}
	}
}

void customers::showLoan() {
	cout << "    Date began:  " << Loan::Year << "/" << Loan::Month << "/" << Loan::Day << "\n\n" << "    Money: " << mablagh << "\n\n"
		<< "    parts(payed): " << paymentNumber << "(" << payed << ")\n\n";
	Account* node = Hesab;
	for (int i = 0; i < hesab; node = node->next, i++);
	cout << "    Hesab vam:";
	node->showAccount();
	node = Hesab;
	for (int i = 0; i < peyAccount; node = node->next, i++);
	cout << "    Hesab pay:    ";
	node->showAccount();
}

string customers::ReturnAccName(int num) {
	Account* node = Hesab;
	for (int i = 0; i < num; node = node->next, i++);
	return node->getNB();
}

void customers::Mojoodi(int num) {
	Account* node = Hesab;
	for (int i = 0; i < num; node = node->next, i++);
	cout << "\n\n               Mojoodi Hesab shome: " << node->getMoney() << "\n\n";
}

int customers::check(string code, string pass, int kind) {
	if (NationalCode == code) {
		if (kind)
			return 1;
		else if (Password == pass)
			return 1;
	}
	return 0;
}

void Banks::firstset(string name_, int year) {
	establishedyear = year;
	name = name_;
	Massages = NULL;
	Boss = NULL;
	next = NULL;
}

void Banks::AddBoss(string name_, string code) {
	Bosses* node = new Bosses;
	node->firstset(name_, code);
	if (Boss == NULL)
		Boss = node;
	else {
		for (node = Boss; node->next != NULL; node = node->next);
		node->next = node;
	}
}

void Banks::AddMassage(Massage* payam) {
	if (Massages == NULL)
		Massages = payam;
	else {
		Massage* last = Massages;
		for (; last->next != NULL; last = last->next);
		last->next = payam;
	}
}

int Banks::check(string code, int kind) {
	Bosses* node = Boss;
	for (int j = 0; node != NULL; node = node->next, j++) {
		if (node->getCode() == code && kind == 1)
			return j;
		if (node->getName() == code && kind == 2)
			return j;
	}
	return -1;
}

void Banks::showmenu(int num) {
	Bosses* node2 = Boss;
	for (int i = 0; i < num; node2 = node2->next, i++);
	int kind1 = 0, kind2 = 0;
	for (Massage* node3 = Massages; node3 != NULL; node3 = node3->next) {
		if (node3->getkind() == 1 && node3->getvaziat() == 0)
			kind1++;
		if (node3->getkind() == 2 && node3->getvaziat() == 0)
			kind2++;
	}
	cout << "\n\n  " << name << "    Bank: " << name << "\n\n";
	cout << "  1.account verification(" << kind1 << ")\n\n  2.Loan review("
		<< kind2 << ")\n\n  3.lock\n\n  0.exit\n\n";
}

void Banks::showMassage(int kind) {
	cout << "                                                               Massages\n\n";
	int a = 0;
	for (Massage* payam = Massages; payam != NULL; payam = payam->next)
		if (payam->getkind() == kind) {
			a++;
			break;
		}
	if (a) {
		if (kind == 1)
			cout << "ROW       vaziat        Recever          Sender         Kind of Account      Mablagh Avalie\n\n";
		else
			cout << "ROW       vaziat     Recever          Sender         number of installment      Mablagh vam\n\n";
		for (Massage* payam = Massages; payam != NULL; payam = payam->next) {
			if (payam->getkind() == kind) {
				cout << a << ".     ";
				a++;
				payam->showMassage(kind);
			}
		}
	}
	else
		cout << "  No Massage\n\n";
}

void Banks::write(ofstream& banks) {
	banks << name << "\n" << establishedyear << "\n";
	int j = 0;
	for (Bosses* last = Boss; last != NULL; last = last->next, j++);
	for (banks << j; Boss != NULL; Boss->write(banks), Boss = Boss->next);
	if (j == 0)
		banks << "\n";
	j = 0;
	for (Massage* last = Massages; last != NULL; last = last->next, j++);
	for (banks << j; Massages != NULL; Massages->write(banks), Massages = Massages->next);
}

void Banks::Read(ifstream& banks) {
	int x;
	getline(banks, name);
	banks >> establishedyear >> x;
	if (x == 0)
		Boss = NULL;
	else {
		Bosses* last1 = Boss;
		for (int j = 0; j < x; j++) {
			Bosses* node1 = new Bosses;
			node1->Read(banks);
			if (j == 0) {
				Boss = node1;
				last1 = Boss;
			}
			else {
				last1->next = node1;
				last1 = last1->next;
			}
		}
	}
	banks >> x;
	if (x == 0)
		Massages = NULL;
	else {
		Massage* last2 = Massages;
		for (int j = 0; j < x; j++) {
			Massage* node2 = new Massage;
			node2->Read(banks);
			if (j == 0) {
				Massages = node2;
				last2 = Massages;
			}
			else {
				last2->next = node2;
				last2 = last2->next;
			}
		}
	}
}

void Banks::Delete(int k) {
	for (; Massages->getvaziat() == 1 && Massages->getkind() == k; Massages = Massages->next)
		if (Massages->next == NULL) {
			Massages = Massages->next;
			break;
		}
	Massage* last = Massages;
	Massage* node = new Massage;
	Massage* prev = new Massage;
	for (node = last; last != NULL; last = last->next) {
		if (1 == last->getvaziat() && last->getkind() == k) {
			prev->next = node->next;
			node = last->next;
			continue;
		}
		node = last->next;
		prev = last;
	}
	cout << "                              Deleted";
	Sleep(3000);
}

void Banks::checkAccount(customers* moshtary) {
	cout << "    Enter number of Massage: ";
	int i;
	cin >> i;
	char x = getchar();
	Massage* node = Massages;
	if (node->getkind() != 1)
		for (; node->getkind() != 1; node = node->next);
	for (int j = 0; j < i - 1; node = node->next) {
		if (node == NULL) {
			cout << "                                  out of range";
			Sleep(3000);
			return;
		}
		if (node->getkind() == 1)
			j++;
	}
	if (node->getvaziat())
		cout << "\n\n                              Already checked\n\n";
	else {
		node->checked();
		cout << "    1.Agree    2.Disagree: ";
		int y;
		cin >> y;
		char x = getchar();
		fputs("\033[A\033[2K", stdout);
		rewind(stdout);
		customers* node2 = moshtary;
		for (int i = 0; i < node->getnum(); node2 = node2->next, i++);
		Massage* node1 = new Massage;
		node1->firstset(node, node2->getName(), 1, y);
		node2->AddMassage(node1);
		if (y == 1)
			node2->AddAccount(node);
		cout << "\n\n                                   checked";
	}
	Sleep(3000);
}

void Banks::checkLoan(customers* moshtary) {
	cout << "    Enter number of Massage: ";
	int i;
	cin >> i;
	char x = getchar();
	Massage* node = Massages;
	if (node->getkind() != 2)
		for (; node->getkind() != 2; node = node->next);
	for (int j = 0; j < i - 1; node = node->next) {
		if (node == NULL) {
			cout << "                                  out of range";
			Sleep(3000);
			return;
		}
		if (node->getkind() == 2)
			j++;
	}
	if (node->getvaziat())
		cout << "\n\n                              Already checked\n\n";
	else {
		node->checked();
		cout << "    1.Agree    2.Disagree: ";
		int y;
		cin >> y;
		char x = getchar();
		fputs("\033[A\033[2K", stdout);
		rewind(stdout);
		customers* node2 = moshtary;
		for (int i = 0; i < node->getnum(); node2 = node2->next, i++);
		Massage* node1 = new Massage;
		node1->firstset(node, node2->getName(), 2, y);
		node2->AddMassage(node1);
		if (y == 1)
			node2->setLoan(node);
		cout << "\n\n                                   checked";
	}
	Sleep(3000);
}