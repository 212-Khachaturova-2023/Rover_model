#include "functions.h"

class Hill {
    friend class Surface;
    double x;
    double y;
    double z;
    double sigma_y, sigma_x;
    double rotation_angle;
public:
    Hill(const double& x0 = 0, const double& y0 = 0, const double& z0 = 0, const double& sig_x = 1, const double& sig_y = 1, const double& ax_rotat_angle = 0);
    double get_hill_height(const double& x, const double& y);
};

class Beam {
    friend class Surface;
    double x1;
    double x2;
    double y1;
    double y2;
    double beam_rad;
public:
    Beam(const double& x1_0 = 0.0, const double& y1_0 = 0.0, const double& x2_0 = 0.0, const double& y2_0 = 0.0, const double& radius = 0.0);
    double get_beam_height(const double& x = 0.0, const double& y = 0.0);
};

class Stone
{
    friend class Surface;
    double x;
    double y;
    double radius_stone;
public:
    Stone(const double& x0 = 0.0, const double& y0 = 0, const double& radius = 0);
    double get_stone_height(const double& x = 0.0, const double& y = 0.0);
};

class Cursor {
    friend class Control;
    double x;
    double y;
public:
    Cursor(const double& x0 = 0, const double& y0 = 0);
};