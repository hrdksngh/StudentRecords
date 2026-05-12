// StudentRecords.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <optional>

#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
// Windows.h defines a macro called Division, clashes with string division in Student class. That's why the 2 shits above are needed

#include <commdlg.h>

#pragma comment(lib, "comdlg32.lib")

#include <stdexcept>

using namespace std;

// Helper functions go here:

bool getYesNo(const string& prompt) {
    char response;

    while (true) {
        cout << prompt << " (Y/N): ";
        cin >> response;

        if (response == 'Y' || response == 'y') {
            return true;
        }
        else if (response == 'N' || response == 'n') {
            return false;
        }
        else {
            cout << "Don't get frisky with response ideas. Stick to the options given!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int getInt(const string& prompt) {
    int response;

    while(true){
        cout << prompt;
        cin >> response;

        if (cin.fail()) {
            cout << "Invalid input! That's not a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            return response;
        }
    }
}

string avoidCommas(const string& prompt) {
    string input;

    while (true) {
        cout << prompt;
        getline(cin >> ws, input);

        if (input.find(',') == string::npos) {
            return input;
        }

        cout << "Storing commas is not supported yet. Please enter a value without it!" << endl;
    }
}

class Student {
private:

public:
    static int serial;
    int id;
    string name;
    string lastname;
    int age;
    int grade;
    string division;

    Student(const string& name, const string& lastname, int age, int grade, string division)
        : name(name), lastname(lastname), age(age), grade(grade), division(division) {
        id = ++serial;
    }

    void displayStudentInfo() const {
        cout << "ID: " << id << endl;
        cout << "First Name: " << name << endl;
		cout << "Last Name: " << lastname << endl;
        cout << "Age: " << age << endl;
        cout << "Grade: " << grade << endl;
        cout << "Division: " << division << endl;
	}
};

class StudentList {
public:
    vector<Student> studentlist;

    optional<Student> searchInfoByName(string name) { // This may be an obsolete function. May be deleted at the end of the project
        for (auto i = studentlist.begin(); i != studentlist.end(); i++) {
            if (i->name == name) {
                return *i;
            }
        }
        return nullopt;
    }

    void searchInfoByID(int id) {
        for (auto i = studentlist.begin(); i != studentlist.end(); i++) {
            if (i->id == id) {
                cout << "First Name: " << i->name << endl;
                cout << "Last Name: " << i->lastname << endl; 
                cout << "Age: " << i->age << endl; 
                cout << "Grade: " << i->grade << endl;
                cout << "Division: " << i->division << endl << endl;
                return;
            }
        }
        cout << "No such record with ID " << id << " exists!" << endl << endl;
    }

    void searchInfoByFirstName(string name) {
        bool hit = true;
        int count = 0;
        for(auto i = studentlist.begin(); i != studentlist.end(); i++){
            if (i->name == name) {
                hit = false;
                count++;
                cout << "ID: " << i->id << " \tFirst Name : " << i->name << " \tLast Name : " << i->lastname << " \tAge : " << i->age << " \tGrade : " << i->grade << " \tDivision : " << i->division << endl;
            }
        }
        if (hit) {
            cout << "No such record of student(s) named " << name << " exists" << endl << endl;
        }
        else {
            cout << "Total " << count << " record(s) found with first name " << name << endl << endl;
        }
    }

    void searchInfoByLastName(string lastname) {
        bool hit = true;
        int count = 0;
        for (auto i = studentlist.begin(); i != studentlist.end(); i++) {
            if (i->lastname == lastname) {
                hit = false;
                count++;
                cout << "ID: " << i->id << " \tFirst Name : " << i->name << " \tLast Name : " << i->lastname << " \tAge : " << i->age << " \tGrade : " << i->grade << " \tDivision : " << i->division << endl;
            }
        }
        if (hit) {
            cout << "No such record of student(s) with last name " << lastname << " exists" << endl << endl;
        }
        else {
            cout << "Total " << count << " record(s) found with last name " << lastname << endl << endl;
        }
    }

    void searchIntInfo(int option, int val){// 4 for Age, 5 for Grade
        bool hit = true;
        int count = 0;

        if (option == 4) {
            for (auto i = studentlist.begin(); i != studentlist.end(); i++) {
                if(i->age == val){
                    hit = false;
                    count++;
                    cout << "ID: " << i->id << " \tFirst Name : " << i->name << " \tLast Name : " << i->lastname << " \tAge : " << i->age << " \tGrade : " << i->grade << " \tDivision : " << i->division << endl;
                }
            }
            if (hit) {
                cout << "No such record with age " << val << " exists!" << endl << endl;
                return;
            }
            else {
                cout << "Total " << count << " record(s) found aged " << val << endl << endl;
                return;
            }
        }
        else {
            for (auto i = studentlist.begin(); i != studentlist.end(); i++) {
                if (i->grade == val) {
                    hit = false;
                    count++;
                    cout << "ID: " << i->id << " \tFirst Name : " << i->name << " \tLast Name : " << i->lastname << " \tAge : " << i->age << " \tGrade : " << i->grade << " \tDivision : " << i->division << endl;
                }
            }
            if (hit) {
                cout << "No such record of grade " << val << " exists!" << endl << endl;
                return;
            }
            else {
                cout << "Total " << count << " record(s) found in grade " << val << endl << endl;
                return;
            }
        }
    }

    void searchInfoByDivision(int grade, string division){
        bool hit = true;
        int count = 0;

        for (auto i = studentlist.begin(); i != studentlist.end(); i++) {
            if (i->grade == grade && i->division == division) {
                hit = false;
                count++;
                cout << "ID: " << i->id << " \tFirst Name : " << i->name << " \tLast Name : " << i->lastname << " \tAge : " << i->age << " \tGrade : " << i->grade << " \tDivision : " << i->division << endl;
            }
        }
        if (hit) {
            cout << "No such record of grade " << grade << " division " << division << " exists!" << endl << endl;
            return;
        }
        else {
            cout << "Total " << count << " record(s) found in grade " << grade << " division " << division << endl << endl;
            return;
        }
    }

    void addInfo(const Student& student) {
        studentlist.push_back(student);
        cout << "Student " << student.name << " added successfully." << endl << endl;

    }

    void deleteInfoByID(int id) {
        for (auto i = studentlist.begin(); i != studentlist.end(); i++) {
            if (i->id == id) {
                studentlist.erase(i);
                cout << "Student with ID " << id << " deleted successfully." << endl << endl;
                return;
            }
        }
        cout << "Student ID" << id << " not found." << endl << endl;
	}

    void deleteInfoByFirstName(string name) {
        int ifcount = 0;
        for (auto i = studentlist.begin(); i != studentlist.end(); ) {
            if (i->name == name) {
                i = studentlist.erase(i);
                /*cout << "Student " << name << " deleted successfully." << endl;
                return;*/
                ifcount++;
            }
            else {
                i++;
            }
        }
        if(!ifcount){
            cout << "Student " << name << " not found." << endl;
        }
        else {
            cout << "All student records by the first name of " << name << " have been deleted successfully!" << endl << endl;
        }
    }

    void deleteInfoByLastName(string lastname) {
        int ifcount = 0;
        for (auto i = studentlist.begin(); i != studentlist.end(); ) {
            if (i->lastname == lastname) {
                i = studentlist.erase(i);
                ifcount++;
            }
            else {
                i++;
            }
        }
        if (!ifcount) {
            cout << "Student " << lastname << " not found." << endl;
        }
        else {
            cout << "All student records by the last name of " << lastname << " have been deleted successfully!" << endl << endl;
        }
    }

    void deleteInfoByAge(int age) {
        int ifcount = 0;
        for (auto i = studentlist.begin(); i != studentlist.end(); ) {
            if (i->age == age) {
                i = studentlist.erase(i);
                ifcount++;
            }
            else {
                i++;
            }
        }
        if (!ifcount) {
            cout << "Student " << age << " not found." << endl;
        }
        else {
            cout << "All student records with the age " << age << " have been deleted successfully!" << endl << endl;
        }
    }

    void deleteInfoByGrade(int grade) {
        int ifcount = 0;
        for (auto i = studentlist.begin(); i != studentlist.end(); ) {
            if (i->grade == grade) {
                i = studentlist.erase(i);
                ifcount++;
            }
            else {
                i++;
            }
        }
        if (!ifcount) {
            cout << "Student " << grade << " not found." << endl;
        }
        else {
            cout << "All student records with the grade " << grade << " have been deleted successfully!" << endl << endl;
        }
    }

    void updateAllInfoByID(int id, string name, string lastname, int age, int grade, string division) {
        for (auto i = studentlist.begin(); i != studentlist.end(); i++) {
            if (i->id == id) {
                i->name = name;
                i->lastname = lastname;
                i->age = age;
                i->grade = grade;
                i->division = division;
                cout << "Student " << id << " updated successfully." << endl << endl;
                return;
            }
        }
        cout << "Student " << id << " not found." << endl << endl;
	}

    void updateStringsInfo(int id, int option, string update) {
        for (auto i = studentlist.begin(); i != studentlist.end(); i++) {

            if (i->id == id) {
          
                switch(option){ // 1, 2 & 5 are the string members

                case 1:
                    i->name = update;
                    cout << "First name of the student updated successfully!" << endl << endl;
                    return;
                case 2:
                    i->lastname = update;
                    cout << "Last name of the student updated successfully!" << endl << endl;
                    return;
                case 5:
                    i->division = update;
                    cout << "Division of the student updated successfully!" << endl << endl;
                    return;
                }
            }
        }
        cout << "No such student with ID " << id << " exists in our records" << endl << endl;
        return;
    }

    void updateIntsInfo(int id, int option, int update) {
        for (auto i = studentlist.begin(); i != studentlist.end(); i++) {

            if (i->id == id) {

                switch (option) { // 3 & 4 are int members

                case 3:
                    i->age = update;
                    cout << "Age of the student updated successfully!" << endl << endl;
                    return;
                case 4:
                    i->grade = update;
                    cout << "Grade of the student updated successfully!" << endl << endl;
                    return;
                }
            }
        }
        cout << "No such student with ID " << id << " exists in our records" << endl << endl;
        return;
    }


    // File I/O Functions
    // .txt is now obsolete

    /* AI TIP:
    const char* cannot be assigned to LPCWSTR / char* cannot be assigned to LPWSTR
    This means your project is set to Unicode character set, but the string literals in OPENFILENAME are narrow (char*).

    FIX:- Project → Properties → Advanced → Character Set → change to "Use Multi-Byte Character Set
    -Claude Sonnet 4.6
    */



    void saveDatabase() {
        char filename[MAX_PATH] = "";

        OPENFILENAME ofn;
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL;
        ofn.lpstrFilter = "CSV Files (*.csv)\0*.csv\0All Files (*.*)\0*.*\0";
        ofn.lpstrFile = filename;
        ofn.nMaxFile = MAX_PATH;
        ofn.lpstrTitle = "Save Database";
        ofn.lpstrDefExt = "csv";
        ofn.Flags = OFN_OVERWRITEPROMPT;

        if (GetSaveFileName(&ofn)) {
            ofstream file(filename);

            if (!file.is_open()) {
                cout << "Error: Could not open file for saving!" << endl << endl;
                return;
            }

            file << "ID,FirstName,LastName,Age,Grade,Division" << endl;

            for (const auto& student : studentlist) {
                file << student.id << ","
                    << student.name << ","
                    << student.lastname << ","
                    << student.age << ","
                    << student.grade << ","
                    << student.division << endl;
            }

            file.close();
            cout << "Database saved successfully!" << endl << endl;
        }
        else {
            cout << "Save operation cancelled." << endl << endl;
        }
    }

    void loadDatabase() {
        char filename[MAX_PATH] = "";

        OPENFILENAME ofn;
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL;
        ofn.lpstrFilter = "CSV Files (*.csv)\0*.csv\0All Files (*.*)\0*.*\0";
        ofn.lpstrFile = filename;
        ofn.nMaxFile = MAX_PATH;
        ofn.lpstrTitle = "Load Database";
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST; // Prevents selecting a non-existent file

        if (GetOpenFileName(&ofn)) {    // Opens the Open dialog. Returns true if user selects a file
            ifstream file(filename);

            if (!file.is_open()) {
                cout << "Error: Could not open the selected file!" << endl << endl;
                return;
            }

            studentlist.clear();

            string line;
            getline(file, line);    // Skip the header row

            int maxID = -1;

            while (getline(file, line)) {
                if (line.empty()) continue;

                stringstream ss(line);
                string token;

                int id, age, grade;
                string name, lastname, division;

                try {
                    getline(ss, token, ',');  id = stoi(token);
                    getline(ss, name, ',');
                    getline(ss, lastname, ',');
                    getline(ss, token, ',');  age = stoi(token);
                    getline(ss, token, ',');  grade = stoi(token);
                    getline(ss, division, ',');
                }
                catch (const invalid_argument&) {
                    cout << "Error: Invalid argument found in CSV. Skipping bad record: ";
                    cout << line << endl << endl;
                    continue;
                }
                catch (const out_of_range&) {
                    cout << "Error: Record Number is either too large or too small. Skipping bad record: ";
                    cout << line << endl << endl;
                    continue;
                }


                Student::serial = id - 1;
                Student s(name, lastname, age, grade, division);
                studentlist.push_back(s);

                if (id > maxID) maxID = id;
            }

            Student::serial = maxID;    // Makes new records continue from the topmost existing ID

            file.close();
            cout << "Database loaded successfully! "
                << studentlist.size() << " record(s) loaded." << endl << endl;
        }
        else {
            cout << "Load operation cancelled." << endl << endl;
        }
    }
};

int Student::serial = -1;

int main()
{
    StudentList sk;

    int x = 8888;
    
    int case3 = 0;
    while (x != 0) {
        bool case2 = true;
        switch (x) {

        case 8888:
            cout << "Database Menu. Select an option to proceed..." << endl;
            cout << "0. Exit" << endl;
            cout << "1. Add record" << endl;
            cout << "2. Search & Update menu" << endl;
            cout << "3. Delete menu" << endl;
			cout << "4. Display all records" << endl;
            cout << "5. Save/Load Database" << endl;
			cout << "Which option would you like to choose? ";
            cin >> x;
            cout << endl;
            break;

        case 1:
        {
            Student S_add = { "", "", 0, 0, " " };
     
            S_add.name = avoidCommas("Enter the first name of the student : ");

            S_add.lastname = avoidCommas("Enter the last name of the student: ");

            S_add.age = getInt("Enter the age of the student: ");

            S_add.grade = getInt("Enter the grade of the student: ");

            S_add.division = avoidCommas("Enter the division of the student: ");
            cout << endl;

            sk.addInfo(S_add);
            x = 8888;
            break;
        }

        // Search & Update Begins
        // x = 2 leads here
        // x = 5 takes back to the database menu
        // 

        case 2:

            while (case2) {

                cout << "Select an operation to perform:" << endl;
                cout << "1. Search record by ID" << endl;
                cout << "2. Search record by First name" << endl;
                cout << "3. Search record by Last name" << endl;
                cout << "4. Search record by Age" << endl;
                cout << "5. Search record by Grade" << endl;
                cout << "6. Search record by Grade & Division" << endl;
                cout << "7. Update a record via ID" << endl;
                cout << "8. Exit to main menu" << endl;

                int case2option = getInt("Which option do you choose? ");
                cout << endl;
                int tempid;

                int case2_7option;
                bool case2_7exit = true;

                string stringupdate = "";
                int intupdate;

                switch (case2option) {

                case 1: {
                    int idlook = getInt("Enter the ID you wish to search: ");
                    sk.searchInfoByID(idlook);
                    break;
                }

                case 2: {
                    string namelook = avoidCommas("Enter the first name to search record(s) of: ");
                    sk.searchInfoByFirstName(namelook);
                    break;
                }

                case 3: {
                    string lastnamelook = avoidCommas("Enter the last name to search record(s) of: ");
                    sk.searchInfoByLastName(lastnamelook);
                    break;
                }

                case 4: {
                    int agelook = getInt("Enter the age to search record(s) of: ");
                    sk.searchIntInfo(case2option, agelook);
                    break;
                }

                case 5: {
                    int gradelook = getInt("Enter the grade to search record(s) of: ");
                    sk.searchIntInfo(case2option, gradelook);
                    break;
                }

                case 6:
                {
                    int gradelook = getInt("Enter the grade to search record(s) of: ");
                    string divisionlook = avoidCommas("Enter the division to search record(s) of: ");

                    sk.searchInfoByDivision(gradelook, divisionlook);
                    break;
                }

                case 7:
                    
                    // This is where the update menu previously was, but pushed inside the while loop so it appears on every interation

                    while (case2_7exit) {

                        cout << "Update Menu" << endl;
                        cout << "1. Update first name" << endl;
                        cout << "2. Update last name" << endl;
                        cout << "3. Update age" << endl;
                        cout << "4. Update grade" << endl;
                        cout << "5. Update division" << endl;
                        cout << "6. Update everything" << endl;
                        cout << "7. Go back..." << endl;

                        case2_7option = getInt("Select an option: ");
                        cout << endl;

                        switch(case2_7option){

                        case 1:
                            tempid = getInt("Enter the ID you wish to update the first name of: ");
                            stringupdate = avoidCommas("Enter the updated first name: ");
                            cout << endl;

                            sk.updateStringsInfo(tempid, case2_7option, stringupdate);
                            //case2_7exit = false;
                            break;

                        case 2:
                            tempid = getInt("Enter the ID you wish to update the last name of: ");
                            stringupdate = avoidCommas("Enter the updated last name: ");
                            cout << endl;

                            sk.updateStringsInfo(tempid, case2_7option, stringupdate);
                            //case2_7exit = false;
                            break;

                        case 3:
                            tempid = getInt("Enter the ID you wish to update the age of: ");
                            intupdate = getInt("Enter the update age: ");

                            sk.updateIntsInfo(tempid,case2_7option,intupdate);
                            //case2_7exit = false;
                            break;

                        case 4:
                            tempid = getInt("Enter the ID you wish to update the grade of: ");
                            intupdate = getInt("Enter the update grade: ");

                            sk.updateIntsInfo(tempid, case2_7option, intupdate);
                            //case2_7exit = false;
                            break;

                        case 5:
                            tempid = getInt("Enter the ID you wish to update the division of: ");
                            stringupdate = avoidCommas("Enter the updated division: ");
                            cout << endl;

                            sk.updateStringsInfo(tempid, case2_7option, stringupdate);
                            //case2_7exit = false;
                            break;

                        case 6: {
                            tempid = getInt("Enter the ID of the student record you wish to update: ");
                            string nameupdate;
                            string lastnameupdate;
                            int ageupdate;
                            int gradeupdate;
                            string divisionupdate;

                            nameupdate = avoidCommas("Enter the first name of the student: ");

                            lastnameupdate = avoidCommas("Enter the last name of the student: ");

                            ageupdate = getInt("Enter the age of the student: ");

                            gradeupdate = getInt("Enter the grade of the student: ");

                            divisionupdate = avoidCommas("Enter the division of the student: ");
                            cout << endl;

                            sk.updateAllInfoByID(tempid, nameupdate, lastnameupdate, ageupdate, gradeupdate, divisionupdate);
                            //case2_7exit = false;
                            break;
                        }
                            
                        case 7:
                            case2_7exit = false;
                            //case2 = false;
                            break;

                        default:
                            cout << "Select a valid option!" << endl << endl;
                            //case2_7exit = false;
                            break;
                        }
                    }
                    break;

                case 8:
                    x = 8888;
                    case2 = false;
                    cout << endl;
                    break;

                default:
                    cout << "Select a valid option!" << endl << endl;
                    break;
                }

            }

            break;


        // 
        // Search & Update Ends
            
        case 3:
            cout << "Enter an option to choose:" << endl;
            cout << "1. Delete by ID" << endl;
            cout << "2. Delete by first name" << endl;
            cout << "3. Delete by last name" << endl;
            cout << "4. Delete by age" << endl;
            cout << "5. Delete by grade" << endl;
            cout << "6. Exit delete menu" << endl;

            cout << "Which option do you choose? ";
            cin >> case3;
            cout << endl;

            while (case3 != 8) {

                int case3optionINT;
                string case3optionSTRING;
                //char case3optionCHAR;
                //char case3optiontag;

                switch (case3) {

                case 6: //Exit delete menu
                    case3 = 8;
                    x = 8888;
                    break;

                case 1:
                    case3optionINT = getInt("Enter the ID to delete: ");

                    if (getYesNo("Are you sure you want to delete the student record of this ID?")) {
                        sk.deleteInfoByID(case3optionINT);
                    }
                    break;
                case 2:
                    case3optionSTRING = avoidCommas("Enter the first name of the records to delete: ");
                    
                    if (getYesNo("Are you sure you want to delete all the student records with this first name?")) {
                        sk.deleteInfoByFirstName(case3optionSTRING);
                    }
                    break;

                case 3:
                    case3optionSTRING = avoidCommas("Enter the last name of the records to delete: ");

                    if (getYesNo("Are you sure you want to delete all the student records with this last name?")) {
                        sk.deleteInfoByLastName(case3optionSTRING);
                    }
                    break;

                case 4:

                    case3optionINT = getInt("Enter the age you wish to delete records of: ");

                    if (getYesNo("Are you sure you want to delete all the students' record of this age?")) {
                        sk.deleteInfoByAge(case3optionINT);
                    }
                    break;

                case 5:

                    case3optionINT = getInt("Enter the grade you wish to delete records of: ");

                    if (getYesNo("Are you sure you want to delete all the student records of this grade?")) {
                        sk.deleteInfoByGrade(case3optionINT);
                    }
                    break;

                default:
                    cout << "Select a valid option!" << endl << endl;
                    break;
                }
                break;
            } // End of while loop of case 3
            break;
        case 4:
			cout << "All Student Records:" << endl;
            for (auto i = sk.studentlist.begin(); i != sk.studentlist.end(); i++) {
                cout << "---------------------------------" << endl;
                i->displayStudentInfo();
                cout << "---------------------------------" << endl;
            }
            cout << endl;
            x = 8888;
            break;
        case 5: {
            int case5option = 0;
            bool case5exit = false;
            
            while (!case5exit) {
                cout << "Save / Load Menu" << endl;
                cout << "1. Load Database" << endl;
                cout << "2. Save Database" << endl;
                cout << "3. Exit to Main Menu" << endl;
                cout << "WARNING: Avoid manually editing save files, as it may cause invalid records to be skipped entirely." << endl;
                case5option = getInt("Enter the option you wish to choose: ");

                switch (case5option) {
                case 1:{
                    cout << "Loading a new Database will overwrite the current Database. All the unsaved data will be lost..." << endl;
                    bool case5tag = getYesNo("Do you wish to proceed?");

                    if (case5tag) {
                        cout << "Database Load operation initiated..." << endl << endl;
                        this_thread::sleep_for(chrono::seconds(3));

                        // Database Load Code
                        sk.loadDatabase();

                        cout << "Datase Load operation ended." << endl;
                        cout << endl << endl;
                    }
                    else {
                        cout << "Loading Database aborted!" << endl << endl;
                    }

                    break;
                }
                case 2:
                    cout << "Database Save operation initiated..." << endl << endl;
                    this_thread::sleep_for(chrono::seconds(3));

                    // Database Save Code
                    sk.saveDatabase();

                    cout << "Datase Save operation ended." << endl;
                    cout << endl << endl;
                    break;
                case 3:
                    case5exit = true;
                    x = 8888;
                    break;
                default:
                    cout << "Enter a valid option!" << endl << endl;
                    break;
                }
            }
            
            
            break;
        }
        default :
            cout << "Invalid option. Please try again." << endl;
            cout << "Which option would you like to choose? ";
            cin >> x;
			break;
        }
    }
}







































// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
