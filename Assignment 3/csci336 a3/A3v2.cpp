#include <gl/glut.h>
#include <iostream>
#include <stdio.h>
#define GAP  15 // gap between subwindows
#include <math.h>
using namespace std;

#define MY_PI 		(3.14159265359)    //declare PI value
#define DEG2RAD(a) 	(MY_PI/180*(a))    //convert degrees into radians



float main_window_x;
float main_window_y;
float main_window_w = 1200;
float main_window_h = 600;
char *window_title = "Scene (ROOM)";
int main_window;
void main_display (void);
void main_reshape (int w, int h);
float subwindow1_x = GAP;
float subwindow1_y = GAP;
float subwindow1_w = (1200-GAP*3)/2;
float subwindow1_h = (1200-GAP*3)/2;
int subwindow_1;


float subwindow2_x = GAP + (1200-GAP*3)/2 + GAP;
float subwindow2_y = GAP;
float subwindow2_w = (1200-GAP*3)/2;
float subwindow2_h = (1200-GAP*3)/2;
int subwindow_2;


float subwindow3_w = 600;
float subwindow3_h = 600;
int subwindow_3;


bool gColourTracking = false;
bool gSmoothShading = true;
bool lightOn1 = true;
bool lightOn2 = true;
bool lightOn3 = true;
bool changed = true;
bool showHelp = false;

//camera variables
GLfloat gCameraPosition[] = { 0.0f, 10.0f, 22.0f };
GLfloat gCameraLookAt[] = { 0.0f, 10.0f, 15.0f };
GLfloat gCameraUp[] = { 0.0f, 1.0f, 0.0f };

GLfloat gCameraPosition2[] = { 0.0f, 17.0f, 5.0f };
GLfloat gCameraLookAt2[] = { 0.0f, 0.0f, 0.0f };
GLfloat gCameraUp2[] = { 0.0f, 1.0f, 0.0f };

GLfloat gCameraYaw = 0.0f;     //camera yaw
GLfloat gMoveForward = 0.0f;   //camera forward/backward movement variable
GLfloat gCameraPitch = 0.0f;
GLfloat gCameraRoll = 0.0f;
GLfloat gMoveUpward = 0.0f;
GLfloat gMoveRightward = 0.0f;


