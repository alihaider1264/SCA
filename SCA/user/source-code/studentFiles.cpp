#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
struct studentType
{
	string fName, lName;
	int testScore;
	char grade;
};
void getInfo(ifstream& inFile, studentType sList[], int listSize)
{
	int n = 0;
	while (n < listSize)
	{
		inFile >> sList[n].lName >> sList[n].fName >> sList[n].testScore;
		n++;
	}
}
void grade(studentType sList[], int listSize)
{
	int i;
	for (i = 0; i < listSize; i++)
		if (sList[i].testScore < 60)
			sList[i].grade = 'F';
		else if (sList[i].testScore < 70)
			sList[i].grade = 'D';
		else if (sList[i].testScore < 80)
			sList[i].grade = 'C';
		else if (sList[i].testScore < 90)
			sList[i].grade = 'B';
		else
			sList[i].grade = 'A';
}
int highestScore(const studentType sList[], int listSize)
{
	int high = 0, i;
	for (i = 0; i < listSize; i++)
		if (high < sList[i].testScore)
			high = sList[i].testScore;
	return high;
}
void print(const studentType sList[], int listSize)
{
		cout << left << setw(30) << "Student Name" << right << setw(10) << "TestScore" << right << setw(7) << "Grade" << endl;
		string name;
		int high, i;
		for (i = 0; i < listSize; i++)
		{
			name = sList[i].lName + ", " + sList[i].fName;
			cout << left << setw(30) << name << right << setw(10) << sList[i].testScore << right << setw(7) << sList[i].grade << endl;
		}
		cout << endl;
		high = highestScore(sList, listSize);
		cout << "Highest Test Score: " << high << endl;
		cout << "Students having the highest test score: " << endl;
		for (int i = 0; i < listSize; i++)
			if (sList[i].testScore == high)
				cout << sList[i].lName << ", " << sList[i].lName << endl;
}
int main()
{
	ifstream in;
	in.open("students.txt");
	if (in.fail()){
		cout << "File failed to open." << endl;
		return 0;}
	studentType sList[20];
	getInfo(in, sList, 20);
	grade(sList, 20);
	print(sList, 20);
	in.close();
	return 0;
}
