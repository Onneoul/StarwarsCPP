#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include <Windows.h>
#include "glut.h"
#include <stdio.h>
#include <math.h>


#define GL_PI 3.1415f
#define TextureWidth 4
#define TextureHeight 4

GLuint textureID, bottomTextureID, topTextureID1, topTextureID2, leftTextureID, rightTextureID;

GLdouble Width_factor = 1.0, Height_factor = 1.0;

double cameraTestz = 10;
double cameraTestx = 0, cameraTesty = -0.7;

double DeathstarX = 22, DeathstarY = 11, DeathstarZ = -124;
double airCraftX, airCraftY, airCraftZ;

int opening = 0;
int endingSequence = 0;

int crash = 0;
int ending = 0;


double movementX = 0, movementY = 0;
double speed = 10;


GLfloat     fovy, nearClip, farClip,
distance,
twistAngle,
elevationAngle,
azimAngle;

void gameOver(int crash);
void drawGameOver();
void drawDeathStar(GLUquadric* quadric, GLfloat x, GLfloat y, GLfloat z, GLfloat size);
//void bindTexture(const char* textureFilePath, int width, int height);

int Width = 800, Height = 800;

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Ŭ���� ���� ���� (������)
    glEnable(GL_DEPTH_TEST);  // ���� �׽�Ʈ Ȱ��ȭ

    // �ؽ�ó �ʱ�ȭ
    glGenTextures(1, &textureID);
    glGenTextures(1, &bottomTextureID);
    glGenTextures(1, &topTextureID1);
    glGenTextures(1, &topTextureID2);
    glGenTextures(1, &leftTextureID);
    glGenTextures(1, &rightTextureID);
}



double  TxVal = 1.0, VtxVal = 1.0, VvVal = 4.0;



void Init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
}
// �ؽ��� ����
//void Init() {
//    glClearColor(0.0, 0.0, 0.0, 0.0);
//    glShadeModel(GL_SMOOTH);
//
//    MyStripeImage();
//
//    glGenTextures(1, &MyTextureObject); // glGenTextures(2, MyTextureObject); <= ������, MyTextureObject [2]�� ���
//    glBindTexture(GL_TEXTURE_1D, MyTextureObject);
//    // ���� ���, glBindTexture(GL_TEXTURE_1D, MyTextureObject [0] );
//    // �Ǵ� glBindTexture(GL_TEXTURE_1D, MyTextureObject [1] );
//
//    glTexImage1D(GL_TEXTURE_1D, 0, 4, stripeImageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
//
//    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//    glTexGenfv(GL_S, GL_OBJECT_PLANE, ref_plane);
//
//    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT); 	  //GL_REPEAT, GL_CLAMP
//    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // GL_NEAREST, GL_LINEAR
//    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); 	// GL_MODULATE, GL_REPLACE
//
//    glEnable(GL_TEXTURE_GEN_S);
//    glEnable(GL_TEXTURE_1D);
//
//    // (�ִٸ�) �� ��° �ؽ��� ������
//}

//void bindTexture(const char* textureFilePath, int width, int height) {
//    int channels;
//    unsigned char* imageData = stbi_load(textureFilePath, &width, &height, &channels, 3);
//    if (!imageData) {
//        printf("Failed to load texture: %s\n", stbi_failure_reason());
//        return;
//    }
//
//    textureID = 0;
//    glGenTextures(1, &textureID);
//    glBindTexture(GL_TEXTURE_2D, textureID);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
//
//    stbi_image_free(imageData);
//}


