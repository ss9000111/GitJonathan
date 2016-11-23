/* 
 * File:   3220Final.cpp
 * Author: Hank
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

class Course {
public:
    vector<string> course_names;
    vector<string> course_nums;
    vector<int> credit_hours;
    vector<string> course_desc;
    Course();
};

Course::Course() {
}

Course course;

int check_course(string cours) {
    int i;
    for (i = 0; i < course.course_nums.size(); i++) {
        if (cours == course.course_nums[i]) {
            return i;
        }
    }
    return -1;
}

class UserType {
protected:
    string username;
    string password;
    string first_name;
    string mid_name;
    string last_name;
public:
    UserType();
    UserType(string fname, string mname, string lname);

    string get_fname() {
        return first_name;
    }
    void set_fname(string fname);

    string get_mname() {
        return mid_name;
    }
    void set_mname(string mname);

    string get_lname() {
        return last_name;
    }
    void set_lname(string lname);

    string get_uname() {
        return username;
    }
    virtual void set_uname();

    string get_password() {
        return password;
    }
    void set_password(string pw);
    virtual void menu();
};

UserType::UserType() {
    cout << "Enter your first name:";
    cin >> first_name;
    cout << "Enter your middle name:";
    cin >> mid_name;
    cout << "Enter your last name:";
    cin >> last_name;
}

UserType::UserType(string fname, string mname, string lname) {
    first_name = fname;
    mid_name = mname;
    last_name = lname;
}

void UserType::set_uname() {
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

class Faculty : public UserType {
private:
    vector<char> schedule;
public:
    Faculty(string fname, string mname, string lname);
    void set_uname();
    void menu();
    void operation(int choice);
    void saLary();
    void enrollSummary();
};

Faculty::Faculty(string fname, string mname, string lname) : UserType(fname, mname, lname) {
    set_uname();
}

void Faculty::set_uname() {
    string tmp_first = get_fname(), tmp_last = get_lname(), tmp_uname;
    tmp_uname = tmp_first[0] + tmp_last;
    username = tmp_uname;
}

void Faculty::menu() {
    system("cls");
    int choice = 0;
    cout << "Welcome " << get_fname() << ", to Elite University" << endl;
    while (choice != 3) {
        system("cls");
        cout << "Choose an operation" << endl <<
                "1. Salary" << endl <<
                "2. Enrollment Summary" << endl <<
                "3. Logout" << endl;
        cin >> choice;
        operation(choice);
    }
}

void Faculty::operation(int choice) {
    switch (choice) {
        case 1:
            saLary();
            break;
        case 2:
            enrollSummary();
            break;
        case 3:
            break;
        default:
            cout << "Invalid choice" << endl;
    }
}

void Faculty::saLary() {
    string pause;
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}

void Faculty::enrollSummary() {
    string pause;
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}

class Teacher : public UserType {
private:
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

Teacher::Teacher(string fname, string mname, string lname) : UserType(fname, mname, lname) {
    set_uname();
}

void Teacher::menu() {
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
    switch (choice) {
        case 1:
            courseEnrollment();
            break;
        case 2:
            saLary();
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

void Teacher::courseEnrollment() {
    system("cls");
    int i;
    string cours, pause;
    cout << "What courses are you teaching this semester:" << endl <<
            "Enter the course number or if you don't know enter 'list' for an "
            "list of courses:" << endl;
    cin >> cours;
    if (cours == "list") {
        for (i = 0; i < course.course_names.size(); i++) {
            cout << course.course_names[i] << endl <<
                    course.course_desc[i] << endl;
        }
    } else {
        if (check_course(cours) != -1)
            schedule.push_back(cours);
        else
            cout << "Not an course offered in the Electrical and Computer "
                "Engineering Department." << endl;
    }
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}

void Teacher::saLary() {
    string pause;
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}

class Student : public UserType {
private:
    double tuition;
    vector<string> schedule;
public:
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
};

vector<Faculty> vecFac;
vector<Teacher> vecTeach;
vector<Student> vecStud;

Student::Student(string fname, string mname, string lname) : UserType(fname, mname, lname) {
    set_uname();
}

void Student::set_uname() {
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

void Teacher::enrollSummary() {
    int i = 0, j = 0;
    string cours, pause;
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
                "2. Salary" << endl <<
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
    int i;
    string cours, pause;
    cout << "What courses are you taking this semester:" << endl <<
            "Enter the course number or if you don't know enter 'list' for an "
            "list of courses:" << endl;
    cin >> cours;
    if (cours == "list") {
        system("cls");
        for (i = 0; i < course.course_names.size(); i++) {
            cout << course.course_names[i] << endl <<
                    course.course_nums[i] << endl <<
                    course.course_desc[i] << endl;
        }
    } else {
        if (check_course(cours) != -1)
            schedule.push_back(cours);
        else
            cout << "Not an course offered in the Electrical and Computer "
                "Engineering Department." << endl;
    }
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}

void Student::tuiTion() {
    system("cls");
    string pause;
    int i, index, hours;
    double total = 0;
    for (i = 0; i < schedule.size(); i++) {
        if ((index = check_course(schedule[i])) != -1) {
            hours = course.credit_hours[index];
            total = total + (hours * 276.20) + (hours * 13.20) +
                    (hours * 117.30) + 102.21 + 146.34 + 169.56;
        }
    }
    cout <<
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Tuition Breakdown~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl <<
            "General Tuition    @ $276.20 per credit hour" << endl <<
            "Info Tech Fee      @ $13.20 per credit hour" << endl <<
            "College of Eng     @ $84.90 per credit hour" << endl <<
            "Eng Excellence     @ $32.40 per credit hour" << endl <<
            "Prepaid Health Fee @ $102.21 flate rate" << endl <<
            "Rec Facility Fee   @ $146.34 flate rate" << endl <<
            "Student Act. Fee   @ $169.56 flate rate" << endl;
    tuition = total;
    cout << " Tuition total is $" << tuition << endl;
    cout << "Press any alpha numeric key followed by enter to continue...";
    cin >> pause;
}

void Student::enrollSummary() {
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

void load_course(int argc, char** argv) {
    int i = 0;
    ifstream fileIn("courses.txt");
    string line;
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
                else {
                    loginsuccess = true;
                    break;
                }
            }
        }
    }

    return 0;
}