#include "enemy.h"
#include "main.h"
#include <iostream>
#include <algorithm>
using namespace std;



Enemy::Enemy(float x, float y, float z, int axis, float ang){
    this->position = glm::vec3(x, y, z);
    this->rotation = ang;
    this->cur = 0;

    static const GLfloat vertex_buffer_data[] = { 
        -5.0f,-3.5f,-10.0f,
        -5.0f,-3.5f, 10.0f,
        -5.0f, 3.5f, 10.0f,
         5.0f, 3.5f,-10.0f,
        -5.0f,-3.5f,-10.0f,
        -5.0f, 3.5f,-10.0f,
         5.0f,-3.5f, 10.0f,
        -5.0f,-3.5f,-10.0f,
         5.0f,-3.5f,-10.0f,
         5.0f, 3.5f,-10.0f,
         5.0f,-3.5f,-10.0f,
        -5.0f,-3.5f,-10.0f,
        -5.0f,-3.5f,-10.0f,
        -5.0f, 3.5f, 10.0f,
        -5.0f, 3.5f,-10.0f,
         5.0f,-3.5f, 10.0f,
        -5.0f,-3.5f, 10.0f,
        -5.0f,-3.5f,-10.0f,
        -5.0f, 3.5f, 10.0f,
        -5.0f,-3.5f, 10.0f,
         5.0f,-3.5f, 10.0f,
         5.0f, 3.5f, 10.0f,
         5.0f,-3.5f,-10.0f,
         5.0f, 3.5f,-10.0f,
         5.0f,-3.5f,-10.0f,
         5.0f, 3.5f, 10.0f,
         5.0f,-3.5f, 10.0f,
         5.0f, 3.5f, 10.0f,
         5.0f, 3.5f,-10.0f,
        -5.0f, 3.5f,-10.0f,
         5.0f, 3.5f, 10.0f,
        -5.0f, 3.5f,-10.0f,
        -5.0f, 3.5f, 10.0f,
         5.0f, 3.5f, 10.0f,
        -5.0f, 3.5f, 10.0f,
         5.0f,-3.5f, 10.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, COLOR_BROWN, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale (glm::vec3(0.25,0.25,0.25));    // glTranslatef



    

    // this->rotation += 2;
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * scale);
    // Matrices.model *= translate ;

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}



bounding_box_t Enemy::get_bbox() {
    float x = this->position.x, y = this->position.y, z=this->position.z;
    bounding_box_t bbox = { x-2, x+2, y-1, y+1, z-3, z+3};
    return bbox;

}