#define _CRT_SECURE_NO_WARNINGS
#include "control.h"  
#include "functions.h"  

bool Control::create_surface(double surf_length, double surf_width, double angle) {
    surf = Surface(surf_length, surf_width, angle);
    auto now = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(now);
    cntrl_log_file << "Surface was generated:" << " length - " << surf_length << ", width - " << surf_width << ", unevennes degree - " << angle << ctime(&end_time);
    set_cursor(surf_length / 2, surf_width / 2);
    return 1;
}

bool Control::set_cursor(double x, double y) {
    cntrl_cursor = Cursor(x, y);
    time_print("Cursor was set ", cntrl_log_file);
    return 1;
}

bool Control::set_random_hills(size_t num) {
    _max_rand_hills = num;
    time_print("Number of hills was set ", cntrl_log_file);
    return 1;
}

bool Control::set_random_stones(size_t num) {
    _max_rand_stones = num;
    time_print("Number of stones was set ", cntrl_log_file);
    return 1;
}

bool Control::set_random_beams(size_t num) {
    _max_rand_beams = num;
    time_print("Number of beams was set ", cntrl_log_file);
    return 1;
}

bool Control::create_hill(double height, double sigma_x, double sigma_y, double angle) {
    surf.add_hill(cntrl_cursor.x_cord, cntrl_cursor.y_cord, height, sigma_x, sigma_y);
    time_print("Hill was created ", cntrl_log_file);
    return 1;
}

bool Control::count_surface() {
    //.file_print(gnu);
    time_print("Surface was counted", cntrl_log_file);
    return 1;
}

bool Control::create_stone(double radius) {
    surf.add_stone(cntrl_cursor.x_cord, cntrl_cursor.y_cord, radius);
    time_print("Stone was created ", cntrl_log_file);
    return 1;
}

bool Control::create_beam(double x1, double y1, double x2, double y2, double radius) {
    surf.add_beam(x1, y1, x2, y2, radius);
    time_print("Log was created ", cntrl_log_file);
    return 1;
}
