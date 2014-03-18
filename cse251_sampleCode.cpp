#include<stdio.h>
#include<stdlib.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glaux.h>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

// Function Declarations
void drawScene();
void update(int value);
void drawBox(float len);
void drawBox1(float len);
void drawBall(float rad);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);
void drawTurret(float len);
void drawLaser(float len);
void drawSpider();
void drawSpidey(float rad);
void update1(int value);
void changeit(int value);
void print();
void drawAragog();
void dragwithmouse(int x,int y);
void printtext(int x,int y,string String);
// Global Variables
int score=0;
int n=0,i=0,n1=0,j=0;
float speed=0.1f;
float laser_y=0.0f;
float ball_x = 0.0f;
float ball_y = -2.0f;
float ball_velx = 0.01f;
float ball_vely = 0.02f;
float ball_rad = 0.2f;
float box_len = 4.0f;
float tri_x = 0.0f;
float tri_y = -1.5f;
float theta = 0.0f;
float box_x=-0.4075f*box_len;//-1.63f
float box_x1=0.4075f*box_len;
float box_y=-0.4075f*box_len;
float box_y1=-0.4075f*box_len;
float box_len1=0.1625f*box_len;//0.65
float turret_len=0.0045f*box_len;//0.018f;
int flag=3;
bool pause= false;
bool flag1 =true;
float angle=0.0f;
float xcomp=0.0f;
float ycomp=0.0f;
int fl = 0;
char c[300];
typedef struct laser
{
	float x1;
	float y1;
	float theta;
	float speedx;
	float speedy;
	int flag;
}lassie;
typedef struct spider
{
	float x;
	float y;
	float speed;
	double color;
	bool flag;
	bool dead;
}spider;
spider spidey[1000];
lassie struc[1000];
int w;
int h;
int WindowWidth;
int WindowHeight;
//GLUquadricObj *quadrics=gluNewQuadric();
//quadrics=gluNewQuadric();

int main(int argc, char **argv) {

//	scanf("Initial Position of Cannon %f\n",&ball_x);
//	scanf("Initial Position of Green Basket %f\n",&box_x1);
//	scanf("Initial Position of Red Basket %f\n",&box_x);
	ball_rad=0.05*box_len;
	ball_y=-box_len/2;
	box_x=-0.4075f*box_len;//-1.63f
	box_x1=0.4075f*box_len;
	box_y=-0.4075f*box_len;
	box_y1=-0.4075f*box_len;
	box_len1=0.1625f*box_len;//0.65
	turret_len=0.0045f*box_len;//0.018f;
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	w = glutGet(GLUT_SCREEN_WIDTH);
	h = glutGet(GLUT_SCREEN_HEIGHT);
	scanf("%d%d",&w,&h);
	int windowWidth = w ;//* (2.5 / 3);
	int windowHeight = h;// * (2.5 / 3);
	WindowWidth=windowWidth;
	WindowHeight=windowHeight;

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

	glutCreateWindow("Arachnophobia");  // Setup the window
	initRendering();

	// Register callbacks
	//if(!pause)
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(handleMouseclick);
	glutMotionFunc(dragwithmouse);
	glutReshapeFunc(handleResize);
	//	if(!pause)
	{
		glutTimerFunc(10, update, 0);
		glutTimerFunc(2000,update1,0);
	}
	glutMainLoop();
	return 0;
}

