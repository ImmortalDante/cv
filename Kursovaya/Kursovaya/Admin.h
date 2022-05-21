#pragma once

using namespace std;

struct users
{
	string login;//логин
	string password;//пароль
	string salt;//соль
	string saltedPassword;//пароль с солью
	int code;//роль
};

struct employees
{
	string FIO; //‘»ќ 
	string personnelNumber;//табельный номер
	int year; //год
	int month;//мес€ц
	int numberOfHours;// оплата за час
	double oneHourPayment;// кол-во часов

};


void menuAdmin(users *&user, employees *&employee);//ћеню администратора
void menuWorkWithDataEmployee(employees *&employee, int &NumberOfEmployee);//ћеню дл€ работы с данными(администратор)
void menuWorkWithAccounts(users *&user, int &numberOfUsers);//ћеню дл€ управлени€ уч. запис€ми(администратор)
void employeesProcessing(employees *&employee, int &NumberOfEmployee);//ћеню дл€ обработки данных(администратор)
void editDataAboutEmployee(employees *&employee, int &NumberOfEmployee);//ћеню дл€ редактировани€ данных (администратор)
void redactionLoginPassword(users *&user, int numberOfUsers);//ћен€ дл€ редактировани€ логина и парол€
void redactionLogin(users *&user, int numberOfUsers);//редактирование логина
void redactionPassword(users *&user, int numberOfUsers);//редактирование парол€
void deleteAccounts(users *&user, int &numberOfUsers);//удаление аккаунтов
void viewLoginsPassword(users *user, int numberOfUsers);//просмотр логинов и паролей
void addingNewUsers(users *&user, int &numberOfUsers);//добавление нового пользовател€
void activationAccounts(users *&user, int numberOfUsers);//активаци€ новах аккаунтов
void addingNewEmployeeData(employees *&employee, int &NumberOfEmployee);//добавление нового сотудника
void deleteEmployeeData(employees *&employee, int &NumberOfEmployee);//удаление сотрудника
void redactionFIO(employees *&employee, int &NumberOfEmployee);//редактирование ‘»ќ
void redactionYear(employees *&employee, int &NumberOfEmployee);//редактирование года
void redactionNumberOfHours(employees *&employee, int &NumberOfEmployee);//редактирование количества часов
void redactionOneHourPayment(employees *&employee, int &NumberOfEmployee);//редактирование оплаты
void redactionMonth(employees *&employee, int &NumberOfEmployee);//редактирование мес€ца
void redactionPersonnelNumber(employees *&employee, int &NumberOfEmployee);//редактирование мес€ца
void individualTask(employees *&employee, int &NumberOfEmployee);//индивидуальное задание
void menuRedactionEmployee(employees *&employee, int &NumberOfEmployee);//ћеню дл€ редактировани€ данных о сотруднике
int inputInt();//¬вод целого числа
double inputDouble();//ввод дробного числа
string inputFIO();//проверка на ввод названи€
int inputYear();//проверка на ввод года
int inputMonth();//проверка на ввод мес€ца


