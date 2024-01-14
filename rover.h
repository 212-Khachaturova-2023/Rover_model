#include "functions.h"
#include "Surface.h"

class Rover {
    friend class Processor;
    int direction;
    int radius_of_wheels_in_pixels;
    int straight_speed = 1;
    int type_of_crawl = 1;
    Point center_gravity_location;
    const Surface* rover_surface;
    double left_tilt, right_tilt;
    double tilt_to_the_side;
    double tilt_along;
    double critical_side_tilt;
    double critical_along_tilt;

    Point first_row_view[5];
    Point second_row_view[7];
    Point third_row_view[9];
    Point first_corner_view[7];
    Point second_corner_view[9];
    Point third_corner_view[11];

public:
    Rover(const int& dir, const int& rad, const double& crit_slope_side, const double& crit_slope_along, const double& start_point_x, const double& start_point_y, const Surface* surf);

    bool check_condition();
    double get_max_side_tilt();
    double get_max_along_tilt();

    bool turn_45_clockwise();
    bool turn_45_counterclockwise();
    bool turn_90_clockwise();
    bool turn_90_counterclockwise();
    void turn_180();

    bool drive_forward_speed_1();

    Point get_location();
    void change_cords(const int& dx, const int& dy);
    void BOOM();
    bool sensor_check();
    bool dest_point(Point Final_Destination);
    void detour_move();
    bool dest_point_achievment(Point Final_Destination);
    void fill_sensor();
    Point get_point_centerdxdy(const int& dx, const int& dy);
};