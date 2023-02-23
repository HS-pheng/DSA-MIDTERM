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

    void addRecord(string id, string title, string author, string genre, string publishDate)
    {
        DataRecord sample;
        sample.id = id;
        sample.title = title;
        sample.author = author;
        sample.genre = genre;
        sample.publishDate = publishDate;
        dataTable.push_back(sample);
    }
    // print the record that has been searched by ID, take ID as parameter
    void printRecord(string id)
    {
        DataRecord dataRecord = findRecord(id);

        cout << left << setfill('-') << setw(5) << "+" << setw((dataRecord.id).length() + 5) << "-" << setw(5) << "+" << setw((dataRecord.title).length() + 5) << "-" << setw(5) << "+";
        cout << left << setw((dataRecord.author).length() + 5) << "-" << setw(5) << "+";
        cout << left << setw((dataRecord.genre).length() + 5) << "-" << setw(5) << "+" << setw((dataRecord.publishDate).length() + 5) << "-" << right << setw(5) << "+" << endl;

        cout << left << setfill(' ') << setw(5) << "|" << setw((dataRecord.id).length() + 5) << "ID" << setw(5) << "|" << setw((dataRecord.title).length() + 5) << "Name" << setw(5) << "|";
        cout << left << setw((dataRecord.author).length() + 5) << "Author" << setw(5) << "|";
        cout << left << setw((dataRecord.genre).length() + 5) << "Genre" << setw(5) << "|" << setw((dataRecord.publishDate).length() + 5) << "Publish Date" << right << setw(5) << "|" << endl;

        cout << left << setfill('-') << setw(5) << "+" << setw((dataRecord.id).length() + 5) << "-" << setw(5) << "+" << setw((dataRecord.title).length() + 5) << "-" << setw(5) << "+";
        cout << left << setw((dataRecord.author).length() + 5) << "-" << setw(5) << "+";
        cout << left << setw((dataRecord.genre).length() + 5) << "-" << setw(5) << "+" << setw((dataRecord.publishDate).length() + 5) << "-" << right << setw(5) << "+" << endl;

        cout << left << setfill(' ') << setw(5) << "|" << setw((dataRecord.id).length() + 5) << dataRecord.id << setw(5) << "|" << setw((dataRecord.title).length() + 5) << dataRecord.title << setw(5) << "|";
        cout << left << setw((dataRecord.author).length() + 5) << dataRecord.author << setw(5) << "|";
        cout << left << setw((dataRecord.genre).length() + 5) << dataRecord.genre << setw(5) << "|" << setw((dataRecord.publishDate).length() + 5) << dataRecord.publishDate << right << setw(5) << "|" << endl;

        cout << left << setfill('-') << setw(5) << "+" << setw((dataRecord.id).length() + 5) << "-" << setw(5) << "+" << setw((dataRecord.title).length() + 5) << "-" << setw(5) << "+";
        cout << left << setw((dataRecord.author).length() + 5) << "-" << setw(5) << "+";
        cout << left << setw((dataRecord.genre).length() + 5) << "-" << setw(5) << "+" << setw((dataRecord.publishDate).length() + 5) << "-" << right << setw(5) << "+" << endl;
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

    void updateRecordAll(string id, string title, string author, string genre, string publishDate)
    {
        deleteRecord(id);
        addRecord(id, title, author, genre, publishDate);
    }

    void updateRecordTitle(string id, string title)
    {
        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            if ((trav->data).id != id)
                continue;
            trav->data.title = title;
        }
        cout << "Successfully modify title to: " << title << endl;
        printRecord(id);
        close();
    }

    void updateRecordGenre(string id, string genre)
    {
         for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            if ((trav->data).id != id)
                continue;
            trav->data.genre = genre;
        }
        cout << "Successfully modify genre to: " << genre << endl;
        printRecord(id);
        close();
    }

    void updateRecordPublishDate(string id, string publishDate)
    {
         for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            if ((trav->data).id != id)
                continue;
            trav->data.publishDate = publishDate;
        }
        cout << "Successfully modify publishDate to: " << publishDate << endl;
        printRecord(id);
        close();
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

    void close() // close and write into csv file
    {
        csvio->write(dataTable);
    }

    void searchById(string id)
    {
        // try printing record, if it null, then throw error
        try
        {
            this->printRecord(id);
        }
        catch (const char *err)
        {
            cout << err << endl;
            system("read");
        }
    }

    void printTable()
    {
        int max_width[] = {5, 5, 5, 5, 10};

        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            max_width[0] = (max_width[0] > (trav->data).id.length()) ? max_width[0] : (trav->data).id.length();
        }

        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            max_width[1] = (max_width[1] > (trav->data).title.length()) ? max_width[1] : (trav->data).title.length();
        }

        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            max_width[2] = (max_width[2] > (trav->data).author.length()) ? max_width[2] : (trav->data).author.length();
        }

        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            max_width[3] = (max_width[3] > (trav->data).genre.length()) ? max_width[3] : (trav->data).genre.length();
        }

        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            max_width[4] = (max_width[4] > (trav->data).publishDate.length()) ? max_width[4] : (trav->data).publishDate.length();
        }
        cout << endl;
        for (int i = 0; i < 5; i++)
            max_width[i] += 5;
            
        cout << left << setfill('-') << setw(5) << "+" << setw(max_width[0]) << "-" << setw(5) << "+" << setw(max_width[1]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[2]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[3]) << "-" << setw(5) << "+" << setw(max_width[4]) << "-" << right << setw(5) << "+" << endl;

        cout << left << setfill(' ') << setw(5) << "|"  << setw(max_width[0]) << "ID" << setw(5) << "|" << setw(max_width[1]) << "Title" << setw(5) << "|";
        cout << left << setw(max_width[2]) << "Author" << setw(5) << "|";
        cout << left << setw(max_width[3]) << "Genre" << setw(5) << "|" << setw(max_width[4]) << "Publish Date" << right << setw(5) << "|" << endl;

        cout << left << setfill('-') << setw(5) << "+" << setw(max_width[0]) << "-" << setw(5) << "+" << setw(max_width[1]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[2]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[3]) << "-" << setw(5) << "+" << setw(max_width[4]) << "-" << right << setw(5) << "+" << endl;

        if (dataTable.size() == 0){
            cout << "No Data Found!" << endl;
        } 

        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            cout << left << setfill(' ') << setw(5) << "|" << setw(max_width[0]) << (trav->data).id << setw(5) << "|" << setw(max_width[1]) << (trav->data).title << setw(5) << "|";
            cout << left << setw(max_width[2]) << (trav->data).author << setw(5) << "|";
            cout << left << setw(max_width[3]) << (trav->data).genre << setw(5) << "|" << setw(max_width[4]) << (trav->data).publishDate << right << setw(5) << "|" << endl;

        }
        cout << left << setfill('-') << setw(5) << "+" << setw(max_width[0]) << "-" << setw(5) << "+" << setw(max_width[1]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[2]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[3]) << "-" << setw(5) << "+" << setw(max_width[4]) << "-"  << right << setw(5) << "+" << endl;

        cout << left << setfill(' ') << setw(5) << "|"  << setw(max_width[0]) << "Total" << setw(5) << " " << setw(max_width[1]) << to_string(dataTable.list_size) + " records" << setw(5) << " ";
        cout << left << setw(max_width[2]) << " " << setw(5) << " ";
        cout << left << setw(max_width[3]) << " " << setw(5) << " " << setw(max_width[4]) << " " << right << setw(5) << "|" << endl;

        
        cout << left << setfill('-') << setw(5) << "+" << setw(max_width[0]) << "-" << setw(5) << "+" << setw(max_width[1]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[2]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[3]) << "-" << setw(5) << "+" << setw(max_width[4]) << "-"  << right << setw(5) << "+" << endl;

        system("read");
    }

    void sort(string sortedBy, string orderBy) {
        dataTable.sort(sortedBy, orderBy);
    }

    void printFilter(Double_list<DataRecord> filterRecord) {
        int max_width[] = {5, 5, 5, 5, 10};

        for (Double_Node<DataRecord> *trav = filterRecord.head(); trav != NULL; trav = trav->next)
        {
            max_width[0] = (max_width[0] > (trav->data).id.length()) ? max_width[0] : (trav->data).id.length();
        }

        for (Double_Node<DataRecord> *trav = filterRecord.head(); trav != NULL; trav = trav->next)
        {
            max_width[1] = (max_width[1] > (trav->data).title.length()) ? max_width[1] : (trav->data).title.length();
        }

        for (Double_Node<DataRecord> *trav = filterRecord.head(); trav != NULL; trav = trav->next)
        {
            max_width[2] = (max_width[2] > (trav->data).author.length()) ? max_width[2] : (trav->data).author.length();
        }

        for (Double_Node<DataRecord> *trav = filterRecord.head(); trav != NULL; trav = trav->next)
        {
            max_width[3] = (max_width[3] > (trav->data).genre.length()) ? max_width[3] : (trav->data).genre.length();
        }

        for (Double_Node<DataRecord> *trav = filterRecord.head(); trav != NULL; trav = trav->next)
        {
            max_width[4] = (max_width[4] > (trav->data).publishDate.length()) ? max_width[4] : (trav->data).publishDate.length();
        }
        cout << endl;
        for (int i = 0; i < 5; i++)
            max_width[i] += 5;
            
        cout << left << setfill('-') << setw(5) << "+" << setw(max_width[0]) << "-" << setw(5) << "+" << setw(max_width[1]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[2]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[3]) << "-" << setw(5) << "+" << setw(max_width[4]) << "-" << right << setw(5) << "+" << endl;

        cout << left << setfill(' ') << setw(5) << "|"  << setw(max_width[0]) << "ID" << setw(5) << "|" << setw(max_width[1]) << "Title" << setw(5) << "|";
        cout << left << setw(max_width[2]) << "Author" << setw(5) << "|";
        cout << left << setw(max_width[3]) << "Genre" << setw(5) << "|" << setw(max_width[4]) << "Publish Date" << right << setw(5) << "|" << endl;

        cout << left << setfill('-') << setw(5) << "+" << setw(max_width[0]) << "-" << setw(5) << "+" << setw(max_width[1]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[2]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[3]) << "-" << setw(5) << "+" << setw(max_width[4]) << "-" << right << setw(5) << "+" << endl;

        if (filterRecord.size() == 0){
            cout << "No Data Found!" << endl;
        } 

        for (Double_Node<DataRecord> *trav = filterRecord.head(); trav != NULL; trav = trav->next)
        {
            cout << left << setfill(' ') << setw(5) << "|" << setw(max_width[0]) << (trav->data).id << setw(5) << "|" << setw(max_width[1]) << (trav->data).title << setw(5) << "|";
            cout << left << setw(max_width[2]) << (trav->data).author << setw(5) << "|";
            cout << left << setw(max_width[3]) << (trav->data).genre << setw(5) << "|" << setw(max_width[4]) << (trav->data).publishDate << right << setw(5) << "|" << endl;

        }
        cout << left << setfill('-') << setw(5) << "+" << setw(max_width[0]) << "-" << setw(5) << "+" << setw(max_width[1]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[2]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[3]) << "-" << setw(5) << "+" << setw(max_width[4]) << "-"  << right << setw(5) << "+" << endl;

        cout << left << setfill(' ') << setw(5) << "|"  << setw(max_width[0]) << "Total" << setw(5) << " " << setw(max_width[1]) << to_string(filterRecord.list_size) + " records" << setw(5) << " ";
        cout << left << setw(max_width[2]) << " " << setw(5) << " ";
        cout << left << setw(max_width[3]) << " " << setw(5) << " " << setw(max_width[4]) << " " << right << setw(5) << "|" << endl;

        
        cout << left << setfill('-') << setw(5) << "+" << setw(max_width[0]) << "-" << setw(5) << "+" << setw(max_width[1]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[2]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[3]) << "-" << setw(5) << "+" << setw(max_width[4]) << "-"  << right << setw(5) << "+" << endl;

        system("read");
    }

    void filterByGenre(string genre) {
        Double_list<DataRecord> filterRecord;

        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            if (((trav->data).genre).find(genre) != string::npos) filterRecord.push_back(trav->data);  
        }
        cout << "Filter by Genre: " << genre << endl;
        printFilter(filterRecord);

    }

    void filterByPublishDate(string publishYear){
        Double_list<DataRecord> filterRecord;

        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            if (((trav->data).publishDate).find(publishYear) != string::npos){
                filterRecord.push_back(trav->data);  
            }
        }
        cout << "Filter by Publish Year: " << publishYear << endl;
        printFilter(filterRecord);
    }

    void filterByAuthor(string author){
        Double_list<DataRecord> filterRecord;

        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            if (((trav->data).author).find(author) != string::npos) filterRecord.push_back(trav->data);  
        }
        cout << "Filter by Author: " << author << endl;
        printFilter(filterRecord);
    }
};
