#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iomanip>
#include "Database.h"
#include "util.h"
using namespace std;

int main()
{
    Database *database = new Database("MOCK_DATA-3.csv");

    string id, title, genre, publishDate;

    while (true)
    {
        //print list of menu to perform functions
        print_menu();

        int choice;
        
        //get input choice and validate input
        get_input_choice(choice);

        switch (choice)
        {
        case 1: // add record to list
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");

            // Display info to be filled up
            cout << "\nPleaes input following information!" << endl;

            //Get id from txt file and auto increment write into id.txt file
            id = get_next_id();

            //get title with validation
            do
            {
                getTitle(title);    
            } while (title == "");  //if title is null, continue looping

            //get genre with validation inside
            getGenre(genre);

            //get publish date from user, try, catch and throw error
            try
            {
                getPublishDate(publishDate);
            }
            catch (const char *err)
            {
                cout << err << endl;
                return 0;
            };

            //add record to database with parameter id, title, genre, publishdate
            database->addRecord(id, title, genre, publishDate);
            cout << "Data has been recorded sucessfully!" << endl;  //Pop up successfull message

            //Close then write record into database (CSV file)
            database->close();

            system("pause");
            break;

        case 2: // search for existing record
            system("cls");
            cout << "\nPlease Input Id to search: ";
            cin >> id;
            
            //perform search function by taking Id as parameter
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
            system("pause");
            break;
        case 5: // terminate program
            return 0;
        default:
            cout << "Invalid choice" << endl;
            system("pause");
            break;
        }
    }

    return 0;
}