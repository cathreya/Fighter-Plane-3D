#include "arrow.h"
#include "main.h"
#include <iostream>
#include <algorithm>
using namespace std;



Arrow::Arrow(glm::vec3 pointfrom, glm::vec3 rot, glm::vec3 pointto){
    // this->position.x = 0.5;
    // this->position.y = 0.5;
    // this->position.z = -0.5;

    this->position = pointfrom;
    this->roll = rot.x;
    this->pitch = rot.y;
    this->yaw = rot.z;
    this->pointto = pointto;
    this->pointfrom = pointfrom;
    
    
    static GLfloat g_vertex_buffer_data[500001];
    static GLfloat g_color_buffer_data[500001];

    int vertices = 74;
    float curx = 1.0; 
    float cury = 0.0;

    float curx2 = 0.0; 
    float cury2 = 0.0;



    float angle = 360.0/vertices;

    angle *= M_PI/180;

    
    for(int i=0;i<9*2*vertices;i+=18){

        g_vertex_buffer_data[i]   =  curx2;
        g_vertex_buffer_data[i+1] =  cury2;
        g_vertex_buffer_data[i+2] =  0.0;
        
        g_color_buffer_data[i]   =  COLOR_BRIGHT_RED.r/256.0;
        g_color_buffer_data[i+1] =  COLOR_BRIGHT_RED.g/256.0;
        g_color_buffer_data[i+2] =  COLOR_BRIGHT_RED.b/256.0;
        


        g_vertex_buffer_data[i+3] = curx;
        g_vertex_buffer_data[i+4] = cury;
        g_vertex_buffer_data[i+5] = -1.8;

        g_color_buffer_data[i]   =  COLOR_BRIGHT_RED.r/256.0;
        g_color_buffer_data[i+1] =  COLOR_BRIGHT_RED.g/256.0;
        g_color_buffer_data[i+2] =  COLOR_BRIGHT_RED.b/256.0;


        float newx = curx*cos(angle) - cury*sin(angle);
        float newy = curx*sin(angle) + cury*cos(angle);
        
        float newx2 = curx2*cos(angle) - cury2*sin(angle);
        float newy2 = curx2*sin(angle) + cury2*cos(angle);


        swap(newx,curx);
        swap(newy,cury);
        
        swap(newx2,curx2);
        swap(newy2,cury2);
        

        g_vertex_buffer_data[i+6] = curx;
        g_vertex_buffer_data[i+7] = cury;
        g_vertex_buffer_data[i+8] = -1.8;

        g_color_buffer_data[i]   =  COLOR_BRIGHT_RED.r/256.0;
        g_color_buffer_data[i+1] =  COLOR_BRIGHT_RED.g/256.0;
        g_color_buffer_data[i+2] =  COLOR_BRIGHT_RED.b/256.0;


        g_vertex_buffer_data[i+9]  =  newx2;
        g_vertex_buffer_data[i+10] =  newy2;
        g_vertex_buffer_data[i+11] =  0.0;

        g_color_buffer_data[i+9]   =  COLOR_BRIGHT_RED.r/256.0;
        g_color_buffer_data[i+10] =  COLOR_BRIGHT_RED.g/256.0;
        g_color_buffer_data[i+11] =  COLOR_BRIGHT_RED.b/256.0;

        
        g_vertex_buffer_data[i+12] = curx;
        g_vertex_buffer_data[i+13] = cury;
        g_vertex_buffer_data[i+14] = -1.8; 

        g_color_buffer_data[i+12]   =  COLOR_BRIGHT_RED.r/256.0;
        g_color_buffer_data[i+13] =  COLOR_BRIGHT_RED.g/256.0;
        g_color_buffer_data[i+14] =  COLOR_BRIGHT_RED.b/256.0;


        g_vertex_buffer_data[i+15] = curx2;
        g_vertex_buffer_data[i+16] = cury2;
        g_vertex_buffer_data[i+17] = 0.0; 

        g_color_buffer_data[i+15]   =  COLOR_BRIGHT_RED.r/256.0;
        g_color_buffer_data[i+16] =  COLOR_BRIGHT_RED.g/256.0;
        g_color_buffer_data[i+17] =  COLOR_BRIGHT_RED.b/256.0;
    }


     curx = 0.5; 
     cury = 0.0;
     
     curx2 = 0.5; 
     cury2 = 0.0;


    for(int i=9*2*vertices;i<2*9*2*vertices;i+=18){

        g_vertex_buffer_data[i]   =  curx2;
        g_vertex_buffer_data[i+1] =  cury2;
        g_vertex_buffer_data[i+2] =  -1.8;
        
        g_color_buffer_data[i]   =  COLOR_BRIGHT_RED.r/256.0;
        g_color_buffer_data[i+1] =  COLOR_BRIGHT_RED.g/256.0;
        g_color_buffer_data[i+2] =  COLOR_BRIGHT_RED.b/256.0;
        


        g_vertex_buffer_data[i+3] = curx;
        g_vertex_buffer_data[i+4] = cury;
        g_vertex_buffer_data[i+5] = -3;

        g_color_buffer_data[i+3]   =  COLOR_BRIGHT_RED.r/256.0;
        g_color_buffer_data[i+4] =  COLOR_BRIGHT_RED.g/256.0;
        g_color_buffer_data[i+5] =  COLOR_BRIGHT_RED.b/256.0;


        float newx = curx*cos(angle) - cury*sin(angle);
        float newy = curx*sin(angle) + cury*cos(angle);
        
        float newx2 = curx2*cos(angle) - cury2*sin(angle);
        float newy2 = curx2*sin(angle) + cury2*cos(angle);


        swap(newx,curx);
        swap(newy,cury);
        
        swap(newx2,curx2);
        swap(newy2,cury2);
        

        g_vertex_buffer_data[i+6] = curx;
        g_vertex_buffer_data[i+7] = cury;
        g_vertex_buffer_data[i+8] = -3;

        g_color_buffer_data[i+6]   =  COLOR_BRIGHT_RED.r/256.0;
        g_color_buffer_data[i+7] =  COLOR_BRIGHT_RED.g/256.0;
        g_color_buffer_data[i+8] =  COLOR_BRIGHT_RED.b/256.0;


        g_vertex_buffer_data[i+9]  =  newx2;
        g_vertex_buffer_data[i+10] =  newy2;
        g_vertex_buffer_data[i+11] =  -1.8;

        g_color_buffer_data[i+9]   =  COLOR_BRIGHT_RED.r/256.0;
        g_color_buffer_data[i+10] =  COLOR_BRIGHT_RED.g/256.0;
        g_color_buffer_data[i+11] =  COLOR_BRIGHT_RED.b/256.0;

        
        g_vertex_buffer_data[i+12] = curx;
        g_vertex_buffer_data[i+13] = cury;
        g_vertex_buffer_data[i+14] = -3; 

        g_color_buffer_data[i+12]   =  COLOR_BRIGHT_RED.r/256.0;
        g_color_buffer_data[i+13] =  COLOR_BRIGHT_RED.g/256.0;
        g_color_buffer_data[i+14] =  COLOR_BRIGHT_RED.b/256.0;


        g_vertex_buffer_data[i+15] = curx2;
        g_vertex_buffer_data[i+16] = cury2;
        g_vertex_buffer_data[i+17] = -1.8; 

        g_color_buffer_data[i+15]   =  COLOR_BRIGHT_RED.r/256.0;
        g_color_buffer_data[i+16] =  COLOR_BRIGHT_RED.g/256.0;
        g_color_buffer_data[i+17] =  COLOR_BRIGHT_RED.b/256.0;
    }

    for(auto &i:g_vertex_buffer_data){
        i*=0.5;
    }



    this->object = create3DObject(GL_TRIANGLES, 2*3*2*vertices, g_vertex_buffer_data, g_color_buffer_data, GL_FILL);
}


