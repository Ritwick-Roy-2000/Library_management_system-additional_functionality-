#include <bits/stdc++.h>
#include <iostream>
#include <conio.h>
#include <iomanip> //input-output manipulator
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctime>
#include <fstream>
using namespace std;
void gotoxy(int x, int y)
{
	cout << setw(x); //horizontal

	for (; y > 0; y--) //vertical
		cout << endl;
}
class book
{
	char bno[6];	//bookno.
	char bname[50]; //bookname
	char aname[20]; //authorname
	string date;

public:
	void createbook()
	{
		cout << "\nNEW BOOK ENTRY...\n";
		cout << "\nENTER BOOK NO.";
		cin >> bno;
		cout << "\nENTER BOOK NAME";
		gets(bname);
		gets(bname); //enables enter with space
		cout << "\nENTER AUTHOR NAME";
		gets(aname);
		cout << "\n\n\nBook Created..";
	}
	void showbook()
	{
		cout << "\nBook Number: " << bno;
		cout << "\n\nBook Name: ";
		puts(bname);
		cout << "\nBook Author Name: ";
		puts(aname);
	}
	void modifybook()
	{
		cout << "\nBook Number: " << bno;
		cout << "\nModify Book Name :";
		gets(bname);
		gets(bname);
		cout << "\nModify Author's Name :";
		gets(aname);
	}

	char *retbno() //string return
	{
		return bno;
	}
	void report()
	{
		cout << bno << setw(30) << bname << setw(30) << aname << endl;
	}
}; //class ends here

class student
{
	char admno[6]; //admission no.
	char name[20];
	char stbno[6]; // student book no
	set<string> bookIssued;
	map<string, string> dateIssued;

	int token; //total book of student
public:
	void createstudent()
	{
		system("cls");
		cout << "\nNEW STUDENT ENTRY...\n";
		cout << "\nEnter The Admission No. ";
		cin >> admno;
		cout << "Enter The Student Name ";
		gets(name);
		gets(name);
		token = 0;
		stbno[0] = '\0';
		cout << "\n\nStudent Record Created...";
	}
	void showstudent()
	{
		cout << "\nAdmission Number : " << admno;
		cout << "\nStudent Name : ";
		puts(name);
		cout << "\nNo of Book Issued : " << bookIssued.size();
		if (token == 1)
		{
			cout << "\nBooks Issued:" << endl;
			for (auto i : dateIssued)
				cout << "Book Number:" << i.first << " \tDate Issued:" << i.second;
		}
	}
	void modifystudent()
	{
		cout << "\nAdmission No. " << admno;
		cout << "\nModify Student Name : ";
		gets(name);
		gets(name);
	}
	char *retadmno()
	{
		return admno;
	}
	char *retstbno()
	{
		return stbno;
	}
	int rettoken()
	{
		return token;
	}
	void addtoken()
	{
		token = 1;
	}
	void resettoken()
	{
		token = 0;
	}
	void getstbno(char t[])
	{
		strcpy(stbno, t);
	}
	int totalBookIssued()
	{
		return bookIssued.size();
	}
	void setbno(string s)
	{
		bookIssued.insert(s);
		time_t now = time(0);

		char *dt = ctime(&now);
		dateIssued[s] = dt;
	}
	string resetbno(string s)
	{
		auto i = bookIssued.find(s);
		bookIssued.erase(i);
		string date;
		for (auto j : dateIssued)
		{
			if (j.first == s)
			{
				date = j.second;
				break;
			}
		}
		dateIssued.erase(s);
		return date;
	}
	bool checkAlreadyIssued(string bn)
	{
		if (bookIssued.find(bn) == bookIssued.end())
		{
			return false;
		}
		return true;
	}
	void report()
	{
		cout << "\t" << admno << setw(20) << name << setw(10) << bookIssued.size() << endl;
	}
};				 //class ends here
fstream fp, fp1; //object
book bk;		 //book class object
student st;		 //student class object

