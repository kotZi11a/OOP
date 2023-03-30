#include <fstream>
#include <string>

using namespace std;

class Rectangle
{
	double x, y;
	double length, width;

public:

	Rectangle() // Конструктор без параметров
	{
		x = 0;
		y = 0;
		length = 0;
		width = 0;
	}

	Rectangle(double nx, double ny, double l, double w) // Конструктор с параметрами(x,y, leight, width)
	{
		x = nx;
		y = ny;
		length = l;
		width = w;
	}

	Rectangle(Rectangle& copy) // Конструктор копирования
	{
		x = copy.x;
		y = copy.y;
		length = copy.length;
		width = copy.width;
	}

	~Rectangle() {} // Деструктор

	void shift_coord(double nx, double ny) // Изменение координат
	{
		x = nx;
		y = ny;
	}

	void shift_lside(double nl) // Изменение длины прямоугольника
	{
		if (nl >= 0)
			length = nl;
		else
			throw runtime_error("Negative side");
	}

	void shift_wside(double nw) // Изменение длины прямоугольника
	{
		if (nw >= 0)
			width = nw;
		else
			throw runtime_error("Negative side");
	}

	double square() { return length * width; } // Площадь прямоугольника

	double perimeter() { return (length * 2) + (width * 2); } // Периметр прямоугольника

	Rectangle& operator=(Rectangle& right) // Перегрузка оператора присваивания
	{
		if (this != &right)
		{
			x = right.x;
			y = right.y;
			length = right.length;
			width = right.width;
		}
		return *this;
	}

	friend Rectangle& operator+(const Rectangle& left, const Rectangle& right) // Перегрузка оператора сложения
	{
		Rectangle* sum = new Rectangle;
		sum->x = (left.x + right.x) / 2;
		sum->y = (left.y + right.y) / 2;
		sum->length = left.length + right.length;
		sum->width = left.width + right.width;
		return *sum;
	}

	friend istream& operator>>(istream& inp, Rectangle& rec) // Ввод пряугольник через перегрузку
	{
		inp >> rec.x >> rec.y >> rec.length >> rec.width;
		if (rec.length < 0 || rec.width < 0)
			throw runtime_error("Negative side");
		return inp;
	}

	friend ostream& operator<<(ostream& out, Rectangle rec) // Вывод прямоугольника через перегрузку
	{
		out << "Coordinate (" << rec.x << ";" << rec.y << ") lenght: " << rec.length << " width: " << rec.width;
		return out;
	}

	friend bool operator<(Rectangle& left, Rectangle& right) // Операторы сравнения по площади
	{
		return (left.square() < right.square());
	}

	friend bool operator<=(Rectangle& left, Rectangle& right)
	{
		return (!(left.square() > right.square()));
	}

	friend bool operator>(Rectangle& left, Rectangle& right)
	{
		return (left.square() > right.square());
	}

	friend bool operator>=(Rectangle& left, Rectangle& right)
	{
		return (!(left.square() < right.square()));
	}

	friend bool operator==(Rectangle& left, Rectangle& right)
	{
		return ((left.length == right.length && left.width == right.width) || (left.length == right.width && left.width == right.length));
	}

};

int main()
{
	ifstream inp("input.txt");// Открытие файла ввода
	Rectangle test; // Создание прямоугольника
	Rectangle test2;
	double l, d; // Длина и ширина для изменения
	int k; // Ключ для тестов
	inp >> k ; // Выбор проверки метода
	ofstream out("output.txt"); // Открытие файла вывода
	switch (k)
	{
	case 1: // Проверка 1 метода из задания(Изменение координат центра прямоугольника)
		double x, y;
		inp >> x >> y;
		test.shift_coord(x, y);
		out << test;
		break;
	case 2: // Проверка 2 метода из задания(Изменение сторон прямоугольника)
		inp >> l >> d;
		test.shift_lside(l);
		test.shift_wside(d);
		out << test;
		break;
	case 3: // Проверка 3 метода из задания(Нахождение площади)
		inp >> l >> d;
		test.shift_lside(l);
		test.shift_wside(d);
		out << "S = " << test.square();
		break;
	case 4: // Проверка 4 метода из задания(Нахождение периметра)
		inp >> l >> d;
		test.shift_lside(l);
		test.shift_wside(d);
		out << "P = " << test.perimeter();
		break;
	case 5: // Проверка 5 метода из задания(Сложение прямоугольников)
		inp >> l >> d;
		test.shift_lside(l);
		test.shift_wside(d);
		test2=test;
		test2.shift_coord(4, 4);
		out << (test + test2);
		break;
	case 6: // Проверка операций сравнения
		test.shift_lside(3);
		test.shift_wside(4);
		test2 = test;
		out << (test2 == test);
	default:
		break;
	}
	inp.close();// Закрытие файлов
	out.close();
}