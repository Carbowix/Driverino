#include <gl/gl.h>

#include <gl/glut.h>

#include <windows.h>

#include <string>

#include <mmsystem.h>

using namespace std;

#pragma comment(lib, "Winmm.lib")

enum gameState {
    GAME_MENU,
    GAME_ACTIVE,
    GAME_END
};

void * font1 = GLUT_BITMAP_TIMES_ROMAN_24;
void * font2 = GLUT_BITMAP_HELVETICA_18;
void * font3 = GLUT_BITMAP_9_BY_15;
const char * GameTitle = "Road Rash";
gameState currentState = GAME_MENU;
int FPS = 60;
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
int currentWindow;

float randomColor (float rgb[3]) {
    for (int i = 0; i < 3; i++) 
        rgb[i] = (float)((rand() % 256) * 1) / (float)255;
}

void renderBitmapString(float x, float y, void * font,
    const char * string) {
    const char * c;
    glRasterPos2f(x, y);
    for (c = string;* c != '\0'; c++) {
        glutBitmapCharacter(font, * c);
    }
};

bool collision(float x1, float y1, float w1, float h1,
    float x2, float y2, float w2, float h2) {
    if ((x1 < (x2 + w2)) &&
        ((x1 + w1) > x2) &&
        (y1 < (y2 + h2)) &&
        ((h1 + y1) > y2)) {
        return true;
    } else {
        return false;
    }
}

void renderTree(int x, int y) {
    // Pine renderTree wood
    glBegin(GL_POLYGON);
    glColor3f(0.145, 0.0824, 0.0431);
    glVertex2d(x + 11, y + 45);
    glVertex2d(x + 11, y + 55);
    glVertex2d(x + 13, y + 55);
    glVertex2d(x + 13, y + 45);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0784, 0.2, 0.0235);
    glVertex2f(x + 12, y + 55);
    glVertex2f(x + 9, y + 47);
    glVertex2f(x + 15, y + 47);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0784, 0.2, 0.0235);
    glVertex2f(x + 12, y + 57);
    glVertex2f(x + 9, y + 50);
    glVertex2f(x + 15, y + 50);
    glEnd();
}

void renderCar(float x, float y, int inverted, float rgb[3]) {
    // Car body
    glBegin(GL_POLYGON);
    glColor3f(rgb[0], rgb[1], rgb[2]);
    // Front lamps body coverage
    glVertex2f(x + (2.5 + 1), y + (inverted * 6));
    // Back lamp body coverage (3.5 * 2, 6.5 * 2)
    glVertex2f(x + (2.5 + 1), y - (inverted * 6.5));
    glVertex2f(x - (2.5 + 1), y - (inverted * 6.5));
    // Front lamps body coverage
    glVertex2f(x - (2.5 + 1), y + (inverted * 6));
    glEnd();
    // car front LAMPs (OffsetY from center = 4.25px, OffsetX between 2 lamps = 2.5px, height of lamp: 1.5 px, width: 1px)
    // Left lamp
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0.0); // Set The Color To Yellow
    glVertex2f(x - 1.5, y + (inverted * 5));
    glVertex2f(x - 2.5, y + (inverted * 5));
    glVertex2f(x - 2.5, y + (inverted * 3.5));
    glVertex2f(x - 1.5, y + (inverted * 3.5));
    glEnd();

    // Right Lamp
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0.0); // Set The Color To Yellow
    glVertex2f(x + 1.5, y + (inverted * 5));
    glVertex2f(x + 2.5, y + (inverted * 5));
    glVertex2f(x + 2.5, y + (inverted * 3.5));
    glVertex2f(x + 1.5, y + (inverted * 3.5));
    glEnd();

    // car brakes lamp (offsetY from center: 5px, height of lamp: 1px, width: 5px)
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(x + 2.5, y - (inverted * 5));
    glVertex2f(x + 2.5, y - (inverted * 6));
    glVertex2f(x - 2.5, y - (inverted * 6));
    glVertex2f(x - 2.5, y - (inverted * 5));
    glEnd();

    // front window shield
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.4);
    glVertex2d(x - 2, y + (inverted * 2.5));
    glVertex2d(x + 2, y + (inverted * 2.5));
    glVertex2d(x + 2, y + (inverted * 0.1));
    glVertex2d(x - 2, y + (inverted * 0.1));
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
    glVertex2f(87, 65);
    glVertex2f(100, 55);
    glVertex2f(60, 55);
    glEnd();

    //Hill 4
    glBegin(GL_TRIANGLES);
    glColor3f(0.000, 0.502, 0.000);
    glVertex2f(70, 70);
    glVertex2f(90, 55);
    glVertex2f(55, 55);
    glEnd();

    // Trees LEFT/RIGHT
    renderTree(0, -5);
    renderTree(0, -25);
    renderTree(15, -10);

    renderTree(80, -5);
    renderTree(82, -25);
    renderTree(65, -10);

    // Title 
    glColor3f(1.000, 1.000, 0.000);
    renderBitmapString(46, 80, font1, GameTitle);


    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(40, 70, font2, "Press SPACE to START");
    glColor3f(1.000, 0.000, 0.000);
    renderBitmapString(44, 65, font2, "Press ESC to Exit");
}


