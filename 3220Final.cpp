/* 
 * File:   3220Final.cpp
 * Title: Interface for Faculty, Teachers, and Students
 * Author: Chanse Meyer, Jonathan Davis, Tianchen Wang
 * Created on November 15, 2016, 5:58 PM
 */

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>
using namespace std;


string letters = "abcdefghijklmnopqrstuvwxyz";
/* class Course contains coutse name, number, credit hours and description and a method of checking entered course name
is/isnt in the course list*/

/* this class initiate course related information and check if input course name in the list */
class Course {
public:
    vector<string> course_names;    //course names vector
    vector<string> course_nums;     //course numbers vector
    vector<int> credit_hours;       //course credit hours vector
    vector<string> course_desc;     //course descriptions vector
    Course();                       //course constructor
};

Course::Course() {                  //course constructor
}

Course course;

int check_course(string cours) {        //checks to see if user's course number is in the actual list of course numbers
    int i;
    for (i = 0; i < course.course_nums.size(); i++) {   //goes through all course numbers to check for match
        if (cours == course.course_nums[i]) {
            return i;       //returns index of match
        }
    }
    return -1;
}


/* class UserType contains username, password, first mid and last name of user and methods handling(save) the inputs*/
/* usertype asking user input infor,  get and save infor */
class UserType {    //generic user class with name, username, and password
protected:
    string username;
    string password;
    string first_name;
    string mid_name;
    string last_name;
public:
    UserType();     //constructor
    UserType(string fname, string mname, string lname);     //second constructor with parameters

    string get_fname() {        //method to send first name
        return first_name;
    }
    void set_fname(string fname);      //method to set first name

    string get_mname() {        //method to send middle name
        return mid_name;
    }
    void set_mname(string mname);       //method to set middle name

    string get_lname() {        //method to send last name
        return last_name;
    }
    void set_lname(string lname);       //method to set last name

    string get_uname() {        //method to send username
        return username;
    }
    virtual void set_uname();       //method to set username

    string get_password() {     //method to send password
        return password;
    }
    void set_password(string pw);   //method to set password
    virtual void menu();
};

UserType::UserType() {      //constructor asking user name(first mid last) 
    cout << "Enter your first name:";
    cin >> first_name;
    cout << "Enter your middle name:";
    cin >> mid_name;
    cout << "Enter your last name:";
    cin >> last_name;
}

UserType::UserType(string fname, string mname, string lname) {      //constructor with parameters
    first_name = fname;
    mid_name = mname;
    last_name = lname;
}

void UserType::set_uname() {                                 //method to set and save user name(first,mid, last
    string tmp_first = get_fname(), tmp_last = get_lname(), tmp_uname;
    tmp_uname = tmp_first[0] + tmp_last;
    username = tmp_uname;
}

void UserType::menu() {                                       //usertype menu display message and filename
    cout << "Welcome " << get_fname() << ", to Elite University" << endl;
}

void UserType::set_password(string pw) {                          //method set password
    password = pw;
}
/* class Faculty inheritance class of Usertype */
class Faculty : public UserType {
private:                            // neither derived classes nor other users can access
    vector<char> schedule;
    int experience;
    double salary;
public:                             //public for all users
    Faculty(string fname, string mname, string lname);
    void set_uname();
    void menu();
    void operation(int choice);
    void saLary();
    void enrollSummary();
};

Faculty::Faculty(string fname, string mname, string lname) : UserType(fname, mname, lname) { // parametric constructor
    int numofyrs, numofmos;
    set_uname();
    cout << "How many years of experience do you have in your carrer?";
    cout << "Enter the number of years:";
    cin >> numofyrs;
    cout << "Enter the number of months:";
    cin >> numofmos;
    numofmos /= 12;
    experience += (numofyrs + numofmos);
}

void Faculty::set_uname() {                                 //method set username to conbine and create new name
    string tmp_first = get_fname(), tmp_last = get_lname(), tmp_uname;
    tmp_uname = tmp_first[0] + tmp_last; //create a new username set first letter of first name+last name
    username = tmp_uname;
}
    
