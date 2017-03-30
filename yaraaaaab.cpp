// yaraaaaab.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

void viewtable();
void insert();
int check(int);
void edit();
void deleteflights();
void Edit_Reservation();
void delete1();
void exit();

struct flights {
	double flightno;
	char flightid[20];
	char flightday[20];
	char from[20];
	char to[20];
	char departure[20];
	char arrival[20];
	char duration[20];
	char frequency[20];
};
struct Passenger {
	char fname[20], lname[20], mname[20], profession[30], nationality[30], gender[20], passnumber[20];
	int day, Day, month, Month, Year, year, id;
	double flightno;
	char flightid[20];
	char flightday[20];
	char from[20];
	char to[20];
	char departure[20];
	char arrival[20];
	char duration[20];
	char frequency[20];
	char Row;
	char Column;
};

void insert() {
	flights z;
	int checker;
	int tableid = 0;
	ofstream fout("table.bin", ios::app);
	do {
		tableid++;
		checker = check(tableid);
	} while (checker == 0);
	cout << "Table ID : " << tableid << endl;
	cout << "FlightNo FlightID Day From To Departure Arrival Duration Frequency\n";
	z.flightno = tableid;
	cin >> z.flightid;
	cin >> z.flightday;
	cin >> z.from;
	cin >> z.to;
	cin >> z.departure;
	cin >> z.arrival;
	cin >> z.duration;
	cin >> z.frequency;
	fout.write((char *)&z, sizeof(z));
	fout.close();
	system("pause");
}
void viewtable() {
	flights y;
	int value = 1;
	int checker = 1;
	cout << "flightno \t flightid \t from \t to \t departure \t arrival \t duration \t frequency \n";
	ifstream fin("table.bin", ios::in | ios::binary);

	do {
		fin.read((char *)&y, sizeof(y));
		if (fin.eof()) break;
		cout << y.flightno << "    \t" << y.flightid << "     \t" << y.flightday << "      \t" << y.from << "    \t" << y.to << "    \t" << y.departure << "    \t" << y.arrival << "    \t" << y.duration << "     \t" << y.frequency << endl;
	} while (!fin.eof());
	fin.close();


}

int check(int searchid) {
	int checker = 1;
	flights a;
	ifstream fin("table.bin", ios::in);
	while (!fin.eof()) {
		fin.read((char *)&a, sizeof(a));
		if (a.flightno == searchid) {
			checker = 0;
			break;
		}
	}
	fin.close();
	return checker;
}

void edit() {
	flights y;
	string id;
	string day;
	long pos;
	cout << "Enter Flight ID : ";
	cin >> id;
	cout << "Enter Flight day : ";
	cin >> day;
	fstream file("table.bin", ios::in | ios::out | ios::binary);
	do {
		pos = file.tellg();
		file.read((char *)&y, sizeof(y));
		if (file.eof()) break;
		if (y.flightid == id && y.flightday == day) {
			cout << "flight number: " << y.flightno << "\n" << "flight ID: " << y.flightid << "\n" << "Flight day: " << y.flightday << "\n" << "From: " << y.from << "\n" << "to: " << y.to << "\n" << "departure" << y.departure << "\n" << "Arrival" << y.arrival << "\n" << "duration" << y.duration << "\n" << "Frequency: " << y.frequency << endl;
			cout << "FlightNo FlightID Day From To Departure Arrival Duration Frequency\n";
			cin >> y.flightid;
			cin >> y.flightday;
			cin >> y.from;
			cin >> y.to;
			cin >> y.departure;
			cin >> y.arrival;
			cin >> y.duration;
			cin >> y.frequency;
			file.write((char *)&y, sizeof(y));
			file.close();
		}
	} while (!file.eof());
}

