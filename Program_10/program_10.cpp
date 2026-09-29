#include <fstream>   // for reading and writing the same file (fstream)
#include <iostream>  // for console input/output (cout, cerr)
#include <string>    // included for string support (not strictly needed here)

using namespace std;  // so I don't have to write std:: every time

int main() {
    // fstream can read AND write the same file
    // ios::in  -> allows reading
    // ios::out -> allows writing
    // ios::trunc -> erases the old content when the file is opened
    fstream file("navigation.txt", ios::in | ios::out | ios::trunc);

    // check if the file was opened properly
    // if not, show an error and stop the program
    if (!file.is_open()) {
        cerr << "Error: Unable to open navigation.txt.\n";
        return 1;  // non-zero return means something went wrong
    }

    // write some letters into the file
    file << "ABCDEF";

    // tellp() tells the current position of the "put" (write) pointer
    // after writing 6 characters it should be 6
    cout << "Write position after writing: " << file.tellp() << '\n';

    // flush() pushes the data from the buffer into the file
    // so that it is really saved before we start reading
    file.flush();

    // seekg() moves the "get" (read) pointer
    // ios::beg means we count the position from the beginning of the file
    file.seekg(0, ios::beg);

    // read the first character of the file
    char first;
    file.get(first);
    cout << "First character: " << first << '\n';

    // tellg() tells the current position of the read pointer
    // it moved forward by one because we read one character
    cout << "Read position after reading one character: " << file.tellg() << '\n';

    // move the read pointer to position 2 (positions start from 0)
    // so 0 = A, 1 = B, 2 = C
    file.seekg(2, ios::beg);

    // read the character present at position 2
    char third;
    file.get(third);
    cout << "Character at position 2: " << third << '\n';

    // extra feature I added: move to the last character using ios::end
    // -1 means one step back from the end of the file
    file.seekg(-1, ios::end);
    char last;
    file.get(last);
    cout << "Last character: " << last << '\n';

    // clear() removes any error flags (like end-of-file)
    // this is important because reading the last character can set the eof flag
    // and the write below would fail if the flag stays on
    file.clear();

    // seekp() moves the "put" (write) pointer
    // position 6 is the end of the file (after F), so "G" gets added at the end
    file.seekp(6, ios::beg);
    file << "G";

    // close the file so the changes are saved properly
    file.close();

    // tell the user that the program is finished
    cout << "----------------------------\n";
    cout << "File navigation completed. Please check navigation.txt\n";

    return 0;  // 0 means the program ran without any problem
}