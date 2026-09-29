#include <cstring>   // for strncpy() to copy text into a char array
#include <fstream>   // for reading and writing files (ifstream, ofstream)
#include <iostream>  // for console input/output (cout, cerr, cin)

// structure to store the details of one student
// every record in the binary file has exactly this same size
struct StudentRecord {
    int rollNumber;  // roll number of the student
    char name[30];   // name stored as a char array (fixed size), because a
                     // std::string cannot be written to a binary file safely
    float marks;     // marks of the student
};

// this function creates one student record and writes it into the file
// the file is passed by reference (&) so the same open file is used every time
void addRecord(std::ofstream& file, int rollNumber, const char* name, float marks) {
    // create a record and set everything to 0 first (no garbage values)
    StudentRecord student{};

    // fill in the details
    student.rollNumber = rollNumber;

    // copy the name into the char array
    // sizeof - 1 leaves space for the '\0' at the end, so the name is always
    // safely terminated (because of the {} above, the remaining bytes are 0)
    std::strncpy(student.name, name, sizeof(student.name) - 1);

    student.marks = marks;

    // write() needs a const char* pointer, so reinterpret_cast is used
    // to treat the structure as a block of raw bytes
    // sizeof(student) tells how many bytes to write
    file.write(reinterpret_cast<const char*>(&student), sizeof(student));
}

int main() {
    // ---------- WRITING THE RECORDS ----------

    // this extra { } block is used so that outputFile is closed automatically
    // when the block ends (the file gets saved before we read it below)
    {
        // ios::binary -> write raw bytes instead of text
        // ios::trunc  -> erase the old content of the file if it already exists
        std::ofstream outputFile("records.dat", std::ios::binary | std::ios::trunc);

        // check if the file was created properly
        // if not, show an error and stop the program
        if (!outputFile) {
            std::cerr << "Error: Could not create records.dat\n";
            return 1;  // non-zero return means something went wrong
        }

        // write 3 student records one after another
        // each record takes sizeof(StudentRecord) bytes in the file
        addRecord(outputFile, 101, "Amit", 85.5F);
        addRecord(outputFile, 102, "Neha", 91.0F);
        addRecord(outputFile, 103, "Ravi", 78.0F);
    }  // outputFile is closed here automatically

    // ---------- READING ONE RECORD (RANDOM ACCESS) ----------

    // open the same file for reading in binary mode
    std::ifstream inputFile("records.dat", std::ios::binary);

    // check if the file was opened properly
    if (!inputFile) {
        std::cerr << "Error: Could not open records.dat\n";
        return 1;
    }

    // ask the user which record they want to see
    int recordNumber;
    std::cout << "Enter record number to read (1 to 3): ";
    std::cin >> recordNumber;

    // validation: only 3 records are present in the file
    // so any number outside 1 to 3 is invalid
    if (recordNumber < 1 || recordNumber > 3) {
        std::cerr << "Invalid record number.\n";
        return 1;
    }

    // calculate how many bytes we need to skip to reach the required record
    // all records have the same size, so:
    // offset = (record number - 1) * size of one record
    // example: record 2 -> skip 1 record, record 3 -> skip 2 records
    // static_cast<std::streamoff> is used because seekg() works with streamoff
    const std::streamoff offset = static_cast<std::streamoff>(recordNumber - 1) *
                                  static_cast<std::streamoff>(sizeof(StudentRecord));

    // seekg() moves the read pointer directly to that position
    // ios::beg means the offset is counted from the beginning of the file
    // this way we don't have to read the earlier records at all
    inputFile.seekg(offset, std::ios::beg);

    // create an empty record to store the data read from the file
    StudentRecord selectedStudent{};

    // read() copies the bytes from the file directly into the structure
    inputFile.read(reinterpret_cast<char*>(&selectedStudent), sizeof(selectedStudent));

    // check if the read worked
    // it fails if the file has less data than expected
    if (!inputFile) {
        std::cerr << "Error: Could not read selected record.\n";
        return 1;
    }

    // show the record that was read from the file
    std::cout << "Roll Number: " << selectedStudent.rollNumber << '\n';
    std::cout << "Name: " << selectedStudent.name << '\n';
    std::cout << "Marks: " << selectedStudent.marks << '\n';

    return 0;  // 0 means the program ran without any problem
}