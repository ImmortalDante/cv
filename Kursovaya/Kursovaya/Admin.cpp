#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>
#include<Windows.h>
#include<iomanip>
#include"Admin.h"
#include"File.h"
#include"Users.h"
#include"Authorization.h"
#include "sha256.h"

using namespace std;

string inputFIO()//проверка на ввод ФИО
{
	string name;
	int l;
	bool flag;
	do {
		flag = true;
		cin >> name;
		l = name.length();
		for (int i = 0; i < l; i++) {
			if (!(name[i] >= 'a'&& name[i] <= 'z') && !(name[i] >= 'A'&& name[i] <= 'Z'))
			{
				cout << "Повторите ввод!! Только латинские буквы\n";
				flag = false;
				break;
			}
		}
	} while (flag == false);
	return name;
}

int inputYear()  //ввод года
{
	int year;
	while (1) {
		year = inputInt();
		if (year == 0 || year > 2020)
		{
			cout << "Введите корректно год!\n";
		}
		else return year;
	}
}

int inputMonth()
{
	int month;
	while (1) {
		month = inputInt();
		if (month == 0 || month > 12)
		{
			cout << "Введите корректно месяц!\n";
		}
		else return month;
	}
}

int inputInt() {  //Ввод целого числа
	string s;
	int i, a = 0, l;
	bool flag = true;
	while (flag)
	{
		cin >> s;
		l = s.length();
		for (i = 0; i < l; i++)
		{
			if ((s[i] >= (char)48) && (s[i] <= (char)57) || (s[i] == (char)45))
			{
				if ((i > 0) && (s[i] == 45))
				{
					flag = true;
					cout << "Значение введено не верно!! Повтороите ввод!" << endl;
					break;
				}
				else flag = false;
			}
			else
			{
				flag = true;
				cout << "Значение введено не верно!! Повтороите ввод!" << endl;
				break;
			}

		}
	}
	return stof(s);
}

double inputDouble() //ввод дробного числа
{
	int i, number = 0, l;
	bool flag = true;
	string s;
	while (flag)
	{
		cin >> s;
		l = s.length();
		for (i = 0; i < l; i++)
		{
			if ((s[i] >= (char)48) && (s[i] <= (char)57) || (s[i] == ','))
			{
				if (s[i] == ',')
				{
					number++;
					if (number > 1)
					{
						flag = true;
						cout << "Значение введено не верно!! Повтороите ввод!" << endl;
						number = 0;
						break;
					}
					else flag = false;
				}
				else flag = false;
			}
			else
			{
				flag = true;
				cout << "Значение введено не верно!! Повтороите ввод!" << endl;
				break;
			}
		}
	}
	return stof(s);
}

void addingNewEmployeeData(employees *&employee, int &NumberOfEmployee)//дабавление сотрудника
{
	string name, personnelNumber;
	int numberOfHours, year, press, month;
	double oneHourPayment;
	ofstream fadd(FILE_LIST, ios::app);
	do {
		cout << "Введите ФИО : ";
		name = inputFIO();
		name = enterStringWithSmallLetter(name);//проверка на ввод с маленькой буквы

		cout << "Введите табельный номер: ";
		cin >> personnelNumber;

		cout << "Введите год: ";
		year = inputYear();

		cout << "Введите месяц: ";
		month = inputMonth();

		cout << "Введите количество проработанных часов: ";
		numberOfHours = inputInt();
		cout << "Введите оплату за один час: ";
		oneHourPayment = inputDouble();
		fadd << setw(25) << left << name       //запись в файл
			<< setw(20) << left << personnelNumber
			<< setw(7) << left << year
			<< setw(5) << left << month
			<< setw(7) << left << numberOfHours
			<< setw(5) << left << oneHourPayment << endl;
		cout << "\nЖелаете ли вы подолжить добавление сотрудников.\n1.Да\n2.Нет\n";
		do {
			press = _getch();
		} while (press != 49 && press != 50);
	} while (press != 50);
	fadd.close();
	NumberOfEmployee = listEmployeeData(employee);
}

