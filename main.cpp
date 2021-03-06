#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include "src/Record.h"
#include "src/Summary.h"

using namespace std;

bool isRegular(const string&);
bool isLeap(const int&);
bool regularDate(const int&, const int&, const int&);
double atof_improved(const string&);
double calculateExp(string);
double convert(string);
void separateDate(vector<Record>&, string, const int&);
void separate(vector<Record>&, stringstream&, int&);
void transferValues(vector<Record>&, vector<Summary>&);
void outputValues(vector<Summary>&);

int main(){
    ifstream inputfile("input.csv");
    if(!inputfile.is_open()) throw runtime_error("Error ocurred while opening the file"); // Checking if the file is opened or there was error while opening
    ofstream errorout ("output.err");
    if(!errorout.is_open()) throw runtime_error("Error ocurred while opening the file");  // Checking if the file is opened or there was error while opening
    
    vector<Record> merenja{};       // Vector of objects from record structure
    int i{0};
    string line{};

    getline(inputfile,line);        // Skipping first line of a CSV file (Header)
    while(getline(inputfile,line)){
        // Gets one line of input file until the end of file
        merenja.push_back(Record());
        stringstream ss(line);
        separate(merenja,ss,i);     // Calling function for separation of read line
        i++;
    }

    vector<Summary> allSummary{};
    allSummary.resize(12);
    int test{0};
    for(string s:{"Januar","Februar","Mart","April","Maj","Jun","Jul","Avgust","Septembar","Oktobar","Novembar","Decembar"}){
        allSummary[test].setName(s);
        test++;
    }

    transferValues(merenja,allSummary); // Calling function for transfering values from records to summary vetor
    outputValues(allSummary);           // Calling function for ouptputing values
    inputfile.close();                  // Closing file
    errorout.close();                   // Closing file
    return 1;
}

bool isRegular(const string &str){
    for(int jot{0}; jot<str.length();jot++){
        if(!((str[jot] >= 48 && str[jot] < 58) || tolower(str[jot]) == 'e' || str[jot] == '+' || str[jot] == '-' || str[jot] == '.'))
        {
            // Checks if the character is allowed, if not it breaks loop and returns 0 value.
            return 0;
        }
    }
    // if the program came to the end of the loop and not returned false value it means that the string has only allowed characters so it returns value of true.
    return 1;
}

bool isLeap(const int &year){
    return((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

bool regularDate(const int &day, const int &month, const int &year){
    vector<int> thirthyOnes = {1,3,5,7,8,10,12};
    vector<int> thirthy = {4,6,9,11};
    int feb = 2;

    if(month == feb && isLeap(year) && day > 0 && day <= 29){
        return 1;
    } else if (month == feb && !isLeap(year) && day > 0 && day <= 28){
        return 1;
    } else {
        for(int i: thirthyOnes){
            if(month == i && day > 0 && day <= 31){
                return 1;
            }
        }

        for(int i: thirthy){
            if(month == i && day > 0 && day <= 30){
                return 1;
            }
        }
    }
    return 0;
}

double atof_improved(const string &str){

    stringstream ss(str);
    double base{};
    if(str.find('e') == string::npos){
        base = convert(str);
    } else {
        string baseStr{}, expStr{};
        getline(ss,baseStr,'e');
        getline(ss,expStr);

        base = convert(baseStr) * calculateExp(expStr);
    }
    return base;
}

double calculateExp(string str){
    double exp{1};

    if(str[0] == '-'){
        str.erase(0,1);
        exp *= pow(0.1,convert(str));
    } else {
        exp *= pow(10,convert(str));
    }
    return exp;
}

double convert(string str){
    int sign{}, pos{0}; // Sign of number and position of decimal point
    double converted{};

    if(str[0] == '-'){
        sign = -1;
        str.erase(0,1);
    } else if(str[0] == '+'){
        sign = 1;
        str.erase(0,1);
    } else {
        sign = 1;
    }
    for(int i=0; i<str.length();i++){
        if(str[i] == '.'){
            pos = i + 1;
        } else {
            converted = 10 * converted + (str[i] - '0');
        }
    }

    if(pos > 0){
        converted *= pow(0.1,str.length() - pos);
    }

    return sign * converted;
}

void separate(vector<Record> &records, stringstream &line, int &pos) {

    ofstream errorout;
    errorout.open("output.err",ios_base::app);
    if(!errorout.is_open()) throw runtime_error("Error ocurred while opening the file");
    string a{},b{},c{};
    
    getline(line,a,',');
    getline(line,b,',');
    getline(line,c,',');

    char delimiter{};

    if(a.find('/') != string::npos){
        // If '/' is found in date, '/' is delimiter
        delimiter = '/';
    } else if(a.find('.') != string::npos){
        // If '.' is found in date, '.' is delimiter
        delimiter = '.';
    }
    stringstream ss(a);
    string temp1{},temp2{},temp3{};

    getline(ss,temp1,delimiter); // Separating first part of stringstream and stores it to a temp1 string (Day)
    getline(ss,temp2,delimiter); // Separating second part of stringstream and stores it to a temp2 string (Month)
    getline(ss,temp3,delimiter); // Separating third part of stringstream and stores it to a temp3 string (Year)

    if(!isRegular(b)){
        // Calling function to check content of string. If function returns false, that means that there is not allowed characters inside of b.
        errorout << "Line " << pos+2 << " cannot be converted into a number. Original value " << b << ", date " << temp1 << "." << temp2 << "." << temp3 << "." << endl;
    } else {
        // If function returns false, b is contained only of allowed characters. Now we need to forward suitable values to a suitable variables.
        records[pos].setDate(a);
        records[pos].setValue(atof_improved(b));
        records[pos].setComment(c);
        records[pos].setDay(stoi(temp1));
        records[pos].setMonth(stoi(temp2));
        records[pos].setYear(stoi(temp3));
    }
}

void transferValues(vector<Record> &rec, vector<Summary> &summ){
    
    // Getting two vectors, first vector from record objects, second vector from summary objects.
    // After that in for loop we are declaring values from records to summary.

    for(int num{0}; num < rec.size(); num++){
        int day = rec[num].getDay();
        int month = rec[num].getMonth();
        int year = rec[num].getYear();
        if(regularDate(day,month,year) && year == 2022){
            summ[month-1].addSum(rec[num].getValue());
            summ[month-1].addI();
        }
    }
}

void outputValues(vector<Summary> &summ){
    //
    //  We need to open file for output and we need to output all objects that have 1 or more records.
    //
    ofstream output("output.csv");
    if(!output.is_open()) throw runtime_error("Error ocurred while opening the file");

    output << "Mesec,Godina,UkupnoMerenja,Suma" << endl;

    for(int i = 0; i < 12; i ++){
        if(summ[i].getI() > 0){
            output << summ[i].getName() << ",2022," << summ[i].getI() << "," << fixed << setprecision(2) << summ[i].getSum() << endl;
        }
    }

    output.close();
}