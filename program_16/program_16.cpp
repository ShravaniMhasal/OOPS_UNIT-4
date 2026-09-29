#include <fstream>   // for reading and writing files (ifstream, ofstream)
#include <iostream>  // for console input/output (cin, cout, cerr)
#include <limits>    // for numeric_limits (used to clear leftover input)
#include <sstream>   // for stringstream (to split a line into parts)
#include <string>    // for using the string type
#include <utility>   // for move() used in the constructor

using namespace std;  // so I don't have to write std:: every time

// class to store the details of one book
// data members are private, so they can only be used through the class functions
class Book {
private:
    int id;          // unique id of the book
    string title;    // title of the book
    string author;   // author of the book
    bool issued;     // true if the book is issued, false if it is available

public:
    // constructor: runs when a Book object is created and sets the values
    // issued has a default value of false, so a new book is "Available" by default
    // move() avoids making an extra copy of the strings
    Book(int bookId, string bookTitle, string bookAuthor, bool status = false)
        : id(bookId), title(move(bookTitle)), author(move(bookAuthor)), issued(status) {}

    // getter function to get the book id (const because it does not change anything)
    int getId() const {
        return id;
    }

    // converts the book details into one line of text so it can be saved in the file
    // format: id|title|author|issued (1 means issued, 0 means available)
    string toFileRecord() const {
        return to_string(id) + "|" + title + "|" + author + "|" + (issued ? "1" : "0");
    }

    // prints the details of the book on the screen
    void display() const {
        cout << "Book ID : " << id << '\n';
        cout << "Title   : " << title << '\n';
        cout << "Author  : " << author << '\n';
        // ternary operator: prints "Issued" if issued is true, otherwise "Available"
        cout << "Status  : " << (issued ? "Issued" : "Available") << '\n';
    }
};

// ---------- FUNCTION 1: ADD A NEW BOOK ----------
// takes the book details from the user and saves them at the end of the file
void addBook() {
    int id;
    string title;
    string author;

    cout << "Enter book ID: ";
    cin >> id;

    // cin >> leaves the newline (Enter key) in the input buffer
    // if we don't remove it, getline will read an empty line and skip the title
    // so ignore() throws away everything up to and including the newline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // getline is used because title and author can have spaces
    cout << "Enter book title: ";
    getline(cin, title);

    cout << "Enter author name: ";
    getline(cin, author);

    // create a Book object with the details (it is "Available" by default)
    Book book(id, title, author);

    // ios::app -> append mode, so the old books are not deleted
    ofstream file("library_books.txt", ios::app);

    // check if the file was opened properly
    // if not, show an error and go back to the menu
    if (!file.is_open()) {
        cerr << "Error: Unable to open library_books.txt for writing.\n";
        return;  // return is used here because the function is void
    }

    // write the book as one line in the file
    file << book.toFileRecord() << '\n';

    // close the file so the data is saved properly
    file.close();

    cout << "Book \"" << title << "\" was added successfully.\n";
}

// ---------- FUNCTION 2: DISPLAY ALL BOOKS ----------
// reads the file and shows every book that is saved in it
void displayBooks() {
    // open the file for reading
    ifstream file("library_books.txt");

    // if the file does not exist yet, there are no books to show
    if (!file.is_open()) {
        cout << "No library record file found.\n";
        return;
    }

    string line;      // stores one full line (one book record)
    int count = 0;    // counter I added to count how many books were displayed

    // read the file line by line
    while (getline(file, line)) {
        // stringstream lets us split the line at every '|' character
        stringstream ss(line);

        string idText;      // book id as text
        string title;       // title of the book
        string author;      // author of the book
        string issuedText;  // "1" or "0" as text

        // split the record into 4 parts: id | title | author | issued
        // the inside code only runs if all 4 parts were read properly
        // (this also skips empty or damaged lines)
        if (getline(ss, idText, '|') &&
            getline(ss, title, '|') &&
            getline(ss, author, '|') &&
            getline(ss, issuedText)) {

            // stoi converts the id from text to an integer
            // issuedText == "1" gives true if the book is issued, otherwise false
            Book book(stoi(idText), title, author, issuedText == "1");

            book.display();  // show the details of this book
            cout << "-------------------------\n";
            count++;         // one more book was displayed
        }
    }

    // close the file because we are done reading from it
    file.close();

    // show the total, or a message if the file had no valid records
    if (count == 0) {
        cout << "No books found in the file.\n";
    }
    else {
        cout << "Total books: " << count << '\n';
    }
}

// ---------- MAIN FUNCTION: MENU ----------
int main() {
    int choice;  // stores the menu option chosen by the user

    // do-while is used so the menu is shown at least once
    // and keeps repeating until the user enters 0
    do {
        // show the menu
        cout << "\n===== Library Record System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // switch calls the function that matches the user's choice
        // break is needed after each case so the next case does not run too
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 0:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                // runs when the number is not one of the options above
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);  // repeat the menu until the user chooses Exit

    return 0;  // 0 means the program ran without any problem
}