void Faculty::menu() {                                         //method faculty menu
    system("cls");                                             //clear screen
    int choice = 0;
    cout << "Welcome " << get_fname() << ", to Elite University" << endl;
    while (choice != 3) {                                      //keep asking user input their chooice until summary picked
        system("cls");
        cout << "Choose an operation" << endl <<
                "1. Salary" << endl <<
                "2. Enrollment Summary" << endl <<
                "3. Logout" << endl;
        cin >> choice;
        operation(choice);                                      //operation called
    }
}

void Faculty::operation(int choice) {                           //operation to switch cases 1 to 3
    switch (choice) {  
        case 1:
            saLary();
            break;
        case 2:
            enrollSummary();
            break;
        case 3:
            break;
        default:                                                //default message: invalid choice displayed
            cout << "Invalid choice" << endl;
    }
}

void Faculty::saLary() {                                        //method salary to calculate and show the salary based on
    string pause;                                               //experience, base pay.
    int numofyrs, numofmos;
    double basepy = 60000;
    salary = basepy + (experience * 500);
    cout << "Salary : " << salary << endl;
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}
    
void Faculty::enrollSummary() {                                    //enrollSummary taking string pause in
    string pause;
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}
/*in class Teacher, inheritance class of class UserType. it asking the experiecne length of working and set name.
method menu display, operation chooice, courseEnrollment to ask what course going to teach and enrollmentSummary to 
give options 1.search enrollment summary for a course and 2 see the summary of enrollment in schedual */
class Teacher : public UserType {                                 //inheritance class of UserType
private:                                                            
    int experience;
    double salary;
    vector<string> schedule;
public:
    Teacher(string fname, string mname, string lname);
    void menu();
    void operation(int choice);
    void courseEnrollment();
    void saLary();
    void enrollSummary();
};

Teacher::Teacher(string fname, string mname, string lname) : UserType(fname, mname, lname) {//parametric constructor
    int numofyrs, numofmos;
    set_uname();
    cout << "How many years of experience do you have in your carrer?";
    cout << "Enter the number of years:";
    cin >> numofyrs;
    cout << "Enter the number of months:";
    cin >> numofmos;
    numofmos /= 12;
    experience += (numofyrs + numofmos);
}

void Teacher::menu() {                          //method display menu asking user chooice opeartion/enrollment/salary
                                                   //enrollment summary or logout
    system("cls");
    int choice = 0;
    cout << "Welcome " << get_fname() << ", to Elite University" << endl;
    while (choice != 4) {
        system("cls");
        cout << "Choose an operation" << endl <<
                "1. Course Enrollment" << endl <<
                "2. Salary" << endl <<
                "3. Enrollment Summary" << endl <<
                "4. Logout" << endl;
        cin >> choice;
        operation(choice);
    }
}

void Teacher::operation(int choice) {
    switch (choice) {                               //swich choice to perform different tasks
        case 1:                                     //case 1 courseEnrollment() being called
            courseEnrollment();
            break;
        case 2:                                     //case 2 saLary() called, the saLary based on information entered 
            saLary();
            break;
        case 3:                                        //case 3 check the enrollment Summary from schedual
            enrollSummary();
            break;
        case 4:                                       //case 4 break
            break;
        default:                                      //default error message 
            cout << "Invalid choice" << endl;
    }
}

void Teacher::courseEnrollment() {
    system("cls");                          //clear screen
    int i, index;
    string cours, pause;                    //define string
    cout << "What courses are you teaching this semester:" << endl <<
            "Enter the course number or if you don't know enter 'list' for an "
            "list of courses:" << endl;
    cin >> cours;
    if (cours == "list") {                          //check if the course name entered is in the list
        for (i = 0; i < course.course_names.size(); i++) {
            cout << course.course_names[i] << endl <<
                    course.course_desc[i] << endl;
        }
    } else {
        if (check_course(cours) != -1)
            schedule.erase(schedule.begin() + check_course(cours));
        else
            cout << "Not an course offered in the Electrical and Computer "
                "Engineering Department." << endl;
    }
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}
/*class student is inheritance class of UserType, */
class Student : public UserType {
private:                                        //private members 
    double tuition;
    double scholarship;
    vector<string> schedule;
public:                                         //public members/methods
    Student(string fname, string mname, string lname);
    void set_uname();
    void set_schedule(string cours);

    vector<string> get_schedule() {             
        return schedule;
    }
    void menu();                                        //declear methods
    void operation(int choice);
    void courseEnrollment();
    void tuiTion();
    void enrollSummary();
};

