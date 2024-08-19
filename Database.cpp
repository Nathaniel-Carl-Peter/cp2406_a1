#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include "my_debugger.h"
#include "Database.h"

using namespace std;

namespace Records {

	Employee& Database::addEmployee(const string& firstName,
		const string& lastName)
	{
		log("start");
		Employee theEmployee(firstName, lastName);
		theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
		theEmployee.hire();
		mEmployees.push_back(theEmployee);

		log("end");
		return mEmployees[mEmployees.size() - 1];
	}

	//Function overide to add a middleName field
	Employee& Database::addEmployee(
		const string& firstName,
		const string& middleName,
		const string& lastName)
	{
		log("start");

		Employee theEmployee(firstName, middleName,lastName);
		theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
		theEmployee.hire();
		mEmployees.push_back(theEmployee);

		log("end");
		return mEmployees[mEmployees.size() - 1];
	}

	Employee& Database::getEmployee(int employeeNumber)
	{
		for (auto& employee : mEmployees) {
			if (employee.getEmployeeNumber() == employeeNumber) {
				return employee;
			}
		}
		throw logic_error("No employee found.");
	}

	Employee& Database::getEmployee(const string& firstName, const string& lastName)
	{
		for (auto& employee : mEmployees) {
			if (employee.getFirstName() == firstName &&
				employee.getLastName() == lastName) {
					return employee;
			}
		}
		throw logic_error("No employee found.");
	}

	void Database::displayAll() const
	{
		for (const auto& employee : mEmployees) {
			employee.display();
		}
	}

	void Database::saveToFile(const string& fileName) const
	{
		// if(fileName.size() == 0)
		// {
		// 	cout << "Ignore saving empty file name" << endl;
		// }

		ofstream dbFile(fileName, ios_base::trunc);
		if (dbFile.fail()) {
			cerr << "Unable to open debug file!" << endl;
			return;
		}
		
		dbFile << "EmployeeNumber";
		dbFile << ", " << "Address";
		for (const auto& employee : mEmployees) 
		{
			string emplNumStr = to_string(employee.getEmployeeNumber());
			dbFile << emplNumStr;
			string addr = employee.getAddress();

			std::replace( addr.begin(), addr.end(), ',', ' ');

			dbFile << ", " << addr;
			dbFile << endl;
			
		}
	}

	void Database::displayCurrent() const
	{
		for (const auto& employee : mEmployees) {
			if (employee.isHired())
				employee.display();
		}
	}

	void Database::displayFormer() const
	{
		for (const auto& employee : mEmployees) {
			if (!employee.isHired())
				employee.display();
		}
	}

	Database loadFile(const string& fileName)
	{
		Database db;
		// if(fileName.size() == 0)
		// {
		// 	cout << "Ignore saving empty file name" << endl;
		// }

		ifstream dbFile(fileName, ios_base::in);
		if (dbFile.fail()) {
			cerr << "Unable to open file!" << fileName << endl;
			return db;
		}
		
		string header;
		getline(dbFile, header);
		cout << header << endl;
		log("header");

		// for (const auto& employee : mEmployees) 
		// {
		// 	string emplNumStr = to_string(employee.getEmployeeNumber());
		// 	dbFile << emplNumStr;
		// 	string addr = employee.getAddress();

		// 	std::replace( addr.begin(), addr.end(), ',', ' ');

		// 	dbFile << ", " << addr;
		// 	dbFile << endl;
			
		// }
		return db;
	}

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


}
