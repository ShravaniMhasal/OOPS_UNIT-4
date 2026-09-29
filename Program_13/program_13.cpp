#include <fstream>   // for reading from files (ifstream)
#include <iostream>  // for console input/output (cout, cerr)
#include <string>    // for using the string type to store each line

int main() {
    // try to open a file that does not exist
    // this is done on purpose to show how error handling works
    std::ifstream inputFile("missing_file.txt");

    // is_open() returns false if the file could not be opened
    // (here it fails because missing_file.txt is not present in the folder)
    if (!inputFile.is_open()) {
        // cerr is used for error messages
        std::cerr << "Error: File could not be opened.\n";
        std::cerr << "Check whether missing_file.txt exists in the current folder.\n";
        return 1;  // non-zero return means the program ended with an error
    }

    // string variable to store one line of the file at a time
    std::string line;

    // getline reads one full line each time the loop runs
    // the loop stops when there are no more lines or when a read fails
    while (std::getline(inputFile, line)) {
        std::cout << line << '\n';  // print the line on the screen
    }

    // after the loop ends, we check WHY it ended using the stream state flags

    // eof() is true when the end of the file was reached
    // this is the normal and expected reason for the loop to stop
    if (inputFile.eof()) {
        std::cout << "End of file reached normally.\n";
    }
    // bad() is true when a serious error happened
    // (for example a hardware problem or the stream got corrupted)
    else if (inputFile.bad()) {
        std::cerr << "A serious file I/O error occurred.\n";
    }
    // fail() is true when a read operation failed for a logical reason
    // (for example the data was not in the expected format)
    else if (inputFile.fail()) {
        std::cerr << "A logical file read error occurred.\n";
    }

    return 0;  // 0 means the program ran without any problem
}