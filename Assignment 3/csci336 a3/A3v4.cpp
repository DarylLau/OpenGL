// Name : Lau Yan Chen Daryl
// Student Number : 4033747
// Course : BMMF
// Title : Assessment3
// fileName : A3v4.cpp
//
// Declaration : This assessment is strictly done on an individual basis
// no parts of the program is passed to my schoolmate.

#include <gl/glut.h>
#include <iostream>
#include <stdio.h>
#define GAP  15 // gap between subwindows
#include <math.h>
#define MY_PI 		(3.14159265359)    //declare PI value
#define DEG2RAD(a) 	(MY_PI/180*(a))    //convert degrees into radians
using namespace std;


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

bool gColourTracking = false;
bool gSmoothShading = true;
bool lightOn1 = true;
bool lightOn2 = true;
bool lightOn3 = true;
bool changed = true;
bool showHelp = false;
bool disco = false;
bool leftWindow = false;

//camera variables
GLfloat gCameraPosition[] = { 0.0f, 10.0f, 22.0f };
GLfloat gCameraLookAt[] = { 0.0f, 10.0f, 15.0f };
GLfloat gCameraUp[] = { 0.0f, 1.0f, 0.0f };

GLfloat gCameraPosition2[] = { 0.0f, 10.0f, 22.0f };
GLfloat gCameraLookAt2[] = { 0.0f, 10.0f, 15.0f };
GLfloat gCameraUp2[] = { 0.0f, 1.0f, 0.0f };

GLfloat gCameraYaw = 0.0f;     //camera yaw
GLfloat gCameraPitch = 0.0f;
GLfloat gCameraRoll = 0.0f;

GLfloat gCameraYaw2 = 0.0f;     //camera yaw
GLfloat gCameraPitch2 = 0.0f;
GLfloat gCameraRoll2 = 0.0f;

GLfloat gMoveForward = 0.0f;   //camera forward/backward movement variable
GLfloat gMoveUpward = 0.0f;
GLfloat gMoveRightward = 0.0f;

GLfloat gMoveForward2 = 0.0f;   //camera forward/backward movement variable
GLfloat gMoveUpward2 = 0.0f;
GLfloat gMoveRightward2 = 0.0f;


GLfloat gMovementSensitivity = 1;      //movement sensitivity
GLfloat gRotationSensitivity = 2;      //rotational sensitivity


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
GLfloat gRedEmission[] = { 1.0f, 0.0f , 0.0f , 1.0f};
GLfloat gBlueEmission[] = { 0.0f, 0.0f, 1.0f, 1.0f};
GLfloat gCyanEmission[] = { 0.0f, 1.0f, 1.0f, 1.0f };
GLfloat gWhiteEmission[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat gBlackEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f};
GLfloat gNone[] = {0.0f, 0.0f, 0.0f, 1.0f};

//light properties
GLfloat gAmbientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };	  //ambient light
GLfloat gAmbientLight2[] = { 0.5f , 0.5f , 0.5f , 1.0f }; 
GLfloat gAmbientLight3[] = { 0.7f, 0.7f, 0.7f, 1.0f};

GLfloat gDiffuseYellowLight[] = { 1.0f, 1.0f, 0.0f, 1.0f };	  //diffuse light
GLfloat gDiffuseCyanLight[] = { 0.0f, 1.0f, 1.0f, 1.0f }; // diffuse cyan light
GLfloat gDiffuseWhiteLight[] = { 1.0f, 1.0f, 1.0f, 1.0f } ; // diffuse white light
GLfloat gDiffuseRedLight[] = { 1.0f, 0.0f, 0.0f , 1.0f }; // diffuse red light
GLfloat gDiffuseBlueLight[] = { 0.0f, 0.0f, 1.0f , 1.0f }; // diffuse blue light
GLfloat gDiffuseGreenLight[] = { 0.0f, 1.0f, 0.0f, 1.0f }; // diffuse green light
GLfloat gDiffusePurpleLight[] = { 1.0f, 0.0f, 1.0f, 1.0f }; // diffuse purple light

GLfloat gLightPosition[] = { 0.0f, 28.0f, -28.0f, 1.0f }; //light position
GLfloat gLightPosition1[] = { 0.0f, 28.0f, 28.0f, 1.0f }; //light1 position

