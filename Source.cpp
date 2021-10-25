#include <conio.h>
#include <iostream>
#include <locale.h>
#include <math.h>
struct Point
{
	double x;
	double y;
};

class Polyline
{
	Point* p;
	size_t vertex;

public:
	Polyline();
	Polyline(int count_vertex);
	~Polyline();
	Polyline(const Polyline& polyline);
	double Length() const;
	Polyline operator+ (const Polyline& polyline) noexcept;
	Polyline& operator = (const Polyline& line) noexcept;
	Point operator[] (const size_t index) const;
	Point& operator[] (const size_t index);
	bool operator == (const Polyline& polyline);
	bool operator != (const Polyline& polyline);
	void AddToEnd(const Point& point);
	void AddToBegin(const Point& point);
	friend std::ostream& operator<< (std::ostream& out, const Polyline& polyline);
};

std::ostream& operator<< (std::ostream& out, const Polyline& polyline);





Polyline::Polyline() : p(nullptr), vertex(0) { }

Polyline::Polyline(int count_vertex)
{
	if (count_vertex < 0) throw "Ошибка подсчета вершин";
	vertex = (size_t)count_vertex;
	p = new Point[count_vertex]();
}

Polyline::~Polyline()
{
	delete[] p;
	vertex = 0;
}

Polyline::Polyline(const Polyline& polyline) : p(new Point[polyline.vertex]), vertex(polyline.vertex)
{
	for (size_t i = 0; i < polyline.vertex; ++i)
	{
		p[i] = polyline.p[i];
	}
}

double Polyline::Length() const
{
	if (p == nullptr) throw "Нет информации о линии";
	double lenght = 0;
	for (size_t i = 0; i < vertex - 1; ++i)
	{
		lenght += sqrt(pow((p[i + 1].x - p[i].x), 2) + pow((p[i + 1].y - p[i].y), 2));
	}
	return lenght;
}


Polyline Polyline::operator+ (const Polyline& polyline) noexcept
{
	Polyline result(vertex + polyline.vertex);
	for (size_t i = 0; i < vertex; ++i)
	{
		result.p[i] = p[i];
	}
	for (size_t i = 0; i < polyline.vertex; ++i)
	{
		result.p[vertex + i] = polyline.p[i];
	}
	return result;
}

Polyline& Polyline::operator = (const Polyline& line) noexcept
{
	if (this == (&line)) return *this;
	if (p) delete[] p;
	if (line.p)
	{
		p = new Point[line.vertex];
		vertex = line.vertex;
		for (size_t i = 0; i < line.vertex; ++i)
		{
			p[i] = line.p[i];
		}
	}
	else
	{
		p = nullptr;
		vertex = 0;
	}
	return *this;
}
bool Polyline::operator == (const Polyline& polyline)
{
	if (vertex != polyline.vertex) return false;
	for (size_t i = 0; i < vertex; i++)
	{
		if ((p[i].x != polyline.p[i].x) || (p[i].y != polyline.p[i].y)) return false;
	}
	return true;
}

bool Polyline::operator != (const Polyline& polyline)
{
	if (vertex != polyline.vertex) return true;
	for (size_t i = 0; i < vertex; i++)
	{
		if ((p[i].x != polyline.p[i].x) || (p[i].y != polyline.p[i].y)) return true;
	}
	return false;
}

Point Polyline::operator[] (const size_t index) const
{
	if (index >= vertex) throw "Неверный индекс";
	return p[index];
}

Point& Polyline::operator[] (const size_t index)
{
	if (index >= vertex) throw "Неверный индекс";
	return p[index];
}

void Polyline::AddToEnd(const Point& point)
{
	for (size_t i = 0; i < vertex; ++i)
	{
		if ((point.x == p[i].x) && (point.y == p[i].y)) throw "Добавление уже существующей точки";
	}
	vertex += 1;
	Point* tmp = new Point[vertex];
	for (size_t i = 0; i < vertex - 1; ++i)
	{
		tmp[i] = p[i];
	}
	tmp[vertex - 1] = point;
	if (p != nullptr) delete[] p;
	p = tmp;
}

void Polyline::AddToBegin(const Point& point)
{
	for (size_t i = 0; i < vertex; ++i)
	{
		if ((point.x == p[i].x) && (point.y == p[i].y)) throw "Добавление уже существующей точки";
	}
	vertex += 1;
	Point* tmp = new Point[vertex];
	tmp[0] = point;
	for (size_t i = 1; i < vertex; ++i)
	{
		tmp[i] = p[i - 1];
	}
	if (p != NULL) delete[] p;
	p = tmp;
}

std::ostream& operator<< (std::ostream& out, const Polyline& polyline)
{
	out << "Polyline<";
	for (size_t i = 0; i < polyline.vertex; ++i)
	{
		out << "vertex[" << i << "]: " << "(" << polyline.p[i].x << "," << polyline.p[i].y;
		if (i != polyline.vertex - 1) out << "); ";
		else out << ")";
	}
	out << ">";
	return out;
}






int GetKey()
{
	int key = _getch();
	if ((key == 0) || (key == 224)) key = _getch();
	return key;
}


int Menu_1()
{
	std::cout << "\nИзменить первую ломанную - 1\nИзменить вторую ломанную - 2\nПросмотр - 3\nСложение двух ломанных - 4\nСравнение на равенство - 5\nСравнение на неравенство - 6\nВыход - Esc" << std::endl;
	while (true)
	{
		int key = GetKey();
		if ((key == 49) || (key == 50) || (key == 51) || (key == 52) || (key == 53)|| (key == 54) || (key == 27)) return key;
	}
}

