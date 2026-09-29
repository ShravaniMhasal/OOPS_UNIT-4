#include <cctype>    // for isspace() to check for spaces, tabs and newlines
#include <fstream>   // for reading from files (ifstream)
#include <iostream>  // for console input/output (cout, cerr)
#include <string>    // included for string support (not strictly needed here)

using namespace std;  // so I don't have to write std:: every time

int main() {
    // open "message.txt" for reading
    ifstream file("message.txt");

    // check if the file was opened properly
    // if not, show an error and stop the program
    if (!file.is_open()) {
        cerr << "Error: Unable to open message.txt for reading.\n";
        return 1;  // non-zero return means something went wrong
    }

    // counters for the things we want to count
    size_t lines = 0;   // number of lines
    size_t words = 0;   // number of words
    size_t chars = 0;   // number of characters (spaces and newlines are included)

    // this tells us if we are currently in the middle of a word
    // it helps to count each word only once
    bool inWord = false;

    char c;  // stores one character at a time

    // get() reads a single character (even spaces and newlines)
    // the loop stops when the end of the file is reached
    while (file.get(c)) {
        chars++;  // every character read is counted

        // a newline character means one line has ended
        if (c == '\n') {
            lines++;
        }

        // check if the character is a space, tab or newline
        // (static_cast<unsigned char> is used to avoid problems with isspace)
        if (isspace(static_cast<unsigned char>(c))) {
            inWord = false;  // we are outside a word now
        }
        else if (!inWord) {
            // this is a normal character and the previous one was a space
            // so a new word has just started
            words++;
            inWord = true;
        }
    }

    // if the last line does not end with '\n', the loop above did not count it
    // so we check the last character of the file and fix the line count
    if (chars > 0) {
        file.clear();                  // clear the end-of-file flag first
        file.seekg(-1, ios::end);      // move to the last character of the file

        char last;
        file.get(last);                // read that last character

        if (last != '\n') {
            lines++;                   // count the last line as well
        }
    }

    // close the file because we are done reading from it
    file.close();

    // show the results
    cout << "File Statistics\n";
    cout << "Total lines      : " << lines << '\n';
    cout << "Total words      : " << words << '\n';
    cout << "Total characters : " << chars << '\n';

    // extra feature I added: average number of words in each line
    // (checked lines > 0 so we don't divide by zero)
    if (lines > 0) {
        cout << "Average words per line: " << (double)words / lines << '\n';
    }

    return 0;  // 0 means the program ran without any problem
}