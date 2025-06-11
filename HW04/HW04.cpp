#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {
    }
};

class BookManager {
private:
    vector<Book> books;

public:
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author));
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (const auto& book : books) {
            cout << "- " << book.title << " by " << book.author << endl;
        }
    }

    vector<Book> getAllBooks() const {
        return books;
    }

    vector<Book> getBooksByTitle(const string& title) const {
        vector<Book> results;
        for (const auto& book : books) {
            if (book.title == title) {
                results.push_back(book);
            }
        }
        return results;
    }

    vector<Book> getBooksByAuthor(const string& author) const {
        vector<Book> results;
        for (const auto& book : books) {
            if (book.author == author) {
                results.push_back(book);
            }
        }
        return results;
    }
};

class BorrowManager {
private:
    unordered_map<string, int> stock;


public:
    void initializeStock(const vector<Book>& books, const int quantity = 3) {
        for (const auto& book : books) {
            if (stock.find(book.title) == stock.end()) {
                stock[book.title] = quantity;
            }
        }
    }

    void borrowBook(const string& title) {
        if (stock.find(title) != stock.end() && stock[title] > 0) {
            stock[title]--;
            cout << "책을 대출했습니다 " << endl;
        }
        else {
            cout << "책이 없거나 모두 대출 중입니다 " << endl;
        }
    }

    void returnBook(const string& title, const int quantity = 3) {
        if (stock.find(title) != stock.end() && stock[title] < quantity) {
            stock[title]++;
            cout << "책을 반납했습니다 " << endl;
        }
        else {
            cout << "반납할 수 없거나 등록되지 않은 책입니다 " << endl;
        }
    }

    void displayStock() const {
        cout << "현재 재고" << endl;
        for (const auto& item : stock) {
            cout << item.first << ": " << item.second << "권" << endl;
        }
    }

    bool isAvailable(const string& title) const {
        auto it = stock.find(title);
        return (it != stock.end() && it->second > 0);
    }
};

int main() {
    BookManager manager;
    BorrowManager borrowManager;

    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl;
        cout << "2. 모든 책 출력" << endl;
        cout << "3. 책 제목 검색" << endl;
        cout << "4. 책 저자 검색" << endl;
        cout << "5. 책 대여 (제목 입력)" << endl;
        cout << "6. 책 반납" << endl;
        cout << "7. 재고 보기" << endl;
        cout << "8. 종료" << endl;

        cout << "선택: ";
        int choice;
        cin >> choice;


        borrowManager.initializeStock(manager.getAllBooks());

        if (choice == 1) {
            string title, author;
            cout << "책 제목: ";
            cin.ignore();
            getline(cin, title);
            cout << "책 저자: ";
            getline(cin, author);
            manager.addBook(title, author);
        }
        else if (choice == 2) {
            manager.displayAllBooks();
        }
        else if (choice == 3) {
            string title;
            cout << "책 제목: ";
            cin.ignore();
            getline(cin, title);
            auto books = manager.getBooksByTitle(title);

            if (books.empty()) {
                cout << "책이 존재하지 않습니다" << endl;
            }
            else {
                for (const auto& book : books) {
                    cout << book.title << " by " << book.author;
                    if (borrowManager.isAvailable(book.title)) {
                        cout << " (대여 가능)" << endl;

                    }
                    else {
                        cout << " (대여 불가)" << endl;
                    }
                }
            }
        }
        else if (choice == 4) {
            string author;
            cout << "검색할 작가명: ";
            cin.ignore();
            getline(cin, author);
            auto books = manager.getBooksByAuthor(author);

            if (books.empty()) {
                cout << "책이 존재하지 않습니다." << endl;
            }
            else {

                for (const auto& book : books) {
                    cout << book.title << " by " << book.author;
                    if (borrowManager.isAvailable(book.title)) {
                        cout << " (대여 가능)" << endl;

                    }
                    else {
                        cout << " (대여 불가)" << endl;
                    }
                }
            }
        }
        else if (choice == 5) {
            string title;
            cout << "대여할 책 제목: ";
            cin.ignore();
            getline(cin, title);
            borrowManager.borrowBook(title);
        }
        else if (choice == 6) {
            string title;
            cout << "반납할 책 제목: ";
            cin.ignore();
            getline(cin, title);
            borrowManager.returnBook(title);
        }
        else if (choice == 7) {
            borrowManager.displayStock();
        }
        else if (choice == 8) {
            cout << "프로그램을 종료합니다." << endl;
            break;
        }
        else {
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
            cin.clear();
            cin.ignore();
        }
    }

    return 0;
}
