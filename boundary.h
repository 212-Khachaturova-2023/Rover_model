#include "control.h"

class Boundary {
    string log_file_name; //variable for log file for boundary class
    ifstream bound_config_file; //open for reading
    ofstream bound_log_file; //open for writing
    bool is_log = false; //variable for defining if log fie had been opened
    bool is_surface = false; //variable for defining if surface was generated
    bool is_counted = false; //variable for defining if all elements of the surface were set
    bool is_date; //variable for defining whether to write time and date
    int is_rand = 0; //variable for counting objects set on surface
    string buff;
    Control controller;

public:
    //class Boundary constructor
    Boundary() {
        read_config();
    };
    //function for reading configuration file
    bool read_config();
};