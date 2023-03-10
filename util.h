bool date_check(string year_s, string month_s, string day_s) // function to validate day, month and year entered
{
    int year = stoi(year_s);
    int month = stoi(month_s);
    int day = stoi(day_s);

    if (month >= 1 && month <= 12)
    {
        if ((month == 2) && ((year % 400 == 0) && ((year % 100 != 0) && (year % 4 == 0))))
        {
            if (day >= 1 && day <= 29)
            {
                return true;
            }
        }
        else if (month == 2)
        {
            if (day >= 1 && day <= 28)
            {
                return true;
            }
        }
        else if (month == 1 or month == 3 or month == 5 or month == 7 or month == 8 or month == 10 or month == 12)
        {
            if (day >= 1 && day <= 31)
            {
                return true;
            }
        }
        else if (month == 4 | month == 6 | month == 9 | month == 11)
        {
            if (day >= 1 && day <= 30)
            {
                return true;
            }
        }
    }
    else
    {
        return false;
    }
    return false;
}

void print_menu() // display options
{
    system("clear");
    cout << "\n\n\t\t\t\t\t\t========= Library Database Program =========" << endl;
    cout << "\t\t\t\t\t\t[1]. Add record" << endl
         << "\t\t\t\t\t\t[2]. Search record" << endl
         << "\t\t\t\t\t\t[3]. Update record" << endl
         << "\t\t\t\t\t\t[4]. Print Record" << endl
         << "\t\t\t\t\t\t[5]. Print Sorting Record" << endl
         << "\t\t\t\t\t\t[6]. Filter Record" << endl
         << "\t\t\t\t\t\t[7]. Delete record" << endl
         << "\t\t\t\t\t\t[8]. Exit" << endl
         << "\t\t\t\t\t\t\tEnter your choice: ";
}

void print_update_menu()
{
    system("clear");
    cout << "\t\t\t\t\tUpdate Option: " << endl;
    cout << "\t\t\t\t\t\t[1]. Update Title" << endl
         << "\t\t\t\t\t\t[2]. Update Genre" << endl
         << "\t\t\t\t\t\t[3]. Update Author's Name" << endl
         << "\t\t\t\t\t\t[4]. Update Publish Date" << endl
         << "\t\t\t\t\t\t[5]. Update Entire Row" << endl
         << "\t\t\t\t\t\t[6]. Back" << endl
         << "\t\t\t\t\t\t\tEnter your choice: ";
}

void print_sorting_by_menu() {
    system("clear");
    cout << "\t\t\t\t\tSort by: " << endl;
    cout << "\t\t\t\t\t\t[1]. By ID" << endl
         << "\t\t\t\t\t\t[2]. By Title" << endl
         << "\t\t\t\t\t\t[3]. By Publish Date" << endl
         << "\t\t\t\t\t\t[4]. Back" << endl
         << "\t\t\t\t\t\t\tEnter your choice: ";
}

void print_sorting_order_menu() {
    cout << "\t\t\t\t\t\tOrder by: " << endl;
    cout << "\t\t\t\t\t\t[1]. Asecnding Order" << endl
         << "\t\t\t\t\t\t[2]. Descending Order" << endl
         << "\t\t\t\t\t\t[3]. Back" << endl
         << "\t\t\t\t\t\t\tEnter your choice: ";
}

void print_filter_by_menu() {
    system("clear");
    cout << "\t\t\t\t\t\tFilter by: " << endl;
    cout << "\t\t\t\t\t\t[1]. Author" << endl
         << "\t\t\t\t\t\t[2]. Genre" << endl
         << "\t\t\t\t\t\t[3]. Publish Year" << endl
         << "\t\t\t\t\t\t[4]. Back" << endl
         << "\t\t\t\t\t\t\tEnter your choice: ";
}

void print_genre_opt() // display genre options
{
    cout << "Choose Genre" << endl;
    cout << "[1]. Horror" << endl
         << "[2]. Action" << endl
         << "[3]. Romantic" << endl
         << "[4]. Comedy" << endl
         << "[5]. Adventure" << endl
         << "[6]. Drama" << endl;
    cout << "Choose Genre Option: ";
}

void get_print_sorting_by_choice(char &choice) // check error input
{
    bool input_err;
    do
    {
        input_err = false;
        cin >> choice;
        if (cin.fail() || (choice != '2' && choice != '1' && choice != '3' && choice != '4'))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            input_err = true;
            cout << "\n\t\t\t\t\t\t\tInvalid input choice\n\n";
            cout << "\t\t\t\t\t\t\tEnter your choice: ";
        }

    } while (input_err);
    cout << endl;
}

