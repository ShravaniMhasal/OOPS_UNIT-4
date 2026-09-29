#include <fstream>   // for file input/output (ofstream)
#include <iostream>  // for console input/output (cout, cerr)

int main() {
    // open "message.txt" in append mode using std::ios::app
    // append mode means the old data stays and new data is added at the end
    // (without ios::app the old content would be erased)
    std::ofstream file("message.txt", std::ios::app);

    // check if the file was opened properly
    // if not, show an error and stop the program
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open message.txt for appending.\n";
        return 1;  // non-zero return means something went wrong
    }

    // add new lines at the end of the file
    file << "This line was added using append mode.\n";
    file << "Append mode does not delete the old content.\n";  // extra line I added

    // close the file so the changes are saved properly
    file.close();

    // tell the user that the lines were added
    std::cout << "New lines were appended to message.txt successfully.\n";

    return 0;  // 0 means the program ran without any problem
}