void deleteflights() {
	char ch;
	flights y;
	string id;
	string day;
	int checker = 0;
	cout << "Enter Flight ID : ";
	cin >> id;
	cout << "Enter Flight day : ";
	cin >> day;
	ifstream fin("table.bin", ios::in);
	ofstream fout("temp.bin", ios::out);
	do {
		fin.read((char*)&y, sizeof(y));
		if (fin.eof()) break;
		if (y.flightid == id && y.flightday == day) {
			cout << "flight number: " << y.flightno << "\n" << "flight ID: " << y.flightid << "\n" << "Flight day: " << y.flightday << "\n" << "From: " << y.from << "\n" << "to: " << y.to << "\n" << "departure" << y.departure << "\n" << "Arrival" << y.arrival << "\n" << "duration" << y.duration << "\n" << "Frequency: " << y.frequency << endl;
			cout << "Are you sure you want to delete ? (y/n)\n";
			cin >> ch;
			if (ch == 'n')
				fout.write((char*)&y, sizeof(y));
			checker = 1;
		}
		else
			fout.write((char*)&y, sizeof(y));
	} while (!fin.eof());
	fin.close();
	fout.close();
	if (checker == 0)
		cout << "Flight not found !\n";
	else
	{
		remove("table.bin");
		rename("temp.bin", "table.bin");
	}
}

void Choosefromtable(Passenger&stdrec) {
	flights bo[65];
	int choice;

	ifstream inbin;
	inbin.open("table.bin", ios::binary);

	for (int x = 0;x<65;x++) {
		inbin.read((char*)&bo[x], sizeof(bo[x]));
		cout << bo[x].flightno << "---->" << bo[x].flightid << "---->" << bo[x].from << "---->" << bo[x].to << "---->" << bo[x].departure << "----> " << bo[x].arrival << "---->" << bo[x].duration << "---->" << bo[x].frequency << endl;
	}

	cout << "Enter the number of flight you want to Reserve on " << endl;
	cin >> choice;

	stdrec.flightno = bo[choice - 1].flightno;
	stdrec.flightid[19] = bo[choice - 1].flightid[19];
	stdrec.from[19] = bo[choice - 1].from[19];
	stdrec.to[19] = bo[choice - 1].to[19];
	stdrec.departure[19] = bo[choice - 1].departure[19];
	stdrec.arrival[19] = bo[choice - 1].arrival[19];
	stdrec.duration[19] = bo[choice - 1].duration[19];
	stdrec.frequency[19] = bo[choice - 1].frequency[19];
}

