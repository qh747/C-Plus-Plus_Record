#include "DMTPrinciple.h"

bool Leader::hasEmployee(const string& name)
{
	if (name == this->getName())
		return true;
	else
		return (m_employeeMap.end() != m_employeeMap.find(name)) ? true : false;
}

double Leader::getEmployeeSalary(const string& name)
{
	if (name == this->getName())
		return this->getSalary();
	else
	{
		map<string, Employee*>::iterator iter = m_employeeMap.find(name);
		if (m_employeeMap.end() != m_employeeMap.find(name))
			return iter->second->getSalary();
		else
			return -1;
	}
}

void Leader::setEmployeeSalary(const string& name, double sal)
{
	if (name == this->getName())
		return this->setSalary(this->getSalary() + sal);
	else
	{
		map<string, Employee*>::iterator iter = m_employeeMap.find(name);
		if (m_employeeMap.end() != m_employeeMap.find(name))
			iter->second->setSalary(iter->second->getSalary() + sal);
	}
}

bool Boss::hasEmployee(const string& name)
{
	for (map<string, Leader*>::iterator iter = m_leaderMap.begin(); iter != m_leaderMap.end(); iter++)
	{
		if (iter->second->hasEmployee(name))
		{
			cout << "Found Employee: " << name << endl;
			return true;
		}
	}
	cout << "Not Found" << endl;
	return false;
}

void Boss::setEmployeeSalary(const string& name, double sal)
{	
	for (map<string, Leader*>::iterator iter = m_leaderMap.begin(); iter != m_leaderMap.end(); iter++)
	{
		if (iter->second->hasEmployee(name))
		{
			iter->second->setEmployeeSalary(name, sal);
			cout << "Employee: " << name << " Salary: " << iter->second->getEmployeeSalary(name) << endl;
			return;
		}
	}
	cout << "Set " << name << " Salary Failed" << endl;
}

void DMTPrincipleTestDemo()
{
	Boss b("Boss A_1");
	Leader lFst("Leader B_2", 10000);
	Leader lSec("Leader C_3", 10000);
	Employee eFst("Employee D_4", 1000);
	Employee eSec("Employee E_5", 1000);
	Employee eTrd("Employee F_6", 1000);

	b.addLeader(&lFst);
	b.addLeader(&lSec);
	lFst.addEmployee(&eFst);
	lFst.addEmployee(&eSec);
	lSec.addEmployee(&eTrd);

	if (b.hasEmployee("Leader B_2"))
		b.setEmployeeSalary("Leader B_2", 1000);
	
	if (b.hasEmployee("Employee E_5"))
		b.setEmployeeSalary("Employee E_5", 500);

	if (b.hasEmployee("Employee G_10"))
		b.setEmployeeSalary("Employee G_10", 500);
}