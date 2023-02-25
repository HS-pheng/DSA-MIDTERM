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
    // Create new database instance
    //Database *database = new Database("MOCK_DATA-5.csv");
    Database *database = new Database("MOCK_DATA-4.csv");
    
    string id = "", title = "", author = "", genre = "", publishDate = "", year = "";

    // Enter program loop
    while (true)
    {
        // print list of menu to perform functions
        print_menu();

        char choice;
        char update_choice, order_choice;
        string sort_by;
        // get input choice and validate input
        get_input_choice(choice);

        switch (choice)
        {
        case '1': // add record to list
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("clear");

            // Display info to be filled up
            cout << "\nPleaes input following information!" << endl;

            // Get id from txt file and auto increment write into id.txt file
            id = get_next_id();

            // get title with validation
            getTitle(title);

            // get author name
            getAuthor(author);

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
            database->addRecord(id, title, author, genre, publishDate);
            cout << "Data has been recorded sucessfully!" << endl; // Pop up successfull message

            // Close then write record into database (CSV file)
            database->close();

            system("read");
            break;

        case '2': // search for existing record
            system("clear");
            cout << "\nPlease Input Id to search: ";
            cin >> id;

            // perform search function by taking Id as parameter
            database->searchById(id);

            cin.clear();
            break;
        case '3': // search for existing record
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
                break;
            }
            print_update_menu();              // print the update menu which consist of the modifier variable
            get_update_choice(update_choice); // get the update choice

            switch (update_choice)
            {

            case '1':
                // get title with validation
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                do
                {
                    getTitle(title);
                } while (title == ""); // if title is null, continue looping
                database->updateRecordTitle(id, title);
                break;
            case '2':
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getGenre(genre);
                database->updateRecordGenre(id, genre);
                break;
            case '3':
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getAuthor(author);
                database->updateRecordAuthor(id, author);
                break;
            case '4':
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
            case '5':
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("clear");

                // Display info to be filled up
                cout << "\nPleaes input new information!" << endl;

                // get title with validation
                getTitle(title);

                // get genre with validation inside
                getGenre(genre);

                // get author information
                getAuthor(author);

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
                database->updateRecordAll(id, title, author, genre, publishDate);
                cout << "Data has been updated sucessfully!" << endl; // Pop up successfull message

                // Close then write record into database (CSV file)
                database->close();

                system("read");
                break;
            case '6':
                break;
            default:
                break;
            }
            cin.clear();
            break;

        case '4':
            database->sort("id", "ASC");
            database->printTable();

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;

        case '5':
            print_sorting_by_menu();
            get_print_sorting_by_choice(choice);
            switch (choice)
            {
            case '1':
                sort_by = "id";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case '2':
                sort_by = "title";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case '3':
                sort_by = "publishDate";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case '4':
                main();
                break;
            default:
                break;
            }
            print_sorting_order_menu();
            get_print_sorting_order_choice(order_choice);
            switch (order_choice)
            {
            case '1':
                database->sort(sort_by, "ASC");
                cout << "\nSorting by " << sort_by << " in ascending order:" << endl;
                database->printTable();
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case '2':
                database->sort(sort_by, "DESC");
                cout << "\nSorting by " << sort_by << " in descending order:" << endl;
                database->printTable();
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case '3':
                break;
            default:
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;

        case '6':
        
            print_filter_by_menu();
            get_filter_option_choice(choice);
            switch (choice)
            {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            case '1':
            cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getAuthor(author);
                database->filterByAuthor(author);
                break;
            case '2':
            cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getGenre(genre);
                database->filterByGenre(genre);
                break;
            case '3':
            cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getYear(year);
                database->filterByPublishDate(year);
                break;
            case '4':
                break;
            default:
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        case '7': // delete existing record
            cin.clear();
            cout << "Please input Id to delete: ";
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
        case '8': // terminate program
            return 0;
        default:
            cout << "Invalid choice" << endl;
            system("read");
            break;
        }
    }

    return 0;
}