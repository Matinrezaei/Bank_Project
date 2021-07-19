#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include "Bank.h"
#pragma warning(disable: 4996)
using namespace std;
using  std::cout;
using  std::cin;

void wellcome(Banks&, customers&);

void menu2(Banks*, customers*, int, int);

void menu(Banks&, customers*, int);

void menu3(Banks*, customers*);

void Massage1(Banks*, customers*, int, int);

void Massage2(Banks*, customers*, int, int);

inline void setFontSize(int a, int b) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = a;
	lpConsoleCurrentFontEx->dwFontSize.Y = b;
	SetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);

}

int listOfBanks(Banks* bank) {
	system("cls");
	setFontSize(25, 25);
	cout << "                            List of Banks\n\n";
	Banks* node = bank;
	if (node == NULL)
		return -1;
	for (int a = 1; node != NULL; node = node->next, a++)
		cout << a << ". " << node->getname() << "\n\n";
	cout << "\n\n       Enter The number of Bank: ";
	int i;
	cin >> i;
	char x = getchar();
	return i;
}

void Exit(Banks* bank, customers* moshtary) {
	ofstream banks, customer;
	banks.open("banks.txt", ios::trunc);
	customer.open("customers.txt", ios::trunc);
	int j = 0;
	for (Banks* node = bank; node != NULL; node = node->next, j++);
	for (banks << j, j = 0; bank != NULL; bank->write(banks), bank = bank->next);
	for (customers* node = moshtary; node != NULL; node = node->next, j++);
	for (customer << j; moshtary != NULL; moshtary->write(customer), moshtary = moshtary->next);
	banks.close();
	customer.close();
	exit(0);
}

void Moneytransfer(Banks& bank, customers* moshtary, int num) {
	system("cls");
	setFontSize(25, 25);
	customers* node = moshtary;
	for (int i = 0; i < num; node = node->next, i++);
	if (node->showAccount()) {
		int number;
		cin >> number;
		char x = getchar();
		fputs("\033[A\033[2K", stdout);
		rewind(stdout);
		cout << "\n\n                 Enter the Destination account number:\n\n                       ";
		string account;
		cin >> account;
		getchar();
		customers* node1 = moshtary;
		int i = 0, a = 0, j = 0;
		for (i = 0; node1 != NULL; node1 = node1->next, i++) {
			j = node1->searchAcc(account);
			if (j != -1) {
				a++;
				break;
			}
		}
		if (a) {
			node1->question(j + 1);
			cout << "Is That True? 1.Yes  2.No";
			cin >> a;
			fputs("\033[A\033[2K", stdout);
			rewind(stdout);
			if (a == 1) {
				cout << "                 Enter the Money: ";
				int mablagh;
				cin >> mablagh;
				char x = getchar();
				node->Moneytransfer(number - 1, node1, j + 1, mablagh);
			}
		}
		else
			cout << "          Not found\n\n";
	}
	cout << "  1.again\n  2.Menu";
	char x = getch();
	if (x == '1')
		Moneytransfer(bank, moshtary, num);
	else
		menu(bank, moshtary, num);
}

void Mojoodi(Banks& bank, customers* moshtary, int num) {
	system("cls");
	setFontSize(25, 25);
	customers* node = moshtary;
	for (int i = 0; i < num; node = node->next, i++);
	if (node->showAccount()) {
		int number;
		cin >> number;
		char x = getchar();
		fputs("\033[A\033[2K", stdout);
		rewind(stdout);
		node->Mojoodi(number - 1);
	}
	cout << "  1.again\n  2.Menu";
	char x = getch();
	if (x == '1')
		Mojoodi(bank, moshtary, num);
	else
		menu(bank, moshtary, num);
}

void CreateAccount(Banks* bank, customers* moshtary, int num) {
	customers* node = moshtary;
	for (int i = 0; i < num; node = node->next, i++);
	int number = listOfBanks(bank);
	if (number != -1) {
		Banks* node1 = bank;
		for (int i = 0; i < number - 1; node1 = node1->next, i++);
		cout << "       Specify your account type:\n       1.Kootah Modat\n       2.Boland Modat\n       3.special\n";
		char x = getch();
		x -= 48;
		cout << "       Mablagh Avalie: ";
		int i;
		cin >> i;
		getchar();
		Massage* payam = new Massage;
		payam->firstset(i, x, num, node->getName(), node1->getname(), 0, 0, 0);
		node1->AddMassage(payam);
		cout << "    Your request has been successfully submitted.The result will be notified to you soon\n\n";
	}
	else
		cout << "   there is no bank yet\n\n";
	cout << "  1.Again\n  2.Menu";
	char x = getch();
	if (x == '1')
		CreateAccount(bank, moshtary, num);
	else
		menu(*bank, moshtary, num);
}

