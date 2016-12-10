/* 
 * File:   3220Final.cpp
 * Title: Interface for Faculty, Teachers, and Students
 * Author: Chanse Meyer, Jonathan Davis, Tianchen Wang
 * 
 * Description:The project is a model of a school portal system similar to myZou.
 * The system will allow the user to login and based on the type of user there 
 * will be an custom menu. The system will provide functions such as showing a 
 * student their tuition, allowing a teacher to enroll into courses and allowing
 * a faculty member to view university revenue . For Teachers, the system will 
 * allow the teacher to look at who is enrolled into certain courses. The system
 * also gives the option to add courses to their schedule. For Faculty, the 
 * system will allow the user to look at how much raw revenue is being made 
 * based on the tuition of all the students currently enrolled in the system.
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
#include <cctype>
using namespace std;


string letters = "abcdefghijklmnopqrstuvwxyz";
/* class Course contains coutse name, number, credit hours and description and a method of checking entered course name
is/isnt in the course list*/

/* this class initiate course related information and check if input course name in the list */
class Course {
public:
    vector<string> course_names; //course names vector
    vector<string> course_nums; //course numbers vector
    vector<int> credit_hours; //course credit hours vector
    vector<string> course_desc; //course descriptions vector
    Course(); //course constructor
};

Course::Course() { //course constructor
}

Course course;

int check_course(string cours) { //checks to see if user's course number is in the actual list of course numbers
    int i;
    for (i = 0; i < course.course_nums.size(); i++) { //goes through all course numbers to check for match
        if (cours == course.course_nums[i]) {
            return i; //returns index of match
        }
    }
    return -1;
}


/* class UserType contains username, password, first mid and last name of user and methods handling(save) the inputs*/

/* usertype asking user input infor,  get and save infor */
class UserType { //generic user class with name, username, and password
protected:
    string username;
    string password;
    string first_name;
    string mid_name;
    string last_name;
public:
    UserType(); //constructor
    UserType(string fname, string mname, string lname); //second constructor with parameters

    string get_fname() { //method to send first name
        return first_name;
    }
    void set_fname(string fname); //method to set first name

    string get_mname() { //method to send middle name
        return mid_name;
    }
    void set_mname(string mname); //method to set middle name

    string get_lname() { //method to send last name
        return last_name;
    }
    void set_lname(string lname); //method to set last name

    string get_uname() { //method to send username
        return username;
    }
    virtual void set_uname(); //method to set username

    string get_password() { //method to send password
        return password;
    }
    void set_password(string pw); //method to set password
    virtual void menu();
};

UserType::UserType() { //constructor asking user name(first mid last) 
    cout << "Enter your first name:";
    cin >> first_name;
    cout << "Enter your middle name:";
    cin >> mid_name;
    cout << "Enter your last name:";
    cin >> last_name;
}

UserType::UserType(string fname, string mname, string lname) { //constructor with parameters
    first_name = fname;
    mid_name = mname;
    last_name = lname;
}

void UserType::set_uname() { //method to set and save user name(first,mid, last
    string tmp_first = get_fname(), tmp_last = get_lname(), tmp_uname;
    tmp_uname = tmp_first[0] + tmp_last;
    username = tmp_uname;
}

void UserType::menu() {
    cout << "Welcome " << get_fname() << ", to Elite University" << endl;
}

void UserType::set_password(string pw) {
    password = pw;
}

/* class Faculty inheritance class of Usertype */
class Faculty : public UserType {
private: // private member 
    vector<char> schedule;
    int experience;
    double salary;
public: //public member
    Faculty(string fname, string mname, string lname);
    void set_uname();
    void menu();
    void operation(int choice);
    void saLary();
    void enrollSummary();
};

Faculty::Faculty(string fname, string mname, string lname) : UserType(fname, mname, lname) {
    int numofyrs, numofmos;                                                     //Declaration of variables
    experience = 0;                                                             //Initialize to zero
    set_uname();                                                                //Calls method
    cout << "How many years of experience do you have in your career?" << endl; //Prompts and takes in user input.
    cout << "Enter the number of years:";
    cin >> numofyrs;
    cout << "Enter the number of months:";
    cin >> numofmos;
    numofmos /= 12;                                                             //Finds the decimal representation of the time frame in a year.
    experience += (numofyrs + numofmos);                                        //Assigns the total experience to the experience member of the class
}

