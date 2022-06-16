#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct record {
    string date;
    string first_value;
    string comment;
    double value;
};

double atof_improved(const string&);

void separate(vector<record> &merenja, stringstream &line, const int &pos) {

    // Function that reads one line of a CSV file, separates that line into 3 pieces and stores it into suitable variables

    string a{};
    int i{0};

    while(getline(line,a,',')){
        switch (i){
            case 0:
                merenja[pos].date = a;
                break;
            case 1:
                merenja[pos].first_value = a;
            case 2:
                merenja[pos].comment = a;
        }
        i++;
    }
}

int main(){

    ifstream inputfile("input.csv");
    if(!inputfile.is_open()) throw runtime_error("Error ocurred while opening the file"); // Checking if the file is opened or there was error while opening

    vector<record> merenja{}; // Vector of objects from record structure
    merenja.push_back(record());
    int i{0};
    string line{};

    getline(inputfile,line); // Skipping first line of a CSV file (Header)
    while(getline(inputfile,line)){
        stringstream ss(line);
        separate(merenja,ss,i);
        i++;
    }

    for(int j{0}; j<i; j++){
        cout << merenja[j].date << "\t" << merenja[j].first_value << "\t" << merenja[j].comment << endl;
    }

    cout << "\nTest: " << merenja[2].first_value << endl;

    inputfile.close();
    return 0;
}