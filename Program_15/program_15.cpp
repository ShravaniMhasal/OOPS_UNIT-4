#include <cstdio>    // for remove() and rename() to delete and rename files
#include <fstream>   // for reading and writing files (ifstream, ofstream)
#include <iostream>  // for console input/output (cin, cout, cerr)
#include <limits>    // for numeric_limits (used to clear leftover input)
#include <sstream>   // for stringstream (to split a line into parts)
#include <string>    // for using the string type

// ---------- FUNCTION 1: ADD A NEW STUDENT ----------
// takes the details from the user and adds them at the end of the file
void addStudent() {
    // ios::app -> append mode, so the old records are not deleted
    std::ofstream outputFile("student_records.txt", std::ios::app);

    // check if the file was opened properly
    // if not, show an error and go back to the menu
    if (!outputFile) {
        std::cerr << "Error: Could not open student_records.txt\n";
        return;  // return is used here because the function is void
    }

    // variables to store the details of one student
    int rollNumber;
    std::string name;
    double marks;

    std::cout << "Enter roll number: ";
    std::cin >> rollNumber;

    // cin >> leaves the newline (Enter key) in the input buffer
    // if we don't remove it, getline will read an empty line and skip the name
    // so ignore() throws away everything up to and including the newline
    std::cout << "Enter name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);  // getline is used because the name can have spaces

    std::cout << "Enter marks: ";
    std::cin >> marks;

    // write the record in one line, with '|' separating each field
    // format: roll|name|marks
    outputFile << rollNumber << '|' << name << '|' << marks << '\n';

    std::cout << "Record added successfully.\n";
}  // outputFile is closed automatically when the function ends

// ---------- FUNCTION 2: DISPLAY ALL STUDENTS ----------
// reads the whole file and prints every record like a table
void displayStudents() {
    // open the file for reading
    std::ifstream inputFile("student_records.txt");

    // if the file does not exist yet, there is nothing to show
    if (!inputFile) {
        std::cout << "No student record file found.\n";
        return;
    }

    std::string line;  // stores one full line (one student record)

    // print the table heading (\t gives a tab space so the columns line up)
    std::cout << "\nRoll No.\tName\t\tMarks\n";
    std::cout << "----------------------------------------\n";

    // read the file line by line
    while (std::getline(inputFile, line)) {
        // stringstream lets us split the line at every '|' character
        std::stringstream record(line);

        std::string rollText;   // roll number as text
        std::string name;       // student name
        std::string marksText;  // marks as text

        // split the record into 3 parts: roll | name | marks
        // the inside code only runs if all 3 parts were read properly
        // (this also skips empty or damaged lines)
        if (std::getline(record, rollText, '|') &&
            std::getline(record, name, '|') &&
            std::getline(record, marksText)) {
            // print the three parts in one row of the table
            std::cout << rollText << "\t\t" << name << "\t\t" << marksText << '\n';
        }
    }
}

// ---------- FUNCTION 3: SEARCH A STUDENT ----------
// finds a student using the roll number and shows the details
void searchStudent() {
    // open the file for reading
    std::ifstream inputFile("student_records.txt");

    if (!inputFile) {
        std::cout << "No student record file found.\n";
        return;
    }

    // ask the user which roll number they want to find
    int targetRoll;
    std::cout << "Enter roll number to search: ";
    std::cin >> targetRoll;

    std::string line;    // stores one full line
    bool found = false;  // becomes true when the roll number is found

    // read the file line by line
    while (std::getline(inputFile, line)) {
        // split the line at every '|' character
        std::stringstream record(line);

        std::string rollText;
        std::string name;
        std::string marksText;

        // split the record into 3 parts and continue only if all were read
        if (std::getline(record, rollText, '|') &&
            std::getline(record, name, '|') &&
            std::getline(record, marksText)) {
            // stoi converts the roll number from text to an integer
            // so it can be compared with the number typed by the user
            if (std::stoi(rollText) == targetRoll) {
                std::cout << "Record Found\n";
                std::cout << "Roll Number: " << rollText << '\n';
                std::cout << "Name: " << name << '\n';
                std::cout << "Marks: " << marksText << '\n';
                found = true;
                break;  // no need to check the remaining lines, so stop the loop
            }
        }
    }

    // if the loop ended and the roll number was never found
    if (!found) {
        std::cout << "Student not found.\n";
    }
}

// ---------- FUNCTION 4: UPDATE MARKS ----------
// a text file cannot be edited in the middle easily, so we copy all the
// records into a temporary file (changing only the required one), then
// delete the old file and rename the temporary file to the old name
void updateMarks() {
    // old file for reading, temporary file for writing the updated data
    std::ifstream inputFile("student_records.txt");
    std::ofstream temporaryFile("student_records_temp.txt");

    // check if both files were opened properly
    if (!inputFile || !temporaryFile) {
        std::cerr << "Error: Could not open record file(s).\n";
        return;
    }

    // take the roll number and the new marks from the user
    int targetRoll;
    double newMarks;
    std::cout << "Enter roll number to update: ";
    std::cin >> targetRoll;
    std::cout << "Enter new marks: ";
    std::cin >> newMarks;

    std::string line;
    bool found = false;  // becomes true if we find the roll number

    // read the old file line by line
    while (std::getline(inputFile, line)) {
        // split the line at every '|' character
        std::stringstream record(line);

        std::string rollText;
        std::string name;
        std::string marksText;  // old marks (not used, we write the new marks)

        if (std::getline(record, rollText, '|') &&
            std::getline(record, name, '|') &&
            std::getline(record, marksText)) {
            if (std::stoi(rollText) == targetRoll) {
                // this is the student we want, so write the NEW marks
                temporaryFile << rollText << '|' << name << '|' << newMarks << '\n';
                found = true;
            } else {
                // this is some other student, so copy the line as it is
                temporaryFile << line << '\n';
            }
        }
    }

    // close both files before removing or renaming them
    // (a file cannot be deleted properly while it is still open)
    inputFile.close();
    temporaryFile.close();

    // if the roll number was not found, no update is needed
    // so delete the temporary file and stop
    if (!found) {
        std::remove("student_records_temp.txt");
        std::cout << "Student not found. No changes made.\n";
        return;
    }

    // remove() and rename() return 0 if they worked
    // first delete the old file, then give its name to the temporary file
    // if either step fails, show an error
    if (std::remove("student_records.txt") != 0 ||
        std::rename("student_records_temp.txt", "student_records.txt") != 0) {
        std::cerr << "Error: Could not replace the record file.\n";
        return;
    }

    std::cout << "Marks updated successfully.\n";
}

// ---------- MAIN FUNCTION: MENU ----------
int main() {
    int choice;  // stores the menu option chosen by the user

    // do-while is used so the menu is shown at least once
    // and keeps repeating until the user enters 0
    do {
        // show the menu
        std::cout << "\nStudent Record Manager\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. Display All Students\n";
        std::cout << "3. Search Student\n";
        std::cout << "4. Update Marks\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        // switch calls the function that matches the user's choice
        // break is needed after each case so the next case does not run too
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateMarks();
                break;
            case 0:
                std::cout << "Exiting program.\n";
                break;
            default:
                // runs when the number is not one of the options above
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);  // repeat the menu until the user chooses Exit

    return 0;  // 0 means the program ran without any problem
}