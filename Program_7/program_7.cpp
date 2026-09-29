#include <fstream>   // for writing to files (ofstream)
#include <iostream>  // for console input/output (cin, cout, cerr)
#include <limits>    // for numeric_limits (used to clear leftover input)
#include <string>    // for using the string type to store the name

using namespace std;  // so I don't have to write std:: every time

int main() {
    // open "students.txt" in append mode so old records are not deleted
    // new records are added at the end of the file
    ofstream file("students.txt", ios::app);

    // check if the file was opened properly
    // if not, show an error and stop the program
    if (!file.is_open()) {
        cerr << "Error: Unable to open students.txt for writing.\n";
        return 1;  // non-zero return means something went wrong
    }

    // variables to store the details of one student
    int roll;
    string name;
    double marks;

    // take the student details from the user
    cout << "Enter roll number: ";
    cin >> roll;

    // cin >> leaves the newline (Enter key) in the input buffer
    // if we don't remove it, getline will read an empty line and skip the name
    // so ignore() throws away everything up to and including the newline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter student name: ";
    getline(cin, name);  // getline is used because the name can have spaces

    cout << "Enter marks: ";
    cin >> marks;

    // check if the marks are in a sensible range (extra check I added)
    if (marks < 0 || marks > 100) {
        cout << "Warning: marks should be between 0 and 100.\n";
    }

    // write the record in one line, with '|' separating each field
    // format: roll|name|marks
    file << roll << '|' << name << '|' << marks << '\n';

    // close the file so the data is saved properly
    file.close();

    // tell the user that the record was saved
    cout << "----------------------------\n";
    cout << "Student record for " << name << " saved successfully.\n";

    return 0;  // 0 means the program ran without any problem
}