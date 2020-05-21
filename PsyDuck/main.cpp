#include <windows.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdio>
using namespace std;

#pragma comment(lib,"glaux.lib")

#define PI 3.14
#define MAX_CHAR 128

#define  GLUT_WHEEL_UP 3
#define  GLUT_WHEEL_DOWN 4

bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;
float cameraDistanceX;
float cameraDistanceY;
float cameraAngleX;
float cameraAngleY;
float times = 1;

int m = 0;
GLfloat step = 0.0f;
GLfloat step2 = 0.0;
GLfloat color = 0.0f;
const int n = 10000;
const float R = 0.28f;
const float R2 = 0.18f;
const float R3 = 0.08f;

static GLfloat colors[8][3] = {
	{ 0.95, 0.86, 0.02 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 },
	{ 0.0, 1.0, 1.0 }, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 0.0 }, { 1.0, 1.0, 1.0 }
};

void selectFont(int size, int charset, const char* face) {
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
                              charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                              DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}

//屏幕显示字体
void drawString(const char* str) {
    static int isFirstCall = 1;
    static GLuint lists;

    if (isFirstCall) {
        isFirstCall = 0;
        //申请 MAX_CHAR个连续的显示列表编号
        lists = glGenLists(MAX_CHAR);
        //把每个字符的绘制命令都装到对应的显示列表中
        wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
    }
    //调用每个字符对应的显示列表，绘制每个字符
    for (; *str != '\0'; ++str) {
        glCallList(lists + *str);
    }
}

void mouseCB(int button, int state, int x, int y) {
    mouseX = x;
    mouseY = y;
    times = 1;

    if(button == GLUT_LEFT_BUTTON) {
        if(state == GLUT_DOWN) {
            mouseLeftDown = true;
        } else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON) {
        if(state == GLUT_DOWN) {
            mouseRightDown = true;
        } else if(state == GLUT_UP)
            mouseRightDown = false;
    }

    /*
    * 鼠标滚轮控制图形缩放
    */
    else if (state == GLUT_UP && button == GLUT_WHEEL_UP) {
        times = 0.008f + 1;
        glutPostRedisplay();
    }

    else if (state == GLUT_UP && button == GLUT_WHEEL_DOWN) {
        times = -0.008f + 1;
        glutPostRedisplay();
    }
}

void mouseMotionCB(int x, int y) {
    cameraAngleX = cameraAngleY = 0;
    cameraDistanceX = cameraDistanceY = 0;

    if (mouseLeftDown) {
        cameraAngleY += (x - mouseX) * 0.1f;
        cameraAngleX += (y - mouseY) * 0.1f;
        mouseX = x;
        mouseY = y;
    }
    if (mouseRightDown) {
        cameraDistanceX = (x - mouseX) * 0.002f;
        cameraDistanceY = -(y - mouseY) * 0.002f;
        mouseY = y;
        mouseX = x;
    }

    glutPostRedisplay();
}

