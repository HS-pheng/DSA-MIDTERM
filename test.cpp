#include <iostream>
using namespace std;

template <typename T>
class double_pair {
    public:
        T first;
        T second;
};

void get_input_choice(int &choice)
{
    bool input_err;
    do
    {
        input_err = false;
        cin >> choice;
        if (cin.fail() || (choice != 2 && choice != 1 && choice != 3 && choice != 4 && choice != 5))
        {
            cout << "Failed" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            input_err = true;
            cout << "\n\tInvalid input choice\n\n";
            cout << "\tEnter your choice: ";
        }
    } while (input_err);
}

int main() {
    string id, title, genre, date;

    int choice;
    get_input_choice(choice);

    cout << "choice: " << choice << endl;


    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "id: ";
    getline(cin, id);
    cout << "id: " << id << endl;

    cout << "title: ";
    getline(cin, title);
    cout << "title: " << title << endl;
}