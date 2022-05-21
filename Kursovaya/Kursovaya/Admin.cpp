#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>
#include<Windows.h>
#include<iomanip>
#include"Admin.h"
#include"File.h"
#include"Users.h"
#include"Authorization.h"
#include "sha256.h"

using namespace std;

string inputFIO()//�������� �� ���� ���
{
	string name;
	int l;
	bool flag;
	do {
		flag = true;
		cin >> name;
		l = name.length();
		for (int i = 0; i < l; i++) {
			if (!(name[i] >= 'a'&& name[i] <= 'z') && !(name[i] >= 'A'&& name[i] <= 'Z'))
			{
				cout << "��������� ����!! ������ ��������� �����\n";
				flag = false;
				break;
			}
		}
	} while (flag == false);
	return name;
}

int inputYear()  //���� ����
{
	int year;
	while (1) {
		year = inputInt();
		if (year == 0 || year > 2020)
		{
			cout << "������� ��������� ���!\n";
		}
		else return year;
	}
}

int inputMonth()
{
	int month;
	while (1) {
		month = inputInt();
		if (month == 0 || month > 12)
		{
			cout << "������� ��������� �����!\n";
		}
		else return month;
	}
}

int inputInt() {  //���� ������ �����
	string s;
	int i, a = 0, l;
	bool flag = true;
	while (flag)
	{
		cin >> s;
		l = s.length();
		for (i = 0; i < l; i++)
		{
			if ((s[i] >= (char)48) && (s[i] <= (char)57) || (s[i] == (char)45))
			{
				if ((i > 0) && (s[i] == 45))
				{
					flag = true;
					cout << "�������� ������� �� �����!! ���������� ����!" << endl;
					break;
				}
				else flag = false;
			}
			else
			{
				flag = true;
				cout << "�������� ������� �� �����!! ���������� ����!" << endl;
				break;
			}

		}
	}
	return stof(s);
}

double inputDouble() //���� �������� �����
{
	int i, number = 0, l;
	bool flag = true;
	string s;
	while (flag)
	{
		cin >> s;
		l = s.length();
		for (i = 0; i < l; i++)
		{
			if ((s[i] >= (char)48) && (s[i] <= (char)57) || (s[i] == ','))
			{
				if (s[i] == ',')
				{
					number++;
					if (number > 1)
					{
						flag = true;
						cout << "�������� ������� �� �����!! ���������� ����!" << endl;
						number = 0;
						break;
					}
					else flag = false;
				}
				else flag = false;
			}
			else
			{
				flag = true;
				cout << "�������� ������� �� �����!! ���������� ����!" << endl;
				break;
			}
		}
	}
	return stof(s);
}

void addingNewEmployeeData(employees *&employee, int &NumberOfEmployee)//���������� ����������
{
	string name, personnelNumber;
	int numberOfHours, year, press, month;
	double oneHourPayment;
	ofstream fadd(FILE_LIST, ios::app);
	do {
		cout << "������� ��� : ";
		name = inputFIO();
		name = enterStringWithSmallLetter(name);//�������� �� ���� � ��������� �����

		cout << "������� ��������� �����: ";
		cin >> personnelNumber;

		cout << "������� ���: ";
		year = inputYear();

		cout << "������� �����: ";
		month = inputMonth();

		cout << "������� ���������� ������������� �����: ";
		numberOfHours = inputInt();
		cout << "������� ������ �� ���� ���: ";
		oneHourPayment = inputDouble();
		fadd << setw(25) << left << name       //������ � ����
			<< setw(20) << left << personnelNumber
			<< setw(7) << left << year
			<< setw(5) << left << month
			<< setw(7) << left << numberOfHours
			<< setw(5) << left << oneHourPayment << endl;
		cout << "\n������� �� �� ��������� ���������� �����������.\n1.��\n2.���\n";
		do {
			press = _getch();
		} while (press != 49 && press != 50);
	} while (press != 50);
	fadd.close();
	NumberOfEmployee = listEmployeeData(employee);
}