void DrawPole() {
    glColor3f(0.435, 0.217, 0);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.5f);
    glBegin(GL_LINE_STRIP);
        glVertex3f(-0.655f, 0.73f, 0.0f);
        glVertex3f(-0.605f, 0.80f, 0.0f);

        glVertex3f(0.97f, 0.31f, 0.0f);
        glVertex3f(0.975f, 0.23f, 0.0f);

        glVertex3f(-0.655f, 0.73f, 0.0f);
    glEnd();
    glDisable(GL_LINE_SMOOTH);

    glColor3f(0.6, 0.302, 0);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_POLYGON);
        glVertex3f(-0.655f, 0.73f, 0.0f);
        glVertex3f(-0.605f, 0.80f, 0.0f);

        glVertex3f(0.97f, 0.31f, 0.0f);
        glVertex3f(0.975f, 0.23f, 0.0f);

        glVertex3f(-0.655f, 0.73f, 0.0f);

    glEnd();
    glDisable(GL_LINE_SMOOTH);

    //The top of the pole
    glColor3f(0, 0, 0);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.5f);
    glBegin(GL_LINE_STRIP);
        glVertex3f(-0.655f, 0.73f, 0.0f);
        glVertex3f(-0.605f, 0.80f, 0.0f);

        glVertex3f(-0.70f, 0.90f, 0.0f);
        glVertex3f(-0.95f, 0.84f, 0.0f);

        glVertex3f(-0.73f, 0.735f, 0.0f);
        glVertex3f(-0.655f, 0.73f, 0.0f);
    glEnd();
    glDisable(GL_LINE_SMOOTH);

    glColor3f(0.906, 0.906, 0.906);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_POLYGON);
        glVertex3f(-0.655f, 0.73f, 0.0f);
        glVertex3f(-0.605f, 0.80f, 0.0f);

        glVertex3f(-0.70f, 0.90f, 0.0f);
        glVertex3f(-0.95f, 0.84f, 0.0f);

        glVertex3f(-0.73f, 0.735f, 0.0f);
        glVertex3f(-0.655f, 0.73f, 0.0f);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_BACK,GL_FILL);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //开启反走样
    glEnable( GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable( GL_POLYGON_SMOOTH);
    glEnable( GL_POINT_SMOOTH);
    glEnable( GL_LINE_SMOOTH);

    //Body
    glPushMatrix();
    GLfloat a = 0.48f, b = 0.4f;
    glColor3f(0.435, 0.217, 0.0);
    glLineWidth(4.5f);
    glBegin(GL_LINE_STRIP);
        for(int i = 1; i <= n; i++){
            glVertex2f(a * cos(2 * PI / i * n), b * sin(2 * PI / i * n));
        }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(colors[0][0], colors[0][1], colors[0][2]);
    glBegin(GL_POLYGON);
        for(int i = 1; i <= n; i++){
            glVertex2f(a * cos(2 * PI / i * n), b * sin(2 * PI / i * n));
        }
    glEnd();
    glPopMatrix();

    //Hood
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glColor3f(0.435, 0.217, 0);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.5f);
    glBegin(GL_LINE_STRIP);
        glVertex3f(-0.42f, 0.20f, 0.0f);
        glVertex3f(-0.32f, 0.30f, 0.0f);
        glVertex3f(0.0f, 0.35f, 0.0f);
        glVertex3f(0.32f, 0.30f, 0.0f);
        glVertex3f(0.43f, 0.2f, 0.0f);
        glVertex3f(0.0f, 0.33f, 0.0f);
        glVertex3f(-0.42f, 0.20f, 0.0f);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glColor3f(0.85f, 0.27f, 0.0f);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_POLYGON);
        glVertex3f(-0.42f, 0.20f, 0.0f);
        glVertex3f(-0.32f, 0.30f, 0.0f);
        glVertex3f(0.0f, 0.35f, 0.0f);
        glVertex3f(0.32f, 0.30f, 0.0f);
        glVertex3f(0.43f, 0.2f, 0.0f);
        glVertex3f(0.0f, 0.33f, 0.0f);
        glVertex3f(-0.42f, 0.20f, 0.0f);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
    glPopMatrix();

    //Grey Hair
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslated(-0.045, 0.28, 0);
    glScalef(0.4, 0.4, 0);
    glColor3f(0.435, 0.217, 0);
    glLineWidth(4.0f);
    glBegin(GL_LINE_STRIP);
        glVertex3f(-0.74f, 0.02f, 0.0f);
        glVertex3f(-0.68f, 0.305f, 0.0f);
        glVertex3f(-0.56f, 0.505f, 0.0f);
        glVertex3f(-0.535f, 0.83f, 0.0f);
        glVertex3f(-0.335f, 0.6f, 0.0f);
        glVertex3f(-0.275f, 0.335f, 0.0f);
        glVertex3f(-0.275f, 0.115f, 0.0f);
        glVertex3f(-0.74f, 0.02f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslated(-0.045, 0.28, 0);
    glScalef(0.4, 0.4, 0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.74f, 0.02f, 0.0f);
        glVertex3f(-0.68f, 0.305f, 0.0f);
        glVertex3f(-0.56f, 0.505f, 0.0f);
        glVertex3f(-0.535f, 0.83f, 0.0f);
        glVertex3f(-0.335f, 0.6f, 0.0f);
        glVertex3f(-0.275f, 0.335f, 0.0f);
        glVertex3f(-0.275f, 0.115f, 0.0f);
        glVertex3f(-0.74f, 0.02f, 0.0f);
    glEnd();
    glPopMatrix();

    //Left Eye
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslated(-0.045, 0.28, 0);
    glScalef(0.4, 0.4, 0);
    glColor3f(0.435, 0.217, 0);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.5f);
    glBegin(GL_LINE_STRIP);
        glVertex3f(-0.625f, -0.24f, 0.0f);
        glVertex3f(-0.725f, -0.355f, 0.0f);

        glVertex3f(-0.71f, -0.475f, 0.0f);
        glVertex3f(-0.655f, -0.565f, 0.0f);

        glVertex3f(-0.64f, -0.57f, 0.0f);

        glVertex3f(-0.575f, -0.585f, 0.0f);
        glVertex3f(-0.37f, -0.555f, 0.0f);

        glVertex3f(-0.23f, -0.52f, 0.0f);
        glVertex3f(-0.175f, -0.455f, 0.0f);

        glVertex3f(-0.17f, -0.44f, 0.0f);
        glVertex3f(-0.135f, -0.345f, 0.0f);

        glVertex3f(-0.17f, -0.44f, 0.0f);
        glVertex3f(-0.135f, -0.345f, 0.0f);

        glVertex3f(-0.135f, -0.245f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslated(-0.045, 0.28, 0);
    glScalef(0.4, 0.4, 0);
    glBegin(GL_POLYGON);
        glVertex3f(-0.625f, -0.24f, 0.0f);
        glVertex3f(-0.725f, -0.355f, 0.0f);

        glVertex3f(-0.71f, -0.475f, 0.0f);
        glVertex3f(-0.655f, -0.565f, 0.0f);

        glVertex3f(-0.64f, -0.57f, 0.0f);

        glVertex3f(-0.575f, -0.585f, 0.0f);
        glVertex3f(-0.37f, -0.555f, 0.0f);

        glVertex3f(-0.23f, -0.52f, 0.0f);
        glVertex3f(-0.175f, -0.455f, 0.0f);

        glVertex3f(-0.17f, -0.44f, 0.0f);
        glVertex3f(-0.135f, -0.345f, 0.0f);

        glVertex3f(-0.17f, -0.44f, 0.0f);
        glVertex3f(-0.135f, -0.345f, 0.0f);

        glVertex3f(-0.135f, -0.245f, 0.0f);
    glEnd();
    glPopMatrix();

    //The Left Eye
    glPushMatrix();
      glTranslated(-0.07, 0.06, 0);
      glTranslated(-0.10, 0.10, 0);
      glScalef(0.3, 0.3, 0);
      glColor3f(0, 0, 0);
      glBegin(GL_POLYGON);
          for(int i = 0;i < n;i++){
             glVertex2f(R3 * cos(2 * PI / n * i) - 0.1, R3 * sin(2 * PI/n * i) - 0.1);
          }
      glEnd();

      glColor3f(1, 1, 1);
      glBegin(GL_POLYGON);
          for(int i = 0;i < n;i++){
             glVertex2f(0.02f * cos(2 * PI / n * i) - 0.1, 0.02f * sin(2 * PI/n * i) - 0.1);
          }
      glEnd();
    glPopMatrix();

    //Right Eye
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslated(0.045, 0.28, 0);
    glScalef(0.4, 0.4, 0);
    glColor3f(0.435, 0.217, 0);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.5f);
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.625f, -0.24f, 0.0f);
        glVertex3f(0.725f, -0.355f, 0.0f);

        glVertex3f(0.71f, -0.475f, 0.0f);
        glVertex3f(0.655f, -0.565f, 0.0f);

        glVertex3f(0.64f, -0.57f, 0.0f);

        glVertex3f(0.575f, -0.585f, 0.0f);
        glVertex3f(0.37f, -0.555f, 0.0f);

        glVertex3f(0.23f, -0.52f, 0.0f);
        glVertex3f(0.175f, -0.455f, 0.0f);

        glVertex3f(0.17f, -0.44f, 0.0f);
        glVertex3f(0.135f, -0.345f, 0.0f);

        glVertex3f(0.17f, -0.44f, 0.0f);
        glVertex3f(0.135f, -0.345f, 0.0f);

        glVertex3f(0.135f, -0.245f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslated(0.045, 0.28, 0);
    glScalef(0.4, 0.4, 0);
    glBegin(GL_POLYGON);
        glVertex3f(0.625f, -0.24f, 0.0f);
        glVertex3f(0.725f, -0.355f, 0.0f);

        glVertex3f(0.71f, -0.475f, 0.0f);
        glVertex3f(0.655f, -0.565f, 0.0f);

        glVertex3f(0.64f, -0.57f, 0.0f);

        glVertex3f(0.575f, -0.585f, 0.0f);
        glVertex3f(0.37f, -0.555f, 0.0f);

        glVertex3f(0.23f, -0.52f, 0.0f);
        glVertex3f(0.175f, -0.455f, 0.0f);

        glVertex3f(0.17f, -0.44f, 0.0f);
        glVertex3f(0.135f, -0.345f, 0.0f);

        glVertex3f(0.17f, -0.44f, 0.0f);
        glVertex3f(0.135f, -0.345f, 0.0f);

        glVertex3f(0.135f, -0.245f, 0.0f);
    glEnd();
    glPopMatrix();

    //The Right Eye
    glPushMatrix();
      glTranslated(0.3, 0.06, 0);
      glTranslated(-0.10, 0.10, 0);
      glScalef(0.3, 0.3, 0);
      glColor3f(0, 0, 0);
      glBegin(GL_POLYGON);
          for(int i = 0;i < n;i++){
             glVertex2f(R3 * cos(2 * PI / n * i) - 0.1, R3 * sin(2 * PI/n * i) - 0.1);
          }
      glEnd();

      glColor3f(1, 1, 1);
      glBegin(GL_POLYGON);
          for(int i = 0;i < n;i++){
             glVertex2f(0.02f * cos(2 * PI / n * i) - 0.1, 0.02f * sin(2 * PI/n * i) - 0.1);
          }
      glEnd();
    glPopMatrix();

    //Left the mouth
    glPushMatrix();
    glTranslated(-0.07, 0.06, 0);
    glTranslated(-0.10, 0.10, 0);
    glScalef(0.3, 0.3, 0);
    glColor3f(1, 1, 0.85);
    glColor3f(0.435, 0.217, 0);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.5f);
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.55f, -0.55f, 0.0f);

        glVertex3f(0.15f, -0.65f, 0.0f);
        glVertex3f(0.16f, -0.655f, 0.0f);

        glVertex3f(-0.35f, -0.83f, 0.0f);
        glVertex3f(-0.38f, -0.86f, 0.0f);
        glVertex3f(-0.20f, -1.0f, 0.0f);
        glVertex3f(-0.26f, -1.3f, 0.0f);

        glVertex3f(-0.3f, -1.85f, 0.0f);

        glVertex3f(0.55f, -2.1f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
      glTranslated(-0.07, 0.06, 0);
      glTranslated(-0.10, 0.10, 0);
      glScalef(0.3, 0.3, 0);
      glColor3f(1, 1, 0.85);
      glBegin(GL_POLYGON);
        glVertex3f(0.55f, -0.55f, 0.0f);

        glVertex3f(0.15f, -0.65f, 0.0f);
        glVertex3f(0.16f, -0.655f, 0.0f);

        glVertex3f(-0.35f, -0.83f, 0.0f);
        glVertex3f(-0.38f, -0.86f, 0.0f);
        glVertex3f(-0.20f, -1.0f, 0.0f);
        glVertex3f(-0.26f, -1.3f, 0.0f);

        glVertex3f(-0.3f, -1.85f, 0.0f);

        glVertex3f(0.55f, -2.1f, 0.0f);
      glEnd();
    glPopMatrix();

    //Right the mouth
    glPushMatrix();
    glScalef(0.3, 0.3, 0);
    glColor3f(1, 1, 0.85);
    glTranslated(0.53, 0.53, 0);
    glColor3f(0.435, 0.217, 0);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.5f);
    glBegin(GL_LINE_STRIP);
        glVertex3f(-0.55f, -0.55f, 0.0f);

        glVertex3f(-0.15f, -0.65f, 0.0f);
        glVertex3f(-0.16f, -0.655f, 0.0f);

        glVertex3f(0.35f, -0.83f, 0.0f);
        glVertex3f(0.38f, -0.86f, 0.0f);
        glVertex3f(0.20f, -1.0f, 0.0f);
        glVertex3f(0.26f, -1.3f, 0.0f);

        glVertex3f(0.3f, -1.85f, 0.0f);

        glVertex3f(-0.55f, -2.1f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
      glScalef(0.3, 0.3, 0);
      glColor3f(1, 1, 0.85);
      glTranslated(0.53, 0.53, 0);
      glBegin(GL_POLYGON);
        glVertex3f(-0.55f, -0.55f, 0.0f);

        glVertex3f(-0.15f, -0.65f, 0.0f);
        glVertex3f(-0.16f, -0.655f, 0.0f);

        glVertex3f(0.35f, -0.83f, 0.0f);
        glVertex3f(0.38f, -0.86f, 0.0f);
        glVertex3f(0.20f, -1.0f, 0.0f);
        glVertex3f(0.26f, -1.3f, 0.0f);

        glVertex3f(0.3f, -1.85f, 0.0f);

        glVertex3f(-0.55f, -2.1f, 0.0f);
      glEnd();
    glPopMatrix();

    //Whiskers
    glPushMatrix();
      glColor3f(0, 0, 0);
      glBegin(GL_LINES);
          glVertex3f(-0.08f, -0.12f, 0.0f);
          glVertex3f(-0.04f, -0.15f, 0.0f);

          glVertex3f(0.08f, -0.12f, 0.0f);
          glVertex3f(0.04f, -0.15f, 0.0f);
      glEnd();
    glPopMatrix();

    //Left Ear
    glPushMatrix();
    glColor3f(0.85f, 0.27f, 0.0f);
    glEnable(GL_LINE_SMOOTH);
    glColor3f(0.435, 0.217, 0);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.5f);
    glBegin(GL_LINE_STRIP);
        glVertex3f(-0.42f, 0.20f, 0.0f);

        glVertex3f(-0.52f, 0.17f, 0.0f);
        glVertex3f(-0.54f, 0.15f, 0.0f);
        glVertex3f(-0.56f, 0.13f, 0.0f);
        glVertex3f(-0.58f, 0.11f, 0.0f);
        glVertex3f(-0.60f, 0.09f, 0.0f);

        glVertex3f(-0.64f, 0.03f, 0.0f);
        glVertex3f(-0.61f, -0.02f, 0.0f);
        glVertex3f(-0.57f, 0.03f, 0.0f);
        glVertex3f(-0.53f, -0.02f, 0.0f);

        glVertex3f(-0.5f, 0.01f, 0.0f);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.95f, 0.86f, 0.02f);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_POLYGON);
        glVertex3f(-0.42f, 0.20f, 0.0f);

        glVertex3f(-0.52f, 0.17f, 0.0f);
        glVertex3f(-0.54f, 0.15f, 0.0f);
        glVertex3f(-0.56f, 0.13f, 0.0f);
        glVertex3f(-0.58f, 0.11f, 0.0f);
        glVertex3f(-0.60f, 0.09f, 0.0f);

        glVertex3f(-0.64f, 0.03f, 0.0f);
        glVertex3f(-0.61f, -0.02f, 0.0f);
        glVertex3f(-0.57f, 0.03f, 0.0f);
        glVertex3f(-0.53f, -0.02f, 0.0f);

        glVertex3f(-0.5f, 0.01f, 0.0f);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
    glPopMatrix();

    //Right ear
    glPushMatrix();
    glColor3f(0.95f, 0.86f, 0.02f);
    glColor3f(0.435, 0.217, 0);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.5f);
    glBegin(GL_LINE_STRIP);
        glVertex3f(0.32f, 0.30f, 0.0f);

        glVertex3f(0.35f, 0.38f, 0.0f);
        glVertex3f(0.40f, 0.33f, 0.0f);
        glVertex3f(0.45f, 0.37f, 0.0f);
        glVertex3f(0.455f, 0.39f, 0.0f);

        glVertex3f(0.47f, 0.37f, 0.0f);
        glVertex3f(0.48f, 0.35f, 0.0f);
        glVertex3f(0.49f, 0.33f, 0.0f);
        glVertex3f(0.50f, 0.31f, 0.0f);
        glVertex3f(0.51f, 0.29f, 0.0f);
        glVertex3f(0.52f, 0.27f, 0.0f);
        glVertex3f(0.53f, 0.25f, 0.0f);
        glVertex3f(0.54f, 0.23f, 0.0f);
        glVertex3f(0.55f, 0.21f, 0.0f);
        glVertex3f(0.56f, 0.18f, 0.0f);

        glVertex3f(0.57f, 0.15f, 0.0f);
        glVertex3f(0.575f, 0.145f, 0.0f);
        glVertex3f(0.45f, 0.15f, 0.0f);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.95f, 0.86f, 0.02f);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_POLYGON);
        glVertex3f(0.32f, 0.30f, 0.0f);

        glVertex3f(0.35f, 0.38f, 0.0f);
        glVertex3f(0.40f, 0.33f, 0.0f);
        glVertex3f(0.45f, 0.37f, 0.0f);
        glVertex3f(0.455f, 0.39f, 0.0f);

        glVertex3f(0.47f, 0.37f, 0.0f);
        glVertex3f(0.48f, 0.35f, 0.0f);
        glVertex3f(0.49f, 0.33f, 0.0f);
        glVertex3f(0.50f, 0.31f, 0.0f);
        glVertex3f(0.51f, 0.29f, 0.0f);
        glVertex3f(0.52f, 0.27f, 0.0f);
        glVertex3f(0.53f, 0.25f, 0.0f);
        glVertex3f(0.54f, 0.23f, 0.0f);
        glVertex3f(0.55f, 0.21f, 0.0f);
        glVertex3f(0.56f, 0.18f, 0.0f);

        glVertex3f(0.57f, 0.15f, 0.0f);
        glVertex3f(0.575f, 0.145f, 0.0f);
        glVertex3f(0.45f, 0.15f, 0.0f);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
    glPopMatrix();

    //Yellow hair
    glPushMatrix();
    glColor3f(0.435, 0.217, 0);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.5f);
    glBegin(GL_LINE_STRIP);
        glVertex3f(-0.305f, 0.40f, 0.0f);

        glVertex3f(-0.325f, 0.41f, 0.0f);
        glVertex3f(-0.335f, 0.43f, 0.0f);
        glVertex3f(-0.345f, 0.45f, 0.0f);
        glVertex3f(-0.355f, 0.47f, 0.0f);
        glVertex3f(-0.365f, 0.49f, 0.0f);
        glVertex3f(-0.375f, 0.50f, 0.0f);
        glVertex3f(-0.30f, 0.60f, 0.0f);

        glVertex3f(-0.28f, 0.53f, 0.0f);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.95f, 0.86f, 0.02f);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_POLYGON);
        glVertex3f(-0.305f, 0.40f, 0.0f);

        glVertex3f(-0.325f, 0.41f, 0.0f);
        glVertex3f(-0.335f, 0.43f, 0.0f);
        glVertex3f(-0.345f, 0.45f, 0.0f);
        glVertex3f(-0.355f, 0.47f, 0.0f);
        glVertex3f(-0.365f, 0.49f, 0.0f);
        glVertex3f(-0.375f, 0.50f, 0.0f);
        glVertex3f(-0.30f, 0.60f, 0.0f);

        glVertex3f(-0.28f, 0.53f, 0.0f);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
    glPopMatrix();

    //The top of head
    glPushMatrix();
    glColor3f(0.435, 0.217, 0);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_POLYGON);
        glVertex3f(0.0f, 0.40f, 0.0f);

        glVertex3f(-0.12f, 0.43f, 0.0f);
        glVertex3f(-0.072f, 0.46f, 0.0f);
        glVertex3f(0.0f, 0.44f, 0.0f);
        glVertex3f(0.0f, 0.63f, 0.0f);
        glVertex3f(0.045f, 0.63f, 0.0f);
        glVertex3f(0.045f, 0.41f, 0.0f);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
    glPopMatrix();

    //Pole
    glScalef(times, times, times);
    glTranslatef(cameraDistanceX, cameraDistanceY, 0);
    glRotatef(cameraAngleX, 1, 0, 0);
    glRotatef(cameraAngleY, 0, 1, 0);
    DrawPole();

    //Sun
    glPushMatrix();
    glTranslated(0.73, 0.73, 0);
    glRotated(step, 0.0f, 0.0f, 1.0f);
    glTranslated(-0.005, -0.005, 0);
    glColor3f(1, 1, 1);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(2.5f);

    glBegin(GL_LINE_STRIP);
        for(int i = 0;i < n;i++){
            glVertex2f(R2 * cos(2 * PI / n * i), R2 * sin(2 * PI / n * i));
        }
    glEnd();

    glColor3f(1, color, 0);
    glBegin(GL_POLYGON);
        for(int i = 0;i < n;i++){
            glVertex2f(R2 * cos(2 * PI / n * i), R2 * sin(2 * PI / n * i));
        }
    glEnd();

    glDisable(GL_LINE_SMOOTH);
    glPopMatrix();

    //Smiling face
    glPushMatrix();
    glColor3f(0, 0, 0);
    glPointSize(15.0f);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
        glVertex3f(0.665f, 0.775f, 0.0f);
    glEnd();
    glDisable(GL_POINT_SMOOTH);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_LINES);
        glVertex3f(0.77f, 0.77f, 0.0f);
        glVertex3f(0.79f, 0.79f, 0.0f);

        glVertex3f(0.79f, 0.79f, 0.0f);
        glVertex3f(0.81f, 0.77f, 0.0f);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_LINES);
        glVertex3f(0.69f, 0.65f, 0.0f);
        glVertex3f(0.72f, 0.63f, 0.0f);

        glVertex3f(0.72f, 0.63f, 0.0f);
        glVertex3f(0.75f, 0.65f, 0.0f);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
    glPopMatrix();

    //The sun's edge
    glPushMatrix();
    glColor3f(1, 1, 0);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_LINES);
        glVertex3f(0.55f, 0.65f, 0.0f);
        glVertex3f(0.50f, 0.62f, 0.0f);

        glVertex3f(0.54f, 0.75f, 0.0f);
        glVertex3f(0.49f, 0.77f, 0.0f);

        glVertex3f(0.95f, 0.63f, 0.0f);
        glVertex3f(0.90f, 0.66f, 0.0f);

        glVertex3f(0.96f, 0.79f, 0.0f);
        glVertex3f(0.91f, 0.77f, 0.0f);

        glVertex3f(0.83f, 0.89f, 0.0f);
        glVertex3f(0.86f, 0.93f, 0.0f);

        glVertex3f(0.63f, 0.88f, 0.0f);
        glVertex3f(0.59f, 0.92f, 0.0f);

        glVertex3f(0.73f, 0.91f, 0.0f);
        glVertex3f(0.73f, 0.96f, 0.0f);

        glVertex3f(0.73f, 0.54f, 0.0f);
        glVertex3f(0.73f, 0.49f, 0.0f);

        glVertex3f(0.63f, 0.56f, 0.0f);
        glVertex3f(0.59f, 0.52f, 0.0f);

        glVertex3f(0.82f, 0.57f, 0.0f);
        glVertex3f(0.86f, 0.53f, 0.0f);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
    glPopMatrix();

    //Font
    glPushMatrix();
    glTranslated(step2, -0.75, 0);
    selectFont(50, ANSI_CHARSET, "Comic Sans MS");
    //设置字体颜色
    glColor3f(0.01f, 1.0f, 1.0f);
    //起始位置
    glRasterPos2i(0, 0);
     //输出的字符串
    drawString("Author: Lili Liang");
    glPopMatrix();

    glutSwapBuffers();
}

