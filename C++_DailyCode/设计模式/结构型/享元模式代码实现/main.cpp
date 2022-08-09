#include <iostream>
#include <cstring>
#include <string>
#include <map>
using namespace std;

/*图形基类    **/
class Shape
{
public:
	virtual ~Shape() { }

public:
	virtual void drawShape() = 0;
};

/*圆形具体类    **/
class Circle : public Shape
{
public:
	Circle(string color = "white", int xPos = 0, int yPos = 0, int radius = 0) : m_color(color), m_xPos(xPos), m_yPos(yPos), m_radius(radius) { }
	virtual ~Circle() { }

public:
	virtual void drawShape()
	{
		cout << "In <" << m_xPos << "," << m_yPos << "> With Color " << m_color << " Draw A Circle." << endl;
	}

public:
	void setColor(string color) { m_color = color; }
	void setXpos(int pos) { m_xPos = pos; }
	void setYpos(int pos) { m_yPos = pos; }
	void setRadius(int radius) { m_radius = radius; }

private:
	string	m_color;
	int		m_xPos;
	int		m_yPos;
	int		m_radius;
};

/*图形类工厂    **/
class ShapeFactory
{
public:
	ShapeFactory() { }
	~ShapeFactory()
	{
		for (map<string, Shape*>::iterator iter = m_CircleMap.begin(); iter != m_CircleMap.end(); ++iter)
		{
			delete (iter->second);
		}
	}

public:
	Shape* getShape(string color)
	{
		Shape* circlePtr = NULL;
		if (m_CircleMap.end() == m_CircleMap.find(color))	/*享元模式为复用已经存在的对象，而对不存在的对象新创建    **/
		{
			cout << "Create New Circle." << endl;
			circlePtr = new Circle(color);
			m_CircleMap.insert(make_pair(color, circlePtr));
		}
		else
		{
			cout << "Use A Exists Circle." << endl;
			circlePtr = m_CircleMap.find(color)->second;

		}

		return circlePtr;
	}

private:
	map<string, Shape*> m_CircleMap;
};

int main()
{
	ShapeFactory circleFactory;
	/*新创建一个绿色的圆    **/
	Circle* circlePtr = dynamic_cast<Circle *>(circleFactory.getShape("green"));
	circlePtr->setXpos(10);
	circlePtr->setYpos(10);
	circlePtr->setRadius(10);
	circlePtr->drawShape();

	/*新创建一个红色的圆    **/
	circlePtr = dynamic_cast<Circle*>(circleFactory.getShape("red"));
	circlePtr->setXpos(20);
	circlePtr->setYpos(20);
	circlePtr->setRadius(20);
	circlePtr->drawShape();

	/*使用一个已经存在的绿色的圆    **/
	circlePtr = dynamic_cast<Circle*>(circleFactory.getShape("green"));
	circlePtr->setXpos(30);
	circlePtr->setYpos(30);
	circlePtr->setRadius(30);
	circlePtr->drawShape();

	system("pause");
	return 0;
}