void deleteEmployeeData(employees *&employee, int &NumberOfEmployee)//�������� ����������
{
	int s = -1, press;
	string FIO;
	cout << "������� ��� ��������, �������� �� ������ ������� �� ������: ";
	cin >> FIO;
	FIO = enterStringWithSmallLetter(FIO); //�������� �� ���� � ��������� �����
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].FIO == FIO) {
			s = i;
			break;
		}
	}
	if (s == -1)
		cout << "������ ����� �������� �� �������.\n";
	else {
		cout << "�� ������������� ������ ������� ������?\n1.��\n2.���\n";
		do {
			press = _getch();
		} while (press != 49 && press != 50);
		if (press == 49)
		{
			for (int i = s; i < NumberOfEmployee - 1; i++)
				employee[i] = employee[i + 1];
			NumberOfEmployee--;
			cout << "�������� ������ �������!!\n";
			return;
		}
		else return;
	}
}

void redactionFIO(employees *&employee, int &NumberOfEmployee)//�������������� ���
{
	string FIO, newFIO;
	int press;
	cout << "������� ��� ��������, ��� ��� �� ������ ��������.\n";
	cin >> FIO;
	FIO = enterStringWithSmallLetter(FIO);//�������� �� ���� � ��������� �����
	//system("CLS");
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].FIO == FIO)
		{
			cout << "������� ����� ���: \n";
			cin >> newFIO;
			newFIO = enterStringWithSmallLetter(newFIO);//�������� �� ���� � ��������� �����
			cout << "�� ������������� ������ ��������?\n1.��\n2.���\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49)
			{
				employee[i].FIO = newFIO;
				system("CLS");
				cout << "�������������� ������� ���������.";
				Sleep(2000); system("CLS");
				return;
			}
			else return;
		}
	}
	cout << "��������! ������� �������� ��� � ���� ������\n";
	return;
}

void redactionYear(employees *&employee, int &NumberOfEmployee)//�������������� ����
{
	string FIO;
	int press;
	int year;
	cout << "������� ��� ��������, ��� ��� ������ ��������.\n";
	cin >> FIO;
	FIO = enterStringWithSmallLetter(FIO);//�������� �� ���� � ��������� �����
	system("CLS");
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].FIO == FIO)
		{
			cout << "������� ����� ���: \n";
			year = inputYear();

			cout << "�� ������������� ������ ��������?\n1.��\n2.���\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49)
			{
				employee[i].year = year;
				system("CLS");
				cout << "�������������� ������� ���������.";
				Sleep(2000); system("CLS");
				return;
			}
			else return;
		}
	}
	cout << "��������! ������� �������� ��� � ���� ������\n";
	return;
}

void redactionNumberOfHours(employees *&employee, int &NumberOfEmployee)//�������������� ���-�� �����
{
	string FIO;
	int press, numberOfHours;
	cout << "������� ��� ��������, ��� ���������� ������������� ����� �� ������ ��������.\n";
	cin >> FIO;
	
	FIO = enterStringWithSmallLetter(FIO);
	system("CLS");
	
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].FIO == FIO)
		{
			cout << "������� ����� ���������� ������������� �����: \n";
			numberOfHours = inputInt();
			
			cout << "�� ������������� ������ ��������?\n1.��\n2.���\n";
			
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			
			if (press == 49)
			{
				employee[i].numberOfHours = numberOfHours;
				system("CLS");
				cout << "�������������� ������� ���������.";
				Sleep(2000); system("CLS");
				return;
			}
			else return;
		}
	}
	cout << "��������! ������� �������� ��� � ���� ������\n";
	return;
}

