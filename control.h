#include "surface.h"

class Control {
private:
    ofstream cntrl_log_file; //log file for control class
    ofstream gnu; //file with points for gnuplot to open
    Surface surf;
    bool is_date_at_log = true; //variable for defining whether to write date and time
    Cursor cntrl_cursor;
public:
    //class Control constructor
    Control(string gnu_filename = "Gnuplot.txt") {
        _max_rand_hills = 0;
        _max_rand_beams = 0;
        _max_rand_stones = 0;
        cntrl_log_file.open("Log_control.txt");
        gnu.open(gnu_filename);
    }

    //function defines surface 
    bool create_surface(double surf_length, double surf_width, double surf_unevennes);

    //function defines cntrl_cursor
    bool set_cursor(double x, double y);

    //function defines _max_rand_hills
    bool set_random_hills(size_t num);

    //function defines _max_rand_stones
    bool set_random_stones(size_t num);

    //function defines _max_rand_beams
    bool set_random_beams(size_t num);

    //function runs function surf.add_hill(cntrl_cursor.x_cord, cntrl_cursor.y_cord, height, sigma_x, sigma_y);
    bool create_hill(double height, double sigma_x, double sigma_y, double angle);

    //function runs function surf.add_beam(x1, y1, x2, y2, radius);
    bool create_beam(double x1, double y1, double x2, double y2, double radius);

    //function runs function surf.add_stone(cntrl_cursor.x_cord, cntrl_cursor.y_cord, radius);
    bool create_stone(double radius);

    //function runs funcion surf.file_print(gnu);
    bool count_surface();
};