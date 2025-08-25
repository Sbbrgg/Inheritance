#include<iostream>
using namespace std;

#define delimeter "\n--------------------------------------------------------\n"
#define pi 3.14

enum Color
{
	//прозрачность, синий, зелёный, красный
	Red = 0x000000FF,
	Green = 0x0000FF00,
	Blue = 0x00FF0000,
	Yellow = 0x0000FFFF,
	Orange = 0x0000A5FF,
	White = 0x00FFFFFF,
	SomeColor,// = 0x00FFFFFF + 1;
};

class Shape
{
	Color color;
public:
	Shape(Color color):color(color){}
	virtual double get_area()const = 0;			//Площадь
	virtual double get_perimeter()const = 0;	//Периметр
	virtual void draw()const = 0;				//Рисование
	virtual void info()const
	{
		cout << "Площадь фигуры: " << get_area() << endl;
		cout << "Периметр фигуры: " << get_perimeter() << endl;
		draw();
	}
};

class Square :public Shape
{
	double side;
public:
	Square(double side, Color color) :Shape(color)
	{
		set_side(side);
	}
	double get_side()const
	{
		return side;
	}
	void set_side(double side)
	{
		this->side = side;
	}
	double get_area()const override
	{
		return side * side;
	}
	double get_perimeter()const override
	{
		return side * 4;
	}
	void draw()const override
	{
		for (int i = 0; i < side; i++)
		{
			for (int j = 0; j < side; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
	void info()const override
	{
		cout << typeid(*this).name() << endl;
		cout << "Длина стороны квадрата: " << get_side() << endl;
		Shape::info();
	}
};
class Rectangle:public Shape
{
	double width;
	double height;
public:
	Rectangle(double width, double height, Color color = White) : Shape(color)
	{
		set_width(width);
		set_height(height);
	}
	double get_width()const
	{
		return width;
	}
	double get_height()const
	{
		return height;
	}
	void set_width(double width)
	{
		this->width = width;
	}
	void set_height(double height)
	{
		this->height = height;
	}

	double get_area()const override
	{
		return width * height;
	}
	double get_perimeter()const override
	{
		return (width + height) * 2;
	}
	void draw()const override
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
	void info()const override
	{
		cout << "Длина ширины прямоугольника: " << get_width() << endl;
		cout << "Длина высоты прямоугольника: " << get_height() << endl;
		Shape::info();
	}
};
class Triangle :public Shape
{
	double a;
	double b;
	double c;
public:
	Triangle(double a, double b, double c, Color color = White) :Shape(color)
	{
		set_sides(a, b, c);
	}
	double get_side_a()const
	{
		return a;
	}
	double get_side_b()const
	{
		return b;
	}
	double get_side_c()const
	{
		return c;
	}
	/*void set_a(double a)
	{
		this->a = a;
	}
	void set_b(double b)
	{
		this->b = b;
	}
	void set_c(double c)
	{
		this->c = c;
	}*/
	void set_sides(double a, double b, double c)
	{
		if (((a + b) > c) and ((a + c) > b) and ((b + c) > a) and a > 0 and b > 0 and c > 0)
		{
			this->a = a;
			this->b = b;
			this->c = c;
		}
		else
		{
			this->a = this->b = this->c = 1;
		}
	}
	double get_area()const override
	{
		double p = get_perimeter() / 2;
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}
	double get_perimeter() const override
	{
		return a + b + c;
	}
	void draw()const override
	{
		cout << "\t***\n       pupupu\n\t***";
	}
	void info()const override
	{
		cout << "Первая сторона" << get_side_a() << endl;
		cout << "Вторая сторона" << get_side_b() << endl;
		cout << "Третья сторона" << get_side_c() << endl;
		Shape::info();
	}
};
class Circle :public Shape
{
	double radius;
public:
	Circle(double radius, Color color = White) :Shape(White)
	{
		set_radius(radius);
	}
	double get_radius()const
	{
		return radius;
	}
	void set_radius(double radius)
	{
		this->radius = radius > 0 ? radius : 1;
	}
	double get_area()const override
	{
		return pi * radius * radius;
	}
	double get_perimeter()const override
	{
		return 2 * pi * radius;
	}

	void draw()const override
	{
		cout << "\n\t\t\tO\n";
	}
	void info()const override
	{
		cout << "Радиус окружности: " << get_radius() << endl;
		Shape::info();
	}
};
void main()
{
	setlocale(LC_ALL, "");
	cout << hex << Color::SomeColor << endl;

	Square square(5, Color::Red);
	/*cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	cout << delimeter << endl;
	Rectangle rectangle(7, 3, Color::Blue);
	rectangle.info();

	cout << delimeter << endl;
	Triangle triangle(3, 4, 5, Color::Orange);
	triangle.info();

	cout << delimeter << endl;
	Circle circle(7, Color::Orange);
	circle.info();
}