void bindTexture(const char* textureFilePath, int width, int height, GLuint* textureID) {
    int channels;
    unsigned char* imageData = stbi_load(textureFilePath, &width, &height, &channels, STBI_rgb);
    if (!imageData) {
        printf("Failed to load texture: %s\n", stbi_failure_reason());
        return;
    }

    // �ؽ�ó ID ����
    glGenTextures(1, textureID);
    glBindTexture(GL_TEXTURE_2D, *textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    stbi_image_free(imageData);
}

void xWingTexture() {

}

void cockPitTexture() {

}

void tieFighterTexture() {

}

void laserTexture() {

}

// ��ü ���� �Լ�
void drawDeathStar(GLUquadric* quadric, GLfloat x, GLfloat y, GLfloat z, GLfloat size) {
    //Death star
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(x, y, z);
    gluSphere(quadric, size, 30, 30);
    glPopMatrix();
}

void TieFighter(GLfloat x, GLfloat y, GLfloat z) {
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glRotatef(90, 0, -1, 0);
    //glScalef(0.5, 0.5, 0.5);
    glColor3f(0.65, 0.65, 0.65);
    glPushMatrix();
    glTranslatef(x, y, z);
    gluSphere(gluNewQuadric(), 1.0, 40.0, 40.0);
    glPushMatrix();
    glColor3f(0.2, 1.0, 0.2);
    glColor3f(0.65, 0.65, 0.65);
    glScalef(6.0, 0.6, 1.0); // body
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2, 0.5, 1.0);
    glColor3f(0.65, 0.65, 0.65);
    glTranslatef(x - 3.0, y, z);
    glScalef(0.4, 5.0, 4.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x - 3.0, y, z);
    glColor3f(0.2, 0.2, 0.7);
    gluSphere(gluNewQuadric(), .4, 20., 20.0);
    glPopMatrix();  // right Solar Array Wing

    glPushMatrix();
    glColor3f(0.5, 0.2, 1.0);
    glColor3f(0.65, 0.65, 0.65);
    glTranslatef(x + 3.0, y, z);
    glScalef(0.4, 5.0, 4.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x + 3.0, y, z);
    glColor3f(0.2, 0.2, 0.7);
    gluSphere(gluNewQuadric(), .4, 20.0, 20.0);
    glPopMatrix();
    // left Solar Array Wing
    glPopMatrix();
}

