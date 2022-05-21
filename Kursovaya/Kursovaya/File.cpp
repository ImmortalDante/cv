#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include"Admin.h"
#include"File.h"


using namespace std;


int listEmployeeData(employees *&employee)//вывод информации из файла в массив с сотрудниками
{
	ifstream fin;
	fin.open(FILE_LIST, ofstream::in);
	char str[100];
	int kol = 0;
	for (; fin.getline(str, 100); kol++);
	fin.close();
	fin.open(FILE_LIST, ifstream::in);
	employee = new employees[kol];
	for (int i = 0; i < kol; i++)
	{
		fin >> employee[i].FIO
			>> employee[i].personnelNumber
			>> employee[i].year
			>> employee[i].month
			>> employee[i].numberOfHours
			>> employee[i].oneHourPayment;
	}
	fin.close();
	return kol;
}

int listUsers(users *&user)		//Чтение информации из файла с логином и паролем
{
	ifstream fin;
	fin.open(FILE_ACCOUNT, ofstream::in);
	char str[90];
	int kol = 0;
	for (; fin.getline(str, 90); kol++);
	fin.close();
	fin.open(FILE_ACCOUNT, ifstream::in);
	user = new users[kol];
	for (int i = 0; i < kol; i++)
	{
		fin >> user[i].login;
		fin >> user[i].salt;
		fin >> user[i].password;
		fin >> user[i].code;
	}
	fin.close();
	return kol;
}

void addToFileOneAccount(string login, string salt, string saltedPassword, int code)//добавление в конец файла одной записи
{
	ofstream fadd(FILE_ACCOUNT, ios::app);
	fadd << setw(20) << left << login << setw(20) << salt << setw(70) << saltedPassword << setw(5) << left << code << endl;
	fadd.close();
}

void InputAllInformationAboutAccountsInFile(users *user, int numberOfUsers)//перезапись файла с логинами и паролями
{
	ofstream fadd(FILE_ACCOUNT);
	for (int i = 0; i < numberOfUsers; i++) {
		fadd << setw(20) << left << user[i].login << setw(30) << user[i].password << setw(5) << left << user[i].code << endl;
	}
	fadd.close();
}

void InputAllInformationAboutEmployeeDataInFile(employees *employee, int NumberOfEmployee)//перезапись файла с бсотрудниками
{
	ofstream fout(FILE_LIST);
	for (int i = 0; i < NumberOfEmployee; i++) {
		fout << setw(25) << left << employee[i].FIO
			<< setw(20) << left << employee[i].personnelNumber
			<< setw(7) << left << employee[i].year
			<< setw(5) << left << employee[i].month
			<< setw(7) << left << employee[i].numberOfHours
			<< setw(5) << left << employee[i].oneHourPayment << endl;
	}
	fout.close();
}