void deleteEmployeeData(employees *&employee, int &NumberOfEmployee)//удаление сотрудника
{
	int s = -1, press;
	string FIO;
	cout << "Введите ФИО человека, которого вы хотите удалить из списка: ";
	cin >> FIO;
	FIO = enterStringWithSmallLetter(FIO); //проверка на ввод с маленькой буквы
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].FIO == FIO) {
			s = i;
			break;
		}
	}
	if (s == -1)
		cout << "Данные этого человека не найдены.\n";
	else {
		cout << "Вы действительно хотите удалить запись?\n1.Да\n2.Нет\n";
		do {
			press = _getch();
		} while (press != 49 && press != 50);
		if (press == 49)
		{
			for (int i = s; i < NumberOfEmployee - 1; i++)
				employee[i] = employee[i + 1];
			NumberOfEmployee--;
			cout << "УДАЛЕНИЕ ПРОШЛО УСПЕШНО!!\n";
			return;
		}
		else return;
	}
}

void redactionFIO(employees *&employee, int &NumberOfEmployee)//редактирование ФИО
{
	string FIO, newFIO;
	int press;
	cout << "Введите ФИО человека, чьё ФИО вы хотите изменить.\n";
	cin >> FIO;
	FIO = enterStringWithSmallLetter(FIO);//проверка на ввод с маленькой буквы
	//system("CLS");
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].FIO == FIO)
		{
			cout << "Введите новое ФИО: \n";
			cin >> newFIO;
			newFIO = enterStringWithSmallLetter(newFIO);//проверка на ввод с маленькой буквы
			cout << "Вы действительно хотите изменить?\n1.Да\n2.Нет\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49)
			{
				employee[i].FIO = newFIO;
				system("CLS");
				cout << "РЕДАКТИРОВАНИЕ УСПЕШНО ВЫПОЛНЕНО.";
				Sleep(2000); system("CLS");
				return;
			}
			else return;
		}
	}
	cout << "Извените! Данного человека нет в этом списке\n";
	return;
}

void redactionYear(employees *&employee, int &NumberOfEmployee)//редактирование года
{
	string FIO;
	int press;
	int year;
	cout << "Введите ФИО человека, чей год хотите изменить.\n";
	cin >> FIO;
	FIO = enterStringWithSmallLetter(FIO);//проверка на ввод с маленькой буквы
	system("CLS");
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].FIO == FIO)
		{
			cout << "Введите новый год: \n";
			year = inputYear();

			cout << "Вы действительно хотите изменить?\n1.Да\n2.Нет\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49)
			{
				employee[i].year = year;
				system("CLS");
				cout << "РЕДАКТИРОВАНИЕ УСПЕШНО ВЫПОЛНЕНО.";
				Sleep(2000); system("CLS");
				return;
			}
			else return;
		}
	}
	cout << "Извените! Данного человека нет в этом списке\n";
	return;
}

void redactionNumberOfHours(employees *&employee, int &NumberOfEmployee)//редактирование кол-ва часов
{
	string FIO;
	int press, numberOfHours;
	cout << "Введите ФИО человека, чьё количество проработанных часов вы хотите изменить.\n";
	cin >> FIO;
	
	FIO = enterStringWithSmallLetter(FIO);
	system("CLS");
	
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].FIO == FIO)
		{
			cout << "Введите новое количество пророботанных часов: \n";
			numberOfHours = inputInt();
			
			cout << "Вы действительно хотите изменить?\n1.Да\n2.Нет\n";
			
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			
			if (press == 49)
			{
				employee[i].numberOfHours = numberOfHours;
				system("CLS");
				cout << "РЕДАКТИРОВАНИЕ УСПЕШНО ВЫПОЛНЕНО.";
				Sleep(2000); system("CLS");
				return;
			}
			else return;
		}
	}
	cout << "Извените! Данного человека нет в этом списке\n";
	return;
}

