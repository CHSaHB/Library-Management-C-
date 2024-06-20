#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <Windows.h>
#include <ctime>

using namespace std;

struct Book {
    int stock;
    string author;
    string publisher;
    string bookName;
    string issuedTo;
    int userID;
};

struct Student {
    string name;
    int id;
    string bookIssued;
    int date;
};

vector<Book> books;

void loadBooks();
void displayBooks();
void searchAndIssueBook(const string& username);
bool authenticate(const string& username, const string& password);
void saveUserData(const Student& user, const string& filename);
void displayUserData(const string& filename);
void saveBookData(const Book& book, const string& filename);
void updateBooksFile(const vector<Book>& books, const string& filename);
void SetColor(int textColor);

const string green = "\033[32m";
const string red = "\033[31m";
const string yellow = "\033[33m";
const string cyan = "\033[36m";
const string blue = "\033[34m";
const string navy = "\033[38;5;48m";
const string orange = "\033[38;5;214m";
const string reset = "\033[0m";

void SetColor(int textColor) {
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, textColor);
}

void welcomeMessage() {
    SetColor(14);
    string helloDetail[20] = {
        "                                                                                                           \n\n",
        " \t\t  W    W    W   EEEEEE  L         CCCCCC      OOOOO    MM      MM  EEEEEEEE         TTTTTTTTTTT    OOOOO        \n",
        " \t\t  W    W    W   E       L        C      C    O     O   MM      MM  E                     T        O     O       \n",
        " \t\t  W    W    W   E       L       C           O       O  M  M  M  M  E                     T       O       O      \n",
        " \t\t  W   WIW   W   EEEEEE  L       C           O       O  M   MM   M  EEEEEEE               T       O       O      \n",
        " \t\t   W  WWW   W   E       L       C           O       O  M        M  E                     T       O       O      \n",
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
        "     \t\t\t\t\t      LLLLLLLLLL   ::    M           M    ::    SSSSSSSS              \n "
    };

    for (const auto& line : helloDetail) {
        cout << line;
    }
    cout << " \n \n ";
}

int main() {
    string username, password;
    srand(time(0));
    while (true) {
        cout << navy << "\n\n \t\tYou need to login to Access This Project !!! " << endl;
        cout << " \n\t\t Dear Admin! " << reset;
        cout << cyan << "\n \n \t\t\t  Enter Your Username: ";
        cin >> username;
        cout << "\n \n \t\t \t   Enter password: " << reset;
        cin >> password;

        if (authenticate(username, password)) {
            cout << green << "Access granted." << reset << endl;
            system("CLS");

            welcomeMessage();

            while (true) {
                int choice;
                cout << cyan << endl;
                cout << "\n\t\t\t\t\t*************************************" << endl;
                cout << "\t\t\t\t\tChoose from the following options:" << endl;
                cout << yellow << " \n\t\t\t\t\t 1. Load Books \n\t\t\t\t\t 2. Display Books ";
                cout << " \n\t\t\t\t\t 3. Search and Issue Book \n\t\t\t\t\t 4. Display Issued Books \n\t\t\t\t\t 5. Exit\n\t\t\t" << reset;
                cout << "\n\t\t\t\t\t*************************************" << endl;
                cout << "\n\t\t\t\t\t Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                    system("CLS");
                    loadBooks();
                    break;
                case 2:
                    system("CLS");
                    displayBooks();
                    break;
                case 3:
                    system("CLS");
                    searchAndIssueBook(username);
                    break;
                case 4:
                    system("CLS");
                    displayUserData("student_data.txt");
                    break;
                case 5:
                    cout << cyan << "Thank You for using the Small Library system." << reset << endl;
                    return 0;
                default:
                    cout << red << "Enter a Valid Choice!!" << reset << endl;
                }
            }
        }
        else
        {
            cout << red << "Invalid Username or Password. " << endl;
            cout << " Access Denied " << endl;
            cout << " Try Again " << reset << endl;
        }
    }

    return 0;
}

void loadBooks() {
    char select;
    do {
        cout << green << "\n \t\t\t\t **************************************" << endl;
        cout << "\t\t\t\t LOAD BOOK " << endl;
        Book book;
        cout << "\n\t\t\t\t Enter Book Name: ";
        cin.ignore();
        getline(cin, book.bookName);
        cout << "\n\t\t\t\t Enter Author Name: ";
        getline(cin, book.author);
        cout << "\n\t\t\t\t Enter Publisher Name: ";
        getline(cin, book.publisher);
        cout << "\n\t\t\t\t Enter Stock(Integers only) : ";
            cin >> book.stock;
        books.push_back(book);
        saveBookData(book, "books.txt");
        cout << "\t\t\t\t_____________________________________________" << endl;
        cout << "\t\t\t\t_____________________________________________" << endl;
        cout << yellow << "\t\t\t\t Do you want to load another book? " << reset << endl;
        cout << "\t\t\t\t Enter 'y' for Yes or 'n' for No: ";
        cin >> select;
        cin.ignore(); 
    } while (select == 'y');
}

