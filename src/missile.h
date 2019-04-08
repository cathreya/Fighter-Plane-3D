#include "main.h"

#ifndef MISS_H
#define MISS_H


class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z, int type, glm::vec3 rot);
    glm::vec3 position;
    int type;
    float roll;
    float pitch;
    float yaw;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    glm::vec4 speed;
    bounding_box_t get_bbox();
private:
    VAO *object;
};

#endif // BALL_H