// Function to draw objects on the screen
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	// Draw Box
	glTranslatef(0.0f, 0.0f, -5.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawBox(box_len);
	//Draw Box 1
	glPushMatrix();
	glTranslatef(box_x,box_y,0.0f);
	glColor3f(1.0f,0.0f,0.0f);
	drawBox1(box_len1);
	glPopMatrix();
	//Draw Side Boxes
	glPushMatrix();
	glTranslatef(box_len,0.0f,0.0f);
	glColor3f(148.0f,0.0f,300.0f);
	drawBox(box_len);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-box_len,0.0f,0.0f);
	glColor3f(148.0f,0.0f,300.0f);
	drawBox(box_len);
	glPopMatrix();
	//Draw Box 2
	glPushMatrix();
	glTranslatef(box_x1,box_y1,0.0f);
	glColor3f(0.0f,1.0f,0.0f);
	drawBox1(box_len1);
	glPopMatrix();
	// Draw Ball
	glPushMatrix();
	glTranslatef(ball_x, ball_y, 0.0f);
	glColor3f(0.7f, 0.7f, 0.7f);
	glScalef(box_len/2,box_len/2,box_len/2);
	drawBall(ball_rad);
	glColor3f(300.0f,0.0f,300.0f);
	glRotatef(theta,0.0f,0.0f,1.0f);
	drawTurret(turret_len);
	glPopMatrix();
	//Draw Laser
	for(i=0;i<n;i++)
	{	glPushMatrix();
		//		laser_y=ball_y;
		glTranslatef(struc[i].x1, struc[i].y1, 0.0f);
		glScalef(box_len/2,box_len/2,box_len/2);
		glColor3f(148.0f,0.0f,300.0f);
		if(struc[i].flag==0)
			glRotatef(struc[i].theta,0.0f,0.0f,1.0f);
		else
			glRotatef(-struc[i].theta,0.0f,0.0f,1.0f);
		drawLaser(turret_len);
		glPopMatrix();
	}
	//Draw Spidey
	for(i=0;i<n1;i++)
	{
		if(spidey[i].dead==false)
		{
			glPushMatrix();
			glTranslatef(spidey[i].x,spidey[i].y,0.0f);
			if(spidey[i].color>=1&&spidey[i].color<2)
				glColor3f(1.0f,0.0f,0.0f);
			else if(spidey[i].color>=2&&spidey[i].color<3)
				glColor3f(0.0f,1.0f,0.0f);
			else if(spidey[i].color>=3&&spidey[i].color<4)
				glColor3f(0.0f,0.0f,0.0f);
			//	drawSpidey(0.2f);
			glScalef(0.05f,0.05f,0.05f);
			drawAragog();
			glPopMatrix();
		}
	}
	if (fl == 1)
	{
		printtext(box_len*155,box_len*100,"GAME OVER");
	}
	sprintf(c,"Score = %d",score);
	printtext(box_len*155,box_len*160,c);
	/*	// Draw Triangle
		glPushMatrix();
		glTranslatef(tri_x, tri_y, 0.0f);
		glRotatef(theta, 0.0f, 0.0f, 1.0f);
		glScalef(0.5f, 0.5f, 0.5f);
		drawTriangle();
		glPopMatrix();*/

	/*	//Draw Cylinder
		gluQuadricTexture(quadrics, true);

	//Draw the cylinder and the sphere
	glPushMatrix();                        //save first position
	//Draw the cylinder
	glTranslatef(0.0f, -1.0f, 0.0f);      //Move to cylinder center
	glPushMatrix();                       //save cylinder center
	glRotatef(90.0f, 1.0f, 0.0f, 0.f);  //cylinder rotation
	glTranslatef(-1.5f,0.0f,0.0f);            //go to the bottom of the cylinder
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);        //put the cylinder horizontal
	//Cylinder render (fill or line)
	gluQuadricDrawStyle(quadrics, GLU_FILL);
	gluCylinder(quadrics, 0.5, 0.5, 1.5, 20, 20);
	glPopMatrix();                        //load cylinder center
	//	glRotatef(90.0f,0.0f,0.0f,1.0f);*/

	glPopMatrix();
	glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void changeit(int value)
{
	flag1=true;
}
void drawSpider()
{
	double min=-0.425*box_len,max=0.425*box_len;double min2=1;double max2=4;
	double f=(max - min) * ( (double)rand() / (double)RAND_MAX ) + min;
	double color=(max2-min2) * ( (double)rand() / (double)RAND_MAX ) + min2;
	//	double f = (double)rand() / 2;
	//	spidey[n1].x=(-2+f*(4));
	spidey[n1].x=f;
	spidey[n1].y=box_len/2;
	spidey[n1].color=color;
	spidey[n1].flag=true;
	spidey[i].dead=false;
	n1++;
}
void update(int value) {
	if(pause==false)
	{
		// Handle ball collisions with box
		if(ball_x + ball_rad >0.475*box_len) 
			ball_x -= speed;
		if(ball_x - ball_rad < -0.475*box_len)
			ball_x += speed;
		if(box_x+box_len1/2>box_len/2) 
			box_x -=speed;
		if(box_x-box_len1/2<-box_len/2)
			box_x +=speed;
		if(box_x1+box_len1/2>box_len/2)
			box_x1 -=speed;
		if(box_x1-box_len1/2<-box_len/2)
			box_x1 +=speed;
		for(i=0;i<n1;i++)
		{
			/*if(spidey[i].color>=3&&spidey[i].color<4)
			  {
			  if(spidey[i].y<=(-box_len/2+0.23))
			  {
			  printf("\n\nGAMEOVER\n\n");
			  print();
			//pause=true;
			exit(0);
			}
			}*/
			if(spidey[i].y<=(-box_len/2+0.23))
			{
				if(spidey[i].flag==true)
				score-=5;
				spidey[i].flag=false;
			}
			if(spidey[i].x<=ball_x+ball_rad+0.1 && spidey[i].x>=ball_x-ball_rad-0.1 && spidey[i].y <=(-box_len/2+0.23))
			{
			//	printf("\n\nGAMEOVER\n\n");
				fl = 1;
				pause=true;
				//pause=true;
				//exit(0);
			}
		}
		for(i=0;i<n;i++)
			for(j=0;j<n1;j++)
			{
				if(/*spidey[j].color>=3&& spidey[j].color<4 && */spidey[j].flag==true)
					if((struc[i].x1<(spidey[j].x+ball_rad)&&struc[i].x1>(spidey[j].x-ball_rad))&&((struc[i].y1+0.2)<(spidey[j].y+ball_rad)&&(struc[i].y1+0.2)>(spidey[j].y-ball_rad)))
					{
						if(spidey[i].color>=3 && spidey[i].color<4)
							score+=2;
						struc[i].y1=1000;
						spidey[j].y=1000000;
						spidey[j].dead=true;
					}
			}
		for(i=0;i<n1;i++)
		{
			if(spidey[i].flag==true)
			{
				if(spidey[i].color>=1&&spidey[i].color<2)
				{
					if(spidey[i].x >= box_x-(box_len1/2) &&spidey[i].x <= box_x+(box_len1/2)&&spidey[i].y+ball_rad <=box_y+box_len1/2)
					{
						score+=2;
						spidey[i].y=-1000;
						spidey[i].dead=true;
					}
				}
				else if(spidey[i].color>=2&&spidey[i].color<3)
					if(spidey[i].x >= box_x1-(box_len1/2) &&spidey[i].x <= box_x1+(box_len1/2)&&spidey[i].y+ball_rad <=box_y1+box_len1/2)
					{
						score+=2;
						spidey[i].y=-1000;
						spidey[i].dead=true;
					}
			}
		}
		// Update position of ball
		//	ball_x += ball_velx;
		//laser_y += ball_vely;
		for(i=0;i<n;i++)
		{
			if((struc[i].x1+(0.2f*sin(DEG2RAD(-struc[i].theta))))<=-box_len/2 || (struc[i].x1+(0.2f*sin(DEG2RAD(-struc[i].theta))))>=0.475*box_len)
			{
				//	if(struc[i].flag==0)
				//	{
				(struc[i].speedx)*=-1;
				//	struc[i].theta*=-1;
				struc[i].flag=!struc[i].flag;
				//	}
			}
			//printf("%f",struc[i].speedy);
			xcomp=struc[i].speedx*sin(DEG2RAD(-struc[i].theta));
			ycomp=struc[i].speedy*cos(DEG2RAD(-struc[i].theta));
			//	glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
			struc[i].y1+=ycomp;
			struc[i].x1+=xcomp;
		}
		for(i=0;i<n1;i++)
		{
			if(spidey[i].flag==true && spidey[i].dead==false)
				spidey[i].y-=0.01f;
		}
	}
	//if(pause==true)
	glutTimerFunc(10, update, 0);
}
/*void print()
{
	char string[1000]="GAME OVER";
	glRasterPos2f(2.0f,2.0f);
	glColor3f(1.0f,0.0f,0.0f);
	for(i=0;i<9;i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
	}
}*/
void update1(int value)
{
	if(pause==false)
		drawSpider();
	//if(pause==true)
	glutTimerFunc(2000,update1,0);
}
void drawBox(float len) {

	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex2f(-len / 2, -len / 2);
	glVertex2f(len / 2, -len / 2);
	glVertex2f(len / 2, len / 2);
	glVertex2f(-len / 2, len / 2);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void drawSpidey(float rad)
{
	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++) {
		glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
	}
	glEnd();
}
void leg(int angle)
{
	// Draw leg for spider

	glPushMatrix();
	glRotatef(angle,1,0,0);
	GLUquadricObj *quadratic1;
	quadratic1 = gluNewQuadric();
	gluCylinder(quadratic1,0.15f,0.15f,4.0f,32,32);


	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 4.0f);
	glRotatef(-100, 1.0, 0.0, 0.0);
	GLUquadricObj *quadratic2;
	quadratic2 = gluNewQuadric();
	gluCylinder(quadratic2,0.15f,0.05f,3.0f,32,32);
	glPopMatrix();
	glPopMatrix();

}

