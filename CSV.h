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
            string a, b, c, d;
            getline(ss, a, ',');
            getline(ss, b, ',');
            getline(ss, c, ',');
            getline(ss, d, ',');

            record.id = a;
            record.title = b;
            record.genre = c;
            record.publishDate = d;

            dataTable.push_back(record);
        }
    }

    void write(Double_list<DataRecord> lm)
    {
        ofstream fout(fileName);
        fout << "id,title,genre,publishDate\n";

        for (Double_Node<DataRecord> *trav = lm.head(); trav != NULL; trav = trav->next)
        {
            fout << (trav->data).id << ',' << (trav->data).title << ',';
            fout << (trav->data).genre << ',' << (trav->data).publishDate << "\n";
        }
    }

    void print_info(Double_list<DataRecord> dataTable)
    {
        system("cls");
        int max_width[] = {5, 5, 5, 10};

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
            max_width[2] = (max_width[2] > (trav->data).genre.length()) ? max_width[2] : (trav->data).genre.length();
        }

        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            max_width[3] = (max_width[3] > (trav->data).publishDate.length()) ? max_width[3] : (trav->data).publishDate.length();
        }
        cout << endl;
        for (int i = 0; i < 4; i++)
            max_width[i] += 5;
            
        cout << left << setfill('-') << setw(5) << "+" << setw(max_width[0]) << "-" << setw(5) << "+" << setw(max_width[1]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[2]) << "-" << setw(5) << "+" << setw(max_width[3]) << "-" << right << setw(5) << "+" << endl;

        cout << left << setfill(' ') << setw(5) << "|"  << setw(max_width[0]) << "ID" << setw(5) << "|" << setw(max_width[1]) << "Name" << setw(5) << "|";
        cout << left << setw(max_width[2]) << "Genre" << setw(5) << "|" << setw(max_width[3]) << "Publish Date" << right << setw(5) << "|" << endl;

        cout << left << setfill('-') << setw(5) << "+" << setw(max_width[0]) << "-" << setw(5) << "+" << setw(max_width[1]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[2]) << "-" << setw(5) << "+" << setw(max_width[3]) << "-" << right << setw(5) << "+" << endl;

        if (dataTable.size() == 0){
            cout << "No Data Found!" << endl;
        } 

        for (Double_Node<DataRecord> *trav = dataTable.head(); trav != NULL; trav = trav->next)
        {
            cout << left << setfill(' ') << setw(5) << "|" << setw(max_width[0]) << (trav->data).id << setw(5) << "|" << setw(max_width[1]) << (trav->data).title << setw(5) << "|";
            cout << left << setw(max_width[2]) << (trav->data).genre << setw(5) << "|" << setw(max_width[3]) << (trav->data).publishDate << right << setw(5) << "|" << endl;

        }
        cout << left << setfill('-') << setw(5) << "+" << setw(max_width[0]) << "-" << setw(5) << "+" << setw(max_width[1]) << "-" <<  setw(5) << "+";
        cout << left << setw(max_width[2]) << "-" << setw(5) << "+" << setw(max_width[3]) << "-"  << right << setw(5) << "+" << endl;
    }
};