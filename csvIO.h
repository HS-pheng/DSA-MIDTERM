#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <map>
#include <iomanip>


class CsvIO {
    private:
        string fileName;

    public:
        CsvIO(string fileName) {
            this->fileName = fileName;
        }

        list<map<string, string> > read() {
            list<map<string, string> > vm;
            bool isHeaderLine = true;

            vector<string> fieldNames;
            string line;
            ifstream fin(fileName);
            while(getline(fin, line)) {
                stringstream ss(line);
                string fieldValue;

                if (isHeaderLine) {
                    while(getline(ss, fieldValue, ',')) {
                        fieldNames.push_back(fieldValue);
                    }
                    isHeaderLine = false;
                    continue;
                }

                map<string, string> tm;
                for (string fieldName: fieldNames) {
                    getline(ss, tm[fieldName], ',');
                }

                vm.push_back(tm);
            }
            return vm;
        }

        void write(list<map<string, string> > lm, vector<string> fieldsToWrite) {
            ofstream fout(fileName);
            for (auto &field : fieldsToWrite) {
                fout << field << ((&field - &fieldsToWrite[0] < fieldsToWrite.size() - 1) ? ',' : '\n');
            }
            for (auto m : lm) {
                for (int i = 0; i < fieldsToWrite.size(); i++) {
                    string &valueToWrite = m[fieldsToWrite[i]];
                    char delimiter = (i < fieldsToWrite.size() - 1) ? ',' : '\n';
                    fout << valueToWrite << delimiter;
                }
            }
        }

        void print_info(vector<string> fieldsToWrite)
        {
            list<map<string, string> > lm = this->read();

            vector<int> max_width(fieldsToWrite.size(), 5);

            for (auto m : lm) {
                for (int i = 0; i < fieldsToWrite.size(); i++) {
                    max_width[i] = ((max_width[i] > m[fieldsToWrite[i]].length()) ? max_width[i] : m[fieldsToWrite[i]].length());
                }
            }

            for (int i = 0; i < fieldsToWrite.size(); i++) {
                cout << i << ": "<< max_width[i] << endl;
            }

            max_width[0] += 6;
            max_width[1] += 7;
            max_width[2] += 5;
            cout << left << setw(max_width[0]) << "ID" << setw(max_width[1]) << "Name" << setw(15) << "Age" << endl;


            for (auto m : lm) {
                cout << left << setw(max_width[0]) << m["id"] << setw(max_width[1]) << m["name"] << setw(15) << m["age"] <<  endl; 
            }
        }
};