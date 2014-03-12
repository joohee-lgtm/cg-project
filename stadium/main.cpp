//
//  main.cpp
//  stadium
//
//  Created by KIMJOOHWEE on 2014. 1. 12..
//  Copyright (c) 2014년 KIMJOOHWEE. All rights reserved.
//

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <iostream>

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

#define GL_PI 3.1415f

GLfloat lightPos[] = { 60.0f, -80.0f, -500.0f, 1.0f };

void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-300.0f, 300.0f, 300.0f, -300.0f, 800.0f, -300.0f);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reDrawGo(int value){
    
    xRot -= 5.0f;
    yRot += 5.0f;
    
    glutPostRedisplay();
}

void reDrawBack(int value){
    xRot += 5.0f;
    yRot -= 5.0f;
    glutPostRedisplay();
}

void bottomSet(){
	glPushMatrix();
    
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(70.0f, 0.0f, 1.0f, 0.0f);
    
    glTranslated(0.0f, -150.0f, 150.0f);

    glBegin(GL_QUADS);
    
    // 왼쪽 벽
	glColor3ub(183, 183, 183);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -350.0f);
	glVertex3f(0.0f, -35.0f, -350.0f);
	glVertex3f(0.0f, -35.0f, 0.0f);
    
    // 오른쪽 벽
	glColor3ub(183, 183, 0);
    glVertex3f(0.0f, -35.0f, 0.0f);
	glVertex3f(350.0f, -35.0f, 0.0f);
    glVertex3f(350.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

	// 바닥
	glColor3ub(0, 255, 0);
    glTexCoord3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord3f(350.0f, 0.0f, 0.0f);
    glVertex3f(350.0f, 0.0f, 0.0f);
    glTexCoord3f(350.0f, 0.0f, -350.0f);
    glVertex3f(350.0f, 0.0f, -350.0f);
    glTexCoord3f(0.0f, 0.0f, -350.0f);
    glVertex3f(0.0f, 0.0f, -350.0f);

	glEnd();
	glPopMatrix();
}


void ballSet(){
	//공
	glPushMatrix();

    glTranslated(100.0f, -130.0f, 150.0f);
    
    glTranslated(xRot, yRot, -600.0f);
	glColor3ub(255, 255, 255);
	glutSolidSphere(10, 100, 100);
	glPopMatrix();
}

void KeyControl(int key, int x, int y)
{
    if (key == GLUT_KEY_DOWN){
        if(xRot==0.0f && yRot==0.0f){
            for(int i=0; i<30; i++)
                glutTimerFunc(40, reDrawGo, 1);
        }
    }
    
    if (key == GLUT_KEY_UP){
        if(xRot==-150.0f && yRot==150.0f){
            for(int i=0; i<30; i++)
                glutTimerFunc(40, reDrawBack, 1);
        }
    }
    
    std::cout << "x값";
    std::cout << xRot;
    std::cout << "y값";
    std::cout << yRot;
}

void RenderScene(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFrontFace(GL_CW);
    
    glPushMatrix();
    glScalef(0.8f, 1.0f, 1.0f);
	bottomSet();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-10.0f);
	ballSet();
    glPopMatrix();
    
    // 조명 위치 확인하기
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.f, 0.f, 0.f);
    glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
    glutSolidSphere(3.f, 30, 30);
    glPopMatrix();
    
	glutSwapBuffers();
}

void SetupRC()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
    
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
	GLfloat ambientLight[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat specularLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat material_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glEnable(GL_LIGHTING);
    
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glEnable(GL_LIGHT0);
    
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("stadium");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
    return 0;
}



