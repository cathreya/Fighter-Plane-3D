#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef ARROW_H
#define ARROW_H



class Arrow {
public:
    Arrow() {}
    Arrow(glm::vec3 pointfrom, glm::vec3 rot, glm::vec3 pointto);
    glm::vec3 position;
    void modify(glm::vec3 pointfrom, glm::vec3 rot, glm::vec3 pointto);
    glm::vec3 pointfrom;
    glm::vec3 pointto;
    bounding_box_t get_bbox();
    void draw(glm::mat4 VP);
    float roll,pitch,yaw;

private:
    VAO *object;
};

#endif 
