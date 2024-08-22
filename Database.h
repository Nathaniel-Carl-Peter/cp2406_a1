#pragma once

#include <iostream>
#include <string>  // Required for std::string

#include <string_view>
#include <vector>
#include "Employee.h"

namespace Records {
	const int kFirstEmployeeNumber = 1000;

	class Database
	{
	public:
		Employee& addEmployee(const std::string& firstName,
							  const std::string& lastName);
		
		Employee& addEmployee(Employee empl);
		// Function overide occuring
		Employee& addEmployee(
			const std::string& firstName,
			const std::string& middleName,
			const std::string& lastName);
		Employee& getEmployee(int employeeNumber);
		Employee& getEmployee(const std::string& firstName,
							  const std::string& lastName);

		void displayAll() const;
		void saveToFile(const std::string& fileName) const;
		void searchMenu() const;
		Database searchFirstName() const;
		Database searchMiddleName() const;
		Database searchLasttName() const;
		// void saveToFile(const string& fileName) const;
		// void makeNewdb();
		void displayCurrent() const;
		void displayFormer() const;

	private:
		std::string mFirstName;
		std::string MiddleName;
		std::string mLastName;
		std::vector<Employee> mEmployees;
		int mNextEmployeeNumber = kFirstEmployeeNumber;
		bool mHired = false;
	};
	
	Database makeNewDB();
	Database loadFile(const std::string& fileName);
	// Database loadFromFile(std::string_view fileName);
}
