#pragma once
#include <iostream>
#include <string>
#include <map>
using std::cout;
using std::endl;
using std::map;
using std::string;

// 元素类
class AbstractShape
{
public:
	virtual ~AbstractShape() {}
	virtual void drawShape() = 0;
};

class CircleShape : public AbstractShape
{
public:
	CircleShape(string color = "white", int xPos = 0, int yPos = 0, int radius = 0) : m_color(color), m_xPos(xPos), m_yPos(yPos), m_radius(radius) {}
	virtual ~CircleShape() { }

	virtual void drawShape() { cout << "In <" << m_xPos << "," << m_yPos << "> With Color " << m_color << " Draw A Circle." << endl; }

public:
	void setColor(string color) { m_color = color; }
	void setXpos(int pos)		{ m_xPos = pos; }
	void setYpos(int pos)		{ m_yPos = pos; }
	void setRadius(int radius)  { m_radius = radius; }

private:
	string	m_color;
	int		m_xPos;
	int		m_yPos;
	int		m_radius;
};

// 享元模式
class ShapeFactory
{
public:
	ShapeFactory() { }
	~ShapeFactory();

	AbstractShape* getShape(string color);

private:
	map<string, AbstractShape*> m_CircleMap;
};

// 享元模式测试函数
void ShapeFactoryTestDemo();