void displayBooks()
{
    ifstream inFile("books.txt");
    if (!inFile)
    {
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

    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(20) << "Book Name" << " | "
        << setw(20) << "Author" << " | "
        << setw(20) << "Publisher" << " | "
        << setw(5) << "Stock" << " | "
        << endl;
    cout << "---------------------------------------------------------------------------------" << endl;

    for (const auto& book : books) {
        cout << "| " << left << setw(20) << book.bookName << " | "
            << setw(20) << book.author << " | "
            << setw(20) << book.publisher << " | "
            << setw(10) << book.stock << " | "
            << endl;
    }

    cout << "---------------------------------------------------------------------------------" << endl;
}

void searchAndIssueBook(const string& username) {
    string bookName, author;
    cout << yellow << "\n\n\t\t\t\t\tEnter Name of the Book you want to Search and Issue: " << reset;
    cin.ignore();
    getline(cin, bookName);
    cout << yellow << "\n\t\t\t\t\tEnter Book Author's Name: " << reset;
    getline(cin, author);

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

    for (auto& book : books) {
        if (book.bookName == bookName && book.author == author) {
            if (book.stock > 0) {
                cout << green << "\nBook found and available in Stock." << reset << endl;
                cout << cyan << "\n Do you want to Issue Book \"" << bookName << "\" by " << author << " ?" << reset << endl;
                cout << cyan << "\n Press \" y\"  for Yes, \" n \" for No: " << reset;
                char choice;
                cin >> choice;
                if (choice == 'y') {
                    book.stock--;
                    string student;
                    int student_id;
                    cout << " =============================" << endl;
                    cout << blue << "\n Enter Student name you want to issue book: "<< reset;
                    cin.ignore(); 
                    getline(cin, student);
                    book.issuedTo = student;
                    cout << blue << "\n Enter Student id: " << reset;
                    cin >> student_id;
                    Student info;
                    info.name = student;
                    info.id = student_id;
                    info.bookIssued = bookName;
                    info.date = rand() % 30 + 1;
                    saveUserData(info, "student_data.txt");
                    updateBooksFile(books, "books.txt");
                    cout << green << "\nBook issued successfully!" << reset << endl;
                }
                else {
                    cout << red << "\nBook not issued." << reset << endl;
                }
                return;
            }
            else {
                cout << red << "\nBook found but out of stock." << reset << endl;
                return;
            }
        }
    }
    cout << red << "\nBook not found." << reset << endl;
}

bool authenticate(const string& username, const string& password) {
    ifstream inFile("credentials.txt");
    if (!inFile) {
        cout << red << "Error: Could not open the credentials file." << reset << endl;
        return false;
    }

        string line, storedUsername, storedPassword;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        getline(ss, storedUsername, ',');
        getline(ss, storedPassword, ',');
        if (username == storedUsername && password == storedPassword) {
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}

void saveUserData(const Student& user, const string& filename) {
    ofstream outFile(filename, ios::app);
    if (!outFile) {
        cout << red << "Error: Could not open the file to save user data." << reset << endl;
        return;
    }
        outFile << user.name << ',' << user.id << ',' << user.bookIssued << ','<< user.date << endl;
    outFile.close();
}

void displayUserData(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << red << "Error: Could not open the user data file." << reset << endl;
        return;
    }

        string line;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(20) << "Issued Book Name" << " | "
        << setw(13) << " Student_ID" << " | "
        << setw(20) << "Student Name" << " |" << setw(7) << " Date"<< endl;
    cout << "----------------------------------------------------------------------------" << endl;

    while (getline(inFile, line)) {
        stringstream ss(line);
        Student info;
        getline(ss, info.name, ',');
        ss >> info.id;
        ss.ignore();
        getline(ss, info.bookIssued, ',');
        ss >> info.date;
        cout << "| " << left << setw(20) << info.bookIssued << " | "
            << setw(13) << info.id << " | "
            << setw(20) << info.name << " |" << info.date <<" , 6, 2024  " << " |"<< endl;
    }
    cout << "----------------------------------------------------------------------------" << endl;
    inFile.close();
}

void saveBookData(const Book& book, const string& filename) {
    ofstream outFile(filename, ios::app);
    if (!outFile) {
        cout << red << "Error: Could not open the file to save book data." << reset << endl;
        return;
    }

        outFile << book.bookName << ',' << book.author << ',' << book.publisher << ','
        << book.stock << ',' << book.issuedTo << ',' << book.userID << endl;
    outFile.close();
}

void updateBooksFile(const vector<Book>& books, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << red << "Error: Could not open the file to update book data." << reset << endl;
        return;
    }

        for (const auto& book : books) {
            outFile << book.bookName << ',' << book.author << ',' << book.publisher << ','
                << book.stock << ',' << book.issuedTo << ',' << book.userID << endl;
        }
    outFile.close();
}

