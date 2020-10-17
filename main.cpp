// Sumayyah Alhydary 175063
// This is a library management console application to be used by a librarian and provides the following services:
// reading book information from a file, writing new book information to a file, searching for books by subject,
// loan a book copy (if available), and returning a loaned book.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>


using namespace std;

enum copyAvail {
    IN_LIBRARY_USE, //0
    AVAILABLE, //1
    LOANED //2
};
struct book {
    string ISBN;
    string TITLE;
    string AUTHORS[5]; //up to 5 authors.
    string HEADINGS[5]; //up to 5 subject headings.
    int EDITION;
    string YEAR_OF_PUBLICATION;
    int NUMBER_OF_COPIES;
    copyAvail AVAIL[50]; //assuming the max number of copies is 50. Can be changed if needed.
};


void getBookInfo(book &b);
void displayBookInfo(book &b);
void writeBookInfo(book &b, fstream &outfile);
void readBookInfo(book &b2, fstream &infile);


//these two functions I found in a library file created by a developer (GManNickG) on gethub to manipulate strings.
//I applied few modifications on them to better fit what I need.
vector<string> split(const string& str, const char& ch) {
    string next;
    vector<string> result;

    // For each character in the string
    for (string::const_iterator it = str.begin(); it != str.end(); it++) {
        // If we've hit the terminal character
        if (*it == ch) {
            // If we have some characters accumulated
            if (!next.empty()) {
                // Add them to the result vector
                result.push_back(next);
                next.clear();
            }
        } else {
            // Accumulate the next character into the sequence
            next += *it;
        }
    }
    if (!next.empty())
        result.push_back(next);
    return result;
}
std::string trim(const string& str, const string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos) {return "";} // no content
    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}

