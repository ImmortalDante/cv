#pragma once
#include"Admin.h"

using namespace std;

string inputPasswordStars();//���� ������ ����������
string passwordTest();//�������� �� ���������� ���� ������
bool loginTest(string login);//�������� �� ���� ������
string inputLogin(users *&user);//���� ������
string inputPassword();//���� ������ � ��������������
void registration(users *&user);//����������� ������ ������������
int stringComparison(string s, string a);//��������� ���� �������
int searchLoginPassword(users *&user, int numberOfUsers, int &number_of_attempts, string login, string password);// ����� ������ � ������.����������� ������������ ��� ��������������.
int entrance(users *&user);// �����������
int registrationAndAuthorization(users *&user, int&press);//����� ����������� ��� �����������.
void searchSaltByLogin(users*& user, int numberOfUsers, string login, string& salt);//����� ���� �� ������
