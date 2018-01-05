#include "image.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
static float ww, wh;
static bool input = false;
static int chooseCard[2];
static int deleteIndex = -1;
static int page = 1;
bool lock = false;
int play_time = 0;
int card_center_x[4] = { -90,-30,30,90 };
int card_center_y[4] = { 120,40,-40,-120 };
int card[16] = { 0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7 };
void init();

void drawcardedge() {
     glColor3f(0.5,0,0.5);
     for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 4; j++) {
               glBegin(GL_LINES);
               glVertex2f(card_center_x[i] - 20, card_center_y[j] - 30);
               glVertex2f(card_center_x[i] - 20, card_center_y[j] + 30);

               glVertex2f(card_center_x[i] - 20, card_center_y[j] + 30);
               glVertex2f(card_center_x[i] + 20, card_center_y[j] + 30);

               glVertex2f(card_center_x[i] + 20, card_center_y[j] + 30);
               glVertex2f(card_center_x[i] + 20, card_center_y[j] - 30);

               glVertex2f(card_center_x[i] + 20, card_center_y[j] - 30);
               glVertex2f(card_center_x[i] - 20, card_center_y[j] - 30);
               glEnd();
          }
     }
     for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 4; j++) {
               glBegin(GL_POLYGON);
               //左下
               glColor3f(1, 1, 1);
               glVertex2f(card_center_x[i] - 19, card_center_y[j] - 29);
               //左上
               glColor3f(0, 1, 1);
               glVertex2f(card_center_x[i] - 19, card_center_y[j] + 29);
               //右上
               glColor3f(0.7, 0.5, 1);
               glVertex2f(card_center_x[i] + 19, card_center_y[j] + 29);
               //右下
               glColor3f(1, 0.6, 0.7);
               glVertex2f(card_center_x[i] + 19, card_center_y[j] - 29);
               glEnd();
          }
     }
}

void display() {
     glClearColor(0, 0, 0, 1);
     glClear(GL_COLOR_BUFFER_BIT);
     if (page == 1) {//start
          glClearColor(1, 1, 1, 1);
          glClear(GL_COLOR_BUFFER_BIT);
          drawfirst();
     }
     else if (page == 2) {//play
          glClearColor(0, 0, 0, 1);
          glClear(GL_COLOR_BUFFER_BIT);
          //paper
          glColor3f(1, 1, 1);
          glBegin(GL_POLYGON);
          glVertex2f(130, 170);
          glVertex2f(130, -170);
          glVertex2f(-130, -170);
          glVertex2f(-130, 170);
          glEnd();
          drawcardedge();

          glFlush();
     }
     else if (page == 3) {
          init_end();
          glClearColor(1, 1, 1, 1);
          glClear(GL_COLOR_BUFFER_BIT);
          glCallList('End');
          glColor3f(0, 0, 0);
          char* t1 = new char[10];
          sprintf_s(t1,10,"%d",play_time);
          string t2;
          t2.assign(t1);
          int x = -25;
          int y = -80;
          int shift = 0;
          glRasterPos2i(x, y);       //ABC 輸入文字
          glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'T');
          shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'T');
          glRasterPos2i(x + (shift / 2) + 1, y);
          glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
          shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'i');
          glRasterPos2i(x + (shift / 2) + 1, y);
          glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'm');
          shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'm');
          glRasterPos2i(x + (shift / 2) + 1, y);
          glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
          shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'e');
          glRasterPos2i(x + (shift / 2) + 1, y);
          glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ':');
          shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, ':');
          glRasterPos2i(x + (shift / 2) + 1, y);
          for (int i = 0; i < t2.length(); i++) {
               glutBitmapCharacter(GLUT_BITMAP_9_BY_15, t2[i]);
               shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, t2[i]);
               glRasterPos2i(x + (shift / 2) + 1, y);
          }
          glFlush();
     }     
}