void menuFunc(int value){
    if(value == 1){
        colors[0][0] = colors[1][0];
        colors[0][1] = colors[1][1];
        colors[0][2] = colors[1][2];
    }else if(value == 2){
        colors[0][0] = colors[2][0];
        colors[0][1] = colors[2][1];
        colors[0][2] = colors[2][2];
    }else if(value == 3){
        colors[0][0] = colors[3][0];
        colors[0][1] = colors[3][1];
        colors[0][2] = colors[3][2];
    }else if(value == 4){
        colors[0][0] = colors[4][0];
        colors[0][1] = colors[4][1];
        colors[0][2] = colors[4][2];
    }else if(value == 5){
        colors[0][0] = colors[5][0];
        colors[0][1] = colors[5][1];
        colors[0][2] = colors[5][2];
    }else if(value == 6){
        colors[0][0] = colors[6][0];
        colors[0][1] = colors[6][1];
        colors[0][2] = colors[6][2];
    }else if(value == 7){
        colors[0][0] = colors[7][0];
        colors[0][1] = colors[7][1];
        colors[0][2] = colors[7][2];
    }else if(value == 0){
        colors[0][0] = 0.95;
        colors[0][1] = 0.86;
        colors[0][2] = 0.02;
    }
    glutPostRedisplay();
}

