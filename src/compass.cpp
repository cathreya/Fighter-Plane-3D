#include "compass.h"
#include "main.h"
#include <iostream>
#include <algorithm>
using namespace std;



Compass::Compass(float ang){
    this->position = glm::vec3(-0.8,-0.8, -0.1);
    this->rotation = ang;

    static const GLfloat vertex_buffer_data[] = { 
        -1.0,0,0,
         1,0,0,
         0,3,0,
         
        -1.0,0,0,
         1,0,0,
         0,-3,0,
    };

    static const GLfloat color_buffer_data[] = { 
        COLOR_BRIGHT_RED.r/256.0f,COLOR_BRIGHT_RED.g/256.0f,COLOR_BRIGHT_RED.b/256.0f,
        COLOR_BRIGHT_RED.r/256.0f,COLOR_BRIGHT_RED.g/256.0f,COLOR_BRIGHT_RED.b/256.0f,
        COLOR_BRIGHT_RED.r/256.0f,COLOR_BRIGHT_RED.g/256.0f,COLOR_BRIGHT_RED.b/256.0f,

         
        COLOR_GREEN.r/256.0f,COLOR_GREEN.g/256.0f,COLOR_GREEN.b/256.0f,
        COLOR_GREEN.r/256.0f,COLOR_GREEN.g/256.0f,COLOR_GREEN.b/256.0f,
        COLOR_GREEN.r/256.0f,COLOR_GREEN.g/256.0f,COLOR_GREEN.b/256.0f,
    };




    this->object = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Compass::modify(float ang){
    this->rotation = ang;   
}

void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale (glm::vec3(0.05,0.05,0.05));    // glTranslatef



    

    // this->rotation += 2;
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * scale);
    // Matrices.model *= translate ;

    glm::mat4 MVP =  Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}



bounding_box_t Compass::get_bbox() {
    float x = this->position.x, y = this->position.y, z=this->position.z;
    bounding_box_t bbox = { x-1, x+1, y-1, y+1, z, z};
    return bbox;

}