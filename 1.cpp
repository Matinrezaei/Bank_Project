#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#pragma warning(disable: 4996)
using namespace std;

time_t t = time(NULL);
struct tm* tm = localtime(&t);

typedef struct Date {
	int Day;
	int Month;
	int Year;
	int kol;
}Date;

typedef struct Bosses {
	string name, code;
	Bosses* next;
}Bosses;

typedef struct Massage {
	string Receiver;
	string Sender;
	string Text;
	int payAccount, LoanAccount;
	int vaziat, kindOfMassage;
	int KindOfAccount, num;
	int LoanPart, mablagh;
	Massage* next;
}Massage;

typedef struct Account {
	Date date;
	string AccountNumber;
	string bank;
	int kind, LastPay;
	long double Inventory;
	Account* next;
}Account;

typedef struct Loan {
	Date date;
	int paymentNumber;
	int peyAccount, hesab;
	int LastPay, payed;
	int vaziat;
	long int mablagh;
}Loan;

typedef struct customers {
	string Name, Password;
	string NationalCode;
	Date Birthday;
	Loan vam;
	Account* Hesab;
	Massage* Massages;
	int MassageNumber;
	int vaziat;
}customers;

typedef struct Banks {
	string name;
	Bosses* Boss;
	Massage* Massages;
	int establishedyear;
	int kind1, kind2;
	Banks* next;
}Banks;

void wellcome(Banks&, customers&, int&);

void menu2(Banks*, customers*, int&, int, int);

void menu(Banks&, customers*, int&, int);

void menu3(Banks*, customers*, int&);

void Massage1(Banks*, customers*, int&, int, int);

void Massage2(Banks*, customers*, int&, int, int);

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
		cout << a << ". " << node->name << "\n\n";
	cout << "\n\n       Enter The number of Bank: ";
	int i;
	cin >> i;
	char x = getchar();
	return i;
}

void Exit(Banks* bank, customers* moshtary, int& size) {
	ofstream banks, customer;
	banks.open("banks.txt", ios::trunc);
	customer.open("customers.txt", ios::trunc);
	customer << size;
	for (int i = 0; i < size; i++) {
		customer << moshtary[i].Name << "\n" << moshtary[i].Password << "\n" << moshtary[i].NationalCode << "\n" << moshtary[i].Birthday.Year
			<< " " << moshtary[i].Birthday.Month << " " << moshtary[i].Birthday.Day << " " << moshtary[i].Birthday.kol << " "
			<< moshtary[i].vaziat << " " << moshtary[i].vam.date.Year << " " << moshtary[i].vam.date.Month << " " << moshtary[i].vam.date.Day
			<< " " << moshtary[i].vam.date.kol << " " << moshtary[i].vam.paymentNumber << " " << moshtary[i].vam.peyAccount << " "
			<< moshtary[i].vam.hesab << " " << moshtary[i].vam.LastPay << " " << moshtary[i].vam.payed << " " << moshtary[i].vam.vaziat << " "
			<< moshtary[i].vam.mablagh << "\n";
		int j = 0;
		for (Account* last = moshtary[i].Hesab; last != NULL; last = last->next, j++);
		customer << j << 'x';
		for (; moshtary[i].Hesab != NULL; moshtary[i].Hesab = moshtary[i].Hesab->next)
			customer << moshtary[i].Hesab->AccountNumber << "\n" << moshtary[i].Hesab->bank << "\n" << moshtary[i].Hesab->date.Year
			<< " " << moshtary[i].Hesab->date.Month << " " << moshtary[i].Hesab->date.Day << " " << moshtary[i].Hesab->date.kol
			<< " " << moshtary[i].Hesab->Inventory << " " << moshtary[i].Hesab->kind << " " << moshtary[i].Hesab->LastPay << "x";
		customer << moshtary[i].MassageNumber;
		for (; moshtary[i].Massages != NULL; moshtary[i].Massages = moshtary[i].Massages->next)
			customer << moshtary[i].Massages->Receiver << "\n" << moshtary[i].Massages->Sender << "\n" << moshtary[i].Massages->Text
			<< "\n" << moshtary[i].Massages->payAccount << " " << moshtary[i].Massages->LoanAccount << " "
			<< moshtary[i].Massages->vaziat << " " << moshtary[i].Massages->kindOfMassage << " " << moshtary[i].Massages->KindOfAccount
			<< " " << bank->Massages->num << " " << moshtary[i].Massages->LoanPart << " " << moshtary[i].Massages->mablagh;
	}
	int j = 0;
	for (Banks* node = bank; node != NULL; node = node->next, j++);
	banks << j;
	while (bank != NULL) {
		banks << bank->name << "\n" << bank->establishedyear << " " << bank->kind1 << " " << bank->kind2 << "\n";
		j = 0;
		for (Bosses* last = bank->Boss; last != NULL; last = last->next, j++);
		banks << j;
		for (; bank->Boss != NULL; bank->Boss = bank->Boss->next)
			banks << bank->Boss->name << "\n" << bank->Boss->code << "\n";
		if (j == 0)
			banks << "\n";
		banks << bank->kind1 + bank->kind2;
		for (; bank->Massages != NULL; bank->Massages = bank->Massages->next)
			banks << bank->Massages->Receiver << "\n" << bank->Massages->Sender << "\n" << bank->Massages->payAccount << " "
			<< bank->Massages->LoanAccount << " " << bank->Massages->vaziat << " " << bank->Massages->kindOfMassage << " "
			<< bank->Massages->KindOfAccount << " " << bank->Massages->num << " " << bank->Massages->LoanPart << " " << bank->Massages->mablagh;
		bank = bank->next;
	}
	banks.close();
	customer.close();
	exit(0);
}

