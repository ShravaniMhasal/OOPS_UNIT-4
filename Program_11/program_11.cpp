#include <cstring>   // for strncpy() to copy text into a char array
#include <fstream>   // for reading and writing files (ifstream, ofstream)
#include <iostream>  // for console input/output (cout, cerr)

using namespace std;  // so I don't have to write std:: every time

// structure to store the details of one student
// binary files store the raw bytes of this structure directly
struct Student {
    int roll;       // roll number
    char name[30];  // name stored as a char array (not string, because string
                    // cannot be written to a binary file safely)
    float marks;    // marks of the student
};

int main() {
    // create a student variable and set everything to 0 first
    // the {} makes sure there is no garbage value inside
    Student s1{};

    // fill in the student details
    s1.roll = 102;
    strncpy(s1.name, "Rohan Deshmukh", sizeof(s1.name) - 1);  // copy the name
    // sizeof - 1 keeps space for the '\0' at the end of the name
    s1.marks = 91.5f;

    // ---------- WRITING THE RECORD ----------

    // ios::binary means the data is written as raw bytes, not as text
    ofstream outFile("students.dat", ios::binary);

    // check if the file was created properly
    if (!outFile.is_open()) {
        cerr << "Error: Unable to create students.dat.\n";
        return 1;  // non-zero return means something went wrong
    }

    // write() needs a char* pointer, so reinterpret_cast is used
    // to treat the structure as a block of bytes
    // sizeof(s1) tells how many bytes to write
    outFile.write(reinterpret_cast<const char*>(&s1), sizeof(s1));

    // close the file so the data is saved before we read it back
    outFile.close();

    cout << "Record written to students.dat successfully.\n";

    // ---------- READING THE RECORD ----------

    // create another empty student variable to store the data read from the file
    Student s2{};

    // open the same file for reading in binary mode
    ifstream inFile("students.dat", ios::binary);

    // check if the file was opened properly
    if (!inFile.is_open()) {
        cerr << "Error: Unable to open students.dat for reading.\n";
        return 1;
    }

    // read() copies the bytes from the file directly into s2
    inFile.read(reinterpret_cast<char*>(&s2), sizeof(s2));

    // check if the read worked
    // it fails if the file has less data than expected
    if (!inFile) {
        cerr << "Error: Unable to read the record from students.dat.\n";
        inFile.close();  // close the file before exiting
        return 1;
    }

    // close the file because we are done reading from it
    inFile.close();

    // show the data that was read from the file
    cout << "----------------------------\n";
    cout << "Data read from the file:\n";
    cout << "Roll Number : " << s2.roll << '\n';
    cout << "Name        : " << s2.name << '\n';
    cout << "Marks       : " << s2.marks << '\n';

    // extra feature I added: show how many bytes one record takes in the file
    cout << "Size of one record: " << sizeof(Student) << " bytes\n";

    return 0;  // 0 means the program ran without any problem
}