void redactionOneHourPayment(employees *&employee, int &NumberOfEmployee) //�������������� ����� �� ���
{
	string FIO;
	int press;
	double oneHourPayment;
	cout << "������� ��� ��������, ��� ����� �� ��� ������ ��������.\n";
	cin >> FIO;
	FIO = enterStringWithSmallLetter(FIO);
	system("CLS");
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].FIO == FIO)
		{
			cout << "������� ����� �����: \n";
			oneHourPayment = inputDouble();
			cout << "�� ������������� ������ ��������?\n1.��\n2.���\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49)
			{
				employee[i].oneHourPayment = oneHourPayment;
				system("CLS");
				cout << "�������������� ������� ���������.";
				Sleep(2000); system("CLS");
				return;
			}
			else return;
		}
	}
	cout << "��������! ������� �������� ��� � ���� ������\n";
	return;
}

void redactionMonth(employees *&employee, int &NumberOfEmployee)//�������������� ������
{
	string FIO;
	int press, month;
	cout << "������� ��� ��������, ��� ����� ������ ��������.\n";
	cin >> FIO;
	FIO = enterStringWithSmallLetter(FIO);//�������� �� ���� � ��������� �����
	system("CLS");
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].FIO == FIO)
		{
			cout << "������� ����� �����: \n";
			month=inputMonth();
			cout << "�� ������������� ������ ��������?\n1.��\n2.���\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49)
			{
				employee[i].month = month;
				system("CLS");
				cout << "�������������� ������� ���������.";
				Sleep(2000); system("CLS");
				return;
			}
			else return;
		}
	}
	cout << "��������! ������� �������� ��� � ���� ������\n";
	return;
}

void redactionPersonnelNumber(employees *&employee, int &NumberOfEmployee) {
	string FIO;
	int press, personnelNumber;
	cout << "������� ��� ��������, ��� ��������� ����� ������ ��������.\n";
	cin >> FIO;
	FIO = enterStringWithSmallLetter(FIO);//�������� �� ���� � ��������� �����
	system("CLS");
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].FIO == FIO)
		{
			cout << "������� ����� ��������� �����: \n";

			cin >> personnelNumber;

			cout << "�� ������������� ������ ��������?\n1.��\n2.���\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49)
			{
				employee[i].personnelNumber = personnelNumber;
				system("CLS");
				cout << "�������������� ������� ���������.";
				Sleep(2000); system("CLS");
				return;
			}
			else return;
		}
	}
	cout << "��������! ������� �������� ��� � ���� ������\n";
	return;
}

void individualTask(employees *&employee, int &NumberOfEmployee)//�������������� �������
{
	int month, year;
	double pay, sum=0;
	cout << "������� �����: ";
	month=inputMonth();
	cout << "������� ���: ";
	year=inputYear();

	for (int i = 0; i < NumberOfEmployee; i++)
	{
		if ((employee[i].month == month) && (employee[i].year == year))
		{
			sum++;
			if (employee[i].numberOfHours > 144) {
				pay = (employee[i].oneHourPayment * 144 + (employee[i].numberOfHours - 144) * 2 * employee[i].oneHourPayment)* 0.88;
				cout << employee[i].FIO << "\t" << pay << endl;
			}
			else {
				pay = employee[i].oneHourPayment*employee[i].numberOfHours* 0.88;
				cout << employee[i].FIO << "\t" << pay << endl;
			}
			
		}
		pay = 0;
	}
	if (sum == 0)
	{
		cout << "����� �� ������� � ��� ������!\n";
		Sleep(2000); system("CLS");
		return;
	}
	
	
}

void menuRedactionEmployee(employees *&employee, int &NumberOfEmployee)//���� ��������������� �����������
{
	int press;
	do {
		cout << "\t\t\t\t\t****************************************\n"
			<< "\t\t\t\t\t*     1.���.        .                  *\n"
			<< "\t\t\t\t\t*     2.���.                           *\n"
			<< "\t\t\t\t\t*     3.������ �� ���.                 *\n"
			<< "\t\t\t\t\t*     4.���������� ������������� ����� *\n"
			<< "\t\t\t\t\t*     5.�����.                         *\n"
			<< "\t\t\t\t\t*     0.�����                          *\n"
			<< "\t\t\t\t\t****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 53));
		system("CLS");
		switch (press)
		{
		case 49:
			redactionFIO(employee, NumberOfEmployee); break;//�� ���
		case 50:
			redactionYear(employee, NumberOfEmployee); break;// �� ����
		case 51:
			redactionOneHourPayment(employee, NumberOfEmployee); break;//�� �����
		case 52:
			redactionNumberOfHours(employee, NumberOfEmployee); break; //�� ���-�� �����
		case 53:
			redactionMonth(employee, NumberOfEmployee); break;//�� ������
		case 48: system("CLS"); return;
		}
	} while (press != 53);
}

void employeesProcessing(employees *&employee, int &NumberOfEmployee)	//��������� ������ � �����������
{
	int press;
	do {
		cout << "\t\t\t\t\t*****************************************\n"
			<< "\t\t\t\t\t*               1. �����                *\n"
			<< "\t\t\t\t\t*             2. ����������             *\n"
			<< "\t\t\t\t\t*        3. �������������� �������      *\n"
			<< "\t\t\t\t\t*               0. �����                *\n"
			<< "\t\t\t\t\t*****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 51));
		system("CLS");
		switch (press)
		{
		case 48: return;
		case 49:
			menuSearch(employee, NumberOfEmployee);  break;//���� ������
		case 50:
			menuSorting(employee, NumberOfEmployee); break;//���� ����������
		case 51:
			individualTask(employee, NumberOfEmployee); break;//�������. �������
		}

	} while (press != 48);

}

void editDataAboutEmployee(employees *&employee, int &NumberOfEmployee)	//�������������� ������ � �����������
{
	int press;
	do {
		cout << "\t\t\t\t\t*****************************************\n"
			<< "\t\t\t\t\t*              1. ��������.             *\n"
			<< "\t\t\t\t\t*           2. ��������������.          *\n"
			<< "\t\t\t\t\t*             3. ����������.            *\n"
			<< "\t\t\t\t\t*              4. ��������.             *\n"
			<< "\t\t\t\t\t*               0. �����.               *\n"
			<< "\t\t\t\t\t*****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 52));
		system("CLS");
		switch (press)
		{
		case 48: return;
		case 49:
			ViewEmployee(employee, NumberOfEmployee);  break;//��������
		case 50:
			menuRedactionEmployee(employee, NumberOfEmployee);//���� �������������� �����������
			break;
		case 51:
			addingNewEmployeeData(employee, NumberOfEmployee); break;//���������� �����������
		case 52:
			deleteEmployeeData(employee, NumberOfEmployee); break;//�������� �����������
		}
		if (press != 49 && press != 48) {
			InputAllInformationAboutEmployeeDataInFile(employee, NumberOfEmployee);//���������� � ����
		}

	} while (press != 48);
}

void activationAccounts(users *&user, int numberOfUsers)//��������� ���������
{
	int press, t = 0;
	for (int i = 0; i < numberOfUsers; i++) {
		if (user[i].code == 0) {
			t++;
			cout << user[i].login << " ������ ������������������\n"
				<< "������������ �������?\n1.��\n2.���\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49) user[i].code = 1;
			else user[i].code = 4;
			system("CLS");
		}
		if (user[i].code == 3) {
			t++;
			cout << user[i].login << " ������ ������������������ ��� �������������.\n"
				<< "������������ �������?\n1.��\n2.���\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49) user[i].code = 2;
			else user[i].code = 4;
			system("CLS");
		}
	}
	if (!t) cout << "����� �� �����������������\n";
	return;
}