int Check(customers* moshtary, string NationalCode, int size) {
	customers* node = moshtary;
	for (int i = 0; i < size; i++)
		if (moshtary[i].NationalCode == NationalCode)
			return i;
	return -1;
}

int Check2(customers* moshtary, string NationalCode, string password, int size) {
	customers* node = moshtary;
	for (int i = 0; i < size; i++)
		if (moshtary[i].NationalCode == NationalCode && moshtary[i].Password == password)
			return i;
	return -1;
}

void Delete(Banks* bank, customers* moshtary, int& size, int num1, int num2, int k) {
	Banks* node1 = bank;
	for (int i = 0; i < num1; node1 = node1->next, i++);
	for (; node1->Massages->vaziat == 1 && node1->Massages->kindOfMassage == k; node1->Massages = node1->Massages->next) {
		if (node1->Massages->next == NULL) {
			node1->Massages = node1->Massages->next;
			break;
		}
	}
	Massage* last = node1->Massages;
	Massage* node = new Massage;
	Massage* prev = new Massage;
	for (node = last; last != NULL; last = last->next) {
		if (1 == last->vaziat && last->kindOfMassage == k) {
			prev->next = node->next;
			node = last->next;
			continue;
		}
		node = last->next;
		prev = last;
	}
	menu2(bank, moshtary, size, num1, num2);
}

void barresi1(Massage* payam, Banks* bank, customers* moshtary, int& size, int num1, int num2) {
	cout << "    Enter number of Massage: ";
	int i;
	cin >> i;
	char x = getchar();
	Massage* node = payam;
	if (node->kindOfMassage != 1)
		for (; node->kindOfMassage != 1; node = node->next);
	for (int j = 0; j < i - 1; node = node->next) {
		if (node == NULL) {
			cout << "                                  out of range";
			Sleep(3000);
			return;
		}
		if (node->kindOfMassage == 1)
			j++;
	}
	if (node->vaziat)
		cout << "\n\n                              Already checked\n\n";
	else {
		Banks* node3 = bank;
		for (int i = 0; i < num1; node3 = node3->next, i++);
		node->vaziat = 1;
		cout << "    1.Agree    2.Disagree: ";
		int y;
		cin >> y;
		char x = getchar();
		fputs("\033[A\033[2K", stdout);
		rewind(stdout);
		Massage* node1 = new Massage;
		moshtary[node->num].MassageNumber++;
		node1->Receiver = moshtary[node->num].Name;
		node1->Sender = node->Receiver;
		node1->kindOfMassage = 3;
		node1->vaziat = 0;
		node1->next = NULL;
		Account* node2 = new Account;
		if (y == 1) {
			srand(time(0));
			for (int i = 0; i < 16; node2->AccountNumber += to_string(rand() % 10), i++);
			node2->bank = node->Receiver;
			node2->date.Day = tm->tm_mday;
			node2->date.Month = tm->tm_mon + 1;
			node2->date.Year = tm->tm_year + 1900;
			node2->date.kol = findday(node2->date.Day, node2->date.Month, node2->date.Year);
			node2->Inventory = node->mablagh;
			node2->LastPay = node2->date.kol;
			node2->kind = node->KindOfAccount;
			node2->next = NULL;
			if (moshtary[node->num].Hesab == NULL)
				moshtary[node->num].Hesab = node2;
			else {
				Account* last = moshtary[node->num].Hesab;
				for (; last->next != NULL; last = last->next);
				last->next = node2;
			}
			node1->Text = "Your account has been successfully verified on the ";
		}
		else {
			node1->Text = "Your account was rejected on the ";
		}
		node1->Text += to_string(tm->tm_year + 1900) += "/";
		node1->Text += to_string(tm->tm_mon + 1) += "/";
		node1->Text += to_string(tm->tm_mday);
		if (moshtary[node->num].Massages == NULL)
			moshtary[node->num].Massages = node1;
		else {
			Massage* last1 = moshtary[node->num].Massages;
			for (; last1->next != NULL; last1 = last1->next);
			last1->next = node1;
		}
		cout << "\n\n                                   checked";
	}
	Sleep(3000);
	Massage1(bank, moshtary, size, num1, num2);
}

