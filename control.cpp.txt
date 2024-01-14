#include "Control.h"  
#include "functions.h"  

Control::Control(bool date, string log_filename, string gnu_surf_filename, string gnu_rover_filename, string gnu_load) {
    gnu_load_filename = gnu_load;
    is_date = date;
    _max_rand_hills = 0;
    _max_rand_beams = 0;
    _max_rand_stones = 0;
    control_log_file.open(log_filename);
    surf_gnu_file.open(gnu_surf_filename);
    rover_gnu_file.open(gnu_rover_filename);
};

Control::~Control() {
    surface_delete();
    close_files();
    delete rover;
    delete surf_0;
}


bool Control::surface_create(const double& surf_length, const double& surf_width, const double& surf_unevennes) {
    if (surf_length < 0 || surf_width < 0) return 0;
    surf_0 = new Surface(surf_length, surf_width, surf_unevennes);
    print_message_in_beam("Surface was generated: length - " + to_string(surf_length) + ", width - " + to_string(surf_width) + ", unevennes degree - " + to_string(surf_unevennes) + " ");
    set_cursor(surf_length / 2, surf_width / 2);
    return 1;
}
bool Control::set_cursor(const double& x, const double& y) {
    if (x < 0 || y < 0 || x > surf_0->length || y > surf_0->width) return 0;
    control_cursor = Cursor(x, y);
    print_message_in_beam("Cursor was located ");
    return 1;
}
bool Control::surface_set_random_hills(const double& num) {
    if (can_double_to_int(num) == 0 || num < 0) return 0;
    _max_rand_hills = int(num);
    print_message_in_beam("Number of random hummocks was setted ");
    return 1;
}
bool Control::surface_set_random_stones(const double& num) {
    if (can_double_to_int(num) == 0 || num < 0) return 0;
    _max_rand_stones = int(num);
    print_message_in_beam("Number of random stones was setted ");
    return 1;
}
bool Control::surface_set_random_beams(const double& num) {
    if (can_double_to_int(num) == 0 || num < 0) return 0;
    _max_rand_beams = int(num);
    print_message_in_beam("Number of random logs was setted ");
    return 1;
}
bool Control::surface_create_hill(const double& height, const double& sigma_x, const double& sigma_y, const double& rotation) {
    surf_0->add_hill(control_cursor.x, control_cursor.y, height, sigma_x, sigma_y, rotation);
    print_message_in_beam("Hummock was created ");
    return 1;
}
bool Control::surface_count() {
    ofstream file;
    file.open("TEST.txt");
    surf_0->count_surface();
    surf_0->Print_in_file(surf_gnu_file);
    print_message_in_beam("Surface was counted ");
    return 1;
}

bool Control::surface_create_stone(const double& radius) {
    if (radius < 0) return 0;
    surf_0->add_stone(control_cursor.x, control_cursor.y, radius);
    print_message_in_beam("Stone was created ");
    return 1;
}

bool Control::surface_create_beam(const double& x1, const double& y1, const double& x2, const double& y2, const double& radius) {
    if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0 || radius < 0 || x1 > surf_0->length || x2 > surf_0->length || y1 > surf_0->width || y2 > surf_0->width) return 0;
    surf_0->add_beam(x1, y1, x2, y2, radius);
    print_message_in_beam("Log was created ");
    return 1;
}

void Control::print_message_in_beam(string message)
{
    if (is_date) {
        printer_with_time(message, control_log_file);
    }
    else {
        control_log_file << message << "\n";
    }
}

void Control::rover_create(const int& dir, const int& rad, const double& crit_slope_side, const double& crit_slope_along, const double& start_point_x, const double& start_point_y)
{
    rover = new Rover(dir, rad, crit_slope_side, crit_slope_along, start_point_x, start_point_y, surf_0);
    rover_print_current_loc();
}

bool Control::rover_drive_forward_1() {

    if (rover->drive_forward_speed_1()) {
        print_message_in_beam("The rover successfully drove forward at a speed of 1 ");
        rover_print_current_loc();
        return 1;
    }
    else {
        print_message_in_beam("The rover broke down ");
        return 0;
    }
}
bool Control::rover_turn_90_clock() {
    if (rover->turn_90_clockwise()) {
        print_message_in_beam("The rover successfully turned 90 clockwise ");
        rover_print_current_loc();
        return 1;
    }
    else {
        print_message_in_beam("The rover broke down ");
        return 0;
    }
}
bool Control::rover_turn_90_counterclock() {
    if (rover->turn_90_counterclockwise()) {
        print_message_in_beam("The rover successfully turned 90 counterclockwise ");
        rover_print_current_loc();
        return 1;
    }
    else {
        print_message_in_beam("The rover broke down ");
        return 0;
    }
}
bool Control::rover_turn_45_counterclock() {
    if (rover->turn_45_counterclockwise()) {
        print_message_in_beam("The rover successfully turned 45 counterclockwise ");
        rover_print_current_loc();
        return 1;
    }
    else {
        print_message_in_beam("The rover broke down ");
        return 0;
    }
}
bool Control::rover_turn_45_clock() {
    if (rover->turn_45_clockwise()) {
        print_message_in_beam("The rover successfully turned 45 counterclockwise ");
        rover_print_current_loc();
        return 1;
    }
    else {
        print_message_in_beam("The rover broke down ");
        return 0;
    }
}
void Control::rover_turn_180() {
    rover->turn_180();
    print_message_in_beam("The rover successfully turned 180 ");
    rover_print_current_loc();
}

void Control::close_files() {
    control_log_file.close();
    surf_gnu_file.close();
    rover_gnu_file.close();
}

void Control::rover_print_current_loc() {
    Point point = rover->get_location();
    rover_gnu_file << point.x_cord << " " << point.y_cord << " " << point.z_cord << "\n";
}

void Control::surface_delete() {
    delete surf_0;
    free(surf_0);
};