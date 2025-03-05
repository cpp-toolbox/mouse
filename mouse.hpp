#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <glm/glm.hpp>
#include <tuple>

class Mouse {
  public:
    Mouse(double user_sensitivity) : user_sensitivity(user_sensitivity) {};
    double user_sensitivity;
    double sensitivity_scale = 0.001;
    double last_mouse_position_x = 0.0, last_mouse_position_y = 0.0;
    std::tuple<double, double> get_yaw_pitch_deltas(double mouse_position_x, double mouse_position_y,
                                                    double sensitivity_override = -1);
    std::tuple<double, double> get_yaw_pitch_deltas_from_mouse_deltas(double mouse_delta_x, double mouse_delta_y,
                                                                      double requested_sens);
    glm::vec2 get_ndc_mouse_pos(unsigned int window_width, unsigned int window_height);
};

#endif // MOUSE_HPP