void drawAragog () {
	// Make Spider animate by changing theta

	int a1=120,a2=122,a3=117,a4=124,a5=118,a6=123,a7=115,a8=120;

	// Draw Spider

	glutSolidSphere(1.0f,100,100);
	glPushMatrix();
	glTranslatef(0.2,0.2,-0.1);
	glutSolidSphere(0.1,32,32);
	glTranslatef(-0.4,0.2,0);
	glutSolidSphere(0.1,32,32);
	glPopMatrix();
	glTranslatef(0,0,0.2);
	glRotatef(20, 0.0, 0.0, 1.0);
	leg(a1);
	glRotatef(45, 0.0, 0.0, 1.0);
	leg(a2);
	glRotatef(90, 0.0, 0.0, 1.0);
	leg(a3);
	glRotatef(135, 0.0, 0.0, 1.0);
	leg(a4);
	glRotatef(180, 0.0, 0.0, 1.0);
	leg(a5);
	glRotatef(225, 0.0, 0.0, 1.0);
	leg(a6);
	glRotatef(270, 0.0, 0.0, 1.0);
	leg(a7);
	glRotatef(315, 0.0, 0.0, 1.0);
	leg(a8);
}

void drawBox1(float len) {

	glBegin(GL_QUADS);
	glVertex2f(-len / 2, -len / 2);
	glVertex2f(len / 2, -len / 2);
	glVertex2f(len / 2, len / 2);
	glVertex2f(-len / 2, len / 2);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void drawTurret(float len) {

	glBegin(GL_QUADS);
	glVertex2f(-len / 2, 0.0f);
	glVertex2f(len / 2, 0.0f);
	glVertex2f(len / 2, 0.075*box_len);
	glVertex2f(-len / 2, 0.075*box_len);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void drawLaser(float len) {

	glBegin(GL_QUADS);
	glVertex2f(-len / 3, 0.0f);
	glVertex2f(len / 3, 0.0f);
	glVertex2f(len / 3, 0.05*box_len);
	glVertex2f(-len / 3, 0.05*box_len);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void drawBall(float rad) {

	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<=180 ; i++) {
		glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
	}
	glEnd();
}

void drawTriangle() {

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

	if (key == 27) {
		exit(0);     // escape key is pressed
	}
	if(key=='r')
		flag=1;
	else if(key=='g')
		flag=2;
	else if(key=='b')
		flag=3;
	if(key=='p')
	{
		pause=!pause;
		//	for(;pause==false;);
	}
	if(key==32)
	{	
		if(flag1)
		{
			system("aplay sound2.wav &");
			flag1=false;
			struc[n].x1=ball_x;
			struc[n].y1=ball_y;
			struc[n].speedx=0.3f;
			struc[n].speedy=0.3f;
			struc[n].theta=theta;
			struc[i].flag=0;
			n++;
			glutTimerFunc(500, changeit, 0);
		}
	}

}

void handleKeypress2(int key, int x, int y) {
	if (key == GLUT_KEY_UP && theta-10>=-70)
		theta -= 10;
	if (key == GLUT_KEY_DOWN && theta+10<=70)
		theta += 10;
	//Flag for ball
	if(flag==3)
	{
		if (key == GLUT_KEY_LEFT)
		{
			ball_x -= speed;
			for(i=0;i<n1;i++)
			{
				if(spidey[i].flag==false && ball_x-ball_rad> spidey[i].x-0.2f&& ball_x-ball_rad<=(spidey[i].x+0.25f))
					ball_x+=(speed);
			}
		}
		if (key == GLUT_KEY_RIGHT)
		{
			ball_x += speed;
			for(i=0;i<n1;i++)
			{
				if(spidey[i].flag==false && ball_x+ball_rad<spidey[i].x+0.2f && ball_x+ball_rad>=(spidey[i].x-0.25f))
					ball_x-=speed;
			}
		}
	}
	//Flag for green
	if(flag==2)
	{
		if (key == GLUT_KEY_LEFT)
		{
			box_x1 -= speed;
			for(i=0;i<n1;i++)
			{
				if(spidey[i].flag==false && box_x1-box_len1/2> spidey[i].x-0.2f && box_x1-box_len1/2<=(spidey[i].x+0.25f))
					box_x1+=(speed);
			}
		}
		if (key == GLUT_KEY_RIGHT)
		{
			box_x1 += speed;
			for(i=0;i<n1;i++)
			{
				if(spidey[i].flag==false && box_x1+box_len1/2> spidey[i].x-0.2f && box_x1+box_len1/2<=(spidey[i].x+0.25f))
					box_x1-=(speed);
			}
		}
	}
	//Flag for red
	if(flag==1)
	{
		if (key == GLUT_KEY_LEFT)
		{
			box_x -= speed;

			for(i=0;i<n1;i++)
			{
				if(spidey[i].flag==false && box_x-box_len1/2> spidey[i].x-0.2 && box_x-box_len1/2<=(spidey[i].x+0.25))
					box_x+=(speed);
			}
		}
		if (key == GLUT_KEY_RIGHT)
		{
			box_x += speed;

			for(i=0;i<n1;i++)
			{
				if(spidey[i].flag==false && box_x+box_len1/2> spidey[i].x-0.2f && box_x+box_len1/2<=(spidey[i].x+0.25f))
					box_x-=(speed);
			}
		}
	}

}
float mouseposx,mouseposy,mouseposz;
void GetOGLPos(int x, int y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	mouseposx=posX*100/2;
	mouseposy=(posY*100)/2;
	mouseposz=posZ*100;
}

float mousex;
float mousey;
int togcan,toggreen,togred,rotcan;
float distance(float x1,float y1,float x2,float y2)
{
	float dist;
	dist=sqrt(((y2-y1)*(y2-y1))+((x2-x1)*(x2-x1)));
	return dist;
}
void printtext(int x, int y, string String)
{
        //(x,y) is from the bottom left of the window
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, WindowWidth, 0, WindowHeight, -1.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glPushAttrib(GL_DEPTH_TEST);
        glDisable(GL_DEPTH_TEST);
        glRasterPos2i(x,y);
	glScalef(2.0f,2.0f,2.0f);
        for (int i=0; i<String.size(); i++)
        {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, String[i]);
        }
        glPopAttrib();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
}

void handleMouseclick(int button, int state, int x, int y) {

	// if(paused)
	//   return;
	GetOGLPos(x,y);
	mousex=mouseposx;//(float)x;//((float)x-w/2)/w;
	mousey=mouseposy;//(float)y;//(-(float)y+h/2)/h;
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			//cout<<x<<":"<<mousex<<": "<<can_x<<"\n";
			if(distance(mousex,mousey,ball_x,ball_y)<0.3)
			{
				togcan=1;
				toggreen=0;
				togred=0;
				rotcan=0;

			}
			else if(distance(mousex,mousey,box_x1,box_y1)<0.3)
			{
				togcan=0;
				toggreen=1;
				togred=0;
				rotcan=0;
			}
			else if(distance(mousex,mousey,box_x,box_y)<0.3)
			{
				togcan=0;
				toggreen=0;
				togred=1;
				rotcan=0;
			}
			else
			{
				togcan=0;
				toggreen=0;
				togred=0;
				rotcan=0;
			}

			//  cout<<"hi\n";
		}
		if(button == GLUT_RIGHT_BUTTON)
		{
			togcan=0;
			toggreen=0;
			togred=0;
			if(distance(mousex,mousey,ball_x,ball_y)<0.5)
			{
				rotcan=1;
			}
			else
				rotcan=0;
		}
		//cout<<"x: "<<mousex<<"can_x: "<<can_x<<"\n";
		//else if (button == GLUT_RIGHT_BUTTON)
		//           cout<<"y: "<<mousey<<"\n";
	}
	cout<<distance(mousex,mousey,ball_x,ball_y)<<"\n";
	cout<<mousex<<" "<<mousey<<" "<<ball_x<<" "<<ball_y<<"\n";
	cout<<togcan<<rotcan<<togred<<toggreen<<"\n";
	glutPostRedisplay();
}

