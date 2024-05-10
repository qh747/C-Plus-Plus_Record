#include "ShareElement.h"

ShapeFactory::~ShapeFactory()
{
	for (map<string, AbstractShape*>::iterator iter = m_CircleMap.begin(); iter != m_CircleMap.end(); ++iter)
	{
		delete (iter->second);
	}
}

AbstractShape* ShapeFactory::getShape(string color)
{
	// 享元模式为复用已经存在的对象，而对不存在的对象新创建
	map<string, AbstractShape*>::iterator iter = m_CircleMap.find(color);
	if (m_CircleMap.end() == iter)
	{
		AbstractShape* pNewObj = new CircleShape(color);
		m_CircleMap.insert(make_pair(color, pNewObj));
		return pNewObj;
	}
	else
		return m_CircleMap.find(color)->second;
}

void ShapeFactoryTestDemo()
{
	ShapeFactory circleFactory;
	// 新建一个元素
	CircleShape* circlePtr = dynamic_cast<CircleShape *>(circleFactory.getShape("green"));
	circlePtr->setXpos(10);
	circlePtr->setYpos(10);
	circlePtr->setRadius(10);
	circlePtr->drawShape();

	// 复用元素
	circlePtr = dynamic_cast<CircleShape*>(circleFactory.getShape("green"));
	circlePtr->drawShape();

	// 修改元素属性
	circlePtr->setXpos(30);
	circlePtr->setYpos(30);
	circlePtr->setRadius(30);
	circlePtr->drawShape();
}