void vam(Banks* bank, customers* moshtary, int num) {
	system("cls");
	setFontSize(25, 25);
	customers* node = moshtary;
	for (int i = 0; i < num; node = node->next, i++);
	if (node->getvv()) {
		if (node->showAccount()) {
			cout << "    Please enter the account number on which you want to borrow: ";
			int number, paynum = 0, q, money, part;
			cin >> number;
			paynum = number - 1;
			cout << "\n\n     Do you pay with this account?  1.Yes  2.No";
			cin >> q;
			fputs("\033[A\033[2K", stdout);
			rewind(stdout);
			if (num == 2) {
				cout << "\n    Please enter the account number on which you want Pay: ";
				cin >> paynum;
			}
			cout << "\n      Number of loan installments: ";
			cin >> part;
			cout << "\n      Money: ";
			cin >> money;
			getchar();
			Banks* node1 = bank;
			string AccName = node->ReturnAccName(number - 1);
			for (; node1->getname() != AccName; node1 = node1->next);
			Massage* payam = new Massage;
			payam->firstset(money, -1, num, node->getName(), AccName, number - 1, paynum - 1, part);
			node1->AddMassage(payam);
			cout << "\n\n   Your request has been successfully submitted.The result will be notified to you soon\n\n";
		}
	}
	else {
		cout << "                                 you Already have a loan\n\n\n";
		node->showLoan();
	}
	cout << "\n\n  1.Menu";
	char x = getch();
	if (x == '1')
		menu(*bank, moshtary, num);
}

void Massage1(Banks* bank, customers* moshtary, int num1, int num2) {
	system("cls");
	setFontSize(25, 25);
	Banks* node = bank;
	for (int i = 0; i < num1; node = node->next, i++);
	node->showMassage(1);
	cout << "\n\n\n  1.check Massage\n  2.Delete Checked Massage\n  3.menu\n\n";
	char x = getch();
	if (x == '1') {
		node->checkAccount(moshtary);
		Massage1(bank, moshtary, num1, num2);
	}
	else if (x == '2') {
		node->Delete(1);
		Massage1(bank, moshtary, num1, num2);
	}
	else if (x == '3')
		menu2(bank, moshtary, num1, num2);
}

void Massage2(Banks* bank, customers* moshtary, int num1, int num2) {
	system("cls");
	setFontSize(25, 25);
	Banks* node = bank;
	for (int i = 0; i < num1; node = node->next, i++);
	node->showMassage(2);
	cout << "\n\n  1.check Massage\n  2.Delete Checked Massage\n  3.menu\n\n";
	char x = getch();
	if (x == '1') {
		node->checkLoan(moshtary);
		Massage2(bank, moshtary, num1, num2);
	}
	else if (x == '2') {
		node->Delete(2);
		Massage2(bank, moshtary, num1, num2);
	}
	else if (x == '3')
		menu2(bank, moshtary, num1, num2);
}

void AddBoss(Banks* bank, customers* moshtary) {
	system("cls");
	setFontSize(25, 25);
	int number = listOfBanks(bank);
	if (number != -1) {
		Banks* node = bank;
		for (int i = 0; i < number - 1; node = node->next, i++);
		cout << "\n\n       Boss name: ";
		string name, code;
		getline(cin, name);
		if (node->check(name, 2) == -1) {
			cout << "\n\n       Boss code: ";
			cin >> code;
			char x = getchar();
			node->AddBoss(name, code);
			cout << "\n\n      Successfully added\n\n";
		}
		else
			cout << "      A Boss with the same name is registered in the Bank.\n\n";
	}
	else
		cout << "   there is no bank yet\n\n";
	cout << "  1.Again   2.menu";
	char x = getch();
	if (x == '1')
		AddBoss(bank, moshtary);
	if (x == '2')
		menu3(bank, moshtary);
}

