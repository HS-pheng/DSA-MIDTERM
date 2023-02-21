#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iomanip>
#include <limits>
#include "Database.h"
#include "util.h"
using namespace std;

int main()
{
    Database *database = new Database("MOCK_DATA-3.csv");

    string id = "", title = "", genre = "", publishDate = "";

    while (true)
    {
        // print list of menu to perform functions
        print_menu();

        int choice, update_choice;

        // get input choice and validate input
        get_input_choice(choice);

        switch (choice)
        {
        case 1: // add record to list
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("clear");

            // Display info to be filled up
            cout << "\nPleaes input following information!" << endl;

            // Get id from txt file and auto increment write into id.txt file
            id = get_next_id();

            // get title with validation
            getTitle(title);

            // get genre with validation inside
            getGenre(genre);

            // get publish date from user, try, catch and throw error
            try
            {
                getPublishDate(publishDate);
            }
            catch (const char *err)
            {
                cout << err << endl;
                return 0;
            };

            // add record to database with parameter id, title, genre, publishdate
            database->addRecord(id, title, genre, publishDate);
            cout << "Data has been recorded sucessfully!" << endl; // Pop up successfull message

            // Close then write record into database (CSV file)
            database->close();

            system("read");
            break;

        case 2: // search for existing record
            system("clear");
            cout << "\nPlease Input Id to search: ";
            cin >> id;

            // perform search function by taking Id as parameter
            database->searchById(id);

            cin.clear();
            break;
        case 3: // search for existing record
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            system("clear");
            cout << "\nPlease Input Record Id to Modify: ";
            cin >> id;
            try
            {
                database->findRecord(id);
            }
            catch (const char *err)
            {
                cout << "Error: " << err << endl;
                system("read");
            }
            print_update_menu();              // print the update menu which consist of the modifier variable
            get_update_choice(update_choice); // get the update choice

            switch (update_choice)
            {

            case 1:
                // get title with validation
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                do
                {
                    getTitle(title);
                } while (title == ""); // if title is null, continue looping
                database->updateRecordTitle(id, title);
                break;
            case 2:
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getGenre(genre);
                database->updateRecordGenre(id, genre);
                break;
            case 3:
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                try
                {
                    getPublishDate(publishDate);
                }
                catch (const char *err)
                {
                    cout << err << endl;
                    return 0;
                };
                database->updateRecordPublishDate(id, publishDate);
                break;
            case 4:
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("clear");

                // Display info to be filled up
                cout << "\nPleaes input new information!" << endl;

                // get title with validation
                getTitle(title);

                // get genre with validation inside
                getGenre(genre);

                // get publish date from user, try, catch and throw error
                try
                {
                    getPublishDate(publishDate);
                }
                catch (const char *err)
                {
                    cout << err << endl;
                    return 0;
                };

                // add record to database with parameter id, title, genre, publishdate
                database->updateRecordAll(id, title, genre, publishDate);
                cout << "Data has been updated sucessfully!" << endl; // Pop up successfull message

                // Close then write record into database (CSV file)
                database->close();

                system("read");
                break;
            case 5:
                break;
            default:
                break;
            }
            cin.clear();
            break;
        case 4: // print existing records
            database->printTable();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        case 5: // delete existing record
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
        case 6: // terminate program
            return 0;
        default:
            cout << "Invalid choice" << endl;
            system("read");
            break;
        }
    }

    return 0;
}