int calculatemonthday(int im, int dm, int id, int dd)
{
	int days = 0;
	int dayinMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	for (int i = im; i <= dm; i++)
	{
		if (i == im)
		{
			days += (dayinMonth[i-1] - id);
		}
		else if (i == dm)
		{
			days += dd;
		}
		else
		{
			days += dayinMonth[i-1];
		}
	}
	return days;
}
int leapyeardays(int iy, int dy, int im, int dm)
{
	int leapyears = 0;
	iy = im <= 2 ? iy : iy + 1;
	dy = dm > 2 ? dy : dy - 1;
	for (int i = iy; i <= dy; i++)
	{
		if (i % 100 == 0)
		{
			if (i % 400 == 0)
			{
				leapyears++;
			}
		}
		else if (i % 4 == 0)
		{
			leapyears++;
		}
	}
	return leapyears;
}
int calculateday(int dy, int dm, int dd, int iy, string im, int id) //calculating number of days the student kept the boook
{
	int diffYear = dy - iy;
	int issuemon;
	if (im == "Jan")
		issuemon = 1;
	else if (im == "Fab")
		issuemon = 2;
	else if (im == "Mar")
		issuemon = 3;
	else if (im == "Apr")
		issuemon = 4;
	else if (im == "May")
		issuemon = 5;
	else if (im == "Jun")
		issuemon = 6;
	else if (im == "Jul")
		issuemon = 7;
	else if (im == "Aug")
		issuemon = 8;
	else if (im == "Sep")
		issuemon = 9;
	else if (im == "Oct")
		issuemon = 10;
	else if (im == "Nov")
		issuemon = 11;
	else
		issuemon = 12;
	int diffday;
	if (diffYear == 0)
	{
		if (issuemon == dm)
		{
			diffday = dd - id;
		}
		else
		{
			diffday = calculatemonthday(issuemon, dm, id, dd);
		}
	}
	else
	{
		diffday = calculatemonthday(issuemon, 12, id, 31) + calculatemonthday(1, dm, 1, dd)+1;
		diffday += (diffYear - 1) * 365;
	}
	diffday += leapyeardays(iy, dy, issuemon, dm);
	return diffday;
}
void writebook()
{
	char ch;
	fp.open("book.dat", ios::out | ios::app); //write and append data
	do
	{
		system("cls");
		bk.createbook();
		fp.write((char *)&bk, sizeof(book)); //size of class
		cout << "\n\nDo you want to add more record...(y/n?) ";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	fp.close();
}

void writestudent()
{
	char ch;
	fp.open("student.dat", ios::out | ios::app); //write and append data
	do
	{
		system("cls");
		st.createstudent();
		fp.write((char *)&st, sizeof(student)); //size of class
		cout << "\n\nDo you want to add more record...(y/n?) ";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	fp.close();
}
void displayspb(char n[])
{
	int flag = 0;				  //book not found
	fp.open("book.dat", ios::in); //read data
	while (fp.read((char *)&bk, sizeof(book)))
	{
		if (strcmpi(bk.retbno(), n) == 0) //not case sensitive
		{
			cout << "\nBOOK DETAILS\n";
			bk.showbook();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0) //book not found
	{
		cout << "\n\nBook does not exist";
	}
	getch();
}
void displaysps(char n[])
{
	int flag = 0;					 //student not found
	fp.open("student.dat", ios::in); //read data
	while (fp.read((char *)&st, sizeof(student)))
	{
		if (strcmpi(st.retadmno(), n) == 0) //not case sensitive
		{
			cout << "\nSTUDENT DETAILS\n";
			st.showstudent();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0) //student not found
	{
		cout << "\n\nStudent does not exist";
	}
	getch();
}
void modifybook()
{
	char n[6];
	int found = 0; //seach book of given data
	system("cls");
	cout << "\n\nMODIFY BOOK RECORD...";
	cout << "\n\nEnter the book no. ";
	cin >> n;
	fp.open("book.dat", ios::in | ios::out);
	while (fp.read((char *)&bk, sizeof(book)) && found == 0)
	{
		if (strcmpi(bk.retbno(), n) == 0)
		{
			bk.showbook();
			cout << "\nEnter the new details book";
			bk.modifybook();
			int pos = -1 * sizeof(bk);
			fp.seekp(pos, ios::cur); //back from current position
			fp.write((char *)&bk, sizeof(book));
			cout << "\n\nRecord Updated";
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
	{
		cout << "\n\nRecord Not Found";
	}
	getch(); //press key to get out
}
void modifystudent()
{
	char n[6];
	int found = 0; //seach book of given data
	system("cls");
	cout << "\n\nMODIFY STUDENT RECORD...";
	cout << "\n\nEnter the Admission no. ";
	cin >> n;
	fp.open("student.dat", ios::in | ios::out);
	while (fp.read((char *)&st, sizeof(student)) && found == 0)
	{
		if (strcmpi(st.retadmno(), n) == 0)
		{
			st.showstudent();
			cout << "\nEnter the new details of student";
			st.modifystudent();
			int pos = -1 * sizeof(st);
			fp.seekp(pos, ios::cur); //back from current position
			fp.write((char *)&st, sizeof(student));
			cout << "\n\nRecord Updated";
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
	{
		cout << "\n\nRecord Not Found";
	}
	getch(); //press key to get out
}

void deletestudent()
{
	char n[6];
	int flag = 0;
	system("cls");
	cout << "\n\n\n\tDELETE STUDENT...";
	cout << "\n\nEnter the Admission no> : ";
	cin >> n;
	fp.open("student.dat", ios::in | ios::out);
	fstream fp2;
	fp2.open("temp.dat", ios::out);
	fp.seekg(0, ios::beg);
	while (fp.read((char *)&st, sizeof(student)))
	{
		if (strcmpi(st.retadmno(), n) != 0)
		{
			fp2.write((char *)&st, sizeof(student));
		}
		else
		{
			flag = 1; //student found
		}
	}
	fp2.close();
	fp.close();
	remove("student.dat");
	rename("temp.dat", "student.dat"); //data after deletion moved to temp
	if (flag == 1)
	{
		cout << "\n\n\tRecord Deleted..";
	}
	else
	{
		cout << "\n\nRecord not Found";
	}
	getch();
}
void deletebook()
{
	char n[6]; //book no.
	int flag = 0;
	system("cls");
	cout << "\n\n\n\tDELETE BOOK...";
	cout << "\n\nEnter the Book no> : ";
	cin >> n;
	fp.open("book.dat", ios::in | ios::out);
	fstream fp2;					//New onject
	fp2.open("Temp.dat", ios::out); //temp having data else than that to be deleted
	fp.seekg(0, ios::beg);
	while (fp.read((char *)&bk, sizeof(book)))
	{
		if (strcmpi(bk.retbno(), n) != 0)
		{
			fp2.write((char *)&st, sizeof(book));
		}
		else
		{
			flag = 1; //student found
		}
	}
	fp2.close();
	fp.close();
	remove("book.dat");
	rename("Temp.dat", "book.dat"); //data after deletion moved to temp
	if (flag == 1)
	{
		cout << "\n\n\tRecord Deleted... ";
	}
	else
	{
		cout << "\n\nRecord not Found";
	}
	getch();
}
void displayalls()
{
	system("cls");
	fp.open("student.dat", ios::in); //read mode
	if (!fp)
	{
		cout << "File Could Not Be Open";
		getch();
		return; //press any key and return
	}
	cout << "\n\n\t\tStudent List\n\n";
	cout << "==================================================================\n";
	cout << "\tAdmission No." << setw(10) << "Name" << setw(20) << "Book Issued\n";
	cout << "==================================================================\n";
	while (fp.read((char *)&st, sizeof(student)))
	{
		st.report();
	}
	fp.close();
	getch();
}
void displayallb()
{
	system("cls");
	fp.open("book.dat", ios::in); //read mode
	if (!fp)
	{
		cout << "File Could Not Be Open";
		getch();
		return; //press any key and return
	}
	cout << "\n\n\t\tBook List\n\n";
	cout << "==================================================================\n";
	cout << "\tBook No." << setw(20) << "Book Name" << setw(25) << "Book Author\n";
	cout << "==================================================================\n";
	while (fp.read((char *)&bk, sizeof(book)))
	{
		bk.report();
	}
	fp.close();
	getch();
}
void bookissue()
{
	char sn[6], bn[6];
	int found = 0, flag = 0;
	system("cls");
	cout << "\n\nBOOK ISSUE...";
	cout << "\n\n\tEnter Admission no.";
	cin >> sn;
	fp.open("student.dat", ios::in | ios::out);
	fp1.open("book.dat", ios::in | ios::out);
	while (fp.read((char *)&st, sizeof(student)) && found == 0)
	{
		if (strcmpi(st.retadmno(), sn) == 0) //compare admsn no.
		{
			found = 1;
			if (st.totalBookIssued() < 4) //if book not issued
			{
				cout << "\n\n\tEnter The Book No.";
				cin >> bn;
				while (fp1.read((char *)&bk, sizeof(book)) && flag == 0)
				{
					if (strcmpi(bk.retbno(), bn) == 0) //compare book no.
					{
						flag = 1;
						if (st.checkAlreadyIssued(bn))
						{
							cout << "Book already issued" << endl;
						}
						else
						{
							st.setbno(bn);
							st.addtoken();
							st.getstbno(bk.retbno()); //pass book no.
							int pos = -1 * sizeof(st);
							fp.seekg(pos, ios::cur);
							fp.write((char *)&st, sizeof(student));
							cout << "\n\n\tBook Issued Successfully\n\n Please Note The Book Issue Date On Backside Of Your Book And Return Book Within 10 Days,After that fine will be imposed,for 7 days delay fine will be 5 rupees,After 7 days each day fine will be 2 rupees.";
						}
					}
				}
				if (flag == 0)
				{
					cout << "Book No. Does Not Exists";
				}
			}
			else
			{
				cout << "You already have issued 4 Book";
			}
		}
	}
	if (found == 0)
	{
		cout << "Student Record Not Exists...";
	}
	getch();
	fp.close();
	fp1.close();
}

void bookdeposit()
{
	char sn[6], bn[6];
	int found = 0, flag = 0, day, fine;
	string date;
	system("cls");
	cout << "\n\nBOOK DEPOSIT...";
	cout << "\n\n\tEnter Admission no. Of Student";
	cin >> sn;
	fp.open("student.dat", ios::in | ios::out);
	fp1.open("book.dat", ios::in | ios::out);
	while (fp.read((char *)&st, sizeof(student)) && found == 0)
	{
		if (strcmpi(st.retadmno(), sn) == 0) //compare admsn no.
		{
			found = 1;
			if (st.totalBookIssued() > 0) //if book issued
			{
				cout << "\n\n\tEnter The Book No.";
				cin >> bn;
				while (fp1.read((char *)&bk, sizeof(book)) && flag == 0)
				{
					if (strcmpi(bk.retbno(), bn) == 0)
					{
						flag = 1;
						if (!st.checkAlreadyIssued(bn))
						{
							cout << "Book not issued" << endl;
						}
						else
						{
							date = st.resetbno(bn);
							int issueYear = stoi(date.substr(date.length() - 6));
							string issueMon = date.substr(4, 3);
							int issueDay;
							if (date[8] == ' ')
							{
								issueDay = date[9] - '0';
							}
							else
							{
								issueDay = (date[8] - '0') * 10 + date[9] - '0';
							}
							time_t now = time(0);
							char *dt = ctime(&now);
							tm *ltm = localtime(&now);
							int yeardeposit, monthdeposit, daydeposit;
							yeardeposit = 1900 + ltm->tm_year;
							monthdeposit = ltm->tm_mon;
							daydeposit = ltm->tm_mday;
							day = calculateday(yeardeposit, monthdeposit, daydeposit, issueYear, issueMon, issueDay);
							if (day > 10)
							{
								fine = 5;
								if (day > 17)
									fine += (day - 17) * 2;
								cout << "\n\n Fine = " << fine;
							}
							if (st.totalBookIssued() == 0)
								st.resettoken();

							int pos = -1 * sizeof(st);
							fp.seekg(pos, ios::cur);
							fp.write((char *)&st, sizeof(student));
							cout << "\n\n\tBook Deposited Successfully";
						}
					}
				}
				if (flag == 0)
				{
					cout << "Book No. Does Not Exists";
				}
			}

			else
			{

				cout << "No Book Issued";
			}
		}
	}
	if (found == 0)
	{
		cout << "Student Record Not Exists...";
	}
	getch();
	fp.close();
	fp1.close();
}

void start()
{
	system("cls");
	gotoxy(35, 11);
	cout << "LIBRARY";
	gotoxy(35, 14);
	cout << "MANAGEMENT";
	gotoxy(35, 17);
	cout << "SYSTEM";
	cout << " \n  by: Chahat";
	getch();
}
void adminmenu()
{
	system("cls");
	int ch2;
	cout << "\n\n\n\tADMINISTRATOR MENU";
	cout << "\n\n\n\t1.CREATE STUDENT RECORD";
	cout << "\n\n\n\t2.DISPLAY ALL STUDENT RECORD";
	cout << "\n\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD";
	cout << "\n\n\n\t4.MODIFY STUDENT RECORD";
	cout << "\n\n\n\t5.DELETE STUDENT RECORD";
	cout << "\n\n\n\t6.CREATE BOOK";
	cout << "\n\n\n\t7.DISPLAY ALL BOOKS";
	cout << "\n\n\n\t8.DISPLAY SPECIFIC BOOK";
	cout << "\n\n\n\t9.MODIFY BOOK RECORD";
	cout << "\n\n\n\t10.DELETE BOOK RECORD";
	cout << "\n\n\n\t11.BACK TO MAIN MENU";
	cout << "\n\n\n\tPLEASE ENTER YOUR CHOICE(1-11)";
	cin >> ch2;
	switch (ch2)
	{
	case 1:
		writestudent();
		break;
	case 2:
		displayalls();
		break;
	case 3:
		char num[6];
		system("cls");
		cout << "\n\n\t Please enter admission no.";
		cin >> num;
		displaysps(num);
		break;
	case 4:
		modifystudent();
		break;
	case 5:
		deletestudent();
		break;
	case 6:
		writebook();
		break;
	case 7:
		displayallb();
		break;
	case 8:
	{
		char num[6];
		system("cls");
		cout << "\n\n\tPlease enter book no.";
		cin >> num;
		displayspb(num);
		break;
	}
	case 9:
		modifybook();
		break;
	case 10:
		deletebook();
		break;
	case 11:
		return;
	default:
		cout << "Invalid choice";
	}
	adminmenu();
}
int main()

{
	char ch;
	system("cls");
	start();
	do
	{
		system("cls");
		cout << "\n\n\n\t MAIN MENU";
		cout << "\n\n\n\t1 BOOK ISSUE";
		cout << "\n\n\n\t2 BOOK DEPOSIT";
		cout << "\n\n\n\t3 ADMINISTRATOR MENU";
		cout << "\n\n\n\t4 EXIT";
		cout << "\n\n\n\t PLEASE SELECT YOUR OPTION(1-4)";
		cin>>ch;
		switch (ch)
		{
		case '1':
			bookissue();
			break;
		case '2':
			bookdeposit();
			break;
		case '3':
			adminmenu();
			break;
		case '4':
			exit(0);
			break;
		default:
			cout << "INVALID CHOICE";
		}
	} while (ch != 4);
}