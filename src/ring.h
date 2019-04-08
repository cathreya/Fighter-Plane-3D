#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef RING_H
#define RING_H



class Ring {
public:
    Ring() {}
    Ring(float x, float y, float z, int axis, float angle);
    glm::vec3 position;
    bounding_box_t get_bbox();
    void draw(glm::mat4 VP);
    float rotation;
    int cur;

private:
    VAO *object;
};

#endif 
