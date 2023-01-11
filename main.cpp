#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;

template <class T> // Generic template for the Double_node class
class Double_Node
{
public:
    T data;               // Generic data type
    Double_Node<T> *next; // Node pointer pointing to the next node
    Double_Node<T> *prev; // Node pointer pointing to the previous node
};

class DataRecord
{
public:
    string id;
    string name;
};

template <typename T>
class Double_list
{
public:
    Double_Node<T> *list_head;
    Double_Node<T> *list_tail;
    int list_size;

public:
    Double_list()
    {
        list_head = NULL;
        list_tail = NULL;
        list_size = 0;
    }

    Double_list(Double_list<T> &list) : Double_list()
    {
        for (Double_Node<T> *trav = list.list_head; trav != NULL; trav = trav->next)
        {
            this->push_back(trav->data);
        }
    }

    void diplayList() const
    {
        for (Double_Node<T> *trav = list_head; trav != NULL; trav = trav->next)
        {
            cout << trav->data << (trav->next == NULL ? "\n" : "->");
        }
    }

    void displayReverse() const
    {
        for (Double_Node<T> *trav = list_tail; trav != NULL; trav = trav->prev)
        {
            cout << trav->data << (trav->prev == NULL ? "\n" : "->");
        }
    }

    void push_back(T data)
    {
        Double_Node<T> *newNode = new Double_Node<T>();
        if (newNode == NULL)
        {
            throw "Overflow";
        }

        newNode->data = data;
        newNode->next = NULL;
        list_size++;

        if (list_head == NULL)
        {
            list_head = newNode;
            list_tail = newNode;
            newNode->prev = NULL;
            return;
        }

        newNode->prev = list_tail;
        list_tail->next = newNode;
        list_tail = newNode;
    }

    void pop_front()
    {
        list_head->next->prev = NULL;
        Double_Node<T> *temp = list_head->next;

        delete (list_head);

        list_head = temp;
        list_size--;
    }

    int size() const
    {
        return list_size;
    }

    T front() const
    {
        return list_head->data;
    }

    T back() const
    {
        return list_tail->data;
    }

    int count(T data) const
    {
        int counter = 0;
        for (Double_Node<T> *trav = list_head; trav != NULL; trav = trav->next)
        {
            if (trav->data == data)
                counter++;
        }
        return counter;
    }

    int erase(T data)
    {
        int erased = 0;
        for (Double_Node<T> *trav = list_head; trav != NULL; trav = trav->next)
        {
            if (trav->data != data)
            {
                continue;
            }

            erased++;

            if (list_size == 1)
            {
                delete (trav);
                list_head = list_tail = NULL;
                return 1;
            }

            Double_Node<T> *temp_next;
            Double_Node<T> *temp_prev;

            if (trav->next != NULL)
            {
                temp_next = trav->next;
            }
            else
            {
                trav->prev->next = NULL;
                list_tail = trav->prev;
                delete (trav);
                return 1;
            }

            if (trav->prev != NULL)
            {
                temp_prev = trav->prev;
            }
            else
            {
                trav->next->prev = NULL;
                list_head = trav->next;
                delete (trav);
                return 1;
            }

            temp_next->prev = temp_prev;
            temp_prev->next = temp_next;
            delete (trav);
            break;
        }
        return erased;
    }

    bool empty()
    {
        return list_size > 0 ? false : true;
    }

    Double_Node<T> *head()
    {
        return list_head;
    }

    Double_Node<T> *tail()
    {
        return list_tail;
    }

    void swap(Double_list<T> &list)
    {
        std::swap(list_head, list.list_head);
        std::swap(list_tail, list.list_tail);
    }

    ~Double_list()
    {
        for (Double_Node<T> *trav = list_head; trav != NULL;)
        {
            Double_Node<T> *temp = trav->next;
            delete (trav);
            trav = temp;
        }
    }
};

class CsvIO
{
private:
    string fileName;

public:
    CsvIO(string fileName)
    {
        this->fileName = fileName;
    }

    void read(Double_list<DataRecord> &dataTable)
    {
        string line;
        ifstream fin(fileName);
        getline(fin, line);
        while (getline(fin, line))
        {
            stringstream ss(line);
            string fieldValue;

            DataRecord record;
            string a, b;
            getline(ss, a, ',');
            getline(ss, b, ',');
            record.id = a;
            record.name = b;

            dataTable.push_back(record);
        }
    }

    void write(Double_list<DataRecord> lm)
    {
        ofstream fout(fileName);
        fout << "id,name\n";

        for (Double_Node<DataRecord> *trav = lm.head(); trav != NULL; trav = trav->next) {
            fout << (trav->data).id << ',' << (trav->data).name << "\n";
        }
    }

    void print_info(Double_list<DataRecord> dataTable)
    {
        int max_width[] = {5,5};

        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav=trav->next) {
            max_width[0] = (max_width[0] > (trav->data).id.length()) ? max_width[0] : (trav->data).id.length();
        }

        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav=trav->next) {
            max_width[1] = (max_width[1] > (trav->data).name.length()) ? max_width[1] : (trav->data).name.length();
        }


        for (int i = 0; i < 2; i++) {
            max_width[i] += 5;
            cout << i << ": "<<  max_width[i] << endl;
        }

        cout << left << setw(max_width[0]) << "ID" << setw(max_width[1]) << "Name" << endl;

        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav=trav->next) {
            cout << left << setw(max_width[0]) << (trav->data).id << setw(max_width[1]) << (trav->data).name << endl;
        }
    }
};

void deleteRecord(Double_list<DataRecord> &dataTable, string id){
    for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            if ((trav->data).id != id)
            {
                continue;
            }

            if (dataTable.size() == 1)
            {
                delete (trav);
                dataTable.list_head = dataTable.list_tail= NULL;
                break;
            }

            Double_Node<DataRecord> *temp_next;
            Double_Node<DataRecord> *temp_prev;

            if (trav->next != NULL)
            {
                temp_next = trav->next;
            }
            else
            {
                trav->prev->next = NULL;
                dataTable.list_tail = trav->prev;
                delete (trav);
                break;
            }

            if (trav->prev != NULL)
            {
                temp_prev = trav->prev;
            }
            else
            {
                trav->next->prev = NULL;
                dataTable.list_head = trav->next;
                delete (trav);
                break;
            }

            temp_next->prev = temp_prev;
            temp_prev->next = temp_next;
            delete (trav);
            break;
        }
}

DataRecord search(Double_list<DataRecord> &dataTable, string id){
    for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            if ((trav->data).id != id)
            {
                continue;
            }

            return (trav->data);
        }
    throw "Not found";
}

void printRecord(DataRecord dataRecord){
    cout << left << setw((dataRecord.id).length() + 5) << "ID" << setw((dataRecord.name).length()) << "Name" << endl; 
    cout << left << setw((dataRecord.id).length() + 5) << dataRecord.id << setw((dataRecord.name).length()) << dataRecord.name << endl;
}
int main()
{
    CsvIO *c = new CsvIO("test.csv");

    Double_list<DataRecord> dataTable;
    c->read(dataTable);

    DataRecord sample;
    sample.id = "12";
    sample.name = "Mix Kor Ban";
    dataTable.push_back(sample);


    deleteRecord(dataTable, "2");
    c->write(dataTable);
    try {
        DataRecord target = search(dataTable, "1234567"); 
        printRecord(target);
    } catch(const char* e) {
        cout << e << endl;
    }

    //c->print_info(dataTable); 

    return 0;
}