#include "mouse.hpp"
#include <tuple>

std::tuple<double, double> Mouse::get_yaw_pitch_deltas(double mouse_position_x, double mouse_position_y,
                                                       double senstivity_override) {

    double requested_sens;

    if (senstivity_override != -1) {
        requested_sens = senstivity_override;
    } else {
        requested_sens = user_sensitivity;
    }

    double mouse_delta_x = (this->last_mouse_position_x - mouse_position_x);
    double mouse_delta_y = (this->last_mouse_position_y - mouse_position_y);

    this->last_mouse_position_x = mouse_position_x;
    this->last_mouse_position_y = mouse_position_y;

    return get_yaw_pitch_deltas_from_mouse_deltas(mouse_delta_x, mouse_delta_y, requested_sens);
}

std::tuple<double, double> Mouse::get_yaw_pitch_deltas_from_mouse_deltas(double mouse_delta_x, double mouse_delta_y,
                                                                         double requested_sens) {

    double change_in_yaw_angle = this->sensitivity_scale * mouse_delta_x;
    double change_in_pitch_angle = this->sensitivity_scale * mouse_delta_y;

    change_in_yaw_angle *= requested_sens;
    change_in_pitch_angle *= requested_sens;

    std::tuple yaw_pitch_deltas = {change_in_yaw_angle, change_in_pitch_angle};

    return yaw_pitch_deltas;
}

glm::vec2 Mouse::get_ndc_mouse_pos(unsigned int window_width, unsigned int window_height) {
    return {(2.0f * (float)this->last_mouse_position_x) / window_width - 1.0f,
            1.0f - (2.0f * (float)this->last_mouse_position_y) / window_height};
}