vector<Faculty> vecFac;                               //vector define
vector<Teacher> vecTeach;
vector<Student> vecStud;

Student::Student(string fname, string mname, string lname) : UserType(fname, mname, lname) {
    set_uname();                                        //parametric constructor
}

void Student::set_uname() {                             //set student name, all lower cases
    int index = rand() % 26;
    string tmp_first = get_fname(), tmp_mid = get_mname(), tmp_last = get_lname(), tmp_uname;
    stringstream ss;
    ss << tmp_first.length() % 10;
    string num = ss.str();
    tmp_uname.push_back(tolower(tmp_first[0]));
    tmp_uname.push_back(tolower(tmp_mid[0]));
    tmp_uname.push_back(tolower(tmp_last[0]));
    tmp_uname += num;
    tmp_uname.push_back(letters[index]);                  
    index = rand() % 26;
    tmp_uname.push_back(letters[index]);
    username = tmp_uname;
}

void Student::set_schedule(string cours) {
    schedule.push_back(cours);
}

void Teacher::enrollSummary() {     //with this the teacher method enrollSummary will not out of scope
    int i = 0, j = 0, choice, schcntr;
    string cours, pause;
    cout << "Choose an operation:" << endl <<
            "1) Search for the enrollment summary for a course." << endl <<
            "2) View the enrollment summary for a course in your schedule." << endl;
    cin >> choice;
    if (schedule.size() < 1)
        courseEnrollment();
    system("cls");
    while (choice != -1) {
        switch (choice) {
            case 1:
                cout << "Enter a course number using the following format CC ####:";
                fflush(stdin);
                getline(cin, cours, '\n');
                if (check_course(cours) != -1) {
                    while (i < vecStud.size()) {
                        j = 0;
                        while (j < vecStud[i].get_schedule().size()) {
                            if (vecStud[i].get_schedule()[j] == cours)
                                cout << vecStud[i].get_fname() + " " + vecStud[i].get_lname() << endl;
                            j++;
                        }
                        i++;
                    }
                } else {
                    cout << "Invalid course number" << endl;
                }
                break;
            case 2:
                int sumchoice;
                i = 0;
                sumchoice = -1;
                while (sumchoice < 0 || sumchoice > schedule.size()) {
                    cout << "Choose an course from your schedule you would like to view:" << endl;
                    for (schcntr = 0; schcntr < schedule.size(); schcntr++) {
                        cout << i++ << ") " << schedule[schcntr] << endl;
                    }
                    cout << ++i << ") Export all classes in your schedule to an pdf." << endl;
                    cin >> sumchoice;
                    i = 0;
                    if (sumchoice > 0 && sumchoice <= schedule.size()) {
                        cout << schedule[sumchoice] << endl;
                        if (sumchoice < vecStud.size()) {
                            while (i < vecStud.size()) {
                                j = 0;
                                while (j < vecStud[i].get_schedule().size()) {
                                    if (vecStud[i].get_schedule()[j] == schedule[sumchoice])
                                        cout << vecStud[i].get_fname() + " " + vecStud[i].get_lname() << endl;
                                    j++;
                                }
                                i++;
                            }
                        } else if (sumchoice == vecStud.size()) {
                            //Export function
                        }
                    } else
                        cout << "Invalid course selection." << endl;
                }
                break;
            default:
                cout << "Invalid choice pick again." << endl;
                break;
        }
    }
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}

void Teacher::saLary() {
    string pause;
    int schcntr, veccntr, strcntr, numofStud = 0;
    double basepy = 60000;
    for (schcntr = 0; schcntr < schedule.size(); schcntr++) {
        for (veccntr = 0; veccntr < vecStud.size(); veccntr++) {
            for (strcntr = 0; strcntr < vecStud[strcntr].get_schedule().size(); strcntr++) {
                if (schedule[schcntr] == vecStud[veccntr].get_schedule()[strcntr]) {
                    numofStud++;
                }
            }
        }
    }
    salary = basepy + (experience * 1200) + (numofStud * 500);
    cout << "Salary : $" << salary << endl;
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}