void Faculty::set_uname() {
    string tmp_first = get_fname(), tmp_last = get_lname(), tmp_uname;
    tmp_uname = tmp_first[0] + tmp_last; //create a nuw username set first letter of first name+last name
    username = tmp_uname;
}
/*Unique menu for faculty class. Display 3 options instead of 4*/
void Faculty::menu() {
    system("cls");
    int choice = 0;
    string selection, pause;
    while (choice != 3) {
        system("cls");
        cout << "Welcome " << get_fname() << endl;                              //Prompts user with the menu
        cout << "Choose an operation" << endl <<
                "1. Salary" << endl <<
                "2. Revenue" << endl <<
                "3. Logout" << endl;
        fflush(stdin);
        getline(cin, selection, '\n');                                          //Takes in a user input
        if (isalpha(selection[0])) {                                            //Checks for an non numeric input
            cout << "Invalid input. You need to select an integer." << endl <<  //Prints error message
                    "Press any alpha numeric key followed by enter to continue...";
            cin >> pause;
        } else {
            choice = stoi(selection);                                           //converts an string to integer and assign to choice
            operation(choice);                                                  //calls the operation method
        }
    }
}
/*This is an unique operation method that provides the user 3 options*/
void Faculty::operation(int choice) {
    switch (choice) {
        case 1:
            saLary();                                                           //calls the saLary method
            break;
        case 2:
            enrollSummary();                                                    //calls the enrollSummary method
            break;
        case 3:
            break;
        default:
            cout << "Invalid choice" << endl;                                   //Prints invalid choice message to standard output
    }
}

void Faculty::saLary() {
    string pause;
    int numofyrs, numofmos;
    double basepy = 60000;
    salary = basepy + (experience * 500);                                       //Conduct math operations and assign to salary member.
    system("cls");
    cout << "Salary : " << salary << endl;                                      //Prints user's salary
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}

class Teacher : public UserType {
private:                                                                        //Private members
    int experience;
    double salary;
    vector<string> schedule;
public:                                                                         //Public members
    Teacher(string fname, string mname, string lname);
    void menu();
    void operation(int choice);
    void courseEnrollment();
    void saLary();
    void enrollSummary();
    void exportToFile();
};

Teacher::Teacher(string fname, string mname, string lname) : UserType(fname, mname, lname) {
    int numofyrs, numofmos;
    experience = 0;
    set_uname();                                                                //Sets user's username
    cout << "How many years of experience do you have in your career?" << endl; //Prompts user for experience
    cout << "Enter the number of years:";
    cin >> numofyrs;
    cout << "Enter the number of months:";
    cin >> numofmos;
    numofmos /= 12;
    experience += (numofyrs + numofmos);                                        //sums up experience and assigns value to experience member
}

void Teacher::menu() {
    system("cls");
    int choice = 0;
    string selection, pause;
    while (choice != 4) {                                                       //checks for exit option
        system("cls");
        cout << "Welcome " << get_fname() << endl;                              //Prompts the user with an menu
        cout << "Choose an operation" << endl <<
                "1. Course Enrollment" << endl <<
                "2. Salary" << endl <<
                "3. Enrollment Summary" << endl <<
                "4. Logout" << endl;
        fflush(stdin);
        getline(cin, selection, '\n');                                          //Takes in user input
        if (isalpha(selection[0])) {                                            //Checks for non-numeric input
            cout << "Invalid input. You need to select an integer." << endl <<  //Print invalid input message
                    "Press any alpha numeric key followed by enter to continue...";
            cin >> pause;
        } else {
            choice = stoi(selection);                                           //Converts string to integer and assign to choice
            operation(choice);                                                  //Calls operation method passing choice to the method
        }
    }
}
/*This method is unique to teacher class. It offers four options to user*/
void Teacher::operation(int choice) {
    switch (choice) {
        case 1:
            courseEnrollment();                                                 //calls courseEnrollment method
            break;
        case 2:
            saLary();                                                           //calls saLary method
            break;
        case 3:
            enrollSummary();                                                    //calls enrollSummary method
            break;
        case 4:
            break;
        default:
            cout << "Invalid choice" << endl;                                   //Prints invalid input message to standard input
    }
}
/*This method allows the teacher to add an course to their schedule*/
void Teacher::courseEnrollment() {
    system("cls");
    int i, index, err = 1;
    string cours, pause;
    char cont = 't';
    while (cont != 'N' && cont != 'n') {                                        //Checks to see if the user wants to leave the method
        err = 1;
        system("cls");
        cout << "What courses are you teaching this semester:" << endl <<       //Prompts the user for input
                "Enter the course number or if you don't know enter 'list' for an "
                "list of courses:" << endl;
        fflush(stdin);
        getline(cin, cours, '\n');                                              //Takes in from standard input
        if (cours == "list") {
            for (i = 0; i < course.course_names.size(); i++) {                  //Prints all course offering to the standard output
                cout << course.course_names[i] << endl <<
                        "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl <<
                        course.course_desc[i] << endl;
            }
        } else {
            if (check_course(cours) != -1) {                                    //Checks for valid course
                schedule.push_back(cours);
            } else
                cout << "Not an course offered in the Electrical and Computer " //Prints if not an course offered
                    "Engineering Department." << endl;
            while (err != 0) {                                                  //Handles error check
                cout << "Do you want to add another course(y/n)?" << endl;
                cin >> cont;
                if (cont != 'y' && cont != 'n' && cont != 'Y' && cont != 'N')
                    cout << "Invalid input." << endl;
                else
                    err = 0;
            }

        }
        cout << "Press any alpha numeric key followed by enter to continue...";
        cin >> pause;
    }
}

