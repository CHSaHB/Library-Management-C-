#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
#include <iomanip>

using namespace std;

struct Book {
    int stock;
    string author;
    string publisher;
    string bookName;
    string issuedTo;
    int userID;
};

struct Admin {
    string name;
    int id;
    string bookIssued;
};

vector<Book> books;

void loadBooks();
void displayBooks();
void searchAndIssueBook(const string& username);
bool authenticate(const string& username, const string& password);
void saveUserData(const Admin& user, const string& filename);
void displayUserData(const string& filename);
void saveBookData(const Book& book, const string& filename);
void updateBooksFile(const vector<Book>& books, const string& filename);

// ANSI escape codes for colors
const string green = "\033[32m";
const string red = "\033[31m";
const string yellow = "\033[33m";
const string cyan = "\033[36m";
const string lightBlueBackground = "\033[104m";
const string reset = "\033[0m";

int main() {

    string username, password;
label1:

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (authenticate(username, password)) {
        cout << green << "Access granted." << reset << endl;

        int choice;
        cout << cyan << "Welcome to the Small Library" << reset << endl;
        string helloDetail[20] = {
            "                                                                                                           \n\n",
            " \t\t  W    W    W   EEEEEE  L         CCCCCC      OOOOO    MM      MM  EEEEEEEE         TTTTTTTTTTT    OOOOO        \n",
            " \t\t  W    W    W   E       L        C      C    O     O   MM      MM  E                     T        O     O       \n",
            " \t\t  W    W    W   E       L       C           O       O  M  M  M  M  E                     T       O       O      \n",
            " \t\t  W   W W   W   EEEEEE  L       C           O       O  M   MM   M  EEEEEEE               T       O       O      \n",
            " \t\t   W  W  W  W   E       L       C           O       O  M        M  E                     T       O       O      \n",
            " \t\t    W W  W W    E       L        C      C    O     O   M        M  E                     T        O     O       \n",
            " \t\t     W    W     EEEEEE  LLLLLLL   CCCCCC      OOOOO    M        M  EEEEEEEE              T         OOOOO        \n",
            "                                                                            \n",
            "                                                                            \n",
            "                                                                            \n \n",
            "     \t\t\t\t\t      L                  MMM       MMM           SSSSSSS              \n",
            "     \t\t\t\t\t      L                  MMM       MMM          S                     \n",
            "     \t\t\t\t\t      L                  M MM     MM M         S                      \n",
            "     \t\t\t\t\t      L                  M  MM   MM  M          S                     \n",
            "     \t\t\t\t\t      L                  M    MMM    M           SSSSSSS              \n",
            "     \t\t\t\t\t      L                  M     M     M                  S             \n",
            "     \t\t\t\t\t      L                  M           M                   S            \n",
            "     \t\t\t\t\t      L                  M           M                  S             \n",
            "     \t\t\t\t\t      LLLLLLLLL    ::    M           M    ::    SSSSSSSS              \n "
        };

        for (int i = 0; i < 20; ++i) {
            cout << helloDetail[i];
        }
        cout << " \n \n ";
        do {
            cout << "\n***************" << endl;
            cout << "Choose from the following options:" << endl;
            cout << yellow << "\n 1. Load Books\n 2. Display Books\n 3. Search and Issue Book\n 4. Display Issued Books\n 5. Exit\n" << reset;
            cout << "\n Enter your choice: ";
            cin >> choice;
            switch (choice) {
            case 1:
                loadBooks();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchAndIssueBook(username);
                break;
            case 4:
                displayUserData("user_data.txt");
                break;
            case 5:
                cout << cyan << "Thank you for using the Small Library system." << reset << endl;
                exit(0);
            default:
                cout << red << "Enter a valid choice!!" << reset << endl;
            }
        } while (true);
    }
    else {
        cout << red << "Invalid username or password. Access denied." << reset << endl;
        cout << red <<" Try Again " << reset << endl;
        goto label1;
    }

    return 0;
}

void loadBooks() {
    int select;
    do {
        Book book;
        cout << "\nEnter Book Name: ";
        cin.ignore(); // To ignore the newline character left in the buffer
        getline(cin, book.bookName);
        cout << "\nEnter Author Name: ";
        getline(cin, book.author);
        cout << "\nEnter Publisher Name: ";
        getline(cin, book.publisher);
        cout << "\nEnter Stock: ";
        cin >> book.stock;
        book.issuedTo = "";
        book.userID = books.size() + 1; // Assign a unique ID
        books.push_back(book);
        saveBookData(book, "books.txt"); // Save the book data to file
        cout << "_________________________" << endl;
        cout << yellow << " Do you want to load another book? " << reset << endl;
        cout << " Enter '1' for yes or '0' for no: ";
        cin >> select;
        cin.ignore(); // Clear the buffer before taking another input
    } while (select == 1);
}

