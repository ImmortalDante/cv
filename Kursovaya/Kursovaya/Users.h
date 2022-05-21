#pragma once
#include"Admin.h"

using namespace std;

void sortingFIO(employees *employee, int NumberOfEmployee);//сортировка по ФИО
void sortingNumberOfHours(employees *employee, int NumberOfEmployee);//сорт. по кол-ву проработанных часов
void ViewSearch(employees *, int k, int);//просмотр при поиске
void sortingOneHourPayment(employees *employee, int NumberOfEmployee);//сортировка по оплате
void sortingYear(employees *employee, int NumberOfEmployee);//сортировка по году
void ViewEmployee(employees *employee, int NumberOfEmployee);//просмотр сотрудников
void searchFIO(employees *employee, int NumberOfEmployee);//поиск по ФИО
void searchYear(employees *employee, int NumberOfEmployee);//поиск по году
void searchOneHourPayment(employees *employee, int NumberOfEmployee);//поиск по оплате
void searchMonth(employees *employee, int NumberOfEmployee);//поиск по месяцу
void menuSearch(employees *employee, int NumberOfEmployee);//меню поиска
void menuSorting(employees *employee, int NumberOfEmployee);//меню сортировки
void menuUsers(employees *&employee);//меню пользователя
string enterStringWithSmallLetter(string FIO); //ввод строки с маленькой буквы