//this function get one book’s information from the librarian and fill up the struct designed.
void getBookInfo(book &b){
    cout << "ISBN: ";
    getline(cin, b.ISBN);

    cout << "Title: ";
    getline(cin, b.TITLE);


    cout << "Please list up to 5 author names. Leave author name blank if less than 5." << endl;
    for (int i=0; i<5 ; i++) {
        if (i==0) {
            cin.clear();
        }
        cout << "author " << (i+1) << " : " ;
        getline(cin, b.AUTHORS[i]);
    }

    /*cout << "TESTING OUTPUT: " ;
    for (int i=0; i<5 ; i++) {
        cout << b.AUTHORS[i] << " " ;
    } cout << endl; */


    cout << "Please list up to 5 subject headings in lower-case. Leave subject heading blank if less than 5." << endl;
    for (int i=0; i<5 ; i++) {
        if (i==0) {
            cin.clear();
        }
        cout << "topic " << (i+1) << ": " ;
        getline(cin, b.HEADINGS[i]);
    }

    /*cout << "TESTING OUTPUT: " ;
    for (int i=0; i<5 ; i++) {
        cout << b.HEADINGS[i] << " " ;
    } cout << endl; */

    cout << "Edition: " ;
    cin >> b.EDITION;

    cout << "Year: " ;
    cin >> b.YEAR_OF_PUBLICATION;

    cout << "Number of hard copies: " ;
    cin >> b.NUMBER_OF_COPIES;

    cout << "Please list the availability status of each copy." << endl;
    cout << "type A if available." << endl;
    cout << "type L if loaned." << endl;
    cout << "type I if in-library-use only." << endl;
    for (int i=1 ; i<=b.NUMBER_OF_COPIES ; i++) {
        cout << "copy " << i << ": " ;
        char c = ' ';
        cin >> c;
        c = ::toupper(c);
        switch (c){
            case 'A': b.AVAIL[i-1] = AVAILABLE; break;
            case 'L': b.AVAIL[i-1] = LOANED; break;
            case 'I': b.AVAIL[i-1] = IN_LIBRARY_USE; break;
            default: break;
        }
    }

    /*cout << "TESTING OUTPUT: ";
    for (int i=0 ; i<nohc ; i++) {
        cout << b.AVAIL[i] << " " ; }
    cout << endl; */

}
//this function print a book’s information to the screen.
void displayBookInfo(book &b) {
    cout << "ISBN: " << b.ISBN << endl;
    cout << "Title: " << b.TITLE << endl;
    cout << "Authors: " ;
    //print all in one line separated with commas.
    for (int i=0 ; i< (sizeof(b.AUTHORS)/sizeof(b.AUTHORS[0])) ; i++) {
        if (!b.AUTHORS[i].empty()) {
            cout << b.AUTHORS[i] << "," ;
        }
    };
    cout << endl << "Subjects: " ;
    //print all in one line separated with commas.
    for (int i=0 ; i< (sizeof(b.HEADINGS)/sizeof(b.HEADINGS[0])) ; i++) {
        if (!b.HEADINGS[i].empty()) {
            cout << b.HEADINGS[i] << "," ;
        }
    }
    cout << endl;

    cout << "Edition: " << b.EDITION << endl;
    cout << "Year: " << b.YEAR_OF_PUBLICATION << endl;
    cout << "Number of copies: " << b.NUMBER_OF_COPIES << endl;
    //loop through all copies.
    for (int i=0 ; i<b.NUMBER_OF_COPIES ; i++) {
        if (b.AVAIL[i] == 0) {
            cout << "Copy " << (i+1) << " : in library use only" << endl; }
        if (b.AVAIL[i] == 1) {
            cout << "Copy " << (i+1) << " : available" << endl; }
        if (b.AVAIL[i] == 2) {
            cout << "Copy " << (i+1) << " : loaned" << endl; }
    }
    cout << endl;
}
//this function write a book’s information to a file.
void writeBookInfo(book &b, fstream &outfile) {
    // will be same as displayBookInfo but use outfile instead of cout.
    outfile << "ISBN: " << b.ISBN << endl;
    outfile << "Title: " << b.TITLE << endl;
    outfile << "Authors: " ;
    //print all in one line separated with commas.
    for (int i=0 ; i< (sizeof(b.AUTHORS)/sizeof(b.AUTHORS[0])) ; i++) {
        if (!b.AUTHORS[i].empty()) {
            outfile << b.AUTHORS[i] << ", " ;
        }
    };
    outfile << endl << "Subjects: " ;
    //print all in one line separated with commas.
    for (int i=0 ; i< (sizeof(b.HEADINGS)/sizeof(b.HEADINGS[0])) ; i++) {
        if (!b.HEADINGS[i].empty()) {
            outfile << b.HEADINGS[i] << ", " ;
        }
    };
    outfile << endl;
    outfile << "Edition: " << b.EDITION << endl;
    outfile << "Year: " << b.YEAR_OF_PUBLICATION << endl;
    outfile << "Number of copies: " << b.NUMBER_OF_COPIES << endl;
    for (int i=0 ; i<b.NUMBER_OF_COPIES ; i++) {
        if (b.AVAIL[i] == 0) {
            outfile << "Copy " << (i+1) << ": in library use only" << endl; }
        if (b.AVAIL[i] == 1) {
            outfile << "Copy " << (i+1) << ": available" << endl; }
        if (b.AVAIL[i] == 2) {
            outfile << "Copy " << (i+1) << ": loaned" << endl; }
    }
    outfile << "================================================" << endl;
}
//read a book’s information from a file.
void readBookInfo(book &b2, fstream &infile) {
    string str;
    string arr[100]; //assuming no book will require more than 100 lines to write down its info.
    int i = 0;
    while (getline(infile, str)) {
        if (str[0] != '=') { //to read info for only one book
            //take the substring between : and \n and store it in arr[i].
            unsigned first = str.find(':');
            unsigned last = str.find('\n');
            string strNew = str.substr (first+1,last-first);
            arr[i] = strNew;
            i++; //to count how many lines exist for the book.

        }
        else { break; } //stop when finish reading only one book lines.
    }

    //remove leading and trailing spaces from strings stored in arr.
    for (int j=0 ; j<i ; j++) {
        arr[j] = trim(arr[j]);
    }

    //store extraced info from txt file into book b2.
    b2.ISBN = arr[0];
    b2.TITLE = arr[1];

    //since authors' names are in one line, we need to split them.
    //split the line by using , as delimiter and store names in vectors.
    string temp = arr[2];
    vector<string> result = split(temp, ',');
    for (int i=0 ; i<5 ; i++) {
        if (i < result.size()) { //to avoid accessing index out of range.
            result[i] = trim(result[i]); //remove leading spaces after split (space after comma).
            b2.AUTHORS[i] = result[i];
        }
        else {
            b2.AUTHORS[i] = ""; }
    } //for


    //since subject headings are in one line, we need to split them.
    //split the line by using , as delimiter and store subjects in vectors.
    temp = arr[3];
    result = split(temp, ',');
    for (int i=0 ; i<5 ; i++) {
        if (i < result.size()) { //to avoid accessing index out of range.
            result[i] = trim(result[i]); //remove leading spaces after split (space after comma).
            b2.HEADINGS[i] = result[i];
        }
        else {
            b2.HEADINGS[i] = ""; }
    } //for


    //change from string to int to store Edition in b2.EDITION
    stringstream geek(arr[4]);
    geek >> b2.EDITION;

    b2.YEAR_OF_PUBLICATION = arr[5];

    //change from string to int to store number of copies in b2.NUMBER_OF_COPIES
    stringstream geek2(arr[6]);
    geek2 >> b2.NUMBER_OF_COPIES;

    //read the status of each copy
    for (int i=7 ; i<(7+b2.NUMBER_OF_COPIES) ; i++) {
        if (arr[i] == "available") {
            b2.AVAIL[i-7] = AVAILABLE ;
            //cout << b2.AVAIL[i-7] << endl;
        }
        else if (arr[i] == "loaned") {
            b2.AVAIL[i-7] = LOANED;
            //cout << b2.AVAIL[i-7] << endl;
        }
        else if (arr[i] == "in library use only") {
            b2.AVAIL[i-7] = IN_LIBRARY_USE;
            //cout << b2.AVAIL[i-7] << endl;
        }
        else { cerr << "unrecognized data or data entered do not match the format. Book status must be in lower case." << endl; }
    }

}