float top_lane = 0, mid_lane = 0, bot_lane = 0, score = 0;
float moveOffsetX = 0, left_lane[3], right_lane[2], colors_left[3][3], colors_right[3][3], carColor[3];
const float carWidth = 3.5 * 2, carHeight = 6.5 * 2;
bool fading = false;

void endGame() {
    top_lane = mid_lane = bot_lane = score = moveOffsetX = 0;
    memset(left_lane, 0.0, sizeof(left_lane));
    memset(right_lane, 0.0, sizeof(right_lane));
    PlaySound((LPCTSTR)"assets//sound//lost.wav", NULL, SND_ASYNC | SND_FILENAME);
    currentState = GAME_END;
    fading = true;
}

void gameDesign(void) {
    // Ground-Design
    // Grass
    glClearColor(0.000, 0.392, 0.000, 1);

    // Road Asphalt
    glBegin(GL_POLYGON);
    glColor3f(0.165, 0.161, 0.133);
    glVertex2f(20, 0);
    glVertex2f(20, 100);
    glVertex2f(80, 100);
    glVertex2f(80, 0);
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
    top_lane -= 1.0 + (score * ((float)FPS / 1000.0) * 0.3); // Random formula that worked (Max range = 6)
    if (top_lane < -100) {
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
    mid_lane -= 1.0 + (score * ((float)FPS / 1000.0) * 0.3);
    if (mid_lane < -60) {
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
    bot_lane -= 1.0 + (score * ((float)FPS / 1000.0) * 0.3);
    if (bot_lane < -20) {
        bot_lane = 100;
    }

    // left-side trees
    renderTree(-2, top_lane + 40);
    renderTree(-2, mid_lane + 0);
    renderTree(-2, bot_lane + -40);

    // right-side trees
    renderTree(79, top_lane + 40);
    renderTree(79, mid_lane + 0);
    renderTree(79, bot_lane + -40);

    // cars simulator
    // Main Car
    renderCar(65 + moveOffsetX, 15, 1, carColor);
    // Traffic Cars
    // Start SP.Y = 110
    // Middle SP.Y = 50 
    // END SP.Y = -10
    // Total Cars (left): 3 * 110 = 330
    // Total Cars (right): 2 * 130 = 220

    // Left road
    renderCar(35, 100 - left_lane[0], -1, colors_left[0]);
    if (collision(65 + moveOffsetX, 15, carWidth, carHeight, 35, 100 - left_lane[0], carWidth, carHeight)) {
        endGame();
    }
    left_lane[0] += 1.0 + (score * ((float)FPS / 1000.0) * 0.3);
    if (left_lane[0] >= 330) { // 120 to reach from (110 -> -10 Y-axis), so 330 to wait for the next cars to reach the end.
        left_lane[0] = 0;
        score++;
        randomColor(colors_left[0]);
    }

    // Duo
    renderCar(42, 210 - left_lane[1], -1, colors_left[1]);
    renderCar(25, 210 - left_lane[1], -1, colors_left[1]);
    if (collision(65 + moveOffsetX, 15, carWidth, carHeight, 42, 210 - left_lane[1], carWidth, carHeight) ||
        collision(65 + moveOffsetX, 15, carWidth, carHeight, 25, 210 - left_lane[1], carWidth, carHeight)
     ) {
        endGame();
    }
    left_lane[1] += 1.0 + (score * ((float)FPS / 1000.0) * 0.3);
    if (left_lane[1] >= 330) {
        left_lane[1] = 0;
        score++;
        randomColor(colors_left[1]);
    }

    // Solo end
    renderCar(42, 320 - left_lane[2], -1, colors_left[2]);
    if (collision(65 + moveOffsetX, 15, carWidth, carHeight, 42, 320 - left_lane[2], carWidth, carHeight)) {
        endGame();
    }
    left_lane[2] += 1.0 + (score * ((float)FPS / 1000.0) * 0.3);
    if (left_lane[2] >= 330) {
        left_lane[2] = 0;
        score++;
        randomColor(colors_left[2]);
    }

    // Right road
    renderCar(65, 130 - right_lane[0], 1, colors_right[0]);
    if (collision(65 + moveOffsetX, 15, carWidth, carHeight, 65, 130 - right_lane[0], carWidth, carHeight)) {
        endGame();
    }
    right_lane[0] += 1.0 + (score * ((float)FPS / 1000.0) * 0.3);
    if (right_lane[0] >= (140 + 60)) {
        right_lane[0] = 0;
        score++;
        randomColor(colors_right[0]);
    }
    renderCar(60, 170 - right_lane[1], 1, colors_right[1]);
    if (collision(65 + moveOffsetX, 15, carWidth, carHeight, 60, 170 - right_lane[1], carWidth, carHeight)) {
        endGame();
    }
    right_lane[1] += 1.0 + (score * ((float)FPS / 1000.0) * 0.3);
    if (right_lane[1] >= 180 + 120) {
        right_lane[1] = 0;
        score += 1;
        randomColor(colors_right[1]);
    }

    // Scoreboard
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(82, 97);
    glVertex2f(100, 97);
    glVertex2f(100, 90);
    glVertex2f(82, 90);
    glEnd();

    char scoreBuff[30], speedBuff[30];
    sprintf(scoreBuff, "SCORE: %d", (int)score);
    sprintf(speedBuff, "SPEED: %.1f KM/H", (float)FPS + 1.0 + (score * ((float)FPS / 1000.0) * 3));
    
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(83, 94,(void *)font3, scoreBuff);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(83, 91,(void *)font3, speedBuff);
    
    // Debug Speed stuff
    /*
    glColor3f(0, 1, 0);
    renderBitmapString(46, 80, font1, std::to_string(1.0 + (score * ((float)FPS / 1000.0) * 0.4)).c_str());
    */
}

void lostDesign() {
    glClearColor(0, 0, 0, 1);
    glColor3f(1.000, 0, 0);
    renderBitmapString(45, 80, font1, "GAME OVER");
    glColor3f(0, 1, 0);
    renderBitmapString(34, 75, font1, "PRESS F TO PAY RESPECTS");
}


void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (fading) {
        float colors[4];
        glGetFloatv(GL_COLOR_CLEAR_VALUE, colors);
        if (colors[0] > 0.0 || colors[1] > 0 || colors[2] > 0) {
            glClearColor(colors[0] - 0.1, colors[1] - 0.1, colors[2] - 0.1, colors[4] - 0.1);
        } else {
            fading = false;
            Sleep(2000);
            if (currentState == GAME_ACTIVE) {
            PlaySound((LPCTSTR)
                "assets//sound//ingame.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
            }
        }
    } else {
        switch (currentState) {
            case GAME_MENU:
                menuDesign();
                break;
            case GAME_ACTIVE:
                glClearColor(1, 1, 1, 1);
                gameDesign();
                break;
            default:
                lostDesign();
                break;
        };
    }
    glFlush();
    glutSwapBuffers();
};


void gameControls(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC
            if (currentState == GAME_MENU) {
                exit(0);
            }
            break;
        case ' ':
            if (currentState == GAME_MENU) {

                PlaySound((LPCTSTR)
                    "assets//sound//start.wav", NULL, SND_ASYNC | SND_FILENAME);
                fading = true;
                currentState = GAME_ACTIVE;
            }
            break;
        case 'A':
        case 'a':
            if (currentState == GAME_ACTIVE) {
                if (moveOffsetX > -40.4) {
                    moveOffsetX -= 2;
                }
            }
            break;
        case 'D':
        case 'd':
            if (currentState == GAME_ACTIVE) {
                if (moveOffsetX < 10.4) {
                    moveOffsetX += 2;
                }
            }
            break;
        case 'W':
        case 'w':
            if (currentState == GAME_ACTIVE) {
                FPS += 1;
            }
            break;
        case 'S':
        case 's':
            if (currentState == GAME_ACTIVE) {
                FPS -= 1;
            }
            break;
        case 'F':
        case 'f':
            if (currentState == GAME_END) {
                currentState = GAME_MENU;
                PlaySound((LPCTSTR)"assets//sound//menu.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
            }
    }
}

void timer(int _) {
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);
}

int main(int argc, char ** argv) {
    for (int i = 0; i < 3; i++) { // Init random colors for cars.
        randomColor(colors_left[i]);
        randomColor(colors_right[i]);
    };
    glutInit( & argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(200, 20);
    currentWindow = glutCreateWindow(GameTitle);
    PlaySound((LPCTSTR)"assets//sound//menu.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
    glOrtho(0, 100, 0, 100, -1, 1); // glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
    glutDisplayFunc(render);
    glutKeyboardFunc(gameControls);
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
}