GLfloat gMovementSensitivity = 1;      //movement sensitivity
GLfloat gRotationSensitivity = 2;      //rotational sensitivity
bool refreshPosition = false;
// material properties
GLfloat gAmbientMaterial[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat gDiffuseMaterial[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat gSpecularMaterial[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLint gShininessMaterial = 50;

GLfloat gAmbientMaterial2[] = {0.4f, 0.4f, 0.4f, 1.0f};
GLfloat gSpecularMaterial2[] = {0.8f, 0.8f, 0.8f, 1.0f};

GLfloat gAmbientMaterial3[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat gSpecularMaterial3[] = {0.7f, 0.7f, 0.7f, 1.0f};

GLfloat gAmbientMaterial4[] = {0.4f, 0.4f, 0.4f, 1.0f};
GLfloat gSpecularMaterial4[] = {0.8f, 0.8f, 0.8f, 1.0f};

GLfloat gAmbientMaterial5[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat gSpecularMaterial5[] = {0.9f, 0.9f, 0.9f, 1.0f};

GLfloat gAmbientMaterial6[] = {0.4f, 0.4f, 0.4f, 1.0f};
GLfloat gSpecularMaterial6[] = {0.8f, 0.8f, 0.8f, 1.0f};

GLfloat gAmbientMaterial7[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat gSpecularMaterial7[] = {0.7f, 0.7f, 0.7f, 1.0f};

GLfloat gAmbientMaterial8[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat gSpecularMaterial8[] = {0.6f, 0.6f, 0.6f, 1.0f};


GLfloat gDiffuseBlue[] = {0.0f, 0.0f, 1.0f, 1.0f};
GLfloat gDiffuseRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
GLfloat gDiffuseGreen[] = { 0.0f, 1.0f, 0.0f, 1.0f};
GLfloat gDiffusePurple[]= { 1.0f, 0.0f, 1.0f, 1.0f};
GLfloat gDiffuseYellow[] = { 1.0f, 1.0f , 0.0f, 1.0f};
GLfloat gDiffuseGray[] = { 0.9f, 0.9f, 0.9f , 1.0f };
GLfloat gDiffuseLightBlue[] = { 0.4f, 0.4f, 0.5f, 1.0f};
GLfloat gDiffuseDarkBrown[] = {0.65f, 0.18f, 0.18f, 1.0f};
GLfloat gDiffuseLightBrown[] = { 0.80f, 0.52f, 0.25f, 1.0f};
GLfloat gDiffuseLimeGreen[] = { 0.6f, 1.0f, 0.2f, 1.0f};
GLfloat gDiffuseCyan[] = { 0.0f, 0.8f, 0.8f, 1.0f};
GLfloat gDiffuseForestGreen[] = { 0.0f, 0.6f, 0.0f, 1.0f};
GLfloat gDiffusePink[] = { 1.0f, 0.6f, 1.0f, 1.0f};
GLfloat gDiffuseOrange[] = { 1.0f, 0.6f, 0.2f, 1.0f};
GLfloat gDiffuseLightPurple[] = { 0.6f, 0.0f, 0.8f, 1.0f};
GLfloat gDiffuseLightGreen[] = {0.4f, 1.0f, 0.2f, 1.0f};
GLfloat gDiffuseLightRed[] = { 1.0f, 0.0f, 0.2f, 1.0f};
GLfloat gDiffuseBrightOrange[]= { 1.0f, 0.6f, 0.0f, 1.0f};
GLfloat gDiffuseBlack[] = { 0.0f , 0.0f , 0.0f , 1.0f };



GLfloat gYellowEmission[] = {1.0f, 1.0f, 0.0f, 1.0f};
GLfloat gBlueEmission[] = { 0.0f, 0.0f, 1.0f, 1.0f};
GLfloat gWhiteEmission[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat gBlackEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f};
GLfloat gNone[] = {0.0f, 0.0f, 0.0f, 1.0f};

//light properties
GLfloat gAmbientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };	  //ambient light
//GLfloat gAmbientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };	  //ambient light
GLfloat gDiffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };	  //diffuse light

//GLfloat gDiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };	  //diffuse light
GLfloat gLightPosition[] = { 0.0f, 28.0f, -28.0f, 0.0f }; //light position

GLfloat gLightPosition1[] = { 0.0f, 28.0f, 28.0f, 0.0f }; //light1 position

float spotlightX = 0;
float spotlightY = 20;
//GLfloat gLightPosition2[] = { 0.0f, 29.0f, 0.0f, 1.0f}; // light2(spotLight) position
//GLfloat gLightPosition2[] = { spotlightX, spotlightY, 0.0f, 1.0f};
GLfloat gLightSpecular2[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat gLightDirection2[] = { 0.0f, -1.0f, 0.0f};

// moving light
  static long last_update_time = glutGet(GLUT_ELAPSED_TIME);
  static GLint gFrameCount = 0;   //frame count
  static float gFPS = 0;          //frames per second
  static char gFPS_str[50];  
bool leftSide = true;
bool rightSide = true;
bool rightMax = false;
bool leftMax = false;
bool passOthroughR = false;
bool passOthroughL = false;
int currentTime, previousTime, elapsedTime = 0 ;
float unitMovementPerSec = 5;



//  Call Back Functions
void init();
void drawScene();
void display_str(GLint, GLint , void* , char* );
void helpDisplay ();
void updateCamera();
void myKeypress(unsigned char, int , int );
void mySpecialKeys(int, int , int );
void subwindow1_display ();
void subwindow1_reshape (int, int);
void subwindow2_display ();
void subwindow2_reshape (int, int);

//set up states that are going to be used
void init()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //set clear background colour to black

  glEnable(GL_DEPTH_TEST);	//enable depth test

  //set material properties
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseMaterial);        //set material diffuse component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial);      //set material specular component
  glMateriali(GL_FRONT, GL_SHININESS, gShininessMaterial);     //set material shininess

  //setup light 0
  glLightfv(GL_LIGHT0, GL_AMBIENT, gAmbientLight);		//set light0's ambient component
  glLightfv(GL_LIGHT0, GL_DIFFUSE, gDiffuseLight);		//set light0's diffuse component
  glLightfv(GL_LIGHT0, GL_POSITION, gLightPosition);	//set light0's position
   
  //setup light 1
  glLightfv(GL_LIGHT1, GL_AMBIENT, gAmbientLight);		//set light1's ambient component
  glLightfv(GL_LIGHT1, GL_DIFFUSE, gDiffuseLight);		//set light1's diffuse component
  glLightfv(GL_LIGHT1, GL_POSITION, gLightPosition1);	//set light1's position  

  //setup spotlight
  GLfloat gLightPosition2[] = { spotlightX, spotlightY, 0.0f, 1.0f};
  glLightfv(GL_LIGHT2, GL_AMBIENT, gAmbientLight);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, gDiffuseLight);
  glLightfv(GL_LIGHT2, GL_SPECULAR, gLightSpecular2);
  glLightfv(GL_LIGHT2, GL_POSITION, gLightPosition2);
//glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.5);
//glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.5);
//glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.2);
  glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 15.0);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, gLightDirection2);
  glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);

  //enable lighting and select shading model
  glEnable(GL_LIGHT0);      //enable light0
  glEnable(GL_LIGHT1);      //enable light1
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHTING);    //enable lighting
  glEnable(GL_NORMALIZE);
//  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//  glEnable(GL_COLOR_MATERIAL);        //enable colour tracking
  glShadeModel(GL_SMOOTH);	//set shading model
}