float drag(float position)//,float lefy,float rify)
{
	float  move;
	if(distance(mousex,mousey,position,ball_y)<0.7)
	{   
		move=(2*(mousex-position));
		if(move>0)
		{
			position+=(move*0.3);
			/*for(i=0;i<n1;i++)
			  {
			  if(spidey[i].flag==false && position+(move*0.3)<spidey[i].x+0.2f && position+(move*0.3)>=(spidey[i].x-0.25f))
			  position-=(move*0.3);
			  }*/

			// if(position+(move*0.3)< rify)
			//   position+=(move*0.3);
		}   
		else if(move<0)
		{   
			position+=(move*0.3);
			/*	for(i=0;i<n1;i++)
				{
				if(spidey[i].flag==false && position+(move*0.3)> spidey[i].x-0.2f && position+(move*0.3)<=(spidey[i].x+0.25f))
				position-=(move*0.3);
				}*/
			//    if(position+(move*0.3)>lefy)
			//      position+=(move*0.3);
		}   
	}   
	return position;
}
void dragwithmouse(int x,int y)
{
	//    if(paused)
	//        return;
	GetOGLPos(x,y);
	mousex=mouseposx;//((float)x-455)/125;
	mousey=mouseposy;//(-(float)y+255)/125;
	if(togred)
	{
		box_x=drag(box_x);//prev_r_min,prev_r_max);
	}
	else if(toggreen)
	{
		box_x1=drag(box_x1);//,prev_g_min,prev_g_max);
	}
	else if(togcan)
	{
		ball_x=drag(ball_x);//,prev_min,prev_max);
	}
	if(rotcan && distance(mousex,mousey,ball_x,ball_y)<0.8)
	{
		if(ball_x-mousex>0)
		{
			if(theta + 10<80)//DEG2RAD(10)<DEG2RAD(180))
				theta += 5;//DEG2RAD(10);
		}
		else
			if(theta - 10>-80)//DEG2RAD(10)>DEG2RAD(0))
				theta -= 5;//DEG2RAD(10);
	}

}
/*void handleMouseclick(int button, int state, int x, int y) {

  if (state == GLUT_DOWN)
  {
  if (button == GLUT_LEFT_BUTTON && theta-10>=-90)
  theta -= 10;
  else if (button == GLUT_RIGHT_BUTTON && theta+10<=90)
  theta += 10;
  }
  }*/
