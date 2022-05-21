#pragma once
#include"Admin.h"


const string FILE_ACCOUNT = "user.txt";
const string FILE_LIST = "employee.txt";

using namespace std;

int listEmployeeData(employees *&employee);//вывод информации из файла в массив с Сотрудниками
int listUsers(users *&user);//Чтение информации из файла с логином и паролем
void addToFileOneAccount(string login, string salt, string saltedPassword, int code);//добавление в конец файла одной записи
void InputAllInformationAboutAccountsInFile(users *user, int numberOfUsers);//перезапись файла с логинами и паролями
void InputAllInformationAboutEmployeeDataInFile(employees *employee, int NumberOfEmployee);//перезапись файла с сотрудниками