class Student : public UserType {
private:                                                                        //Private members
    double tuition;
    double scholarship;
    vector<string> schedule;
public:                                                                         //Public members
    Student(string fname, string mname, string lname);
    void set_uname();
    void set_schedule(string cours);

    vector<string> get_schedule() {
        return schedule;
    }
    void menu();
    void operation(int choice);
    void courseEnrollment();
    void tuiTion();
    void enrollSummary();
    void printTuition();

    void setScholarship(double amount) {
        scholarship = amount;
    }

    double getTuition() {
        return tuition;
    }
};

vector<Faculty> vecFac;                                                         //This vector holds class type Faculty
vector<Teacher> vecTeach;                                                       //This vector holds class type Teacher
vector<Student> vecStud;                                                        //This vector holds class type Student

Student::Student(string fname, string mname, string lname) : UserType(fname, mname, lname) {
    set_uname();                                                                //Sets username for Student user
}

void Student::set_uname() {
    int index = rand() % 26;
    string tmp_first = get_fname(), tmp_mid = get_mname(), tmp_last = get_lname(), tmp_uname;
    stringstream ss;
    ss << tmp_first.length() % 10;                                              //Gets the remainder of the length of the first name divided by ten
    string num = ss.str();
    tmp_uname.push_back(tolower(tmp_first[0]));                                 //Takes the first character of the first, middle, and last name
    tmp_uname.push_back(tolower(tmp_mid[0]));
    tmp_uname.push_back(tolower(tmp_last[0]));
    tmp_uname += num;                                                           //Concatenate the remainder
    tmp_uname.push_back(letters[index]);                                        //Concatenate two random characters
    index = rand() % 26;
    tmp_uname.push_back(letters[index]);
    username = tmp_uname;                                                       //Assigns generated string to username member
}

void Student::set_schedule(string cours) {                                      
    schedule.push_back(cours);                                                  //Adds course to schedule
}
/*This method exports all of the courses in the schedule to an text individual to each course*/
void Teacher::exportToFile() {
    int i = 0, j = 0, k = 0;
    while (i < schedule.size()) {                                               //Loops through schedule
        string course = schedule[i];
        course += ".txt";                                                       //Concatenate filename
        ofstream fileOut(course);                                               //Opens a file
        fileOut << schedule[i] << " Roster" << endl <<                          //Writes to file
                "~~~~~~~~~~~~~~~~~~~~~~" << endl <<
                "Professor: " << first_name << " " << last_name << endl;
        while (k < vecStud.size()) {                                            //Loops through the vector of students
            j = 0;
            while (j < vecStud[k].get_schedule().size()) {  
                if (vecStud[k].get_schedule()[j] == schedule[i])                //Checks for students enrolled in course        
                    fileOut << vecStud[k].get_fname() << " " << vecStud[k].get_lname() << endl; //Prints students name to file
                j++;
            }
            k++;
        }
        fileOut.close();                                                        //Closes file
        i++;
    }

}
/*This method prints the total revenue based on the number of students enrolled and tuition being paid*/
void Faculty::enrollSummary() {
    system("cls");
    string pause;
    int i = 0;
    double revenue = 0;
    while (i < vecStud.size()) {                                                //Loops through vector of students
        vecStud[i].tuiTion();                                                   //calls the tuiTion method for every student
        revenue += vecStud[i].getTuition();                                     //Sums up the tuition of all students and assign to an variable
        i++;
    }
    cout << "Total Revenue = $" << revenue << endl;                             //Prints total revenue
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}

