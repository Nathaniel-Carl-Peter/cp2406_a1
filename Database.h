#pragma once

#include <iostream>
#include <vector>
#include "Employee.h"

namespace Records {
	const int kFirstEmployeeNumber = 1000;

	class Database
	{
	public:
		Employee& addEmployee(const std::string& firstName,
							  const std::string& lastName);
		
		// Function overide occuring
		Employee& addEmployee(
			const std::string& firstName,
			const std::string& middleName,
			const std::string& lastName);
		Employee& getEmployee(int employeeNumber);
		Employee& getEmployee(const std::string& firstName,
							  const std::string& lastName);

		void displayAll() const;
		void saveToFile(const string& fileName) const;
		void loadFromFile(string_view filename);
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
}
