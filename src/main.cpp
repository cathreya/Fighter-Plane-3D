#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "segment.h"
#include "missile.h"
#include "ring.h"
#include "fuel.h"
#include "volcano.h"
#include "enemy.h"
#include "arrow.h"
#include "compass.h"
#include "parachute.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#define pb push_back
using namespace std;


GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Compass compass;
vector<Parachute> parachutes;
vector<Volcano> volcanos;
vector<Fuel> fuelups;
vector<Ring> ring;
vector<Missile> miss;

vector<Segment> display[6];
Platform plat;
Ball ball1, ball2;
int cameraview = 0;
Arrow arrow;

Enemy enemy;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
// glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
glm::vec3 eye (0,0,10);
glm::vec3 target (0, 0, 0);
glm::vec3 up (0, 1, 0);

int score = 0;
int altitude = 0;
float fuel = 100;
float health = 100;
float enemyHealth = 10;
float speed = 0;


void display_score(){
    
    float x = 0.9;
    float y = 0.9;
    float z = -0.1;


    // cout<<x<<" "<<y<<" "<<z<<endl;
    string s = to_string((int)speed);
    reverse(s.begin(), s.end());
    display[0].clear();
    for(char c: s){
        display[0].pb(Segment(c, x, y, z));
        // x-= 1.25;
        x -= 0.15;
    }
    // x -= 2.5;
    x -= 0.18;
    s = to_string(altitude);
    reverse(s.begin(), s.end());
    display[1].clear();
    for(char c: s){
        display[1].pb(Segment(c,x,y,z));
        // x -= 1.25;
        x -= 0.15;
    }
    
    // x -= 2.5;
    x -= 0.18;
    s = to_string((int)fuel);
    reverse(s.begin(), s.end());
    display[2].clear();
    for(char c: s){
        display[2].pb(Segment(c,x,y,z));
        // x -= 1.25;
        x -= 0.15;
    }

    x -= 0.18;
    s = to_string((int)health);
    reverse(s.begin(), s.end());
    display[3].clear();
    for(char c: s){
        display[3].pb(Segment(c,x,y,z));
        // x -= 1.25;
        x -= 0.15;
    }

    x = 0.9;
    y = -0.9;
    z = -0.1;

    s = to_string((int)enemyHealth);
    reverse(s.begin(), s.end());
    display[4].clear();
    for(char c: s){
        display[4].pb(Segment(c, x, y, z));
        // x-= 1.25;
        x -= 0.15;
    }

    x -= 0.18;
    s = to_string((int)score);
    reverse(s.begin(), s.end());
    display[5].clear();
    for(char c: s){
        display[5].pb(Segment(c,x,y,z));
        // x -= 1.25;
        x -= 0.15;
    }



}



void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up = glm::cross(eye, target);


    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
    plat.draw(VP);
    arrow.draw(VP);
    compass.draw(VP);

    for(auto r:ring){
        r.draw(VP);
    }

    
    for (auto &i:display){
        for(auto &seg:i){
            seg.draw(VP);        
        }
    }
    for(auto &m: miss){
        m.draw(VP);
    }
    for(auto &f:fuelups){
        f.draw(VP);
    }
    for(auto &f:volcanos){
        f.draw(VP);
    }
    enemy.draw(VP);

    for(auto &p:parachutes){
        p.draw(VP);
    }

    // ball2.draw(VP);
}

void isDead(int force=0){
    if(health == 0){
        force = 1;
        cout<<"You have been shot down!"<<endl;
    }
    if(altitude == 0){
        force = 1;
        cout<<"Crashed into the water!"<<endl;
    } 
    else if(fuel == 0){
        force = 1;
        cout<<"Ran out of Fuel!"<<endl;
    }
    if(force){
        cout<<"GAME OVER"<<endl;
        cout<<"Score "<<score<<endl;
        exit(0);
    }
}


void changeView(int cnt){
    if(cnt == 0){
        //Plane View
        float x = ball1.end.x;
        float y = ball1.end.y; 
        float z = ball1.end.z; 

        float x1 = ball1.tip.x;
        float y1 = ball1.tip.y; 
        float z1 = ball1.tip.z; 



        eye = glm::vec3(x,y,z);

        // auto away = glm::vec4(x,y,-50,1);

        // target = glm::vec3(away.x,away.y,away.z);
            
        target = glm::vec3(x1,y1,z1);
        // up =  glm::vec3(0,1,0);
        up = glm::vec3(ball1.up.x, ball1.up.y, ball1.up.z);
    }
    else if(cnt ==1){
        //Top View
        float x = ball1.position.x;
        float y = ball1.position.y; 
        float z = ball1.position.z; 
        // eye = glm::vec3(0,30,0);
        eye = glm::vec3(x,30,z);
        // target = glm::vec3(0,-20,0);
        target = glm::vec3(x,-20,z);
        up =  glm::vec3(0,0,-1);
    }
    else if(cnt == 2){
        //Follow-cam
        float x = ball1.position.x;
        float y = ball1.position.y; 
        float z = ball1.position.z; 
        eye = glm::vec3(x,y+10,z+10);
        target = glm::vec3(x,y,z);
        up =  glm::vec3(0,1,0);
    }
    else if(cnt == 3){
        //Tower View
        float x = ball1.position.x;
        float y = ball1.position.y; 
        float z = ball1.position.z; 
        eye = glm::vec3(-20,-20,z);
        target = glm::vec3(x,y,z);
        up =  glm::vec3(0,1,0);
    }
}


