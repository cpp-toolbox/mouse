#include "mouse.hpp"
#include <tuple>

/**
 * \brief Get delta angles based on mouse
 *
 * \details Take in absolute mouse positions and turn them into delta angles wrt yaw and pitch
 *
 * \note In radians tau = 2 * pi ~= 6.28 represents a full rotation, and on average we can assume that a a player
 * usually wants to rotate their view angle by theta := tau/4 ~= 1.57, also note that delta mouse positions are coming
 * in at (probably) a rate of at least 60Hz, which means that if a player wants to rotate their view by theta in one
 * second they must at least be producing deltas of size theta/60 = 0.0261.
 *
 * On average it seems that most mice produce deltas of size TODO, which are much greater than this value, and a general
 * rule of thumb is that to produce good delta angles, we should scale down our delta by 1000x
 *
 * \param mouse_position_x the current mouse x position
 * \param mouse_position_y the current mouse y position
 * \return a tuple t such that t1 is the change in yaw angle, and t2 is the change in pitch angle
 *
 * \author cuppajoeman
 * \date 2024
 */
std::tuple<double, double> Mouse::get_yaw_pitch_deltas(double mouse_position_x, double mouse_position_y,
                                                       double senstivity_override) {

    double requested_sens;

    if (senstivity_override != -1) {
        requested_sens = senstivity_override;
    } else {
        requested_sens = user_sensitivity;
    }

    double change_in_yaw_angle = this->sensitivity_scale * (this->last_mouse_position_x - mouse_position_x);
    double change_in_pitch_angle = this->sensitivity_scale * (this->last_mouse_position_y - mouse_position_y);

    change_in_yaw_angle *= requested_sens;
    change_in_pitch_angle *= requested_sens;

    std::tuple yaw_pitch_deltas = {change_in_yaw_angle, change_in_pitch_angle};

    this->last_mouse_position_x = mouse_position_x;
    this->last_mouse_position_y = mouse_position_y;

    return yaw_pitch_deltas;
}

glm::vec2 Mouse::get_ndc_mouse_pos(unsigned int window_width, unsigned int window_height) {
    return {(2.0f * (float)this->last_mouse_position_x) / window_width - 1.0f,
            1.0f - (2.0f * (float)this->last_mouse_position_y) / window_height};
}