void NormalKeys(unsigned char key, int x, int y){
    int mod = glutGetModifiers();
    if(mod == GLUT_ACTIVE_ALT){
        if(key == '1'){
            step -= 20.0f;
        }
        if(key == '2'){
            step += 20.0f;
        }
        step = (GLfloat)((int)step % 360);
        glutPostRedisplay();
    }
}

void SpecialKeys(int key, int x, int y) {
    if(key == GLUT_KEY_LEFT)
        step2 -= 0.02f;
    if(key == GLUT_KEY_RIGHT)
        step2 += 0.02f;
    step = (GLfloat)((int)step % 360);
    glutPostRedisplay();
}

void resize(GLsizei w,GLsizei h){
	GLfloat ratio = (GLfloat)w / (GLfloat)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h)
		gluOrtho2D(-1.0, 1.0, -1.0 / ratio, 1.0 / ratio);
	else
		gluOrtho2D(-1.0 * ratio, 1.0 * ratio, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void time(int value){
    m++;
    if(m % 2 == 0){
        color = 1.0f;
    }
    else if(m % 2 == 1){
        color = 0.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(600, time, 1);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(250, 100);
    glutInitWindowSize(650, 650);
    glutCreateWindow("Hi! I am PsyDuck!");
    glutMouseFunc(mouseCB);
    glutMotionFunc(mouseMotionCB);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    int MainManuHandle = glutCreateMenu(menuFunc);
    glutAddMenuEntry("Original color", 0);
    glutAddMenuEntry("Red color", 1);
    glutAddMenuEntry("Green color", 2);
    glutAddMenuEntry("Dark blue", 3);
    glutAddMenuEntry("Light blue", 4);
    glutAddMenuEntry("Pink color", 5);
    glutAddMenuEntry("Pure yellow", 6);
    glutAddMenuEntry("White color", 7);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutKeyboardFunc(NormalKeys);
    glutSpecialFunc(SpecialKeys);
    glutTimerFunc(50, time, 1);
    glutReshapeFunc(resize);
    glClearColor(0.160, 0.576, 0.090, 0);
    glutMainLoop();
    return 0;
}