#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef ENEM_H
#define ENEM_H



class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, float z, int axis, float angle);
    glm::vec3 position;
    bounding_box_t get_bbox();
    void draw(glm::mat4 VP);
    float rotation;
    int cur;

private:
    VAO *object;
};

#endif 
