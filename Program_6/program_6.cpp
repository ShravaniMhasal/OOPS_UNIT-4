#include <fstream>   // for reading from files (ifstream)
#include <iostream>  // for console input/output (cin, cout, cerr)
#include <string>    // for using the string type to store words

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

    // ask the user which word they want to look for
    string target;
    cout << "Enter the word you want to search: ";
    cin >> target;

    string word;         // stores one word from the file at a time
    int count = 0;       // counts how many times the target word is found
    int totalWords = 0;  // counter I added to count all the words in the file

    // the >> operator reads one word at a time (it skips spaces and newlines)
    // the loop stops when there are no more words in the file
    while (file >> word) {
        totalWords++;  // every word read is counted

        // compare the word from the file with the word typed by the user
        // note: this comparison is case sensitive, so "File" and "file" are different
        if (word == target) {
            count++;  // found a match, so increase the counter
        }
    }

    // close the file because we are done reading from it
    file.close();

    // show the results
    cout << "----- Search Result -----\n";
    cout << "The word '" << target << "' was found " << count << " time(s).\n";
    cout << "Total words in the file: " << totalWords << '\n';

    // extra message I added to make the output more helpful
    if (count == 0) {
        cout << "Sorry, that word is not present in the file.\n";
    }

    return 0;  // 0 means the program ran without any problem
}