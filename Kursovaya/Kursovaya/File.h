#pragma once
#include"Admin.h"


const string FILE_ACCOUNT = "user.txt";
const string FILE_LIST = "employee.txt";

using namespace std;

int listEmployeeData(employees *&employee);//����� ���������� �� ����� � ������ � ������������
int listUsers(users *&user);//������ ���������� �� ����� � ������� � �������
void addToFileOneAccount(string login, string salt, string saltedPassword, int code);//���������� � ����� ����� ����� ������
void InputAllInformationAboutAccountsInFile(users *user, int numberOfUsers);//���������� ����� � �������� � ��������
void InputAllInformationAboutEmployeeDataInFile(employees *employee, int NumberOfEmployee);//���������� ����� � ������������
