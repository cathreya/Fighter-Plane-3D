#include "parachute.h"
#include "main.h"
#include <iostream>
#include <algorithm>
using namespace std;



Parachute::Parachute(float x, float y, float z, int axis, float ang){
    this->position = glm::vec3(x, y, z);
    this->rotation = ang;
    this->cur = 0;

    static GLfloat g_vertex_buffer_data[500001];

    int vertices = 74;
    float curx = 1.0; 
    float cury = 0.0;

    float curx2 = 1.0; 
    float cury2 = 0.0;



    float angle = 360.0/vertices;

    angle *= M_PI/180;

    vertices/=2;

    int i;
    for(i=0;i<9*2*vertices;i+=18){

        g_vertex_buffer_data[i]   =  curx2;
        g_vertex_buffer_data[i+1] =  cury2;
        g_vertex_buffer_data[i+2] =  -0.8;
        
        g_vertex_buffer_data[i+3] = curx;
        g_vertex_buffer_data[i+4] = cury;
        g_vertex_buffer_data[i+5] = -0.1;


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
        g_vertex_buffer_data[i+8] = -0.1;

        g_vertex_buffer_data[i+9]  =  newx2;
        g_vertex_buffer_data[i+10] =  newy2;
        g_vertex_buffer_data[i+11] =  -0.8;
        
        g_vertex_buffer_data[i+12] = curx;
        g_vertex_buffer_data[i+13] = cury;
        g_vertex_buffer_data[i+14] = -0.1; 

        g_vertex_buffer_data[i+15] = curx2;
        g_vertex_buffer_data[i+16] = cury2;
        g_vertex_buffer_data[i+17] = -0.8; 


    }

    cout<<i<<endl;

    vector<float> verticeslist = {
        -1.0f,-1.5f - 2.0f,-1.0f,
        -1.0f,-1.5f - 2.0f, 1.0f,
        -1.0f, 1.5f - 2.0f, 1.0f,
         1.0f, 1.5f - 2.0f,-1.0f,
        -1.0f,-1.5f - 2.0f,-1.0f,
        -1.0f, 1.5f - 2.0f,-1.0f,
         1.0f,-1.5f - 2.0f, 1.0f,
        -1.0f,-1.5f - 2.0f,-1.0f,
         1.0f,-1.5f - 2.0f,-1.0f,
         1.0f, 1.5f - 2.0f,-1.0f,
         1.0f,-1.5f - 2.0f,-1.0f,
        -1.0f,-1.5f - 2.0f,-1.0f,
        -1.0f,-1.5f - 2.0f,-1.0f,
        -1.0f, 1.5f - 2.0f, 1.0f,
        -1.0f, 1.5f - 2.0f,-1.0f,
         1.0f,-1.5f - 2.0f, 1.0f,
        -1.0f,-1.5f - 2.0f, 1.0f,
        -1.0f,-1.5f - 2.0f,-1.0f,
        -1.0f, 1.5f - 2.0f, 1.0f,
        -1.0f,-1.5f - 2.0f, 1.0f,
         1.0f,-1.5f - 2.0f, 1.0f,
         1.0f, 1.5f - 2.0f, 1.0f,
         1.0f,-1.5f - 2.0f,-1.0f,
         1.0f, 1.5f - 2.0f,-1.0f,
         1.0f,-1.5f - 2.0f,-1.0f,
         1.0f, 1.5f - 2.0f, 1.0f,
         1.0f,-1.5f - 2.0f, 1.0f,
         1.0f, 1.5f - 2.0f, 1.0f,
         1.0f, 1.5f - 2.0f,-1.0f,
        -1.0f, 1.5f - 2.0f,-1.0f,
         1.0f, 1.5f - 2.0f, 1.0f,
        -1.0f, 1.5f - 2.0f,-1.0f,
        -1.0f, 1.5f - 2.0f, 1.0f,
         1.0f, 1.5f - 2.0f, 1.0f,
        -1.0f, 1.5f - 2.0f, 1.0f,
         1.0f,-1.5f - 2.0f, 1.0f,
    };
    int cnt = i;
    for(float f:verticeslist){
        g_vertex_buffer_data[i++] = f;
        cout<<i<<endl;
    }
    for(int i=0;i<cnt;i++){
        g_vertex_buffer_data[i]*=8;
    }


    this->object = create3DObject(GL_TRIANGLES, i/3, g_vertex_buffer_data, COLOR_BROWN, GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
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

void Parachute::tick(){
    this->position.y -= 0.05;
}


bounding_box_t Parachute::get_bbox() {
    float x = this->position.x, y = this->position.y, z=this->position.z;
    bounding_box_t bbox = { x-1, x+1, y-3.5f, y-0.5f, z-1, z+1};
    return bbox;

}