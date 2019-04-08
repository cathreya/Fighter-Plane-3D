#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float roll;
    float pitch;
    float yaw;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void fixAngles();
    glm::vec4 speed;
    glm::vec4 tip;
    glm::vec4 end;
    glm::vec4 up;
    bounding_box_t get_bbox();
private:
    VAO *object;
};

#endif // BALL_H