float hAngle = M_PI;
float vAngle = 0.0f;
float mouseSpeed = 0.005f;


int rollsu = 0;
int pitchsu = 0;

long long  counter = 1e2;
long long  counter2 = 6e2;

void startCounter(){
    // cout<<counter<<endl;
    if(counter <= 0){
        // cout<<"RESET"<<endl;
        counter = 1e2;
        rollsu = 0;
    }
    if(counter2 <= 0){
        counter2 = 6e2;
        pitchsu = 0;
    }
    
    if(abs(rollsu) >= 70){
        cout<<"Barrel Roll!"<<endl;
        score+= 10;
        rollsu = 0;
        counter= 0;
    }
    if(abs(pitchsu) >= 350){
        cout<<"Loop the Loop!"<<endl;
        score+= 10;
        pitchsu = 0;
        counter2= 0;
    }

    counter --;
    counter2 --;

}

void tick_input(GLFWwindow *window) {
    // cout<<su<<endl;/
    startCounter();
    int w  = glfwGetKey(window, GLFW_KEY_W);
    int a  = glfwGetKey(window, GLFW_KEY_A);
    int s  = glfwGetKey(window, GLFW_KEY_S);
    int d  = glfwGetKey(window, GLFW_KEY_D);
    int q  = glfwGetKey(window, GLFW_KEY_Q);
    int e  = glfwGetKey(window, GLFW_KEY_E);
    int r  = glfwGetKey(window, GLFW_KEY_R);

    int one = glfwGetKey(window,GLFW_KEY_1);
    int two = glfwGetKey(window,GLFW_KEY_2);
    int three = glfwGetKey(window,GLFW_KEY_3);
    int four = glfwGetKey(window,GLFW_KEY_4);
    int five = glfwGetKey(window,GLFW_KEY_5);


    if(one) cameraview = (0);
    if(two) cameraview = (1);
    if(three) cameraview = (2);
    if(four) cameraview = (3);
    if(five) cameraview = (4);

    float yawspeed = 2;
    float pitchspeed = 1;
    float rollspeed = 4;

    if(d){
        ball1.roll += rollspeed;
        rollsu++;
    }
    if(a){
        ball1.roll -= rollspeed;
        rollsu--;
    }
    if(s){
        ball1.pitch += pitchspeed;
        pitchsu++;
    }
    if(w){
        ball1.pitch -= pitchspeed;
        pitchsu--;
    }
    if(q){
        ball1.yaw += yawspeed;
    }
    if(e){
        ball1.yaw -= yawspeed;
    }
    if(r){
        ball1.speed.z = 0.6;
        speed = ball1.speed.z*10;
        fuel -= 0.02;
    }
    else{
        ball1.speed.z = 0.1;
        speed = ball1.speed.z*10;
        fuel -= 0.001;
    }

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if(cameraview==4){

        double xpos, ypos;
        glfwGetCursorPos(window,&xpos, &ypos);
        glfwSetCursorPos(window,300,300);


        target = glm::vec3(ball1.position.x, ball1.position.y, ball1.position.z);

        hAngle += mouseSpeed *   float(300 - xpos );
        vAngle   += mouseSpeed * float(300 - ypos );

        glm::vec3 dir(
            screen_zoom*cos(vAngle) * sin(hAngle),
            screen_zoom*sin(vAngle),
            screen_zoom*cos(vAngle) * cos(hAngle)
        );

        glm::vec3 right = glm::vec3(
            sin(hAngle - M_PI/2.0f),
            0,
            cos(hAngle - M_PI/2.0f)
        );

        eye = target + dir;
        // target = eye+dir;
        up = glm::cross(right,dir);
    }

}


void scroll_callback(GLFWwindow *window, double x, double y){
    screen_zoom += y;

    if(screen_zoom < 1) screen_zoom = 1;
    if(screen_zoom > 60) screen_zoom = 60;
}

void fire(){
    glm::vec3 dir = ball1.position - enemy.position;
    miss.pb(Missile(enemy.position.x, enemy.position.y, enemy.position.z, 2, dir));
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        
        miss.pb(Missile(ball1.tip.x,ball1.tip.y,ball1.tip.z, 0, glm::vec3(ball1.roll, ball1.pitch, ball1.yaw)));
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        
        miss.pb(Missile(ball1.tip.x,ball1.tip.y,ball1.tip.z, 1, glm::vec3(ball1.roll, ball1.pitch, ball1.yaw)));
    }

}