void resetCamera ()
{
  gCameraPosition[0] = 0.0f;
  gCameraPosition[1] = 10.0f;
  gCameraPosition[2] = 22.0f;
  gCameraLookAt[0] = 0.0f;
  gCameraLookAt[1] = 10.0f;
  gCameraLookAt[2] = 15.0f;
  gCameraUp[0] = 0.0f;
  gCameraUp[1] = 1.0f;
  gCameraUp[2] = 0.0f;
  gCameraYaw = 0.0f;     //camera yaw
  gMoveForward = 0.0f;   //camera forward/backward movement variable
  gCameraPitch = 0.0f;
  gCameraRoll = 0.0f;
  gMoveUpward = 0.0f;
  gMoveRightward = 0.0f;

  updateCamera();
}

//draw the scene here
void drawScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clear the colour buffer to the colour previously set in glClearColor 

  if(glutGetWindow() == subwindow_1)
    glDisable(GL_DEPTH_TEST);
  else
    glEnable(GL_DEPTH_TEST);

  if (changed)
  {
    glRotatef (gCameraYaw, 0.0f, 1.0f, 0.0f); 
    glRotatef (gCameraPitch, 1.0f, 0.0f, 0.0f); // edited
    glRotatef (gCameraRoll, 0.0f, 0.0f, 1.0f);

    cout << "CAMERA ROOLL " << endl;
  }

  changed = false;


  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseBlue); 
  //glColor3f(0.0f, 0.0f, 1.0f);
  glPushMatrix();
    glTranslatef(0.0f, 28.0f, -28.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(2.0f, 1.0f, 16, 8);
  glPopMatrix();

  glLightfv(GL_LIGHT0, GL_POSITION, gLightPosition);	//set light0's position
  //draw the light
  glPushMatrix();
    if( lightOn1)
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, gYellowEmission);  //set material emission component
        //glColorMaterial (GL_FRONT, GL_EMISSION);
        //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        //glColor3f(1.0, 1.0, 0.0);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, gBlackEmission);
        //glColorMaterial (GL_FRONT, GL_EMISSION);
        //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        //glColor3f(0.0, 0.0, 0.0);
    }
    glTranslatef(0.0f, 28.0f, -28.0f);
    glutSolidSphere(0.5f, 16, 16);
    glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
  glPopMatrix();
 

  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseBlue); 
  //glColor3f(0.0f, 0.0f, 1.0f);
  glPushMatrix();
    glTranslatef(0.0f, 28.0f, 28.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(2.0f, 1.0f, 16, 8);
  glPopMatrix(); 
 

  glLightfv(GL_LIGHT1, GL_POSITION, gLightPosition1);
  glPushMatrix();
    if(lightOn2)
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, gBlueEmission);  //set material emission component
                //glColorMaterial (GL_FRONT, GL_EMISSION);
              //  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
               // glColor3f(0.0, 1.0, 1.0);
    }
    else
    {
         glMaterialfv(GL_FRONT, GL_EMISSION, gBlackEmission);
        //glColorMaterial (GL_FRONT, GL_EMISSION);
            ///    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
            //    glColor3f(0.0, 0.0, 0.0);
    }
        
    glTranslatef(0.0f, 28.0f, 28.0f);
    glutSolidSphere(0.5f, 16, 16);
    glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
  glPopMatrix();  


  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseBlue); 
  //glColor3f(0.0f, 0.0f, 1.0f);
  glPushMatrix();
    glTranslatef(spotlightX, spotlightY, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(2.0f, 1.0f, 16, 8);
  glPopMatrix(); 
  
  glMaterialfv( GL_FRONT, GL_DIFFUSE, gDiffuseBlack );
  //glColor3f( 0.0f, 0.0f, 0.0f);
  glBegin(GL_LINES);
    glVertex3f(0.0f, 30.0f, 0.0f );
    glVertex3f( spotlightX , spotlightY + 1, 0.0f );
  glEnd();
 
  GLfloat gLightPosition2[] = { spotlightX, spotlightY, 0.0f, 1.0f};
  glLightfv(GL_LIGHT2, GL_POSITION, gLightPosition2);
  glPushMatrix();
    if (lightOn3)
    {
       glMaterialfv(GL_FRONT, GL_EMISSION, gWhiteEmission);  //set material emission component
        //    glColorMaterial (GL_FRONT, GL_EMISSION);
        //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        //glColor3f(1.0, 1.0, 1.0);
    }
    else
    {
       glMaterialfv(GL_FRONT, GL_EMISSION, gBlackEmission);
       //glColorMaterial (GL_FRONT, GL_EMISSION);
            //    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
            //    glColor3f(0.0, 0.0, 0.0);
    }
    //glTranslatef(0.0f, 20.0f, 0.0f);
    glTranslatef(spotlightX, spotlightY, 0);
    glutSolidSphere(0.5f, 16, 16);
    glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
  glPopMatrix();  

  //draw floor
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseRed);        //set material diffuse component
  //glColor3f( 1.0f, 0.0f, 0.0f );
  glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(30.0f, 0.0f, 30.0f);	
    glVertex3f(30.0f, 0.0f, -30.0f);
    glVertex3f(-30.0f, 0.0f, -30.0f);
    glVertex3f(-30.0f, 0.0f, 30.0f);
  glEnd();
  
  //draw ceiling
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLimeGreen);
  //glColor3f( 0.6f, 1.0f, 0.2f);
  glBegin (GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f( 30.0f , 30.0f, 30.0f);
    glVertex3f(30.0f, 30.0f, -30.0f);
    glVertex3f(-30.0f, 30.0f , - 30.0f);
    glVertex3f(-30.0f, 30.0f, 30.0f);
  glEnd();
  
  
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseGreen);
  //glColor3f(0.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);
  //draw left wall
    glNormal3f(1.0f , 0.0f, 1.0f);
    glVertex3f(-30.0f, 0.0f, -30.0f);
    glVertex3f(-30.0f, 30.0f, -30.0f);
    glVertex3f(-30.0f, 30.0f, 30.0f);
    glVertex3f(-30.0f, 0.0f, 30.0f);
  //draw right wall
    glNormal3f(-1.0f , 0.0f, 1.0f);
    glVertex3f(30.0f, 0.0f, -30.0f);
    glVertex3f(30.0f, 30.0f, -30.0f);
    glVertex3f(30.0f, 30.0f, 30.0f);
    glVertex3f(30.0f, 0.0f, 30.0f); 
  glEnd();
  
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseForestGreen);
  //glColor3f( 0.0f, 0.6f, 0.0f);
  glBegin(GL_QUADS);
  //draw back wall
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-30.0f, 0.0f, -30.0f);
    glVertex3f(-30.0f, 30.0f, -30.0f);
    glVertex3f(30.0f, 30.0f, -30.0f);
    glVertex3f(30.0f, 0.0f , -30.0f);
 
  //draw front wall
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-30.0f, 0.0f, 30.0f);
    glVertex3f(-30.0f, 30.0f, 30.0f);
    glVertex3f(30.0f, 30.0f, 30.0f);
    glVertex3f(30.0f, 0.0f , 30.0f);         
  glEnd();
 
  //draw table
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseDarkBrown);        //set material diffuse component
  //glColor3f(0.65f, 0.18f, 0.18f);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glPushMatrix();
    glTranslatef(0.0f, 6.5f, 0.0f);
    glScalef(1.5f, 0.1f, 1.0f);
    glutSolidCube(10);
  glPopMatrix();
  //draw four legs of table
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightBrown);
  //glColor3f(0.8f, 0.52f, 0.25f );
  //glNormal3f(0.0f, 0.0f, 0.0f);
  //back left leg
  glPushMatrix();
    glTranslatef(-6.0f, 3.0f, -4.5f);
    glScalef(0.1f, 1.0f, 0.1f);
    glutSolidCube(6);
  glPopMatrix();
  // front left leg
  glPushMatrix();
    glTranslatef(-6.0f, 3.0f, 4.5f);
    glScalef(0.1f, 1.0f, 0.1f);
    glutSolidCube(6);
  glPopMatrix();
  // back right leg
  glPushMatrix();
    glTranslatef(6.0f, 3.0f, -4.5f);
    glScalef(0.1f, 1.0f, 0.1f);
    glutSolidCube(6);
  glPopMatrix();
  // back right leg
  glPushMatrix();
    glTranslatef(6.0f, 3.0f, 4.5f);
    glScalef(0.1f, 1.0f, 0.1f);
    glutSolidCube(6);
  glPopMatrix();
  
  //draw chair 1
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseDarkBrown);        //set material diffuse component
  //glColor3f(0.65f, 0.18f, 0.18f);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glPushMatrix();
    glTranslatef(-8.0f, 3.5f, 0.0f);
    glScalef(1.0f, 0.1f, 1.0f);
    glutSolidCube(5);
  glPopMatrix();  
  //draw four legs of chair1
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightBrown);
  //glColor3f(0.8f, 0.52f, 0.25f );
  //glNormal3f(0.0f, 0.0f, 0.0f);
  //back left leg
  glPushMatrix();
    glTranslatef(-10.0f, 1.7f, -2.2f);
    glScalef(0.1f, 0.85f, 0.1f);
    glutSolidCube(4);
  glPopMatrix();
  // front left leg
  glPushMatrix();
    glTranslatef(-10.0f, 1.7f, 2.2f);
    glScalef(0.1f, 0.85f, 0.1f);
    glutSolidCube(4);
  glPopMatrix();
  // back right leg
  glPushMatrix();
    glTranslatef(-6.0f, 1.7f, -2.2f);
    glScalef(0.1f, 0.85f, 0.1f);
    glutSolidCube(4);
  glPopMatrix();
  // back right leg
  glPushMatrix();
    glTranslatef(-6.0f, 1.7f, 2.2f);
    glScalef(0.1f, 0.85f, 0.1f);
    glutSolidCube(4);
  glPopMatrix();
  //back rest
  glPushMatrix();
    glNormal3f(-1.0, 0.0, 0.0);
    glTranslatef(-10.2f, 6.5f, 0.0f);
    glScalef(0.1f, 1.2f, 1.0f);
    glutSolidCube(5);
  glPopMatrix();    
 
  //draw chair 2
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseDarkBrown);        //set material diffuse component
  //glColor3f(0.65f, 0.18f, 0.18f);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glPushMatrix();
    glTranslatef(8.0f, 3.5f, 0.0f);
    glScalef(1.0f, 0.1f, 1.0f);
    glutSolidCube(5);
  glPopMatrix();  
  //draw four legs of chair 2
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightBrown);
  //glColor3f(0.8f, 0.52f, 0.25f );
  //glNormal3f(0.0f, 0.0f, 0.0f);
  //back left leg
  glPushMatrix();
    glTranslatef(10.0f, 1.7f, -2.2f);
    glScalef(0.1f, 0.85f, 0.1f);
    glutSolidCube(4);
  glPopMatrix();
  // front left leg
  glPushMatrix();
    glTranslatef(10.0f, 1.7f, 2.2f);
    glScalef(0.1f, 0.85f, 0.1f);
    glutSolidCube(4);
  glPopMatrix();
  // back right leg
  glPushMatrix();
    glTranslatef(6.0f, 1.7f, -2.2f);
    glScalef(0.1f, 0.85f, 0.1f);
    glutSolidCube(4);
  glPopMatrix();
  // back right leg
  glPushMatrix();
    glTranslatef(6.0f, 1.7f, 2.2f);
    glScalef(0.1f, 0.85f, 0.1f);
    glutSolidCube(4);
  glPopMatrix();
  //back rest
  glPushMatrix();
    glNormal3f(-1.0, 0.0, 0.0);
    glTranslatef(10.2f, 6.5f, 0.0f);
    glScalef(0.1f, 1.2f, 1.0f);
    glutSolidCube(5);
  glPopMatrix();   
 
  //draw cone
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial);      //set material specular component  
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseBlue); 
  //glColor3f(0.0f, 0.0f, 1.0f);
  glPushMatrix();
    glTranslatef(-2.5f, 7.0f, -2.5f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(2.0f, 4.0f, 16, 8);
  glPopMatrix();
  
  //draw sphere
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial2);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial2);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseCyan); 
  //glColor3f(0.0f, 0.8f, 0.8f );
  glPushMatrix();
    glTranslatef(-2.0f, 8.0f, 2.5f);
    glutSolidSphere(1.0f, 16, 16); 
  glPopMatrix();
  
  //draw torus
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial3);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial3);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffusePink); 
  //glColor3f(1.0f, 0.6f, 1.0f);
  glPushMatrix();
    glTranslatef(2.0f, 9.5f, -2.5f);
    glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);
    glutSolidTorus(0.5f, 2.0f, 8, 16);
  glPopMatrix();

  //draw teapot
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial4);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial4);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseOrange);
  //glColor3f(1.0f, 0.6f, 0.2f);
  glPushMatrix();
    glTranslatef(1.0f, 8.1f, 1.0f);
    glRotatef(135.0f, 0.0f, 1.0f, 0.0f);
    glutSolidTeapot(1.5f);
  glPopMatrix();

  //draw dodecahedron
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial5);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial5);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightPurple);
  //glColor3f( 0.6f, 0.0f, 0.8f);
  glPushMatrix();
    glTranslatef(5.0f, 8.4f, 0.0f);
    glRotatef(120.0f, 1.0f,  0.0f, 0.0f);
    glutSolidDodecahedron();
  glPopMatrix();  
    
  //draw octahedron
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial6);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial6);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightGreen);
  //glColor3f(0.4f, 1.0f, 0.2f);
  glPushMatrix();
    glTranslatef(-5.0f, 8.0f, 0.0f);
    glutSolidOctahedron();
  glPopMatrix();

  //draw tetrahedron
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial7);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial7);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightRed);
  //glColor3f(1.0f, 0.0f, 0.2f );
  glPushMatrix();
    glTranslatef(-4.0f, 7.55f, 4.0f);
    //glRotatef(180.0f, 1.0f, 1.0f, .0f);
    glutSolidTetrahedron();
  glPopMatrix();  
  
  //draw Icosahedron
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial8);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial8);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseBrightOrange);
  //glColor3f(1.0f, 0.6f , 0.0f);
  glPushMatrix();
    glTranslatef(3.0f, 8.0f, 3.5f);
    glRotatef(145.0f, 1.0f, 0.0f, 0.0f);
    glutSolidIcosahedron();
  glPopMatrix();

  gFrameCount++;

  helpDisplay();




  glFlush();
  glutSwapBuffers();     //swap front and back buffers
}


