// StudentRecords.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <optional>
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

    void displayStudentInfo() {
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
        cout << "Student " << student.name << " added successfully." << endl;

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
};

int Student::serial = -1;

int main()
{
    StudentList sk;
    
    Student placeholderDataEntry = { "Fefault", "Lefault", 0, 0, "Default"};
    sk.studentlist.push_back(placeholderDataEntry);
    
    Student s1("Hardik","Singh",23,17,"B");
    Student s2("Mansi", "Pathak", 23, 17, "B");
    Student s3("Ayushi", "Khanduri", 25, 19, "D");
    Student s4("Brahmjot", "Singh", 23, 17, "A");
    Student s5("Shelly", "Sharma", 25, 19, "B");
    Student s6("Lahari", "Basu", 25, 19, "E");
    sk.studentlist.push_back(s1);
    sk.studentlist.push_back(s2);
    sk.studentlist.push_back(s3);
    sk.studentlist.push_back(s4);
    sk.studentlist.push_back(s5);
    sk.studentlist.push_back(s6);
    
    /*
    sk.searchInfo("Sneha")->displayStudentInfo();
    cout << endl;
    */

    int x = 5;
    
    int case3 = 0;
    while (x != 0) {
        bool case2 = true;
        switch (x) {

        case 5:
            cout << "Database Menu. Select an option to proceed..." << endl;
            cout << "0. Exit" << endl;
            cout << "1. Add record" << endl;
            cout << "2. Search & Update menu" << endl;
            cout << "3. Delete menu" << endl;
			cout << "4. Display all records" << endl;
			cout << "Which option would you like to choose? ";
            cin >> x;
            cout << endl;
            break;

        case 1:
        {
            Student S_add = { "", "", 0, 0, " " };
     
            cout << "Enter the first name of the student: ";
            cin >> S_add.name;

            cout << "Enter the last name of the student: ";
            cin >> S_add.lastname;

            S_add.age = getInt("Enter the age of the student: ");

            S_add.grade = getInt("Enter the grade of the student: ");

            cout << "Enter the division of the student: ";
            cin >> S_add.division;
            cout << endl;

            sk.addInfo(S_add);
            x = 5;
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
                    string namelook;
                    cout << "Enter the first name to search record(s) of: ";
                    cin >> namelook;
                    sk.searchInfoByFirstName(namelook);
                    break;
                }

                case 3: {
                    string lastnamelook;
                    cout << "Enter the last name to search record(s) of: ";
                    cin >> lastnamelook;
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
                    string divisionlook;
                    cout << "Enter the division to search record(s) of: ";
                    cin >> divisionlook;

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
                            cout << "Enter the updated first name: ";
                            cin >> stringupdate;
                            cout << endl;

                            sk.updateStringsInfo(tempid, case2_7option, stringupdate);
                            //case2_7exit = false;
                            break;

                        case 2:
                            tempid = getInt("Enter the ID you wish to update the last name of: ");
                            cout << "Enter the updated last name: ";
                            cin >> stringupdate;
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
                            cout << "Enter the updated division: ";
                            cin >> stringupdate;
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

                            cout << "Enter the first name of the student: ";
                            cin >> nameupdate;

                            cout << "Enter the last name of the student: ";
                            cin >> lastnameupdate;

                            ageupdate = getInt("Enter the age of the student: ");

                            gradeupdate = getInt("Enter the grade of the student: ");

                            cout << "Enter the division of the student: ";
                            cin >> divisionupdate;
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
                    x = 5;
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
                    x = 5;
                    break;

                case 1:
                    case3optionINT = getInt("Enter the ID to delete: ");

                    if (getYesNo("Are you sure you want to delete the student record of this ID?")) {
                        sk.deleteInfoByID(case3optionINT);
                    }
                    break;
                case 2:
                    cout << "Enter the first name of the records to delete: ";
                    cin >> case3optionSTRING;
                    
                    if (getYesNo("Are you sure you want to delete all the student records with this first name?")) {
                        sk.deleteInfoByFirstName(case3optionSTRING);
                    }
                    break;

                case 3:
                    cout << "Enter the last name of the records to delete: ";
                    cin >> case3optionSTRING;

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
            x = 5;
            break;
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
