#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H



class Compass {
public:
    Compass() {}
    Compass(float angle);
    glm::vec3 position;
    void modify(float ang);
    bounding_box_t get_bbox();
    void draw(glm::mat4 VP);
    float rotation;
    int cur;

private:
    VAO *object;
};

#endif 
