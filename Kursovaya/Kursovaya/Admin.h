#pragma once

using namespace std;

struct users
{
	string login;//�����
	string password;//������
	string salt;//����
	string saltedPassword;//������ � �����
	int code;//����
};

struct employees
{
	string FIO; //��� 
	string personnelNumber;//��������� �����
	int year; //���
	int month;//�����
	int numberOfHours;// ������ �� ���
	double oneHourPayment;// ���-�� �����

};


void menuAdmin(users *&user, employees *&employee);//���� ��������������
void menuWorkWithDataEmployee(employees *&employee, int &NumberOfEmployee);//���� ��� ������ � �������(�������������)
void menuWorkWithAccounts(users *&user, int &numberOfUsers);//���� ��� ���������� ��. ��������(�������������)
void employeesProcessing(employees *&employee, int &NumberOfEmployee);//���� ��� ��������� ������(�������������)
void editDataAboutEmployee(employees *&employee, int &NumberOfEmployee);//���� ��� �������������� ������ (�������������)
void redactionLoginPassword(users *&user, int numberOfUsers);//���� ��� �������������� ������ � ������
void redactionLogin(users *&user, int numberOfUsers);//�������������� ������
void redactionPassword(users *&user, int numberOfUsers);//�������������� ������
void deleteAccounts(users *&user, int &numberOfUsers);//�������� ���������
void viewLoginsPassword(users *user, int numberOfUsers);//�������� ������� � �������
void addingNewUsers(users *&user, int &numberOfUsers);//���������� ������ ������������
void activationAccounts(users *&user, int numberOfUsers);//��������� ����� ���������
void addingNewEmployeeData(employees *&employee, int &NumberOfEmployee);//���������� ������ ���������
void deleteEmployeeData(employees *&employee, int &NumberOfEmployee);//�������� ����������
void redactionFIO(employees *&employee, int &NumberOfEmployee);//�������������� ���
void redactionYear(employees *&employee, int &NumberOfEmployee);//�������������� ����
void redactionNumberOfHours(employees *&employee, int &NumberOfEmployee);//�������������� ���������� �����
void redactionOneHourPayment(employees *&employee, int &NumberOfEmployee);//�������������� ������
void redactionMonth(employees *&employee, int &NumberOfEmployee);//�������������� ������
void redactionPersonnelNumber(employees *&employee, int &NumberOfEmployee);//�������������� ������
void individualTask(employees *&employee, int &NumberOfEmployee);//�������������� �������
void menuRedactionEmployee(employees *&employee, int &NumberOfEmployee);//���� ��� �������������� ������ � ����������
int inputInt();//���� ������ �����
double inputDouble();//���� �������� �����
string inputFIO();//�������� �� ���� ��������
int inputYear();//�������� �� ���� ����
int inputMonth();//�������� �� ���� ������


