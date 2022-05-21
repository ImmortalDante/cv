#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>
#include<Windows.h>
#include<iomanip>
#include"Admin.h"
#include"File.h"
#include "sha256.h"


using namespace std;

string inputPasswordStars()            //���� ������ ����������
{
	string s;
	int i = 0;
	int ch = 0;
	while (1) {

		ch = _getch();
		if ((ch >= 'a'&& ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {		//��������� ������� ��� �����
			s += (char)ch; i++;
			cout << "*";
			continue;
		}
		if (ch == 13) break;
		if (ch == 8) {						//�������� �������
			if (i > 0) {
				cout << "\b \b";
				i--;
				s.erase(i, 1);				//�������� 1 ������� c i �������
			}
		}
	}
	return s;
}

string passwordTest()                              //�������� ������ �� ������������ �����
{
	string s;
	int l, j = 0, k = 0;
	bool flag = false;
	do {
		s = inputPasswordStars();
		l = s.length();
		for (int i = 0; i < l; i++) {
			if (s[i] >= 'a'&& s[i] <= 'z') continue;
			if (s[i] >= 'A' && s[i] <= 'Z') {
				j++; continue;
			}
			if (s[i] >= '0' && s[i] <= '9') {
				k++;
			}
		}
		if (k == 0 || j == 0) {
			cout << "\n�������� ���� ������! ��������� ����!!\n";
			flag = false;
		}
		else flag = true;
	} while (flag == false);
	return s;
}

bool loginTest(string login)		// �������� �� ������������ ����� ������
{
	int l;
	l = login.length();
	if (l > 20) {
		system("CLS");
		cout << "����� ������� �������.\n";
		return false;
	}
	else
	{
		for (int i = 0; i < l; i++) {
			if (login[i] == ' ' || (!(login[i] >= 'a'&& login[i] <= 'z')
				&& !(login[i] >= 'A' && login[i] <= 'Z')
				&& !(login[i] >= '0' && login[i] <= '9'))) return false;
		}
		return true;
	};
}

string inputLogin(users *&user)				//���� ������ � ��������� �� ������������
{
	int numberOfUsers;
	string login;
	bool flag;
	numberOfUsers = listUsers(user);	//��������� � ������ ������ � �������������
	do {
		flag = false;
		while (flag == false) {
			cout << "����� ��� �������� ���������� ������� � �� ������ 20 ��������\n";
			cout << "������� �����: ";
			cin >> login;
			flag = loginTest(login);
		}
		for (int i = 0; i < numberOfUsers; i++) {	//��������� � �������������
			if (login == user[i].login) {
				system("CLS");
				cout << "����� ����� ��� ����������.\n";
				flag = false;
				break;
			}
		}
	} while (flag == false);
	return login;
}

string inputPassword()					// ���� ������ � ��������� ��� ������
{
	string password, password1;
	bool flag;
	do {
		cout << "\n���������� ������. �� ������ �������� �� ���� ���������� ��������, �� ������� ���� �� ���� ������������, � ����\n";
		password = passwordTest();
		cout << "\n��� ������������� ��������� ���� ������: \n";		//��������� ���� ������ ��� �������������
		password1 = inputPasswordStars();
		if (password != password1) {
			system("CLS");
			cout << "������ �� ���������. ��������� ���� �������.\n";
			flag = false;
		}
		else flag = true;
	} while (flag == false);
	return password;
}

void registration(users *&user)									// ����������� ����������� ��� ��������������
{
	string login, password, salt, saltedPassword;
	int code, press;
	bool flag = true;
	system("CLS");
	cout << "\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t****************************************\n"
		<< "\t\t\t\t\t*               ��� ��?                *\n"
		<< "\t\t\t\t\t*         1.����� �������������.       *\n"
		<< "\t\t\t\t\t*         2.����� ������������.        *\n"
		<< "\t\t\t\t\t*              0.�����                 *\n"
		<< "\t\t\t\t\t****************************************\n";
	do {
		press = _getch();
	} while (press != 49 && press != 50 && press != 48);
	system("CLS");
	if (press == 49)
		code = 3;
	else if (press == 50)
		code = 0;
	else return;
	login = inputLogin(user);
	salt = generationSalt();
	password = inputPassword();
	saltedPassword = generationHashPassword(password + salt);
	system("CLS");
	addToFileOneAccount(login, salt, saltedPassword, code);			//������ � ���� ������ ������������
	cout << "������� �� �����������. � ������ ������� ������������� ���������� ���� �����������.";
	Sleep(3000);
	return;
}

int stringComparison(string s, string a)			//��������� ���� �����
{
	int l, l1;
	l = s.length();
	l1 = a.length();
	if (l != l1) return 0;
	else
	{
		for (int i = 0; i < l; i++) {
			if (s[i] == a[i])
				continue;
			else return 0;
		}
		return 1;
	}
}

int searchLoginPassword(users *&user, int numberOfUsers, int &number_of_attempts, string login, string password)//����������� ������ � ������
{
	int d;
	for (int i = 0; i < numberOfUsers; i++) {
		if (user[i].login == login)					//������� ���� ����� 
		{
			number_of_attempts++;
			d = stringComparison(user[i].password, password); // ���������� ������
			if (d == 0) {
				system("CLS");
				cout << "����� ��� ������ ������� �������!\n��������� ����.\n";
				return 3;
			}
			else {
				if (user[i].code == 4) {
					system("CLS");
					cout << "��� ������� �������������! ���������� ������������������ ��� ���.";
					Sleep(2000);
					return 4;
				}
				if (user[i].code == 2) return 2;  //��� ��������������
				if (user[i].code == 1) return 1; //��� ������������
				if (user[i].code == 0 || user[i].code == 3)  //��� ���������������� �����������
				{
					system("CLS");
					cout << "������� �� �����������";
					Sleep(2000);
					return 0;
				}
			}
		}
	}
	number_of_attempts = 0;
	if (number_of_attempts == 0) {
		system("CLS");
		cout << "����� ������ �������!\n��������� ����.\n";
		return 3;
	}
}

void searchSaltByLogin(users*& user, int numberOfUsers, string login, string& salt) 
{
	for (int i = 0; i < numberOfUsers; i++)
	{
		if (user[i].login == login)
		{
			salt = user[i].salt;
		}
	}
}

int entrance(users *&user)						//�����������
{
	string password, login, salt, saltedPassword;
	int d = 0, press, numberOfAttempts = 0, numberOfUsers;
	bool flag;
	numberOfUsers = listUsers(user);
	cout << "\t\t\t\t\t\t    �����������\n";
	do {
		cout << "������� �����: ";
		cin >> login;
		cout << "������� ������: ";
		password = inputPasswordStars();
		searchSaltByLogin(user, numberOfUsers, login, salt);
		saltedPassword = generationHashPassword(password + salt);
		flag = true;
		d = searchLoginPassword(user, numberOfUsers, numberOfAttempts, login, saltedPassword);
		if (d == 1) return 1;
		if (d == 2) return 2;
		if (d == 3) flag = false;
		if (numberOfAttempts == 3) {
			system("CLS");
			cout << "\n������� �� �� ������� ������.\n1.��\n2.���\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			system("CLS");
			if (press == 49) redactionPassword(user, numberOfUsers);
			else numberOfAttempts = 0;
		}
	} while (flag == false);
}

int registrationAndAuthorization(users *&login, int &press)   //���� ����������� � �����������
{
	int choice;
	do {
		cout << "\n\n\n\n\t\t\t\t\t\t     ������� ����";
		cout << "\n\n";
		cout << "\t\t\t\t\t****************************************\n"
			<< "\t\t\t\t\t*            1.�����������             *\n"
			<< "\t\t\t\t\t*            2.�����������             *\n"
			<< "\t\t\t\t\t*              0. �����                *\n"
			<< "\t\t\t\t\t****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 50));
		system("CLS");
		switch (press)
		{
		case 48: return press; break;
		case 49:
			registration(login); //�����������
			system("CLS");
			break;
		case 50:
			press = entrance(login);  // �����������
			//system("CLS");
			return press;
		}
	} while (press != 48);
}