//this function updates the camera
void updateCamera()
{
  if(gCameraYaw > 360.0)    //keep yaw between 0 - 360 degrees
    gCameraYaw -= 360.0;
  else if(gCameraYaw < 0.0)
    gCameraYaw += 360.0;
    
  if( gCameraRoll > 45.0 )
      gCameraRoll = 45.0;
  else if (gCameraRoll < -45.0 )
       gCameraRoll = -45.0;
  
  if ( gCameraPitch > 90.0 )
      gCameraPitch = 90.0;
  else if ( gCameraPitch < -10.0 )
      gCameraPitch = -10.0;
 
 // gCameraPosition[0] += sin(DEG2RAD(gCameraYaw))*gMoveForward;    //calculate movement along x axis
 // gCameraPosition[2] += -cos(DEG2RAD(gCameraYaw))*gMoveForward;   //calculate movement along z axis
 
  gCameraPosition[2] += gMoveForward;
  gCameraLookAt[2] += gMoveForward;
  gMoveForward = 0;     //reset forward/backward movement


  gCameraPosition[1]+= gMoveUpward;
  gCameraLookAt[1] += gMoveUpward;
  gMoveUpward = 0;
 // gCameraLookAt[0] = gCameraPosition[0] + sin(DEG2RAD(gCameraYaw));   //rotate camera lookat direction
 // gCameraLookAt[2] = gCameraPosition[2] -cos(DEG2RAD(gCameraYaw));

  gCameraPosition[0] +=  gMoveRightward;
  gCameraLookAt[0] += gMoveRightward;
  gMoveRightward = 0;

  glLoadIdentity();     //load modelview matrix with identity matrix
  gluLookAt(gCameraPosition[0], gCameraPosition[1], gCameraPosition[2],   //set position
            gCameraLookAt[0], gCameraLookAt[1], gCameraLookAt[2],         //set where eye/camera is looking at
	        gCameraUp[0], gCameraUp[1], gCameraUp[2]);                    //set 'up' vector

  glutPostRedisplay();  //refresh display
}


void display_str(GLint x, GLint y, void* font, char* str)
{
// to display words on the diagram
  char* ptr;              //temp pointer to position in string
  
  glRasterPos2i(x, y);    //place raster position

  for(ptr = str; *ptr != '\0'; ptr++)
  {
    glutBitmapCharacter(font, *ptr); //draw bitmap character
  }
}

void helpDisplay ()
{
     
 // gFrameCount++;


     
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  
  glLoadIdentity();
  gluOrtho2D(0, 800, 0, 600);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  
  if(gFrameCount >= 100)
  {
    gFPS = (1000.0f*(float)gFrameCount)/((float)glutGet(GLUT_ELAPSED_TIME) - last_update_time);  //calculate fps
    sprintf(gFPS_str, "FPS - %f", gFPS);
    gFrameCount = 0;
    last_update_time = glutGet(GLUT_ELAPSED_TIME);     
  }     

  display_str (20, 560,GLUT_BITMAP_8_BY_13, "Press [h] to toggle Help Info" );
  display_str (400, 560, GLUT_BITMAP_8_BY_13,gFPS_str);


  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
     
}


//called when ASCII key pressed
void myKeypress(unsigned char key, int x, int y)
{
     glutSetWindow (subwindow_2);    
  changed = true;   
     
  switch(key)
  {
    //if ESC pressed, quit program
    case '\e': exit(1);     //quit
		       break;
    case 'w':  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    //wireframe mode
		       break;
    case 's':  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //fill mode
		       break;
  
    case '1' : 
              if ( lightOn1 )
              {
                   glDisable(GL_LIGHT0);
                   lightOn1 = false;
              }
              else
              {
                  glEnable (GL_LIGHT0);
                  lightOn1 = true;
              }
              break;
    
    case '2' :
              if ( lightOn2 )
              {
                   glDisable ( GL_LIGHT1);
                   lightOn2 = false;
              }
              else
              {
                  glEnable ( GL_LIGHT1);
                  lightOn2 = true;
              }
              break;
    
    case '3' :
              if ( lightOn3 )
              {
                   glDisable(GL_LIGHT2);
                   lightOn3 = false;
              }
              else
              {
                  glEnable (GL_LIGHT2);
                  lightOn3 = true;
              }
              break;
              
    case 'r':  
               resetCamera();
               break;
    case 't' :
               if ( gSmoothShading)
               {
                    glShadeModel(GL_FLAT);
                    gSmoothShading = false;
               }
               else 
               {
                    glShadeModel(GL_SMOOTH);
                    gSmoothShading = true;
               }
               break;
    
    case 'y' :
               if ( gColourTracking)
               {
                    glDisable(GL_COLOR_MATERIAL);
                    gColourTracking = false;
                    
                    glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial);
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseMaterial);
               }
               else
               {                  
                   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
                   glEnable(GL_COLOR_MATERIAL);  
                   gColourTracking = true;
               }
               break;            
    
    case 'u' :
               changed = true;
               gCameraRoll -= gRotationSensitivity;
               break;
    case 'o' :
               changed = true;
               gCameraRoll += gRotationSensitivity;
               break;
    case 'i' :
               changed = true;
               gCameraPitch += gRotationSensitivity;
               break;
    case 'k' : 
               changed = true;
               gCameraPitch -= gRotationSensitivity;
               break;
    case 'j' : 
               changed = true ;
               gCameraYaw -= gRotationSensitivity; 
               //gMoveRightward -= gMovementSensitivity;
               break;
    case 'l' :
               changed = true;
               gCameraYaw += gRotationSensitivity; 
               //gMoveRightward += gMovementSensitivity;;
               break;
    default: break;
  };
  updateCamera();
