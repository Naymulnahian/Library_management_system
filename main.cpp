#include <bits/stdc++.h>
using namespace std;

class Book {
public:
    string BookID;
    string Title;
    string Author;
    bool isAvailable;
    Book(string id, string t, string a) {
        BookID = id;
        Title = t;
        Author = a;
        isAvailable = true;
    }
};

class Borrower {
public:
    string BorrowerID, Name;
    string contect;
    Borrower(string id, string n, string c) {
        BorrowerID = id;
        Name = n;
        contect = c;
    }
};

vector<Book> books;
vector<Borrower> borrowers;

void Addbook() {
    string id, t, a;
    cout << "Enter Book ID: ";
    cin >> id;
    for (const auto& it : books) {
        if (it.BookID == id) {
            cout << "The Book already Exists.
";
            return;
        }
    }
    cout << "Enter Book Title: ";
    cin.ignore();
    getline(cin, t);
    cout << "Enter Author name: ";
    getline(cin, a);
    books.emplace_back(id, t, a);
    cout << "Book Added successfully
";
}

void Updatebook() {
    string id, t, a;
    cout << "Enter ID for update: ";
    cin >> id;
    auto it = find_if(books.begin(), books.end(), [&](const Book& b) { return b.BookID == id; });
    if (it == books.end()) {
        cout << "ID is not found
";
        return;
    }
    cout << "Enter New Title: ";
    cin.ignore();
    getline(cin, t);
    cout << "Enter New Author name: ";
    getline(cin, a);
    it->Title = t;
    it->Author = a;
    cout << "Updated successfully.
";
}

void Deletebook() {
    string id;
    cout << "Enter ID: ";
    cin.ignore();
    getline(cin, id);
    auto it = find_if(books.begin(), books.end(), [&](const Book& b) { return b.BookID == id; });
    if (it == books.end()) {
        cout << "Book Is not Found.
";
        return;
    }
    if (!it->isAvailable) {
        cout << "Cannot Delete.
";
        return;
    }
    books.erase(it);
    cout << "Book is Deleted successfully!
";
}

void Searchbook() {
    int option;
    cout << "Search Book By:
1.ID
2.Title
";
    cin >> option;
    cin.ignore();
    if (option == 1) {
        string id;
        cout << "Enter ID: ";
        cin >> id;
        auto it = find_if(books.begin(), books.end(), [&](const Book& b) { return b.BookID == id; });
        if (it == books.end()) {
            cout << "The Book is not found.
";
        } else {
            cout << "Book Found:
";
            cout << "ID: " << it->BookID << "
Title: " << it->Title << "
Author: " << it->Author << "
Status: " << (it->isAvailable ? "Available" : "Borrowed") << "
";
        }
    } else if (option == 2) {
        string t;
        cout << "Enter Title: ";
        getline(cin, t);
        auto it = find_if(books.begin(), books.end(), [&](const Book& b) { return b.Title == t; });
        if (it == books.end()) {
            cout << "No Book found with matching title.
";
        } else {
            cout << "Book Found:
";
            cout << "ID: " << it->BookID << "
Title: " << it->Title << "
Author: " << it->Author << "
Status: " << (it->isAvailable ? "Available" : "Borrowed") << "
";
        }
    } else {
        cout << "Invalid option...
";
    }
}

void Registerborrower() {
    string id, n, c;
    cout << "Enter Borrower ID: ";
    cin >> id;
    for (const auto& it : borrowers) {
        if (it.BorrowerID == id) {
            cout << "The ID already Exists.
";
            return;
        }
    }
    cout << "Enter Borrower Name: ";
    cin.ignore();
    getline(cin, n);
    cout << "Enter Contact Info: ";
    getline(cin, c);
    borrowers.emplace_back(id, n, c);
    cout << "Borrower Added successfully
";
}

void Returnbook() {
    string id, it;
    cout << "Enter Book ID: ";
    cin >> id;
    cout << "Enter Borrower ID: ";
    cin >> it;
    auto bookIt = find_if(books.begin(), books.end(), [&](const Book& b) { return b.BookID == id; });
    auto borrowerIt = find_if(borrowers.begin(), borrowers.end(), [&](const Borrower& b) { return b.BorrowerID == it; });
    if (bookIt == books.end()) {
        cout << "Book ID not found.
";
        return;
    }
    if (borrowerIt == borrowers.end()) {
        cout << "Borrower ID not found.
";
        return;
    }
    if (bookIt->isAvailable) {
        cout << "This book was not borrowed.
";
        return;
    }
    bookIt->isAvailable = true;
    cout << "Book returned successfully!
";
}

void Displayallbooks() {
    if (books.empty()) {
        cout << "No Books in this system.
";
        return;
    }
    cout << "Available books:
";
    for (const auto& b : books) {
        cout << "Book ID: " << b.BookID << "
Title: " << b.Title << "
Author: " << b.Author << "
Status: " << (b.isAvailable ? "Available" : "Borrowed") << "
------------------------
";
    }
}

void borrowbook() {
    string id, bid;
    cout << "Enter Book ID: ";
    cin >> id;
    cout << "Enter Borrower ID: ";
    cin >> bid;
    auto bookIt = find_if(books.begin(), books.end(), [&](const Book& b) { return b.BookID == id; });
    auto borrowerIt = find_if(borrowers.begin(), borrowers.end(), [&](const Borrower& b) { return b.BorrowerID == bid; });
    if (bookIt == books.end()) {
        cout << "Book ID not found.
";
        return;
    }
    if (borrowerIt == borrowers.end()) {
        cout << "Borrower ID not found.
";
        return;
    }
    if (!bookIt->isAvailable) {
        cout << "Book is already borrowed.
";
        return;
    }
    bookIt->isAvailable = false;
    cout << "Book borrowed successfully!
";
}

void Displayoverduebooks() {
    cout << "
Overdue Books:
";
    bool found = false;
    for (const auto& b : books) {
        if (!b.isAvailable) {
            cout << "ID: " << b.BookID << ", Title: " << b.Title << ", Author: " << b.Author << " (Status: Borrowed)
";
            found = true;
        }
    }
    if (!found) {
        cout << "No overdue books right now.
";
    }
}

int main() {
    int choice;
    while (true) {
        cout << "========Library Management System==========
";
        cout << "1.Add a book
2.Update a book
3.Delete a book
4.Search for a book
5.Register a borrower
6.Borrow a book
7.Return a book
8.Display overdue books
9.Display all books
10.Exit the program
";
        cin >> choice;
        switch (choice) {
            case 1: Addbook(); break;
            case 2: Updatebook(); break;
            case 3: Deletebook(); break;
            case 4: Searchbook(); break;
            case 5: Registerborrower(); break;
            case 6: borrowbook(); break;
            case 7: Returnbook(); break;
            case 8: Displayoverduebooks(); break;
            case 9: Displayallbooks(); break;
            case 10: cout << "=======Exiting========"; return 0;
            default: cout << "Invalid input.
"; break;
        }
    }
    return 0;
}