void barresi2(Massage* payam, Banks* bank, customers* moshtary, int& size, int num1, int num2) {
	cout << "    Enter number of Massage: ";
	int i;
	cin >> i;
	char x = getchar();
	Massage* node = payam;
	if (node->kindOfMassage != 2)
		for (; node->kindOfMassage != 2; node = node->next);
	for (int j = 0; j < i - 1; node = node->next) {
		if (node == NULL) {
			cout << "                                  out of range";
			Sleep(3000);
			return;
		}
		if (node->kindOfMassage == 2)
			j++;
	}
	if (node->vaziat)
		cout << "\n\n                              Already checked\n\n";
	else {
		Banks* node3 = bank;
		for (int i = 0; i < num1; node3 = node3->next, i++);
		node->vaziat = 1;
		cout << "    1.Agree    2.Disagree: ";
		int y;
		cin >> y;
		char x = getchar();
		fputs("\033[A\033[2K", stdout);
		rewind(stdout);
		Massage* node1 = new Massage;
		moshtary[node->num].MassageNumber++;
		node1->Receiver = moshtary[node->num].Name;
		node1->Sender = node->Receiver;
		node1->kindOfMassage = 3;
		node1->vaziat = 0;
		node1->next = NULL;
		if (y == 1) {
			Account* node2 = moshtary[node->num].Hesab;
			for (int i = 0; i < node->LoanAccount; node2 = node2->next, i++);
			moshtary[node->num].vam.paymentNumber = node->LoanPart;
			moshtary[node->num].vam.date.Day = tm->tm_mday;
			moshtary[node->num].vam.date.Month = tm->tm_mon + 1;
			moshtary[node->num].vam.date.Year = tm->tm_year + 1900;
			moshtary[node->num].vam.date.kol = findday(moshtary[node->num].vam.date.Day,
				moshtary[node->num].vam.date.Month, moshtary[node->num].vam.date.Year);
			node2->Inventory += node->mablagh;
			moshtary[node->num].vam.mablagh = node->mablagh;
			moshtary[node->num].vam.LastPay = moshtary[node->num].vam.date.kol;
			moshtary[node->num].vam.hesab = node->LoanAccount;
			moshtary[node->num].vam.peyAccount = node->payAccount;
			moshtary[node->num].vam.payed = 0;
			moshtary[node->num].vam.vaziat = 0;
			node1->Text = "Your Loan has been successfully verified on the ";
		}
		else {
			node1->Text = "Your Loan was rejected on the ";
		}
		node1->Text += to_string(tm->tm_year + 1900) += "/";
		node1->Text += to_string(tm->tm_mon + 1) += "/";
		node1->Text += to_string(tm->tm_mday);
		if (y == 1) {
			node1->Text += "    next installments money: ";
			node1->Text += to_string(node->mablagh / node->LoanPart);
		}
		if (moshtary[node->num].Massages == NULL)
			moshtary[node->num].Massages = node1;
		else {
			Massage* last = moshtary[node->num].Massages;
			for (; last->next != NULL; last = last->next);
			last->next = node1;
		}
		cout << "\n\n                                   checked";
	}
	Sleep(3000);
	Massage2(bank, moshtary, size, num1, num2);
}

void Moneytransfer(Banks& bank, customers* moshtary, int& size, int num) {
	system("cls");
	setFontSize(25, 25);
	if (moshtary[num].vaziat == 0 || moshtary[num].Hesab == NULL) {
		if (moshtary[num].Hesab == NULL)
			cout << "                                  No account available\n\n";
		else
			cout << "      Your account has been blocked. You will not be able to transfer funds\n\n";
	}
	else {
		Account* node = moshtary[num].Hesab, * node1 = NULL;
		cout << "Row         Account Number           Kind             Bank          vaziat\n\n";
		for (int a = 1; node != NULL; node = node->next, a++) {
			cout << a << ".         " << node->AccountNumber << "        ";
			if (node->kind == 1)
				cout << "Kootah Modat      " << node->bank;
			else if (node->kind == 2)
				cout << "Boland Modat      " << node->bank;
			else if (node->kind == 3)
				cout << "      Special      " << node->bank;
			if (moshtary[num].vaziat)
				cout << "    Free\n\n";
			else
				cout << "    Blocked\n\n";
		}
		int number;
		cin >> number;
		char x = getchar();
		fputs("\033[A\033[2K", stdout);
		rewind(stdout);
		node = moshtary[num].Hesab;
		for (int i = 0; i < number - 1; node = node->next, i++);
		cout << "\n\n                 Enter the Destination account number:\n                 ";
		string account;
		cin >> account;
		getchar();
		int i = 0, a = 0;
		for (; i < size; i++) {
			node1 = moshtary[i].Hesab;
			for (; node1 != NULL; node1 = node1->next) {
				if (account == node1->AccountNumber) {
					a = 1;
					break;
				}
			}
			if (a) break;
		}
		if (a) {
			cout << "                 " << moshtary[i].Name << "       " << node1->bank << "\n\n";
			cout << "Is That True? 1.Yes  2.No";
			cin >> i;
			fputs("\033[A\033[2K", stdout);
			rewind(stdout);
			if (i == 1) {
				cout << "                 Enter the Money: ";
				int mablagh;
				cin >> mablagh;
				char x = getchar();
				if (node->Inventory >= mablagh) {
					node1->Inventory += mablagh;
					node->Inventory -= mablagh;
					cout << "                  mission accomplished\n\n";
				}
				else
					cout << "                 Your account balance is not enough\n\n";
			}
		}
		else
			cout << "          Not found\n\n";
	}
	cout << "  1.again\n  2.Menu";
	char x = getch();
	if (x == '1')
		Moneytransfer(bank, moshtary, size, num);
	else
		menu(bank, moshtary, size, num);
}

void Mojoodi(Banks& bank, customers* moshtary, int& size, int num) {
	system("cls");
	setFontSize(25, 25);
	if (moshtary[num].Hesab == NULL)
		cout << "                                  No account available\n\n";
	else {
		Account* node = moshtary[num].Hesab;
		cout << "Row         Account Number           Kind             Bank          vaziat\n\n";
		for (int a = 1; node != NULL; node = node->next, a++) {
			cout << a << ".         " << node->AccountNumber << "        ";
			if (node->kind == 1)
				cout << "Kootah Modat      " << node->bank;
			else if (node->kind == 2)
				cout << "Boland Modat      " << node->bank;
			else if (node->kind == 3)
				cout << "      Special      " << node->bank;
			if (moshtary[num].vaziat)
				cout << "    Free\n\n";
			else
				cout << "    Blocked\n\n";
		}
		int number;
		cin >> number;
		char x = getchar();
		fputs("\033[A\033[2K", stdout);
		rewind(stdout);
		node = moshtary[num].Hesab;
		for (int i = 0; i < number - 1; node = node->next, i++);
		cout << "\n\n               Mojoodi Hesab shome: " << (long long int)node->Inventory << "\n\n";
	}
	cout << "  1.again\n  2.Menu";
	char x = getch();
	if (x == '1')
		Mojoodi(bank, moshtary, size, num);
	else
		menu(bank, moshtary, size, num);
}