int pick(float x, float y) {
     if (card_center_y[0] - 30 <= y && card_center_y[0] + 30 >= y) {//上 to 下
          if (card_center_x[0] - 20 <= x && card_center_x[0] + 20 >= x ){//上 to 下
               return 0;
          }
          else if (card_center_x[1] - 20 <= x && card_center_x[1] + 20 >= x) {
               return 1;
          }
          else if (card_center_x[2] - 20 <= x && card_center_x[2] + 20 >= x) {
               return 2;
          }
          else if (card_center_x[3] - 20 <= x && card_center_x[3] + 20 >= x) {
               return 3;
          }
          else return 16;
     }
     else if (card_center_y[1] - 30 <= y && card_center_y[1] + 30 >= y) {
          if (card_center_x[0] - 20 <= x && card_center_x[0] + 20 >= x) {//上 to 下
               return 4;
          }
          else if (card_center_x[1] - 20 <= x && card_center_x[1] + 20 >= x) {
               return 5;
          }
          else if (card_center_x[2] - 20 <= x && card_center_x[2] + 20 >= x) {
               return 6;
          }
          else if (card_center_x[3] - 20 <= x && card_center_x[3] + 20 >= x) {
               return 7;
          }
          else return 16;
     }
     else if (card_center_y[2] - 30 <= y && card_center_y[2] + 30 >= y) {
          if (card_center_x[0] - 20 <= x && card_center_x[0] + 20 >= x) {//上 to 下
               return 8;
          }
          else if (card_center_x[1] - 20 <= x && card_center_x[1] + 20 >= x) {
               return 9;
          }
          else if (card_center_x[2] - 20 <= x && card_center_x[2] + 20 >= x) {
               return 10;
          }
          else if (card_center_x[3] - 20 <= x && card_center_x[3] + 20 >= x) {
               return 11;
          }
          else return 16;
     }
     else if (card_center_y[3] - 30 <= y && card_center_y[3] + 30 >= y) {
          if (card_center_x[0] - 20 <= x && card_center_x[0] + 20 >= x) {//上 to 下
               return 12;
          }
          else if (card_center_x[1] - 20 <= x && card_center_x[1] + 20 >= x) {
               return 13;
          }
          else if (card_center_x[2] - 20 <= x && card_center_x[2] + 20 >= x) {
               return 14;
          }
          else if (card_center_x[3] - 20 <= x && card_center_x[3] + 20 >= x) {
               return 15;
          }
          else return 16;
     }
     else return 16;
}

void clean(int a) {
     int i_x = chooseCard[1] % 4;
     int i_y = chooseCard[1] / 4;

     glBegin(GL_POLYGON);
     glColor3f(0.7, 0.5, 1);
     glVertex2f(card_center_x[i_x] + 18, card_center_y[i_y] + 28);//右上
     glColor3f(1, 0.6, 0.7);
     glVertex2f(card_center_x[i_x] + 18, card_center_y[i_y] - 28);//右下
     glColor3f(1, 1, 1);
     glVertex2f(card_center_x[i_x] - 18, card_center_y[i_y] - 28);//左下
     glColor3f(0, 1, 1);
     glVertex2f(card_center_x[i_x] - 18, card_center_y[i_y] + 28);//左上
     glEnd();

     i_x = chooseCard[0] % 4;
     i_y = chooseCard[0] / 4;

     glBegin(GL_POLYGON);
     glColor3f(0.7, 0.5, 1);
     glVertex2f(card_center_x[i_x] + 18, card_center_y[i_y] + 28);
     glColor3f(1, 0.6, 0.7);
     glVertex2f(card_center_x[i_x] + 18, card_center_y[i_y] - 28);
     glColor3f(1, 1, 1);
     glVertex2f(card_center_x[i_x] - 18, card_center_y[i_y] - 28);
     glColor3f(0, 1, 1);
     glVertex2f(card_center_x[i_x] - 18, card_center_y[i_y] + 28);
     glEnd();

     glFlush();
     lock = false;
}

void calculate(int a) {
     if (page == 2) {
          play_time++;
          glutTimerFunc(1000, calculate, 1);
     }
}

