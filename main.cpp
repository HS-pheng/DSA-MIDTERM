#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Database.h"
#include "util.h"
using namespace std;

int main()
{
    Database *database = new Database("MOCK_DATA-3.csv");

    string id, title, genre, publishDate;

    int genre_option;

    while (true)
    {
        print_menu();

        int choice;
        get_input_choice(choice);

        switch (choice)
        {
        case 1: // add record to list
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("clear");
            // Display info to be filled up
            cout << "\nPleaes input following information!" << endl;

            id = get_next_id();
            do
            {
                getTitle(title);
            } while (title == "");

            getGenre(genre);
            try
            {
                getPublishDate(publishDate);
            }
            catch (const char *err)
            {
                cout << err << endl;
                ;
                return 0;
            };

            database->addRecord(id, title, genre, publishDate);
            cout << "Data has been recorded sucessfully!" << endl;

            database->close();
            system("read");
            break;

        case 2: // search for existing record
            system("clear");
            cout << "\nPlease Input Id to search: ";
            cin >> id;
            database->searchById(id);
            cin.clear();
            break;
        case 3: // print existing records
            database->printTable();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        case 4: // delete existing record
            cout << "Please input id to delete: ";
            cin >> id;
            if (database->deleteRecord(id))
            {
                cout << "Data deleted successfully" << endl;
                database->close();
            }
            else
            {
                cout << "Data not found" << endl;
            }
            system("read");
            break;
        case 5: // terminate program
            return 0;
        default:
            cout << "Invalid choice" << endl;
            system("read");
            break;
        }
    }

    return 0;
}