#include "ball.h"
#include "main.h"
#include "objloader.hpp"


Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->tip = glm::vec4(x,y,-5,1);
    this->end = glm::vec4(x,y,+5,1);
    this->roll = 0;
    this->pitch = 0;
    this->yaw = 180;

    this->speed = glm::vec4(0,0,0,1);

    this->up = glm::vec4(0,1,0,1);


    std::vector<glm::vec3> vertices = {
        glm::vec3(0.650832, 0.271315, -1.000000),
        glm::vec3(1.240349, -0.000333, 1.000000),
        glm::vec3(0.650832, 0.315481, -1.000000),
        glm::vec3(1.240348, 0.180615, 0.560630),
        glm::vec3(0.805783, -0.000334, 4.284117),
        glm::vec3(0.805782, 0.180615, 4.284118),
        glm::vec3(3.119281, -0.942804, 2.322021),
        glm::vec3(3.119280, -0.761855, 1.882651),
        glm::vec3(0.650832, 0.315481, -1.000000),
        glm::vec3(1.240348, 0.180615, 0.560630),
        glm::vec3(3.119280, -0.761855, 1.882651),
        glm::vec3(0.507604, 0.512063, -1.000000),
        glm::vec3(0.556329, 0.986010, 1.000001),
        glm::vec3(0.218978, 0.452316, 3.753458),
        glm::vec3(1.240349, -0.000333, -0.372761),
        glm::vec3(1.240349, 0.180615, -0.372760),
        glm::vec3(3.119281, -0.942804, 0.949260),
        glm::vec3(3.119281, -0.761855, 0.949260),
        glm::vec3(1.240349, 0.180615, -0.372760),
        glm::vec3(3.119281, -0.761855, 0.949260),
        glm::vec3(0.653542, 0.986010, -0.372760),
        glm::vec3(3.457423, -0.942803, 2.322021),
        glm::vec3(3.457423, -0.761854, 1.882651),
        glm::vec3(3.457423, -0.942803, 0.949260),
        glm::vec3(3.457423, -0.761854, 0.949261),
        glm::vec3(3.119281, -0.942804, 2.322021),
        glm::vec3(3.119280, -0.761855, 2.321895),
        glm::vec3(3.457423, -0.942803, 2.322021),
        glm::vec3(3.457423, -0.761854, 2.321895),
        glm::vec3(3.182715, -0.908858, 2.321997),
        glm::vec3(3.182715, -0.795800, 2.321919),
        glm::vec3(3.393988, -0.908857, 2.321997),
        glm::vec3(3.393988, -0.795800, 2.321919),
        glm::vec3(3.182715, -0.907922, 3.673004),
        glm::vec3(3.182715, -0.794865, 3.672926),
        glm::vec3(3.393988, -0.907922, 3.673004),
        glm::vec3(3.393988, -0.794865, 3.672926),
        glm::vec3(3.242466, -0.875948, 3.672982),
        glm::vec3(3.242466, -0.826839, 3.672948),
        glm::vec3(3.334237, -0.875948, 3.672982),
        glm::vec3(3.334237, -0.826839, 3.672948),
        glm::vec3(3.242466, -0.875760, 3.945883),
        glm::vec3(3.242466, -0.826651, 3.945849),
        glm::vec3(3.334237, -0.875760, 3.945883),
        glm::vec3(3.334237, -0.826651, 3.945849),
        glm::vec3(0.960107, 0.565249, 0.770461),
        glm::vec3(0.525541, 0.310371, 4.030690),
        glm::vec3(0.582431, 0.409363, -1.000000),
        glm::vec3(0.960107, 0.565249, -0.372760),
        glm::vec3(0.845504, 0.498033, 1.630241),
        glm::vec3(0.538940, 0.845265, 1.726136),
        glm::vec3(1.125746, 0.180615, 1.542580),
        glm::vec3(1.125746, -0.000333, 1.866080),
        glm::vec3(-0.650832, 0.271315, -1.000000),
        glm::vec3(-1.240349, -0.000333, 1.000000),
        glm::vec3(0.000000, -0.000333, 1.000000),
        glm::vec3(0.000000, 0.271315, -1.000000),
        glm::vec3(-0.650832, 0.315481, -1.000000),
        glm::vec3(-1.240348, 0.180615, 0.560630),
        glm::vec3(0.000000, 0.315481, -1.000000),
        glm::vec3(-0.805783, -0.000334, 4.284117),
        glm::vec3(0.000000, -0.000334, 5.383713),
        glm::vec3(-0.805782, 0.180615, 4.284118),
        glm::vec3(0.000000, 0.180615, 5.383713),
        glm::vec3(-3.119281, -0.942804, 2.322021),
        glm::vec3(-3.119280, -0.761855, 1.882651),
        glm::vec3(-0.650832, 0.315481, -1.000000),
        glm::vec3(-1.240348, 0.180615, 0.560630),
        glm::vec3(-3.119280, -0.761855, 1.882651),
        glm::vec3(-0.507604, 0.512063, -1.000000),
        glm::vec3(-0.556329, 0.986010, 1.000001),
        glm::vec3(0.000000, 0.986010, 1.000000),
        glm::vec3(0.000000, 0.512063, -1.000000),
        glm::vec3(-0.218978, 0.452316, 3.753458),
        glm::vec3(0.000000, 0.452316, 4.853053),
        glm::vec3(-1.240349, -0.000333, -0.372761),
        glm::vec3(0.000000, -0.000333, -0.372761),
        glm::vec3(-1.240349, 0.180615, -0.372760),
        glm::vec3(-3.119281, -0.942804, 0.949260),
        glm::vec3(-3.119281, -0.761855, 0.949260),
        glm::vec3(-1.240349, 0.180615, -0.372760),
        glm::vec3(-3.119281, -0.761855, 0.949260),
        glm::vec3(-0.653542, 0.986010, -0.372760),
        glm::vec3(0.000000, 0.986010, -0.372761),
        glm::vec3(-3.457423, -0.942803, 2.322021),
        glm::vec3(-3.457423, -0.761854, 1.882651),
        glm::vec3(-3.457423, -0.942803, 0.949260),
        glm::vec3(-3.457423, -0.761854, 0.949261),
        glm::vec3(-3.119281, -0.942804, 2.322021),
        glm::vec3(-3.119280, -0.761855, 2.321895),
        glm::vec3(-3.457423, -0.942803, 2.322021),
        glm::vec3(-3.457423, -0.761854, 2.321895),
        glm::vec3(-3.182715, -0.908858, 2.321997),
        glm::vec3(-3.182715, -0.795800, 2.321919),
        glm::vec3(-3.393988, -0.908857, 2.321997),
        glm::vec3(-3.393988, -0.795800, 2.321919),
        glm::vec3(-3.182715, -0.907922, 3.673004),
        glm::vec3(-3.182715, -0.794865, 3.672926),
        glm::vec3(-3.393988, -0.907922, 3.673004),
        glm::vec3(-3.393988, -0.794865, 3.672926),
        glm::vec3(-3.242466, -0.875948, 3.672982),
        glm::vec3(-3.242466, -0.826839, 3.672948),
        glm::vec3(-3.334237, -0.875948, 3.672982),
        glm::vec3(-3.334237, -0.826839, 3.672948),
        glm::vec3(-3.242466, -0.875760, 3.945883),
        glm::vec3(-3.242466, -0.826651, 3.945849),
        glm::vec3(-3.334237, -0.875760, 3.945883),
        glm::vec3(-3.334237, -0.826651, 3.945849),
        glm::vec3(0.000000, 0.409363, -1.000000),
        glm::vec3(-0.960107, 0.565249, 0.770461),
        glm::vec3(-0.525541, 0.310371, 4.030690),
        glm::vec3(-0.582431, 0.409363, -1.000000),
        glm::vec3(0.000000, 0.310371, 5.130285),
        glm::vec3(-0.960107, 0.565249, -0.372760),
        glm::vec3(-0.845504, 0.498033, 1.630241),
        glm::vec3(-0.538940, 0.845265, 1.726136),
        glm::vec3(0.000000, 0.948491, 1.700656),
        glm::vec3(0.000000, -0.000333, 2.156063),
        glm::vec3(-1.125746, 0.180615, 1.542580),
        glm::vec3(-1.125746, -0.000333, 1.866080),
    };

    std::vector<int> choose = {
        15, 2, 56, 77,
        49, 48, 12, 21,
        17, 15, 19, 20,
        48, 109, 73, 12,
        5, 6, 64, 62,
        3, 1, 57, 60,
        118, 53, 5, 62,
        53, 52, 6, 5,
        17, 18, 25, 24,
        4, 2, 7, 8,
        19, 10, 11, 20,
        1, 3, 16, 15,
        16, 4, 10, 19,
        4, 8, 11, 10,
        21, 84, 72, 13,
        50, 46, 13, 51,
        1, 15, 77, 57,
        46, 49, 21, 13,
        2, 15, 17, 7,
        8, 18, 20, 11,
        3, 16, 19, 9,
        12, 73, 84, 21,
        24, 25, 23, 22,
        7, 17, 24, 22,
        23, 8, 27, 29,
        18, 8, 23, 25,
        29, 27, 31, 33,
        8, 7, 26, 27,
        22, 23, 29, 28,
        7, 22, 28, 26,
        33, 31, 35, 37,
        27, 26, 30, 31,
        28, 29, 33, 32,
        26, 28, 32, 30,
        37, 35, 39, 41,
        30, 32, 36, 34,
        31, 30, 34, 35,
        32, 33, 37, 36,
        41, 39, 43, 45,
        35, 34, 38, 39,
        36, 37, 41, 40,
        34, 36, 40, 38,
        43, 42, 44, 45,
        40, 41, 45, 44,
        38, 40, 44, 42,
        39, 38, 42, 43,
        16, 3, 48, 49,
        3, 60, 109, 48,
        64, 6, 47, 113,
        52, 4, 46, 50,
        4, 16, 49, 46,
        2, 4, 52, 53,
        6, 52, 50, 47,
        56, 2, 53, 118,
        13, 72, 117, 51,
        76, 77, 56, 55,
        114, 83, 70, 112,
        79, 82, 81, 76,
        112, 70, 73, 109,
        61, 62, 64, 63,
        58, 60, 57, 54,
        118, 62, 61, 120,
        120, 61, 63, 119,
        79, 87, 88, 80,
        59, 66, 65, 55,
        81, 82, 69, 68,
        54, 76, 78, 58,
        78, 81, 68, 59,
        59, 68, 69, 66,
        83, 71, 72, 84,
        115, 116, 71, 110,
        54, 57, 77, 76,
        110, 71, 83, 114,
        55, 65, 79, 76,
        66, 69, 82, 80,
        58, 67, 81, 78,
        70, 83, 84, 73,
        87, 85, 86, 88,
        65, 85, 87, 79,
        86, 92, 90, 66,
        80, 88, 86, 66,
        92, 96, 94, 90,
        66, 90, 89, 65,
        85, 91, 92, 86,
        65, 89, 91, 85,
        96, 100, 98, 94,
        90, 94, 93, 89,
        91, 95, 96, 92,
        89, 93, 95, 91,
        100, 104, 102, 98,
        93, 97, 99, 95,
        94, 98, 97, 93,
        95, 99, 100, 96,
        104, 108, 106, 102,
        98, 102, 101, 97,
        99, 103, 104, 100,
        97, 101, 103, 99,
        106, 108, 107, 105,
        103, 107, 108, 104,
        101, 105, 107, 103,
        102, 106, 105, 101,
        78, 114, 112, 58,
        58, 112, 109, 60,
        64, 113, 111, 63,
        119, 115, 110, 59,
        59, 110, 114, 78,
        55, 120, 119, 59,
        63, 111, 115, 119,
        56, 118, 120, 55,
        71, 116, 117, 72,
        51, 117, 75, 14,
        113, 47, 14, 75,
        47, 50, 51, 14,
        116, 74, 75, 117,
        113, 75, 74, 111,
        111, 74, 116, 115,
    };

    GLfloat vertex_buffer_data[500001];
    GLfloat color_buffer_data[500001];

    int k = 0;
    int l = 0;
    for(int i=0;i<choose.size();i+=4){
        int a = choose[i];
        int b = choose[i+1];
        int c = choose[i+2];
        int d = choose[i+3];

        vertex_buffer_data[k++] = vertices[a-1][0];
        vertex_buffer_data[k++] = vertices[a-1][1];
        vertex_buffer_data[k++] = vertices[a-1][2];
        
        vertex_buffer_data[k++] = vertices[b-1][0];
        vertex_buffer_data[k++] = vertices[b-1][1];
        vertex_buffer_data[k++] = vertices[b-1][2];
        
        vertex_buffer_data[k++] = vertices[c-1][0];
        vertex_buffer_data[k++] = vertices[c-1][1];
        vertex_buffer_data[k++] = vertices[c-1][2];

        vertex_buffer_data[k++] = vertices[a-1][0];
        vertex_buffer_data[k++] = vertices[a-1][1];
        vertex_buffer_data[k++] = vertices[a-1][2];
        
        vertex_buffer_data[k++] = vertices[d-1][0];
        vertex_buffer_data[k++] = vertices[d-1][1];
        vertex_buffer_data[k++] = vertices[d-1][2];
        
        vertex_buffer_data[k++] = vertices[c-1][0];
        vertex_buffer_data[k++] = vertices[c-1][1];
        vertex_buffer_data[k++] = vertices[c-1][2];

        color_buffer_data[l++] = 192.0f/256.0f;
        color_buffer_data[l++] = 192.0f/256.0f;
        color_buffer_data[l++] = 192.0f/256.0f;
        
        color_buffer_data[l++] = 169.0f/256.0f;
        color_buffer_data[l++] = 169.0f/256.0f;
        color_buffer_data[l++] = 169.0f/256.0f;
        
        color_buffer_data[l++] = 192.0f/256.0f;
        color_buffer_data[l++] = 192.0f/256.0f;
        color_buffer_data[l++] = 192.0f/256.0f;

        color_buffer_data[l++] = 169.0f/256.0f;
        color_buffer_data[l++] = 169.0f/256.0f;
        color_buffer_data[l++] = 169.0f/256.0f;
        
        color_buffer_data[l++] = 192.0f/256.0f;
        color_buffer_data[l++] = 192.0f/256.0f;
        color_buffer_data[l++] = 192.0f/256.0f;
        
        color_buffer_data[l++] = 169.0f/256.0f;
        color_buffer_data[l++] = 169.0f/256.0f;
        color_buffer_data[l++] = 169.0f/256.0f;


    }
    
    
    // this->object = create3DObject(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices[0], color, GL_FILL);
    // this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, g_color_buffer_data, GL_FILL);
    this->object = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data, color_buffer_data, GL_FILL);
    // this->object = create3DObject(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
}