void Student::menu() {
    system("cls");
    int choice = 0;
    cout << "Welcome " << get_fname() << ", to Elite University" << endl;
    while (choice != 4) {
        system("cls");
        cout << "Choose an operation" << endl <<
                "1. Course Enrollment" << endl <<
                "2. Tuition" << endl <<
                "3. Enrollment Summary" << endl <<
                "4. Logout" << endl;
        cin >> choice;
        operation(choice);
    }
}

void Student::operation(int choice) {
    switch (choice) {
        case 1:
            courseEnrollment();
            break;
        case 2:
            tuiTion();
            break;
        case 3:
            enrollSummary();
            break;
        case 4:
            break;
        default:
            cout << "Invalid choice" << endl;
    }
}

void Student::courseEnrollment() {
    system("cls");
    int i, choice, delchoice, schcntr, index, err = 1;
    char cont = 'n';
    string cours, pause;
    cout << "Choose an operation:" << endl <<
            "1) Enroll in to a course" << endl <<
            "2) Drop an course" << endl;
    cin >> choice;
    switch (choice) {
        case 1:
            while (cont != 'y' || cont != 'Y') {
                cout << "What courses are you taking this semester:" << endl <<
                        "Enter the course number or if you don't know enter 'list' for an "
                        "list of courses:" << endl;
                fflush(stdin);
                getline(cin, cours, '\n');
                if (cours == "list") {
                    system("cls");
                    cout << "Electrical and Computer Engineering course offering:" << endl << endl;
                    for (i = 0; i < course.course_names.size(); i++) {
                        cout << course.course_names[i] << endl <<
                                "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl <<
                                course.course_nums[i] << endl <<
                                "*************************" << endl <<
                                course.course_desc[i] << endl << endl;
                        if (i % 3 == 0) {
                            cout << "Press any alpha numeric key followed by enter to continue...";
                            cin >> pause;
                        }
                    }
                } else {
                    int enrolled = 0;
                    if (check_course(cours) != -1) {
                        while (i <= schedule.size()) {
                            if (schedule[i] == cours) {
                                cout << "You're already enrolled in this course." << endl;
                                enrolled = 1;
                            } else if (i == schedule.size() && enrolled != 1)
                                schedule.push_back(cours);
                        }
                        cout << "Success, " << cours << " has been added to your schedule." << endl;
                    } else
                        cout << "Not an course offered in the Electrical and Computer "
                            "Engineering Department." << endl;
                }
                cout << "Press any alpha numeric key followed by enter to continue...";
                cin >> pause;
                while (err != 0) {
                    system("cls");
                    cout << "Would you like to add more courses to your schedule(y/n)?" << endl;
                    cin >> cont;
                    if (cont != 'y' || cont != 'Y' || cont != 'n' || cont != 'N') {
                        cout << "Invalid option, try again." << endl;
                    } else
                        err = 0;
                }
            }
            break;
        case 2:
            cont = 'n';
            while (cont != 'y' || cont != 'Y') {
                if (schedule.size() > 0) {
                    while (delchoice < 0 || delchoice > schedule.size()) {
                        cout << first_name << " " << last_name << "\'s Schedule" << endl <<
                                "****************************" << endl;
                        for (schcntr = 0; schcntr < schedule.size(); schcntr++) {
                            cout << i << ") " << schedule[schcntr] << endl;
                        }
                        cout << "Enter an course number from your schedule you would like to delete:" << endl;
                        cin >> cours;
                        i = 0;
                        if (check_course(cours) != -1)
                            while (i < schedule.size()) {
                                if (schedule[i] == cours)
                                    schedule[i].erase();
                                i++;
                                err = 1;
                                while (err != 0) {
                                    system("cls");
                                    cout << "Would you like to remove more courses from your schedule(y/n)?" << endl;
                                    cin >> cont;
                                    if (cont != 'y' || cont != 'Y' || cont != 'n' || cont != 'N') {
                                        cout << "Invalid option, try again." << endl;
                                    } else
                                        err = 0;
                                }
                            } else
                            cout << "Not an course offered in the Electrical and Computer "
                                "Engineering Department. Try entering another course number." << endl;
                    }
                } else
                    cout << "You are not enrolled into any classes.";
            }
            break;
        default:
            cout << "Invalid operation. Try again." << endl;
            break;
    }
}

