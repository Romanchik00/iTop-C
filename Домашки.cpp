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
#include <algorithm>
#include<functional>
#include <vector>
#include <map>
#include <list>

using namespace std;

#define LoopI(N) for(int i{}; i < N; ++i)
#define LoopJ(N) for(int j{}; j < N; ++j)

//#define Name(Name) # Name

/*
Задание.
Создайте приложение для работы автосалона. Необходимо хранить информацию о продаваемых автомобилях 
(название, год выпуска, объем двигателя, цену). Реализуйте интерфейс для добавления данных, 
удаления данных, отображения данных, сортировке данных по различным параметрам, поиску данных по 
различным параметрам. При реализации используйте контейнеры, функторы и
алгоритмы.
*/
enum Sigil { Descend, Ascend };
enum Tag { Name, Capasity, Year, Price };


struct Car {
	string name;
	double engine_capasity;
	int year;
	int price;

	Car() : name{}, engine_capasity{}, year{}, price{} {};
	Car(string n, double ec, int y, int p) :name{ n }, engine_capasity{ ec }, year{ y }, price{ p }{};
	void fill(string n, int y, int ec, int p) {
		name = n;
		engine_capasity = ec;
		year = y;
		price = p;
	}
	void print() const{
		std::cout << "Car:" << endl
			<< "\tname: " << name << endl
			<< "\tengine capasity: " << engine_capasity << " liter" << endl
			<< "\tyear: " << year << endl
			<< "\tprice: " << price << " $" << endl;
	}
	

	~Car() { 
		//cout << "__Del__" << endl;
	};
};



class Autosalon {
	vector<Car> Cars;
	std::vector<Car>::iterator searcher(const char* val){
		return find_if(Cars.begin(), Cars.end(), [&](Car e) {
			if (e.name == val) return true;
			else return false;
			});
	}
	std::vector<Car>::iterator searcher(double val){
		return find_if(Cars.begin(), Cars.end(), [&](Car e) {
			if (e.engine_capasity == val) return true;
			else return false;
			});
	}
	std::vector<Car>::iterator searcher(int val) {
		if (val / 1000 <= 2) {
			return find_if(Cars.begin(), Cars.end(), [&](Car e) {
				if (e.year == val) return true;
				else return false;
				});
		}
		else
			 {
				return find_if(Cars.begin(), Cars.end(), [&](Car e) {
					if (e.price == val) return true;
					else
						return false; });
			}
	}
public:
	Autosalon() {};
	Autosalon(int size) {
		Cars.resize(size);
	}
	Autosalon(initializer_list<Car>C) {
		for (auto e : C) {
			Cars.push_back(e);
		}
	};
	void sort(Sigil s, Tag t) {
		switch (t) {
		case 0:
			std::sort(Cars.begin(), Cars.end(), [s](Car a, Car b) {
				if (s) return a.name[0] < b.name[0];
				else return a.name[0] > b.name[0];
				});
			break;
		case 1:
			std::sort(Cars.begin(), Cars.end(), [s](Car a, Car b) {
				if (s) return a.engine_capasity < b.engine_capasity;
				else return a.engine_capasity > b.engine_capasity;
				});
			break;
		case 2:
			std::sort(Cars.begin(), Cars.end(), [s](Car a, Car b) {
				if (s) return a.year < b.year;
				else return a.year > b.year;
				});
			break;
		case 3:
			std::sort(Cars.begin(), Cars.end(), [s](Car a, Car b) {
				if (s) return a.price < b.price;
				else return a.price > b.price;
				});
			break;
		default:
			break;
		}
	}

	template<typename T>
	auto search(T val) {
		std::vector<Car>::iterator it = searcher(val);
		if (it == end(Cars))
			cout << "--not found-\tvalue: " << val << endl;
		else
			(*it).print();
	}

	void push(Car x) {
		Cars.push_back(x);
	}
	void print() const{
		for (auto e : Cars) {
			e.print();
		}
	}
	Car& get(int index) {
		try {
			if (index < 0 || index > Cars.size())
				throw 0;
		}
		catch (int){
			std::cout << "--Invalide index-" << endl;
		}

		return Cars[index];
	}
	Car operator[](int i) {
		try {
			if (i < 0 || i > Cars.size())
				throw 0;
			else
				return get(i);
		}
		catch (int) {
			std::cout << "--Invalide index-" << endl;
		}
	}
	void del(int i) {
		
		try {
			auto it = Cars.begin();
			if (it + i >= Cars.end())
				throw 0;
			else
				Cars.erase(it+i);
		}
		catch (int) { std::cout << "--Invalide index-" << endl; }
	}

	~Autosalon() {};
};

int main()
{
	setlocale(LC_ALL, "ru-ru");
	srand(time(NULL));
	//system("pause");
	//system("cls");

	Autosalon Au({
		Car("X5", 3.0, 2023, 14500000),
		Car("Polo", 1.6, 2021, 1629000),
		Car("Wrangler", 3.6, 2024, 12500000),
		Car("Camry", 2.0, 2024, 4879000),
		Car("Q5", 2.0, 2022, 5550000),
		Car("Ku-Ku",22.8,4047,0)
		});
	Au.print();
	std::cout << "\n##*------------------------------------------------------*##\n";

	//Au.get(0).print();
	//Au[1].print();
	Au.del(5);
	//Au.print();
	
	cout << "\n##*------------------------Name------------------------------*##\n";
	Au.sort(Ascend, Name);
	Au.print();
	cout << "\n##*------------------------Name------------------------------*##\n";
	Au.sort(Descend, Name);
	Au.print();
	cout << "\n##*------------------------Capasity------------------------------*##\n";
	Au.sort(Ascend, Capasity);
	Au.print();

	cout << "\n##*------------------------Capasity------------------------------*##\n";
	Au.sort(Descend, Capasity);
	Au.print();
	
	cout << "\n##*------------------------Year------------------------------*##\n";
	Au.sort(Ascend, Year);
	Au.print();

	cout << "\n##*------------------------Year------------------------------*##\n";
	Au.sort(Descend, Year);
	Au.print(); 
	
	cout << "\n##*------------------------Price------------------------------*##\n";
	Au.sort(Ascend, Price);
	Au.print();
	cout << "\n##*------------------------Price------------------------------*##\n";
	Au.sort(Descend, Price);
	Au.print();

	Au.search("Polo");
	Au.search(1.6);
	Au.search(2024);
	Au.search(5550000);

	Au.search("Ku-Ku");
	Au.search(99999);
}