void redactionLogin(users *&user, int numberOfUsers)//�������������� �����
{
	string login, login1;
	int press, s = 0;
	bool flag = true;
	cout << "������� �����, ������� �� ������ ��������: ";
	cin >> login;
	for (int i = 0; i < numberOfUsers; i++) {
		if (user[i].login == login) {
			s++;
			do {
				cout << "�� ����� ����� �� ������ ��������: ";
				login1 = inputFIO();
				for (int i = 0; i < numberOfUsers; i++) {
					if (login1 == user[i].login) {
						cout << "����� ����� ��� ����������.\n";
						flag = false;
						break;
					}
					else flag = true;
				}
			} while (flag == false);

			cout << "�� �������, ��� ������ �������� �����.\n1.��\n2.���\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49) {
				user[i].login = login1;
				system("CLS");
				cout << "�������������� ������� ���������.";
				Sleep(2000); system("CLS");
				return;
			}
			else return;
		}
	}
	if (!s) {
		cout << "����� �� ������.\n";
		return;
	}
}

void redactionPassword(users *&user, int numberOfUsers)			//������ ������� ������ �� �����
{
	int press, s = 0;
	string login, password, salt, saltedPassword;
	cout << "������� ����� ������������, ��� ������ ������ ��������.";
	cin >> login;
	for (int i = 0; i < numberOfUsers; i++) {
		if (user[i].login == login) {
			s++;
			password = inputPassword();
			salt = user[i].salt;
			saltedPassword = generationHashPassword(password + salt);
			cout << "\n�� �������, ��� ������ �������� ������.\n1.��\n2.���\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49) {
				user[i].saltedPassword = saltedPassword;
				system("CLS");
				InputAllInformationAboutAccountsInFile(user, numberOfUsers);
				cout << "�������������� ������� ���������.";
				Sleep(2000); system("CLS");
				return;
			}
			else return;
		}
	}
	if (!s) {
		cout << "����� �� ������.\n";
		return;
	}
}

void addingNewUsers(users *&user, int &numberOfUsers)//���������� ������ ������������(���������������)
{
	string login, password, salt, saltedPassword;
	int kod = 1, press;
	ofstream fadd(FILE_ACCOUNT, ios::app);
	do {
		system("CLS");
		login = inputLogin(user);
		password = inputPassword();
		saltedPassword = generationHashPassword(password + salt);
		fadd << setw(20) << left << login << setw(20) << salt << setw(70) << saltedPassword << setw(5) << left << kod << endl;
		cout << "\n������� �� �� ���������� ���������� ���������\n1.��\n2.���\n";
		do {
			press = _getch();
		} while (press != 49 && press != 50);

	} while (press != 50);
	fadd.close();
	cout << "���������� ��������� �������!!";
	Sleep(2000);
	numberOfUsers = listUsers(user);
	system("CLS");
}

void viewLoginsPassword(users *user, int numberOfUsers)//����� ������� � �������
{
	cout << "-----------------------------------------------------------------\n"
		<< "|         �����        |            ������              |  ���  |\n"
		<< "-----------------------------------------------------------------\n";
	for (int i = 0; i < numberOfUsers; i++)
	{
		cout << "| " << setw(20) << left << user[i].login << " | " << setw(30) << left << user[i].password << " | "
			<< setw(5) << left << user[i].code << " | " << endl;
		cout << "-----------------------------------------------------------------\n";
	}
}

void redactionLoginPassword(users *&user, int numberOfUsers)//�������������� ������ � ������
{
	int press;
	cout << "\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t*****************************************\n"
		<< "\t\t\t\t\t*       1. �������������� ������.       *\n"
		<< "\t\t\t\t\t*       2. �������������� ������.       *\n"
		<< "\t\t\t\t\t*               0. �����                *\n"
		<< "\t\t\t\t\t*****************************************\n";
	do {
		press = _getch();
	} while (!(press >= 48 && press <= 50));
	system("CLS");
	switch (press)
	{
	case 50: redactionLogin(user, numberOfUsers); break;
	case 49: redactionPassword(user, numberOfUsers); break;
	case 48: break;
	}

}