void Student::tuiTion() {
    system("cls");
    string pause;
    int i, index, hours;
    char choice = 't';
    double total = 0;
    while (choice != 'y' || choice != 'n' || choice != 'Y' || choice != 'N') {
        system("cls");
        cout << "Did you receive scholarship money for this semester(y/n)?" << endl;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "What is the total amount of scholarship money did you receive for this year?: ";
            cin >> scholarship;
        } else if (choice == 'n' || choice == 'N') {
            scholarship = 0;
        } else
            cout << "Invalid option, Try again." << endl;
    }
    for (i = 0; i < schedule.size(); i++) {
        if ((index = check_course(schedule[i])) != -1) {
            hours = course.credit_hours[index];
            total = total + (hours * 276.20) + (hours * 13.20) +
                    (hours * 117.30) + 102.21 + 146.34 + 169.56;
        }
    }
    total -= (scholarship / 2);
    cout <<
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Tuition Breakdown~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl <<
            "General Tuition    @ $276.20 per credit hour" << endl <<
            "Info Tech Fee      @ $13.20 per credit hour" << endl <<
            "College of Eng     @ $84.90 per credit hour" << endl <<
            "Eng Excellence     @ $32.40 per credit hour" << endl <<
            "Prepaid Health Fee @ $102.21 flate rate" << endl <<
            "Rec Facility Fee   @ $146.34 flate rate" << endl <<
            "Student Act. Fee   @ $169.56 flate rate" << endl <<
            "Scholarship        @ -$" << scholarship / 2 << endl;
    tuition = total;
    cout << " Tuition total is $" << tuition << endl;
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}

void Student::enrollSummary() {
    system("cls");
    int i;
    char choice;
    cout << "Enrollment Summary" << endl <<
            "~~~~~~~~~~~~~~~~~~~" << endl;
    for (i = 0; i < schedule.size(); i++) {
        cout << schedule[i] << " " << course.course_names[check_course(schedule[i])] << endl;
    }
    while (choice == 'Y' || choice == 'y' || choice == 'n' || choice == 'N') {
        cout << "Would you like to export your course schedule to an pdf (y/n):";
        cin >> choice;
        if (choice == 'Y' || choice == 'y' || choice == 'n' || choice == 'N') {
            if (choice == 'Y' || choice == 'y') {
                //Put schedule into an file
            }
        } else {
            cout << "Invalid option. Try again." << endl;
            system("cls");
        }
    }
    string pause;
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}

int check_acct(string username, string password) {
    int i = 0;
    while (i < vecFac.size()) {
        if (username == vecFac[i].get_uname()) {
            if (password == vecFac[i].get_password()) {
                vecFac[i].menu();
                return i;
            }
        }
        i++;
    }
    i = 0;
    while (i < vecTeach.size()) {
        if (username == vecTeach[i].get_uname()) {
            if (password == vecTeach[i].get_password()) {
                vecTeach[i].menu();
                return i;
            }
        }
        i++;
    }
    i = 0;
    while (i < vecStud.size()) {
        if (username == vecStud[i].get_uname()) {
            if (password == vecStud[i].get_password()) {
                vecStud[i].menu();
                return i;
            }
        }
        i++;
    }
    return 1;
}

Faculty find_Facacct(string username, int index) {
    if (username == vecFac[index].get_uname())
        return vecFac[index];
}

Teacher find_Teaacct(string username, int index) {
    if (username == vecTeach[index].get_uname())
        return vecTeach[index];
}

Student find_Studacct(string username, int index) {
    if (username == vecStud[index].get_uname())
        return vecStud[index];
}

void load_data(string filename) {
    ifstream file(filename);
    int index = rand() % 26;
    string mname;
    string fname;
    string lname;
    string cours;

    if (!file) {
        cout << "File couldn't be open." << endl;
    } else {
        while (!file.eof()) {
            getline(file, fname);
            getline(file, lname);
            getline(file, cours);
            mname = letters[index];
            Student temp(fname, mname, lname);
            temp.set_schedule(cours);
            vecStud.push_back(temp);
        }
    }
}
/* */
void load_course(int argc, char** argv) {
    int i = 0;
    ifstream fileIn("courses.txt");
    string line, pause;
    if (!fileIn) {
        cout << "File couldn't be open." << endl;
    } else {
        while (!fileIn.eof()) {
            getline(fileIn, line);
            course.course_names.push_back(line);
            getline(fileIn, line);
            course.course_nums.push_back(line);
            getline(fileIn, line);
            course.credit_hours.push_back(stoi(line));
            getline(fileIn, line);
            course.course_desc.push_back(line);
        }
    }
    fileIn.close();
    if (argc == 3) {
        if (argv[1][0] == '-' && argv[1][1] == 'f') {
            load_data(argv[2]);
        }
    } else if (argc > 1) {
        cout << "Program will not run in demo mode" << endl;
        cout << "Press any alpha numeric key followed by enter to continue...";
        cin >> pause;
    }
}

