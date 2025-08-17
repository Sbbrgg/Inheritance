#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define HUMAN_TAKE_PARAMETRS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETRS last_name, first_name, age

class Human
{
	std::string last_name;
	std::string first_name;
	int age;
public:
	const std::string& get_last_name() const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}

	//					Constructorû:
	Human(HUMAN_TAKE_PARAMETRS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "Hconstructor:\t" << this << endl;
	}
	~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//					Methods:
	void info()const
	{
		cout << last_name << " " << first_name << " " << age << endl;
	}
};

#define STUDENT_TAKE_PARAMETRS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETRS speciality, group, rating, attendance

class Student :public Human
{
	std::string speciality;
	std::string group;
	double rating;				//Óñïåâàåìîñòü
	double attendance;			//Ïîñåùàåìîñòü
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this -> group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//						Constructors:
	Student(HUMAN_TAKE_PARAMETRS, STUDENT_TAKE_PARAMETRS): Human(HUMAN_GIVE_PARAMETRS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//						Methods:
	void info() const
	{
		Human::info();
		cout << speciality << " " << group << " " << rating << " " << attendance << endl;
	}
};

#define TEACHER_TAKE_PARAMETRS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETRS speciality, experience

class Teacher :public Human 
{
	std::string speciality;
	int experience;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	int get_experience() const
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(int experience)
	{
		this->experience = experience;
	}

	//				Constructors:
	Teacher(HUMAN_TAKE_PARAMETRS, TEACHER_TAKE_PARAMETRS) : Human(HUMAN_GIVE_PARAMETRS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor: \t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor" << this << endl;
	}
	void info()const
	{
		Human::info();
		cout << speciality << " " << experience << endl;
	}
};

#define GRADUATE_TAKE_PARAMETRS const std::string& thesis_topic, double thesis_score
#define GRADUATE_GIVE_PARAMETRS thesis_topic, thesis_score

class Graduate :public Student
{
	std::string thesis_topic;
	double thesis_score;
public:
	const std::string& get_thesis_topic()const
	{
		return thesis_topic;
	}
	double get_thesis_score() const
	{
		return thesis_score;
	}
	void set_thesis_topic(const std::string& thesis_topic)
	{
		this->thesis_topic = thesis_topic;
	}
	void set_thesis_score(double thesis_score)
	{
		this->thesis_score = thesis_score;
	}

	//					Constructors:
	Graduate(HUMAN_TAKE_PARAMETRS, STUDENT_TAKE_PARAMETRS, GRADUATE_TAKE_PARAMETRS)
		:Student(HUMAN_GIVE_PARAMETRS, STUDENT_GIVE_PARAMETRS)
	{
		set_thesis_topic(thesis_topic);
		set_thesis_score(thesis_score);
		cout << "GConstructor" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor" << this << endl;
	}

	void info() const
	{
		Student::info();
		cout << "Thesis: " << thesis_topic << " " << thesis_score << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	Human human("Montano", "Antonio", 25);
	human.info();

	Student student("Pincman", "Jessy", 22, "chemistry", "WW_220", 95, 98);
	student.info();

	Teacher teacher("White", "Whalter", 50, "Chemistry", 25);
	teacher.info();

	Graduate graduate("Flow", "Sergey", 20, "programm", "GR_2025", 93, 92, "C++", 96);
	graduate.info();
}