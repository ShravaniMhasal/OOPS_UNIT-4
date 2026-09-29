# OOPS_UNIT-4
Name: Shravani Mhasal
<br>
Division: B
<br>
Class: SY BTech
<br>
Branch: AI & Data Science
<br>
ZPRN: 125UAD1008
<br>
Roll Number: AD2233
<br>
Course Name: Object Oriented Programming with C++
<br>
<br>
List of UNIT 4 programs: 
<br>
1) Program 1:
<br> 
Aim: To create a text file and write data into it using std::ofstream.
<br>
2) Program 2: 
<br>
Aim: To read and display the content of a text file using std::ifstream.
<br>
3) Program 3:
<br>
Aim: To add new content at the end of an existing file.
<br>
4) Program 4:
<br>
Aim: To copy the content of one text file into another text file.
<br>
5) Program 5:
<br>
Aim: To count lines, words, and characters in a text file.
<br>
6) Program 6:
<br>
Aim: To search for a word and count its occurrences in a text file.
<br>
7) Program 7:
<br>
Aim: To write student records into a text file using a simple delimiter format.
<br>
8) Program 8:
<br>
Aim: To read delimiter-separated student records and search by roll number.
<br>
9) Program 9:
<br>
Aim: To update a file record safely using a temporary file.
<br>
10) Program 10:
<br>
Aim: To use file pointers for finding positions and navigating in a file.
<br>
11) Program 11:
<br>
Aim: To write and read fixed-size records in a binary file.
<br>
12) Program 12:
<br>
Aim: To access a selected fixed-size record directly from a binary file.
<br>
13) Program 13:
<br>
Aim: To check and report file errors using stream-state functions.
<br>
14) Program 14:
<br>
Aim: To create a file-analysis program that counts lines, words, characters, vowels, digits, and spaces.
<br>
15) Program 15:
<br>
Aim: To create a simple file-based student record manager using text files.
<br>
16) Program 16:
<br>
Aim: To implement a simple object-oriented library record application using file storage.
<br>
<br>
Brief description:
<br>
Program 1: Writing Data to a File
<br>
This program creates a text file called message.txt using an ofstream object and writes several lines into it. It first checks whether the file opened properly, then writes the text with the << operator, the same way cout works. It closes the file so the data is saved and prints a success message. It shows the basics of file output and that files store data permanently.
<br>
<br>
Program 2: Reading Data from a File
<br>
This program opens message.txt with an ifstream object and displays its contents on the screen. It uses getline() inside a while loop to read one line at a time until the file ends, and it prints each line with a line number. It shows how to read a text file line by line and stop safely at the end of the file.
<br>
<br>
Program 3: Appending Data to a File
<br>
This program opens message.txt in append mode using ios::app, so the old content stays and the new lines are added at the end. Without this mode, opening the file with ofstream would erase everything already in it. It shows the difference between overwriting and appending.
<br>
<br>
Program 4: Copying One File into Another
<br>
This program reads message.txt line by line and writes every line into a new file, message_copy.txt. It uses an ifstream for the source and an ofstream for the destination at the same time. It checks that both files opened correctly before copying. It shows how to work with two files at once and how file copying works.
<br>
<br>
Program 5: Counting Lines, Words and Characters
<br>
This program reads message.txt character by character using get() and counts the total lines, words and characters. A bool variable tracks whether the program is inside a word, so each word is counted once. It also checks the last character of the file, so the final line is counted even if it has no newline. It combines character handling, isspace() and file position control.
<br>
<br>
Program 6: Searching for a Word in a File
<br>
The user enters a word, and the program counts how many times it appears in message.txt. It reads the file word by word using the >> operator and compares each word with the one entered. The search is case sensitive. It shows how to combine keyboard input with file reading.
<br>
<br>
Program 7: Saving Student Records to a File
<br>
This program takes a student's roll number, name and marks from the user and saves them as one line in students.txt, separated by the | symbol. It opens the file in append mode so earlier records are kept. It uses cin.ignore() before getline() so the name is read correctly. It shows how to store structured data in a text file.
<br>
<br>
Program 8: Updating a Student's Marks
<br>
This program changes the marks of one student in students.txt. Since a text file cannot easily be edited in the middle, it copies all records into a temporary file and replaces only the matching record. Then it deletes the old file with remove() and renames the temporary file to the original name with rename(). A stringstream splits each line into roll number, name and marks. It shows the standard way to update data in a text file.
<br>
<br>
Program 9: Searching a Student by Roll Number
<br>
This program asks for a roll number and looks for that student in students.txt. It splits every line at the | symbol with a stringstream, converts the roll number using stoi() and compares it with the input. If a match is found, it displays the details and stops the loop using break. Otherwise it prints a "not found" message. It shows searching through stored records.
<br>
<br>
Program 10: File Navigation Using Position Pointers
<br>
This program uses an fstream object, which can read and write the same file. It writes letters into the file and then moves the pointers using seekg() and seekp(), while tellg() and tellp() report the current positions. It also uses ios::beg and ios::end to move relative to the start or end of the file. It shows that a file has separate read (get) and write (put) pointers that can be moved freely.
<br>
<br>
Program 11: Writing and Reading a Binary File
<br>
This program stores a student struct (roll number, name and marks) in students.dat as raw bytes, using the ios::binary mode. It writes the structure with write() and reads it back into another structure with read(). reinterpret_cast converts the structure pointer into a char*. The name is stored as a char array because a std::string cannot be written to a binary file safely. It shows how binary files differ from text files.
<br>
<br>
Program 12: Random Access in a Binary File
<br>
This program writes three student records into records.dat using a function called addRecord(). The user then enters a record number, and the program jumps directly to that record. Because every record has the same size, the position is calculated as (record number - 1) × size of one record and seekg() moves the pointer there. The earlier records don't need to be read. It shows the main advantage of fixed-size binary records.
<br>
<br>
Program 13: File Error Handling
<br>
This program tries to open a file that does not exist and shows how to handle the failure. It uses is_open() to detect the problem and prints an error message using cerr. It also shows how the stream state functions eof(), bad() and fail() tell the reason a read loop ended. It shows why error checking is important in file programs.
<br>
<br>
Program 14: Detailed File Statistics
<br>
This program asks the user for a file name and analyses that file. It counts lines, words, characters, vowels, digits and spaces while reading one character at a time. A separate function, isVowel(), converts the character to lowercase and checks it against the five vowels. It builds on Program 5 with more counters and a user-supplied file name.
<br>
<br>
Program 15: Student Record Manager (Menu-Driven)
<br>
This is a complete program that manages student records in student_records.txt through a menu. The user can add a student, display all students, search by roll number, or update marks, and the menu repeats until the user chooses 0. Each feature is its own function, and the menu uses a do-while loop with a switch statement. It combines everything from Programs 7, 8 and 9 into one application.
<br>
<br>
Program 16: Library Record System Using a Class
<br>
This program manages a library's books in library_books.txt using object-oriented programming. A Book class holds the book ID, title, author and issued status as private data, with a constructor, a display() function and a toFileRecord() function that converts the object into a line for the file. The user can add books or display all saved books through a menu. When displaying, each line is split, converted back into a Book object and shown with its status ("Issued" or "Available"). It combines classes, encapsulation, file handling and menu-driven design in one project.
<br>