void drawXWing(GLfloat x, GLfloat y, GLfloat z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    //glScalef(2, 2, 2);
    glPushMatrix(); // Body Start
    glScalef(.3, .3, .3);
    glPushMatrix(); // rear
    glColor3f(0.2, 0.2, 0.9);
    glBegin(GL_POLYGON);
    //front
    glVertex3f(3.0, -1.1, -1.5);
    glVertex3f(3.0, 1.1, -1.5);
    glVertex3f(3.0, 1.1, 1.5);
    glVertex3f(3.0, -1.1, 1.5);
    glEnd();

    glBegin(GL_POLYGON);
    //Top
    glVertex3f(-2.8, 1.1, -1.5);
    glVertex3f(3.0, 1.1, -1.5);
    glVertex3f(3.0, 1.1, 1.5);
    glVertex3f(-2.8, 1.1, 1.5);
    glEnd();

    glBegin(GL_POLYGON);
    //left
    glVertex3f(-2.8, -1.1, -1.5);
    glVertex3f(-2.8, 1.1, -1.5);
    glVertex3f(3.0, 1.1, -1.5);
    glVertex3f(3.0, -1.1, -1.5);
    glEnd();

    glBegin(GL_POLYGON);
    //right
    glVertex3f(-2.8, -1.1, 1.5);
    glVertex3f(-2.8, 1.1, 1.5);
    glVertex3f(3.0, 1.1, 1.5);
    glVertex3f(3.0, -1.1, 1.5);
    glEnd();

    glBegin(GL_POLYGON);
    //Bottom
    glVertex3f(-2.8, -1.1, -1.5);
    glVertex3f(3.0, -1.1, -1.5);
    glVertex3f(3.0, -1.1, 1.5);
    glVertex3f(-2.8, -1.1, 1.5);
    glEnd();

    glBegin(GL_POLYGON);
    //back
    glVertex3f(-2.8, -1.1, -1.5);
    glVertex3f(-2.8, 1.1, -1.5);
    glVertex3f(-2.8, 1.1, 1.5);
    glVertex3f(-2.8, -1.1, 1.5);
    glEnd();
    glPopMatrix();//rear End

    glPushMatrix(); // front Start
    glColor3f(1.0, 0.2, 0.2);

    glBegin(GL_POLYGON);
    //front
    glVertex3f(13, 0.475, 0.65);
    glVertex3f(13, 0.475, -0.65);
    glVertex3f(13, -0.475, -0.65);
    glVertex3f(13, -0.475, 0.65);
    glEnd();

    glColor3f(0.2, 0.8, 0.2);
    glBegin(GL_POLYGON);
    //left
    glVertex3f(3, 1.1, -1.5);
    glVertex3f(3, -1.1, -1.5);
    glVertex3f(13, -0.475, -0.65);
    glVertex3f(13, 0.475, -0.65);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    //bottom
    glVertex3f(3, -1.1, 1.5);
    glVertex3f(3, -1.1, -1.5);
    glVertex3f(13, -0.475, -0.65);
    glVertex3f(13, -0.475, 0.65);
    glEnd();

    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_POLYGON);
    //top
    glVertex3f(3, 1.1, 1.5);
    glVertex3f(3, 1.1, -1.5);
    glVertex3f(13, 0.475, -0.65);
    glVertex3f(13, 0.475, 0.65);
    glEnd();

    glColor3f(1.0, 0.2, 1.0);
    glBegin(GL_POLYGON);
    //right
    glVertex3f(3, 1.1, 1.5);
    glVertex3f(3, -1.1, 1.5);
    glVertex3f(13, -0.475, 0.65);
    glVertex3f(13, 0.475, 0.65);
    glEnd();
    glPopMatrix(); // front End
    glPopMatrix(); //Body End

    //////Left bottom wing
    glPushMatrix();
    // SpreadWing
    glTranslatef(0, 0.15, -0.05);
    glRotatef(15, -1, 0, 0);

    //Engine
    glPushMatrix();
    glTranslatef(-.4, -.4, -1);
    glRotatef(90, 0, 1, .0);
    glColor3f(.3, 1, .3);
    gluCylinder(gluNewQuadric(), .4, .4, .95, 30, 30);
    glTranslatef(0, -.1, -0.5);
    glColor3f(.3, .3, 1.);
    gluCylinder(gluNewQuadric(), .3, .3, .5, 30, 30);
    glPopMatrix();
    glPushMatrix(); // Wing Body
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_POLYGON);
    glVertex3f(.5, -.3025, -.5);
    glVertex3f(-0.5, -.3025, -.5);
    glVertex3f(-0.2, -.3025, -3.5);
    glVertex3f(.5, -.3025, -3.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(.5, -.05, -.5);
    glVertex3f(.5, -.3025, -.5);
    glVertex3f(.5, -.3025, -3.5);
    glVertex3f(.5, -.05, -3.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(0.5, -.05, -3.5);
    glVertex3f(0.5, -0.3025, -3.5);
    glVertex3f(-0.2, -0.3025, -3.5);
    glVertex3f(-0.2, -.05, -3.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-0.2, -.05, -3.5);
    glVertex3f(-.5, -.05, -.5);
    glVertex3f(-.5, -0.3025, -.5);
    glVertex3f(-0.2, -0.3025, -3.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(.5, -.05, -.5);
    glVertex3f(-0.5, -.05, -.5);
    glVertex3f(-0.2, -.05, -3.5);
    glVertex3f(.5, -.05, -3.5);
    glEnd();
    glPopMatrix(); // Wing Body End
    //    Gun
    glPushMatrix();
    glTranslatef(-.55, -.25, -3.5);
    glRotatef(90, 0, 1, .0);
    glColor3f(.7, .2, .2);
    gluCylinder(gluNewQuadric(), .18, .18, 1.2, 20, 20);
    glColor3f(.7, .2, .2);
    glTranslatef(0, 0, 1.1);
    gluCylinder(gluNewQuadric(), .1, .1, 1, 20, 20);
    glPopMatrix();
    glPopMatrix(); // right Bottom wing end

    //////Left Top Wing
    glPushMatrix();
    // SpreadWing
    glTranslatef(0, -0.15, -0.05);
    glRotatef(15, 1, 0, 0);

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_POLYGON);
    glVertex3f(.5, -.0025, -.5);
    glVertex3f(-0.5, -.0025, -.5);
    glVertex3f(-0.2, -.0025, -3.5);
    glVertex3f(.5, -.0025, -3.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(.5, .25, -.5);
    glVertex3f(.5, -.0025, -.5);
    glVertex3f(.5, -.0025, -3.5);
    glVertex3f(.5, .25, -3.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(0.5, .25, -3.5);
    glVertex3f(0.5, -0.0025, -3.5);
    glVertex3f(-0.2, -0.0025, -3.5);
    glVertex3f(-0.2, .25, -3.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-0.2, .25, -3.5);
    glVertex3f(-.5, .25, -.5);
    glVertex3f(-.5, -0.0025, -.5);
    glVertex3f(-0.2, -0.0025, -3.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(.5, .25, -.5);
    glVertex3f(-0.5, .25, -.5);
    glVertex3f(-0.2, .25, -3.5);
    glVertex3f(.5, .25, -3.5);
    glEnd();
    glPopMatrix();
    ////Engine
    glPushMatrix();
    glTranslatef(-.4, .4, -1);
    glRotatef(90, 0, 1, .0);
    glColor3f(.3, 1, .3);
    gluCylinder(gluNewQuadric(), .4, .4, .95, 30, 30);
    glTranslatef(0, .1, -0.5);
    glColor3f(.3, .3, 1.);
    gluCylinder(gluNewQuadric(), .3, .3, .5, 30, 30);
    glPopMatrix();
    //    Gun
    glPushMatrix();
    glTranslatef(-.55, .15, -3.5);
    glRotatef(90, 0, 1, .0);
    glColor3f(.7, .2, .2);
    gluCylinder(gluNewQuadric(), .18, .18, 1.2, 20, 20);
    glColor3f(.7, .2, .2);
    glTranslatef(0, 0, 1.1);
    gluCylinder(gluNewQuadric(), .1, .1, 1, 20, 20);
    glPopMatrix();
    glPopMatrix();

    ////Right bottom wing
    glPushMatrix();
    glTranslatef(0, 0.15, 0.05);
    glRotatef(15, 1, 0, 0);
    //    Engine
    glPushMatrix();
    glTranslatef(-.4, -.4, 1);
    glRotatef(90, 0, 1, .0);
    glColor3f(.3, 1, .3);
    gluCylinder(gluNewQuadric(), .4, .4, .95, 30, 30);
    glTranslatef(0, 0, -0.5);
    glColor3f(.3, .3, 1.);
    gluCylinder(gluNewQuadric(), .3, .3, .5, 30, 30);
    glPopMatrix();
    glPushMatrix(); // wing body
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_POLYGON);
    glVertex3f(.5, -.3025, .5);
    glVertex3f(-0.5, -.3025, .5);
    glVertex3f(-0.2, -.3025, 3.5);
    glVertex3f(.5, -.3025, 3.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(.5, -.05, .5);
    glVertex3f(.5, -.3025, .5);
    glVertex3f(.5, -.3025, 3.5);
    glVertex3f(.5, -.05, 3.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(0.5, -.05, 3.5);
    glVertex3f(0.5, -0.3025, 3.5);
    glVertex3f(-0.2, -0.3025, 3.5);
    glVertex3f(-0.2, -.05, 3.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-0.2, -.05, 3.5);
    glVertex3f(-.5, -.05, .5);
    glVertex3f(-.5, -0.3025, .5);
    glVertex3f(-0.2, -0.3025, 3.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(.5, -.05, .5);
    glVertex3f(-0.5, -.05, .5);
    glVertex3f(-0.2, -.05, 3.5);
    glVertex3f(.5, -.05, 3.5);
    glEnd();
    glPopMatrix();
    ////Gun
    glPushMatrix();
    glTranslatef(-.55, -.25, 3.5);
    glRotatef(90, 0, 1, .0);
    glColor3f(.7, .2, .2);
    gluCylinder(gluNewQuadric(), .2, .2, 1.2, 20, 20);
    glColor3f(.7, .2, .2);
    glTranslatef(0, 0, 1.1);
    gluCylinder(gluNewQuadric(), .1, .1, 1, 20, 20);
    glPopMatrix();
    glPopMatrix();

    //Right top wing
    glPushMatrix();
    // SpreadWing
    glTranslatef(0, -0.15, 0.05);
    glRotatef(15, -1, 0, 0);

    ////Engine
    glPushMatrix();
    glTranslatef(-.4, .4, 1);
    glRotatef(90, 0, 1, .0);
    glColor3f(.3, 1, .3);
    gluCylinder(gluNewQuadric(), .4, .4, .95, 30, 30);
    glTranslatef(0, .1, -0.5);
    glColor3f(.3, .3, 1.);
    gluCylinder(gluNewQuadric(), .3, .3, .5, 30, 30);
    glPopMatrix();
    glPushMatrix(); // wing Body
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_POLYGON);
    glVertex3f(.5, -.0025, .5);
    glVertex3f(-0.5, -.0025, .5);
    glVertex3f(-0.2, -.0025, 3.5);
    glVertex3f(.5, -.0025, 3.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(.5, .25, .5);
    glVertex3f(.5, -.0025, .5);
    glVertex3f(.5, -.0025, 3.5);
    glVertex3f(.5, .25, 3.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(0.5, .25, 3.5);
    glVertex3f(0.5, -0.0025, 3.5);
    glVertex3f(-0.2, -0.0025, 3.5);
    glVertex3f(-0.2, .25, 3.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-0.2, .25, 3.5);
    glVertex3f(-.5, .25, .5);
    glVertex3f(-.5, -0.0025, .5);
    glVertex3f(-0.2, -0.0025, 3.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(.5, .25, .5);
    glVertex3f(0.5, .25, .5);
    glVertex3f(0.2, .25, 3.5);
    glVertex3f(.5, .25, 3.5);
    glEnd();
    glPopMatrix();
    ////Gun
    glPushMatrix();
    glTranslatef(-.55, .15, 3.5);
    glRotatef(90, 0, 1, .0);
    glColor3f(.7, .2, .2);
    gluCylinder(gluNewQuadric(), .18, .18, 1.2, 20, 20);
    glColor3f(.7, .2, .2);
    glTranslatef(0, 0, 1.1);
    gluCylinder(gluNewQuadric(), .1, .1, 1, 20, 20);
    glPopMatrix();
    glPopMatrix();


    glPopMatrix();
}

void XWingChasingTie(GLfloat XwingX, GLfloat XwingY, GLfloat XwingZ, GLfloat TieX, GLfloat TieY, GLfloat TieZ) {
    glPushMatrix();
    glTranslatef(XwingX, XwingY, XwingZ);
    drawXWing(XwingX, XwingY, XwingZ);

    glPushMatrix();
    glTranslatef(TieX, TieY - 2.5, TieZ + 20);
    glScalef(.6, .6, .6); // Tie Scale
    TieFighter(TieZ, TieY, TieX);
    glPopMatrix();
    glPopMatrix();
}

void TieChasingXWing(GLfloat TieX, GLfloat TieY, GLfloat TieZ, GLfloat XwingX, GLfloat XwingY, GLfloat XwingZ) {
    glPushMatrix();
    glPushMatrix();
    glTranslatef(TieX, TieY - 2.5, TieZ + 20);
    glScalef(.6, .6, .6); // Tie Scale
    TieFighter(TieZ, TieY, TieX);
    glPopMatrix();
    glTranslatef(XwingX, XwingY, XwingZ);
    drawXWing(XwingX, XwingY, XwingZ);
    glPopMatrix();
}

void drawCockpit() {
    glColor3f(0.35, 0.35, 0.35); // ������
    glBegin(GL_POLYGON);
    glVertex3f(1.3, 0.6, 0);
    glVertex3f(1.8, -1, 0);
    glVertex3f(6, 0.4, 0);
    glVertex3f(2, 0.6, 0);
    glEnd();

    glColor3f(0.35, 0.35, 0.35); //���� 
    glBegin(GL_POLYGON);
    glVertex3f(-1.3, 0.6, 0);
    glVertex3f(-1.8, -1, 0);
    glVertex3f(-3, -1, 0);
    glVertex3f(-2, 0.5, 0);
    glEnd();


    //���
    glColor3f(0.25, 0.25, 0.25);
    glBegin(GL_POLYGON);
    glVertex3f(-1.8, 2.5, 0);
    glVertex3f(-0.4, 0.5, 0);
    glVertex3f(-0.4, 0.3, 0);
    glVertex3f(-2, 2.3, 0);
    glEnd();

    glColor3f(0.25, 0.25, 0.25);
    glBegin(GL_POLYGON);
    glVertex3f(1.8, 2.5, 0);
    glVertex3f(0.4, 0.5, 0);
    glVertex3f(0.4, 0.3, 0);
    glVertex3f(2, 2.3, 0);
    glEnd();

    glColor3f(0.25, 0.25, 0.25);
    glBegin(GL_POLYGON);
    glVertex3f(5, 2.3, 0);
    glVertex3f(-5, 2.3, 0.3);
    glVertex3f(-5, 2.5, 0.3);
    glVertex3f(5, 2.5, 0);
    glEnd();

    glColor3f(1, 0, 0); // �����
    glBegin(GL_POLYGON);
    glVertex3f(-2, -0.2, 0);
    glVertex3f(-1.3, 0.7, 0);
    glVertex3f(1.3, 0.7, 0);
    glVertex3f(2, -0.2, 0);
    glEnd();

    glPopMatrix();
}

void laser(int color) {
    int colour = color;

    if (colour == 1) { // �ʷϻ�
        glPushMatrix();
        glEnable(GL_LIGHTING);
        glColor3f(0.8, 1., .8);
        gluCylinder(gluNewQuadric(), 1, 1, 3, 30, 30);
        glPopMatrix();
    }
    else {
        glPushMatrix(); // ������
        glEnable(GL_LIGHTING);
        glColor3f(1, .8, .8);
        gluCylinder(gluNewQuadric(), 1, 1, 3, 30, 30);
        glPopMatrix();
    }

}

void drawTurret(double angle) {
    glPushMatrix();
    glColor3f(1, 0.2, .3);

    glPushMatrix();
    glScalef(1, 2, 1);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(-.2, .7, .4);
    glRotatef(angle, -1, 0, 0);
    gluCylinder(gluNewQuadric(), 0.15, 0.1, .9, 20, 20);
    glTranslatef(0.4, 0, 0);
    gluCylinder(gluNewQuadric(), 0.15, 0.1, .9, 20, 20);
    glPopMatrix();
    glPopMatrix();
}


// ȭ�� ���� ���� �Լ�

void crashCheck() { // �浹 ���� Ȯ��
    if (((cameraTestx >= -1.4) && (cameraTestx <= 1.4)) && ((cameraTesty <= 1.4) && (cameraTesty >= -1.9))) {
        crash = 0;
    }
    else {
        crash = 1;
        gameOver(crash);
    }
}

void gameOver(int crash) {
    // ���� ���� ȭ�� ����
    if (crash == 1) {
        printf("Game Over\n");
        //Sleep(10000);
    }
}

void open(int status) { // ������ �� ���� �Լ�
    if (opening == 0) {
        if (DeathstarX >= 0) { DeathstarX -= 0.2; }
        if (DeathstarY >= 0) { DeathstarY -= 0.1; }
        if (DeathstarZ <= 20) { DeathstarZ += 0.5; }

        if (DeathstarX <= 0 && DeathstarY <= 0 && DeathstarZ >= - 20) {
            // Opening�� 0����
            opening = 1;
            //printf("Opening is End. Opening is %d\n", opening);
            airCraftX = 0, airCraftY = 0, airCraftZ = 0;
        }
        else {
            opening = 0;
            printf("DeathStarX = %f, Y = %f, Z = %f\n", DeathstarX, DeathstarY, DeathstarZ);
        }
    }
}

void end(int status) { // ���� �� ���� �Լ�
    if (endingSequence == 0 && opening == 1) {
        // �̻��� �߻� ���
    }
    else if (endingSequence == 1) {
        // ������Ÿ ���� ���
    }
}


void road() { // �� ȭ�� ���� �Լ�
    crashCheck();
    open(opening);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();


    glEnable(GL_TEXTURE_2D);

    // ������Ÿ ��

    if (opening == 1) {
        glPushMatrix();
        glScalef(0.2, 0.2, 0.2);
        glTranslatef(-3, 15, 0);
        TieChasingXWing(cameraTestx, cameraTesty, cameraTestz, cameraTestx + 4, cameraTesty, cameraTestz);
        glPopMatrix();

        printf("break2\n");
        //Bottom
        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, bottomTextureID);
        printf("break3\n");
        bindTexture("deathstar_bottom_texture1.bmp", 479, 960, &bottomTextureID);
        printf("break4\n");
        glBegin(GL_POLYGON); // Bottom Top

        printf("break5\n");
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-2 + cameraTestx, -2 + cameraTesty, 200 + cameraTestz);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-2 + cameraTestx, -2 + cameraTesty, -200 + cameraTestz);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(2 + cameraTestx, -2 + cameraTesty, -200 + cameraTestz);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(2 + cameraTestx, -2 + cameraTesty, 200 + cameraTestz);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glPopMatrix();


        glColor3f(0.8, 0.8, 0.8); //// Endpoint
        glPushMatrix();
        glColor3f(0.6, 0.4, 0.3);
        glBegin(GL_POLYGON); // End Point front
        glVertex3f(-2 + cameraTestx, -2.5 + cameraTesty, -200 + cameraTestz);
        glVertex3f(-2 + cameraTestx, 0.5 + cameraTesty, -200 + cameraTestz);
        glVertex3f(2 + cameraTestx, 0.5 + cameraTesty, -200 + cameraTestz);
        glVertex3f(2 + cameraTestx, -2.5 + cameraTesty, -200 + cameraTestz);
        glEnd();
        glPopMatrix();


        glPushMatrix();
        glColor3f(0.2, 0.2, 1.0);
        glTranslatef(-16 + cameraTestx, -1 + cameraTesty, cameraTestz);
        glScalef(28, 3, 400);
        glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
        glColor3f(1.0, 0.2, 0.2);
        glBegin(GL_POLYGON); // Left Top
        glVertex3f(-2 + cameraTestx, 0.5 + cameraTesty, 200 + cameraTestz);
        glVertex3f(-2 + cameraTestx, 0.5 + cameraTesty, -200 + cameraTestz);
        glVertex3f(-30 + cameraTestx, 0.5 + cameraTesty, -200 + cameraTestz);
        glVertex3f(-30 + cameraTestx, 0.5 + cameraTesty, 200 + cameraTestz);
        glEnd();

        //glEnable(GL_TEXTURE_2D);
        //bindTexture("deathstar_left_texture2.bmp", 480, 187);
        //glBindTexture(GL_TEXTURE_2D, leftTextureID);
        glColor3f(1.0, 0.2, 0.2);
        glBegin(GL_POLYGON); // Left Wall
        glVertex3f(-2 + cameraTestx, 0.5 + cameraTesty, 200 + cameraTestz);
        glVertex3f(-2 + cameraTestx, -2.5 + cameraTesty, 200 + cameraTestz);
        glVertex3f(-2 + cameraTestx, -2.5 + cameraTesty, -200 + cameraTestz);
        glVertex3f(-2 + cameraTestx, 0.5 + cameraTesty, -200 + cameraTestz);
        glEnd();
        glPopMatrix();
        //glBindTexture(GL_TEXTURE_2D, 0);



        glPushMatrix(); //// Right
        glColor3f(0.5, 0.5, 0.5);
        glTranslatef(16 + cameraTestx, -1 + cameraTesty, cameraTestz);
        glScalef(28, 3, 400);
        glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
        glColor3f(1.0, 0.2, 0.2);
        glBegin(GL_POLYGON); // Right Top
        glVertex3f(2 + cameraTestx, 0.5 + cameraTesty, 200 + cameraTestz);
        glVertex3f(2 + cameraTestx, 0.5 + cameraTesty, -200 + cameraTestz);
        glVertex3f(30 + cameraTestx, 0.5 + cameraTesty, -200 + cameraTestz);
        glVertex3f(30 + cameraTestx, 0.5 + cameraTesty, 200 + cameraTestz);
        glEnd();

        glColor3f(0.2, 0.2, 1.0);
        glBegin(GL_POLYGON); // Right Wall
        glVertex3f(2 + cameraTestx, 0.5 + cameraTesty, 200 + cameraTestz);
        glVertex3f(2 + cameraTestx, -2.5 + cameraTesty, 200 + cameraTestz);
        glVertex3f(2 + cameraTestx, -2.5 + cameraTesty, -200 + cameraTestz);
        glVertex3f(2 + cameraTestx, 0.5 + cameraTesty, -200 + cameraTestz);
        glEnd();
        glPopMatrix();

        // ���� ���
        glPushMatrix();
        glRotatef(0.4, 0, 0, 1);
        glTranslatef(0, -11, 0);
        glScalef(7, 7, 7);
        drawCockpit();
        glPopMatrix();
    }
    else {
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, textureID);
            bindTexture("deathstartest.bmp", 1024, 512, &textureID);
            GLUquadric* deathStarQuadric = gluNewQuadric();
            gluQuadricTexture(deathStarQuadric, GL_TRUE);
            drawDeathStar(deathStarQuadric, DeathstarX, DeathstarY, DeathstarZ, 5);
            glBindTexture(GL_TEXTURE_2D, 0);
        glPopMatrix();
    }

    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

void drawGameOver() {
    crashCheck();
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.7, 0.3, 0.4);

    // ������Ÿ �� �̵� �׽�Ʈ
    //// Endpoint
    glPushMatrix();
    glTranslatef(cameraTestx, -1 + cameraTesty, cameraTestz);
    glScalef(4, 2, 400);
    glutSolidCube(1);
    glPopMatrix();

    //// Bottom
    glPushMatrix();
    glTranslatef(cameraTestx, -2.5 + cameraTesty, cameraTestz);
    glScalef(4, 1, 400);
    glutSolidCube(1);
    glPopMatrix();

    //// Left
    glPushMatrix();
    glTranslatef(-16 + cameraTestx, -1 + cameraTesty, cameraTestz);
    glScalef(28, 3, 400);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix(); //// Right
    glTranslatef(16 + cameraTestx, -1 + cameraTesty, cameraTestz);
    glScalef(28, 3, 400);
    glutSolidCube(1);
    glPopMatrix();



    // ���� ���
    glPushMatrix();
    glTranslatef(0, -12, 0);
    glScalef(6, 6, 6);
    drawCockpit();
    glPopMatrix();

    glutSwapBuffers();
}


void Move(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        movementY += 10;
        glutPostRedisplay();
        printf("Current Location X = %f, Y = %f. Speed is %f\n", movementX, movementY, speed);
        break;
    case 'a':
        movementX += 10;
        glutPostRedisplay();
        printf("Current Location X = %f, Y = %f. Speed is %f\n", movementX, movementY, speed);
        break;
    case 's':
        movementY -= 10;
        glutPostRedisplay();
        printf("Current Location X = %f, Y = %f. Speed is %f\n", movementX, movementY, speed);
        break;
    case 'd':
        movementX -= 10;
        glutPostRedisplay();
        printf("Current Location X = %f, Y = %f. Speed is %f\n", movementX, movementY, speed);
        break;

    case 'r':
        speed += 10;
        printf("Current Location X = %f, Y = %f. Speed is %f\n", movementX, movementY, speed);
        break;
    case 'f':
        speed -= 10;
        printf("Current Location X = %f, Y = %f. Speed is %f\n", movementX, movementY, speed);
        break;

    default:
        printf("Current Key = %c\n", key);
        break;
    }
}

void acceleration(double currentSpeed) {
    if ((currentSpeed += (currentSpeed / (currentSpeed * 2))) <= 600) {
        speed += currentSpeed / (currentSpeed * 2);
        cameraTestz = speed;
    }
    else {
        speed += currentSpeed / (currentSpeed * 4);
        cameraTestz = speed;
    }
}

void deAcceleration(int currentSpeed) {
    if (currentSpeed != 0) {
        speed -= 0.5 * currentSpeed;
        cameraTestz = speed;
    }
}


void gamePlay() {

}

void cameraTest(unsigned char key, int x, int y) {
    switch (key)
    {
    case 'w':
        cameraTesty -= 0.1;
        printf("Current Location X = %.1f, Y = %.1f. Speed is %.1f\n", cameraTestx, cameraTesty, cameraTestz);
        glutPostRedisplay();
        break;
    case 'a':
        cameraTestx += 0.1;
        printf("Current Location X = %.1f, Y = %.1f. Speed is %.1f\n", cameraTestx, cameraTesty, cameraTestz);
        glutPostRedisplay();
        break;
    case 's':
        cameraTesty += 0.1;
        printf("Current Location X = %.1f, Y = %.1f. Speed is %.1f\n", cameraTestx, cameraTesty, cameraTestz);
        glutPostRedisplay();
        break;
    case 'd':
        cameraTestx -= 0.1;
        printf("Current Location X = %.1f, Y = %.1f. Speed is %.1f\n", cameraTestx, cameraTesty, cameraTestz);
        glutPostRedisplay();
        break;

    case 'r':
        //acceleration(speed);
        speed += speed / 42.1;
        cameraTestz = speed;
        printf("Current Location X = %.1f, Y = %.1f. Speed is %f\n", cameraTestx, cameraTesty, cameraTestz);
        break;
    case 'f':
        //deAcceleration(speed);
        speed -= speed / 31.5;
        cameraTestz = speed;
        printf("Current Location X = %.1f, Y = %.1f. Speed is %f\n", cameraTestx, cameraTesty, cameraTestz);
        break;

    default:
        printf("Current Key = %c\n", key);
        break;
    }
}

void cameraTestReshape2(int w, int h) {

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 220.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 20, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void myTimer(int value) {
    glutPostRedisplay();
    glutTimerFunc(16.6, myTimer, 0);
}

int main() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(800, 800);
    //glutInitWindowSize(Width, Height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Battle of DeathStar");
    init();

    glutDisplayFunc(road);
    glutReshapeFunc(cameraTestReshape2);
    //LoadGLTextures();
    glutKeyboardFunc(cameraTest);
    glutTimerFunc(16.6, myTimer, 0);

    glutMainLoop();

    return 0;
}
