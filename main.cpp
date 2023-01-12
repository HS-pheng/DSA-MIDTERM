#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <map>
#include <iomanip>
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
        case 1:
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Display info to be filled up
            cout << "Pleaes input following information!" << endl;

            id = get_next_id();
            getTitle(title);
            getGenre(genre);
            getPublishDate(publishDate);

            database->addRecord(id, title, genre, publishDate);
            cout << "Data has been recorded sucessfully!" << endl;

            database->close();
            system("read");
            break;

        case 2:
            cout << "Please Input Id to search: ";
            cin >> id;
            try
            {
                database->printRecord(id);
            }
            catch (const char *err)
            {
                cout << err << endl;
                system("read");
            }
            cin.clear();
            break;
        case 3:
            database->printTable();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        case 4:
            cout << "Please input id to delete: ";
            cin >> id;
            if (database->deleteRecord(id))
            {
                cout << "Data deleted successfully" << endl;
                database->close();
                system("read");
                break;
            }
            else
            {
                cout << "Data not found" << endl;
                system("read");
            }
            break;
        case 5:
            return 0;
        default:
            cout << "Invalid choice" << endl;
            system("read");
            break;
        }
        cin.clear();
    }

    return 0;
}