void generate(int which){
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int x = uniform_int_distribution<int>(-300,300)(rng);
    int y = uniform_int_distribution<int>(-10,30)(rng);
    int z = uniform_int_distribution<int>(-300,300)(rng);
    float ang = uniform_real_distribution<float>(0,360)(rng);
    switch(which){
        case 1: ring.push_back(Ring(x,y,z,0,ang)); break;
        case 2: fuelups.push_back(Fuel(x,y,z,0,ang)); break;
        case 3: volcanos.push_back(Volcano(x,-36,z,0,0)); break;
        case 4: enemy = Enemy(x,-40,z,0,0); break;
        case 5: parachutes.push_back(Parachute(x,y,z,0,0)); break;
    }
    
}


int cnt = 0;
void tick_elements() {
    // cout<<miss.size()<<" "<<ring.size()<<" "<<fuelups.size()<<" "<<volcanos.size()<<" "<<parachutes.size()<<endl;
    // cout<<ball1.position.x<<" "<<ball1.position.z<<endl;
    glm::vec3 pos = ball1.tip;
    pos.x+=4;pos.y += 4;
    arrow.modify(pos, glm::vec3(ball1.roll, ball1.pitch, ball1.yaw), enemy.position);
    altitude = (int)ball1.position.y + 36;
    isDead();
    ball1.tick();
    compass.modify(-ball1.yaw);
    changeView(cameraview);
    display_score();

    vector<int> er;
    int i=0;
    for(auto &m : miss){
        m.tick();
        if(abs(m.position.x) > 500 || abs(m.position.y)>50 || abs(m.position.z) > 500){
            er.pb(i);
        }
    }
    for(int e:er){
        miss.erase(miss.begin()+e);
    }
    
    er.clear();
    i=0;

    for(auto &p : parachutes){
        p.tick();
        if( abs(p.position.y)>50 ){
            er.pb(i);
        }
        for(auto &m:miss){
            if(m.type != 2 && detect_collision(m.get_bbox() , p.get_bbox())){
                er.pb(i);
                score += 10;
                cout<<"Destroyed enemy parachute!"<<endl;
            }
        }
        i++;
    }
    for(int e:er){
        parachutes.erase(parachutes.begin()+e);
    }


    i = 0;
    er.clear();
    for(auto &r:ring){
        if(detect_collision(ball1.get_bbox(), r.get_bbox())){
            // cout<<"coll"<<cnt<<endl;cnt++;
            float yaw = ball1.yaw-180;
            if(yaw < 0) yaw = 360+yaw;
            // cout<<yaw<<" "<<r.rotation<<" "<<r.rotation + 180<<endl;
            if((abs(yaw - r.rotation) < 20) || (abs(yaw - r.rotation + 180) < 20) || (abs(yaw - r.rotation - 180) < 20)){
                score+= 10;
                er.pb(i);
            }
        }
        i++;
    }
    for(int i:er){
        cout<<"Passed through a ring!"<<endl;
        ring.erase(ring.begin()+i);
    }

    er.clear();
    i=0;
    for(auto &f:fuelups){
        if(detect_collision(ball1.get_bbox(), f.get_bbox())){
            fuel+= 10;
            er.pb(i);
        }
        i++;
    }
    for(int i:er){
        cout<<"Got some fuel!"<<endl;
        fuelups.erase(fuelups.begin()+i);
    }

    for(auto &v:volcanos){
        if(detect_collision(ball1.get_bbox(),v.get_bbox())){
            cout<<"Entered a No Fly Zone!"<<endl;
            isDead(1);
        }
    }


    i= 0;
    er.clear();

    for(auto &m:miss){
        if(m.type != 2 && detect_collision(enemy.get_bbox(),m.get_bbox())){
            enemyHealth -= 0.1;
            enemyHealth = max(enemyHealth,0.0f);
            if(enemyHealth <= 0){
                score+= 20;
                enemyHealth = 10;
                generate(4);
            }
        }
        if(m.type == 2 && detect_collision(ball1.get_bbox(),m.get_bbox())){
            health -= 0.1;
            health = max( health, 0.0f);
        }
    }

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int x = uniform_int_distribution<int>(1,150)(rng);
    if(x == 1) fire();

    // reset_screen();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(0, 0, COLOR_RED);
    plat = Platform(COLOR_BLACK);

    for(int i=0;i<50;i++){
        generate(1);
        generate(2);
        generate(3);
        generate(5);
    }

    generate(4);

    glm::vec3 pos = ball1.tip;
    pos.x+=4;pos.y += 4;

    compass = Compass(0);

    arrow = Arrow(pos, glm::vec3(ball1.roll, ball1.pitch, ball1.yaw), enemy.position);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    

    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            string tmp = "Altitude "+to_string((int)altitude);
            tmp += " Score "+ to_string((int)score);
            tmp += " Fuel " + to_string((int)fuel);
            tmp += " Health "+ to_string((int)health);
            glfwSetWindowTitle(window, tmp.c_str());

            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (a.minX <= b.maxX && a.maxX >= b.minX) &&
           (a.minY <= b.maxY && a.maxY >= b.minY) &&
           (a.minZ <= b.maxZ && a.maxZ >= b.minZ);
}

void reset_screen() {
    Matrices.projection = glm::perspective(
        glm::radians(45.0f),
        3.0f / 3.0f,       
        0.1f,              
        100.0f             
    );
}
