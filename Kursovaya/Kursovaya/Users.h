#pragma once
#include"Admin.h"

using namespace std;

void sortingFIO(employees *employee, int NumberOfEmployee);//���������� �� ���
void sortingNumberOfHours(employees *employee, int NumberOfEmployee);//����. �� ���-�� ������������� �����
void ViewSearch(employees *, int k, int);//�������� ��� ������
void sortingOneHourPayment(employees *employee, int NumberOfEmployee);//���������� �� ������
void sortingYear(employees *employee, int NumberOfEmployee);//���������� �� ����
void ViewEmployee(employees *employee, int NumberOfEmployee);//�������� �����������
void searchFIO(employees *employee, int NumberOfEmployee);//����� �� ���
void searchYear(employees *employee, int NumberOfEmployee);//����� �� ����
void searchOneHourPayment(employees *employee, int NumberOfEmployee);//����� �� ������
void searchMonth(employees *employee, int NumberOfEmployee);//����� �� ������
void menuSearch(employees *employee, int NumberOfEmployee);//���� ������
void menuSorting(employees *employee, int NumberOfEmployee);//���� ����������
void menuUsers(employees *&employee);//���� ������������
string enterStringWithSmallLetter(string FIO); //���� ������ � ��������� �����