float spotlightX = 0;
float spotlightY = 20;
GLfloat gLightSpecular2[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat gLightDirection2[] = { 0.0f, -1.0f, 0.0f};

float discolightZ = 0;

GLfloat gLightSpecular3[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat gLightDirection3[] = { 0.0f, -1.0f, 0.0f};
GLfloat gLightPosition3[] = { 10, 29, discolightZ, 1.0f};

GLfloat gLightSpecular4[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat gLightDirection4[] = { 0.0f, -1.0f, 0.0f};
GLfloat gLightPosition4[] = { -10, 29, discolightZ, 1.0f};

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

// for disco
float moveY = 0;
float angle = 0;
bool up = true;
float counter = 0 ;
float slowCounter = 0;
bool in = true;


//  Call Back Functions
void init();
GLfloat* lightColour(int );
void resetCamera ();
void resetCamera2 ();
void drawScene();
void display_str(GLint, GLint , void* , char* );
void helpDisplay ();
void updateCamera();
void updateCamera2();
void myKeypress(unsigned char, int , int );
void mySpecialKeys(int, int , int );
void myMouseLeftWindow (int , int , int , int );
void myMouseRightWindow (int, int , int , int);
void subwindow1_reshape (int, int);
void subwindow2_reshape (int, int);
void main_display();
void main_reshape (int , int);
void myIdleFunc();
void myMenu(int);
void displayMenu();

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
    glLightfv(GL_LIGHT0, GL_DIFFUSE, gDiffuseYellowLight);		//set light0's diffuse component
    glLightfv(GL_LIGHT0, GL_POSITION, gLightPosition);	//set light0's position
    
    //setup light 1
    glLightfv(GL_LIGHT1, GL_AMBIENT, gAmbientLight);		//set light1's ambient component
    glLightfv(GL_LIGHT1, GL_DIFFUSE, gDiffuseCyanLight);		//set light1's diffuse component
    glLightfv(GL_LIGHT1, GL_POSITION, gLightPosition1);	//set light1's position  

    //setup spotlight 1
    GLfloat gLightPosition2[] = { spotlightX, spotlightY, 0.0f, 1.0f};
    glLightfv(GL_LIGHT2, GL_AMBIENT, gAmbientLight);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, gDiffuseWhiteLight);
    glLightfv(GL_LIGHT2, GL_SPECULAR, gLightSpecular2);
    glLightfv(GL_LIGHT2, GL_POSITION, gLightPosition2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 15.0);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, gLightDirection2);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);
  
    //setup spotlight2
    glLightfv(GL_LIGHT3, GL_AMBIENT, gAmbientLight);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, gDiffuseRedLight);
    glLightfv(GL_LIGHT3, GL_SPECULAR, gLightSpecular3);
    glLightfv(GL_LIGHT3, GL_POSITION, gLightPosition3);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 15.0);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, gLightDirection3);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 2.0);  

    //setup spotlight3
    glLightfv(GL_LIGHT4, GL_AMBIENT, gAmbientLight);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, gDiffuseRedLight);
    glLightfv(GL_LIGHT4, GL_SPECULAR, gLightSpecular4);
    glLightfv(GL_LIGHT4, GL_POSITION, gLightPosition4);
    glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 15.0);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, gLightDirection4);
    glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 2.0);  

    //enable lighting and select shading model
    glEnable(GL_LIGHT0);      //enable light0
    glEnable(GL_LIGHT1);      //enable light1
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHTING);    //enable lighting
    glEnable(GL_NORMALIZE);
//    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//    glEnable(GL_COLOR_MATERIAL);        //enable colour tracking
    glShadeModel(GL_SMOOTH);	//set shading model
}

