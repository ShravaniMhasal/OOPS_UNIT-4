#include <cstdio>    // for remove() and rename() to delete and rename files
#include <fstream>   // for reading and writing files (ifstream, ofstream)
#include <iostream>  // for console input/output (cin, cout, cerr)
#include <sstream>   // for stringstream (to split a line into parts)
#include <string>    // for using the string type

using namespace std;  // so I don't have to write std:: every time

int main() {
    // open the original file for reading
    ifstream oldFile("students.txt");

    // create a temporary file where the updated data will be written
    ofstream tempFile("students_temp.txt");

    // check if the original file opened properly
    if (!oldFile.is_open()) {
        cerr << "Error: Unable to open students.txt for reading.\n";
        return 1;  // non-zero return means something went wrong
    }

    // check if the temporary file was created properly
    if (!tempFile.is_open()) {
        cerr << "Error: Unable to create students_temp.txt.\n";
        oldFile.close();  // close the file that was opened before exiting
        return 1;
    }

    // take the roll number and new marks from the user
    int targetRoll;
    double newMarks;

    cout << "Enter the roll number of the student to update: ";
    cin >> targetRoll;
    cout << "Enter the new marks: ";
    cin >> newMarks;

    string line;         // stores one full line (one student record)
    bool found = false;  // becomes true if we find the roll number
    int total = 0;       // counter I added to count how many records were checked

    // read the file line by line
    while (getline(oldFile, line)) {
        // stringstream lets us split the line at every '|' character
        stringstream ss(line);

        string rollText;   // roll number as text
        string name;       // student name
        string marksText;  // old marks as text

        // split the record into 3 parts: roll | name | marks
        // this only runs the inside code if all 3 parts were read properly
        if (getline(ss, rollText, '|') &&
            getline(ss, name, '|') &&
            getline(ss, marksText)) {

            total++;  // one more valid record was read

            // stoi converts the roll number from text to an integer
            int roll = stoi(rollText);

            if (roll == targetRoll) {
                // this is the student we want, so write the NEW marks
                tempFile << roll << '|' << name << '|' << newMarks << '\n';
                found = true;
            }
            else {
                // this is some other student, so copy the line as it is
                tempFile << line << '\n';
            }
        }
    }

    // close both files before removing or renaming them
    // (a file cannot be deleted properly while it is still open)
    oldFile.close();
    tempFile.close();

    // if the roll number was not found, no update is needed
    // so delete the temporary file and stop
    if (!found) {
        remove("students_temp.txt");
        cout << "Student with roll number " << targetRoll << " was not found. No changes made.\n";
        cout << "Records checked: " << total << '\n';
        return 0;
    }

    // delete the old file (remove returns 0 if it worked)
    if (remove("students.txt") != 0) {
        cerr << "Error: Unable to delete the old students.txt.\n";
        return 1;
    }

    // rename the temporary file so it becomes the new students.txt
    if (rename("students_temp.txt", "students.txt") != 0) {
        cerr << "Error: Unable to rename students_temp.txt.\n";
        return 1;
    }

    // tell the user that everything worked
    cout << "\n";
    cout << "Marks updated successfully for roll number " << targetRoll << ".\n";
    cout << "Records checked: " << total << '\n';

    return 0;  // 0 means the program ran without any problem
}