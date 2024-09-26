#include "functions.h"
class Point {
    friend class Surface;
private:
    double x, y, z;
public:
    Point(double x0 = 0, double y0 = 0, double z0 = 0) {
        x = x0, y = y0, z = z0;
    }
};

class Hill {
    friend class Surface;
private:
    double x_cord;
    double y_cord;
    double z_cord;
    double sig_y_c, sig_x_c;
    double angle_c;
public:
    //class Hill constructor
    Hill(double x = 0, double y = 0, double z = 0, double sig_x = 1, double sig_y = 1, double angle = 0);
    //function returns z coordinate (height) of the Gauss equation in the given point (x0, y0)
    double hill_height(double x0, double y0);
};

class Stone {
    friend class Surface;
private:
    double x_cord;
    double y_cord;
    double r_st;
public:
    //class Stone constructor
    Stone(double x = 0.0, double y = 0, double r_st = 0);
    //function returns z coordinate (height) of the sphere equation in the given point (x0, y0)
    double stone_height(double x0 = 0.0, double y0 = 0.0);
};

class Beam {
    friend class Surface;
private:
    double x1_cord;
    double x2_cord;
    double y1_cord;
    double y2_cord;
    double beam_rad;
public:
    //class Beam constructor
    Beam(double x1 = 0.0, double y1 = 0.0, double x2 = 0.0, double y2 = 0.0, double radius = 0.0);
    //function returns z coordinate (height) of the beam in the given point (x0, y0)
    double beam_height(double x = 0.0, double y = 0.0);
};

class Cursor {
    friend class Control;
private:
    double x_cord;
    double y_cord;
public:
    //class Cursor constructor
    Cursor(double x = 0, double y = 0);
};