GLfloat* lightColour(int no )
{
  switch ( no)
  {
         case 0 : 
                  return gDiffuseYellowLight ;
         case 1 : 
                  return gDiffuseRedLight;
         case 2 :
                  return gDiffuseBlueLight;
         case 3 :
                  return gDiffuseGreenLight ;
         case 4 :
                  return gDiffuseCyanLight ;
         case 5 : 
                  return gDiffusePurpleLight;
         case 6 : 
                  return gDiffuseWhiteLight;
  }
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

void resetCamera2 ()
{
  gCameraPosition2[0] = 0.0f;
  gCameraPosition2[1] = 10.0f;
  gCameraPosition2[2] = 22.0f;
  gCameraLookAt2[0] = 0.0f;
  gCameraLookAt2[1] = 10.0f;
  gCameraLookAt2[2] = 15.0f;
  gCameraUp2[0] = 0.0f;
  gCameraUp2[1] = 1.0f;
  gCameraUp2[2] = 0.0f;
  gCameraYaw2 = 0.0f;     //camera yaw
  gMoveForward2 = 0.0f;   //camera forward/backward movement variable
  gCameraPitch2 = 0.0f;
  gCameraRoll2 = 0.0f;
  gMoveUpward2 = 0.0f;
  gMoveRightward2 = 0.0f;

  updateCamera2();
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
     if(glutGetWindow() == subwindow_1)
     {          
        glRotatef (gCameraYaw, 0.0f, 1.0f, 0.0f); 
        glRotatef (gCameraPitch, 1.0f, 0.0f, 0.0f); // edited
        glRotatef (gCameraRoll, 0.0f, 0.0f, 1.0f);
     }
     else
     {
        glRotatef (gCameraYaw2, 0.0f, 1.0f, 0.0f); 
        glRotatef (gCameraPitch2, 1.0f, 0.0f, 0.0f); // edited
        glRotatef (gCameraRoll2, 0.0f, 0.0f, 1.0f);   
     }      
  }

  changed = false;

  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseBlue); 
  glColor3f(0.0f, 0.0f, 1.0f);
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
        glMaterialfv(GL_FRONT, GL_EMISSION, gYellowEmission);
        glColorMaterial (GL_FRONT, GL_EMISSION);
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glColor3f(1.0, 1.0, 0.0);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, gBlackEmission);
        glColor3f(0.0, 0.0, 0.0 );
    }
    
    glTranslatef(0.0f, 28.0f, -28.0f);
    glutSolidSphere(0.5f, 16, 16);
    glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
  glPopMatrix();
 
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseBlue); 
  glColor3f(0.0f, 0.0f, 1.0f);
  glPushMatrix();
    glTranslatef(0.0f, 28.0f, 28.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(2.0f, 1.0f, 16, 8);
  glPopMatrix(); 
 
  glLightfv(GL_LIGHT1, GL_POSITION, gLightPosition1);
  glPushMatrix();
    if(lightOn2)
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, gCyanEmission);
        glColorMaterial (GL_FRONT, GL_EMISSION);
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glColor3f(0.0, 1.0, 1.0);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, gBlackEmission);
        glColor3f( 0.0, 0.0, 0.0);
    }
    glTranslatef(0.0f, 28.0f, 28.0f);
    glutSolidSphere(0.5f, 16, 16);
    glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
  glPopMatrix();  

  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseBlue); 
  glColor3f(0.0f, 0.0f, 1.0f);
  glPushMatrix();
    glTranslatef(spotlightX, spotlightY, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(2.0f, 1.0f, 16, 8);
  glPopMatrix(); 
  
  glMaterialfv( GL_FRONT, GL_DIFFUSE, gDiffuseBlack );
  glColor3f( 0.0f, 0.0f, 0.0f);
  glBegin(GL_LINES);
    glVertex3f(0.0f, 30.0f, 0.0f );
    glVertex3f( spotlightX , spotlightY + 1, 0.0f );
  glEnd();
 
  GLfloat gLightPosition2[] = { spotlightX, spotlightY, 0.0f, 1.0f};
  glLightfv(GL_LIGHT2, GL_POSITION, gLightPosition2);
  glPushMatrix();
    if (lightOn3)
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, gWhiteEmission);
        glColorMaterial (GL_FRONT, GL_EMISSION);
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glColor3f(1.0, 1.0, 1.0);
    }
    else
    {
       glMaterialfv(GL_FRONT, GL_EMISSION, gBlackEmission); 
       glColor3f(0.0, 0.0, 0.0 );
    }
    glTranslatef(spotlightX, spotlightY, 0);
    glutSolidSphere(0.5f, 16, 16);
    glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
  glPopMatrix();  

  if ( disco)
  {
       // light 4
      glLightfv(GL_LIGHT3, GL_POSITION, gLightPosition3);
      glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, gWhiteEmission);
        glColorMaterial (GL_FRONT, GL_EMISSION);
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(10, 29, discolightZ);
        glutSolidSphere(0.5f, 16, 16);
        glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
      glPopMatrix();     
      
      // light 5
      glLightfv(GL_LIGHT4, GL_POSITION, gLightPosition4);
      glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, gWhiteEmission);
        glColorMaterial (GL_FRONT, GL_EMISSION);
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(-10, 29, discolightZ);
        glutSolidSphere(0.5f, 16, 16);
        glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
      glPopMatrix();   
      
      glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColour(counter));  
      glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColour(counter)); 
      glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColour(counter));  
      glLightfv(GL_LIGHT3, GL_DIFFUSE, lightColour(counter));  
      glLightfv(GL_LIGHT4, GL_DIFFUSE, lightColour(counter));    
        
  }
  //draw floor
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseRed);  
  glColor3f( 1.0f, 0.0f, 0.0f );
  glBegin(GL_QUADS);

    glNormal3f(0.0f, 1.0f, 0.0f);
    for ( int i = 0 ; i < 12 ; i ++ )
    {
      for ( int j = 0 ; j < 12 ; j++ )
      {
          glVertex3f(-30.0 + 5 * j , 0.0 , -30.0 + 5 * i ) ;
          glVertex3f(-30.0 + 5 * ( j + 1 ) , 0.0 , -30 + 5 * i ) ;
          glVertex3f(-30.0 + 5 * ( j + 1 ) , 0.0 , -30 + 5 * (i + 1)  );
          glVertex3f(-30.0 + 5 * j , 0.0 , -30.0 + 5 * ( i + 1 ) ) ;
          
      }
  }  
  glEnd();

  
  //draw ceiling
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLimeGreen);
  glColor3f( 0.6f, 1.0f, 0.2f);
  glBegin (GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    for ( int i = 0 ; i < 12 ; i ++ )
    {
      for ( int j = 0 ; j < 12 ; j++ )
      {
          glVertex3f(-30.0 + 5 * j , 30.0 , -30.0 + 5 * i ) ;
          glVertex3f(-30.0 + 5 * ( j + 1 ) , 30.0 , -30 + 5 * i ) ;
          glVertex3f(-30.0 + 5 * ( j + 1 ) , 30.0 , -30 + 5 * (i + 1)  );
          glVertex3f(-30.0 + 5 * j , 30.0 , -30.0 + 5 * ( i + 1 ) ) ;
          
      }
    }  
    
  glEnd();
  
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseGreen);
  glColor3f(0.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);
  //draw left wall
    glNormal3f(1.0f , 0.0f, 0.0f);
    for ( int i = 0 ; i < 6 ; i ++ )
    {
      for ( int j = 0 ; j < 12 ; j++ )
      {
          glVertex3f(-30.0, 0 + 5 * i  , -30.0 + 5 * j ) ;
          glVertex3f(-30.0, 0 + 5 * ( i + 1 ) , -30 + 5 * j ) ;
          glVertex3f(-30.0, 0 + 5 * ( i + 1 ) , -30 + 5 * (j + 1)  );
          glVertex3f(-30.0, 0 + 5 * i  , -30.0 + 5 * ( j + 1 ) ) ;
          
      }
    }  
  //draw right wall
    glNormal3f(-1.0f , 0.0f, 0.0f);
    for ( int i = 0 ; i < 6 ; i ++ )
    {
      for ( int j = 0 ; j < 12 ; j++ )
      {
          glVertex3f(30.0, 0 + 5 * i  , -30.0 + 5 * j ) ;
          glVertex3f(30.0, 0 + 5 * ( i + 1 ) , -30 + 5 * j ) ;
          glVertex3f(30.0, 0 + 5 * ( i + 1 ) , -30 + 5 * (j + 1)  );
          glVertex3f(30.0, 0 + 5 * i  , -30.0 + 5 * ( j + 1 ) ) ;
          
      }
    }  
    glEnd();
    
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseGreen);
  glColor3f( 0.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);
  //draw back wall
    glNormal3f(0.0f, 0.0f, 1.0f);
    
    for ( int i = 0 ; i < 6 ; i ++ )
    {
      for ( int j = 0 ; j < 12 ; j++ )
      {
          glVertex3f(-30.0 + 5 * j, 0 + 5 * i  , -30.0 ) ;
          glVertex3f(-30 + 5 * j, 0 + 5 * ( i + 1 ) , -30.0 ) ;
          glVertex3f( -30 + 5 * (j + 1), 0 + 5 * ( i + 1 ) , -30.0  );
          glVertex3f(-30.0 + 5 * ( j + 1 ), 0 + 5 * i  , -30.0 ) ;
          
      }
    }  
  //draw front wall
    glNormal3f(0.0f, 0.0f, -1.0f);
    for ( int i = 0 ; i < 6 ; i ++ )
    {
      for ( int j = 0 ; j < 12 ; j++ )
      {
          glVertex3f(-30.0 + 5 * j, 0 + 5 * i  , 30.0 ) ;
          glVertex3f(-30 + 5 * j, 0 + 5 * ( i + 1 ) , 30.0 ) ;
          glVertex3f( -30 + 5 * (j + 1), 0 + 5 * ( i + 1 ) , 30.0  );
          glVertex3f(-30.0 + 5 * ( j + 1 ), 0 + 5 * i  , 30.0 ) ;
          
      }
    }         
  glEnd();
 
  //draw table
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseDarkBrown); 
  glColor3f(0.65f, 0.18f, 0.18f);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glPushMatrix();
    glTranslatef(0.0f, 6.5f, 0.0f);
    glScalef(1.5f, 0.1f, 1.0f);
    glutSolidCube(10);
  glPopMatrix();
  //draw four legs of table
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightBrown);
  glColor3f(0.8f, 0.52f, 0.25f );
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
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseDarkBrown); 
  glColor3f(0.65f, 0.18f, 0.18f);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glPushMatrix();
    glTranslatef(-8.0f, 3.5f, 0.0f);
    glScalef(1.0f, 0.1f, 1.0f);
    glutSolidCube(5);
  glPopMatrix();  
  //draw four legs of chair1
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightBrown);
  glColor3f(0.8f, 0.52f, 0.25f );
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
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseDarkBrown); 
  glColor3f(0.65f, 0.18f, 0.18f);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glPushMatrix();
    glTranslatef(8.0f, 3.5f, 0.0f);
    glScalef(1.0f, 0.1f, 1.0f);
    glutSolidCube(5);
  glPopMatrix();  
  //draw four legs of chair 2
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightBrown);
  glColor3f(0.8f, 0.52f, 0.25f );
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
  glColor3f(0.0f, 0.0f, 1.0f);
  glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-2.5f, 7.0f + moveY, -2.5f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(2.0f, 4.0f, 16, 8);
  glPopMatrix();
  
  //draw sphere
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial2);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial2);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseCyan); 
  glColor3f(0.0f, 0.8f, 0.8f );
  glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-2.0f, 8.0f + moveY, 2.5f);
    glutSolidSphere(1.0f, 16, 16); 
  glPopMatrix();
  
  //draw torus
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial3);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial3);      //set material specular component 
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffusePink); 
  glColor3f(1.0f, 0.6f, 1.0f);
  glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(2.0f, 9.5f + moveY, -2.5f);
    glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);
    glutSolidTorus(0.5f, 2.0f, 8, 16);
  glPopMatrix();

  //draw teapot
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial4);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial4);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseOrange);
  glColor3f(1.0f, 0.6f, 0.2f);
  glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(1.0f, 8.1f + moveY, 1.0f);
    glRotatef(135.0f, 0.0f, 1.0f, 0.0f);
    glutSolidTeapot(1.5f);
  glPopMatrix();

  //draw dodecahedron
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial5);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial5);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightPurple);
  glColor3f( 0.6f, 0.0f, 0.8f);
  glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(5.0f, 8.4f + moveY, 0.0f);
    glRotatef(120.0f, 1.0f,  0.0f, 0.0f);
    glutSolidDodecahedron();
  glPopMatrix();  
    
  //draw octahedron
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial6);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial6);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightGreen);
  glColor3f(0.4f, 1.0f, 0.2f);
  glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-5.0f, 8.0f + moveY, 0.0f);
    glutSolidOctahedron();
  glPopMatrix();

  //draw tetrahedron
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial7);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial7);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightRed);
  glColor3f(1.0f, 0.0f, 0.2f );
  glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-4.0f, 7.55f + moveY, 4.0f);
    //glRotatef(180.0f, 1.0f, 1.0f, .0f);
    glutSolidTetrahedron();
  glPopMatrix();  
  
  //draw Icosahedron
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial8);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial8);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseBrightOrange);
  glColor3f(1.0f, 0.6f , 0.0f);
  glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(3.0f, 8.0f + moveY, 3.5f);
    glRotatef(145.0f, 1.0f, 0.0f, 0.0f);
    glutSolidIcosahedron();
  glPopMatrix();

  gFrameCount++;  
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

  glColor3f(1.0f, 1.0f, 1.0f);
  display_str (20, 580,GLUT_BITMAP_8_BY_13, "Press [h] to toggle Help Info" );
  display_str (400, 560, GLUT_BITMAP_8_BY_13, gFPS_str);
  
  if(glutGetWindow() == subwindow_1)
    display_str (400, 580, GLUT_BITMAP_8_BY_13, "Orthographic projection");
  else
    display_str (400, 580, GLUT_BITMAP_8_BY_13, "Perspective projection");
  
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  if ( leftWindow)
  {
       if(glutGetWindow() == subwindow_1)
         helpDisplay();
  }
  else
  {
      if(glutGetWindow() == subwindow_2)
        helpDisplay();
  }

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
  else if ( gCameraPitch < -22.0 )
      gCameraPitch = -22.0;
 
  gCameraPosition[2] += gMoveForward;
  gCameraLookAt[2] += gMoveForward;
  gMoveForward = 0;     //reset forward/backward movement

  gCameraPosition[1]+= gMoveUpward;
  gCameraLookAt[1] += gMoveUpward;
  gMoveUpward = 0;

  gCameraPosition[0] +=  gMoveRightward;
  gCameraLookAt[0] += gMoveRightward;
  gMoveRightward = 0;
  glLoadIdentity();     //load modelview matrix with identity matrix
  gluLookAt(gCameraPosition[0], gCameraPosition[1], gCameraPosition[2],   //set position
            gCameraLookAt[0], gCameraLookAt[1], gCameraLookAt[2],         //set where eye/camera is looking at
	        gCameraUp[0], gCameraUp[1], gCameraUp[2]);                    //set 'up' vector

  glutPostRedisplay();  //refresh display
}


