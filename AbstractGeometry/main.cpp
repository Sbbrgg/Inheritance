#define _USE_MATH_DEFINES
#include<iostream>
#include<Windows.h>
using namespace std;

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

		mutable HWND hwnd;
		mutable HDC hdc;
		mutable HPEN hPen;
		mutable HBRUSH hBrush;
		void draw_begin()const
		{
			this->hwnd = GetConsoleWindow();
			this->hdc = GetDC(hwnd);
			this->hPen = CreatePen(PS_SOLID, line_width, color);
			this->hBrush = CreateSolidBrush(color);
			SelectObject(this->hdc, this->hPen);
			SelectObject(this->hdc, this->hBrush);
		}
		void draw_end()const
		{
			DeleteObject(this->hBrush);
			DeleteObject(this->hPen);
			ReleaseDC(this->hwnd, this->hdc);
		}
		virtual void draw_figure(HDC hdc) const = 0;
	public:
		static const int MIN_START_X = 100;
		static const int MIN_START_Y = 100;
		static const int MAX_START_X = 1000;
		static const int MAX_START_Y = 600;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 16;
		static const int MIN_SIZE = 32;
		static const int MAX_SIZE = 512;

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

		int filter_size(int size)const
		{
			return
				size < MIN_SIZE ? MIN_SIZE :
				size > MAX_SIZE ? MAX_SIZE :
				size;
		}

		virtual double get_area()const = 0;			//Площадь
		virtual double get_perimeter()const = 0;	//Периметр
		//virtual void draw()const = 0;				//Рисование
		void draw()const
		{
			draw_begin();
			draw_figure(hdc);
			draw_end();
		}

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
			this->width = filter_size(width);
		}
		void set_height(double height)
		{
			this->height = filter_size(height);
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

		void draw_figure(HDC hdc) const override
		{
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);
		}
		//void draw()const override
		//{
		//	//1) Получаем окно консоли:
		//	HWND hwnd = GetConsoleWindow();

		//	//2) Получаем контекст устройства (DC - Device Context) для окна консоли:
		//	HDC hdc = GetDC(hwnd);	// DC - это то, на чём мы будем рисовать

		//	//3) Создадим инструменты, которыми мы будем рисовать
		//	HPEN hPen = CreatePen(PS_SOLID, 5, color);	// Карандаш (Pen) рисует контур фигуры
		//	HBRUSH hBrush = CreateSolidBrush(color);	// Кисть (Brush) рисует зливку фигуры

		//	//4) Выберем созданнеы инструменты
		//	SelectObject(hdc, hPen);
		//	SelectObject(hdc, hBrush);

		//	//5) После того, как все необходимые инструменты созданы и выбраны, можно рисовать
		//	::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);

		//	//6) hdc, hPen, hBrush занимают ресурсы, а ресурсы нужно освобождать:
		//	DeleteObject(hPen);
		//	DeleteObject(hBrush);

		//	ReleaseDC(hwnd, hdc);
		//}
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
	};

	class Circle :public Shape
	{
		double radius;
	public:
		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}

		void set_radius(double radius)
		{
			this->radius = filter_size(radius);
		}
		double get_radius()const
		{
			return radius;
		}
		double get_diametr()const
		{
			return 2 * radius;
		}
		double get_area()const override
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const override
		{
			return M_PI * get_diametr();
		}

		void draw_figure(HDC hdc)const override
		{
			::Ellipse(hdc, start_x, start_y, start_x + get_diametr(), start_y + get_diametr());
		}
		/*void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + get_diametr(), start_y + get_diametr());

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);

		}*/
		void info()const override
		{

		}
	};
	class Triangle :public Shape
	{
	public:
		Triangle(SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS) {}
		virtual double get_height()const = 0;
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			Shape::info();
		}
	};
	class EquilateralTriangle :public Triangle
	{
		// Равносторонний
		double side;
	public:
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		double get_side()const
		{
			return side;
		}
		double get_height()const
		{
			//return sqrt(3) * get_side() / 2;
			return sqrt(pow(side, 2) - pow(side / 2, 2));
		}
		double get_area()const
		{
			return side * get_height() / 2;
		}
		double get_perimeter()const
		{
			return 3 * side;
		}

		void draw_figure(HDC hdc)const override
		{
			const POINT vertices[] =
			{
				{ start_x, start_y + get_height() },
				{ start_x + side, start_y + get_height() },
				{ start_x + side / 2, start_y }
			};// вершины
			::Polygon(hdc, vertices, 3);
		}
		//void draw()const override
		//{
		//	HWND hwnd = GetConsoleWindow();
		//	HDC hdc = GetDC(hwnd);
		//	HPEN hPen = CreatePen(PS_SOLID, line_width, color);
		//	HBRUSH hBrush = CreateSolidBrush(color);

		//	SelectObject(hdc, hPen);
		//	SelectObject(hdc, hBrush);

		//	const POINT vertices[] =
		//	{
		//		{ start_x, start_y + get_height() },
		//		{ start_x + side, start_y + get_height() },
		//		{ start_x + side / 2, start_y }
		//	};// вершины
		//	::Polygon(hdc, vertices, 3);

		//	DeleteObject(hBrush);
		//	DeleteObject(hPen);
		//	ReleaseDC(hwnd, hdc);
		//}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона: " << side << endl;
			cout << "Высота: " << get_height() << endl;
			Shape::info();
		}
	};

	class IsoscelesTriangle :public Triangle
	{
		// Равнобедренный
		double side;
		double base;
	public:
		IsoscelesTriangle(double base, double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_base(base);
			set_side(side);
		}
		void set_base(double base)
		{
			this->base = filter_size(base);
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		double get_base()const { return base; }
		double get_side()const { return side; }

		double get_height()const override { return sqrt(pow(side, 2) - pow(base / 2, 2)); }
		double get_area()const override
		{
			return base * get_height() / 2;
		}
		double get_perimeter()const override
		{
			return base + side * 2;
		}

		void draw_figure(HDC hdc)const override
		{
			const POINT vertices[] =
			{
				{start_x, start_y + get_height()},
				{start_x + base, start_y + get_height()},
				{start_x + base / 2, start_y},
			};
			::Polygon(hdc, vertices, 3);
		}
		/*void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			const POINT vertices[] =
			{
				{start_x, start_y + get_height()},
				{start_x + base, start_y + get_height()},
				{start_x + base / 2, start_y},
			};
			::Polygon(hdc, vertices, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}*/
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Основание: " << base << endl;
			cout << "Боковая сторона: " << side << endl;
			cout << "Высота: " << get_height() << endl;
			Shape::info();
		}
	};
	class RightAngledTriangle :public Triangle
	{
		// Прямоугольный
		double base;
		double height;
	public:
		RightAngledTriangle(double base, double height, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_base(base);
			set_height(height);
		}
		void set_base(double base) { this->base = base; }
		void set_height(double height) { this->height = height; }

		double get_base()const { return base; }
		double get_height()const override { return height; }

		double get_area()const override
		{
			return base * height / 2;
		}
		double get_perimeter()const override
		{
			return base + height + sqrt(pow(base, 2) + pow(height, 2));
		}

		void draw_figure(HDC hdc)const override
		{
			const POINT verices[] =
			{
				{ start_x, start_y + height },
				{ start_x + base, start_y + height },
				{ start_x, start_y }
			};
			::Polygon(hdc, verices, 3);
		}
		/*void draw() const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			const POINT verices[] =
			{
				{ start_x, start_y + height },
				{ start_x + base, start_y + height },
				{ start_x, start_y }
			};
			::Polygon(hdc, verices, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}*/
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Катет a: " << base << endl;
			cout << "Катет b: " << height << endl;
			cout << "Гипотенуза: " << sqrt(pow(base, 2) + pow(height, 2)) << endl;
			Shape::info();
		}
	};
	class DefaultTriangle :public Triangle
	{
		double a;
		double b;
		double c;
	public:
		DefaultTriangle(double a, double b, double c, SHAPE_TAKE_PARAMETERS)
			:Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_sides(a, b, c);
		}
		void set_sides(double a, double b, double c)
		{
			if ((a + b) > c && (a + c) > b && (b + c) > a)
			{
				this->a = filter_size(a);
				this->b = filter_size(b);
				this->c = filter_size(c);
			}
			else
			{
				this->a = this->b = this->c = 1;
			}
		}
		double get_a()const { return a; }
		double get_b()const { return b; }
		double get_c()const { return c; }

		double get_height() const override
		{
			return (2 * get_area()) / a;
		}
		double get_area()const override
		{
			double p = get_perimeter() / 2;
			return sqrt(p * (p - a) * (p - b) * (p - c));
		}
		double get_perimeter()const override
		{
			return a + b + c;
		}

		void draw_figure(HDC hdc)const override
		{
			const POINT vertices[] =
			{
				{start_x, start_y + get_height()},
				{start_x + a, start_y + get_height()},
				{start_x + a / 2, start_y}
			};
			::Polygon(hdc, vertices, 3);
		}
		/*void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			const POINT vertices[] =
			{
				{start_x, start_y + get_height()},
				{start_x + a, start_y + get_height()},
				{start_x + a / 2, start_y}
			};
			::Polygon(hdc, vertices, 3);

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}*/
		void info() const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Стороны: " << a << ", " << b << ", " << c << endl;
			cout << "Высота к стороне a: " << get_height() << endl;
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

	Geometry::Rectangle rect(15000, 10000, 150, 100, 2, Geometry::Color::Orange);
	rect.info();
	cout << delimetr << endl;

	Geometry::Circle circle(50, 800, 200, 1, Geometry::Color::Yellow);
	circle.info();
	cout << delimetr << endl;

	Geometry::EquilateralTriangle e_triangle(50, 550, 350, 32, Geometry::Color::Green);
	e_triangle.info();
	cout << delimetr << endl;

	Geometry::IsoscelesTriangle iso(150, 120, 500, 300, 2, Geometry::Color::Blue);
	iso.info();
	cout << delimetr << endl;
	Geometry::RightAngledTriangle ra(120, 80, 700, 400, 2, Geometry::Color::Orange);
	ra.info();
	cout << delimetr << endl;
	Geometry::DefaultTriangle def(100, 120, 150, 300, 500, 2, Geometry::Color::Red);
	def.info();

	Sleep(1000);
	system("cls");
	while (true)
	{
		rect.draw();
		Sleep(1000);
		system("cls");

		square.draw();
		Sleep(1000);
		system("cls");

		circle.draw();
		Sleep(1000);
		system("cls");

		e_triangle.draw();
		Sleep(1000);
		system("cls");

		iso.draw();
		Sleep(1000);
		system("cls");

		ra.draw();
		Sleep(1000);
		system("cls");

		def.draw();
		Sleep(1000);
		system("cls");
	}
}