void Teacher::enrollSummary() {
    int i = 0, j = 0, k = 0, choice, schcntr;
    string cours, pause, selection;
    while (choice != 3) {                                                       //Checks to see if user wants to return to main menu
        system("cls");
        cout << "Choose an operation:" << endl <<                               //Prompts the user for input
                "1) Search for the enrollment summary for a course." << endl <<
                "2) View the enrollment summary for a course in your schedule." << endl <<
                "3) Return to menu." << endl;
        getline(cin, selection, '\n');                                          //Takes in user input from the standard input
        if (isalpha(selection[0])) {                                            //Checks to see if input is an non-numeric character
            cout << "Invalid input. You need to select an integer." << endl <<  //Error message
                    "Press any alpha numeric key followed by enter to continue...";
            cin >> pause;
        } else {
            choice = stoi(selection);                                           //Convert string to an integer and assign to choic
            if (schedule.size() < 1)                                            //Check for empty schedule
                courseEnrollment();
            system("cls");
            switch (choice) {
                case 1:
                    cout << "Enter a course number using the following format ECE ####:";   //Prompts user
                    fflush(stdin);
                    getline(cin, cours, '\n');                                  //Takes in user input from standard input
                    if (check_course(cours) != -1) {                            //Checks for valid course
                        while (i < vecStud.size()) {                            //Loops through vector of students
                            j = 0;
                            while (j < vecStud[i].get_schedule().size()) {      //Look through students' schedule
                                if (vecStud[i].get_schedule()[j] == cours)      //Checks for enrolled course
                                    cout << vecStud[i].get_fname() + " " + vecStud[i].get_lname() << endl;  //Prints students names
                                j++;
                            }
                            i++;
                        }
                    } else {
                        cout << "Invalid course number" << endl;                //Prints invalid course entry
                    }
                    break;
                case 2:
                    int sumchoice;
                    char leave, print;
                    i = 0;
                    sumchoice = -1;
                    while (leave != 'y' && leave != 'Y') {                      //Checks if user wants to leave
                        cout << "Choose an course from your schedule you would like to view:" << endl;  //Prompts user for input
                        for (schcntr = 0; schcntr < schedule.size(); schcntr++) {   //Prints user schedule
                            cout << i + 1 << ") " << schedule[schcntr] << endl;
                            i++;
                        }
                        cout << ++i << ") Export all classes in your schedule to an pdf." << endl;
                        getline(cin, selection, '\n');                          
                        if (isalpha(selection[0])) {                                            //Checks to see if input is an non-numeric character
                            cout << "Invalid input. You need to select an integer." << endl <<  //Error message
                                    "Press any alpha numeric key followed by enter to continue...";
                            cin >> pause;
                        }else {
                            sumchoice = stoi(selection);                        //Converts string to integer and assigning to sumchoice
                            i = 0;
                            if ((sumchoice - 1) >= 0 && (sumchoice - 1) <= schedule.size()) { //Checks for valid values
                                if ((sumchoice - 1) < schedule.size()) {
                                    cout << schedule[sumchoice - 1] << " Roster" << endl;
                                    while (i < vecStud.size()) {                //Loops through vector of students
                                        j = 0;
                                        while (j < vecStud[i].get_schedule().size()) {  //Loops through schedule
                                            if (vecStud[i].get_schedule()[j] == schedule[sumchoice - 1])    //Checks for enrolled course
                                                cout << vecStud[i].get_fname() + " " + vecStud[i].get_lname() << endl;  //Prints student name
                                            j++;
                                        }
                                        i++;
                                    }
                                    cout << endl << endl << "Would you like to export the roster to an text file?"  //Prompts user for input
                                            "Enter \'y\' for yes or \'n\' for no.: ";
                                    cin >> print;                               //Take in user input
                                    if (print == 'y') {                         //Check input
                                        i = 0;
                                        string course = schedule[sumchoice - 1];
                                        course += ".txt";                       //Concatenate string for filename
                                        ofstream fileOut(course);
                                        fileOut << schedule[sumchoice - 1] << " Roster" << endl <<
                                                "~~~~~~~~~~~~~~~~~~~~~~" << endl <<
                                                "Professor: " << first_name << " " << last_name << endl;
                                        while (i < vecStud.size()) {            //Loops through file
                                            j = 0;
                                            while (j < vecStud[i].get_schedule().size()) {  //Loops through schedule
                                                if (vecStud[i].get_schedule()[j] == schedule[sumchoice - 13])   //Checks for enrolled course
                                                    fileOut << vecStud[i].get_fname() << " " << vecStud[i].get_lname() << endl; //Prints Students name to file
                                                j++;
                                            }
                                            i++;
                                        }
                                        fileOut.close();                        //Close file
                                    }
                                } else if ((sumchoice - 1) == schedule.size()) {//Check for export all option
                                    exportToFile();
                                }
                                while (leave != 'Y' && leave != 'y' && leave != 'n' && leave != 'N') {  //Handles error checking
                                    cout << "Do you want to return to the menu(y/n)?:";
                                    cin >> leave;
                                    if (leave != 'Y' && leave != 'y' && leave != 'n' && leave != 'N')
                                        cout << "Invalid choice, either enter \'y\' for yes or \'n\' for no." << endl;
                                }
                            } else
                                cout << "Invalid course selection." << endl;
                        }
                    }
                    break;
                case 3:
                    break;
                default:
                    cout << "Invalid choice pick again." << endl;               //Prints error message
                    break;
            }
        }
    }
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}
/*This method prints an teacher salary based on experience and number of students enrolled in course they teach*/
void Teacher::saLary() {
    string pause;
    int schcntr, veccntr, strcntr, numofStud = 0;
    double basepy = 60000;
    for (schcntr = 0; schcntr < schedule.size(); schcntr++) {                   //Loops through schedule
        for (veccntr = 0; veccntr < vecStud.size(); veccntr++) {                //Loops through vector of students
            for (strcntr = 0; strcntr < vecStud[strcntr].get_schedule().size(); strcntr++) {    //Loops through student schedules
                if (schedule[schcntr] == vecStud[veccntr].get_schedule()[strcntr]) {    //Checks for enrolled classes
                    numofStud++;                                                //Increment student counter
                }
            }
        }
    }
    salary = basepy + (experience * 1200) + (numofStud * 500);
    cout << "Salary : $" << salary << endl;                                     //Prints salary to standard output
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}

