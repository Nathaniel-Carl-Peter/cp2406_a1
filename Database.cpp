#include <iostream>
#include <stdexcept>

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

// 	void Database::savetoFile(string_view fileName) const
// {
// 	if (fileName.size() == 0)
// 	{
// 		/* code */
// 	}
	
// 	ofstream outFile{ fileName.data(), ios_base::trunc };
// 	if (!outFile) {
// 		cerr << "Cannot open file: " << fileName << endl;
// 		return;
// 	}

	void Database::saveToFile(const string& fileName) const
	{
		if(fileName.size() == 0)
		{
			cout << "Ignore saving empty file name" << endl;
		}

		ofstream dbfile(fileName, ios_base::trunc);
		if (dbfile.fail()) {
			cerr << "Unable to open debug file!" << endl;
			return;
		}
		
		dbfile << "EmployeeNumber" << ", " << endl;
		for (const auto& employee : mEmployees) 
		{
			string emplNumStr = to_string(employee.getEmployeeNumber());
			dbfile << emplNumStr << ", " << endl;
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

	void Database::loadFromFile(string_view filename)
{
	ifstream inFile{ filename.data() };
	if (!inFile) {
		cerr << "Cannot open file: " << filename << endl;
		return;
	}

	while (inFile) {
		// Read line by line, so we can skip empty lines.
		// The last line in the file is empty, for example.
		string line;
		getline(inFile, line);
		if (line.empty()) { // Skip empty lines
			continue;
		}

		// Make a string stream and parse it.
		istringstream inLine{ line };
		string firstName, lastName, initials;
		inLine >> quoted(firstName) >> quoted(lastName) >> quoted(initials);
		if (inLine.bad()) {
			cerr << "Error reading person. Ignoring." << endl;
			continue;
		}

		// Create a person and add it to the database.
		m_persons.push_back(Person{ move(firstName), move(lastName), move(initials) });
	}
}
}
