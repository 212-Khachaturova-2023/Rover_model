#include "functions.h"
#include "elements.h"

class Point
{
    friend class Surface;
    friend class Rover;
    friend class Control;
protected:
    double x_cord;
    double y_cord;
    double z_cord;
public:
    Point(const double& x = 0, const double& y = 0, const double& z = 0) {
        x_cord = x, y_cord = y, z_cord = z;
    };
};

class Surface {
    friend class Rover;
    friend class Beam;
    friend class Stone;
    friend class Hill;
    friend class Control;
    double length;
    double width;
    double unevenness_degree;
    vector <Hill> hills;
    vector <Stone> stones;
    vector <Beam> beams;
    Cursor cursor;
    Point** points;
public:
    Surface(const double& surf_len = 10, const double& surf_wid = 10, const double& surf_uneven = 0.1);
    ~Surface();
    double get_surface_height(const double& x, const double& y);
    void Print_in_file(ofstream& file);
    void count_surface();
    bool add_hill(const double& x = 0.0, const double& y = 0.0, const double& z = 0.0, const double& sig_x = 1.0, const double& sig_y = 1.0, const double& ax_rotat_angle = 0);
    bool add_stone(const double& x = 0.0, const double& y = 0.0, const double& radius = 0);
    bool add_beam(const double& x1 = 0.0, const double& y1 = 0.0, const double& x2 = 0.0, const double& y2 = 0.0, const double& radius = 0.0);
};