void Student::menu() {
    system("cls");
    int choice = 0;
    string selection, pause;
    while (choice != 4) {                                                       //checks for exit option
        system("cls");
        cout << "Welcome " << get_fname() << endl;                              //Prompts the user with an menu
        cout << "Choose an operation" << endl <<
                "1. Course Enrollment" << endl <<
                "2. Tuition" << endl <<
                "3. Enrollment Summary" << endl <<
                "4. Logout" << endl;
        fflush(stdin);
        getline(cin, selection, '\n');                                          //Takes in user input
        if (isalpha(selection[0])) {                                            //Checks for non-numeric input
            cout << "Invalid input. You need to select an integer." << endl <<  //Print invalid input message
                    "Press any alpha numeric key followed by enter to continue...";
            cin >> pause;
        } else {
            choice = stoi(selection);                                           //Converts string to integer and assign to choice
            operation(choice);                                                  //Calls operation method passing choice to the method
        }
    }
}

void Student::operation(int choice) {                   //switch choice to perform different tasks
    switch (choice) {
        case 1:                                         //case 1 courseEnrollment being called
            courseEnrollment();
            break;
        case 2:                                         //case 2 tuiTion and printTuition called
            tuiTion();
            printTuition();
            break;
        case 3:                                         //case 3 enrollSummary called
            enrollSummary();
            break;
        case 4:                                         // case 4 break
            break;
        default:
            cout << "Invalid choice" << endl;           //default error message
    }
}
/*This method allows an student to add an course to their schedule.*/
void Student::courseEnrollment() {
    int i, err = 1;                                                             //Variables are declared for the method 
    char cont = 't';
    string cours, pause;
    while (cont != 'n' && cont != 'N') {                                        //This loop is check to see if the user wants to leave the method
        err = 1;
        cout << "What courses are you taking this semester:" << endl <<         //Prompts user for classes they want to take and gives the user options
                "Enter the course number or if you don't know enter 'list' for an "
                "list of courses:" << endl;
        fflush(stdin);                                                          //Flushes the standard input to prep for the getline method.
        getline(cin, cours, '\n');                                              //This method takes in from standard input until the enter key is pressed.
        if (cours == "list") {
            system("cls");                                                      //Clears screen
            cout << "Electrical and Computer Engineering course offering:" << endl << endl;//Displays the courses offered in the Electrical and Computer Engineering Department.
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
            if (check_course(cours) != -1) {                                    //Checks to see if course is valid course offered
                while (i <= schedule.size()) {
                    if (schedule[i] == cours) {                                 //Checks to see if course is offered
                        cout << "You're already enrolled in this course." << endl;
                        enrolled = 1;
                    }
                }
                if (enrolled != 1) {                                            //Double checks if course is enrolled in to.
                    schedule.push_back(cours);                                  //Adds course to schedule
                    cout << "Success, " << cours << " has been added to your schedule." << endl;    //Prints successful enrollment
                }
            } else
                cout << "Not an course offered in the Electrical and Computer " //Prints invalid course entry
                    "Engineering Department." << endl;
        }
        cout << "Press any alpha numeric key followed by enter to continue...";
        cin >> pause;
        while (err != 0) {                                                      //loop for error check
            system("cls");
            cout << "Would you like to add more courses to your schedule(y/n)?" << endl;
            cin >> cont;
            if (cont != 'y' && cont != 'Y' && cont != 'n' && cont != 'N') {
                cout << "Invalid option, try again." << endl;
            } else
                err = 0;
        }
    }
}
/*This method calculates all of a students fees based on the credit hours taken.*/
void Student::tuiTion() {
    system("cls");
    string pause;
    int i, index, hours;
    char choice = 't';
    double total = 0;
    for (i = 0; i < schedule.size(); i++) {                                             //loops for all courses in schedule
        if ((index = check_course(schedule[i])) != -1) {
            hours = course.credit_hours[index];						//takes # hours for each class
            total = total + (hours * 276.20) + (hours * 13.20) +                        //uses those hours to calculate total tuition
                    (hours * 117.30) + 102.21 + 146.34 + 169.56;
        }
    }
    total -= (scholarship / 2);								//factors scholarship into tuition
    tuition = total;
}
/*This method prints the student tuition breakdown and prints the students tuition amount.*/
void Student::printTuition() {
    string pause;
    cout <<                                                                             //Prints tuition breakdown
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Tuition Breakdown~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl <<
            "General Tuition    @ $276.20 per credit hour" << endl <<
            "Info Tech Fee      @ $13.20 per credit hour" << endl <<
            "College of Eng     @ $84.90 per credit hour" << endl <<
            "Eng Excellence     @ $32.40 per credit hour" << endl <<
            "Prepaid Health Fee @ $102.21 flate rate" << endl <<
            "Rec Facility Fee   @ $146.34 flate rate" << endl <<
            "Student Act. Fee   @ $169.56 flate rate" << endl <<
            "Scholarship        @ $" << scholarship / 2 << endl;
    cout << " Tuition total is $" << tuition << endl;                                   //Prints total net tuition
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}

