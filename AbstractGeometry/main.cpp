#include<iostream>
#include<Windows.h>
using namespace std;

#define pi 3.14159

namespace Geometry
{

#define delimetr "\n--------------------------------------------------------\n"

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

#define SHAPE_TAKE_PARAMETERS	int start_x, int start_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETERS	start_x, start_y, line_width, color

	class Shape
	{
	protected:
		Color color;
		int start_x;
		int start_y;
		int line_width;
	public:
		static const int MIN_START_X = 100;
		static const int MIN_START_Y = 100;
		static const int MAX_START_X = 1000;
		static const int MAX_START_Y = 600;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 16;
		static const int MIN_SIZE = 32;
		static const int MAX_SIZE = 768;

		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		void set_start_x(int start_x)
		{
			this->start_x =
				start_x < MIN_START_X ? MIN_START_X :
				start_x > MAX_START_X ? MAX_START_X :
				start_x;
		}
		void set_start_y(int start_y)
		{
			this->start_y =
				start_y < MIN_START_Y ? MIN_START_Y :
				start_y > MAX_START_Y ? MAX_START_Y :
				start_y;
		}
		void set_line_width(int line_width)
		{
			this->line_width =
				line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH :
				line_width > MAX_LINE_WIDTH ? MAX_LINE_WIDTH :
				line_width;
		}
		int get_start_x()const
		{
			return start_x;
		}
		int get_start_y()const
		{
			return start_y;
		}
		int get_line_width()const
		{
			return line_width;
		}

		virtual double get_area()const = 0;			//Площадь
		virtual double get_perimeter()const = 0;	//Периметр
		virtual void draw()const = 0;				//Рисование
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
		}
	};
	/*class Square :public Shape
	{
		double side;
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
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
	};*/
	class Rectangle :public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		void set_width(double width)
		{
			this->width =
				width < MIN_SIZE ? MIN_SIZE :
				width > MAX_SIZE ? MAX_SIZE :
				width;
		}
		void set_height(double height)
		{
			this->height =
				height < MIN_SIZE ? MIN_SIZE :
				height > MAX_SIZE ? MAX_SIZE :
				height;
		}
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
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
			//1) Получаем окно консоли:
			HWND hwnd = GetConsoleWindow();

			//2) Получаем контекст устройства (DC - Device Context) для окна консоли:
			HDC hdc = GetDC(hwnd);	// DC - это то, на чём мы будем рисовать

			//3) Создадим инструменты, которыми мы будем рисовать
			HPEN hPen = CreatePen(PS_SOLID, 5, color);	// Карандаш (Pen) рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color);	// Кисть (Brush) рисует зливку фигуры

			//4) Выберем созданнеы инструменты
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//5) После того, как все необходимые инструменты созданы и выбраны, можно рисовать
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);

			//6) hdc, hPen, hBrush занимают ресурсы, а ресурсы нужно освобождать:
			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Стороны: " << width << "x" << height << endl;
			Shape::info();
		}
	};
	class Square :public Rectangle
	{
	public:
		Square(int side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона квадрата: " << get_width() << endl;
			Shape::info();
		}
	};
	class Ellipse :public Shape
	{
	protected:
		double radius_x;
		double radius_y;
	public:
		Ellipse(double radius_x, double radius_y, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius_x(radius_x);
			set_radius_y(radius_y);
		}
		void set_radius_x(double x)
		{
			this->radius_x =
				x < MIN_SIZE ? MIN_SIZE :
				x > MAX_SIZE ? MAX_SIZE :
				x;
		}
		void set_radius_y(double y)
		{
			this->radius_y =
				y < MIN_SIZE ? MIN_SIZE :
				y > MAX_SIZE ? MAX_SIZE :
				y;
		}
		double get_radius_x()const { return radius_x; }
		double get_radius_y()const { return radius_y; }

		double get_area()const override
		{
			return pi * radius_x * radius_y;
		}
		double get_perimeter()const override
		{
			return (pi * (3 * (radius_x + radius_y) - sqrt((3 * radius_x + radius_y) * (radius_x + 3 * radius_y)))) / 2;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc,
				start_x - radius_x, start_y - radius_y,
				start_x + radius_x, start_y + radius_y);

			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиусы: " << radius_x << "x" << radius_y << endl;
			Shape::info();
		}
	};
	class Circle :public Ellipse
	{
	public:
		Circle(double radius, SHAPE_TAKE_PARAMETERS) 
			:Ellipse(radius, radius, SHAPE_GIVE_PARAMETERS){}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус: " << get_radius_x() << endl;
			Shape::info();
		}
	};
	
}

void main()
{
	setlocale(LC_ALL, "");
	cout << hex << Geometry::Color::SomeColor << endl;
	cout << delimetr << endl;

	Geometry::Square square(5, 100, 100, 1, Geometry::Color::Red);
	/*cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();
	cout << delimetr << endl;

	Geometry::Rectangle rect(150, 100, 550, 100, 2, Geometry::Color::Orange);
	rect.info();
	cout << delimetr << endl;


	Geometry::Ellipse ell(120, 80, 400, 250, 2, Geometry::Color::Green);
	ell.info();
	cout << delimetr << endl;

	Geometry::Circle circ(90, 700, 300, 3, Geometry::Color::Yellow);
	circ.info();
	while (true)
	{
		ell.draw();
		circ.draw();
	}
}