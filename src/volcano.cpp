#include "volcano.h"
#include "main.h"
#include <iostream>
#include <algorithm>
using namespace std;



Volcano::Volcano(float x, float y, float z, int axis, float ang){
    this->position = glm::vec3(x, y, z);
    this->rotation = ang;
    this->cur = 0;

    static GLfloat g_vertex_buffer_data[500001];
    static GLfloat g_color_buffer_data[500001];

    int vertices = 74;
    float curx = 1.0; 
    float cury = 0.0;

    float curx2 = 0.09; 
    float cury2 = 0.0;



    float angle = 360.0/vertices;

    angle *= M_PI/180;

    
    for(int i=0;i<9*2*vertices;i+=18){

        g_vertex_buffer_data[i]   =  curx2;
        g_vertex_buffer_data[i+1] =  -0.1;
        g_vertex_buffer_data[i+2] =  cury2;
        
        g_color_buffer_data[i]   =  COLOR_MAROON.r/256.0;
        g_color_buffer_data[i+1] =  COLOR_MAROON.g/256.0;
        g_color_buffer_data[i+2] =  COLOR_MAROON.b/256.0;
        


        g_vertex_buffer_data[i+3] = curx;
        g_vertex_buffer_data[i+4] = -1.8;
        g_vertex_buffer_data[i+5] = cury;

        g_color_buffer_data[i]   =  COLOR_MAROON.r/256.0;
        g_color_buffer_data[i+1] =  COLOR_MAROON.g/256.0;
        g_color_buffer_data[i+2] =  COLOR_MAROON.b/256.0;


        float newx = curx*cos(angle) - cury*sin(angle);
        float newy = curx*sin(angle) + cury*cos(angle);
        
        float newx2 = curx2*cos(angle) - cury2*sin(angle);
        float newy2 = curx2*sin(angle) + cury2*cos(angle);


        swap(newx,curx);
        swap(newy,cury);
        
        swap(newx2,curx2);
        swap(newy2,cury2);
        

        g_vertex_buffer_data[i+6] = curx;
        g_vertex_buffer_data[i+7] = -1.8;
        g_vertex_buffer_data[i+8] = cury;

        g_color_buffer_data[i]   =  COLOR_MAROON.r/256.0;
        g_color_buffer_data[i+1] =  COLOR_MAROON.g/256.0;
        g_color_buffer_data[i+2] =  COLOR_MAROON.b/256.0;


        g_vertex_buffer_data[i+9]  =  newx2;
        g_vertex_buffer_data[i+10] =  -0.1;
        g_vertex_buffer_data[i+11] =  newy2;

        g_color_buffer_data[i+9]   =  COLOR_MAROON.r/256.0;
        g_color_buffer_data[i+10] =  COLOR_MAROON.g/256.0;
        g_color_buffer_data[i+11] =  COLOR_MAROON.b/256.0;

        
        g_vertex_buffer_data[i+12] = curx;
        g_vertex_buffer_data[i+13] = -1.8; 
        g_vertex_buffer_data[i+14] = cury;

        g_color_buffer_data[i+12]   =  COLOR_MAROON.r/256.0;
        g_color_buffer_data[i+13] =  COLOR_MAROON.g/256.0;
        g_color_buffer_data[i+14] =  COLOR_MAROON.b/256.0;


        g_vertex_buffer_data[i+15] = curx2;
        g_vertex_buffer_data[i+16] = -0.1; 
        g_vertex_buffer_data[i+17] = cury2;

        g_color_buffer_data[i+15]   =  COLOR_MAROON.r/256.0;
        g_color_buffer_data[i+16] =  COLOR_MAROON.g/256.0;
        g_color_buffer_data[i+17] =  COLOR_MAROON.b/256.0;


    }

    curx = 0.09; 
    cury = 0.0;

    for(int i=9*2*vertices;i<9*2*vertices+9*vertices;i+=9){

        g_vertex_buffer_data[i] = 0.0;
        g_vertex_buffer_data[i+1] = -0.1;
        g_vertex_buffer_data[i+2] =0.0;

        g_color_buffer_data[i]   =  COLOR_BRIGHT_RED.r/256.0;
        g_color_buffer_data[i+1] =  COLOR_BRIGHT_RED.g/256.0;
        g_color_buffer_data[i+2] =  COLOR_BRIGHT_RED.b/256.0;

        
        g_vertex_buffer_data[i+3] = curx;
        g_vertex_buffer_data[i+4] = -0.1;
        g_vertex_buffer_data[i+5] = cury;

        g_color_buffer_data[i+3]   =  COLOR_BRIGHT_RED.r/256.0;
        g_color_buffer_data[i+4] =  COLOR_BRIGHT_RED.g/256.0;
        g_color_buffer_data[i+5] =  COLOR_BRIGHT_RED.b/256.0;


        float newx = curx*cos(angle) - cury*sin(angle);
        float newy = curx*sin(angle) + cury*cos(angle);

        swap(newx,curx);
        swap(newy,cury);
        
        g_vertex_buffer_data[i+6] = curx;
        g_vertex_buffer_data[i+7] = -0.1;
        g_vertex_buffer_data[i+8] = cury;

        g_color_buffer_data[i+6]   =  COLOR_BRIGHT_RED.r/256.0;
        g_color_buffer_data[i+7] =  COLOR_BRIGHT_RED.g/256.0;
        g_color_buffer_data[i+8] =  COLOR_BRIGHT_RED.b/256.0;


    }

    for(auto &i:g_vertex_buffer_data){
        i*=8;
    }



    this->object = create3DObject(GL_TRIANGLES, 3*2*2*vertices, g_vertex_buffer_data, g_color_buffer_data, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale (glm::vec3(1,1,1));    // glTranslatef



    

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



bounding_box_t Volcano::get_bbox() {
    float x = this->position.x, y = this->position.y, z=this->position.z;
    bounding_box_t bbox = { x-0.72, x+0.72, y, y+100, z-0.72, z+0.72};
    return bbox;

}