void redactionOneHourPayment(employees *&employee, int &NumberOfEmployee) //редактирование платы за час
{
	string FIO;
	int press;
	double oneHourPayment;
	cout << "Введите ФИО человека, чью платы за час хотите изменить.\n";
	cin >> FIO;
	FIO = enterStringWithSmallLetter(FIO);
	system("CLS");
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].FIO == FIO)
		{
			cout << "Введите новую плату: \n";
			oneHourPayment = inputDouble();
			cout << "Вы действительно хотите изменить?\n1.Да\n2.Нет\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49)
			{
				employee[i].oneHourPayment = oneHourPayment;
				system("CLS");
				cout << "РЕДАКТИРОВАНИЕ УСПЕШНО ВЫПОЛНЕНО.";
				Sleep(2000); system("CLS");
				return;
			}
			else return;
		}
	}
	cout << "Извените! Данного человека нет в этом списке\n";
	return;
}

void redactionMonth(employees *&employee, int &NumberOfEmployee)//редактирование месяца
{
	string FIO;
	int press, month;
	cout << "Введите ФИО человека, чей месяц хотите изменить.\n";
	cin >> FIO;
	FIO = enterStringWithSmallLetter(FIO);//проверка на ввод с маленькой буквы
	system("CLS");
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].FIO == FIO)
		{
			cout << "Введите новый месяц: \n";
			month=inputMonth();
			cout << "Вы действительно хотите изменить?\n1.Да\n2.Нет\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49)
			{
				employee[i].month = month;
				system("CLS");
				cout << "РЕДАКТИРОВАНИЕ УСПЕШНО ВЫПОЛНЕНО.";
				Sleep(2000); system("CLS");
				return;
			}
			else return;
		}
	}
	cout << "Извените! Данного человека нет в этом списке\n";
	return;
}

void redactionPersonnelNumber(employees *&employee, int &NumberOfEmployee) {
	string FIO;
	int press, personnelNumber;
	cout << "Введите ФИО человека, чей табельный номер хотите изменить.\n";
	cin >> FIO;
	FIO = enterStringWithSmallLetter(FIO);//проверка на ввод с маленькой буквы
	system("CLS");
	for (int i = 0; i < NumberOfEmployee; i++) {
		if (employee[i].FIO == FIO)
		{
			cout << "Введите новый табельный номер: \n";

			cin >> personnelNumber;

			cout << "Вы действительно хотите изменить?\n1.Да\n2.Нет\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49)
			{
				employee[i].personnelNumber = personnelNumber;
				system("CLS");
				cout << "РЕДАКТИРОВАНИЕ УСПЕШНО ВЫПОЛНЕНО.";
				Sleep(2000); system("CLS");
				return;
			}
			else return;
		}
	}
	cout << "Извените! Данного человека нет в этом списке\n";
	return;
}

void individualTask(employees *&employee, int &NumberOfEmployee)//индивидуальное занятие
{
	int month, year;
	double pay, sum=0;
	cout << "Введите месяц: ";
	month=inputMonth();
	cout << "Введите год: ";
	year=inputYear();

	for (int i = 0; i < NumberOfEmployee; i++)
	{
		if ((employee[i].month == month) && (employee[i].year == year))
		{
			sum++;
			if (employee[i].numberOfHours > 144) {
				pay = (employee[i].oneHourPayment * 144 + (employee[i].numberOfHours - 144) * 2 * employee[i].oneHourPayment)* 0.88;
				cout << employee[i].FIO << "\t" << pay << endl;
			}
			else {
				pay = employee[i].oneHourPayment*employee[i].numberOfHours* 0.88;
				cout << employee[i].FIO << "\t" << pay << endl;
			}
			
		}
		pay = 0;
	}
	if (sum == 0)
	{
		cout << "Никто не работал в это месяце!\n";
		Sleep(2000); system("CLS");
		return;
	}
	
	
}

void menuRedactionEmployee(employees *&employee, int &NumberOfEmployee)//меню редактироавания сотрудников
{
	int press;
	do {
		cout << "\t\t\t\t\t****************************************\n"
			<< "\t\t\t\t\t*     1.ФИО.        .                  *\n"
			<< "\t\t\t\t\t*     2.Год.                           *\n"
			<< "\t\t\t\t\t*     3.Оплата за час.                 *\n"
			<< "\t\t\t\t\t*     4.Количество проработанных часов *\n"
			<< "\t\t\t\t\t*     5.Месяц.                         *\n"
			<< "\t\t\t\t\t*     0.Назад                          *\n"
			<< "\t\t\t\t\t****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 53));
		system("CLS");
		switch (press)
		{
		case 49:
			redactionFIO(employee, NumberOfEmployee); break;//по ФИО
		case 50:
			redactionYear(employee, NumberOfEmployee); break;// по году
		case 51:
			redactionOneHourPayment(employee, NumberOfEmployee); break;//по плате
		case 52:
			redactionNumberOfHours(employee, NumberOfEmployee); break; //по кол-ву часов
		case 53:
			redactionMonth(employee, NumberOfEmployee); break;//по месяцу
		case 48: system("CLS"); return;
		}
	} while (press != 53);
}

