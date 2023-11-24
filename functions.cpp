#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"

double get_random(double min, double max) {
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

bool is_extra_symbol_after_semicolon(string str) {
    size_t pos = str.find(";");
    //string::npos - value returning when substring isn't found
    //if symbol ";" was found
    if (pos != std::string::npos) {
        //getting substring after ";"
        string substr = str.substr(pos + 1);
        //checking if there are special symbols after ";"
        if (substr.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
            return true;
        }
        else return false;
    }
    else return false;
}

bool is_substr(string str, string substr) {
    return (str.find(substr) != string::npos);
}

void time_print(string message, ofstream& file) {
    auto now = chrono::system_clock::now(); //getting current time using system clock
    time_t end_time = chrono::system_clock::to_time_t(now);
    file << message << ctime(&end_time); //ctime converts time format to string
}