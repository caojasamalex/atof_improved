#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Record;
class Summary;
bool isRegular(const string&);
bool isLeap(const int&);
bool regularDate(const int&, const int&, const int&);
double atof_improved(const string&);
void separateDate(vector<Record>&, string, const int&);
void separate(vector<Record>&, stringstream&, int&);
void transferValues(vector<Record>&, vector<Summary>&);
void outputValues(vector<Summary>&);

class Summary{
    private:
        string name{};
        int year{};
        int i{};
        double sum{};

    public:

        string setName(const string &str){ return name = str; }
        
        int addI(){ return i += 1; }
        double addSum(const double &val){ return sum += val; }

        string getName(){ return name; }
        int getI(){ return i; }
        double getSum(){ return sum; }

        Summary(){
            name = "";
            year = 2022;
            i = 0;
            sum = 0.0;
        }
};

class Record{
    private:
        string date{}, comment{};
        double value{};
    
    public:

        int day{}, month{}, year{};

        string setDate(const string &str){ return date = str; }
        string setComment(const string &str){ return comment = str; }
        double setValue(const double &val){ return value = val; }

        string getDateStr(){ return date; }
        string getComment(){ return comment; }
        double getValue(){ return value; }

        int setDay(const int &val){ return day = val; }
        int setMonth(const int &val){ return month = val; }
        int setYear(const int &val){ return year = val; }

        int getDay() { return day; }
        int getMonth() { return month; }
        int getYear() { return year; }
};

int main(){

    ifstream inputfile("input.csv");
    if(!inputfile.is_open()) throw runtime_error("Error ocurred while opening the file"); // Checking if the file is opened or there was error while opening
    ofstream errorout ("output.err");
    if(!errorout.is_open()) throw runtime_error("Error ocurred while opening the file");
    
    vector<Record> merenja{}; // Vector of objects from record structure
    int i{0};
    string line{};

    getline(inputfile,line); // Skipping first line of a CSV file (Header)
    while(getline(inputfile,line)){
        merenja.push_back(Record());
        stringstream ss(line);
        separate(merenja,ss,i);
        separateDate(merenja,merenja[i].getDateStr(),i);
        i++;
    }

    vector<Summary> allSummary{};
    allSummary.resize(12);
    int test{0};
    for(string s:{"Januar","Februar","Mart","April","Maj","Jun","Jul","Avgust","Septembar","Oktobar","Novembar","Decembar"}){
        allSummary[test].setName(s);
        test++;
    }

    transferValues(merenja,allSummary);
    outputValues(allSummary);
    inputfile.close();
    errorout.close();
    return 1;
}

bool isRegular(const string &str){
    for(int jot{0}; jot<str.length();jot++){
        if((str[jot] >= 48 && str[jot] < 58) || tolower(str[jot]) == 'e' || str[jot] == '+' || str[jot] == '-' || str[jot] == '.')
        {
            continue;
        } else {
            return 0;
        }
    }
    return 1;
}

bool isLeap(const int &year){
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
        return 1;
    } else {
        return 0;
    }
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

    // Function that converts string value and returns double value.
    // Should implement check if the number is regular in this code snippet.

    double value{}, power{};
    int i{}, sign{}, expsign{}, exp{};
    string esign{};
    
    while(isspace(str[i])){
        i++;
    }
    
    sign = (str[i] == '-') ? -1 : 1;

    if(str[i] == '-')
        i++;

    for(value = 0.0; isdigit(str[i]); i++){
        value = value * 10.0 + (str[i] - '0');
    }
        
    if(str[i] == '.') 
        i++;

    for(power = 1.0; isdigit(str[i]); i++){
        value = value * 10.0 + (str[i] - '0');
        power *= 10.0;
    }

    if(tolower(str[i]) == 'e') i++;

    if(str[i] == '+' || str[i] == '-')
    {
        esign = str[i];
        i++;
    }

    for(exp = 0; isdigit(str[i]); i++){
        exp = exp * 10.0 + (str[i] - '0');
    }

    if(expsign == '-'){
        return sign * (value / power) / pow(10,exp);
    } else {
        return sign * (value / power) * pow(10,exp);
    }
}

void separate(vector<Record> &records, stringstream &line, int &pos) {

    // Function that reads one line of a CSV file, separates that line into 3 pieces and stores it into suitable variables.
    ofstream errorout;
    errorout.open("output.err",ios_base::app);
    if(!errorout.is_open()) throw runtime_error("Error ocurred while opening the file");
    string a{},b{},c{};
    
    getline(line,a,',');
    getline(line,b,',');
    getline(line,c,',');

    if(!isRegular(b)){
        char delimiter{};

        if(a.find('/') != string::npos){
            delimiter = '/';
        } else if(a.find('.') != string::npos){
            delimiter = '.';
        }
        stringstream ss(a);
        string temp1{},temp2{},temp3{};

        getline(ss,temp1,delimiter);
        getline(ss,temp2,delimiter);
        getline(ss,temp3,delimiter);

        errorout << "Line " << pos+2 << " cannot be converted into a number. Original value " << b << ", date " << temp1 << "." << temp2 << "." << temp3 << "." << endl;
    } else {
        records[pos].setDate(a);
        records[pos].setValue(atof_improved(b));
        records[pos].setComment(c);
    }
}

void separateDate(vector<Record> &records, string str, const int &pos){
    stringstream strs(str);
    char delimiter{}; string temp{};
    int i{0};

    if(str.find('/') != string::npos){
        delimiter = '/';
    } else if(str.find('.') != string::npos){
        delimiter = '.';
    }

    while(getline(strs,temp,delimiter)){
        switch(i){
            case 0:
                records[pos].setDay(stoi(temp));
                break;
            case 1:
                records[pos].setMonth(stoi(temp));
                break;
            case 2:
                records[pos].setYear(stoi(temp));
                break;
        }
        i++;
    }
}

void transferValues(vector<Record> &rec, vector<Summary> &summ){
    for(int num{0}; num < rec.size(); num++){
        int day = rec[num].getDay();
        int month = rec[num].getMonth();
        int year = rec[num].getYear();
        if(regularDate(day,month,year)){
            summ[month-1].addSum(rec[num].getValue());
            summ[month-1].addI();
        }
    }
}

void outputValues(vector<Summary> &summ){
    
    ofstream output("output.csv");
    if(!output.is_open()) throw runtime_error("Error ocurred while opening the file");

    output << "Mesec,Godina,UkupnoMerenja,Suma" << endl;

    for(int i = 0; i < 12; i ++){
        int records = summ[i].getI();

        if(records > 0){
            output << summ[i].getName() << ",2022," << summ[i].getI() << "," << fixed << setprecision(2) << summ[i].getSum() << endl;
        }
    }

    output.close();
}