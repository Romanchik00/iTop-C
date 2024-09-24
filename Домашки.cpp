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

#include<memory>

using namespace std;

#define LoopI(N) for(int i{}; i < N; ++i)
#define LoopJ(N) for(int j{}; j < N; ++j)

unsigned int Count{};

template<class T>
class SharedPointer {
	T* point;
	unsigned int* counter = &Count;

	void increase() { ++* counter; }
	void decrease() {
		if (*counter > 0)
			--* counter;
	}

public:
	SharedPointer(T* p = nullptr) : point{ p } {
		cout << "constr A:" << endl;
		if (p)
			increase();
	}
	SharedPointer(const SharedPointer& p) { //----
		cout << "constr B:" << endl;
		point = p.point;					// Оба так ни разу не отработали, хоть я и пытался
		increase();
	};
	SharedPointer(SharedPointer&& p) {     //----
		cout << "constr C:" << endl;
		point = p.point;
		increase();
	};
	SharedPointer& operator=(const SharedPointer& p) {
		point = p.point;
		increase();
		return *this;
	};
	SharedPointer& operator=(SharedPointer&& p) {
		point = p.point;
		increase();
		return *this;
	};


	unsigned int use_count() const { return *counter; }

	~SharedPointer() {
		decrease();
		cout << "del-- " << *counter << endl;
		if (*counter == 0)
			if (point) { //чисто на всякий случай
				cout << "All delete--" << endl;
				delete point;
				point = nullptr; //чисто на всякий случай
			}
	}
	void swap(SharedPointer& p) {
		auto temp = p.point;
		p.point = point;
		point = temp;
	}

	T* get() { return point; }

	operator bool() { return (bool)point; }
	T& operator* () {
		/*try {  // Я пытался, ничего нормального не получилось.
			if (point)*/
		return *point;
		/*else {
			throw 0;
		}
	}
	catch (int) {
		cout << "Error value" << endl;
	}*/
	}
	SharedPointer* operator-> () { // Ваш T* operator-> () { return ptr; } у меня не сработал.
		return *this;
	}
	/*
		V shared_ptr	Создает документ shared_ptr.
		V ~shared_ptr	Удаляет shared_ptr.

		X Typedefs
		X element_type	Тип элемента.
		X weak_type	Тип слабого указателя на элемент.

		Функции-члены
		V get	Возвращает адрес принадлежащего ресурса.
		??? owner_before	Возвращает значение true, если shared_ptr упорядочен до (меньше) предоставленного указателя.
		??? reset	Заменяет принадлежащий ресурс.
		V swap	Меняет местами два объекта shared_ptr.
		X unique	Проверяет, является ли принадлежащий ресурс уникальным.
		V use_count	Подсчитывает количество владельцев ресурса.

		V Операторы
		V operator bool	Проверяет существование принадлежащего ресурса.
		V operator*	Возвращает указанное значение.
		V operator=	Заменяет принадлежащий ресурс.
		V operator->
	*/
};


int main()
{
	setlocale(LC_ALL, "ru-ru");
	srand(time(NULL));
	//system("pause");

	SharedPointer<int> a(new int(5));
	cout << a.use_count() << endl;
	if (a) { cout << "Yes" << endl; }

	cout << endl;

	SharedPointer<int> b;
	cout << "getN:" << b.get() << endl;
	cout << b.use_count() << endl;
	//cout << *b; Alert !!!
	if (b) { cout << "Yes" << endl; }
	else { cout << "No" << endl; }
	b = a;
	cout << "b= " << *b << endl;
	cout << "getF:" << b.get() << endl;
	cout << b.use_count() << endl;

	cout << endl;

	SharedPointer<char>c(SharedPointer<char>(new char{ 'a' })); // <- <- <- Вот сдесь пытался
	cout << c.use_count() << "  " << *(c.get()) << endl;
	cout << endl;
	//auto ss = shared_ptr<int>(new int{ 5 });

}

