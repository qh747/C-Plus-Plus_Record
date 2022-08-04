#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

/*作业抽象类    **/
class AbstractHomework
{
public:
	virtual ~AbstractHomework() { }

public:
	virtual void setTitle(const string& title) = 0;
	virtual string getTitle() = 0;

	virtual void setQuestion(const string& question) = 0;
	virtual string getQuestion() = 0;

	virtual void setStudentName(const string& stuName) = 0;
	virtual string getStudentName() = 0;

public:
	virtual AbstractHomework* clone() = 0;
};

/*语文作业    **/
class ChineseHomework : public AbstractHomework
{
public:
	ChineseHomework() { }
	virtual ~ChineseHomework() { }

public:
	virtual void setTitle(const string& title) { m_homeworkTitle = title; }
	virtual string getTitle() { return m_homeworkTitle; }

	virtual void setQuestion(const string& question) { m_homeworkQuestion = question; }
	virtual string getQuestion() { return m_homeworkQuestion; }

	virtual void setStudentName(const string& stuName) { m_studentName = stuName; }
	virtual string getStudentName() { return m_studentName; }

public:
	virtual AbstractHomework* clone()	/*克隆现有的作业模板    **/
	{
		ChineseHomework* homeworkPtr = new ChineseHomework();
		homeworkPtr->setTitle(this->m_homeworkTitle);
		homeworkPtr->setQuestion(this->m_homeworkQuestion);
		homeworkPtr->setStudentName(this->m_studentName);

		return homeworkPtr;
	}

private:
	string m_homeworkTitle;
	string m_homeworkQuestion;
	string m_studentName;
};

/*数学作业    **/
class MathHomework : public AbstractHomework
{
public:
	MathHomework() { }
	virtual ~MathHomework() { }

public:
	virtual void setTitle(const string& title) { m_homeworkTitle = title; }
	virtual string getTitle() { return m_homeworkTitle; }

	virtual void setQuestion(const string& question) { m_homeworkQuestion = question; }
	virtual string getQuestion() { return m_homeworkQuestion; }

	virtual void setStudentName(const string& stuName) { m_studentName = stuName; }
	virtual string getStudentName() { return m_studentName; }

public:
	virtual AbstractHomework* clone()	/*克隆现有的作业模板    **/
	{
		MathHomework* homeworkPtr = new MathHomework();
		homeworkPtr->setTitle(this->m_homeworkTitle);
		homeworkPtr->setQuestion(this->m_homeworkQuestion);
		homeworkPtr->setStudentName(this->m_studentName);

		return homeworkPtr;
	}

private:
	string m_homeworkTitle;
	string m_homeworkQuestion;
	string m_studentName;
};

void showHomework(AbstractHomework* homeworkPtr)
{
	cout << "Homework Title: " << homeworkPtr->getTitle() << endl;
	cout << "Homework Question: " << homeworkPtr->getQuestion() << endl;
	cout << "Student Name: " << homeworkPtr->getStudentName() << endl;
}

/*作业派发函数    **/
void distributeHomework(AbstractHomework* homeworkPtr, const vector<string>& studentArray)
{
	for (int i = 0; i < studentArray.size(); ++i)
	{
		AbstractHomework* thisStudentHomeWorkPtr = homeworkPtr->clone();
		string thisStudentName = studentArray.at(i);
		thisStudentHomeWorkPtr->setStudentName(thisStudentName);

		showHomework(thisStudentHomeWorkPtr);
		cout << "Distrubute Success." << endl << endl;

		delete thisStudentHomeWorkPtr;
		thisStudentHomeWorkPtr = NULL;
	}
}

int main()
{
	/*创建班级    **/
	vector<string> studentArray;
	studentArray.push_back(string("Peter"));
	studentArray.push_back(string("John"));
	studentArray.push_back(string("Lisa"));

	/*创建语文作业模板    **/
	AbstractHomework* chineseHomeworkPtr = new ChineseHomework();
	chineseHomeworkPtr->setTitle(string("Chinese"));
	chineseHomeworkPtr->setQuestion(string("Introduce Yourself In 300 Words ."));
	chineseHomeworkPtr->setStudentName(string("xxx"));

	/*派发语文作业    **/
	distributeHomework(chineseHomeworkPtr, studentArray);

	/*创建数学作业模板    **/
	AbstractHomework* mathHomeworkPtr = new MathHomework();
	mathHomeworkPtr->setTitle(string("Math"));
	mathHomeworkPtr->setQuestion(string("Calculate One Plus One Equals To ?"));
	mathHomeworkPtr->setStudentName(string("xxx"));

	/*派发数学作业    **/
	distributeHomework(mathHomeworkPtr, studentArray);

	delete chineseHomeworkPtr;
	chineseHomeworkPtr = NULL;

	delete mathHomeworkPtr;
	mathHomeworkPtr = NULL;

	system("pause");
	return 0;
}