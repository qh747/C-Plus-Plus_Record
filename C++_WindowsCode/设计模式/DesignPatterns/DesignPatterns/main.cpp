#include "../ObjectPrinciple/OpenClosePrinciple.h"
#include "../ObjectPrinciple/DMTPrinciple.h"
#include "../ObjectPrinciple/SyncMultipPrinciple.h"
#include "../ObjectPrinciple/RelyInersionPrinciple.h"
#include "../CreateType/SimpleFactory.h"
#include "../CreateType/FactoryMethod.h"
#include "../CreateType/AbstractFactory.h"
#include "../CreateType/HungrySingleton.h"
#include "../CreateType/LazySingleton.h"
#include "../CreateType/ThreadSingleton.h"
#include "../CreateType/Builder.h"
#include "../CreateType/ProtoType.h"
#include "../StructuralType/ObjAdapter.h"
#include "../StructuralType/Facade.h"
#include "../StructuralType/ShareElement.h"
#include "../StructuralType/Proxy.h"
#include "../StructuralType/Decorator.h"
#include "../StructuralType/Component.h"
#include "../StructuralType/Bridging.h"
#include "../BehavioralType/TemplateMethod.h"
#include "../BehavioralType/Strategy.h"
#include "../BehavioralType/Observer.h"
#include "../BehavioralType/Command.h"
#include "../BehavioralType/ResponsibilityChain.h"
#include "../BehavioralType/Memento.h"
#include "../BehavioralType/Mediator.h"
#include "../BehavioralType/StateMode.h"
#include "../BehavioralType/Interpreter.h"
#include "../BehavioralType/VistorMode.h"

// 面向对象设计原则测试程序
void ObjectPrincipleTestDemo();

// 创建型设计模式
void CreateTypeDesignModeTestDemo();

// 结构型设计模式
void StructrualTypeDesignModeTestDemo();

// 行为型设计模式
void BehavioralTypeDesignModeTestDemo();

int main()
{
	// 面向对象设计原则测试程序
	// ObjectPrincipleTestDemo();

	// 创建型设计模式
	// CreateTypeDesignModeTestDemo();

	// 结构型设计模式
	// StructrualTypeDesignModeTestDemo();

	// 行为型设计模式
	BehavioralTypeDesignModeTestDemo();

	return 0;
}

// 面向对象设计原则测试程序
void ObjectPrincipleTestDemo()
{
	// 开闭原则测试函数
	// OpenClosePrincipleTestDemo();

	// 创建型设计模式
	// CreateTypeDesignModeTestDemo();

	// 迪米特法则测试函数
	// DMTPrincipleTestDemo();

	// 合成复用测试函数
	// SyncMultipPrincipleTestDemo();

	// 依赖倒转原则测试函数
	// RelyOnInersionPrincipleTestDemo();
}

// 创建型设计模式
void CreateTypeDesignModeTestDemo()
{
	// 简单工厂模式测试
	// SimpleFactoryTestDemo();

	// 工厂方法模式测试
	// FactoryMethodTestDemo();

	// 抽象工厂模式测试函数
	// AbstractFactoryTestDemo();

	// 饿汉式单例模式测试函数
	// HungrySingletonTestDemo();

	// 懒汉式单例模式测试函数
	// LazySingletonTestDemo();

	// 多线程单例模式测试函数
	// ThreadSingletonTestDemo();

	// 构建器模式测试函数
	// BuilderTestDemo();

	// 原型模式测试函数
	// ProtoTypeTestDemo();
}

// 结构型设计模式
void StructrualTypeDesignModeTestDemo()
{
	// 适配器模式测试函数
	// ClassAdapterTestDemo();
	// ObjAdapterTestDemo();

	// 外观模式测试函数
	// FacadeTestDemo();

	// 享元模式测试函数
	// ShapeFactoryTestDemo();

	// 代理模式测试函数
	// ProxyTestDemo();

	// 装饰器模式测试函数
	// DecoratorTestDemo();

	// 组合模式测试函数
	// ComponentModeTestDemo();

	// 桥接模式测试函数
	// BridgingModeTestDemo();
}

// 行为型设计模式
void BehavioralTypeDesignModeTestDemo()
{
	// 模板方法模式测试函数
	// TemplateMethodTestDemo();

	// 策略模式测试函数
	// StrategyTestDemo();

	// 观察者模式测试函数
	// ObserverTestDemo();

	// 命令模式测试函数
	// CommandTestDemo();

	// 责任链模式测试函数
	// RespChainTestDemo();

	// 快照模式测试函数
	// MementoTestDemo();

	// 中介者模式测试函数
	// MediatorTestDemo();

	// 状态模式测试函数
	//StateTestDemo();

	// 解释器模式测试函数
	// InterpreterTestDemo();

	// 访问者模式测试函数
	VistorTestDemo();
}
