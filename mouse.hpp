#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <glm/glm.hpp>
#include <tuple>

/**
 * @brief A class that holds information to compute yaw pitch detlas based on mouse movement
 *
 *
 *
 */
class Mouse {
  public:
    Mouse(double user_sensitivity) : user_sensitivity(user_sensitivity) {};
    /// @brief the sensitivity used when computing
    double user_sensitivity = 1;
    double sensitivity_scale = 0.001;
    // NOTE: this might not always be synchronized with the actual current mouse position because sometimes you'll pause
    // the mouse eg you want to freeze a players camera and so you don't call get_yaw_pitch_deltas.
    double last_mouse_position_x = 0.0, last_mouse_position_y = 0.0;

    /**
     * @brief Get delta angles based on mouse positions
     *
     * @details Take in absolute mouse positions and turn them into delta angles wrt yaw and pitch
     *
     * @param sensitivity_override this allows us to override the built in user_sensitivity. When this parameter is -1,
     * then \a user_sensitivity is used, otherwise \p sensitivity_override is used.
     *
     * @todo \p sensitivity_override should probably be an optional instead of using -1, fine for now.
     *
     * @note In radians tau = 2 * pi ~= 6.28 represents a full rotation, and on average we can assume that a a player
     * usually wants to rotate their view angle by theta := tau/4 ~= 1.57, also note that delta mouse positions are
     * coming in at (probably) a rate of at least 60Hz, which means that if a player wants to rotate their view by theta
     * in one second they must at least be producing deltas of size theta/60 = 0.0261.
     *
     * On average it seems that most mice produce deltas of size TODO, which are much greater than this value, and a
     * general rule of thumb is that to produce good delta angles, we should scale down our delta by 1000x
     *
     *
     * @note after this function terminates lmpx, lmpy are set to the mpx, mpy that came in during the update
     *
     * @param mouse_position_x the current mouse x position
     * @param mouse_position_y the current mouse y position
     * @return a tuple t such that t1 is the change in yaw angle, and t2 is the change in pitch angle
     *
     */
    std::tuple<double, double> get_yaw_pitch_deltas(double mouse_position_x, double mouse_position_y,
                                                    double sensitivity_override = -1);

    /**
     * @brief Get delta angles based on mouse position deltas
     *
     * @param requested_sens a value which scales the computed yaw pitch deltas
     *
     */
    std::tuple<double, double> get_yaw_pitch_deltas_from_mouse_deltas(double mouse_delta_x, double mouse_delta_y,
                                                                      double requested_sens);
    glm::vec2 get_ndc_mouse_pos(unsigned int window_width, unsigned int window_height);
};

#endif // MOUSE_HPP
