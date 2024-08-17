#include <iostream>
#include <stdexcept>
#include <exception>

#include "my_debugger.h"
#include "Database.h"

const string Logger::msDebugFileName = "debugfile.txt";

using namespace std;
using namespace Records;

int displayMenu();
void doHire(Database& db);
void doFire(Database& db);
void doPromote(Database& db);
void doDemote(Database& db);

// Database makeNewDB(int nFirst =20, int nMiddle =20, int nLastname =20)
Database makeNewDB()
{
    log("start");
    vector<string> arrFirst {
    "first1", "Anis",
    "first2", "Anis2"
    };

    vector<string> arrMiddle {
    "middle1", "Wynn",
    "middle2", "Wynn2",
    };

    vector<string> arrLast {
    "last1", "Palettia",
    "last2", "Palettia2",
    };

    // Database res;
    // for (const string & firstName: arrFirst)
    // {
    //     db.addEmployee(firstName, "Peter");
    // }

    Database db;
    for (const string & firstName: arrFirst){
        for (const string& middleName: arrMiddle){
            for (const string& lastName: arrLast){
                // random street number
                // string
                db.addEmployee(firstName, middleName, lastName);
                // empl.setAdress();
            }
        }
    }

    log("end");
    return db;
}

int main()
{
    log("start");

	Database employeeDB;

	bool done = false;
	while (!done) {
		int selection = displayMenu();
		switch (selection) {
		case 0:
            log("case0");
			done = true;
			break;
		case 1:
			doHire(employeeDB);
			break;
		case 2:
			doFire(employeeDB);
			break;
		case 3:
			doPromote(employeeDB);
			break;
		case 4:
			employeeDB.displayAll();
			break;
		case 5:
			employeeDB.displayCurrent();
			break;
		case 6:
			employeeDB.displayFormer();
			break;
        
        case 7:
			employeeDB = makeNewDB();
            // DB = Data Base
			break;
		default:
			cerr << "Unknown command." << endl;
			break;
		}
	}

    return 0;
    log("end");
}

int displayMenu()
{
	// Note:
	//		One important note is that this code assumes that the user will
	//		"play nice" and type a number when a number is requested.
	//		When you read about I/O in Chapter 13, you will learn how to
	//		protect against bad input.

    int selection;

    cout << endl;
    cout << "Employee Database" << endl;
    cout << "-----------------" << endl;
    cout << "1) Hire a new employee" << endl;
    cout << "2) Fire an employee" << endl;
    cout << "3) Promote an employee" << endl;
    cout << "4) List all employees" << endl;
    cout << "5) List all current employees" << endl;
    cout << "6) List all former employees" << endl;
    cout << "7) Generate new Database" << endl;
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "---> ";
    
	cin >> selection;
    
	return selection;
}

void doHire(Database& db)
{
    log("start");
    string firstName;
    string lastName;

    cout << "First name? ";
    cin >> firstName;
    cout << "Last name? ";
    cin >> lastName;
    
    db.addEmployee(firstName, lastName);
    log("end");
}

void doFire(Database& db)
{
    log("start");
    
    int employeeNumber;

    cout << "Employee number? ";
    cin >> employeeNumber;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        emp.fire();
        cout << "Employee " << employeeNumber << " terminated." << endl;
    } catch (const std::logic_error& exception) {
        cerr << "Unable to terminate employee: " << exception.what() << endl;
    }
    
    log("end");
}

void doPromote(Database& db)
{
    log("start");

    int employeeNumber;
    int raiseAmount;

    cout << "Employee number? ";
    cin >> employeeNumber;
    cout << "How much of a raise? ";
    cin >> raiseAmount;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        emp.promote(raiseAmount);
    } catch (const std::logic_error& exception) {
        cerr << "Unable to promote employee: " << exception.what() << endl;
    }
    
    log("end");
}