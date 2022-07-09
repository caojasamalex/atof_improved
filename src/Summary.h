#ifndef _SUMMARY_H_
#define _SUMMARY_H_

#include <string>

class Summary{
    private:
        std::string name{};
        int year{}, i{};
        double sum{};

    public:

        std::string setName(const std::string &str){ return name = str; }
        
        int addI(){ return i += 1; }
        double addSum(const double &val){ return sum += val; }

        std::string getName(){ return name; }
        int getI(){ return i; }
        double getSum(){ return sum; }

        Summary(std::string n = "", int y = 2022, int iterator = 0, double defSum = 0.0)
            : name{n}, year{y}, i{iterator}, sum{defSum} {
            }

        ~Summary(){
        }
};
#endif