//  glutPostRedisplay();  //refresh display
  glutPostWindowRedisplay(subwindow_2);
}

//called when non-ASCII key pressed
void mySpecialKeys(int key, int x, int y)
{
    glutSetWindow (subwindow_2);     
     
  switch(key)
  {
    //if home pressed
    case GLUT_KEY_HOME: 
                        changed = true;
                        gCameraPosition[1] += gMovementSensitivity;       //increment camera height
                        gCameraLookAt[1] += gMovementSensitivity;
		                break;
    //if end pressed
    case GLUT_KEY_END:  
                        changed = true;
                        gCameraPosition[1] -= gMovementSensitivity;       //decrement camera height
                        gCameraLookAt[1] -= gMovementSensitivity;
		                break;
    //if arrow up pressed
    case GLUT_KEY_UP:   
                        changed = true;
                        gMoveForward -= gMovementSensitivity;             //increment forward movement
		                break;
    //if arrow down pressed
    case GLUT_KEY_DOWN: 
                        changed = true;
                        gMoveForward += gMovementSensitivity;             //increment backward movement
		                break;
    //if left pressed
    case GLUT_KEY_LEFT: 
                        changed = true;
                        //gCameraYaw -= gRotationSensitivity;               //increment camera yaw
    	                gMoveRightward -= gMovementSensitivity;
                        break;
    //if right pressed
    case GLUT_KEY_RIGHT: 
                         changed = true;
                         //gCameraYaw += gRotationSensitivity;
                        gMoveRightward += gMovementSensitivity;              //decrement camera yaw
    	                break;
    default: break;
  };
  
  updateCamera();       //call function to update camera and refresh the scene
}


