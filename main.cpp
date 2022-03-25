#include <gl/gl.h>

#include <gl/glut.h>

enum gameState {
    GAME_MENU,
    GAME_ACTIVE,
    GAME_END
};

void* font1 = GLUT_BITMAP_TIMES_ROMAN_24;
void* font2 = GLUT_BITMAP_HELVETICA_18 ;
void* font3 = GLUT_BITMAP_9_BY_15;
const char * GameTitle = "Cargasm";
gameState currentState = GAME_MENU;
int FPS = 50;
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
int currentWindow;

void renderBitmapString(float x, float y, void * font, const char * string) {
    const char * c;
    glRasterPos2f(x, y);
    for (c = string;* c != '\0'; c++) {
        glutBitmapCharacter(font, * c);
    }
};

void tree(int x, int y){
    // Pine tree wood
    glBegin(GL_POLYGON);
    glColor3f(0.145, 0.0824, 0.0431);
        glVertex2d(x + 11, y + 45);
        glVertex2d(x + 11, y + 55);
        glVertex2d(x + 13, y + 55);
        glVertex2d(x + 13, y + 45);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(0.0784, 0.2, 0.0235);
        glVertex2f(x + 12,y + 55);
        glVertex2f(x + 9,y + 47);
        glVertex2f(x + 15,y + 47);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(0.0784, 0.2, 0.0235);
        glVertex2f(x + 12,y + 57);
        glVertex2f(x + 9,y + 50);
        glVertex2f(x + 15,y + 50);
    glEnd();
}

void menuDesign(void) {
    glClearColor(0.145, 0.596, 0.854, 0.8); // Blue Sky
    // Ground-design
    // Grass
    glColor3f(0.000, 0.392, 0.000);
    glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(0, 55);
        glColor3f(0.604, 0.804, 0.196);
        glVertex2f(100, 55);
        glVertex2f(100, 0);
    glEnd();

    // Road Asphalt
    glBegin(GL_POLYGON);
        glColor3f(0, 0, 0);
        glVertex2f(30, 0);
        glVertex2f(90, 0);
        glVertex2f(55, 55);
        glVertex2f(50, 55);
    glEnd();

    //Road Paint #1
    glBegin(GL_POLYGON);
        glColor3f(0.968, 0.709, 0);
        glVertex2f(54, 0);
        glVertex2f(56, 0);
        glVertex2f(52.4, 55);
        glVertex2f(52.3, 55);
    glEnd();
    // Road Paint #2
    glBegin(GL_POLYGON);
        glColor3f(0.968, 0.709, 0);
        glVertex2f(58, 0);
        glVertex2f(60, 0);
        glVertex2f(52.8, 55);
        glVertex2f(52.7, 55);
    glEnd();
    //Hill 1
    glBegin(GL_TRIANGLES);
        glColor3f(0.235, 0.702, 0.443);
        glVertex2f(20, 65);
        glVertex2f(27, 55);
        glVertex2f(0, 55);
    glEnd();

    //Hill 2
    glBegin(GL_TRIANGLES);
        glColor3f(0.000, 0.502, 0.000);
        glVertex2f(35, 67);
        glVertex2f(50, 55);
        glVertex2f(10, 55);
    glEnd();

    //Hill 3
    glBegin(GL_TRIANGLES);
        glColor3f(0.235, 0.702, 0.443);
        glVertex2f(87,65);
        glVertex2f(100,55);
        glVertex2f(60,55);
    glEnd();

    //Hill 4
    glBegin(GL_TRIANGLES);
        glColor3f(0.000, 0.502, 0.000);
        glVertex2f(70,70);
        glVertex2f(90,55);
        glVertex2f(55,55);
    glEnd();

    // Trees LEFT/RIGHT
    tree(0, -5);
    tree(0, -25);
    tree(15, -10);

    tree(80, -5);
    tree(82, -25);
    tree(65, -10);

    // Title 
    glColor3f(1.000, 1.000, 0.000);
    renderBitmapString(46, 80, font1,"CarGASM");
    

    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(40, 70, font2,"Press SPACE to START");
    glColor3f(1.000, 0.000, 0.000);    
    renderBitmapString(44, 65, font2,"Press ESC to Exit");
}


int top_lane = 0, mid_lane = 0, bot_lane = 0;
void gameDesign(void) {
    // Ground-Design
    // Grass
    glClearColor(0.000, 0.392, 0.000, 1);
    // Road Asphalt
    glBegin(GL_POLYGON);
    glColor3f(0.165, 0.161, 0.133);
        glVertex2f(20,0);
        glVertex2f(20,100);
        glVertex2f(80,100);
        glVertex2f(80,0);
    glEnd();
    
    // Left/Right Border paint
    glBegin(GL_POLYGON);
    glColor3f(1.000, 1.000, 1.000);
        glVertex2f(20, 0);
        glVertex2f(20, 100);
        glVertex2f(21, 100);
        glVertex2f(21, 0);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(1.000, 1.000, 1.000);
        glVertex2f(79, 0);
        glVertex2f(79, 100);
        glVertex2f(80, 100);
        glVertex2f(80, 0);
    glEnd();

    // Lanes seperator
    // Top seperator
    
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, top_lane + 80);
    glVertex2f(48, top_lane + 100);
    glVertex2f(52, top_lane + 100);
    glVertex2f(52, top_lane + 80);
    glEnd();
    top_lane--;
    if(top_lane < -100) {
        top_lane = 20;
    }
    
    // Middle Seperator
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, mid_lane + 40);
    glVertex2f(48, mid_lane + 60);
    glVertex2f(52, mid_lane + 60);
    glVertex2f(52, mid_lane + 40);
    glEnd();
    mid_lane--;
    if(mid_lane < -60) {
        mid_lane = 60;
    }
    
    // Bottom seperator
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, bot_lane + 0);
    glVertex2f(48, bot_lane + 20);
    glVertex2f(52, bot_lane + 20);
    glVertex2f(52, bot_lane + 0);
    glEnd();
    bot_lane--;
    if(bot_lane < -20) {
        bot_lane = 100;
    }

        // left-side trees
        tree(-2, top_lane + 40);
        tree(-2, mid_lane + 0);
        tree(-2, bot_lane + -40);

        // right-side trees
        tree(79, top_lane + 40);
        tree(79, mid_lane + 0);
        tree(79, bot_lane + -40);
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    switch (currentState) {
        case GAME_MENU:
            menuDesign();
            break;
        case GAME_ACTIVE:
            gameDesign();
            break;
        default:
            break;
    };

    glFlush();
    glutSwapBuffers();
};

void gameControls(unsigned char key, int x, int y) {
    switch (key) {
        case ' ':
            bool faded = false;
            if (currentState == GAME_MENU) {
                while (!faded) {
                    GLfloat colors[4]; 
                    glGetFloatv(GL_COLOR_CLEAR_VALUE, colors);
                    if (colors[4] > 0.0) {
                        glClearColor(colors[0] - 0.1, colors[1] - 0.1, colors[2] - 0.1, colors[4] - 0.1);
                    }
                }
            }
            break;
    }
}

void timer(int _) {
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);
}

int main(int argc, char ** argv) {
    glutInit( & argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(200, 20);
    currentWindow = glutCreateWindow(GameTitle);

    glOrtho(0, 100, 0, 100, -1, 1); // glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
    // glClearColor(0.184, 0.310, 0.310, 1); // Dark Green.
    glutDisplayFunc(render);
    glutKeyboardFunc(gameControls);
    glutTimerFunc(1000, timer, 0);

    glutMainLoop();
}