void CreateAccount(Banks* bank, customers* moshtary, int& size, int num) {
	int number = listOfBanks(bank);
	if (number != -1) {
		if (moshtary[num].vaziat) {
			Banks* node = bank;
			for (int i = 0; i < number - 1; node = node->next, i++);
			cout << "       Specify your account type:\n       1.Kootah Modat\n       2.Boland Modat\n       3.special\n";
			char x = getch();
			x -= 48;
			cout << "       Mablagh Avalie: ";
			int i;
			cin >> i;
			getchar();
			Massage* payam = new Massage;
			payam->mablagh = i;
			payam->kindOfMassage = 1;
			payam->KindOfAccount = x;
			payam->next = NULL;
			payam->Sender = moshtary[num].Name;
			payam->Receiver = node->name;
			payam->vaziat = 0;
			payam->num = num;
			node->kind1++;
			if (node->Massages == NULL)
				node->Massages = payam;
			else {
				Massage* last = node->Massages;
				for (; last->next != NULL; last = last->next);
				last->next = payam;
			}
			cout << "    Your request has been successfully submitted.The result will be notified to you soon\n\n";
		}
		else
			cout << "    You are not allowed to create an account in any bank due to non-payment of your loan installment\n\n";
	}
	else
		cout << "   there is no bank yet\n\n";
	cout << "  1.Again\n  2.Menu";
	char x = getch();
	if (x == '1')
		CreateAccount(bank, moshtary, size, num);
	else
		menu(*bank, moshtary, size, num);
}

void vam(Banks* bank, customers* moshtary, int& size, int num) {
	system("cls");
	setFontSize(25, 25);
	Account* node = moshtary[num].Hesab;
	if (moshtary[num].vaziat && moshtary[num].vam.vaziat) {
		if (node != NULL) {
			cout << "    Please enter the account number on which you want to borrow: \n\n";
			cout << "   Row         Account Number           Kind             Bank          vaziat\n\n";
			for (int a = 1; node != NULL; node = node->next, a++) {
				cout << "   " << a << ".        " << node->AccountNumber << "        ";
				if (node->kind == 1)
					cout << "Kootah Modat      " << node->bank;
				else if (node->kind == 2)
					cout << "Boland Modat      " << node->bank;
				else if (node->kind == 3)
					cout << "      Special      " << node->bank;
				if (moshtary[num].vaziat)
					cout << "       Free\n";
				else
					cout << "       Blocked\n";
			}
			int number = 0;
			cin >> number;
			char x = getchar();
			node = moshtary[num].Hesab;
			for (int i = 0; i < number - 1; node = node->next, i++);
			Banks* node1 = bank;
			for (; node1->name != node->bank; node1 = node1->next);
			fputs("\033[A\033[2K", stdout);
			rewind(stdout);
			Massage* payam = new Massage;
			payam->LoanAccount = number - 1;
			payam->payAccount = number - 1;
			cout << "\n\n     Do you pay with this account?  1.Yes  2.No";
			cin >> number;
			fputs("\033[A\033[2K", stdout);
			rewind(stdout);
			if (number == 2) {
				cout << "\n    Please enter the account number on which you want Pay: ";
				cin >> number;
				payam->payAccount = number - 1;
				fputs("\033[A\033[2K", stdout);
				rewind(stdout);
			}
			cout << "\n      Number of loan installments: ";
			cin >> number;
			payam->LoanPart = number;
			cout << "\n      Money: ";
			cin >> number;
			getchar();
			payam->mablagh = number;
			payam->kindOfMassage = 2;
			payam->next = NULL;
			payam->Sender = moshtary[num].Name;
			payam->Receiver = node1->name;
			payam->vaziat = 0;
			payam->num = num;
			node1->kind2++;
			if (node1->Massages == NULL)
				node1->Massages = payam;
			else {
				Massage* last = node1->Massages;
				for (; last->next != NULL; last = last->next);
				last->next = payam;
			}
			cout << "\n\n   Your request has been successfully submitted.The result will be notified to you soon\n\n";
		}
		else
			cout << "                                              No Account yet.\n\n";
	}
	else {
		if (moshtary[num].vam.vaziat == 0) {
			cout << "                                 you Already have a loan\n\n\n";
			cout << "    Date began:  " << moshtary[num].vam.date.Year << "/" << moshtary[num].vam.date.Month << "/"
				<< moshtary[num].vam.date.Day << "\n\n";
			cout << "    Money: " << moshtary[num].vam.mablagh << "\n\n";
			cout << "    parts(payed): " << moshtary[num].vam.paymentNumber << "(" << moshtary[num].vam.payed << ")\n\n";
			for (int i = 0; i < moshtary[num].vam.hesab; node = node->next, i++);
			cout << "    Hesab vam:    " << node->AccountNumber << "       ";
			if (node->kind == 1)
				cout << "Kootah Modat      " << node->bank;
			else if (node->kind == 2)
				cout << "Boland Modat      " << node->bank;
			else if (node->kind == 3)
				cout << "      Special      " << node->bank;
			if (moshtary[num].vaziat)
				cout << "    Free\n\n";
			else
				cout << "    Blocked\n\n";
			node = moshtary[num].Hesab;
			for (int i = 0; i < moshtary[num].vam.peyAccount; node = node->next, i++);
			cout << "    Hesab pay:    " << node->AccountNumber << "       ";
			if (node->kind == 1)
				cout << "Kootah Modat      " << node->bank;
			else if (node->kind == 2)
				cout << "Boland Modat      " << node->bank;
			else if (node->kind == 3)
				cout << "      Special      " << node->bank;
			if (moshtary[num].vaziat)
				cout << "    Free\n\n";
			else
				cout << "    Blocked\n\n";
		}
		else
			cout << "    You are not allowed to create an account in any bank due to non-payment of your loan installment\n\n";
	}
	cout << "  1.Menu";
	char x = getch();
	if (x == '1')
		menu(*bank, moshtary, size, num);
}

