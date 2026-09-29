#include <fstream>   // for file input/output (ofstream)
#include <iostream>  // for console input/output (cout, cerr)

int main() {
    // create an output file stream object and open (or create) "message.txt"
    std::ofstream file("message.txt");

    // check if the file was opened properly
    // if it failed, show an error and stop the program
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open message.txt for writing.\n";
        return 1;  // non-zero return means the program ended with an error
    }

    // write some lines into the file using the << operator (same as cout)
    file << "Welcome to C++ File Handling\n";
    file << "This is the first line written to a file.\n";
    file << "Files store data permanently.\n";
    file << "I wrote this file using my own C++ program.\n";  // extra line I added

    // close the file so all the data is saved properly
    file.close();

    // tell the user that everything worked
    std::cout << "Data was written successfully to message.txt\n";

    return 0;  // 0 means the program ran without any problem
}