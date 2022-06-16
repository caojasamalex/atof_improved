#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct record {
    string date;
    string first_value;
    double value;
    string comment;
};

int main(){

    fstream inputfile;
    inputfile.open("input.csv",ios::in);

    if(!inputfile.is_open()) throw runtime_error("Error ocurred while opening the file");

    vector<record> merenja{};

    
}