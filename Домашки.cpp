#include <iostream>
#include <windows.h>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <conio.h>
#include <io.h>

using namespace std;

#define LoopI(N) for(int i{}; i < N; ++i)
#define LoopJ(N) for(int j{}; j < N; ++j)

//Задание 1.
//Создать программу, обрабатывающую исключения при работе
//с вещественными числами с использованием инструкции try, catch, throw.
//Проект – консольное приложение.
//В задании надо рассчитывать массив f[x] = 1 / (x – N) при x = 0…k.
//Варианты заданий.
//N – последняя цифра номера паспорта плюс 5.
//Необходимо отслеживать два исключения :
//Деление на 0.
//Выход за пределы диапазона.
//При работе с программой менять k, чтобы получать разные
//условия возможного возникновения исключений.
//Пример.
//
//Вариант задания : f[x] = 1 / (x - 5).N = 10

double f(int x) { 

	const int N = 12;

	if (x - N == 0)
		throw 0;
	return (1.0 / (x - N)); 
}

void task1(const unsigned int k) {
	try {
		if (k >= 245000000)
			throw 'b';
	}
	catch (char) {
		cout << "--bad alloc-" << endl;
		return;
	}
	double* arr = new double[k] {};
	for (int x{}; x <= k; ++x) {
		try
		{
			if (x == k)
				throw "--выход за пределы диапазона-";
			arr[x] = f(x);
			cout << arr[x] << endl;
		}
		catch (int)
		{
			cout << "--деление на ноль-" << endl;
		}
		catch (const char e[]) {
			cout << e << endl;
		}
	}

	delete[] arr;
}

//Задание 2.
//
//1) Деление на ноль        ---  Было выше , не вижу смысла повторять
//2) Ввод числа вместо буквы
//3) Выход за границы массива(матрицы).Матрица 2х2, мы, к примеру, перемножаем элементы(3; 3)
//4) Неверный тип входных параметров(вместо Int пишем double)

//task2

void task2_2() {
	char ch{};
	cout << "--Vvedite bukvu-" << endl;
	try {
		cin >> ch;
		if ((ch < 'A' || ch >'Z') || (ch > 'z' || ch < 'a'))
			throw 0;
	}
	catch (int) {
		cout << "--Ne bukva-" << endl;
	}
}

void task2_3() {
	int arrch[2][2]{1,2,3,4};
	int mul1{}, mul2{};
	try {
		cin >> mul1 >> mul2;
		if ((mul1 > 2 || mul2 > 2) || (mul1 < 0 || mul2 < 0)) {
			throw 'B';
			return;
		}
			
	}
	catch (char) {
		cout << "Vyhod za granitsi" << endl;
	}

	cout << arrch[mul1][mul2] << endl;
}

void task2_4(int e) {}

int main()
{
	setlocale(LC_ALL, "ru-ru");
	srand(time(NULL));

	//system("pause");
	//system("cls");
	
	//task1(12);
	//task1(24);
	//task1(48);

	//task2_2();

	//task2_3(); 

	//task2_4(1.0);// Y ne smog pridumat` , kak viletet` s double-om : int obrezaet . PS i v f(int) , i v cin >> <int>
}

