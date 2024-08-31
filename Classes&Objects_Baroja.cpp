#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std; 

namespace Text {
    inline void ToUpper(string& str) 
	{
        for (char& c : str) 
		{
            if (c >= 'a' && c <= 'z') {
                c = c - 32;
            }
        }
    }

    inline void ToLower(string& str) 
	{
        for (char& c : str) 
		{
            if (c >= 'A' && c <= 'Z') 
			{
                c = c + 32;
            }
        }
    }

    inline void RemoveExtraSpaces(string& str) 
	{
        str.erase(std::unique(str.begin(), str.end(), [](char a, char b) { return isspace(a) && isspace(b); }), str.end());
        if (str.front() == ' ') str.erase(str.begin());
        if (str.back() == ' ') str.pop_back();
    }
}

class Book 
{
	
public:
    Book(int bookID, const string& title, const std::string& author, const string& year)
        : m_BookID(bookID), m_Title(title), m_Author(author), m_Year(year) {}

    const string& GetTitle() const 
	{
        return m_Title;
    }

    const string& GetAuthor() const 
	{
        return m_Author;
    }

    const string& GetYear() const 
	{
        return m_Year;
    }

private:
    int m_BookID;
    string m_Title;
    string m_Author;
    string m_Year;
};

class Library 
{
public:
    void AddBook(const string& title, const string& author, const string& year) 
	{
        books.emplace_back(bookCounter++, title, author, year);
        cout<<"BookIndex["<<books.size()-1<<"] Successfully added\n";
    }

    void ListBooks() const 
{
    if (books.empty()) 
    {
        cout << "No books in the library.\n";
    } 
    else 
    {
        cout << "Here are the books we have:\n\n";
        cout << left << setw(25) << "Title" << setw(20) << "Author" << "Year\n";
        cout << "-----------------------------------------------------------\n";
        for (const auto& book : books) 
        {
            cout << left << setw(25) << book.GetTitle() << setw(20) << book.GetAuthor() << book.GetYear() << "\n";
        }
        cout << "-----------------------------------------------------------\n";
    }
}

    void SearchBook(const string& query) const
	{
        string searchQuery = query;
        Text::ToLower(searchQuery);
        Text::RemoveExtraSpaces(searchQuery);

        bool found = false;
        for(const auto& book : books) 
		{
            string title = book.GetTitle();
            string author = book.GetAuthor();

            Text::ToLower(title);
            Text::RemoveExtraSpaces(title);

            Text::ToLower(author);
            Text::RemoveExtraSpaces(author);

            if (title == searchQuery || author == searchQuery) 
			{
                
				cout<<"\nInformation for Book found:\n";
                cout<<"Title: " << book.GetTitle() << "\n";
                cout<<"Author: " << book.GetAuthor() << "\n";
                cout<<"Year: " << book.GetYear() << "\n\n";
                found = true;
                break;
            }
        }

        if (!found) 
		{
            cout<<"\nBook '"<<query<< "' not found!\n";
        }
    }

private:
    vector<Book> books;
    int bookCounter = 0;
};

void ProcessAddBook(Library& library) {
    string title, author, year;

    cout<<"Enter Book Title [3-32 characters only!!]: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, title);
    cout<<"Enter Book Author [3-32 characters only!!]: ";
    getline(cin, author);
    cout<<"Enter Year Published [4 characters only!!]: ";
    getline(cin, year);

    library.AddBook(title, author, year);
}

void ProcessListBooks(const Library& library) 
{
    library.ListBooks();
}

void ProcessSearchBooks(const Library& library) 
{
    string query;
    cout<<"Enter Book Title or Author to Search For: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, query);

    library.SearchBook(query);
}

int main() 
{
    Library library;
    cout<<"Ezekiel Archives Library Book Manager\n";

    for (;;) 
	{
        cout<<"Please choose an option fellow Bookworm:\n"
                     "1 - To add Book\n"
                     "2 - List Book\n"
                     "3 - Search Book\n"
                     "4 - Exit\n"
                     "______________________\n> ";

        char in;
        cin >> in;
        switch (in) 
		{
            case '1': 
			{
                ProcessAddBook(library);
                break;
            }
            case '2': 
			{
                ProcessListBooks(library);
                break;
            }
            case '3': 
			{
                ProcessSearchBooks(library);
                break;
            }
            case '4': 
			{
                cout<<"Thank you, come again!\n";
                return 0;
            }
            default: 
			{
                cout<<"Wrong command! Try again.\n";
                break;
            }
        }
    }

    return 0;
}