void Massage1(Banks* bank, customers* moshtary, int& size, int num1, int num2) {
	system("cls");
	setFontSize(25, 25);
	Banks* node1 = bank;
	for (int i = 0; i < num1; node1 = node1->next, i++);
	cout << "                                                                Massages\n\n";
	int a = 0;
	for (Massage* payam = node1->Massages; payam != NULL; payam = payam->next)
		if (payam->kindOfMassage == 1) {
			a++;
			break;
		}
	if (a) {
		cout << "ROW       vaziat        Recever          Sender         Kind of Account      Mablagh Avalie\n\n";
		for (Massage* payam = node1->Massages; payam != NULL; payam = payam->next, a++) {
			if (payam->kindOfMassage == 2) {
				a--;
				continue;
			}
			cout << a << ".     ";
			if (payam->vaziat == 0)
				cout << "Not checked  ";
			if (payam->vaziat == 1)
				cout << "  checked  ";
			cout << payam->Receiver << "       " << payam->Sender << "      ";
			if (payam->KindOfAccount == 1)
				cout << "Kootah Modat        " << payam->mablagh << "\n";
			else if (payam->KindOfAccount == 2)
				cout << "Boland Modat        " << payam->mablagh << "\n";
			else if (payam->KindOfAccount == 3)
				cout << "Special        " << payam->mablagh << "\n";
		}
	}
	else
		cout << "  No Massage";
	cout << "\n\n\n  1.check Massage\n  2.Delete Checked Massage\n  3.menu\n\n";
	char x = getch();
	if (x == '1')
		barresi1(node1->Massages, bank, moshtary, size, num1, num2);
	else if (x == '2')
		Delete(bank, moshtary, size, num1, num2, 1);
	else if (x == '3')
		menu2(bank, moshtary, size, num1, num2);
}

void Massage2(Banks* bank, customers* moshtary, int& size, int num1, int num2) {
	system("cls");
	setFontSize(25, 25);
	Banks* node1 = bank;
	for (int i = 0; i < num1; node1 = node1->next, i++);
	cout << "                                                               Massages\n\n";
	int a = 0;
	for (Massage* payam = node1->Massages; payam != NULL; payam = payam->next)
		if (payam->kindOfMassage == 2) {
			a++;
			break;
		}
	if(a){
		cout << "ROW       vaziat     Recever          Sender         number of installment      Mablagh vam\n\n";
		for (Massage* payam = node1->Massages; payam != NULL; payam = payam->next, a++) {
			if (payam->kindOfMassage == 1) {
				a--;
				continue;
			}
			cout << a << ".     ";
			if (payam->vaziat == 0)
				cout << "Not checked   ";
			if (payam->vaziat == 1)
				cout << "  checked   ";
			cout << payam->Receiver << "      " << payam->Sender << "                    " << payam->LoanPart
				<< "                  " << payam->mablagh << "\n\n";
		}
	}
	else
		cout << "  No Massage\n\n";
	cout << "\n\n  1.check Massage\n  2.Delete Checked Massage\n  3.menu\n\n";
	char x = getch();
	if (x == '1')
		barresi2(node1->Massages, bank, moshtary, size, num1, num2);
	else if (x == '2')
		Delete(bank, moshtary, size, num1, num2, 2);
	else if (x == '3')
		menu2(bank, moshtary, size, num1, num2);
}

