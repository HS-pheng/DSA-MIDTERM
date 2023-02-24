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
            string a, b, author, c, d;
            getline(ss, a, ',');
            getline(ss, b, ',');
            getline(ss, author, ',');
            getline(ss, c, ',');
            getline(ss, d, ',');
            record.id = a;
            record.title = b;
            record.author = author;
            record.genre = c;
            record.publishDate = d;

            dataTable.push_back(record);
        }
    }

    void write(Double_list<DataRecord> lm)
    {
        ofstream fout(fileName);
        fout << "id,title,author,genre,publishDate\n";

        for (Double_Node<DataRecord> *trav = lm.head(); trav != NULL; trav = trav->next)
        {
            fout << (trav->data).id << ',' << (trav->data).title << ',' << (trav->data).author << ',';
            fout << (trav->data).genre << ',' << (trav->data).publishDate << "\n";
        }
    }
};