void displayBooks() {
    ifstream inFile("books.txt");
    if (!inFile) {
        cout << red << "Error: Could not open the file." << reset << endl;
        return;
    }

    vector<Book> books;
    string line;
    while (getline(inFile, line)) {
        Book book;
        stringstream ss(line);
        getline(ss, book.bookName, ',');
        getline(ss, book.author, ',');
        getline(ss, book.publisher, ',');
        ss >> book.stock;
        ss.ignore();
        getline(ss, book.issuedTo, ',');
        ss >> book.userID;
        books.push_back(book);
    }
    inFile.close();

    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(20) << "Book Name" << " | "
        << setw(20) << "Author" << " | "
        << setw(20) << "Publisher" << " | "
        << setw(5) << "Stock" << " | "
        << setw(5) << "ID" << " |" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;

    for (const auto& book : books) {
        cout << "| " << left << setw(20) << book.bookName << " | "
            << setw(20) << book.author << " | "
            << setw(20) << book.publisher << " | "
            << setw(5) << book.stock << " | "
            << setw(5) << book.userID << " |" << endl;
    }

    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
}

void searchAndIssueBook(const string& username) {
    ifstream inFile("books.txt");
    if (!inFile) {
        cout << red << "Error: Could not open the file." << reset << endl;
        return;
    }

    vector<Book> books;
    string line;
    while (getline(inFile, line)) {
        Book book;
        stringstream ss(line);
        getline(ss, book.bookName, ',');
        getline(ss, book.author, ',');
        getline(ss, book.publisher, ',');
        ss >> book.stock;
        ss.ignore();
        getline(ss, book.issuedTo, ',');
        ss >> book.userID;
        books.push_back(book);
    }
    inFile.close();

    string bookName, authorName;
    string student;
    cout << "Enter name of the Book: ";
    cin.ignore(); // To ignore the newline character left in the buffer
    getline(cin, bookName);
    cout << "Enter name of the Author: ";
    getline(cin, authorName);

    for (auto& book : books) {
        if (bookName == book.bookName && authorName == book.author) {
            cout << green << "\nBook Present\n\n" << reset;
            cout << "\nName of the Book: " << book.bookName;
            cout << "\nAuthor of the Book: " << book.author;
            cout << "\nPublisher of the Book: " << book.publisher;
            cout << "\nStock Present: " << book.stock;
            cout << "\n-------------\n";
            cout << yellow << "Do you want to issue a copy of: " << book.bookName << " by " << book.author << " ? " << reset << endl;
            cout << "Press 1 for Yes\nPress 0 for No" << endl;
            int choice;
            cout << "Your choice: ";
            cin >> choice;
            if (choice == 1 && book.stock > 0) {
                book.stock--;
                cout << "Enter Student Name: ";
                cin.ignore(); // To ignore the newline character left in the buffer
                getline(cin, student);
                book.issuedTo = student; // Update the issuedTo field
                cout << green << "\nThe book \"" << book.bookName << "\" has been issued to: " << student << reset << endl;
                cout << "Please return the book before the due date." << endl;
                cout << "Remaining stock of the book \"" << book.bookName << "\": " << book.stock << endl;
                Admin user = { student, book.userID, book.bookName };
                saveUserData(user, "user_data.txt");
                updateBooksFile(books, "books.txt"); // Update the file with the new stock value
            }
            else if (book.stock <= 0) {
                cout << red << "Sorry, the book is out of stock." << reset << endl;
            }
            else {
                cout << yellow << "Thank you" << reset << endl;
            }
            return;
        }
    }
    cout << red << "Not Present!!" << reset << endl;
}

bool authenticate(const string& username, const string& password) {
    ifstream file("credentials.txt");
    if (!file) {
        cout << red << "Error: Could not open credentials file." << reset << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string storedUsername, storedPassword;

        if (getline(ss, storedUsername, ',') && getline(ss, storedPassword)) {
            if (username == storedUsername && password == storedPassword) {
                return true;
            }
        }
    }

    return false;
}

void saveUserData(const Admin& user, const string& filename) {
    ofstream outFile(filename, ios::app); // Open the file in append mode
    if (!outFile) {
        cout << red << "Error: Could not open the file." << reset << endl;
        return;
    }
    outFile << "Name: " << user.name << endl;
    outFile << "ID: " << user.id << endl;
    outFile << "Book Issued: " << user.bookIssued << endl;
    outFile << "-------------------------" << endl;
    outFile.close();
}

void displayUserData(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << red << "Error: Could not open the file." << reset << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();
}

void saveBookData(const Book& book, const string& filename) {
    ofstream outFile(filename, ios::app); // Open the file in append mode
    if (!outFile) {
        cout << red << "Error: Could not open the file." << reset << endl;
        return;
    }
    outFile << book.bookName << "," << book.author << "," << book.publisher << "," << book.stock << "," << book.issuedTo << "," << book.userID << endl;
    outFile.close();
}

void updateBooksFile(const vector<Book>& books, const string& filename) {
    ofstream outFile(filename, ios::trunc); // Open the file in truncate mode to overwrite existing content
    if (!outFile) {
        cout << red << "Error: Could not open the file." << reset << endl;
        return;
    }
    for (const auto& book : books) {
        outFile << book.bookName << "," << book.author << "," << book.publisher << "," << book.stock << "," << book.issuedTo << "," << book.userID << endl;
    }
    outFile.close();
}