void CreateBank(Banks* bank, customers* moshtary, int& size) {
	system("cls");
	setFontSize(25, 25);
	cout << "\n\n      Bank name: ";
	string name;
	getline(cin, name);
	Banks* node = bank;
	int i = 1;
	for (; node != NULL; node = node->next) {
		if (node->name == name) {
			i--;
			break;
		}
	}
	Banks* node2 = new Banks;
	if (i) {
		cout << "\n\n      established year: ";
		cin >> node2->establishedyear;
		char x = getchar();
		node2->kind1 = 0;
		node2->kind2 = 0;
		node2->name = name;
		node2->Massages = NULL;
		node2->Boss = NULL;
		node2->next = NULL;
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
		CreateBank(bank, moshtary, size);
	if (x == '2')
		menu3(bank, moshtary, size);
}

void AddBoss(Banks* bank, customers* moshtary, int& size) {
	system("cls");
	setFontSize(25, 25);
	int number = listOfBanks(bank);
	if (number != -1) {
		Banks* node1 = bank;
		for (int i = 0; i < number - 1; node1 = node1->next, i++);
		cout << "\n\n       Boss name: ";
		string name;
		getline(cin, name);
		Bosses* node = node1->Boss;
		Bosses* last = new Bosses;
		int i = 1;
		for (; node != NULL; node = node->next) {
			if (node->name == name) {
				i--;
				break;
			}
		}
		if (i) {
			cout << "\n\n       Boss code: ";
			cin >> last->code;
			char x = getchar();
			last->name = name;
			last->next = NULL;
			if (node1->Boss == NULL)
				node1->Boss = last;
			else {
				for (node = node1->Boss; node->next != NULL; node = node->next);
				node->next = last;
			}
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
		AddBoss(bank, moshtary, size);
	if (x == '2')
		menu3(bank, moshtary, size);
}

void ShowMassage(Banks& bank, customers* moshtary, int& size, int num) {
	system("cls");
	setFontSize(20, 20);
	cout << "                                    Massages\n\n";
	if (moshtary[num].Massages != NULL) {
		cout << "ROW         vaziat     Recever            Sender                                     Text\n\n";
		Massage* payam = moshtary[num].Massages;
		for (int a = 1; payam != NULL; payam = payam->next, a++) {
			cout << a << ".      ";
			if (payam->vaziat == 0) {
				cout << "Not checked   ";
				payam->vaziat = 1;
			}
			else if (payam->vaziat == 1)
				cout << "  checked   ";
			cout << payam->Receiver << "     " << payam->Sender << "      " << payam->Text << "\n\n";
		}
	}
	else
		cout << "  No Massage";
	cout << "\n\n\n  1.Delete Massages\n  2.menu\n\n";
	char x = getch();
	if (x == '1') {
		moshtary[num].Massages = NULL;
		cout << "                              Deleted";
		moshtary[num].MassageNumber = 0;
		Sleep(3000);
		ShowMassage(bank, moshtary, size, num);
	}
	else if (x == '2')
		menu(bank, moshtary, size, num);
}

void menu(Banks& bank, customers* moshtary, int& size, int num) {
	system("cls");
	system("COLOR C0");
	setFontSize(25, 25);
	int p = 0;
	for (Massage* node3 = moshtary[num].Massages; node3 != NULL; node3 = node3->next) {
		if (node3->vaziat == 0)
			p++;
	}
	cout << "\n\n  " << moshtary[num].Name << "   " << moshtary[num].Birthday.Year << "/"
		<< moshtary[num].Birthday.Month << "/" << moshtary[num].Birthday.Day << "\n\n";
	cout << "  1.Money transfer\n\n  2.Inventory\n\n  3.Create Account\n\n";
	cout << "  4.Apply for a loan\n\n  5.Massages(" << p << ")\n\n  6.lock\n\n  0.exit\n\n";
	char x = getch();
	if (x == '1')
		Moneytransfer(bank, moshtary, size, num);
	if (x == '2')
		Mojoodi(bank, moshtary, size, num);
	if (x == '3')
		CreateAccount(&bank, moshtary, size, num);
	if (x == '4')
		vam(&bank, moshtary, size, num);
	if (x == '5')
		ShowMassage(bank, moshtary, size, num);
	if (x == '6')
		wellcome(bank, *moshtary, size);
	if (x == '0')
		Exit(&bank, moshtary, size);
}

void menu2(Banks* bank, customers* moshtary, int& size, int num1, int num2) {
	system("cls");
	system("COLOR E0");
	setFontSize(25, 25);
	Banks* node1 = bank;
	for (int i = 0; i < num1; node1 = node1->next, i++);
	Bosses* node2 = node1->Boss;
	for (int i = 0; i < num2; node2 = node2->next, i++);
	int kind1 = 0, kind2 = 0;
	for (Massage* node3 = node1->Massages; node3 != NULL; node3 = node3->next) {
		if (node3->kindOfMassage == 1 && node3->vaziat == 0)
			kind1++;
		if (node3->kindOfMassage == 2 && node3->vaziat == 0)
			kind2++;
	}
	cout << "\n\n  " << node2->name << "    Bank: " << node1->name << "\n\n";
	cout << "  1.account verification(" << kind1 << ")\n\n  2.Loan review("
		<< kind2 << ")\n\n  3.lock\n\n  0.exit\n\n";
	char x = getch();
	if (x == '1')
		Massage1(bank, moshtary, size, num1, num2);
	if (x == '2')
		Massage2(bank, moshtary, size, num1, num2);
	if (x == '3')
		wellcome(*bank, *moshtary, size);
	if (x == '0')
		Exit(bank, moshtary, size);
}

void menu3(Banks* bank, customers* moshtary, int& size) {
	system("cls");
	system("COLOR D7");
	setFontSize(25, 25);
	cout << "\n\n               Matin Rezaei             1381/3/3\n\n";
	cout << "  1.Add Bank\n\n  2.Add Boss\n\n  3.Lock\n\n  0.exit\n\n";
	char x = getch();
	if (x == '1')
		CreateBank(bank, moshtary, size);
	if (x == '2')
		AddBoss(bank, moshtary, size);
	if (x == '3')
		wellcome(*bank, *moshtary, size);
	if (x == '0')
		Exit(bank, moshtary, size);
}

void login(Banks* bank, customers& moshtary, int& size) {
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
			menu3(bank, &moshtary, size);
		}
		else {
			int i = Check2(&moshtary, NationalCode, password, size);
			if (i != -1) {
				system("cls");
				setFontSize(200, 200);
				cout << "\n    Customer\n";
				Sleep(3000);
				menu(*bank, &moshtary, size, i);
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
			if (node->name == BankName) {
				Bosses* node1 = node->Boss;
				for (int j = 0; node1 != NULL; node1 = node1->next, j++)
					if (node1->code == code) {
						system("cls");
						setFontSize(200, 200);
						cout << "\n      Boss\n";
						Sleep(3000);
						menu2(bank, &moshtary, size, i, j);
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
		wellcome(*bank, moshtary, size);
	if (x == '2')
		login(bank, moshtary, size);
	if (x == '0')
		Exit(bank, &moshtary, size);
}

void logup(Banks& bank, customers* moshtary, int& size) {
	system("cls");
	system("COLOR F0");
	setFontSize(40, 40);
	string name, NationalCode, password;
	cout << "                                name: ";
	getline(cin, name);
	cout << "\n\n\n                               Natinal code: ";
	getline(cin, NationalCode);
	if (int i = Check(moshtary, NationalCode, size) > -1) {
		cout << "  A person with this national code is registered in the system \n\n\n";
		cout << "  1.try again     2.Lock\n\n";
		char x = getch();
		if (x == '1')
			logup(bank, moshtary, size);
		if (x == '2')
			wellcome(bank, *moshtary, size);
	}
	else {
		size++;
		moshtary[size - 1].Name = name;
		moshtary[size - 1].NationalCode = NationalCode;
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
		password = pass;
		moshtary[size - 1].Password = password;
		cout << "\n\n\n                        Bithday(Format:year/month/day): ";
		scanf("%d/%d/%d", &moshtary[size - 1].Birthday.Year, &moshtary[size - 1].Birthday.Month, &moshtary[size - 1].Birthday.Day);
		getchar();
		moshtary[size - 1].Birthday.kol = findday(moshtary[size - 1].Birthday.Day,
			moshtary[size - 1].Birthday.Month, moshtary[size - 1].Birthday.Year);
		moshtary[size - 1].MassageNumber = 0;
		moshtary[size - 1].Massages = NULL;
		moshtary[size - 1].Hesab = NULL;
		moshtary[size - 1].vam.vaziat = 1;
		moshtary[size - 1].vaziat = 1;
		cout << "\n\n                           Account created successfully\n\n\n";
		cout << "                               1.Login            2.Lock\n\n";
		char x = getch();
		if (x == '1')
			login(&bank, *moshtary, size);
		if (x == '2')
			return wellcome(bank, *moshtary, size);
	}
}

void wellcome(Banks& bank, customers& moshtary, int& size) {
	system("cls");
	system("COLOR 0F");
	setFontSize(22, 22);
	cout << "                                                                  internet Bank\n\n\n";
	cout << "                                                              developer: Matin Rezaei\n\n";
	cout << "                                                            1.Sign in        2.Sign up\n\n";
	cout << "                                                                      0.Exit\n";
	char x = getch();
	if (x == '1')
		login(&bank, moshtary, size);
	if (x == '2')
		logup(bank, &moshtary, size);
	if (x == '0')
		Exit(&bank, &moshtary, size);
}

int main() {
	int size = 0, num = 0;
	Banks* bank = new Banks;
	ifstream banks, customer;
	banks.open("banks.txt", ios::in);
	customer.open("customers.txt", ios::in);
	customer >> size;
	customers* moshtary = new customers[size + 10];
	for (int i = 0, x = 0; i < size; i++) {
		getline(customer, moshtary[i].Name);
		getline(customer, moshtary[i].Password);
		getline(customer, moshtary[i].NationalCode);
		customer >> moshtary[i].Birthday.Year >> moshtary[i].Birthday.Month >> moshtary[i].Birthday.Day >> moshtary[i].Birthday.kol
			>> moshtary[i].vaziat >> moshtary[i].vam.date.Year >> moshtary[i].vam.date.Month >> moshtary[i].vam.date.Day
			>> moshtary[i].vam.date.kol >> moshtary[i].vam.paymentNumber >> moshtary[i].vam.peyAccount >> moshtary[i].vam.hesab
			>> moshtary[i].vam.LastPay >> moshtary[i].vam.payed >> moshtary[i].vam.vaziat >> moshtary[i].vam.mablagh >> x;

		if (x == 0) {
			moshtary[i].Hesab = NULL;
			char m;
			customer >> m;
			customer >> moshtary[i].MassageNumber;
		}
		else {
			Account* last1 = moshtary[i].Hesab;
			for (int j = 0; j < x; j++) {
				Account* node1 = new Account;
				char m;
				customer >> m;
				getline(customer, node1->AccountNumber);
				getline(customer, node1->bank);
				customer >> node1->date.Year >> node1->date.Month >> node1->date.Day >> node1->date.kol
					>> node1->Inventory >> node1->kind >> node1->LastPay;
				node1->next = NULL;
				if (j == 0) {
					moshtary[i].Hesab = node1;
					last1 = moshtary[i].Hesab;
				}
				else {
					last1->next = node1;
					last1 = last1->next;
				}
			}
			char m;
			customer >> m;
			customer >> moshtary[i].MassageNumber;
		}
		if (moshtary[i].MassageNumber == 0)
			moshtary[i].Massages = NULL;
		else {
			Massage* last2 = moshtary[i].Massages;
			for (int j = 0; j < moshtary[i].MassageNumber; j++) {
				Massage* node2 = new Massage;
				getline(customer, node2->Receiver);
				getline(customer, node2->Sender);
				getline(customer, node2->Text);
				customer >> node2->payAccount >> node2->LoanAccount >> node2->vaziat >> node2->kindOfMassage >> node2->KindOfAccount
					>> node2->num >> node2->LoanPart >> node2->mablagh;
				node2->next = NULL;
				if (j == 0) {
					moshtary[i].Massages = node2;
					last2 = moshtary[i].Massages;
				}
				else {
					last2->next = node2;
					last2 = last2->next;
				}
			}
		}
	}
	banks >> num;
	if (num == 0)
		bank = NULL;
	Banks* last = bank;
	for (int i = 0, x = 0; i < num; i++) {
		Banks* node = new Banks;
		getline(banks, node->name);
		banks >> node->establishedyear >> node->kind1 >> node->kind2 >> x;
		if (x == 0) {
			node->Boss = NULL;
			banks >> x;
		}
		else {
			Bosses* last1 = node->Boss;
			for (int j = 0; j < x; j++) {
				Bosses* node1 = new Bosses;
				getline(banks, node1->name);
				getline(banks, node1->code);
				node1->next = NULL;
				if (j == 0) {
					node->Boss = node1;
					last1 = node->Boss;
				}
				else {
					last1->next = node1;
					last1 = last1->next;
				}
			}
			banks >> x;
		}
		if (x == 0)
			node->Massages = NULL;
		else {
			Massage* last2 = node->Massages;
			for (int j = 0; j < x; j++) {
				Massage* node2 = new Massage;
				getline(banks, node2->Receiver);
				getline(banks, node2->Sender);
				banks >> node2->payAccount >> node2->LoanAccount >> node2->vaziat >> node2->kindOfMassage >> node2->KindOfAccount
					>> node2->num >> node2->LoanPart >> node2->mablagh;
				node2->next = NULL;
				if (j == 0) {
					node->Massages = node2;
					last2 = node->Massages;
				}
				else {
					last2->next = node2;
					last2 = last2->next;
				}
			}
		}
		node->next = NULL;
		if (i == 0) {
			bank = node;
			last = bank;
		}
		else {
			last->next = node;
			last = last->next;
		}
	}
	customer.close();
	banks.close();
	for (int i = 0; i < size; i++) {
		Massage* last = moshtary[i].Massages;
		int kol = findday(tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
		for (Account* node2 = moshtary[i].Hesab; node2 != NULL; node2 = node2->next) {
			int x = kol - node2->LastPay;
			int kind = 0;
			if (node2->kind == 1)
				kind = 10;
			if (node2->kind == 2)
				kind = 30;
			if (node2->kind == 3)
				kind = 50;
			node2->LastPay = kol;
			for (int j = 0; j < x; node2->Inventory += (node2->Inventory * kind) / 100, j++) {
				Massage* node = new Massage;
				node->Receiver = moshtary[i].Name;
				node->vaziat = 0;
				node->next = NULL;
				Banks* node3 = bank;
				for (; node3->name != node2->bank; node3 = node3->next);
				node->Sender = node2->bank;
				node->Text = "Your account balance New deposit: ";
				node->Text += to_string((long long int)node2->Inventory);
				if (moshtary[i].Massages == NULL)
					moshtary[i].Massages = node;
				else {
					for (last = moshtary[i].Massages; last->next != NULL; last = last->next);
					last->next = node;
				}
				moshtary[i].MassageNumber++;
			}
		}
		if (moshtary[i].vam.vaziat == 0) {
			int x = kol - moshtary[i].vam.LastPay;
			last = moshtary[i].Massages;
			for (; x >= 30; moshtary[i].vam.LastPay += 30, x -= 30) {
				Massage* node = new Massage;
				Account* node1 = moshtary[i].Hesab;
				for (int j = 0; j < moshtary[i].vam.peyAccount; node1 = node1->next, j++);
				node->Receiver = moshtary[i].Name;
				node->Sender = node1->bank;
				node->vaziat = 0;
				node->next = NULL;
				int ghest = moshtary[i].vam.mablagh / moshtary[i].vam.paymentNumber;
				if (moshtary[i].vam.payed == moshtary[i].vam.paymentNumber - 1)
					ghest += moshtary[i].vam.mablagh % moshtary[i].vam.paymentNumber;
				if (node1->Inventory > ghest) {
					node1->Inventory -= ghest;
					moshtary[i].vam.payed++;
					if (moshtary[i].vam.payed == moshtary[i].vam.paymentNumber) {
						node->Text += "The last installment of your loan was deducted from your account ";
						moshtary[i].vam.vaziat = 1;
					}
					else {
						node->Text += to_string(moshtary[i].vam.payed) += "/";
						node->Text += to_string(moshtary[i].vam.paymentNumber);
						node->Text += " installment of your loan was deducted from your account ";
						node->Text += "   next installments money: ";
						node->Text += to_string(ghest);
					}
				}
				else {
					node->Text += "Your account balance was not enough to pay your loan installment and your accounts were blocked";
					moshtary[i].vaziat = 0;
				}
				if (moshtary[i].Massages == NULL)
					moshtary[i].Massages = node;
				else {
					for (last = moshtary[i].Massages; last->next != NULL; last = last->next);
					last->next = node;
				}
				moshtary[i].MassageNumber++;
			}
		}
	}
	wellcome(*bank, *moshtary, size);
}