#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H



class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z, int axis, float angle);
    glm::vec3 position;
    bounding_box_t get_bbox();
    void draw(glm::mat4 VP);
    void tick();
    float rotation;
    int cur;

private:
    VAO *object;
};

#endif 