void updateCamera2()
{
  if(gCameraYaw2 > 360.0)    //keep yaw between 0 - 360 degrees
    gCameraYaw2 -= 360.0;
  else if(gCameraYaw2 < 0.0)
    gCameraYaw2 += 360.0;
    
  if( gCameraRoll2 > 45.0 )
      gCameraRoll2 = 45.0;
  else if (gCameraRoll2 < -45.0 )
       gCameraRoll2 = -45.0;
  
  if ( gCameraPitch2 > 90.0 )
      gCameraPitch2 = 90.0;
  else if ( gCameraPitch2 < -22.0 )
      gCameraPitch2 = -22.0;

  gCameraPosition2[2] += gMoveForward2;
  gCameraLookAt2[2] += gMoveForward2;
  gMoveForward2 = 0;     //reset forward/backward movement

  gCameraPosition2[1]+= gMoveUpward2;
  gCameraLookAt2[1] += gMoveUpward2;
  gMoveUpward2 = 0;

  gCameraPosition2[0] +=  gMoveRightward2;
  gCameraLookAt2[0] += gMoveRightward2;
  gMoveRightward2 = 0;

  glLoadIdentity();     //load modelview matrix with identity matrix
  gluLookAt(gCameraPosition2[0], gCameraPosition2[1], gCameraPosition2[2],   //set position
            gCameraLookAt2[0], gCameraLookAt2[1], gCameraLookAt2[2],         //set where eye/camera is looking at
	        gCameraUp2[0], gCameraUp2[1], gCameraUp2[2]);                    //set 'up' vector

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
     
  gFrameCount++;
  char swing_str[50] ;
  sprintf(swing_str, "Swinging Speed - %f", unitMovementPerSec);  
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  
  glLoadIdentity();
  gluOrtho2D(0, 800, 0, 600);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  
  
  if ( showHelp)
  {
    display_str (20, 560,GLUT_BITMAP_8_BY_13, "Camera Controls" );
    display_str (20, 550,GLUT_BITMAP_8_BY_13, "=================" );
    display_str (20, 535,GLUT_BITMAP_8_BY_13, "[Up]     Zoom In" );
    display_str (20, 520,GLUT_BITMAP_8_BY_13, "[Down]   Zoom Out" );
    display_str (20, 505,GLUT_BITMAP_8_BY_13, "[Left]   Move Leftwards" );
    display_str (20, 490,GLUT_BITMAP_8_BY_13, "[Right]  Move Rightwards" );
    display_str (20, 475,GLUT_BITMAP_8_BY_13, "[Home]   Move Upwards" );
    display_str (20, 460,GLUT_BITMAP_8_BY_13, "[End]    Move Downwards" );
    display_str (20, 445,GLUT_BITMAP_8_BY_13, "[u]      Roll Left" );
    display_str (20, 430,GLUT_BITMAP_8_BY_13, "[o]      Roll Right" );
    display_str (20, 415,GLUT_BITMAP_8_BY_13, "[i]      Pitch Up" );
    display_str (20, 400,GLUT_BITMAP_8_BY_13, "[k]      Pitch Down" );
    display_str (20, 385,GLUT_BITMAP_8_BY_13, "[j]      Yaw Left" );
    display_str (20, 370,GLUT_BITMAP_8_BY_13, "[l]      Yaw Right" );
    display_str (20, 355,GLUT_BITMAP_8_BY_13, "[r]      Reset Camera" );
  
    display_str (20, 330,GLUT_BITMAP_8_BY_13, "Display" );
    display_str (20, 320,GLUT_BITMAP_8_BY_13, "=================" );
    display_str (20, 305,GLUT_BITMAP_8_BY_13, "[w]      Wire Frame Mode" );
    display_str (20, 290,GLUT_BITMAP_8_BY_13, "[s]      Solid Fill Mode" );
    display_str (20, 275,GLUT_BITMAP_8_BY_13, "[q]      Flat/Smooth Shading" );
    display_str (20, 260,GLUT_BITMAP_8_BY_13, "[a]      Colour Tracking" );
  
    display_str (20, 235,GLUT_BITMAP_8_BY_13, "Lights" );
    display_str (20, 225,GLUT_BITMAP_8_BY_13, "==================" );
    display_str (20, 210,GLUT_BITMAP_8_BY_13, "[1]      Toggle BackLight on/off " );
    display_str (20, 195,GLUT_BITMAP_8_BY_13, "[2]      Toggle FrontLight on/off" );
    display_str (20, 180,GLUT_BITMAP_8_BY_13, "[3]      Toggle SpotLight on/off" );
    display_str (20, 165,GLUT_BITMAP_8_BY_13, "[d]      Toggle Disco on/off" );
    display_str (20, 150,GLUT_BITMAP_8_BY_13, "[z]      Decrease Swinging Speed" );
    display_str (20, 135,GLUT_BITMAP_8_BY_13, "[x]      Increase Swinging Speed" );
    display_str (20, 120,GLUT_BITMAP_8_BY_13, swing_str );

    display_str (20, 95,GLUT_BITMAP_8_BY_13, "Quit" );
    display_str (20, 85 ,GLUT_BITMAP_8_BY_13, "==================" );
    display_str (20, 70 ,GLUT_BITMAP_8_BY_13, "[Esc]     Close Application" );
  }
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
     
}

