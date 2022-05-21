#include<iostream>
#include<conio.h>
#include<iomanip>
#include<string>
#include"Admin.h"
#include"File.h"

using namespace std;

void ViewEmployee(employees *employee, int NumberOfEmployee)//�������� �����������
{
	cout << "----------------------------------------------------------------------------------------\n"
		<< " � |        ���       |   ��������� �����   |     ���    |  �����  |���.�����|  �����  |\n"
		<< "----------------------------------------------------------------------------------------\n";

	for (int i = 0; i < NumberOfEmployee; i++) {
		cout << " " << i + 1 << " | " << setw(16) << left << employee[i].FIO << " | "
			<< setw(20) << left << employee[i].personnelNumber << " | "
			<< setw(10) << left << employee[i].year << " | "
			<< setw(7) << left << employee[i].month << " | "
			<< setw(7) << left << employee[i].numberOfHours << " | "
			<< setw(7) << left << employee[i].oneHourPayment << " |" << endl;
		cout << "----------------------------------------------------------------------------------------\n";
	}
}

void ViewSearch(employees *employee, int k, int i)//�������� ��� ������
{
	if (k == 1) {
		cout << "-------------------------------------------------------------------------------------\n"
			<< "|        ���       |   ��������� �����   |     ���    |  �����  |���.�����|  �����  |\n"
			<< "------------------------------------------------------------------------------------\n";
		cout << "| " << setw(16) << left << employee[i].FIO << " | "
			<< setw(20) << left << employee[i].personnelNumber << " | "
			<< setw(10) << left << employee[i].year << " | "
			<< setw(7) << left << employee[i].month << " | "
			<< setw(7) << left << employee[i].numberOfHours << " | "
			<< setw(7) << left << employee[i].oneHourPayment << " |" << endl;
		cout << "----------------------------------------------------------------------------------------\n";
	}
	else {
		cout << "| " << setw(16) << left << employee[i].FIO << " | "
			<< setw(10) << left << employee[i].year << " | "
			<< setw(7) << left << employee[i].month << " | "
			<< setw(7) << left << employee[i].numberOfHours << " | "
			<< setw(7) << left << employee[i].oneHourPayment << " |" << endl;
		cout << "----------------------------------------------------------------------------------------\n";
	}
}

string enterStringWithSmallLetter(string FIO)//���� ������ � ��������� �����
{
	int a;
	if (FIO[0] >= (char)97 && FIO[0] <= 122) {
		a = (int)FIO[0] - 32;
		FIO[0] = (char)a;
	}
	return FIO;
}

void searchFIO(employees *employee, int NumberOfEmployee)//����� �� ���
{
	string FIO;
	int k = 0;
	cout << "������� ��� ��������: ";
	cin >> FIO;
	FIO = enterStringWithSmallLetter(FIO);
	system("CLS");
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].FIO == FIO)
		{
			k++;
			ViewSearch(employee, k, i);
			return;
		}
	}
	cout << "������ �� �������!\n";
	return;
}

void searchYear(employees *employee, int NumberOfEmployee)//����� �� ����
{
	int year;
	int k = 0;
	cout << "������� ���, �� ������� �� ������ ����� ����������: \n";
	year = inputYear();
	system("CLS");
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].year == year)
		{
			k++;
			ViewSearch(employee, k, i);
		}
	}

	if (k == 0) {
		cout << "������ �� �������!\n";
		return;
	}
	else return;
}

void searchOneHourPayment(employees *employee, int NumberOfEmployee)//����� �� ������������� �����
{
	int oneHourPayment;
	int k = 0;
	cout << "������� ���������� ������������� �����: \n";
	oneHourPayment = inputInt();
	system("CLS");
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].oneHourPayment <= oneHourPayment)
		{
			k++;
			ViewSearch(employee, k, i);
		}
	}
	if (k == 0) {
		cout << "��������! ��� ���� ����������� ������ ��� "<< oneHourPayment <<" ���� \n";
		return;
	}
	else return;
}

void searchMonth(employees *employee, int NumberOfEmployee)//����� �� ������
{
	int month;
	int k = 0;
	cout << "������� �����: ";
	month=inputMonth();
	//system("CLS");
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].month == month)
		{
			k++;
			ViewSearch(employee, k, i);
		}
	}
	if (k == 0) {
		cout << "� ���� ������ ����� �� �����!\n";
	}
}

void sortingFIO(employees *employee, int NumberOfEmployee)//���������� �� ���
{
	employees s;
	for (int i = 0; i < NumberOfEmployee - 1; i++)
		for (int j = i; j < NumberOfEmployee; j++)
			if (employee[i].FIO > employee[j].FIO)
			{
				s = employee[i];
				employee[i] = employee[j];
				employee[j] = s;
			}
	ViewEmployee(employee, NumberOfEmployee);
}

