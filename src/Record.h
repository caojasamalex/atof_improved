#ifndef _RECORD_H_
#define _RECORD_H_

#include <string>

class Record{
    private:
        std::string date{}, comment{};
        double value{};
        int day{}, month{}, year{};

    public:
        void setDate(const std::string &str){ date = str; }
        void setComment(const std::string &str){ comment = str; }
        void setValue(const double &val){ value = val; }

        std::string getDateStr(){ return date; }
        std::string getComment(){ return comment; }
        double getValue(){ return value; }

        void setDay(const int &val){ day = val; }
        void setMonth(const int &val){ month = val; }
        void setYear(const int &val){ year = val; }

        int getDay() { return day; }
        int getMonth() { return month; }
        int getYear() { return year; }

        Record(std::string d = "", std::string com = "", double val = 0, int defDay = 0, int defMonth = 0, int defYear = 2022)
            : date{d}, comment{com}, value{val}, day{defDay}, month{defMonth}, year{defYear} {
            }

        ~Record(){
            std::cout << "Destructor called" << std::endl;
        }
};

#endif