void myMouseLeftWindow (int button, int state, int x, int y)
{
   if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   {
      leftWindow = true;
   }
}     

void myMouseRightWindow (int button, int state, int x, int y)
{
   if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   {
      leftWindow = false;
   }
} 
//called when ASCII key pressed
void myKeypress(unsigned char key, int x, int y)
{
  if ( leftWindow)
  {
       glutSetWindow(subwindow_1);
  }
  else
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
               if ( leftWindow)
                  resetCamera();
               else
                   resetCamera2();
               break;
    case 'q' :
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
    
    case 'a' :
               if ( gColourTracking)
               {
                    glDisable(GL_COLOR_MATERIAL);
                    gColourTracking = false;
                    
                    glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial);
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseMaterial);
               }
               else
               {
                   glEnable(GL_COLOR_MATERIAL);
                   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  
                   gColourTracking = true;
               }
               break; 
    
    case 'd' :
               if ( disco )
               {
                  glDisable ( GL_LIGHT3);
                  glDisable ( GL_LIGHT4);
                  glLightfv(GL_LIGHT0, GL_DIFFUSE, gDiffuseYellowLight);
                  glLightfv(GL_LIGHT1, GL_DIFFUSE, gDiffuseCyanLight);
                  glLightfv(GL_LIGHT2, GL_DIFFUSE, gDiffuseWhiteLight);
                  disco = false;
               }
               else
               {

                    glEnable ( GL_LIGHT4);
                    glEnable ( GL_LIGHT3 );
                   disco = true;
               }
               break; 
    
    case 'z' :
                unitMovementPerSec -- ;
                if ( unitMovementPerSec <= 5 )
                   unitMovementPerSec = 5 ;
                 
                 break;
    
    case 'x' :
                 unitMovementPerSec ++ ;
                 if ( unitMovementPerSec >= 60 )
                    unitMovementPerSec = 60;
                  
                  break;          
    
    case 'h' :
                 if ( showHelp )
                 {
                      showHelp = false;
                 }
                 else
                     showHelp = true;
                 break;
                   
    case 'u' : 
               if ( leftWindow)        
                  gCameraRoll -= gRotationSensitivity;
               else
                  gCameraRoll2 -= gRotationSensitivity; 
               break;
    case 'o' :
               if ( leftWindow )
                  gCameraRoll += gRotationSensitivity;
               else
                  gCameraRoll2 += gRotationSensitivity;
               break;
    case 'i' :
               if ( leftWindow )
                  gCameraPitch += gRotationSensitivity;
               else
                  gCameraPitch2 += gRotationSensitivity; 
               break;
    case 'k' : 
               if ( leftWindow)
                   gCameraPitch -= gRotationSensitivity;
               else
                   gCameraPitch2 -= gRotationSensitivity;
               break;
    case 'j' : 
               if ( leftWindow)
                  gCameraYaw -= gRotationSensitivity; 
               else
                  gCameraYaw2 -= gRotationSensitivity; 
               break;
    case 'l' :
               if ( leftWindow)
                   gCameraYaw += gRotationSensitivity; 
               else
                   gCameraYaw2 += gRotationSensitivity;
               break;
    default: break;
  };
  updateCamera();
  updateCamera2();
  glutPostRedisplay();  //refresh display
}