int main() {

    book data[1000]; //store book data up to 1000 books.
    fstream records; //fstream read and write.
    records.open("records.txt"); //records.txt must be in same directory.
    if (records.fail()) {
        cerr << "Could not open input file." << endl; }

    int mark=0; //to store the position of the next available slot in data[].
    for (int i=0 ; i<1000 ; i++) {
        readBookInfo(data[i], records); //read books data from file to data[].
        if (data[i].NUMBER_OF_COPIES == 0) { //no books with zero number of copies.
            mark = i;
            break; // end of file.
        }
    }



    int choice=0;
    cout << "Welcome to your library!" << endl;
    cout << "==================================" << endl;
    cout << "What would you like to do:" << endl;
    cout << "1: enter a new book information. " << endl;
    cout << "2: search for a book in certain subject." << endl;
    cout << "3: loan a book." << endl;
    cout << "4: return a book." << endl;
    cout << "5: Quit." << endl;
    cout << "? ";
    cin >> choice;
    cin.clear();
    cin.ignore(10000, '\n');
    while (true) {
        switch (choice) {
            case 1:
                getBookInfo(data[mark]);
                mark++;
                break;
            case 2: {
                cout << "subject? ";
                string temp = {0};
                getline(cin, temp);
                cin.clear();
                //convert input to lowercase (from thispointer.com):
                for_each(temp.begin(), temp.end(), [](char & c){ c = tolower(c); });

                bool flag = false; //checking possible input error.
                for (int i = 0 ; i<mark ; i++) {
                    for (int j=0 ; j<5 ; j++) {
                        if (data[i].HEADINGS[j] == temp) {
                            displayBookInfo(data[i]);
                            flag = true;
                        }//if
                    }//for
                }//for
                if (!flag) { cout << "Could not find books with this subject, sorry!" << endl; }
                break;
            } //case 2
            case 3: {
                cout << "ISBN? ";
                string temp2 = {0};
                getline(cin, temp2);
                cin.clear();
                bool flag2 = false; //checking possible input error.
                for (int i = 0; i < mark; i++) {
                    if (data[i].ISBN == temp2) {
                        for (int j=0 ; j < data[i].NUMBER_OF_COPIES; j++) {
                            if (data[i].AVAIL[j] == 1) { //at least one copy status is available.
                                cout << data[i].TITLE << " checked out." << endl;
                                data[i].AVAIL[j] = LOANED; //update status of that copy.
                                flag2 = true;
                                break; // change status of only one copy
                            } //if
                        } //for
                    }//if
                }//for
                if (!flag2) { cout << "could not find ISBN or no available copies to loan. " << endl; }
                break;
            } //case 3
            case 4: {
                cout << "ISBN? ";
                string temp3 = {0};
                getline(cin, temp3);
                cin.clear();
                bool flag3 = false; //checking possible input error.
                for (int i=0 ; i<mark ; i++) {
                    if (data[i].ISBN == temp3) {
                        for (int j=0 ; j<data[i].NUMBER_OF_COPIES ; j++) {
                            if (data[i].AVAIL[j] == 2) { // at least one copy status is loaned.
                                cout << data[i].TITLE << " returned." << endl;
                                data[i].AVAIL[j] = AVAILABLE; //update copy status to available.
                                flag3 = true;
                                break; //return only one copy.
                            } //if
                        } //for
                    }//if
                }//for
                if (!flag3) { cout << "could not find ISBN or no loaned copies to return." << endl;}
                break;
            } //case 4
            case 5: {
                records.close();
                fstream records1;
                records1.open("records.txt");
                for (int i = 0; i < mark; i++) {
                    writeBookInfo(data[i], records1); //overwrite all data in records.txt with data in data[].
                }
                records1.close();
                cout << "library records updated." << endl;
                cout << "Thank you! Bye Bye :) " << endl;
                return 0;
            }
            default: break;
        } //switch
        cout << "==================================" << endl;
        cout << "What would you like to do:" << endl;
        cout << "1: enter a new book information. " << endl;
        cout << "2: search for a book in certain subject." << endl;
        cout << "3: loan a book." << endl;
        cout << "4: return a book." << endl;
        cout << "5: Quit." << endl;
        cout << "? ";
        cin >> choice;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}