void CreateBank(Banks* bank, customers* moshtary) {
	system("cls");
	setFontSize(25, 25);
	cout << "\n\n      Bank name: ";
	string name;
	getline(cin, name);
	Banks* node = bank;
	int i = 1;
	for (; node != NULL; node = node->next) {
		if (node->getname() == name) {
			i--;
			break;
		}
	}
	if (i) {
		Banks* node2 = new Banks;
		cout << "\n\n      established year: ";
		int year;
		cin >> year;
		char x = getchar();
		node2->firstset(name, year);
		if (bank == NULL)
			bank = node2;
		else {
			for (node = bank; node->next != NULL; node = node->next);
			node->next = node2;
		}
		cout << "\n\n      Successfully added\n\n";
	}
	else
		cout << "      A bank with the same name is registered in the system.\n\n";
	cout << "  1.Again   2.menu";
	char x = getch();
	if (x == '1')
		CreateBank(bank, moshtary);
	if (x == '2')
		menu3(bank, moshtary);
}

void ShowMassage(Banks& bank, customers* moshtary, int num) {
	system("cls");
	setFontSize(20, 20);
	customers* node = moshtary;
	for (int i = 0; i < num; node = node->next, i++);
	node->showMassage();
	cout << "\n\n\n  1.Delete Massages\n  2.menu\n\n";
	char x = getch();
	if (x == '1') {
		node->Delete();
		ShowMassage(bank, moshtary, num);
	}
	else if (x == '2')
		menu(bank, moshtary, num);
}

void menu(Banks& bank, customers* moshtary, int num) {
	system("cls");
	system("COLOR C0");
	setFontSize(25, 25);
	customers* node = moshtary;
	for (int i = 0; i < num; node = node->next, i++);
	node->showmenu();
	char x = getch();
	if (x == '1')
		Moneytransfer(bank, moshtary, num);
	if (x == '2')
		Mojoodi(bank, moshtary, num);
	if (x == '3')
		CreateAccount(&bank, moshtary, num);
	if (x == '4')
		vam(&bank, moshtary, num);
	if (x == '5')
		ShowMassage(bank, moshtary, num);
	if (x == '6')
		wellcome(bank, *moshtary);
	if (x == '0')
		Exit(&bank, moshtary);
}

void menu2(Banks* bank, customers* moshtary, int num1, int num2) {
	system("cls");
	system("COLOR E0");
	setFontSize(25, 25);
	Banks* node1 = bank;
	for (int i = 0; i < num1; node1 = node1->next, i++);
	node1->showmenu(num2);
	char x = getch();
	if (x == '1')
		Massage1(bank, moshtary, num1, num2);
	if (x == '2')
		Massage2(bank, moshtary, num1, num2);
	if (x == '3')
		wellcome(*bank, *moshtary);
	if (x == '0')
		Exit(bank, moshtary);
}

void menu3(Banks* bank, customers* moshtary) {
	system("cls");
	system("COLOR D7");
	setFontSize(25, 25);
	cout << "\n\n               Matin Rezaei             1381/3/3\n\n";
	cout << "  1.Add Bank\n\n  2.Add Boss\n\n  3.Lock\n\n  0.exit\n\n";
	char x = getch();
	if (x == '1')
		CreateBank(bank, moshtary);
	if (x == '2')
		AddBoss(bank, moshtary);
	if (x == '3')
		wellcome(*bank, *moshtary);
	if (x == '0')
		Exit(bank, moshtary);
}

void login(Banks* bank, customers* moshtary) {
	system("cls");
	system("COLOR F0");
	setFontSize(40, 40);
	cout << "1.Customer or Admin           2.Bosses\n";
	char x = getch();
	if (x == '1') {
		string NationalCode, password;
		char pass[20];
		cout << "\n\n                          Natinal code: ";
		getline(cin, NationalCode);
		cout << "\n\n\n                          Password: ";
		for (int i = 0;; i++) {
			pass[i] = getch();
			if (pass[i] == '\r') {
				pass[i] = '\0';
				cout << " \b\n";
				break;
			}
			if (pass[i] != 8)
				cout << " \b*";
			else {
				cout << "\b \b";
				pass[i - 1] = '\0';
				i -= 2;
			}
		}
		password = pass;
		if (NationalCode == "1250675715" && password == "matin") {
			system("cls");
			setFontSize(200, 200);
			cout << "\n      Admin\n";
			Sleep(3000);
			menu3(bank, moshtary);
		}
		else {
			int i = 0, a = 0;
			for (customers* node = moshtary; node != NULL; node = node->next, i++)
				if (node->check(NationalCode, password, 0)) {
					a++;
					break;
				}
			if (a) {
				system("cls");
				setFontSize(200, 200);
				cout << "\n    Customer\n";
				Sleep(3000);
				menu(*bank, moshtary, i);
			}
		}
	}
	else {
		string BankName, code;
		cout << "\n\n                          Bank Name: ";
		getline(cin, BankName);
		cout << "\n\n\n                          Boss code: ";
		getline(cin, code);
		Banks* node = bank;
		for (int i = 0; node != NULL; node = node->next, i++) {
			if (BankName == node->getname()) {
				int j = node->check(code, 1);
				if (j != -1) {
					system("cls");
					setFontSize(200, 200);
					cout << "\n      Boss\n";
					Sleep(3000);
					menu2(bank, moshtary, i, j);
				}
			}
		}
	}
	cout << "\n\n\n\n\n                          Fail to Login\n\n";
	cout << "  1.Lock\n\n";
	cout << "  2.Try again\n\n";
	cout << "  0.exit\n\n";
	x = getch();
	if (x == '1')
		wellcome(*bank, *moshtary);
	if (x == '2')
		login(bank, moshtary);
	if (x == '0')
		Exit(bank, moshtary);
}

