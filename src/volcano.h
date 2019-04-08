#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef VOLC_H
#define VOLC_H



class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y, float z, int axis, float angle);
    glm::vec3 position;
    bounding_box_t get_bbox();
    void draw(glm::mat4 VP);
    float rotation;
    int cur;

private:
    VAO *object;
};

#endif 