void Student::enrollSummary() {								//method to display student enrollment summary
    system("cls");									//clears the screen
    int i;
    char choice='t';
    cout << "Enrollment Summary" << endl <<
            "~~~~~~~~~~~~~~~~~~~" << endl;
    for (i = 0; i < schedule.size(); i++) {						//for loop to print all classes in a student schedule vector
        cout << schedule[i] << " " << course.course_names[check_course(schedule[i])] << endl;	//prints all classes in schedule
    }
    while (choice != 'n' && choice != 'N') {		
        cout << "Would you like to export your course schedule to an pdf (y/n):";	//asks user if they want a pdf of their classes
        cin >> choice;									//reads in user decision
        if (choice == 'Y' || choice == 'y') {						//writes schedule to PDF
            i = 0;
            string filename = first_name + "_" + last_name + "CourseSchedule";
            filename += ".txt";
            ofstream fileOut(filename);
            fileOut << first_name << " " << last_name << " Course Schedule" << endl <<
                    "~~~~~~~~~~~~~~~~~~~~~~" << endl;
            while (i < schedule.size()) {
                fileOut << schedule[i] << " " << course.course_names[check_course(schedule[i])] << endl;
                i++;
            }
            fileOut.close();
        } else if (choice != 'n' && choice != 'N') {
            cout << "Invalid option. Try again." << endl;
            system("cls");
        }
        cout << "Do you want to return to menu(y/n)?:";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
            choice = 'n';
    }
    string pause;
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}

int check_acct(string username, string password) {					//method used during login to check whether user entered valid account credentials
    int i = 0;
    while (i < vecFac.size()) {								//loops to check through all Faculty classes
        if (username == vecFac[i].get_uname()) {					//checks inputed username with each existing Faculty class's username
            if (password == vecFac[i].get_password()) {                                 //checks inputed password with each existing Faculty class's password
                vecFac[i].menu();                                                       //if they match, the menu comes up and all possible actions are implemented from there
                return i;                                                               //returns the index of the matched account in the Faculty vector
            }
        }
        i++;										//increments i so while loop searches next class in vector
    }
    i = 0;										//i is reset to 0 to search through Teacher vector
    while (i < vecTeach.size()) {							//loops to check through all Teacher classes
        if (username == vecTeach[i].get_uname()) {					//checks inputed username with each existing Teacher class's username
            if (password == vecTeach[i].get_password()) {                               //checks inputed password with each existing Teacher class's password
                vecTeach[i].menu();							//if they match, the menu comes up and all possible actions are implemented from there
                return i;								//returns the index of the matched account in the Teacher vector
            }
        }
        i++;                                                                            //increments i so while loop searches next class in vector
    }
    i = 0;										//i is reset to 0 to search through Student vector
    while (i < vecStud.size()) {                                                        //loops to check through all Student classes
        if (username == vecStud[i].get_uname()) {					//checks inputed username with each existing Student class's username
            if (password == vecStud[i].get_password()) {                                //checks inputed password with each existing Student class's password
                vecStud[i].menu();							//if they match, the menu comes up and all possible actions are implemented from there
                return i;								//returns the index of the matched account in the Student vector
            }
        }
        i++;										//increments i so while loop searches next class in vector
    }
    return -1;										//if there are no matches, return -1
}

void load_data(string filename) {							//load data method for demo mode (adds fake user accounts)
    ifstream file(filename);								//opens file
    int index = rand() % 26;								//random index used later
    string mname;													
    string fname;
    string lname;
    string cours;

    if (!file) {									//checks for demo.txt nonexistence
        cout << "File couldn't be open." << endl;					//error message
    } else {										//file exists case
        while (!file.eof()) {								//loops until reaches end of file
            getline(file, fname);							//gets next line (containing a first name)
            getline(file, lname);							//gets next line (containing a last name)
            getline(file, cours);							//gets next line (containing a course name)
            mname = letters[index];							//gives fake user a random middle initial
            Student temp(fname, mname, lname);						//creates Student class for fake student
            temp.set_schedule(cours);							//sets fake Student's class schedule
            temp.setScholarship(0);                                                     //Gives imported students scholarship of $0.
            vecStud.push_back(temp);							//pushes current student class onto Student vector
        }
    }
}

