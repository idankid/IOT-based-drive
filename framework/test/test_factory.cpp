/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-12
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include <iostream>
#include <string>
#include "factory.hpp"

enum type
{
	SQUARE =1,
	CIRCLE = 2
};

class Shape
{
public:
	Shape(std::string name = "shape", int num = 5);
	virtual ~Shape();
	void draw();
private:
	std::string m_name;
	int m_num;
};

Shape::Shape(std::string name, int num): m_name(name), m_num(num){}

Shape::~Shape(){}

void Shape::draw()
{
	std::cout << m_name << m_num << std::endl;
}

class Square : public Shape
{
public:
	Square(int num);
	~Square();
};

Square::Square(int num): Shape("Square", num){}

Square::~Square(){}

class Circle : public Shape
{
public:
	Circle(int num);
	~Circle();
};

Circle::Circle(int num): Shape("Circle", num){}

Circle::~Circle(){}

std::shared_ptr<Shape> CreateSquare(int num)
{
	return std::make_shared<Square>(num);
}

std::shared_ptr<Shape> CreateCircle(int num)
{
	return std::make_shared<Circle>(num);
}

int main()
{
	ilrd::Factory<type, Shape, int> factory;
	factory.Register(type::CIRCLE, CreateCircle);
	factory.Register(type::SQUARE, CreateSquare);

	std::shared_ptr<Shape> s1 = factory.Create(type::CIRCLE, 9);
	std::shared_ptr<Shape> s2 = factory.Create(type::SQUARE, 6);

	s1->draw();
	s2->draw();

	return 0;
}