void Arrow::modify(glm::vec3 pointfrom, glm::vec3 rot, glm::vec3 pointto){
    this->position = pointfrom;
    this->roll = rot.x;
    this->pitch = rot.y;
    this->yaw = rot.z;
    this->pointto = pointto;
    this->pointfrom = pointfrom;
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale (glm::vec3(0.1,0.1,0.1));    // glTranslatef


    // // glm::mat4 rotate = glm::transpose(glm::lookAt(this->position, this->pointto, glm::vec3(0.0f, 1.0f, 0.0f)));

    auto my = glm::vec3(0,0,1);
    auto pos = this->pointto - this->position;

    pos /= glm::length(pos);

    glm::vec3 axis = glm::cross(my,pos);
    axis = axis/glm::length(axis);
    float angle = acos(glm::dot(pos,my));    

    glm::mat4 rotate = glm::rotate(angle,axis);

    // this->rotation += 2;
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    // Matrices.model *= translate ;

    glm::mat4 MVP = VP * Matrices.model;
    // glm::mat4 MVP = Matrices.model;

    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}



bounding_box_t Arrow::get_bbox() {
    float x = this->position.x, y = this->position.y, z=this->position.z;
    bounding_box_t bbox = { x,x,y,y,z,z};
    return bbox;

}