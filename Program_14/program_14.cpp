#include <cctype>    // for tolower(), isspace(), isalpha(), isdigit()
#include <fstream>   // for reading from files (ifstream)
#include <iostream>  // for console input/output (cin, cout, cerr)
#include <string>    // for using the string type to store the file name

// function to check if a character is a vowel
// it returns true for a, e, i, o, u (both capital and small letters)
bool isVowel(char ch) {
    // convert the character to lowercase first, so 'A' and 'a' are treated the same
    // static_cast<unsigned char> avoids problems with negative char values
    ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));

    // the character is a vowel if it matches any one of these five letters
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

int main() {
    // ask the user for the name of the file to analyse
    std::string fileName;
    std::cout << "Enter file name: ";
    std::getline(std::cin, fileName);  // getline is used in case the name has spaces

    // open the file the user entered for reading
    std::ifstream inputFile(fileName);

    // check if the file was opened properly
    // if not, show an error with the file name and stop the program
    if (!inputFile) {
        std::cerr << "Error: Could not open " << fileName << '\n';
        return 1;  // non-zero return means something went wrong
    }

    // counters for everything we want to count
    // size_t is used because counts can never be negative
    std::size_t lines = 0;       // number of lines
    std::size_t words = 0;       // number of words
    std::size_t characters = 0;  // total characters (spaces and newlines included)
    std::size_t vowels = 0;      // number of vowels
    std::size_t digits = 0;      // number of digits (0 to 9)
    std::size_t spaces = 0;      // number of space characters

    // tells us if we are currently in the middle of a word
    // it helps us count each word only once
    bool insideWord = false;

    char ch;  // stores one character at a time

    // get() reads a single character, even spaces and newlines
    // the loop stops when the end of the file is reached
    while (inputFile.get(ch)) {
        ++characters;  // every character read is counted

        // a newline character means one line has ended
        if (ch == '\n') {
            ++lines;
        }

        // isspace() is true for space, tab, newline etc.
        if (std::isspace(static_cast<unsigned char>(ch))) {
            // count only the normal space character separately
            if (ch == ' ') {
                ++spaces;
            }
            insideWord = false;  // we are outside a word now
        } else if (!insideWord) {
            // this is a normal character and the previous one was a space
            // so a new word has just started
            ++words;
            insideWord = true;
        }

        // check if the character is a letter and also a vowel
        if (std::isalpha(static_cast<unsigned char>(ch)) && isVowel(ch)) {
            ++vowels;
        }

        // check if the character is a digit
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            ++digits;
        }
    }

    // if the last line does not end with '\n', the loop above did not count it
    // so we check the last character of the file and fix the line count
    // (characters > 0 makes sure the file is not empty)
    if (characters > 0) {
        inputFile.clear();                // clear the end-of-file flag first
        inputFile.seekg(-1, std::ios::end);  // move to the last character of the file

        char lastCharacter;
        inputFile.get(lastCharacter);     // read that last character

        // if it is not a newline, the last line was not counted yet
        if (lastCharacter != '\n') {
            ++lines;
        }
    }

    // show all the results
    std::cout << "\nFile Statistics\n";
    std::cout << "Lines: " << lines << '\n';
    std::cout << "Words: " << words << '\n';
    std::cout << "Characters: " << characters << '\n';
    std::cout << "Vowels: " << vowels << '\n';
    std::cout << "Digits: " << digits << '\n';
    std::cout << "Spaces: " << spaces << '\n';

    return 0;  // 0 means the program ran without any problem
}