int Menu_2()
{
	std::cout << "\nДобавить точку в начало  - 1\nДобавить точку в конец - 2\nИзменить вершину по индексу - 3\nРассчитать длину ломанной - 4\nНазад - Esc" << std::endl;
	while (true)
	{
		int key = GetKey();
		if ((key == 49) || (key == 50) || (key == 51) || (key == 52) || (key == 27)) return key;
	}
}


int main() {

	setlocale(LC_ALL, "Russian");

	Polyline line_1, line_2;
	while (true)
	{
		system("cls");
		std::cout << "Лабораторная работа №1. Вариант 4. Ломанные линии" << std::endl;
		int m1 = Menu_1();
		if (m1 == 49)
		{
			while (true)
			{
				system("cls");

				std::cout << line_1 << std::endl;
				int m2 = Menu_2();
				if (m2 == 49)
				{
					Point p;
					std::cout << "Введите координаты точки" << std::endl;
					std::cout << "Введите x и у через пробел: " << std::endl;
					std::cin >> p.x;
					std::cin >> p.y;
					try
					{
						line_1.AddToBegin(p);
					}
					catch (const char* err)
					{
						std::cout << err << std::endl;
						system("pause");
					}
				}
				if (m2 == 50)
				{
					Point p;
					std::cout << "Введите координаты точки" << std::endl;
					std::cout << "Введите x и у через пробел: " << std::endl;
					std::cin >> p.x;
					std::cin >> p.y;
					try
					{
						line_1.AddToEnd(p);
					}
					catch (const char* err)
					{
						std::cout << err << std::endl;
						system("pause");
					}
				}
				if (m2 == 51)
				{
					int index = 0;
					std::cout << "Введите индекс точки" << std::endl;
					std::cin >> index;
					try
					{
						std::cout << "(" << line_1[index].x << "," << line_1[index].y << ")" << std::endl;
						Point p;
						std::cout << "Введите координаты точки" << std::endl;
						std::cout << "Введите x и у через пробел: " << std::endl;
						std::cin >> p.x;
						std::cin >> p.y;
						line_1[index].x = p.x;
						line_1[index].y = p.y;
					}
					catch (const char* err)
					{
						std::cout << err << std::endl;
						system("pause");
					}
				}
				if (m2 == 52)
				{
					try
					{
						system("cls");
						std::cout << "Длина первой ломанной: " << line_1.Length() << std::endl;
						system("pause");
					}
					catch (const char* err)
					{
						std::cout << err << std::endl;
						system("pause");
					}
					
				}
				if (m2 == 27) break;
			}
		}

		if (m1 == 50)
		{
			while (true)
			{
				system("cls");
				std::cout << line_2 << std::endl;
				int m2 = Menu_2();
				if (m2 == 49)
				{
					Point p;
					std::cout << "Введите координаты точки" << std::endl;
					std::cout << "Введите x и у через пробел: " << std::endl;
					std::cin >> p.x;
					std::cin >> p.y;
					try
					{
						line_2.AddToBegin(p);
					}
					catch (const char* err)
					{
						std::cout << err << std::endl;
						system("pause");
					}
				}
				if (m2 == 50)
				{
					Point p;
					std::cout << "Введите координаты точки" << std::endl;
					std::cout << "Введите x и у через пробел: " << std::endl;
					std::cin >> p.x;
					std::cin >> p.y;
					try
					{
						line_2.AddToEnd(p);
					}
					catch (const char* err)
					{
						std::cout << err << std::endl;
						system("pause");
					}
				}
				if (m2 == 51)
				{
					int index = 0;
					std::cout << "Введите индекс точки" << std::endl;
					std::cin >> index;
					try
					{
						std::cout << "(" << line_2[index].x << "," << line_2[index].y << ")" << std::endl;
						Point p;
						std::cout << "Введите координаты точки" << std::endl;
						std::cout << "Введите x и у через пробел: " << std::endl;
						std::cin >> p.x;
						std::cin >> p.y;
						line_2[index].x = p.x;
						line_2[index].y = p.y;
					}
					catch (const char* err)
					{
						std::cout << err << std::endl;
						system("pause");
					}
				}
				if (m2 == 52)
				{
					try
					{
						system("cls");
						std::cout << "Длина второй ломанной линии: " << line_2.Length() << std::endl;
						system("pause");
					}
					catch (const char* err)
					{
						std::cout << err << std::endl;
						system("pause");
					}
				}
				if (m2 == 27) break;
			}
		}

		if (m1 == 51)
		{
			system("cls");
			std::cout << "Ваши линии:" << std::endl;
			std::cout << line_1 << std::endl;
			std::cout << line_2 << std::endl;
			system("pause");
		}



		if (m1 == 52)
		{
			system("cls");
			Polyline result = line_1 + line_2;
			std::cout << result << std::endl;
			system("pause");
		}
		if (m1 == 53)
		{
			system("cls");
			if (line_1 == line_2) std::cout << "равны" << std::endl;
			else std::cout << "не равны" << std::endl;
			system("pause");
		}

		if (m1 == 54)
		{
			system("cls");
			if (line_1 != line_2) std::cout << "не равны" << std::endl;
			else std::cout << "равны" << std::endl;
			system("pause");
		}

		if (m1 == 27) break;
	}
	return 0;
}