void get_print_sorting_order_choice(char &choice) // check error input
{
    bool input_err;
    do
    {
        input_err = false;
        cin >> choice;
        if (cin.fail() || (choice != '2' && choice != '1' && choice != '3'))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            input_err = true;
            cout << "\n\t\t\t\t\t\t\tInvalid input choice\n\n";
            cout << "\t\t\t\t\t\t\tEnter your choice: ";
        }

    } while (input_err);
    cout << endl;
}

void get_filter_option_choice(char &choice) // check error input
{
    bool input_err;
    do
    {
        input_err = false;
        cin >> choice;
        if (cin.fail() || (choice != '2' && choice != '1' && choice != '3' && choice != '4'))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            input_err = true;
            cout << "\n\t\t\t\t\t\t\tInvalid input choice\n\n";
            cout << "\t\t\t\t\t\t\tEnter your choice: ";
        }

    } while (input_err);
    cout << endl;
}

void get_update_choice(char &choice) // check error input
{
    bool input_err;
    do
    {
        input_err = false;
        cin >> choice;
        if (cin.fail() || (choice != '2' && choice != '1' && choice != '3' && choice != '4' && choice != '5' && choice != '6'))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            input_err = true;
            cout << "\n\t\t\t\t\t\t\tInvalid input choice\n\n";
            cout << "\t\t\t\t\t\t\tEnter your choice: ";
        }

    } while (input_err);
    cout << endl;
}

void get_input_choice(char &choice) // check error input
{
    bool input_err;
    do
    {
        input_err = false;
        cin >> choice;
        if (cin.fail() || (choice != '2' && choice != '1' && choice != '3' 
        && choice != '4' && choice != '5' && choice != '6' && choice != '7' && choice != '8'))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            input_err = true;
            cout << "\n\t\t\t\t\t\t\tInvalid input choice\n\n";
            cout << "\t\t\t\t\t\t\tEnter your choice: ";
        }

    } while (input_err);
    cout << endl;
}

void getGenre(string &genre) // get genre option from suer
{
    int genre_option;
    bool gen_flag;
    do
    {
        print_genre_opt();
        cin >> genre_option;
        if (!cin.fail())
        {
            switch (genre_option)
            {
            case 1:
                genre = "Horror";
                gen_flag = false;

                break;
            case 2:
                genre = "Action";
                gen_flag = false;
                break;
            case 3:
                genre = "Romantic";
                gen_flag = false;
                break;
            case 4:
                genre = "Comedy";
                gen_flag = false;
                break;
            case 5:
                genre = "Adventure";
                gen_flag = false;
                break;
            case 6:
                genre = "Drama";
                gen_flag = false;
                break;
            default:
                gen_flag = true;
                break;
            }
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            gen_flag = true;
        }
    } while (gen_flag);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void getPublishDate(string &publishDate) // get publuish date from suer
{

    string year, month, day;
    int slashcounter = 0;
    do
    {
        cout << "Publish Date (dd/mm/yyyy): ";
        getline(cin, publishDate);
        for (int i = 0; i < publishDate.length(); i++)
        {
            if (isdigit(publishDate[i]))
            {
                continue;
            }
            else if (publishDate[i] == '/')
            {
                slashcounter++;
                continue;
            }
            else
            {
                throw "Bad Input";
            }
        }
        if (slashcounter < 2 or slashcounter > 2)
        {
            throw "Bad Input";
        }
        slashcounter = 0;
        stringstream ss(publishDate);
        getline(ss, day, '/');
        getline(ss, month, '/');
        getline(ss, year);
    } while (!(date_check(year, month, day)));
}

void getTitle(string &title) // get title from user
{
    do
    {
        cout << "Title: ";
        getline(cin, title);
    } while (title == ""); // if title is null, continue looping
}

void getAuthor(string &author) {
    do
    {
        cout << "Author: ";
        getline(cin, author);
    } while (author == ""); // if author is null, continue looping
    
} // get author

void getYear(string &year) // get title from user
{
    do
    {
        cout << "Enter Publish Year: ";
        getline(cin, year);
    } while (year == ""); // if title is null, continue looping
}

string get_next_id() // automatically assign id
{
    int id;
    ifstream fin("id.txt");
    fin >> id;

    fin.close();

    ofstream fout("id.txt");
    fout << id + 1;
    return to_string(id);
}