void deleteAccounts(users *&user, int &numberOfUsers)//�������� ��������� �������������
{
	int s = -1, press;
	string login;
	cout << "������� ����� ��������, ������� �� ������ �������: ";
	cin >> login;
	for (int i = 0; i < numberOfUsers; i++) {
		if (user[i].login == login) {
			if (user[i].code == 2) s = -2;
			else s = i;
			break;
		}
	}
	//system("CLS");
	if (s == -2)
	{
		cout << "��� ������� ��������������. �� �� ������ ��� �������!!\n";
		return;
	}
	if (s == -1)
		cout << "������ ������� �� ������.\n";
	else {
		cout << "�� ������������� ������ ������� ������?\n1.��\n2.���\n";
		do {
			press = _getch();
		} while (press != 49 && press != 50);
		if (press == 49)
		{

			for (int i = s; i < numberOfUsers - 1; i++)
				user[i] = user[i + 1];
			numberOfUsers--;
			cout << "�������� �������� ��������� �������!\n";
			viewLoginsPassword(user, numberOfUsers);
			return;
		}
		else return;
	}
}

void menuWorkWithDataEmployee(employees *&employee, int &NumberOfEmployee)//���� ��� ������ � �������(�������������)
{
	int press;

	do {
		cout << "\t\t\t\t\t*****************************************\n"
			<< "\t\t\t\t\t*           1. ��������������           *\n"
			<< "\t\t\t\t\t*             2. ���������              *\n"
			<< "\t\t\t\t\t*               0. �����                *\n"
			<< "\t\t\t\t\t*****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 50));
		system("CLS");
		switch (press)
		{
		case 48: return;
		case 50:
			employeesProcessing(employee, NumberOfEmployee); break;
		case 49:
			editDataAboutEmployee(employee, NumberOfEmployee); break;
		}

	} while (press != 48);

}

void menuWorkWithAccounts(users *&user, int &numberOfUsers)//���� ��� ���������� ��. ��������(�������������)
{
	int press;
	do {
		cout << "\t\t\t\t\t*****************************************\n"
			<< "\t\t\t\t\t*              1. ��������.             *\n"
			<< "\t\t\t\t\t*         2. ��������� ���������.       *\n"
			<< "\t\t\t\t\t*           3. ��������������.          *\n"
			<< "\t\t\t\t\t*              4. ��������.             *\n"
			<< "\t\t\t\t\t*              5. ��������.             *\n"
			<< "\t\t\t\t\t*                0. �����               *\n"
			<< "\t\t\t\t\t*****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 53));
		system("CLS");
		switch (press)
		{
		case 49:
			viewLoginsPassword(user, numberOfUsers); break;
		case 50:
			activationAccounts(user, numberOfUsers); break;
		case 51:
			redactionLoginPassword(user, numberOfUsers); break;
		case 52:
			addingNewUsers(user, numberOfUsers); break;
		case 53:
			deleteAccounts(user, numberOfUsers); break;
		case 48: return;
		}
		if (press != 48 && press != 49)
		{
			InputAllInformationAboutAccountsInFile(user, numberOfUsers);
		}
	} while (press != 48);
}

void menuAdmin(users *&user, employees *&employee)//���� ��������������
{
	int press, numberOfUsers = listUsers(user);
	int NumberOfEmployee = listEmployeeData(employee);
	do {
		cout << "\n\n\n\n\t\t\t\t\t\t    ���� ��������������";
		cout << "\n\n";
		cout << "\t\t\t\t\t*****************************************\n"
			<< "\t\t\t\t\t*     1. ������ � �������� ��������     *\n"
			<< "\t\t\t\t\t*         2. ������ � �������           *\n"
			<< "\t\t\t\t\t*              0. �����                 *\n"
			<< "\t\t\t\t\t*****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 50));
		system("CLS");
		switch (press)
		{
		case 49:
			menuWorkWithAccounts(user, numberOfUsers);
			break;
		case 50:
			menuWorkWithDataEmployee(employee, NumberOfEmployee);
			break;
		case 48: return;
		}
	} while (press != 48);
}
