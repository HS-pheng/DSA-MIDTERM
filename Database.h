#include "DoubleList.h"
#include "CSV.h"
using namespace std;
class Database
{
private:
    Double_list<DataRecord> dataTable;
    CsvIO *csvio;

public:
    Database(string baseFile)
    {
        csvio = new CsvIO(baseFile);
        csvio->read(dataTable);
    }

    void printTable()
    {
        this->csvio->print_info(this->dataTable);
        system("read");
    }

    void addRecord(string id, string title, string genre, string publishDate)
    {
        DataRecord sample;
        sample.id = id;
        sample.title = title;
        sample.genre = genre;
        sample.publishDate = publishDate;
        dataTable.push_back(sample);
    }
    // print the record that has been searched by ID, take ID as parameter
    void printRecord(string id)
    {
        DataRecord dataRecord = findRecord(id);
        cout << left << setw((dataRecord.id).length() + 5) << "ID" << setw((dataRecord.title).length() + 5) << "Title";
        cout << left << setw((dataRecord.genre).length() + 5) << "Genre" << setw((dataRecord.publishDate).length() + 5) << "Publish Date" << endl;

        cout << left << setw((dataRecord.id).length() + 5) << dataRecord.id << setw((dataRecord.title).length()) << dataRecord.title;
        cout << left << setw((dataRecord.genre).length() + 5) << dataRecord.genre << setw((dataRecord.publishDate).length()) << dataRecord.publishDate << endl;
        system("read");
    }

    DataRecord findRecord(string id)
    {
        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            if ((trav->data).id != id)
                continue;

            return (trav->data);
        }
        throw "Not found";
    }

    bool deleteRecord(string id)
    {
        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            if ((trav->data).id != id)
            {
                continue;
            }

            if (dataTable.size() == 1)
            {
                delete (trav);
                dataTable.list_head = dataTable.list_tail = NULL;
                return true;
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
                return true;
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
                return true;
            }

            temp_next->prev = temp_prev;
            temp_prev->next = temp_next;
            delete (trav);
            return true;
        }
        return false;
    }

    void close()
    {
        csvio->write(dataTable);
    }
};