int main(int argc, char** argv) {
    load_course(argc, argv);
    srand(time(NULL));
    int choice, index;
    bool loginsuccess = false;
    bool passwordsuccess = false;
    string username, firstname, midname, lastname, password, psswrdcon;
    char newuser = 'n', faculty = 'n', teacher = 'n', student = 'n';
    while (!loginsuccess) {
        cout << "Are you an new user?:" << endl;
        cin >> newuser;
        system("cls");
        while (newuser == 'Y' || newuser == 'y' || newuser == 'N' || newuser == 'n') {
            if (newuser == 'Y' || newuser == 'y') {
                cout << "What type of user are you?\n"
                        "1)Faculty\n"
                        "2)Teacher\n"
                        "3)Stdudent\n";
                cin >> choice;
                system("cls");
                if (choice == 1) {
                    cout << "Enter your first name:";
                    cin >> firstname;
                    cout << "Enter your middle name:";
                    cin >> midname;
                    cout << "Enter your last name:";
                    cin >> lastname;
                    while (!passwordsuccess) {
                        cout << "Enter your password:";
                        cin >> password;
                        cout << "Re-Enter your password:";
                        cin >> psswrdcon;
                        if (password == psswrdcon) {
                            passwordsuccess = true;
                        } else
                            cout << "Your password doesn't match. Try again" << endl;
                    }
                    Faculty temp(firstname, midname, lastname);
                    temp.set_uname();
                    system("cls");
                    cout << "Your user name is:" << temp.get_uname() << endl;
                    temp.set_password(password);
                    vecFac.push_back(temp);
                    newuser = 'n';
                } else if (choice == 2) {
                    cout << "Enter your first name:";
                    cin >> firstname;
                    cout << "Enter your middle name:";
                    cin >> midname;
                    cout << "Enter your last name:";
                    cin >> lastname;
                    while (!passwordsuccess) {
                        cout << "Enter your password:";
                        cin >> password;
                        cout << "Re-Enter your password:";
                        cin >> psswrdcon;
                        if (password == psswrdcon) {
                            passwordsuccess = true;
                        } else
                            cout << "Your password doesn't match. Try again" << endl;
                    }
                    Teacher temp(firstname, midname, lastname);
                    temp.set_uname();
                    system("cls");
                    cout << "Your user name is:" << temp.get_uname() << endl;
                    temp.set_password(password);
                    vecTeach.push_back(temp);
                    newuser = 'n';
                } else if (choice == 3) {
                    cout << "Enter your first name:";
                    cin >> firstname;
                    cout << "Enter your middle name:";
                    cin >> midname;
                    cout << "Enter your last name:";
                    cin >> lastname;
                    while (!passwordsuccess) {
                        cout << "Enter your password:";
                        cin >> password;
                        cout << "Re-Enter your password:";
                        cin >> psswrdcon;
                        if (password == psswrdcon) {
                            passwordsuccess = true;
                        } else
                            cout << "Your password doesn't match. Try again" << endl;
                    }
                    Student temp(firstname, midname, lastname);
                    temp.set_uname();
                    system("cls");
                    cout << "Your user name is:" << temp.get_uname() << endl;
                    temp.set_password(password);
                    vecStud.push_back(temp);
                    newuser = 'n';
                } else {
                    cout << "Invalid choice, try again:" << endl;
                }
            } else {
                cout << "Enter username:";
                cin >> username;
                cout << "Enter password:";
                cin >> password;
                if ((index = check_acct(username, password)) == 1)
                    cout << "Username and password does not match." << endl;
            }
        }
    }
    return 0;
}