void Ball::fixAngles(){
    if(this->yaw > 360) this->yaw -= 360;
    if(this->pitch > 360) this->pitch -= 360;
    if(this->roll > 360) this->roll -= 360;

    if(this->yaw < 0) this->yaw += 360;
    if(this->pitch < 0) this->pitch += 360;
    if(this->roll < 0) this->roll += 360;


}

void Ball::draw(glm::mat4 VP) {
    fixAngles();

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate              = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(1, 0, 0))* rotate;
    rotate              = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, 1, 0)) * rotate;


    this->tip = translate * rotate * glm::vec4(0, 0, 5,1);
    this->end = translate * rotate * glm::vec4(0, 0, -10,1);
    this->up = rotate * glm::vec4(0,1,0,1);
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    glm::mat4 rotate    = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate              = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(1, 0, 0))* rotate;
    rotate              = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, 1, 0)) * rotate;


    auto newspeed = this->speed;
    newspeed = rotate * newspeed;

    this->position.x += newspeed.x;
    this->position.y += newspeed.y;
    this->position.z += newspeed.z;

}

bounding_box_t Ball::get_bbox() {
    float x = this->position.x, y = this->position.y, z=this->position.z;
    bounding_box_t bbox = { x-2, x+2, y-2, y+2, z-2, z+2 };
    return bbox;

}
