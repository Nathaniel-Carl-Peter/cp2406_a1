#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string> // Required for std::string
// #include <iomanip>

#include <algorithm>
#include "my_debugger.h"
#include "Database.h"
// #include <bits/stdc++.h>


using namespace std;

namespace Records
{

	Employee &Database::addEmployee(const string &firstName, 
									const string &lastName)
	{
		log("start");
		Employee theEmployee(firstName, lastName);
		theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
		theEmployee.hire();
		mEmployees.push_back(theEmployee);

		log("end");
		return mEmployees[mEmployees.size() - 1];
	}

	Employee &Database::addEmployee(Employee empl)
	{

		mEmployees.push_back(empl);
		return mEmployees[mEmployees.size() - 1];
	}

	// Function overide to add a middleName field
	Employee &Database::addEmployee(
		const string &firstName,
		const string &middleName,
		const string &lastName)
	{
		log("start");

		Employee theEmployee(firstName, middleName, lastName);
		theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
		theEmployee.hire();
		mEmployees.push_back(theEmployee);

		log("end");
		return mEmployees[mEmployees.size() - 1];
	}

	Employee &Database::getEmployee(int employeeNumber)
	{
		for (auto &employee : mEmployees)
		{
			if (employee.getEmployeeNumber() == employeeNumber)
			{
				return employee;
			}
		}
		throw logic_error("No employee found.");
	}

	Employee &Database::getEmployee(const string &firstName, const string &lastName)
	{
		for (auto &employee : mEmployees)
		{
			if (employee.getFirstName() == firstName &&
				employee.getLastName() == lastName)
			{
				return employee;
			}
		}
		throw logic_error("No employee found.");
	}

	void Database::displayAll() const
	{
		for (const auto &employee : mEmployees)
		{
			employee.display();
		}
	}

	int displayseachMenu()
	{
		// Note:
		//		One important note is that this code assumes that the user will
		//		"play nice" and type a number when a number is requested.
		//		When you read about I/O in Chapter 13, you will learn how to
		//		protect against bad input.

		int selection;

		cout << endl;
		cout << "Search a Employee" << endl;
		cout << "Search by" << endl;
		cout << "-----------------" << endl;
		cout << "1) FirstName" << endl;
		cout << "1) MiddleName" << endl;
		cout << "1) LastName" << endl;
		cout << "1) Address" << endl;
		cout << "0) Quit" << endl;
		cout << endl;
		cout << "---> ";

		cin >> selection;
		return selection;
	}

	void Database::searchEmployee() const
	{
		bool done = false;
		while (!done) {
			int selection = displayseachMenu();
		switch (selection) 
		{
			case 0:
				log("case0");
				done = true;
				break;
			// case 1:
			// 	doHire(employeeDB);
			// 	break;
			// case 2:
			// 	doFire(employeeDB);
			// 	break;
		}
		
		return 0;
	}

	

	void Database::saveToFile(const string &fileName) const
	{
		// if(fileName.size() == 0)
		// {
		// 	cout << "Ignore saving empty file name" << endl;
		// }

		ofstream dbFile(fileName, ios_base::trunc);
		if (dbFile.fail())
		{
			cerr << "Unable to open file!" << endl;
			return;
		}

		dbFile << "EmployeeNumber";
		dbFile << ", " << "Address";
		dbFile << ", " << "Firstname:";
		dbFile << ", " << "Middlename:";
		dbFile << ", " << "Lastname";
		dbFile << endl;
		for (const auto &employee : mEmployees)
		{
			string emplNumStr = to_string(employee.getEmployeeNumber());
			dbFile << emplNumStr;

			string addr = employee.getAddress();
			dbFile << addr;

			string firstname = employee.getFirstName();
			dbFile << firstname;

			string middlename = employee.getMiddleName();
			dbFile << middlename;

			string lastname = employee.getLastName();
			dbFile << lastname;

			std:: replace(addr.begin(), addr.end(), ',', ' ');
			std:: replace(firstname.begin(), firstname.end(), ',', ' ');
			// std:: replace(middlename.begin(), firstname.end(), ',', ' ');
			// std:: replace(firstname.begin(), firstname.end(), ',', ' ');


			// dbFile << ", " << addr;
			// dbFile << ", " << empl.getFirstName();
			dbFile << endl;
		}
	}

	void Database::displayCurrent() const
	{
		for (const auto &employee : mEmployees)
		{
			if (employee.isHired())
				employee.display();
		}
	}

	void Database::displayFormer() const
	{
		for (const auto &employee : mEmployees)
		{
			if (!employee.isHired())
				employee.display();
		}
	}

	// void loadFile(const string &fileName) const
	// void Database::loadFile(const string& fileName)

	Database makeNewDB()
{
    log("start");
    vector<string> arrFirst {
    "first1", "Anisphia","John",
    "first2", "Anisphia2","John2",
    };

    vector<string> arrMiddle {
    "middle1", "Wynn","Mitchell",
    "middle2", "Wynn2","Mitchell2",
    };

    vector<string> arrLast {
    "last1", "Palettia","Doe",
    "last2", "Palettia2","Doe2",
    };

    // Database res;
    // for (const string & firstName: arrFirst)
    // {
    //     db.addEmployee(firstName, "Peter");
    // }

    Database db;
    int count = 0;
    for (const string & firstName: arrFirst){
        for (const string& middleName: arrMiddle)
        {
            for (const string& lastName: arrLast){
                // random street number
                // string
                count ++;
                string countStr = to_string(count);
                Employee& empl= db.addEmployee(firstName, middleName, lastName);
                // string address = to_string(count);
                string address = countStr + "Street#" + countStr;
                empl.setAddress(address);
            }
        }
    }

    log("end");
    return db;
}

	Database loadFile(const string& fileName)
	{
		log("start");

		Database db;
		ifstream dbFile(fileName, ios_base::trunc);
		if (dbFile.fail()) {
			cerr << "Cannot open file: " << fileName << endl;
			return db;
		}

		string header;
		getline(dbFile, header);
		cout << header << endl;
		log(header);
		string line;

		// Read contents of the file
		// https://www.geeksforgeeks.org/read-a-file-line-by-line-in-cpp/
		// https://www.w3schools.com/cpp/cpp_files.asp
		
		while (getline (dbFile, line)) 
		{
		// Output the text from the file
			cout << line << "\n";

			// stringstream inLine{ line };
			// string firstName, lastName, initials;
			// inLine >> (firstName) >> (lastName) >> (initials);
			// if (inLine.bad()) {
			// 	cerr << "Error reading person. Ignoring." << endl;
			// 	continue;
			vector<string> tokens;
			stringstream streamFromLine(line);
			string token;
			while(getline(streamFromLine, token, ','))
			{
				tokens.push_back(token);
			}

			string emplNumStr = tokens[Employee::CSV_INDEX_EMPLOYEE_NUM];
			string address = tokens[Employee::CSV_INDEX_EMPLOYEE_NUM];
			Employee empl("", "");
			empl.setAddress(address);
			empl.setEmployeeNumber(emplNumStr);
			// Add all fields
			db.addEmployee(empl);

			// Create a person and add it to the database.

			// mEmployees.push_back(theEmployee);
		}

		log("end");
		return db;
	}
}
