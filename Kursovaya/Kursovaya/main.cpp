#include<iostream>
#include"Authorization.h"
#include"Users.h"
#include"Admin.h"

using namespace std;


int main()
{
	setlocale(LC_ALL, "rus");
	users *user;
	employees *employee;
	int choice;
	do {
		registrationAndAuthorization(user, choice);// ����������� � �����������
		if (choice == 2)	menuAdmin(user, employee);			//���� ������
		else if (choice == 1) menuUsers(employee);				//���� ������������
	} while (choice != 48);
}