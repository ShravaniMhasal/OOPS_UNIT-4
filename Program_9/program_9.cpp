#include <fstream>   // for reading from files (ifstream)
#include <iostream>  // for console input/output (cin, cout, cerr)
#include <sstream>   // for stringstream (to split a line into parts)
#include <string>    // for using the string type

using namespace std;  // so I don't have to write std:: every time

int main() {
    // open "students.txt" for reading
    ifstream file("students.txt");

    // check if the file was opened properly
    // if not, show an error and stop the program
    if (!file.is_open()) {
        cerr << "Error: Unable to open students.txt for reading.\n";
        return 1;  // non-zero return means something went wrong
    }

    // ask the user which roll number they want to find
    int targetRoll;
    cout << "Enter the roll number to search: ";
    cin >> targetRoll;

    string line;          // stores one full line (one student record)
    bool found = false;   // becomes true when the roll number is found
    int checked = 0;      // counter I added to count how many records were checked

    // read the file line by line
    while (getline(file, line)) {
        // stringstream lets us split the line at every '|' character
        stringstream ss(line);

        string rollText;   // roll number as text
        string name;       // student name
        string marksText;  // marks as text

        // split the record into 3 parts: roll | name | marks
        // the inside code only runs if all 3 parts were read properly
        if (getline(ss, rollText, '|') &&
            getline(ss, name, '|') &&
            getline(ss, marksText)) {

            checked++;  // one more valid record was read

            // stoi converts text to int, stod converts text to double
            int roll = stoi(rollText);
            double marks = stod(marksText);

            // compare the roll number in the file with the one typed by the user
            if (roll == targetRoll) {
                cout << "----------------------------\n";
                cout << "Record Found!\n";
                cout << "Roll Number : " << roll << '\n';
                cout << "Name        : " << name << '\n';
                cout << "Marks       : " << marks << '\n';

                // extra feature I added: show a simple result based on the marks
                if (marks >= 40) {
                    cout << "Result      : Pass\n";
                }
                else {
                    cout << "Result      : Fail\n";
                }

                found = true;
                break;  // no need to check the remaining lines, so stop the loop
            }
        }
    }

    // close the file because we are done reading from it
    file.close();

    // if the loop ended and the roll number was never found
    if (!found) {
        cout << "Student with roll number " << targetRoll << " was not found.\n";
        cout << "Records checked: " << checked << '\n';
    }

    return 0;  // 0 means the program ran without any problem
}