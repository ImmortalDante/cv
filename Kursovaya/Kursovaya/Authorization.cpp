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

string inputPasswordStars()            //Ввод пароля звёздочками
{
	string s;
	int i = 0;
	int ch = 0;
	while (1) {

		ch = _getch();
		if ((ch >= 'a'&& ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {		//возможные символы для ввода
			s += (char)ch; i++;
			cout << "*";
			continue;
		}
		if (ch == 13) break;
		if (ch == 8) {						//удаление символа
			if (i > 0) {
				cout << "\b \b";
				i--;
				s.erase(i, 1);				//удаление 1 символа c i позиции
			}
		}
	}
	return s;
}

string passwordTest()                              //Проверка пароля на правильность ввода
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
			cout << "\nНеверный ввод пароля! Повторите ввод!!\n";
			flag = false;
		}
		else flag = true;
	} while (flag == false);
	return s;
}

bool loginTest(string login)		// проверка на правильность ввода логина
{
	int l;
	l = login.length();
	if (l > 20) {
		system("CLS");
		cout << "Логин слишком длинный.\n";
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

string inputLogin(users *&user)				//Ввод пароля с проверкой на уникальность
{
	int numberOfUsers;
	string login;
	bool flag;
	numberOfUsers = listUsers(user);	//занесение в массив данных о пользователей
	do {
		flag = false;
		while (flag == false) {
			cout << "Логин без пробелов латинскими буквами и не больше 20 символов\n";
			cout << "Введите логин: ";
			cin >> login;
			flag = loginTest(login);
		}
		for (int i = 0; i < numberOfUsers; i++) {	//сравнение с существующими
			if (login == user[i].login) {
				system("CLS");
				cout << "Такой логин уже существует.\n";
				flag = false;
				break;
			}
		}
	} while (flag == false);
	return login;
}

string inputPassword()					// Ввод пароля с повторным его вводом
{
	string password, password1;
	bool flag;
	do {
		cout << "\nПридумайте пароль. Он должен состоять из букв латинского алфавита, из которых хотя бы одна пропрописная, и цифр\n";
		password = passwordTest();
		cout << "\nДля подтверждения повторите ввод пароля: \n";		//повторный ввод пароля для подтверждения
		password1 = inputPasswordStars();
		if (password != password1) {
			system("CLS");
			cout << "Пароли не совпадают. Повторите ввод паролей.\n";
			flag = false;
		}
		else flag = true;
	} while (flag == false);
	return password;
}

void registration(users *&user)									// Регистрация пльзователя или администратора
{
	string login, password, salt, saltedPassword;
	int code, press;
	bool flag = true;
	system("CLS");
	cout << "\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t****************************************\n"
		<< "\t\t\t\t\t*               Кто вы?                *\n"
		<< "\t\t\t\t\t*         1.Новый администратор.       *\n"
		<< "\t\t\t\t\t*         2.Новый пользователь.        *\n"
		<< "\t\t\t\t\t*              0.Назад                 *\n"
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
	addToFileOneAccount(login, salt, saltedPassword, code);			//запись в файл нового пользователя
	cout << "Спасибо за регистрацию. В скором времени администратор подтвердит вашу регистрацию.";
	Sleep(3000);
	return;
}

int stringComparison(string s, string a)			//Сравнение двух строк
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

int searchLoginPassword(users *&user, int numberOfUsers, int &number_of_attempts, string login, string password)//сравнивание логина и пароля
{
	int d;
	for (int i = 0; i < numberOfUsers; i++) {
		if (user[i].login == login)					//сначала ищем логин 
		{
			number_of_attempts++;
			d = stringComparison(user[i].password, password); // сравниваем пароли
			if (d == 0) {
				system("CLS");
				cout << "Логин или пароль введены неверно!\nПовторите ввод.\n";
				return 3;
			}
			else {
				if (user[i].code == 4) {
					system("CLS");
					cout << "Ваш аккаунт заблокировали! Попробуйте зарегистрироваться ещё раз.";
					Sleep(2000);
					return 4;
				}
				if (user[i].code == 2) return 2;  //код администратора
				if (user[i].code == 1) return 1; //код пользователя
				if (user[i].code == 0 || user[i].code == 3)  //код неактивированных пользовател
				{
					system("CLS");
					cout << "Аккаунт не активирован";
					Sleep(2000);
					return 0;
				}
			}
		}
	}
	number_of_attempts = 0;
	if (number_of_attempts == 0) {
		system("CLS");
		cout << "Логин введен неверно!\nПовторите ввод.\n";
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

int entrance(users *&user)						//авторизация
{
	string password, login, salt, saltedPassword;
	int d = 0, press, numberOfAttempts = 0, numberOfUsers;
	bool flag;
	numberOfUsers = listUsers(user);
	cout << "\t\t\t\t\t\t    АВТОРИЗАЦИЯ\n";
	do {
		cout << "Введите логин: ";
		cin >> login;
		cout << "Введите пароль: ";
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
			cout << "\nЖелаете ли вы сменить пароль.\n1.Да\n2.Нет\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			system("CLS");
			if (press == 49) redactionPassword(user, numberOfUsers);
			else numberOfAttempts = 0;
		}
	} while (flag == false);
}

int registrationAndAuthorization(users *&login, int &press)   //меня регистрации и авторизации
{
	int choice;
	do {
		cout << "\n\n\n\n\t\t\t\t\t\t     ГЛАВНОЕ МЕНЮ";
		cout << "\n\n";
		cout << "\t\t\t\t\t****************************************\n"
			<< "\t\t\t\t\t*            1.Регистрация             *\n"
			<< "\t\t\t\t\t*            2.Авторизация             *\n"
			<< "\t\t\t\t\t*              0. Выход                *\n"
			<< "\t\t\t\t\t****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 50));
		system("CLS");
		switch (press)
		{
		case 48: return press; break;
		case 49:
			registration(login); //регистрация
			system("CLS");
			break;
		case 50:
			press = entrance(login);  // авторизация
			//system("CLS");
			return press;
		}
	} while (press != 48);
}