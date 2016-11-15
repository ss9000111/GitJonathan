// Lab9_vectors.cpp
// This program shows some simple vector examples, and asks for simple tasks.
// Reference: Lippman, section 3.3

// Author: Luis Rivera

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
// Example: g++ Lab9_vectors.cpp -o Lab9_vectors -std=c++11
// Some initialization methods and other things are not supported by the old standard.

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>

using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.

int main() {
    vector<int> ivec1(5), ivec2;
    vector<double> dvec1{5.1}, dvec2(5, 1.5);
    vector<string> svec1 = {"hello", "world"};
    // vector<myClass> myCvec;	//you can have vectors of objects
    // in general: vector<Type> vec;	//vector is a template

    for (int i = 0; i < ivec1.size(); i++)
        cout << ivec1[i] << endl;
    cout << "\n------------------------------------------------------------------" << endl;

    for (auto i : ivec1) // This is equivalent to the above for loop
        cout << i << endl;
    cout << "\n------------------------------------------------------------------" << endl;

    for (auto i : dvec1)
        cout << i << endl;
    cout << "\n------------------------------------------------------------------" << endl;

    for (auto i : dvec2)
        cout << i << endl;
    cout << "\n------------------------------------------------------------------" << endl;

    for (auto i : svec1)
        cout << i << endl;
    cout << "\n------------------------------------------------------------------" << endl;

    cout << "Original size: " << ivec2.size() << endl;
    ivec2.push_back(50);
    cout << "New size: " << ivec2.size() << "\nAdded element: " << ivec2[0] << endl;
    cout << "\n------------------------------------------------------------------" << endl;

    vector<int> v6 = ivec1;
    cout << v6[0] << endl;

    vector<double> v7(3, 0);
    v7[0] = 2;
    v7[1] = 24;
    v7[2] = 92;

    for (auto i : v7)
        cout << i << endl;

    vector<int> exc314(5, 0);
    vector<string> names(3);
    int count = 0;
    cout << "Enter 5 values:" << endl;
    while (count < exc314.size()) {
        cin >> exc314[count];
        count++;
    }
    if (!exc314.empty()) {
        cout << "The integer vector contains:" << endl;
        for (auto i : exc314)
            cout << i << endl;
    }
    cout << "The vector contains " << exc314.size() << " elements." << endl;
    count = 0;
    cout << "Enter three names :" << endl;
    while (count < names.size()){
        cin >> names[count];
        count++;
    }
    cout << "These are the inputted names:" << endl;
    for (auto i : names)
        cout << i << endl;
    cout << "Enter an name that will replace the second name:";
    cin >> names[1];
    return 0;
}