void main_display ()
{

	//  Set background color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
	//  Swap front and back buffers
    glutSwapBuffers();
}

void main_reshape (int width, int height) 
{

	if (width < GAP * 6 || height < GAP * 4)
	{
		glutSetWindow (main_window);
		glutReshapeWindow (main_window_w, main_window_h);
		return;
	}

	subwindow1_w = (subwindow1_w * (width-GAP*2.0))/(main_window_w-GAP*2.0);
	subwindow1_h = (subwindow1_h * (height-GAP*3.0))/(main_window_h-GAP*3.0);

	//  Set subwindow 1 as current window and then reposition and resize it
    glutSetWindow (subwindow_1);
    glutPositionWindow (GAP, GAP);
    glutReshapeWindow (subwindow1_w, subwindow1_h);
	
	//  Change the subwindow 2 dimensions as window dimensions change
	subwindow2_w = (subwindow2_w * (width-GAP*2.0))/(main_window_w-GAP*2.0);
	subwindow2_h = (subwindow2_h * (height-GAP*3.0))/(main_window_h-GAP*3.0);

	//  Set subwindow 2 as current window and then reposition and resize it
    glutSetWindow (subwindow_2);
    glutPositionWindow (GAP+subwindow1_w+GAP, GAP);
    glutReshapeWindow (subwindow2_w, subwindow2_h);
    
	//  Stay updated with the window width and height
	main_window_w = width;
	main_window_h = height;
}

void subwindow1_reshape (int width, int height) 
{
  GLfloat range = 30.0;
     
  if(height == 0)           //just in case, to prevent divide by zero when calculating aspect ratio
    height = 1;
  
  GLfloat aspect = (GLfloat) width/(GLfloat) height;  //calculate aspect ratio
  
  glViewport(0, 0, width, height);  //set the viewport

  glMatrixMode(GL_PROJECTION);	 //set matrix mode to projection matrix
  glLoadIdentity();		         //set projection matrix to identity matrix (analogous to clearing the projection matrix)

  //establish clipping volume (left, right, bottom, top, near, far)
  //the following is done to maintain aspect ratio, i.e. a cube will be displayed as a cube not a rectangle when window is resized
  if(aspect < 1.0) 
    glOrtho (-range, range, -range/aspect, range/aspect, -range*2.0f, range*2.0f);
  else 
    glOrtho (-range*aspect, range*aspect, -range, range, -range*2.0f, range*2.0f);

  glMatrixMode(GL_MODELVIEW);	 //set matrix mode to modelview matrix
  glLoadIdentity();	
    
    gluLookAt (gCameraPosition [0], gCameraPosition [1], gCameraPosition[2],
               gCameraLookAt [0], gCameraLookAt [1], gCameraLookAt[2],
               gCameraUp [0], gCameraUp [1], gCameraUp [2]);

}