void getdata(Passenger&bo) { 

	ofstream outbin;
	outbin.open("Passenger.bin", ios::binary);

	cout << "Enter your name (First name / Middle name / last name)" << endl;
	cin >> bo.fname >> bo.mname >> bo.lname;
	cout << "Please enter your Date of Birth(Day / Month / Year)" << endl;
	cin >> bo.day >> bo.month >> bo.year;
	cout << "Nationality" << endl;
	cin >> bo.nationality;
	cout << "Please enter Gender" << endl;
	cin >> bo.gender;
	cout << "Enter passport number :" << endl;
	cin >> bo.passnumber;







	for (int j = 0; j < 500; j++) {
		cout << " ";
	}
	cout << char(248) << char(248);
	for (int i = 0; i < 92; i++) {
		cout << char(205);
	}
	cout << char(187);
	cout << "\n" << "                " << char(248) << char(248) << "                                                                                                " << char(186);
	cout << "\n" << "              " << char(248) << char(248) << "     " << 'F' << " " << char(219) << " " << char(219) << " " << char(219) << " " << char(219) << " " << char(186) << " " << 'F' << " " << char(254) << " " << char(254) << " " << char(254) << " " << char(254) << " " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << " " << char(186);
	cout << "\n" << "            " << char(248) << char(248) << "                 " << char(186) << " " << 'E' << " " << char(254) << " " << char(254) << " " << char(254) << " " << char(254) << " " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << " " << char(186);
	cout << "\n" << "          " << char(248) << char(248) << "         " << 'D' << " " << char(219) << " " << char(219) << " " << char(219) << " " << char(219) << " " << char(186) << " " << 'D' << " " << char(254) << " " << char(254) << " " << char(254) << " " << char(254) << " " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << " " << char(186);
	cout << "\n" << "        " << char(248) << char(248) << char(248) << char(248) << char(248) << "          " << 1 << " " << 2 << " " << 3 << " " << 4 << " " << char(186) << "   " << 5 << " " << 6 << " " << 7 << " " << 8 << " " << 9 << " " << 10 << " " << 11 << " " << 12 << " " << 13 << " " << 14 << " " << 15 << " " << 16 << " " << 17 << " " << 18 << " " << 19 << " " << 20 << " " << 21 << " " << 22 << " " << 23 << " " << 24 << " " << 25 << " " << 26 << " " << 27 << " " << 28 << " " << 29 << " " << 30 << " " << 31 << " " << 32 << " " << char(186);
	cout << "\n" << "          " << char(248) << char(248) << "         " << 'C' << " " << char(219) << " " << char(219) << " " << char(219) << " " << char(219) << " " << char(186) << " " << 'C' << " " << char(254) << " " << char(254) << " " << char(254) << " " << char(254) << " " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << " " << char(186);
	cout << "\n" << "            " << char(248) << char(248) << "                 " << char(186) << " " << 'B' << " " << char(254) << " " << char(254) << " " << char(254) << " " << char(254) << " " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << " " << char(186);
	cout << "\n" << "              " << char(248) << char(248) << "     " << 'A' << " " << char(219) << " " << char(219) << " " << char(219) << " " << char(219) << " " << char(186) << " " << 'A' << " " << char(254) << " " << char(254) << " " << char(254) << " " << char(254) << " " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << " " << char(186);
	cout << "\n" << "                " << char(248) << char(248) << "                                                                                                " << char(186);
	cout << "\n" << "                   ";
	cout << char(248) << char(248);
	for (int i = 0; i < 92; i++) {
		cout << char(205);
	}
	cout << char(188);
	cout << endl;
	








	cout << "Enter Row Number :" << endl;
	cin >> bo.Row;
	cout << "Enter Column Number :" << endl;
	cin >> bo.Column;
	cout << "Enter Expiration Date Of Your Passport(Day / Month / Year):" << endl;
	cin >> bo.Day >> bo.Month >> bo.Year;

	srand(time(0));
	bo.id = rand() % 10000000;
	cout << "Your id is " << bo.id << endl;

	if (bo.Year<2016 && bo.Year>2023) {
		cout << "You Have Entered Wrong or Expired Date Please Try again later" << endl;
	
	}
	outbin.write((char*)&bo, sizeof(bo));

	system("cls");
	cout << "Mr./Mrs.        :" << bo.fname << " " << bo.mname << " " << bo.lname << endl;
	cout << "Gender          :" << bo.gender << endl;
	cout << "Date of birth   :" << bo.day << "/" << bo.month << "/" << bo.year << endl;
	cout << "nationality     :" << bo.nationality << endl;
	cout << "Passport number :" << bo.passnumber << endl;
	cout << "Expiration date :" << bo.Day << "/" << bo.Month << "/" << bo.Year << endl;
	cout << "Your seat is    : " << bo.Row<<bo.Column << endl;
	cout << "ID              :" << bo.id << endl;
	outbin.close();

}

void Edit_Reservation() {

	Passenger bo[800];
	bool y = false;
	int z;
	int id;

	ifstream inbin;
	inbin.open("Passenger.bin", ios::binary);

	cout << "Please enter your ID" << endl;
	cin >> id;

	for (int x = 0;x<800;x++) {
		inbin.read((char*)&bo[x], sizeof(bo[x]));
		if (id == bo[x].id) {
			y = true;
			z = x;
			break;
		}
		
	}
	int choice;
	if (y == true) {
		cout << "What you want to change" << endl;
		cout << "1.name" << endl;
		cout << "2.Date of birth" << endl;
		cout << "3.Gender" << endl;
		cout << "4.nationality" << endl;
		cout << "5.Passport number" << endl;
		cout << "6.Expiration Date" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			cin >> bo[z].fname >> bo[z].mname >> bo[z].lname;
			break;
		case 2:
			cin >> bo[z].day >> bo[z].month >> bo[z].year;
			break;

		case 3:
			cin >> bo[z].gender;
			break;
		case 4:
			cin >> bo[z].nationality;
			break;

		case 5:
			cin >> bo[z].passnumber;
			break;

		case 6:
			cin >> bo[z].Day >> bo[z].Month >> bo[z].Year;
			if (bo[z].Year<2016 && bo[z].Year>2023) {
				cout << "You Have Entered Wrong or Expired Date Please Try again later" << endl;
				return;
			}
			break;
		}
	}
	else {
		cout << "We Didn't Find your ID" << endl;
	}
	ofstream outbin;
	outbin.open("Passenger.bin", ios::binary);
	for (int x = 0;x<800;x++) {
		
		outbin.write((char*)&bo[x], sizeof(bo[x]));
	}

}