void sortingYear(employees *employee, int NumberOfEmployee)//���������� �� ����
{
	employees s;
	for (int i = 0; i < NumberOfEmployee - 1; i++)
		for (int j = i; j < NumberOfEmployee; j++)
			if (employee[i].year > employee[j].year)
			{
				s = employee[i];
				employee[i] = employee[j];
				employee[j] = s;
			}
	ViewEmployee(employee, NumberOfEmployee);
}

void sortingOneHourPayment(employees *employee, int NumberOfEmployee)//���������� �������� �� �� ���
{
	employees s;
	for (int i = 0; i < NumberOfEmployee - 1; i++)
		for (int j = i; j < NumberOfEmployee; j++)
			if (employee[i].oneHourPayment > employee[j].oneHourPayment)
			{
				s = employee[i];
				employee[i] = employee[j];
				employee[j] = s;
			}
	ViewEmployee(employee, NumberOfEmployee);
}

void sortingNumberOfHours(employees *employee, int NumberOfEmployee)//����. �� ���-�� �����
{
	employees s;
	for (int i = 0; i < NumberOfEmployee - 1; i++)
		for (int j = i; j < NumberOfEmployee; j++)
			if (employee[i].numberOfHours > employee[j].numberOfHours)
			{
				s = employee[i];
				employee[i] = employee[j];
				employee[j] = s;
			}
	ViewEmployee(employee, NumberOfEmployee);
}

void menuSearch(employees *employee, int NumberOfEmployee)//���� ������
{
	int press;
	do {
		cout << "\t\t\t\t\t****************************************\n"
			<< "\t\t\t\t\t*      1.�� ���.                       *\n"
			<< "\t\t\t\t\t*      2.�� ����.                      *\n"
			<< "\t\t\t\t\t*      3.�� ������ �� ���� ���.        *\n"
			<< "\t\t\t\t\t*      4.�� ������.                    *\n"
			<< "\t\t\t\t\t*      0.�����                         *\n"
			<< "\t\t\t\t\t****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 52));
		system("CLS");
		switch (press)
		{
		case 49:
			searchFIO(employee, NumberOfEmployee); break;
		case 50:
			searchYear(employee, NumberOfEmployee); break;
		case 51:
			searchOneHourPayment(employee, NumberOfEmployee); break;
		case 52:
			searchMonth(employee, NumberOfEmployee); break;
		case 48: system("CLS"); return;
		}
	} while (press != 48);
}

void menuSorting(employees *employee, int NumberOfEmployee)//���� ����������
{
	int press;
	do {
		cout << "\t\t\t\t\t****************************************\n"
			<< "\t\t\t\t\t*   1.�� ���.                           *\n"
			<< "\t\t\t\t\t*   2.�� ����.                          *\n"
			<< "\t\t\t\t\t*   3.�� ������ �� ���.                *\n"
			<< "\t\t\t\t\t*   4.�� ���������� ������������� ����� *\n"
			<< "\t\t\t\t\t*   0.�����                             *\n"
			<< "\t\t\t\t\t****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 52));
		system("CLS");
		switch (press)
		{
		case 49:sortingFIO(employee, NumberOfEmployee); break;
		case 50:
			sortingYear(employee, NumberOfEmployee); break;
		case 51:
			sortingOneHourPayment(employee, NumberOfEmployee); break;
		case 52:
			sortingNumberOfHours(employee, NumberOfEmployee);
			break;
		case 48: system("CLS"); return;
		}
	} while (press != 48);
}

void menuUsers(employees *&employee)//���� ������������
{
	int press, NumberOfEmployee;
	cout << "\n\n\n\n\t\t\t\t\t\t    ���� ������������\n\n";
	do {
		cout << "\t\t\t\t\t****************************************\n"
			<< "\t\t\t\t\t*      1.�������� ���� �����������.     *\n"
			<< "\t\t\t\t\t*       2.�������������� �������.       *\n"
			<< "\t\t\t\t\t*              3.�����.                 *\n"
			<< "\t\t\t\t\t*            4.����������.              *\n"
			<< "\t\t\t\t\t*               0.�����                 *\n"
			<< "\t\t\t\t\t****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 53));

		NumberOfEmployee = listEmployeeData(employee);
		system("CLS");
		switch (press)
		{
		case 49:
			ViewEmployee(employee, NumberOfEmployee);  break;
		case 50:
			individualTask(employee, NumberOfEmployee); break;
		case 51:
			menuSearch(employee, NumberOfEmployee); break;
		case 52:
			menuSorting(employee, NumberOfEmployee); break;
		case 48:system("CLS"); return;
		}
	} while (press != 54);
}