void subwindow2_reshape (int width, int height) 
{
  if(height == 0)           //prevent divide by zero
    height = 1;
  
  glViewport(0, 0, width, height);  //set the viewport

  glMatrixMode(GL_PROJECTION);	 //select projection matrix
  glLoadIdentity();		         //clear current contents to identity matrix
  gluPerspective(60.0f, 	     //set up perspective projection with 60 degrees field of view
		(GLfloat) width/(GLfloat) height, //set aspect ratio
        1.0f, 		             //set near clipping plane to 1.0
		1000.0f);	             //set far clipping plane to 100.0
		
  glMatrixMode(GL_MODELVIEW);	 //select modelview matrix
  glLoadIdentity();		         //clear current contents to identity matrix

  gluLookAt(gCameraPosition[0], gCameraPosition[1], gCameraPosition[2],   //set position
            gCameraLookAt[0], gCameraLookAt[1], gCameraLookAt[2],         //set where eye/camera is looking at
	        gCameraUp[0], gCameraUp[1], gCameraUp[2]);                    //set 'up' vector
}


void myIdleFunc()
{

  passOthroughR = false;
  passOthroughL = false;

  if ( spotlightX == 6 )
     rightMax = true;
  else if ( spotlightX == -6 )
     leftMax = true;
  else if ( spotlightX > 0 && spotlightX <= 6 )
  {
     rightSide = true;
     leftSide = false;
     leftMax = false;
     
  }
  else if ( spotlightX >= -6 && spotlightX < 0 )
  {
     leftSide = true;
     rightSide = false;
     rightMax = false;
     
  }
  else if ( spotlightX == 0 )
  {
       rightMax = false;
       leftMax = false;
       if ( rightSide)
          passOthroughR = true;
       else if ( leftSide )
          passOthroughL = true;
  }

  currentTime = glutGet(GLUT_ELAPSED_TIME);
  elapsedTime = currentTime - previousTime;   
 
  if ( (elapsedTime > ( 1/unitMovementPerSec * 1000)))
  {
       previousTime = currentTime ;
       if ( passOthroughR )
       {
          spotlightX -- ;
          spotlightY = spotlightY + 0.5;
       }
       else if ( passOthroughL )
       {
          spotlightX ++ ;
          spotlightY = spotlightY + 0.5;
       } 
       else if ( rightSide && !rightMax)
       {
         spotlightX ++ ;
         spotlightY = spotlightY + 0.5;
       }
       else if ( rightSide && rightMax )
       {
         spotlightX -- ;
         spotlightY = spotlightY - 0.5;
       }
       else if ( leftSide && !leftMax)
       {
         spotlightX -- ;
         spotlightY = spotlightY + 0.5;
       }
       else if ( leftSide && leftMax)
       {
         spotlightX ++ ;
         spotlightY = spotlightY - 0.5;
       }
  }
    
  //glutPostRedisplay();  //refresh display
  glutPostWindowRedisplay(subwindow_2);
  glutPostWindowRedisplay(subwindow_1);
}


int main (int argc, char **argv)
{
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);      //requests properties for the window (sets up the rendering context)
    glutInitWindowSize (main_window_w, main_window_h);			//set window size in pixels
    glutInitWindowPosition(50, 50);       //set window position from top-left corner of display
    main_window = glutCreateWindow (window_title);
    init ();
    
    glutDisplayFunc (main_display);
	glutReshapeFunc  (main_reshape);
	glutKeyboardFunc(myKeypress);		    //register non-ASCII keypress callback function
    glutSpecialFunc(mySpecialKeys);		//register non-ASCII keypress callback function
	
    subwindow_1 = glutCreateSubWindow (main_window, subwindow1_x, subwindow1_y, subwindow1_w, subwindow1_h);
    init();
	glutDisplayFunc (drawScene);
	glutReshapeFunc  (subwindow1_reshape);	
	glutIdleFunc(myIdleFunc);
	
    subwindow_2 = glutCreateSubWindow (main_window, subwindow2_x, subwindow2_y, subwindow2_w, subwindow2_h);
    init();
	glutDisplayFunc (drawScene);
	glutReshapeFunc  (subwindow2_reshape);
	glutIdleFunc(myIdleFunc);

    
    
    glutMainLoop();
    
}

