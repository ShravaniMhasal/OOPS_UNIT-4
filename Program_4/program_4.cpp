#include <fstream>   // for reading and writing files (ifstream, ofstream)
#include <iostream>  // for console input/output (cout, cerr)
#include <string>    // for using the string type to store each line

using namespace std;  // so I don't have to write std:: every time

int main() {
    // open the original file for reading
    ifstream source("message.txt");

    // create (or overwrite) the new file that will hold the copy
    ofstream copy("message_copy.txt");

    // check if the original file opened properly
    // if it didn't, there is nothing to copy so we stop here
    if (!source.is_open()) {
        cerr << "Error: Unable to open message.txt for reading.\n";
        return 1;  // non-zero return means something went wrong
    }

    // check if the new file was created properly
    if (!copy.is_open()) {
        cerr << "Error: Unable to create message_copy.txt.\n";
        source.close();  // close the source file before exiting
        return 1;
    }

    // string variable to store one line at a time
    string text;

    int count = 0;  // counter I added to keep track of how many lines were copied

    // read the original file line by line
    // and write each line into the new file
    while (getline(source, text)) {
        copy << text << '\n';  // getline removes the newline, so I add it back
        count++;               // increase the line count
    }

    // close both files because we are done with them
    source.close();
    copy.close();

    // tell the user that the copy is finished
    cout << "File copied successfully to message_copy.txt\n";
    cout << "Total lines copied: " << count << "\n";

    return 0;  // 0 means the program ran without any problem
}