void employeesProcessing(employees *&employee, int &NumberOfEmployee)	//обработка данных о сотрудниках
{
	int press;
	do {
		cout << "\t\t\t\t\t*****************************************\n"
			<< "\t\t\t\t\t*               1. Поиск                *\n"
			<< "\t\t\t\t\t*             2. Сортировка             *\n"
			<< "\t\t\t\t\t*        3. Индивидуальное задание      *\n"
			<< "\t\t\t\t\t*               0. Назад                *\n"
			<< "\t\t\t\t\t*****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 51));
		system("CLS");
		switch (press)
		{
		case 48: return;
		case 49:
			menuSearch(employee, NumberOfEmployee);  break;//меню поиска
		case 50:
			menuSorting(employee, NumberOfEmployee); break;//меню сортировки
		case 51:
			individualTask(employee, NumberOfEmployee); break;//индивид. задание
		}

	} while (press != 48);

}

void editDataAboutEmployee(employees *&employee, int &NumberOfEmployee)	//редактирование данных о сотрудниках
{
	int press;
	do {
		cout << "\t\t\t\t\t*****************************************\n"
			<< "\t\t\t\t\t*              1. Просмотр.             *\n"
			<< "\t\t\t\t\t*           2. Редактирование.          *\n"
			<< "\t\t\t\t\t*             3. Добавление.            *\n"
			<< "\t\t\t\t\t*              4. Удаление.             *\n"
			<< "\t\t\t\t\t*               0. Назад.               *\n"
			<< "\t\t\t\t\t*****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 52));
		system("CLS");
		switch (press)
		{
		case 48: return;
		case 49:
			ViewEmployee(employee, NumberOfEmployee);  break;//просмотр
		case 50:
			menuRedactionEmployee(employee, NumberOfEmployee);//меня редактирования сотрудниках
			break;
		case 51:
			addingNewEmployeeData(employee, NumberOfEmployee); break;//дабавление сотрудниках
		case 52:
			deleteEmployeeData(employee, NumberOfEmployee); break;//удаление сотрудников
		}
		if (press != 49 && press != 48) {
			InputAllInformationAboutEmployeeDataInFile(employee, NumberOfEmployee);//перезапись в файл
		}

	} while (press != 48);
}

void activationAccounts(users *&user, int numberOfUsers)//активация аккаунтов
{
	int press, t = 0;
	for (int i = 0; i < numberOfUsers; i++) {
		if (user[i].code == 0) {
			t++;
			cout << user[i].login << " желает зарегистрироваться\n"
				<< "Активировать аккаунт?\n1.Да\n2.Нет\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49) user[i].code = 1;
			else user[i].code = 4;
			system("CLS");
		}
		if (user[i].code == 3) {
			t++;
			cout << user[i].login << " желает зарегистрироваться как администратор.\n"
				<< "Активировать аккаунт?\n1.Да\n2.Нет\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49) user[i].code = 2;
			else user[i].code = 4;
			system("CLS");
		}
	}
	if (!t) cout << "Никто не зарегистрировался\n";
	return;
}

