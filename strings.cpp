// Lab9_strings.cpp
// This program shows some simple string examples, and asks for simple tasks.

#include <iostream>
#include <string>

using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.
int main()
{
	string s1, s2("Hello"), s3 = "World";
	cout << "\nEnter a word:" << endl;
	cin >> s1;
	
	string s4(s1);
	
	cout << s1 << endl
		 << s2 << endl
		 << s3 << endl
		 << s4 << endl;
	
	s1 = s2 + s3;
	cout << s1 << endl;
        
        string s5;
        cout << "Enter your name: ";
        getline(cin, s5, '\r');
        cout << s5 << endl;
        
        if (s5.empty() == 1)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl
                 << "size of s5 is "
                 << s5.size() << endl
                 << "The second letter in the string is "
                 << s5[1] << endl;
        
        string s6;
        s6 = s2 + " " + s5;
        cout << s6 << endl;
// -----------------------------------------------------------------------
	string line;
	cout << "\nEnter some text, finish it with an &" << endl;
	getline(cin, line, '&');
	cout << line << endl;
        int i = 0;
        while (i < line.length()){
            if (isupper(line[i]) && isalpha(line[i])){
                line[i] = tolower(line[i]);
            }
            else if (islower(line[i]) && isalpha(line[i])){
                line [i] = toupper(line[i]);
            }
            else if (isspace(line[i])){
                line[i] = '.';
            }
            i++;
        }
        cout << line << endl;
	return 0;
}