//called when non-ASCII key pressed
void mySpecialKeys(int key, int x, int y)
{
  if ( leftWindow)
  {
       glutSetWindow(subwindow_1);
  }
  else
       glutSetWindow (subwindow_2);      
  changed = true; 
  switch(key)
  {
    //if home pressed
    case GLUT_KEY_HOME: 
                        if ( leftWindow)
                        {
                           gCameraPosition[1] += gMovementSensitivity;       //increment camera height
                           gCameraLookAt[1] += gMovementSensitivity;
                        }
                        else
                        {
                           gCameraPosition2[1] += gMovementSensitivity;       //increment camera height
                           gCameraLookAt2[1] += gMovementSensitivity;
                        } 
		                break;
    //if end pressed
    case GLUT_KEY_END:  
                        if ( leftWindow )
                        {
                           gCameraPosition[1] -= gMovementSensitivity;       //decrement camera height
                           gCameraLookAt[1] -= gMovementSensitivity;
                        }
                        else
                        {
                            gCameraPosition2[1] -= gMovementSensitivity;       //decrement camera height
                            gCameraLookAt2[1] -= gMovementSensitivity;
                        }
		                break;
    //if arrow up pressed
    case GLUT_KEY_UP:   
                        if ( leftWindow)
                           gMoveForward -= gMovementSensitivity;             //increment forward movement
                        else
                           gMoveForward2 -= gMovementSensitivity;
		                break;
    //if arrow down pressed
    case GLUT_KEY_DOWN: 
                        if ( leftWindow)
                           gMoveForward += gMovementSensitivity;             //increment backward movement
                        else
                            gMoveForward2 += gMovementSensitivity;
		                break;
    //if left pressed
    case GLUT_KEY_LEFT: 
    	                if ( leftWindow)
                             gMoveRightward -= gMovementSensitivity;
                        else
                            gMoveRightward2 -= gMovementSensitivity;
                        break;
    //if right pressed
    case GLUT_KEY_RIGHT: 
                        if ( leftWindow )
                             gMoveRightward += gMovementSensitivity;              //decrement camera yaw
                        else
                            gMoveRightward2 += gMovementSensitivity;
    	                break;
    default: break;
  };
  
  updateCamera();       //call function to update camera and refresh the scene
  updateCamera2();
  glutPostRedisplay();  //refresh display
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

  gluLookAt(gCameraPosition2[0], gCameraPosition2[1], gCameraPosition2[2],   //set position
            gCameraLookAt2[0], gCameraLookAt2[1], gCameraLookAt2[2],         //set where eye/camera is looking at
	        gCameraUp2[0], gCameraUp2[1], gCameraUp2[2]);                    //set 'up' vector
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
       if ( disco )
       {
            if ( in )
            {
                 discolightZ ++;
            }
            else
            {
                discolightZ --;
            }
            if ( discolightZ >= 20 )
            {
                 in = false;
            }
            else if ( discolightZ <= -20 )
            {
                 in = true;
            }
       }
  }
  
  
  if ( disco )
  {
       if ( up )
       {
            moveY = moveY + 0.25 ;
       }
       else
       {
           moveY = moveY - 0.25 ;
       }
       
       if ( moveY >= 5 )
       {
            up = false;
       }
       else if ( moveY <= 0 )
       {
            up = true;
       }
       
       angle ++ ;
       if ( angle >= 360 )
          angle = 0 ;
          
       slowCounter = slowCounter + 0.20 ;
       if ( slowCounter == 1 )
       {
            counter = rand()% 6;
            slowCounter = 0;
       }
  }
  else
  {
      moveY = 0;
      angle = 0;
  }      

  if (leftWindow)
     glutPostWindowRedisplay(subwindow_1);
  else
     glutPostWindowRedisplay(subwindow_2);
}

