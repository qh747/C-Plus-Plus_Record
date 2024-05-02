#pragma once
#include <iostream>
#include <string>
#include <map>
using std::cout;
using std::endl;
using std::string;
using std::map;

// 迪米特法则
class AbstractPerson
{
public:
	AbstractPerson(const string& name) : m_name(name) {}
	virtual ~AbstractPerson() {}

public:
	const string& getName() { return m_name; }

private:
	string m_name;
};

class Employee : public AbstractPerson
{
public:
	Employee(const string& name, double sal) : AbstractPerson(name), m_salary(sal) {}
	virtual ~Employee() {}

public:
	void	setSalary(double sal) { m_salary = sal; }
	double	getSalary() { return m_salary; }

private:
	double m_salary;
};

class Leader : public AbstractPerson
{
public:
	Leader(const string& name, double sal) : AbstractPerson(name), m_salary(sal) {}
	virtual ~Leader() {}
	void addEmployee(Employee* pEmp) { m_employeeMap.insert(std::make_pair(pEmp->getName(), pEmp)); }

public:
	void setSalary(double sal) { m_salary = sal; }
	double getSalary() { return m_salary; }

public:
	bool hasEmployee(const string& name);
	double getEmployeeSalary(const string& name);
	void setEmployeeSalary(const string& name, double sal);

private:
	double m_salary;
	map<string, Employee*> m_employeeMap;
};

class Boss : public AbstractPerson
{
public:
	Boss(const string& name) : AbstractPerson(name) {}
	virtual ~Boss() {}
	void addLeader(Leader* pLea) { m_leaderMap.insert(std::make_pair(pLea->getName(), pLea)); }

public:
	// Boss类通过Leader类间接获取和修改Employee类参数
	bool hasEmployee(const string& name);
	void setEmployeeSalary(const string& name, double sal);

private:
	map<string, Leader*> m_leaderMap;
};

// 迪米特法则测试函数
void DMTPrincipleTestDemo();