/* */
void load_course(int argc, char** argv) {                           //method to load in the courses.txt document
    int i = 0;
    ifstream fileIn("courses.txt");                                 //checks for a file
    string line, pause;
    if (!fileIn) {                                                  //checks for a nonexistent or unable to open file
        cout << "File couldn't be open." << endl;
    } else {                                                        //case for a good file
        while (!fileIn.eof()) {                                     //runs until end of file is reached
            getline(fileIn, line);                                  //takes in the next line
            course.course_names.push_back(line);                    //pushes next line to the course names vector
            getline(fileIn, line);                                  //gets next line
            course.course_nums.push_back(line);                     //pushes next line to course numbers vector
            getline(fileIn, line);                                  //gets next line
            course.credit_hours.push_back(stoi(line));              //pushes next line to the course credit hours vector
            getline(fileIn, line);                                  //gets next line
            course.course_desc.push_back(line);                     //pushes next line to the course descriptions vector
        }
    }
    fileIn.close();                                                 //once the end of file causes the while loop to stop, the file is closed
    if (argc == 3) {                                                //checks for 3 command line arguments (used for Demo)
        if (argv[1][0] == '-' && argv[1][1] == 'f') {               //checks for -f in command line (for demo, command line input would be "Final.exe -f demo.txt"
            load_data(argv[2]);                                     //loads user data from demo.txt
        }
    } else if (argc > 1) {                                          //if you are not doing a demo, but entered more than 1 argument, it tells you of an error
        cout << "Program will run, but not in demo mode" << endl;   //tells the user that the program will continue to run, just not in demo mode
        cout << "Press any alpha numeric key followed by enter to continue...";
        cin >> pause;
    }
}