void displayMenu()
{
// what is to be shown in the menu when right click     

  int sub_menu = glutCreateMenu(myMenu);
  glutAddMenuEntry("low", 'q');
  glutAddMenuEntry("medium", 'w');
  glutAddMenuEntry("high", 'e');

  int main_menu = glutCreateMenu(myMenu);
  glutAddMenuEntry("Main Menu", 0);
  glutAddMenuEntry("", 0);
  glutAddSubMenu("Ambient Settings", sub_menu);
  glutAddMenuEntry("Reset Camera" , 2 );
  glutAddMenuEntry("Quit", 1);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void myMenu(int value)
{
// show what each of the different case in the menu does     
  switch(value)
  {
    case 1: exit(1);
            break;
    case 2: resetCamera();
            break;
    case 'q':   glLightfv(GL_LIGHT0, GL_AMBIENT, gAmbientLight);
                glLightfv(GL_LIGHT1, GL_AMBIENT, gAmbientLight);	
                glLightfv(GL_LIGHT2, GL_AMBIENT, gAmbientLight);		
              break;
    case 'w':   glLightfv(GL_LIGHT0, GL_AMBIENT, gAmbientLight2);
                glLightfv(GL_LIGHT1, GL_AMBIENT, gAmbientLight2);	
                glLightfv(GL_LIGHT2, GL_AMBIENT, gAmbientLight2);		
              break;
    case 'e':   glLightfv(GL_LIGHT0, GL_AMBIENT, gAmbientLight3);
                glLightfv(GL_LIGHT1, GL_AMBIENT, gAmbientLight3);	
                glLightfv(GL_LIGHT2, GL_AMBIENT, gAmbientLight3);		
              break;

    default: break;
  };
  
  glutPostWindowRedisplay(subwindow_1);
  glutPostWindowRedisplay(subwindow_2);  
}


int main (int argc, char **argv)
{
    srand(time(NULL));
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
	glutMouseFunc(myMouseLeftWindow);
	glutIdleFunc(myIdleFunc);
	displayMenu();

    subwindow_2 = glutCreateSubWindow (main_window, subwindow2_x, subwindow2_y, subwindow2_w, subwindow2_h);
    init();
	glutDisplayFunc (drawScene);
	glutReshapeFunc  (subwindow2_reshape);
	glutMouseFunc(myMouseRightWindow);
	glutIdleFunc(myIdleFunc);
	displayMenu();
    
    glutMainLoop();
}

