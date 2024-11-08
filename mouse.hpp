#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <tuple>

class Mouse {
  public:
    Mouse(double user_sensitivity) : user_sensitivity(user_sensitivity) {};
    double user_sensitivity;
    double sensitivity_scale = 0.001;
    double last_mouse_position_x = 0.0, last_mouse_position_y = 0.0;
    std::tuple<double, double> get_yaw_pitch_deltas(double mouse_position_x, double mouse_position_y);
};

#endif // MOUSE_HPP