void redactionLogin(users *&user, int numberOfUsers)//редактирование логин
{
	string login, login1;
	int press, s = 0;
	bool flag = true;
	cout << "Введите логин, который вы хотите изменить: ";
	cin >> login;
	for (int i = 0; i < numberOfUsers; i++) {
		if (user[i].login == login) {
			s++;
			do {
				cout << "На какой логин вы хотите заменить: ";
				login1 = inputFIO();
				for (int i = 0; i < numberOfUsers; i++) {
					if (login1 == user[i].login) {
						cout << "Такой логин уже существует.\n";
						flag = false;
						break;
					}
					else flag = true;
				}
			} while (flag == false);

			cout << "Вы уверены, что хотите изменить логин.\n1.Да\n2.Нет\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49) {
				user[i].login = login1;
				system("CLS");
				cout << "РЕДАКТИРОВАНИЕ УСПЕШНО ВЫПОЛНЕНО.";
				Sleep(2000); system("CLS");
				return;
			}
			else return;
		}
	}
	if (!s) {
		cout << "Логин не найден.\n";
		return;
	}
}

void redactionPassword(users *&user, int numberOfUsers)			//Замена старого пароля на новый
{
	int press, s = 0;
	string login, password, salt, saltedPassword;
	cout << "Введите логин пользователя, чей пароль хотите изменить.";
	cin >> login;
	for (int i = 0; i < numberOfUsers; i++) {
		if (user[i].login == login) {
			s++;
			password = inputPassword();
			salt = user[i].salt;
			saltedPassword = generationHashPassword(password + salt);
			cout << "\nВы уверены, что хотите изменить пароль.\n1.Да\n2.Нет\n";
			do {
				press = _getch();
			} while (press != 49 && press != 50);
			if (press == 49) {
				user[i].saltedPassword = saltedPassword;
				system("CLS");
				InputAllInformationAboutAccountsInFile(user, numberOfUsers);
				cout << "РЕДАКТИРОВАНИЕ УСПЕШНО ВЫПОЛНЕНО.";
				Sleep(2000); system("CLS");
				return;
			}
			else return;
		}
	}
	if (!s) {
		cout << "Логин не найден.\n";
		return;
	}
}

void addingNewUsers(users *&user, int &numberOfUsers)//добавление нового пользователя(администратором)
{
	string login, password, salt, saltedPassword;
	int kod = 1, press;
	ofstream fadd(FILE_ACCOUNT, ios::app);
	do {
		system("CLS");
		login = inputLogin(user);
		password = inputPassword();
		saltedPassword = generationHashPassword(password + salt);
		fadd << setw(20) << left << login << setw(20) << salt << setw(70) << saltedPassword << setw(5) << left << kod << endl;
		cout << "\nЖелаете ли вы продолжить добавление аккаунтов\n1.Да\n2.Нет\n";
		do {
			press = _getch();
		} while (press != 49 && press != 50);

	} while (press != 50);
	fadd.close();
	cout << "ДОБАВЛЕНИЕ ВЫПОЛНЕНО УСПЕШНО!!";
	Sleep(2000);
	numberOfUsers = listUsers(user);
	system("CLS");
}

void viewLoginsPassword(users *user, int numberOfUsers)//вывод логинов и паролей
{
	cout << "-----------------------------------------------------------------\n"
		<< "|         Логин        |            Пароль              |  Код  |\n"
		<< "-----------------------------------------------------------------\n";
	for (int i = 0; i < numberOfUsers; i++)
	{
		cout << "| " << setw(20) << left << user[i].login << " | " << setw(30) << left << user[i].password << " | "
			<< setw(5) << left << user[i].code << " | " << endl;
		cout << "-----------------------------------------------------------------\n";
	}
}

void redactionLoginPassword(users *&user, int numberOfUsers)//редактирование логина и пароля
{
	int press;
	cout << "\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t*****************************************\n"
		<< "\t\t\t\t\t*       1. Редактирование пароля.       *\n"
		<< "\t\t\t\t\t*       2. Редактирование логина.       *\n"
		<< "\t\t\t\t\t*               0. Назад                *\n"
		<< "\t\t\t\t\t*****************************************\n";
	do {
		press = _getch();
	} while (!(press >= 48 && press <= 50));
	system("CLS");
	switch (press)
	{
	case 50: redactionLogin(user, numberOfUsers); break;
	case 49: redactionPassword(user, numberOfUsers); break;
	case 48: break;
	}

}