void mouse(int btn, int state, int x, int y) {
     static int cardNo = 0;
     static int deleteCard[16];
     int which;
     float x1 = (x - (ww / 2)) / (ww / 340);
     float y1 = (-y * 2 / (wh / 170) + 170);
     //cout << x1 << endl << y1 << endl;
     if (lock)return;
     if (btn != GLUT_LEFT_BUTTON || state == GLUT_UP)return;

     if (page == 1) {
          float x1 = (x - (ww / 2)) / (ww / 340);
          float y1 = (-y * 2 / (wh / 170) + 170);
          if (x1 >= -15 && x1 <= 25) {
               if (y1 >= -50 && y1 <= -40) {
                    page = 2;
                    glutPostRedisplay();
                    calculate(0);
               }
          }
     }
     else if (page == 2) {
          which = pick(x1, y1);
          if (which == 16) return;
          for (int i = 0; i <= deleteIndex; i++) {
               if (which == deleteCard[i]) {
                    return;
               }
          }
          int i_x = which % 4;
          int i_y = which / 4;
          glTranslatef(card_center_x[i_x], card_center_y[i_y], 0);
          drawImage(card[which]);
          glTranslatef(-card_center_x[i_x], -card_center_y[i_y], 0);
          glFlush();

          if (cardNo == 0) {
               chooseCard[0] = which;
               cardNo = 1;
          }
          else if (cardNo == 1) {
               lock = true;
               cardNo = 0;
               chooseCard[1] = which;
               if (chooseCard[0] == chooseCard[1]) {
                    glutTimerFunc(10, clean, 1);
                    cardNo = 0;
                    return;
               }

               if (card[chooseCard[0]] == card[chooseCard[1]]) {
                    deleteIndex++;
                    deleteCard[deleteIndex] = chooseCard[0];
                    deleteIndex++;
                    deleteCard[deleteIndex] = chooseCard[1];
                    lock = false;
               }
               else if (card[chooseCard[0]] != card[chooseCard[1]]) {
                    glutTimerFunc(1000, clean, 1);
               }
               if (deleteIndex == 15) {
                    init_end();
                    page = 3;
                    glutPostRedisplay();
               }
          }
     }
     else if (page == 3) {
          float x1 = (x - (ww / 2)) / (ww / 340);
          float y1 = (-y * 2 / (wh / 170) + 170);
          if (x1 >= -40 && x1 <= 40) {
               if (y1 >= -50 && y1 <= -40) {
                    page = 2;
                    init();
                    glutPostRedisplay();
                    calculate(0);
               }
          }
     }
}

void init() {
     // random card order
     srand(time(NULL));
     int k = (rand() % 50) + 50;
     for (int i = 0; i < k; i++) {
          int a = (rand() % 15);
          int b = (rand() % 15);
          while (a == b) { b = (rand() % 15); }
          int temp = card[a];
          card[a] = card[b];
          card[b] = temp;
     }
     for (int i = 0; i < 16; i++) {
          cout << card[i] << " ";
     }
     //initial image
     init_image();
     //initial parameter
     deleteIndex = -1;
     play_time = 0;
}

void reshape(int w, int h) {
     GLfloat aspectRatio;
     if (h == 0)  h = 1;        //預防h為0,無法÷
     ww = w;
     wh = h;
     glViewport(0, 0, w, h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     aspectRatio = (GLfloat)w / (GLfloat)h;
     if (w <= h)
          glOrtho(-170, 170, -170 / aspectRatio,
               170 / aspectRatio, 1.0, -1.0);
     else
          glOrtho(-170 * aspectRatio,
               170 * aspectRatio, -170, 170,
               1.0, -1.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
}

int main() {
     glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
     glutInitWindowSize(700, 700);
     glutInitWindowPosition(0, 0);
     gluOrtho2D(-170, 170, -170, 170);
     glutCreateWindow("Sample");
     glutDisplayFunc(display);
     glutReshapeFunc(reshape);
     if (!lock) {
          glutMouseFunc(mouse);
     }
     init();
     glutMainLoop();
}