int main(int argc, char** argv) {
    load_course(argc, argv); //calls function to load the list of courses
    srand(time(NULL)); //Initializes random number generator for use in creating username
    int choice, index;
    double amount;
    bool loginsuccess = false; //sets login result to failure as default so that later loops run at least once
    bool passwordsuccess = false; //sets password result to failure as default so that later loops run at least once 
    string username, firstname, midname, lastname, password, psswrdcon; //define strings for names, username, and password
    char newuser = 'n', faculty = 'n', teacher = 'n', student = 'n', schchoice = 't', eXit; //sets answers to questions to no as default 
    while (!loginsuccess) { //loop for login screen. loops until successful login is achieved
        system("cls");
        cout << "Are you an new user? (y/n):" << endl; //asks user to input whether they are a new user or not
        cin >> newuser; //reads in y/n response
        system("cls"); //clears the screen
        while (newuser == 'Y' || newuser == 'y' || newuser == 'N' || newuser == 'n') { //loop checking for a new user y/n response. if you respond anything
            if (newuser == 'Y' || newuser == 'y') { //new user Y case   //other than y, Y, n, or N, you will be looped back to the new user question
                cout << "What type of user are you?\n" //asks for type of user you are. your answer willdetermine what actions the program lets you perform
                        "1)Faculty\n"
                        "2)Teacher\n"
                        "3)Student\n";
                cin >> choice; //reads in user answer for type of user
                system("cls"); //clears the screen to prepare for next screen
                if (choice == 1) { //Faculty user case
                    cout << "Enter your first name:"; //asks for user first name
                    cin >> firstname; //reads in user first name input
                    cout << "Enter your middle name:"; //asks for user middle name
                    cin >> midname; //reads in user middle name input
                    cout << "Enter your last name:"; //asks for user last name
                    cin >> lastname; //reads in user last name input
                    while (!passwordsuccess) { //loop runs until successful password is achieved
                        cout << "Enter your password:"; //asks user for password
                        cin >> password; //reads in user password
                        cout << "Re-Enter your password:"; //asks for user to verify password
                        cin >> psswrdcon; //reads in user password again
                        if (password == psswrdcon) { //checks to see if user entered the same password each time, 
                            passwordsuccess = true; //therefore, setting the user's password to what they entered and allowing them to proceed
                        } else //case for incorrect entered password verification, causing this while to loop again
                            cout << "Your password doesn't match. Try again" << endl; //tells user their passwords did not match
                    }
                    Faculty temp(firstname, midname, lastname); //once you set a password, a Faculty class gets constructed for the current user
                    temp.set_uname(); //set user name method called to generate and set the username of the user in their instance of the class Faculty
                    system("cls"); //clears the screen
                    cout << "Your user name is:" << temp.get_uname() << endl; //tells the user their newly generated username
                    temp.set_password(password); //set password function called to set the password of the user in their instance of the class Faculty
                    vecFac.push_back(temp); //pushes newlymade Faculty class onto the vector of user classes
                    newuser = 'n';
                } else if (choice == 2) { //Teacher user case
                    cout << "Enter your first name:"; //asks for user first name
                    cin >> firstname; //reads in user first name input
                    cout << "Enter your middle name:"; //asks for user middle name
                    cin >> midname; //reads in user middle name input
                    cout << "Enter your last name:"; //asks for user last name
                    cin >> lastname; //reads in user last name input
                    while (!passwordsuccess) { //loop runs until successful password is achieved
                        cout << "Enter your password:"; //asks user for password
                        cin >> password; //reads in user password
                        cout << "Re-Enter your password:"; //asks for user to verify password
                        cin >> psswrdcon; //reads in user password again
                        if (password == psswrdcon) { //checks to see if user entered the same password each time, 
                            passwordsuccess = true; //therefore, setting the user's password to what they entered and allowing them to proceed
                        } else //case for incorrect entered password verification, causing this while to loop again
                            cout << "Your password doesn't match. Try again" << endl; //tells user their passwords did not match
                    }
                    Teacher temp(firstname, midname, lastname); //once you set a password, a Teacher class gets constructed for the current user
                    temp.set_uname(); //set user name method called to generate and set the username of the user in their instance of the class Teacher
                    system("cls"); //clears the screen
                    cout << "Your user name is:" << temp.get_uname() << endl; //tells the user their newly generated username
                    temp.set_password(password); //set user name method called to generate and set the username of the user in their instance of the class Teacher
                    vecTeach.push_back(temp); //pushes newlymade Teacher class onto the vector of user classes
                    newuser = 'n';
                } else if (choice == 3) { //Student user case
                    cout << "Enter your first name:"; //asks for user first name
                    cin >> firstname; //reads in user first name input
                    cout << "Enter your middle name:"; //asks for user middle name
                    cin >> midname; //reads in user middle name input
                    cout << "Enter your last name:"; //asks for user last name
                    cin >> lastname; //reads in user last name input
                    while (!passwordsuccess) { //loop runs until successful password is achieved
                        cout << "Enter your password:"; //asks user for password
                        cin >> password; //reads in user password
                        cout << "Re-Enter your password:"; //asks for user to verify password
                        cin >> psswrdcon; //reads in user password again
                        if (password == psswrdcon) { //checks to see if user entered the same password each time, 
                            passwordsuccess = true; //therefore, setting the user's password to what they entered and allowing them to proceed
                        } else //case for incorrect entered password verification, causing this while to loop again
                            cout << "Your password doesn't match. Try again" << endl; //tells user their passwords did not match
                    }
                    while (schchoice != 'y' && schchoice != 'n' && schchoice != 'Y' && schchoice != 'N') {
                        system("cls");
                        cout << "Did you receive scholarship money for this semester(y/n)?" << endl;
                        cin >> schchoice;
                        if (schchoice == 'y' || schchoice == 'Y') {
                            cout << "What is the total amount of scholarship money did you receive for this year?: ";
                            cin >> amount;
                        } else if (schchoice == 'n' || schchoice == 'N') {
                            amount = 0;
                        } else
                            cout << "Invalid option, Try again." << endl;
                    }
                    Student temp(firstname, midname, lastname); //once you set a password, a Student class gets constructed for the current user
                    temp.set_uname(); //set user name method called to generate and set the username of the user in their instance of the class Student
                    system("cls"); //clears the screen

                    cout << "Your user name is:" << temp.get_uname() << endl; //tells the user their newly generated username
                    temp.setScholarship(amount);
                    temp.set_password(password); //set user name method called to generate and set the username of the user in their instance of the class Student
                    vecStud.push_back(temp); //pushes newlymade Student class onto the vector of user classes
                    newuser = 'n';
                } else { //case for if the user doesn't enter a number corresponding to teacher, faculty, or student
                    cout << "Invalid choice, try again:" << endl;
                }
            } else { //case for if the user enters n or once a new account is created, meaning that they are now an existing user
                cout << "Enter username:"; //asks for the existing username
                cin >> username; //reads in username
                cout << "Enter password:"; //asks for existing password
                cin >> password; //reads in password
                if ((index = check_acct(username, password)) == 1) //calls method to check for existing account
                    cout << "Username and password does not match." << endl; //tells user if existing username and password do not match records
                cout << "Do you want to exit the program(y/n)?:";
                cin >> eXit;
                if (eXit == 'y' || eXit == 'Y') {
                    loginsuccess = true;
                } else if (eXit == 'n' || eXit == 'N')
                    newuser = 't';
            }
        }
    }
    return 0;
}