void deleteAccounts(users *&user, int &numberOfUsers)//удаление аккаунтов пользователей
{
	int s = -1, press;
	string login;
	cout << "Введите логин аккаунта, который вы хочите удалить: ";
	cin >> login;
	for (int i = 0; i < numberOfUsers; i++) {
		if (user[i].login == login) {
			if (user[i].code == 2) s = -2;
			else s = i;
			break;
		}
	}
	//system("CLS");
	if (s == -2)
	{
		cout << "Это аккаунт администратора. Вы не можите его удалить!!\n";
		return;
	}
	if (s == -1)
		cout << "Данный аккаунт не найден.\n";
	else {
		cout << "Вы действительно хотите удалить запись?\n1.Да\n2.Нет\n";
		do {
			press = _getch();
		} while (press != 49 && press != 50);
		if (press == 49)
		{

			for (int i = s; i < numberOfUsers - 1; i++)
				user[i] = user[i + 1];
			numberOfUsers--;
			cout << "УДАЛЕНИЕ АККАУНТА ВЫПОЛНЕНО УСПЕШНО!\n";
			viewLoginsPassword(user, numberOfUsers);
			return;
		}
		else return;
	}
}

void menuWorkWithDataEmployee(employees *&employee, int &NumberOfEmployee)//Меню для работы с данными(администратор)
{
	int press;

	do {
		cout << "\t\t\t\t\t*****************************************\n"
			<< "\t\t\t\t\t*           1. Редактирование           *\n"
			<< "\t\t\t\t\t*             2. Обработка              *\n"
			<< "\t\t\t\t\t*               0. Назад                *\n"
			<< "\t\t\t\t\t*****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 50));
		system("CLS");
		switch (press)
		{
		case 48: return;
		case 50:
			employeesProcessing(employee, NumberOfEmployee); break;
		case 49:
			editDataAboutEmployee(employee, NumberOfEmployee); break;
		}

	} while (press != 48);

}

void menuWorkWithAccounts(users *&user, int &numberOfUsers)//Меню для управления уч. записями(администратор)
{
	int press;
	do {
		cout << "\t\t\t\t\t*****************************************\n"
			<< "\t\t\t\t\t*              1. Просмотр.             *\n"
			<< "\t\t\t\t\t*         2. Активация аккаунтов.       *\n"
			<< "\t\t\t\t\t*           3. Редактирование.          *\n"
			<< "\t\t\t\t\t*              4. Добавить.             *\n"
			<< "\t\t\t\t\t*              5. Удаление.             *\n"
			<< "\t\t\t\t\t*                0. Назад               *\n"
			<< "\t\t\t\t\t*****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 53));
		system("CLS");
		switch (press)
		{
		case 49:
			viewLoginsPassword(user, numberOfUsers); break;
		case 50:
			activationAccounts(user, numberOfUsers); break;
		case 51:
			redactionLoginPassword(user, numberOfUsers); break;
		case 52:
			addingNewUsers(user, numberOfUsers); break;
		case 53:
			deleteAccounts(user, numberOfUsers); break;
		case 48: return;
		}
		if (press != 48 && press != 49)
		{
			InputAllInformationAboutAccountsInFile(user, numberOfUsers);
		}
	} while (press != 48);
}

void menuAdmin(users *&user, employees *&employee)//Меню администратора
{
	int press, numberOfUsers = listUsers(user);
	int NumberOfEmployee = listEmployeeData(employee);
	do {
		cout << "\n\n\n\n\t\t\t\t\t\t    МЕНЮ АДМИНИСТРАТОРА";
		cout << "\n\n";
		cout << "\t\t\t\t\t*****************************************\n"
			<< "\t\t\t\t\t*     1. Работа с учётными записями     *\n"
			<< "\t\t\t\t\t*         2. Работа с данными           *\n"
			<< "\t\t\t\t\t*              0. Назад                 *\n"
			<< "\t\t\t\t\t*****************************************\n";
		do {
			press = _getch();
		} while (!(press >= 48 && press <= 50));
		system("CLS");
		switch (press)
		{
		case 49:
			menuWorkWithAccounts(user, numberOfUsers);
			break;
		case 50:
			menuWorkWithDataEmployee(employee, NumberOfEmployee);
			break;
		case 48: return;
		}
	} while (press != 48);
}