void logup(Banks& bank, customers* moshtary) {
	system("cls");
	system("COLOR F0");
	setFontSize(40, 40);
	string name, NationalCode;
	cout << "                                name: ";
	getline(cin, name);
	cout << "\n\n\n                               Natinal code: ";
	getline(cin, NationalCode);
	int i = 0, a = 0;
	for (customers* node = moshtary; node != NULL; node = node->next, i++)
		if (node->check(NationalCode, name, 1)) {
			a++;
			break;
		}
	if (a)
		cout << "  A person with this national code is registered in the system \n\n\n";
	else {
		customers* node = new customers;
		cout << "\n\n\n                                Password: ";
		char pass[20];
		for (int i = 0;; i++) {
			pass[i] = getch();
			if (pass[i] == '\r') {
				pass[i] = '\0';
				cout << " \b\n";
				break;
			}
			if (pass[i] != 8)
				cout << " \b*";
			else {
				cout << "\b \b";
				pass[i - 1] = '\0';
				i -= 2;
			}
		}
		int y, m, d;
		cout << "\n\n\n                    Bithday(Format:year/month/day): ";
		scanf("%d/%d/%d", &y, &m, &d);
		getchar();
		node->firstset(name, NationalCode, pass, y, m, d);
		if (moshtary == NULL)
			moshtary = node;
		else {
			customers* last = moshtary;
			for (; last->next != NULL; last = last->next);
			last->next = node;
		}
		cout << "\n\n                           Account created successfully\n\n\n";
	}
	cout << "                               1.Login            2.Lock\n\n";
	char x = getch();
	if (x == '1')
		login(&bank, moshtary);
	if (x == '2')
		return wellcome(bank, *moshtary);
}

void wellcome(Banks& bank, customers& moshtary) {
	system("cls");
	system("COLOR 0F");
	setFontSize(22, 22);
	cout << "                                                                  internet Bank\n\n\n";
	cout << "                                                              developer: Matin Rezaei\n\n";
	cout << "                                                            1.Sign in        2.Sign up\n\n";
	cout << "                                                                      0.Exit\n";
	char x = getch();
	if (x == '1')
		login(&bank, &moshtary);
	if (x == '2')
		logup(bank, &moshtary);
	if (x == '0')
		Exit(&bank, &moshtary);
}

int main() {
	int num = 0;
	ifstream banks, customer;
	banks.open("banks.txt", ios::in);
	customer.open("customers.txt", ios::in);
	Banks* bank = new Banks;
	customers* moshtary = new customers;
	customer >> num;
	if (num == 0)
		moshtary = NULL;
	else {
		customers* last = moshtary;
		for (int i = 0; i < num; i++) {
			customers* node = new customers;
			node->Read(customer);
			if (i == 0) {
				moshtary = node;
				last = moshtary;
			}
			else {
				last->next = node;
				last = last->next;
			}
		}
	}
	num = 0;
	banks >> num;
	if (num == 0)
		bank = NULL;
	else {
		Banks* last = bank;
		for (int i = 0; i < num; i++) {
			Banks* node = new Banks;
			node->Read(banks);
			if (i == 0) {
				bank = node;
				last = bank;
			}
			else {
				last->next = node;
				last = last->next;
			}
		}
	}
	customer.close();
	banks.close();
	wellcome(*bank, *moshtary);
}