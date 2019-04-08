#include "missile.h"
#include "main.h"



Missile::Missile(float x, float y, float z, int type, glm::vec3 rot) {
    this->position = glm::vec3(x, y, z);
    
    this->roll = rot.x;
    this->pitch = -rot.y;
    this->yaw = rot.z-180;

    if(type == 0){
        this->speed = glm::vec4(0,0,-1,1);        
    }
    else if(type == 2){
        this->speed = glm::vec4(rot.x,rot.y,rot.z,1);
        this->speed = this->speed/(glm::length(this->speed)*2);
    }
    else{
        this->speed = glm::vec4(0,-0.1,0,1);        
    }
    this->type = type;

    static const GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, COLOR_RED, GL_FILL);
    
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(glm::vec3(0.1, 0.1, 0.1));
    if(this->type == 0){
        scale = glm::scale(glm::vec3(0.1, 0.1, 1));
    }
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate              = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(1, 0, 0))* rotate;
    rotate              = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, 1, 0)) * rotate;

    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Missile::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Missile::tick() {
    glm::mat4 rotate    = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate              = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(1, 0, 0))* rotate;
    rotate              = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, 1, 0)) * rotate;


    auto newspeed = this->speed;

    if(type == 0){
        newspeed = rotate * newspeed;
    }

    this->position.x += newspeed.x;
    this->position.y += newspeed.y;
    this->position.z += newspeed.z;

}

bounding_box_t Missile::get_bbox() {
    float x = this->position.x, y = this->position.y, z= this->position.z;
    bounding_box_t bbox = { x-0.1f,x+0.1f,y-0.1f,y+0.1f,z-0.1f,z+0.1f };
    return bbox;
}
