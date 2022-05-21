#pragma once
#include"Admin.h"

using namespace std;

string inputPasswordStars();//ввод пароля звёздачками
string passwordTest();//проверка на правильный ввод пароля
bool loginTest(string login);//проверка на ввод логина
string inputLogin(users *&user);//ввод логина
string inputPassword();//ввод пароля с подтверждением
void registration(users *&user);//Регистрация нового пользователя
int stringComparison(string s, string a);//сравнение двух паролей
int searchLoginPassword(users *&user, int numberOfUsers, int &number_of_attempts, string login, string password);// Поиск логина и пароля.Определение пользователя или администратора.
int entrance(users *&user);// Авторизация
int registrationAndAuthorization(users *&user, int&press);//Выбор авторизация или регистрация.
void searchSaltByLogin(users*& user, int numberOfUsers, string login, string& salt);//поиск соли по логину
