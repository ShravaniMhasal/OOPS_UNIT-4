#include <fstream>   // for reading from files (ifstream)
#include <iostream>  // for console input/output (cout, cerr)
#include <string>    // for using the string type to store each line

int main() {
    // create an input file stream object and try to open "message.txt"
    std::ifstream file("message.txt");

    // check if the file was opened properly
    // if not, show an error and stop the program
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open message.txt for reading.\n";
        return 1;  // non-zero return means something went wrong
    }

    // string variable to store one line of the file at a time
    std::string text;

    std::cout << "Reading the file now...\n";
    std::cout << "----------------------\n";

    int lineNumber = 1;  // counter I added to number each line

    // getline reads one full line from the file each time the loop runs
    // the loop stops automatically when there are no more lines left
    while (std::getline(file, text)) {
        // print the line number followed by the line itself
        std::cout << lineNumber << ": " << text << '\n';
        lineNumber++;  // move to the next line number
    }

    // close the file because we are done reading from it
    file.close();

    std::cout << "----------------------\n";
    std::cout << "Finished reading " << lineNumber - 1 << " lines.\n";

    return 0;  // 0 means the program ran successfully
}