void delete1() {
	Passenger bo[800];
	bool z = false;
	int id;
	int a;
	cout << "Please enter your ID " << endl;
	cin >> id;
	ifstream inbin;
	inbin.open("Passenger.bin", ios::binary);
	for (int x = 0;x<800;x++) {
		inbin.read((char*)&bo[x], sizeof(bo[x]));
		if (id == bo[x].id) {
			z = true;
			a = x;
			break;
		}

	}
	if (z == true) {
		ofstream outbin;
		outbin.open("Temp.bin", ios::binary);
		for (int x = 0;x<10;x++) {
			if (x != a) {
				outbin.write((char*)&bo[x], sizeof(bo[x]));
			}
			else {
				continue;
			}


		}
		inbin.close();
		outbin.close();
		remove("Passenger.bin");
		rename("Temp.bin", "Passenger.bin");


	}
	else {
		cout << "WE didn't find the user" << endl;
	}





}

void exit()
{
	cout << " * Have a nice trip * " << endl;

	return;
}

int main()
{
	system("CLS");
	system("COLOR 70");
	int x;
	char y;
	Passenger bo;
	for (int i = 0; i<80; i++)
	{
		cout << char(221);
	}
	cout << char(221) << setw(79) << char(221);
	cout << char(221) << setw(79) << char(221);
	cout << char(221) << setw(79) << char(221);
	cout << char(221) << setw(79) << char(221);
	cout << char(221) << setw(79) << char(221);
	cout << char(221) << setw(40) << "1 - Insert            " << setw(39) << char(221);
	cout << char(221) << setw(79) << char(221);
	cout << char(221) << setw(40) << "2 - View table        " << setw(39) << char(221);
	cout << char(221) << setw(79) << char(221);
	cout << char(221) << setw(40) << "3 - Edit flight       " << setw(39) << char(221);
	cout << char(221) << setw(79) << char(221);
	cout << char(221) << setw(40) << "4 - Delete flight     " << setw(39) << char(221);
	cout << char(221) << setw(79) << char(221);
	cout << char(221) << setw(40) << "5 - Reserve           " << setw(39) << char(221);
	cout << char(221) << setw(79) << char(221);
	cout << char(221) << setw(40) << "6 - Edit reservation  " << setw(39) << char(221);
	cout << char(221) << setw(79) << char(221);
	cout << char(221) << setw(40) << "7 - Delete reservation" << setw(39) << char(221);
	cout << char(221) << setw(79) << char(221);
	cout << char(221) << setw(40) << "8 - Exit              " << setw(39) << char(221);
	cout << char(221) << setw(79) << char(221);
	cout << char(221) << setw(79) << char(221);
	for (int i = 0; i<80; i++)
	{
		cout << char(221);
	};
	//cout << "1 - Insert\n2 - View\n3 - Edit\n4 - Delete\n";
	cin >> x;
	switch (x) {
	case 1:
		system("CLS");
		insert();
		break;
	case 2:
		system("CLS");
		viewtable();
		break;
	case 3:
		system("CLS");
		edit();
		break;
	case 4:
		system("CLS");
		deleteflights();
		break;
	case 5:
		system("CLS");
		Choosefromtable(bo);
		getdata(bo);

		break;
	case 6:
		system("CLS");
		Edit_Reservation();
		break;

	case 7:
		system("CLS");
		delete1();
		break;

	case 8:
		system("CLS");
		exit();
		break;
	}
	


	return 0;
}
