#include "functions.h"
#include "elements.h"

class Surface {
    friend class Beam;
    friend class Stone;
    friend class Hill;
    friend class Control;
private:
    double length;
    double width;
    double variance;
    vector <Hill> hills;
    vector <Stone> stones;
    vector <Beam> beams;
    Cursor cursor;
    //Point* points;
public:
    //class Surface constructor
    Surface(double surf_len = 10, double surf_wid = 10, double degree = 0.1);
    //function return sum of z coordinates of hills, stones and beams in the given point (x0, y0)
    double surface_height(double x0, double y0);
    //function prints x-, y-, z-corrdinates in the file
    //void file_print(ofstream& file);
    //function adds hills to the array of hils
    bool add_hill(double x = 0.0, double y = 0.0, double z = 0.0, double sig_x = 1.0, double sig_y = 1.0, double angle = 0);
    //function adds stones to the array of stones
    bool add_stone(double x = 0.0, double y = 0.0,double radius = 0);
    //function adds beams to te array of beams
    bool add_beam(double x1 = 0.0, double y1 = 0.0, double x2 = 0.0, double y2 = 0.0, double radius = 0.0);
};
