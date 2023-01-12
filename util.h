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

void print_menu()
{
    system("clear");
    cout << "\n\n========= Library Database Program =========" << endl;
    cout << "[1]. Add record" << endl
         << "[2]. Search record" << endl
         << "[3]. Print records" << endl
         << "[4]. Delete record" << endl
         << "[5]. Exit" << endl
         << "\tEnter your choice: ";
}

void print_genre_opt()
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

void get_input_choice(int &choice)
{
    bool input_err;
    do
    {
        input_err = false;
        cin >> choice;
        if (cin.fail() || (choice != 2 && choice != 1 && choice != 3 && choice != 4 && choice != 5))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            input_err = true;
            cout << "\n\tInvalid input choice\n\n";
            cout << "\tEnter your choice: ";
        }

    } while (input_err);
}

void getGenre(string &genre)
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

void getPublishDate(string &publishDate)
{
    string year, month, day;
    do
    {
        cout << "Publish Date (dd/mm/yyyy): ";
        getline(cin, publishDate);
        stringstream ss(publishDate);
        getline(ss, day, '/');
        getline(ss, month, '/');
        getline(ss, year);
    } while (!(date_check(year, month, day)));
}

void getTitle(string &title)
{
    cout << "Title: ";
    getline(cin, title);
}

string get_next_id()
{
    int id;
    ifstream fin("id.txt");
    fin >> id;

    fin.close();

    ofstream fout("id.txt");
    fout << id + 1;
    return to_string(id);
}

