// Name : Lau Yan Chen Daryl
// Student Number : 4033747
// Course : BMMF
// Title : Assignment
// fileName : AssnV1.cpp
//
// Declaration : This assessment is strictly done on an individual basis
// no parts of the program is passed to my schoolmate.

#include <gl/glut.h>    //include glut library (automatically includes gl and glu libraries)
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <WinGDI.h>

#define MY_PI 		(3.14159265359)    //declare PI value
#define DEG2RAD(a) 	(MY_PI/180*(a))    //convert degrees into radians
using namespace std;

//camera variables
GLfloat gCameraPosition[] = { 0.0f, 10.0f, 15.0f };
GLfloat gCameraLookAt[] = { 0.0f, 10.0f, 14.0f };
GLfloat gCameraUp[] = { 0.0f, 1.0f, 0.0f };

GLfloat gCameraYaw = 0.0f;     //camera yaw
GLfloat gCameraPitch = 0.0f;
GLfloat gCameraRoll = 0.0f;
GLfloat gMoveForward = 0.0f;   //camera forward/backward movement variable
GLfloat gMoveUpward = 0.0f;
GLfloat gMoveRightward = 0.0f;


GLfloat gMovementSensitivity = 1;      //movement sensitivity
GLfloat gRotationSensitivity = 2;      //rotational sensitivity

// material properties
GLfloat gAmbientMaterial[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat gDiffuseMaterial[] = {0.0f, 0.0f, 1.0f, 1.0f};
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

  
GLfloat gAmbientFloor[] = {0.5f, 0.5f, 0.5f, 0.6f};
GLfloat gDiffuseFloor[] = {1.0f, 0.5f, 0.2f, 0.6f};  


GLfloat gDiffuseBlue[] = {0.0f, 0.0f, 1.0f, 1.0f};
GLfloat gDiffuseRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
GLfloat gDiffuseWhite[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat gDiffuseWhiteTransparent[] = { 1.0f, 1.0f, 1.0f, 0.3f};
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
GLfloat gDiffuseBrownWall[] = { 0.8f, 0.2f, 0.0f, 1.0f };


GLfloat gYellowEmission[] = {1.0f, 1.0f, 0.0f, 1.0f};
GLfloat gRedEmission[] = { 1.0f, 0.0f , 0.0f , 1.0f};
GLfloat gBlueEmission[] = { 0.0f, 0.0f, 1.0f, 1.0f};
GLfloat gCyanEmission[] = { 0.0f, 1.0f, 1.0f, 1.0f };
GLfloat gWhiteEmission[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat gBlackEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f};
GLfloat gNone[] = {0.0f, 0.0f, 0.0f, 1.0f};

//light properties
GLfloat gAmbientLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };	  //ambient light
GLfloat gAmbientLight2[] = { 0.4f, 0.4f, 0.4f, 1.0f };	  //ambient light
GLfloat gDiffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };	  //diffuse light
GLfloat gDiffuseYellowLight[] = { 1.0f, 1.0f, 0.0f, 1.0f };	  //diffuse light
GLfloat gDiffuseCyanLight[] = { 0.0f, 1.0f, 1.0f, 1.0f }; // diffuse cyan light
GLfloat gDiffuseWhiteLight[] = { 1.0f, 1.0f, 1.0f, 1.0f } ; // diffuse white light
GLfloat gDiffuseRedLight[] = { 1.0f, 0.0f, 0.0f , 1.0f }; // diffuse red light
GLfloat gDiffuseBlueLight[] = { 0.0f, 0.0f, 1.0f , 1.0f }; // diffuse blue light
GLfloat gDiffuseGreenLight[] = { 0.0f, 1.0f, 0.0f, 1.0f }; // diffuse green light
GLfloat gDiffusePurpleLight[] = { 1.0f, 0.0f, 1.0f, 1.0f }; // diffuse purple light

GLfloat gLightPosition[] = { 0.0f, 35.0f, 0.0f, 0.0f }; //light position

GLfloat gLightSpecular1[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat gLightDirection1[] = { 0.0f, -1.0f, 0.0f};
GLfloat gLightPosition1[] = { -47, 40, 0.0 , 1.0f};

GLfloat gLightSpecular2[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat gLightDirection2[] = { 0.0f, -1.0f, 0.0f};
GLfloat gLightPosition2[] = { 20, 40, -20.0 , 1.0f};

GLfloat gLightSpecular3[] = { 0.6, 0.6, 0.6, 1.0 };
GLfloat gLightDirection3[] = { 0.0f, -1.0f, 0.0f};
GLfloat gLightPosition3[] = { 47, 40, 0.0 , 1.0f};

GLfloat gLightSpecular4[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat gLightDirection4[] = { 0.0f, -1.0f, 0.0f};
GLfloat gLightPosition4[] = { -25.0, 40.0, 37.0 , 1.0f};

GLfloat gLightSpecular5[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat gLightDirection5[] = { 0.0f, 0.0f, -1.0f};


// boolean
bool dayTime = true;
bool showHelp = false;
bool lightOn1 = true;
bool lightOn2 = true;
bool lightOn3 = true;
bool lightOn4 = true;
bool lightOn5 = true;
bool flashOn = true;
bool picTaken = false;
int bCounter = 7 ;
bool changed = true;
int flashColour = 4;
int flashIntensity = 1;
bool motionBlurring = false;
bool aa = false;

// for motion blurring
GLint gTotalPasses = 20; // total number of passes


//variables to store texture information
unsigned char* tex_image;   //image data
GLuint textureID;           //texture id
GLint imageWidth;           //image width info
GLint imageHeight;          //image height info
const int noOfTexture = 20;
GLuint textures[noOfTexture];   

GLUquadric *quad;

// for idle function
float angle = 0.0f;
int currentTime, previousTime, elapsedTime = 0 ;
float unitMovementPerSec = 10;
static long last_update_time = glutGet(GLUT_ELAPSED_TIME);
static GLint gFrameCount = 0;   //frame count
static float gFPS = 0;          //frames per second
static char gFPS_str[50];  

// for reading file
int qty = 0 ;
static char fileName_str[50];

// functions
unsigned char* LoadBMPFile(char *) ;
void init();
void resizeWindow(int, int) ;
void loadTexture(GLuint , char* );
void drawCube();
void display_str(GLint , GLint , void* , char* );
void helpDisplay();
void drawFloor();
void drawScene();
void drawAllObject();
void updateCamera();
void resetCamera ();
void myKeypress(unsigned char, int, int );
void mySpecialKeys(int, int, int );
void myIdleFunc();
void SaveAsBMP(const char *);
void readFile( fstream&  , char* );
void writeFile( fstream&  , char* );


unsigned char* LoadBMPFile(char *filename)
{
  BITMAPINFOHEADER BMPInfoHeader;     //bitmap info header
  BITMAPFILEHEADER BMPFileHeader;	  //bitmap file header
  FILE *filePtr;					  //the file pointer
  unsigned char *bitmapImage;		  //bitmap image data
  unsigned char temp;				  //temp variable for swapping RGB values
  int size, i = 0;		              //counter


  // open filename for reading in binary mode
  if ((filePtr = fopen(filename, "rb")) == NULL)
  {
	return NULL;
  }
  
  // read bitmap file header
  fread(&BMPFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	
  // check whether file is really a bitmap file
  if (BMPFileHeader.bfType != 0x4D42)
  {
    fclose(filePtr); // if file is not a bitmap file the close and return NULL
	return NULL;
  }

  // read bitmap information header
  fread(&BMPInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

  // locate beginning of bitmap data
  fseek(filePtr, BMPFileHeader.bfOffBits, SEEK_SET);

  size = BMPInfoHeader.biSizeImage;      // store image size
  
  imageWidth = BMPInfoHeader.biWidth;    // store image width 
  imageHeight = BMPInfoHeader.biHeight;  // store image height

  // allocate memory for image data, check if not allocated properly then close file and return NULL
  if((bitmapImage = (unsigned char*)malloc(size)) == NULL)
  {
	fclose(filePtr);
	return NULL;
  }
 
  // read bitmap data
  fread(bitmapImage, 1, size, filePtr);

  // colours in bitmap are of the format BGR, hence need to swap B and R to get RGB
  for (i = 0; i < size; i += 3)
  {
    temp = bitmapImage[i];
	bitmapImage[i] = bitmapImage[i+2];
	bitmapImage[i+2] = temp;
  }

  fclose(filePtr);    // close file
  return bitmapImage; // return pointer to image data
}

//set up states that are going to be used
void init()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //set clear background colour to black
  glClearAccum(0.0, 0.0, 0.0, 1.0f); //clear accumulation buffer to black

  glEnable(GL_DEPTH_TEST);	//enable depth test

  //set material properties
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial);      //set material specular component
  glMateriali(GL_FRONT, GL_SHININESS, gShininessMaterial);     //set material shininess

  //setup light 0
  glLightfv(GL_LIGHT0, GL_AMBIENT, gAmbientLight);		//set light0's ambient component
  glLightfv(GL_LIGHT0, GL_DIFFUSE, gDiffuseWhiteLight);		//set light0's diffuse component
  glLightfv(GL_LIGHT0, GL_POSITION, gLightPosition);	//set light0's position

  //setup light 1 ( spotlight )(left side)
  glLightfv(GL_LIGHT1, GL_AMBIENT, gAmbientLight);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, gDiffuseWhiteLight);
  glLightfv(GL_LIGHT1, GL_SPECULAR, gLightSpecular1);
  glLightfv(GL_LIGHT1, GL_POSITION, gLightPosition1);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, gLightDirection1);
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 5.0);    
  
  //setup light 2 ( spotlight )(table side)
  glLightfv(GL_LIGHT2, GL_AMBIENT, gAmbientLight);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, gDiffuseWhiteLight);
  glLightfv(GL_LIGHT2, GL_SPECULAR, gLightSpecular2);
  glLightfv(GL_LIGHT2, GL_POSITION, gLightPosition2);
  glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 50.0);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, gLightDirection2);
  glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);  
 
 // setup light 3 ( spotlight) (right side)
  glLightfv(GL_LIGHT3, GL_AMBIENT, gAmbientLight);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, gDiffuseWhiteLight);
  glLightfv(GL_LIGHT3, GL_SPECULAR, gLightSpecular3);
  glLightfv(GL_LIGHT3, GL_POSITION, gLightPosition3);
  glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 40.0);
  glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, gLightDirection3);
  glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 5.0);    
  
  // setup light 4 ( spotlight) (right side)
  glLightfv(GL_LIGHT4, GL_AMBIENT, gAmbientLight);
  glLightfv(GL_LIGHT4, GL_DIFFUSE, gDiffuseWhiteLight);
  glLightfv(GL_LIGHT4, GL_SPECULAR, gLightSpecular4);
  glLightfv(GL_LIGHT4, GL_POSITION, gLightPosition4);
  glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 30.0);
  glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, gLightDirection4);
  glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 5.0); 
  
  
  // setup flashlight
  GLfloat gLightPosition5[] = { gCameraPosition[0], gCameraPosition[1], gCameraPosition[2] , 1.0f};
  glLightfv(GL_LIGHT5, GL_AMBIENT, gAmbientLight);
  glLightfv(GL_LIGHT5, GL_DIFFUSE, gDiffuseWhiteLight);
  glLightfv(GL_LIGHT5, GL_SPECULAR, gLightSpecular5);
  glLightfv(GL_LIGHT5, GL_POSITION, gLightPosition5);
  glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 15.0);
  glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, gLightDirection5);
  glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 5.0); 
  
  
   // load BMP file into image
 
  glGenTextures(noOfTexture, textures);
  loadTexture(textures[0], "marble4.bmp");
  loadTexture(textures[1], "wall3.bmp");
  loadTexture(textures[2], "ceilwhite.bmp");
  loadTexture(textures[3], "wooden3.bmp");
  loadTexture(textures[4], "wooden2.bmp");
  loadTexture(textures[5], "silver.bmp");
  loadTexture(textures[6], "plate.bmp");
  loadTexture(textures[7], "honeycomb.bmp");
  loadTexture(textures[8], "chocolate.bmp");
  loadTexture(textures[9], "blackwood.bmp");
  loadTexture(textures[10], "lightwood.bmp");
  loadTexture(textures[11], "wallpaper.bmp");
  loadTexture(textures[12], "portrait1.bmp");
  loadTexture(textures[13], "cute.bmp");
  loadTexture(textures[14], "bear.bmp");
  loadTexture(textures[15], "room.bmp");

  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

//glBindTexture(GL_TEXTURE_2D, textures[1]);
  glBindTexture(GL_TEXTURE_2D, 0);

  //enable lighting and select shading model
  glEnable(GL_LIGHT0);      //enable light0
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHT3);
  glEnable(GL_LIGHT4);
  glEnable(GL_LIGHT5);
  glEnable(GL_LIGHTING);    //enable lighting
  glShadeModel(GL_SMOOTH);	//set shading model
  glEnable(GL_TEXTURE_2D);	// enable 2D texturing
   
}

void loadTexture(GLuint texture, char* filename)
{
// load mutiple texture
  tex_image = LoadBMPFile(filename);

  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imageWidth, imageHeight, GL_RGB, GL_UNSIGNED_BYTE, tex_image);
}

//called whenever the window is resized (also called once when window is first drawn)
void resizeWindow(int width, int height)   //window width and height
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


void drawCube()
{
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);	// top face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    glNormal3f(0.0f, 0.0f, 1.0f);	// front face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);

    glNormal3f(1.0f, 0.0f, 0.0f);	// right face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

    glNormal3f(-1.0f, 0.0f, 0.0f);	// left face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);

    glNormal3f(0.0f, -1.0f, 0.0f);	// bottom face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);	

    glNormal3f(0.0f, 0.0f, -1.0f);	// back face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
  glEnd();

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


void helpDisplay()
{
// help menu
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
  display_str (400, 580, GLUT_BITMAP_8_BY_13, gFPS_str);
   if ( showHelp)
  {
    display_str (20, 560,GLUT_BITMAP_8_BY_13, "Camera Controls" );
    display_str (20, 550,GLUT_BITMAP_8_BY_13, "=================" );
    display_str (20, 535,GLUT_BITMAP_8_BY_13, "[Up]     Move Forward/ Zoom In" );
    display_str (20, 520,GLUT_BITMAP_8_BY_13, "[Down]   Move Backward/ Zoom Out" );
    display_str (20, 505,GLUT_BITMAP_8_BY_13, "[Left]   Move Leftwards" );
    display_str (20, 490,GLUT_BITMAP_8_BY_13, "[Right]  Move Rightwards" );
    display_str (20, 475,GLUT_BITMAP_8_BY_13, "[Pg Up]   Move Upwards" );
    display_str (20, 460,GLUT_BITMAP_8_BY_13, "[Pg Down]    Move Downwards" );
    display_str (20, 445,GLUT_BITMAP_8_BY_13, "[q]      Roll Left" );
    display_str (20, 430,GLUT_BITMAP_8_BY_13, "[e]      Roll Right" );
    display_str (20, 415,GLUT_BITMAP_8_BY_13, "[w]      Pitch Up" );
    display_str (20, 400,GLUT_BITMAP_8_BY_13, "[s]      Pitch Down" );
    display_str (20, 385,GLUT_BITMAP_8_BY_13, "[a]      Yaw Left" );
    display_str (20, 370,GLUT_BITMAP_8_BY_13, "[d]      Yaw Right" );
    display_str (20, 355,GLUT_BITMAP_8_BY_13, "[r]      Reset Camera" );
  
    display_str (20, 330,GLUT_BITMAP_8_BY_13, "Display" );
    display_str (20, 320,GLUT_BITMAP_8_BY_13, "=================" );
    display_str (20, 305,GLUT_BITMAP_8_BY_13, "[n]      Night/ Day Mode" );
    display_str (20, 290,GLUT_BITMAP_8_BY_13, "[b]      Wireframe mode with Black background" );
    display_str (20, 275,GLUT_BITMAP_8_BY_13, "[b]      Wireframe mode with White background" );
    display_str (20, 260,GLUT_BITMAP_8_BY_13, "[b]      Wireframe mode with Blue background" );
    display_str (20, 245,GLUT_BITMAP_8_BY_13, "[b]      Solid mode with Primitives coloured w/o textures or lighting" );
    display_str (20, 230,GLUT_BITMAP_8_BY_13, "[b]      Solid mode with Primitives shaded using lighting" );
    display_str (20, 215,GLUT_BITMAP_8_BY_13, "[b]      Solid mode with Primitives textured w/o lighting " );
    display_str (20, 200,GLUT_BITMAP_8_BY_13, "[b]      Solid mode with Primitives shaded using lighting and textured" );

    display_str (20, 175,GLUT_BITMAP_8_BY_13, "Lightings" );
    display_str (20, 165,GLUT_BITMAP_8_BY_13, "==================" );
    display_str (20, 150,GLUT_BITMAP_8_BY_13, "[1]      Toggle Center Light on/off" );
    display_str (20, 135,GLUT_BITMAP_8_BY_13, "[2]      Toggle Left Spotlight on/off" );
    display_str (20, 120,GLUT_BITMAP_8_BY_13, "[3]      Toggle Table Spotlight on/off" );
    display_str (20, 105,GLUT_BITMAP_8_BY_13, "[4]      Toggle Right Spotlight on/off" );
    display_str (20, 90,GLUT_BITMAP_8_BY_13,  "[5]      Toggle Picture Spotlight on/off" );
    
    display_str (400, 560,GLUT_BITMAP_8_BY_13, "Flash Light" );
    display_str (400, 550,GLUT_BITMAP_8_BY_13, "=================" );
    display_str (400, 535,GLUT_BITMAP_8_BY_13, "[f]      Toggle Flashlight on/off" );
    display_str (400, 520,GLUT_BITMAP_8_BY_13, "[i]      Toggle Flashlight Intensity ( low, medium, high )" );
    display_str (400, 505,GLUT_BITMAP_8_BY_13, "[c]      Toggle Flashlight Colour ( red, green, blue, white)" );
    
    display_str (400, 480,GLUT_BITMAP_8_BY_13, "Quit" );
    display_str (400, 470 ,GLUT_BITMAP_8_BY_13, "==================" );
    display_str (400, 455,GLUT_BITMAP_8_BY_13, "[Esc]     Close Application" );
    
    display_str (400, 430,GLUT_BITMAP_8_BY_13, "Advance Task" );
    display_str (400, 420,GLUT_BITMAP_8_BY_13, "====================" );
    display_str (400, 405,GLUT_BITMAP_8_BY_13, "[p]       ScreenShot" );
    display_str (400, 395,GLUT_BITMAP_8_BY_13, "[m]       Motion Blurring" );
    display_str (400, 380,GLUT_BITMAP_8_BY_13, "[x]       Full Scene Anti-aliasing" );
  }
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

void drawFloor()
{
  //draw floor
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseWhite);        //set material diffuse component
  glColor3f(1.0f, 1.0f, 1.0f );
  glBindTexture(GL_TEXTURE_2D, textures[0]);
  glBegin(GL_QUADS);
   glNormal3f(0.0f, 1.0f, 0.0f);
    for ( int i = 0 ; i < 16 ; i ++ )
    {
      for ( int j = 0 ; j < 20 ; j++ )
      {
          glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0 + 5 * j , 0.0 , -40.0 + 5 * i ) ;
          glTexCoord2f(1.0f, 1.0f); glVertex3f(-50.0 + 5 * ( j + 1 ) , 0.0 , -40 + 5 * i ) ;
          glTexCoord2f(1.0f, 0.0f); glVertex3f(-50.0 + 5 * ( j + 1 ) , 0.0 , -40 + 5 * (i + 1)  );
          glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0 + 5 * j , 0.0 , -40.0 + 5 * ( i + 1 ) ) ;     
      }
  }  
  glEnd();
}

//draw the scene here
void drawScene()
{
     
   GLint current_pass;	
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);  //clear the colour buffer to the colour previously set in glClearColor 
  
  // wireframe , black, blue white background
  if ( bCounter == 2 )
  {
     glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
  }
  else if ( bCounter == 3 )
  {
       glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
  }
  else
  {
      glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
  }
  
  
  // camera yaw, pitch, row
  float x , y , z ;
  if (changed)
  {   
    glLoadIdentity();       
    glRotatef (gCameraRoll, 0.0f, 0.0f, 1.0f);  
    glRotatef (gCameraPitch, 1.0f, 0.0f, 0.0f); 
    glRotatef (gCameraYaw, 0.0f, 1.0f, 0.0f); 
    glTranslated(-gCameraPosition[0], -gCameraPosition[1], -gCameraPosition[2]);
  }
  changed = false;
  
  // specifying flashlight colour
  if ( flashColour == 1 )
       glLightfv(GL_LIGHT5, GL_DIFFUSE, gDiffuseRedLight);
  else if ( flashColour == 2 )
       glLightfv(GL_LIGHT5, GL_DIFFUSE, gDiffuseGreenLight);
  else if ( flashColour == 3 )
       glLightfv(GL_LIGHT5, GL_DIFFUSE, gDiffuseBlueLight);
  else if ( flashColour == 4 )
       glLightfv(GL_LIGHT5, GL_DIFFUSE, gDiffuseWhiteLight);
  
  // specifying flashlight intensity
  if ( flashIntensity == 1 )     
       glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 5.0); 
  else if ( flashIntensity == 2 )
       glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 50.0);
  else if (flashIntensity == 3 )
       glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 100.0);  

// reflective floor surface
//disable depth buffer and draw mirror surface to stencil buffer
  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);  //disable any modification of all color components
  glDepthMask(GL_FALSE);                                //disable any modification to depth buffer
  glEnable(GL_STENCIL_TEST);                            //enable stencil testing

  //setup the stencil buffer for a function reference value
  glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
  glStencilFunc(GL_ALWAYS, 1, 1);

  drawFloor();              //draw floor

//enable depth buffer, draw reflected geometry where stencil buffer passes

  //render where the stencil buffer equal to 1
  glStencilFunc(GL_EQUAL, 1, 1);
  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);   //allow all color components to be modified 
  glDepthMask(GL_TRUE);                              //allow depth buffer contents to be modified

  glPushMatrix();
    glScalef(1.0, -1.0, 1.0);
    glLightfv(GL_LIGHT0, GL_POSITION, gLightPosition);	//set light0's position
    glLightfv(GL_LIGHT1, GL_POSITION, gLightPosition1);
    glLightfv(GL_LIGHT2, GL_POSITION, gLightPosition2);
    glLightfv(GL_LIGHT3, GL_POSITION, gLightPosition3);
    glLightfv(GL_LIGHT4, GL_POSITION, gLightPosition4);
    drawAllObject();             //draw all objects
  glPopMatrix();

  glLightfv(GL_LIGHT0, GL_POSITION, gLightPosition);   //reset light0's position
  glLightfv(GL_LIGHT1, GL_POSITION, gLightPosition1);
  glLightfv(GL_LIGHT2, GL_POSITION, gLightPosition2);
  glLightfv(GL_LIGHT3, GL_POSITION, gLightPosition3);
  glLightfv(GL_LIGHT4, GL_POSITION, gLightPosition4);	
  glDisable(GL_STENCIL_TEST);     	//disable stencil testing

  //blend in reflection
  glEnable(GL_BLEND);  //enable blending            
  glBlendFunc(GL_ONE, GL_ONE);
  drawFloor();              //draw floor
  glDisable(GL_BLEND);      //disable blending

  // when anti aliasing is enabled
  if ( aa)
  {
     glEnable( GL_LINE_SMOOTH );
     glEnable( GL_POLYGON_SMOOTH );
     glEnable (GL_BLEND);
     glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     glHint( GL_LINE_SMOOTH_HINT, GL_NICEST);
     glHint( GL_POLYGON_SMOOTH_HINT,GL_NICEST);
     glLineWidth (1.5);            
  }
  
  drawAllObject();
  glDisable (GL_BLEND);

  glFlush();
  glutSwapBuffers();        //swap front and back buffers
}

void drawAllObject()
{
// draw all the objects
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseMaterial);  

  glPushMatrix();
    if(lightOn1)
    {
      glMaterialfv(GL_FRONT, GL_EMISSION, gWhiteEmission);  //set material emission component
      glColorMaterial(GL_FRONT, GL_EMISSION);
      glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
      glColor3f(1.0, 1.0, 1.0);
    }
    else
    {
      glMaterialfv(GL_FRONT, GL_EMISSION, gBlackEmission);
      glColor3f(0.0, 0.0, 0.0);
    }   
    glTranslatef(0.0f, 35.0f, 0.0f);
    glRotatef( angle, 0.0, 1.0, 0.0 );
    glutSolidSphere(0.8f, 16, 16);
    glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
  glPopMatrix();

  //draw light1
  glPushMatrix();
    if (lightOn2)
    {
       glMaterialfv(GL_FRONT, GL_EMISSION, gWhiteEmission);  //set material emission component
       glColorMaterial (GL_FRONT, GL_EMISSION);
       glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
       glColor3f(1.0, 1.0, 1.0);
    }
    else
    {
       glMaterialfv(GL_FRONT, GL_EMISSION, gBlackEmission);
       glColor3f(0.0, 0.0, 0.0 );
    }
    glTranslatef(-47, 40, 0);
    glutSolidSphere(2.0f, 16, 16);
    glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
  glPopMatrix();  
  
  // draw light 2
 glPushMatrix();
    if (lightOn3)
    {
       glMaterialfv(GL_FRONT, GL_EMISSION, gWhiteEmission);  //set material emission component
       glColorMaterial (GL_FRONT, GL_EMISSION);
       glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
       glColor3f(1.0, 1.0, 1.0);
    }
    else
    {
       glMaterialfv(GL_FRONT, GL_EMISSION, gBlackEmission);
       glColor3f(0.0, 0.0, 0.0 );
    }
    glTranslatef(20, 40, -20);
    glutSolidSphere(2.0f, 16, 16);
    glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
  glPopMatrix();  
  
  // draw light 3
  glPushMatrix();
    if (lightOn4)
    {
       glMaterialfv(GL_FRONT, GL_EMISSION, gWhiteEmission);  //set material emission component
       glColorMaterial (GL_FRONT, GL_EMISSION);
       glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
       glColor3f(1.0, 1.0, 1.0);
    }
    else
    {
       glMaterialfv(GL_FRONT, GL_EMISSION, gBlackEmission);
       glColor3f(0.0, 0.0, 0.0 );
    }
    glTranslatef(37, 40, 0);
    glutSolidSphere(2.0f, 16, 16);
    glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
  glPopMatrix();    
  
  // draw light 4
  glPushMatrix();
      if (lightOn5)
      {
        glMaterialfv(GL_FRONT, GL_EMISSION, gWhiteEmission);  //set material emission component
        glColorMaterial (GL_FRONT, GL_EMISSION);
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glColor3f(1.0, 1.0, 1.0);
     } 
     else
     {
         glMaterialfv(GL_FRONT, GL_EMISSION, gBlackEmission);
         glColor3f(0.0, 0.0, 0.0 );
     }
    glTranslatef(-25, 40, 37);
    glutSolidSphere(2.0f, 16, 16);
    glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
  glPopMatrix(); 
 
  // draw left wall
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseBrownWall);        //set material diffuse component
  glColor3f(0.8f, 0.1f, 0.0f );
  glBindTexture(GL_TEXTURE_2D, textures[1]);
  glBegin(GL_QUADS);
    glNormal3f(1.0f , 0.0f, 0.0f);
    for ( int i = 0 ; i < 8 ; i ++ )
    {
      for ( int j = 0 ; j < 16 ; j++ )
      {
          glTexCoord2f(1.0f, 0.0f); glVertex3f(-50.0, 0 + 5 * i  , -40.0 + 5 * j ) ;
          glTexCoord2f(1.0f, 1.0f); glVertex3f(-50.0, 0 + 5 * ( i + 1 ) , -40 + 5 * j ) ;
          glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0, 0 + 5 * ( i + 1 ) , -40 + 5 * (j + 1) );
          glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0, 0 + 5 * i  , -40.0 + 5 * ( j + 1 ) ) ;    
      }
    }  
  glEnd();
 
  //draw right wall
  glBegin(GL_QUADS);
    glNormal3f(-1.0f , 0.0f, 0.0f);
    for ( int i = 0 ; i < 8 ; i ++ )
    {
      for ( int j = 0 ; j < 16 ; j++ )
      {
          glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0, 0 + 5 * i  , -40.0 + 5 * j ) ;
          glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0, 0 + 5 * ( i + 1 ) , -40 + 5 * j ) ;
          glTexCoord2f(0.0f, 1.0f); glVertex3f(50.0, 0 + 5 * ( i + 1 ) , -40 + 5 * (j + 1)  );
          glTexCoord2f(0.0f, 0.0f); glVertex3f(50.0, 0 + 5 * i  , -40.0 + 5 * ( j + 1 ) ) ;
          
      }
    }  
  glEnd();
  
  //draw back wall
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    for ( int i = 0 ; i < 8 ; i ++ )
    {
      for ( int j = 0 ; j < 20 ; j++ )
      {
          glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0 + 5 * j, 0 + 5 * i  , -40.0 ) ;
          glTexCoord2f(0.0f, 1.0f); glVertex3f(-50 + 5 * j, 0 + 5 * ( i + 1 ) , -40.0 ) ;
          glTexCoord2f(1.0f, 1.0f); glVertex3f( -50 + 5 * (j + 1), 0 + 5 * ( i + 1 ) , -40.0  );
          glTexCoord2f(1.0f, 0.0f); glVertex3f(-50.0 + 5 * ( j + 1 ), 0 + 5 * i  , -40.0 ) ; 
      }
    }  
    glEnd();
  
  // draw front wall
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 0.0f, -1.0f);
  for ( int i = 0 ; i < 8 ; i ++ )
  {
      for ( int j = 0 ; j < 20 ; j++ )
      {
          glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0 + 5 * j, 0 + 5 * i  , 40.0 ) ;
          glTexCoord2f(0.0f, 1.0f); glVertex3f(-50 + 5 * j, 0 + 5 * ( i + 1 ) , 40.0 ) ;
          glTexCoord2f(1.0f, 1.0f); glVertex3f( -50 + 5 * (j + 1), 0 + 5 * ( i + 1 ) , 40.0  );
          glTexCoord2f(1.0f, 0.0f); glVertex3f(-50.0 + 5 * ( j + 1 ), 0 + 5 * i  , 40.0 ) ; 
      }
    }  
  glEnd();
  
  //draw ceiling
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseGray);
  glColor3f(0.9f, 0.9f, 0.9f);
  glBindTexture(GL_TEXTURE_2D, textures[2]);
  glBegin (GL_QUADS);
  glNormal3f(0.0f, -1.0f, 0.0f);
    for ( int i = 0 ; i < 16 ; i ++ )
    {
      for ( int j = 0 ; j < 20 ; j++ )
      {
          glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0 + 5 * j , 40.0 , -40.0 + 5 * i ) ;
          glTexCoord2f(1.0f, 1.0f); glVertex3f(-50.0 + 5 * ( j + 1 ) , 40.0 , -40 + 5 * i ) ;
          glTexCoord2f(1.0f, 0.0f); glVertex3f(-50.0 + 5 * ( j + 1 ) , 40.0 , -40 + 5 * (i + 1)  );
          glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0 + 5 * j , 40.0 , -40.0 + 5 * ( i + 1 ) ) ;     
      }
  }  
  glEnd();
  
  // for motion blurring of fan
  GLint current_pass;	
  
  // the square piece in the middle of the fan
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseGray);
  glColor3f(0.9f, 0.9f, 0.9f);
  glBindTexture(GL_TEXTURE_2D, textures[5]);
  glPushMatrix();
    glRotatef( angle, 0.0, 1.0, 0.0 );
    glTranslatef ( 0.0f , 35.0f, 0.0f );
    glScalef( 2.0f, 0.1f, 2.0f);
    drawCube();
  glPopMatrix(); 
  
  // motion blur of the fan
  if ( motionBlurring) 
  {
       for(current_pass = 0; current_pass < gTotalPasses; current_pass++)
      {
            glPushMatrix();
                  glRotatef( angle , 0.0, 1.0, 0.0 );
                  glTranslatef( 0.0, 0.0, current_pass * -0.1 );
                  // draw fan blade 1
                  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseGray);
                  glColor3f(0.9f, 0.9f, 0.9f);
                  glBindTexture(GL_TEXTURE_2D, textures[5]);
                  glPushMatrix();
                    glRotatef( angle, 0.0, 1.0, 0.0 );
                    glTranslatef ( -5.0f , 35.0f, 0.0f );
                    glScalef( 8.0f, 0.1f, 2.0f);
                    drawCube();
                  glPopMatrix();
            glPopMatrix();
            if(current_pass < 1)
              glAccum(GL_LOAD, 0.5);	// first time load from draw buffer into accumulation buffer
            else
              glAccum(GL_ACCUM, (0.5 * (1.0 / (float)gTotalPasses)));	// accumulate in accumulation buffer
      }
      glAccum(GL_RETURN, 1.0);  
      
      for(current_pass = 0; current_pass < gTotalPasses; current_pass++)
      {         
            glPushMatrix();
                  glRotatef( angle, 0.0, 1.0, 0.0 );
                  glTranslatef( 0.0, 0.0, current_pass * 0.1 );
                  // draw fan blade 2
                  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseGray);
                  glColor3f(0.9f, 0.9f, 0.9f);
                  glBindTexture(GL_TEXTURE_2D, textures[5]);
                  glPushMatrix();
                    glRotatef( angle, 0.0, 1.0, 0.0 );
                    glTranslatef ( 5.0f , 35.0f, 0.0f );
                    glScalef( 8.0f, 0.1f, 2.0f);
                    drawCube();
                  glPopMatrix();
            glPopMatrix();
            if(current_pass < 1)
              glAccum(GL_LOAD, 0.5);	// first time load from draw buffer into accumulation buffer
            else
              glAccum(GL_ACCUM, (0.5 * (1.0 / (float)gTotalPasses)));	// accumulate in accumulation buffer
      }
      glAccum(GL_RETURN, 1.0);  
      for(current_pass = 0; current_pass < gTotalPasses; current_pass++)
      {
 
            glPushMatrix();
                  glRotatef( angle, 0.0, 1.0, 0.0 );
                  glTranslatef( current_pass * -0.1, 0.0, 0.0  );
                  // fan  blade 3
                  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseGray);
                  glColor3f(0.9f, 0.9f, 0.9f);
                  glBindTexture(GL_TEXTURE_2D, textures[5]);
                  glPushMatrix();
                    glRotatef( angle, 0.0, 1.0, 0.0 );
                    glTranslatef ( 0.0f , 35.0f, 5.0f );
                    glScalef( 2.0f, 0.1f, 8.0f);
                    drawCube();
                  glPopMatrix();
            glPopMatrix();
            if(current_pass < 1)
              glAccum(GL_LOAD, 0.5);	// first time load from draw buffer into accumulation buffer
            else
              glAccum(GL_ACCUM, (0.5 * (1.0 / (float)gTotalPasses)));	// accumulate in accumulation buffer
      }       
      glAccum(GL_RETURN, 1.0);   
      for(current_pass = 0; current_pass < gTotalPasses; current_pass++)
      {
            glPushMatrix();
                  glRotatef( angle, 0.0, 1.0, 0.0 );
                  glTranslatef( current_pass * 0.1, 0.0 ,0.0 );
                  // fan  blade 4
                  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseGray);
                  glColor3f(0.9f, 0.9f, 0.9f);
                  glBindTexture(GL_TEXTURE_2D, textures[5]);
                  glPushMatrix();
                    glRotatef( angle, 0.0, 1.0, 0.0 );
                    glTranslatef ( 0.0f , 35.0f, -5.0f );
                    glScalef( 2.0f, 0.1f, 8.0f);
                    drawCube();
                  glPopMatrix();
            glPopMatrix();      
            if(current_pass < 1)
              glAccum(GL_LOAD, 0.5);	// first time load from draw buffer into accumulation buffer
            else
              glAccum(GL_ACCUM, (0.5 * (1.0 / (float)gTotalPasses)));	// accumulate in accumulation buffer
        }
        glAccum(GL_RETURN, 1.0); // transfer accumulation buffer contents back to draw buffer

        glDisable(GL_BLEND); 
  }
  else
  {
      // draw fan blade 1
      glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseGray);
      glColor3f(0.9f, 0.9f, 0.9f);
      glBindTexture(GL_TEXTURE_2D, textures[5]);
      glPushMatrix();
        glRotatef( angle, 0.0, 1.0, 0.0 );
        glTranslatef ( -5.0 , 35.0f, 0.0f );
        glScalef( 8.0f, 0.1f, 2.0f);
        drawCube();
      glPopMatrix();
      
      // draw fan blade 2
      glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseGray);
      glColor3f(0.9f, 0.9f, 0.9f);
      glBindTexture(GL_TEXTURE_2D, textures[5]);
      glPushMatrix();
        glRotatef( angle, 0.0, 1.0, 0.0 );
        glTranslatef ( 5.0f , 35.0f, 0.0f );
        glScalef( 8.0f, 0.1f, 2.0f);
        drawCube();
      glPopMatrix();
      
      // fan  blade 3
      glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseGray);
      glColor3f(0.9f, 0.9f, 0.9f);
      glBindTexture(GL_TEXTURE_2D, textures[5]);
      glPushMatrix();
        glRotatef( angle, 0.0, 1.0, 0.0 );
        glTranslatef ( 0.0f , 35.0f, 5.0f );
        glScalef( 2.0f, 0.1f, 8.0f);
        drawCube();
      glPopMatrix();
      
      // fan  blade 4
      glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseGray);
      glColor3f(0.9f, 0.9f, 0.9f);
      glBindTexture(GL_TEXTURE_2D, textures[5]);
      glPushMatrix();
        glRotatef( angle, 0.0, 1.0, 0.0 );
        glTranslatef ( 0.0f , 35.0f, -5.0f );
        glScalef( 2.0f, 0.1f, 8.0f);
        drawCube();
      glPopMatrix();
  }
  // draw fan stem
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseBlack);
  glColor3f(0.0f, 0.0f, 0.0f);
  quad = gluNewQuadric();
  glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textures[9]);
    gluQuadricTexture(quad,1); //http://www.opengl.org/sdk/docs/man2/xhtml/gluQuadricTexture.xml
    glTranslatef(0.0f , 35.0f, 0.0f);
    glRotatef( angle, 0.0, 1.0, 0.0 );
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad,0.8,0.8,5.0,10,10);
  glPopMatrix();

  
  float moveTableX = 20;
  float moveTableZ = -20;
  
  // draw Table
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseDarkBrown);
  glColor3f(0.65f, 0.18f, 0.18f);
  glBindTexture(GL_TEXTURE_2D, textures[3]);
  glPushMatrix();
    glTranslatef( 0.0f + moveTableX , 8.0f , 0.0f + moveTableZ );
    glScalef(15.0f, 1.5f, 15.0f);
    drawCube();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef( -6.5f + moveTableX , 4.0f, -6.5f + moveTableZ);
    glScalef(1.0f, 8.0f, 1.0f);
    drawCube();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef( -6.5f + moveTableX , 4.0f, 6.5f + moveTableZ );
    glScalef(1.0f, 8.0f, 1.0f);
    drawCube();
  glPopMatrix();                 

  glPushMatrix();
    glTranslatef( 6.5f + moveTableX, 4.0f, -6.5f + moveTableZ );
    glScalef(1.0f, 8.0f, 1.0f);
    drawCube();
  glPopMatrix();  
  
  glPushMatrix();
    glTranslatef( 6.5f + moveTableX, 4.0f, 6.5f + moveTableZ);
    glScalef(1.0f, 8.0f, 1.0f);
    drawCube();
  glPopMatrix();    

  //draw left chair
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseLightBrown);
  glColor3f(0.80f, 0.52f, 0.25f);
  glBindTexture(GL_TEXTURE_2D, textures[4]);
  glPushMatrix();
    glTranslatef( -9.0f + moveTableX, 5.0f, 0.0f + moveTableZ );
    glScalef(6.0f, 1.0f, 6.0f);
    drawCube();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef( -11.5f + moveTableX, 2.5f, -2.5f + moveTableZ );
    glScalef(1.0f, 5.0f, 1.0f);
    drawCube();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef( -11.5f + moveTableX, 2.5f, 2.5f + moveTableZ);
    glScalef(1.0f, 5.0f, 1.0f);
    drawCube();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef( -6.5f + moveTableX , 2.5f, -2.5f + moveTableZ);
    glScalef(1.0f, 5.0f, 1.0f);
    drawCube();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef( -6.5f + moveTableX, 2.5f, 2.5f + moveTableZ);
    glScalef(1.0f, 5.0f, 1.0f);
    drawCube();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef( -11.5f + moveTableX , 8.0f, 0.0f + moveTableZ);
    glScalef( 1.0f, 8.0f, 6.0f);
    drawCube();
  glPopMatrix();

  //draw Right chair
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseLightBrown);
  glColor3f(0.80f, 0.52f, 0.25f);
  glBindTexture(GL_TEXTURE_2D, textures[4]);
  glPushMatrix();
    glTranslatef( 9.0f + moveTableX, 5.0f, 0.0f + moveTableZ);
    glScalef(6.0f, 1.0f, 6.0f);
    drawCube();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef( 11.5f + moveTableX, 2.5f, -2.5f + moveTableZ);
    glScalef(1.0f, 5.0f, 1.0f);
    drawCube();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef( 11.5f + moveTableX, 2.5f, 2.5f + moveTableZ);
    glScalef(1.0f, 5.0f, 1.0f);
    drawCube();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef( 6.5f + moveTableX, 2.5f, -2.5f + moveTableZ );
    glScalef(1.0f, 5.0f, 1.0f);
    drawCube();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef( 6.5f + moveTableX, 2.5f, 2.5f + moveTableZ);
    glScalef(1.0f, 5.0f, 1.0f);
    drawCube();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef( 11.5f + moveTableX, 8.0f, 0.0f + moveTableZ);
    glScalef( 1.0f, 8.0f, 6.0f);
    drawCube();
  glPopMatrix();
    

  // draw cabinets on left side
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseBlack);
  glColor3f(0.0f, 0.0f, 0.0f);
  glBindTexture(GL_TEXTURE_2D, textures[9]);
  glPushMatrix();
    glTranslatef( -45.0f , 15.0f, 0.0f );
    glScalef(10.0f, 2.0f, 80.0f);
    drawCube();
  glPopMatrix();    
  
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseGray);
  glColor3f(0.9f, 0.9f, 0.9f);
  glBindTexture(GL_TEXTURE_2D, textures[10]);
  glPushMatrix();
    glTranslatef( -45.0f, 7.0f, 0.0f );
    glScalef(10.0f, 14.0f, 20.0f);
    drawCube();
  glPopMatrix();  

  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseGray);
  glColor3f(0.9f, 0.9f, 0.9f); 
  glBindTexture(GL_TEXTURE_2D, textures[10]);
  glPushMatrix();
    glTranslatef( -45.0f, 7.0f, 30.0f );
    glScalef(10.0f, 14.0f, 20.0f);
    drawCube();
  glPopMatrix(); 

  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseGray);
  glColor3f(0.9f, 0.9f, 0.9f); 
  glBindTexture(GL_TEXTURE_2D, textures[10]);
  glPushMatrix();
    glTranslatef( -45.0f, 7.0f, -30.0f );
    glScalef(10.0f, 14.0f, 20.0f);
    drawCube();
  glPopMatrix();     
  
  // draw portrait 1   ( left side ) 
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseLightBlue);
  glColor3f(0.4f, 0.4f, 0.5f);
  glBindTexture(GL_TEXTURE_2D, textures[11]);
  glPushMatrix();
    glTranslatef( -49.5f, 28.0f, 0.0f );
    glScalef(1.0f, 20.0f, 20.0f);
    drawCube();
  glPopMatrix();   
    
  // draw picture 1
  glBindTexture(GL_TEXTURE_2D, textures[12]);
  glBegin(GL_QUADS);
    glNormal3f(1.0f , 0.0f, 0.0f);
          glTexCoord2f(0.0f, 0.0f); glVertex3f(-48.9, 20  , 9 ) ;
          glTexCoord2f(1.0f, 0.0f); glVertex3f(-48.9, 20 , -9 ) ;
          glTexCoord2f(1.0f, 1.0f); glVertex3f(-48.9, 35 , -9  );
          glTexCoord2f(0.0f, 1.0f); glVertex3f(-48.9, 35  , 9 ) ;  
  glEnd();
  
  // draw portrait 2  ( front right )
  glBindTexture(GL_TEXTURE_2D, textures[11]);
  glPushMatrix();
    glTranslatef( 25.0f, 25.0f, -39.5f );
    glScalef(22.0f, 22.0f, 1.0f);
    drawCube();
  glPopMatrix();    

  // draw picture 2
  glBindTexture(GL_TEXTURE_2D, textures[13]);
  glBegin(GL_QUADS);
    glNormal3f(1.0f , 0.0f, 0.0f);
          glTexCoord2f(0.0f, 0.0f); glVertex3f( 15, 15 , -38.9 ) ;
          glTexCoord2f(1.0f, 0.0f); glVertex3f( 35, 15 , -38.9 ) ;
          glTexCoord2f(1.0f, 1.0f); glVertex3f( 35, 35 , -38.9  );
          glTexCoord2f(0.0f, 1.0f); glVertex3f( 15, 35 , -38.9 ) ;  
  glEnd();
  
  // draw portrait 3 ( front left )
  glBindTexture(GL_TEXTURE_2D, textures[11]);
  glPushMatrix();
    glTranslatef( -20.0f, 25.0f, -39.5f );
    glScalef(22.0f, 22.0f, 1.0f);
    drawCube();
  glPopMatrix();    
  
  // draw picture 3 ( screenshot will be place here )
  glBindTexture(GL_TEXTURE_2D, textures[15]);
  glBegin(GL_QUADS);
  glNormal3f(1.0f , 0.0f, 0.0f);
         glTexCoord2f(0.0f, 0.0f); glVertex3f( -30, 15 , -38.9 ) ;
         glTexCoord2f(1.0f, 0.0f); glVertex3f( -10, 15 , -38.9 ) ;
         glTexCoord2f(1.0f, 1.0f); glVertex3f( -10, 35 , -38.9  );
         glTexCoord2f(0.0f, 1.0f); glVertex3f( -30, 35 , -38.9 ) ;  
  glEnd(); 

  // draw portrait 4 ( back left )
  glBindTexture(GL_TEXTURE_2D, textures[11]);
  glPushMatrix();
    glTranslatef( -20.0f, 25.0f, 39.5f );
    glScalef(22.0f, 22.0f, 1.0f);
    drawCube();
  glPopMatrix();  
  // draw picture 4
  glBindTexture(GL_TEXTURE_2D, textures[14]);
  glBegin(GL_QUADS);
    glNormal3f(1.0f , 0.0f, 0.0f);
          glTexCoord2f(0.0f, 0.0f); glVertex3f( -10, 15 , 38.9 ) ;
          glTexCoord2f(1.0f, 0.0f); glVertex3f( -30, 15 , 38.9 ) ;
          glTexCoord2f(1.0f, 1.0f); glVertex3f( -30, 35 , 38.9  );
          glTexCoord2f(0.0f, 1.0f); glVertex3f( -10, 35 , 38.9 ) ;  
  glEnd();  
  
  // the two transparent display cabinet
  glEnable (GL_BLEND); 
  glBlendFunc (GL_ONE, GL_ONE); 
  glBindTexture(GL_TEXTURE_2D, textures[5]);
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseWhiteTransparent);
  glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
  glPushMatrix();
    glTranslatef( -45.0f, 7.0f, -15.0f );
    glScalef(10.0f, 14.0f, 10.0f);
    drawCube();
  glPopMatrix();  

  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseWhiteTransparent);
  glColor4f(1.0f, 1.0f, 1.0f, 0.3f);  
  glBindTexture(GL_TEXTURE_2D, textures[5]);
  glPushMatrix();
    glTranslatef( -45.0f, 7.0f, 15.0f );
    glScalef(10.0f, 14.0f, 10.0f);
    drawCube();
  glPopMatrix();  
  glDisable (GL_BLEND);
  
  //draw steps
  float spacing = 5.0;
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseDarkBrown);
  glColor3f(0.65f, 0.18f, 0.18f);
  glBindTexture(GL_TEXTURE_2D, textures[3]);
  for ( int i = 0 ; i < 2 ; i ++ )
  {
      glPushMatrix();
        glTranslatef( 35.0f - ((spacing + 20) * i) , 15.0f + (spacing * i), 37.5f );
        glScalef(15.0f, 2.5f, 5.0f);
        drawCube();
      glPopMatrix();  
  }

  // draw table2
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseDarkBrown);
  glColor3f(0.65f, 0.18f, 0.18f);
  glBindTexture(GL_TEXTURE_2D, textures[3]);
  glPushMatrix();
    glTranslatef( 45.0f, 10.0f, 15.0f );
    glScalef(10.0f, 2.5f, 30.0f);
    drawCube();
  glPopMatrix();  

  // draw object on table 2
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial2);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial2);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseCyan); 
  glColor3f(0.0f, 0.8f, 0.8f );
  glBindTexture(GL_TEXTURE_2D, textures[5]);
  //draw teapot
  glPushMatrix();
    glTranslatef(45, 12.5, 15);
    glRotatef(angle + 20, 0.0f, 1.0f, 0.0f);
    glScalef( 1.0f, 1.0f, 1.0f);
    glutSolidTeapot(1.5f);
  glPopMatrix();  
  
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial3);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial3);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseBlack); 
  glColor3f(0.0f, 0.0f, 0.0f );
  glBindTexture(GL_TEXTURE_2D, textures[9]);
  //draw teapot
  glPushMatrix();
    glTranslatef(45, 12.5, 5);
    glRotatef(angle + 50, 0.0f, 1.0f, 0.0f);
    glScalef( 1.0f, 1.0f, 1.0f);
    glutSolidTeapot(1.5f);
  glPopMatrix(); 

  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial4);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial4);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightBlue); 
  glColor3f(0.4f, 0.4f, 0.5f );
  glBindTexture(GL_TEXTURE_2D, textures[10]);
  //draw teapot
  glPushMatrix();
    glTranslatef(45, 12.5, 25);
    glRotatef(angle + 80, 0.0f, 1.0f, 0.0f);
    glScalef( 1.0f, 1.0f, 1.0f);
    glutSolidTeapot(1.5f);
  glPopMatrix(); 
  

  // draw table objects  
  //draw cups x 2
  glEnable (GL_BLEND);
  glBlendFunc (GL_ONE, GL_ONE); 
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial5);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial5);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseWhiteTransparent); 
  glColor4f(1.0f, 1.0f, 1.0f, 0.3f );
  glBindTexture(GL_TEXTURE_2D, textures[6]);
  quad = gluNewQuadric();
  glPushMatrix();
    gluQuadricTexture(quad,1); //http://www.opengl.org/sdk/docs/man2/xhtml/gluQuadricTexture.xml
    glTranslatef(-3.5f + moveTableX, 8.5f, 4.0f + moveTableZ);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad,0.8,0.8,2.5,10,10);
    glPopMatrix();
  
  quad = gluNewQuadric();
  glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textures[6]);
    gluQuadricTexture(quad,1); //http://www.opengl.org/sdk/docs/man2/xhtml/gluQuadricTexture.xml
    glTranslatef(3.5f + moveTableX, 8.5f, -4.0f + moveTableZ);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad,0.8,0.8,2.5,10,10);
  glPopMatrix();
  glDisable(GL_BLEND);

  //draw ice cream cone
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial6);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial6);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseYellow); 
  glColor3f(1.0f, 1.0f, 0.0f );  
  quad = gluNewQuadric();
  glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textures[7]);
    gluQuadricTexture(quad,1); //http://www.opengl.org/sdk/docs/man2/xhtml/gluQuadricTexture.xml
    glTranslatef(3.5f + moveTableX, 8.8f, 2.0f + moveTableZ);
    glRotatef(-70, 1, 0, 0);
    gluCylinder(quad,0,0.5,2.0,10,10);
  glPopMatrix();

  // draw chocolate ice cream
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial6);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial6);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseDarkBrown); 
  glColor3f(0.65f, 0.18f, 0.18f );
  quad = gluNewQuadric();
  glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textures[8]);
    gluQuadricTexture(quad,1); //http://www.opengl.org/sdk/docs/man2/xhtml/gluQuadricTexture.xml
    glTranslatef(3.5f + moveTableX, 11.0f, 2.7f + + moveTableZ);
    glScalef(0.7f, 0.7f, 0.7f);
    gluSphere(quad,1,10,10);
  glPopMatrix();
  
  //draw teapot
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial7);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial7);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseBrightOrange); 
  glColor3f(1.0f, 0.6f, 0.5f );
  glBindTexture(GL_TEXTURE_2D, textures[5]);
  glPushMatrix();
    glTranslatef(0.0f + moveTableX, 9.8f, 1.0f + moveTableZ);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glScalef( 0.8f, 0.8f, 0.8f);
    glutSolidTeapot(1.5f);
  glPopMatrix();
  
  // draw donut x 2
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial8);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial8);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightBrown); 
  glColor3f(0.4f, 0.4f, 0.5f ); 
  glBindTexture(GL_TEXTURE_2D, textures[8]);
  glPushMatrix();
    glTranslatef(-4.0f + moveTableX, 9.0f, -2.5f + moveTableZ);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glScalef( 0.3f, 0.3f, 0.3f);
    glutSolidTorus(1.2f, 2.0f, 8, 16);
  glPopMatrix();
 
  glPushMatrix();
    glTranslatef(-4.0f + moveTableX, 9.5f, -1.5f + + moveTableZ);
    glRotatef(-40.0f, 1.0f, 0.0f, 0.0f);
    glScalef( 0.3f, 0.3f, 0.3f);
    glutSolidTorus(1.2f, 2.0f, 8, 16);
  glPopMatrix();
  
  glBindTexture(GL_TEXTURE_2D, textures[6]);
  
  //draw cone  on left table
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial3);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial3);      //set material specular component 
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffusePink); 
  glColor3f(1.0f, 0.6f, 1.0f);
  glPushMatrix();
    glTranslatef(-45.0f, 15.0f, 25.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glScalef( 2.0f, 2.0f, 2.0f);
    glutSolidCone(2.0f, 4.0f, 16, 8);
  glPopMatrix();
  
  //draw sphere
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial2);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial2);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseCyan); 
  glColor3f(0.0f, 0.8f, 0.8f );
  glPushMatrix();
    glTranslatef(-43.0f, 21.5f, -25.0f);
    glutSolidSphere(3.0f, 16, 16); 
  glPopMatrix();
  
  //draw torus
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial4);        //set material ambient component
  glMaterialfv(GL_FRONT, GL_SPECULAR, gSpecularMaterial4);      //set material specular component
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseOrange);
  glPushMatrix();
    glTranslatef(-43.0f, 22.0f, -25.5f);
    glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);
    glScalef( 2.0f, 2.0f, 2.0f);
    glutSolidTorus(0.5f, 3.0f, 8, 16);
  glPopMatrix();
  
  gFrameCount ++;
  helpDisplay();
  glBindTexture(GL_TEXTURE_2D, 0);
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
  else if ( gCameraPitch < -90.0 )
      gCameraPitch = -90.0;

// keep first

  gCameraPosition[0] += sin(DEG2RAD(gCameraYaw))*gMoveForward;    //calculate movement along x axis
  gCameraPosition[2] += -cos(DEG2RAD(gCameraYaw))*gMoveForward;   //calculate movement along z axis
  gCameraPosition[1] +=   -sin(DEG2RAD(gCameraPitch))*gMoveForward ;
  gMoveForward = 0;     //reset forward/backward movement

  gCameraLookAt[0] = gCameraPosition[0] + sin(DEG2RAD(gCameraYaw));   //rotate camera lookat direction
  gCameraLookAt[2] = gCameraPosition[2] -cos(DEG2RAD(gCameraYaw));
  gCameraLookAt[1] = gCameraPosition[1] + -sin(DEG2RAD(gCameraPitch)) ;
  
  cout << gCameraPosition[1] << endl;
  cout << gCameraLookAt[1] << endl;


  gCameraPosition[1]+= gMoveUpward;
  gCameraLookAt[1] += gMoveUpward;
  gMoveUpward = 0;

  gCameraPosition[0] += cos(DEG2RAD(gCameraYaw))*gMoveRightward;    //calculate movement along x axis
  gCameraPosition[2] += sin(DEG2RAD(gCameraYaw))*gMoveRightward;   //calculate movement along z axis
  gCameraPosition[1] +=   -sin(DEG2RAD(gCameraRoll))*gMoveRightward ;
  gMoveRightward = 0;     //reset leftward/rightward movement

  gCameraLookAt[0] = gCameraPosition[0] +cos(DEG2RAD(gCameraYaw)) ;  //rotate camera lookat direction
  gCameraLookAt[2] = gCameraPosition[2]+ sin(DEG2RAD(gCameraYaw));
  gCameraLookAt[1] = gCameraPosition[1] + -sin(DEG2RAD(gCameraRoll)) ;

  glLoadIdentity();     //load modelview matrix with identity matrix
  gluLookAt(gCameraPosition[0], gCameraPosition[1], gCameraPosition[2],   //set position
            gCameraLookAt[0], gCameraLookAt[1], gCameraLookAt[2],         //set where eye/camera is looking at
	        gCameraUp[0], gCameraUp[1], gCameraUp[2]);                    //set 'up' vector
         
  glutPostRedisplay();  //refresh display
}

void resetCamera ()
{
// reset camera value
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

//called when ASCII key pressed
void myKeypress(unsigned char key, int x, int y)
{
  fstream afile ; 
  fstream outfile ;  
     
  changed = true;
  switch(key)
  {
    //if ESC pressed, quit program
    case '\e': exit(1);     //quit
		       break;
   case '1' :                          // toggle light 1 on/off
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
    
    case '2' :                         // toggle light 2 on/off
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
    
    case '3' :                          // toggle light 3 on/off
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
    case '4' :                         // toggle light 4 on/off
              if ( lightOn4 )
              {
                   glDisable(GL_LIGHT3);
                   lightOn4 = false;
              }
              else
              {
                  glEnable (GL_LIGHT3);
                  lightOn4 = true;
              }
              break;
    case '5' :                         // toggle light 5 on/off
              if ( lightOn5 )
              {
                   glDisable(GL_LIGHT4);
                   lightOn5 = false;
              }
              else
              {
                  glEnable (GL_LIGHT4);
                  lightOn5 = true;
              }
              break;
    
    case 'b' :                          // toggle through the 7 state
                if ( bCounter == 1 )    // wireframe mode with white background
                {
                     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
                     bCounter = 2 ;
                }
                else if ( bCounter == 2 )             // wireframe mode with white background
                {
                     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
                     bCounter = 3;
                }
                else if ( bCounter == 3 )          // solid mode with primitives coloured w/o texture or lighting
                {
                     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                     glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
                     glEnable(GL_COLOR_MATERIAL);        //enable colour tracking                     
                     glDisable(GL_LIGHTING);    //enable lighting
                     glShadeModel(GL_FLAT);
                     glDisable(GL_TEXTURE_2D);	// enable 2D texturing
                     bCounter = 4 ;
                }
                else if ( bCounter == 4 )  // solid mode with primitives shaded using lighting     
                {
                     glEnable(GL_LIGHTING);
                     glDisable (GL_COLOR_MATERIAL);
                     glShadeModel(GL_SMOOTH);
                     glDisable(GL_TEXTURE_2D);
                     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                     bCounter = 5 ;
                }
                else if ( bCounter == 5 )  // solid mode with primitives textured w/o lighting
                {
                     glShadeModel(GL_FLAT);
                     glEnable(GL_TEXTURE_2D);
                     glDisable(GL_LIGHTING);
                     glDisable(GL_COLOR_MATERIAL);
                     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                     bCounter = 6 ;
                }
                else if ( bCounter == 6) // solid mode with primitives shaded using lighting and textured
                {
                     glShadeModel(GL_SMOOTH);
                     glEnable(GL_TEXTURE_2D);
                     glEnable(GL_LIGHTING);
                     glDisable (GL_COLOR_MATERIAL);
                     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                     bCounter = 7 ;
                }
                else if ( bCounter == 7) // wireframe mode with black background
                {
                     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
                     bCounter = 1 ;
                }
                break;
    case 'i' :        // changes intensity of flash light
               if ( flashIntensity == 1 )
               {
                    flashIntensity = 2 ;
               }
               else if ( flashIntensity == 2 )
               {
                    flashIntensity = 3 ;
               }
               else if ( flashIntensity == 3 )
               {
                    flashIntensity = 1 ;
               }
               break;
    
    case 'c' : // changes colour of flash light
               if ( flashColour == 1 )
               {
                    flashColour = 2 ;
               }
               else if ( flashColour == 2 )
               {
                    flashColour = 3 ;
               }
               else if ( flashColour == 3 )
               {
                    flashColour = 4;
               }
               else if ( flashColour == 4 )
               {
                    flashColour = 1;
               }
               break;
    case 'f' :  // toggle flashlight on/off
               if ( flashOn )
               {
                    glDisable(GL_LIGHT5);
                    flashOn = false;
               }
               else
               {
                   glEnable(GL_LIGHT5);
                   flashOn = true;
               }
               break;
   
    case 'h' : // display help on/off
              if ( showHelp)
                 showHelp = false;
              else
                  showHelp = true;
              break;
    case 'm' :  // toggle motionBlurring on/off
               if (motionBlurring)
                  motionBlurring = false;
               else
                  motionBlurring = true;
               break;
    
    case 'n' : // toggle day and night mode
               if ( dayTime)
               {
                    glLightfv(GL_LIGHT0, GL_AMBIENT, gAmbientLight2);
                    glLightfv(GL_LIGHT1, GL_AMBIENT, gAmbientLight2);
                    glLightfv(GL_LIGHT2, GL_AMBIENT, gAmbientLight2);
                    glLightfv(GL_LIGHT3, GL_AMBIENT, gAmbientLight2);
                    glLightfv(GL_LIGHT4, GL_AMBIENT, gAmbientLight2);

                    dayTime = false;
               }
               else
               {
                   glLightfv(GL_LIGHT0, GL_AMBIENT, gAmbientLight);
                   glLightfv(GL_LIGHT1, GL_AMBIENT, gAmbientLight);
                   glLightfv(GL_LIGHT2, GL_AMBIENT, gAmbientLight);
                   glLightfv(GL_LIGHT3, GL_AMBIENT, gAmbientLight);
                   glLightfv(GL_LIGHT4, GL_AMBIENT, gAmbientLight);
                   
                   dayTime = true;
               }
               break;
    case 'p' :  // take a screenshot
               readFile(afile,"pictureNumber.txt");
               qty ++ ; // then save
               sprintf(fileName_str, "%d.bmp", qty);
               //SaveAsBMP("testing.bmp");
               SaveAsBMP(fileName_str);
               writeFile(outfile, "pictureNumber.txt" );
               readFile(afile, "pictureNumber.txt" );            
               loadTexture(textures[15], fileName_str);
               picTaken = true;
               break;
    case 'x' :  // toggle anti aliasing on/off
               if ( aa )
               {
                   glDisable( GL_LINE_SMOOTH );
                   glDisable( GL_POLYGON_SMOOTH );
                   glDisable( GL_BLEND);
                   aa = false;
                   cout << "AA is switched off  " << endl;
               }
               else
               {
                   aa = true;
                   cout << "AA is switched on " << endl;
               }
               break;    
    case 'w' : // pitch up
               gCameraPitch += gRotationSensitivity;
               break;
    case 's' : // pitch down
               gCameraPitch -= gRotationSensitivity;
               break;
    case 'q' : // roll left
               gCameraRoll -= gRotationSensitivity;
               break;
    case 'e' : // roll right
               gCameraRoll += gRotationSensitivity;
               break;
    case 'a' : // yaw left
               gCameraYaw -= gRotationSensitivity; 
               break;
    case 'd' : // yaw right
               gCameraYaw += gRotationSensitivity; 
               break;
    
    case 'r' :  // reset camera
               resetCamera();
               break;
    
    default: break;
  };
  
  updateCamera();
  glutPostRedisplay();  //refresh display
}

//called when non-ASCII key pressed
void mySpecialKeys(int key, int x, int y)
{
  changed = true;
  switch(key)
  {
    //if home pressed
    case GLUT_KEY_PAGE_UP:  // move vertically up
                               gCameraPosition[1] += gMovementSensitivity;       //increment camera height
                               gCameraLookAt[1] += gMovementSensitivity;
		                       break;
    //if end pressed
    case GLUT_KEY_PAGE_DOWN:  // move vertically down
                               gCameraPosition[1] -= gMovementSensitivity;       //decrement camera height
                               gCameraLookAt[1] -= gMovementSensitivity;
		                       break;
    //if arrow up pressed      // move forward
    case GLUT_KEY_UP:   gMoveForward += gMovementSensitivity;             //increment forward movement
		                break;
    //if arrow down pressed // move backward
    case GLUT_KEY_DOWN: gMoveForward -= gMovementSensitivity;             //increment backward movement
		                break;
    //if left pressed
    case GLUT_KEY_LEFT:  // strafe leftward
                         gMoveRightward -= gMovementSensitivity;
                        //gCameraYaw -= gRotationSensitivity;               //increment camera yaw
    	                break;
    //if right pressed
    case GLUT_KEY_RIGHT:  // strafe rightward
                        gMoveRightward += gMovementSensitivity; 
                        //gCameraYaw += gRotationSensitivity;              //decrement camera yaw
    	                break;
    default: break;
  };
  
  updateCamera();       //call function to update camera and refresh the scene
}

void myIdleFunc()
{
// rotate fan
  currentTime = glutGet(GLUT_ELAPSED_TIME);
  elapsedTime = currentTime - previousTime;        
     
  if ( (elapsedTime > ( 1/unitMovementPerSec * 1000)))
  {
       previousTime = currentTime ;
       
       angle ++ ;
       if ( angle >= 360 )
       {
            angle = 0;
       }
  }
  
  glutPostRedisplay(); 
}     


void SaveAsBMP(const char *fileName) // http://stackoverflow.com/questions/9657196/how-can-i-save-opengl-draw-with-opengl
{
// save screenshot
    FILE *file;
    unsigned long imageSize;
    GLbyte *data=NULL;
    GLint viewPort[4];
    GLenum lastBuffer;
    BITMAPFILEHEADER bmfh;
    BITMAPINFOHEADER bmih;
    bmfh.bfType='MB';
    bmfh.bfReserved1=0;
    bmfh.bfReserved2=0;
    bmfh.bfOffBits=54;
    glGetIntegerv(GL_VIEWPORT,viewPort);
    imageSize=((viewPort[2]+((4-(viewPort[2]%4))%4))*viewPort[3]*3)+2;
    bmfh.bfSize=imageSize+sizeof(bmfh)+sizeof(bmih);
    data=(GLbyte*)malloc(imageSize);
    glPixelStorei(GL_PACK_ALIGNMENT,4);
    glPixelStorei(GL_PACK_ROW_LENGTH,0);
    glPixelStorei(GL_PACK_SKIP_ROWS,0);
    glPixelStorei(GL_PACK_SKIP_PIXELS,0);
    glPixelStorei(GL_PACK_SWAP_BYTES,1);
    glGetIntegerv(GL_READ_BUFFER,(GLint*)&lastBuffer);
    glReadBuffer(GL_FRONT);
    glReadPixels(0,0,viewPort[2],viewPort[3],GL_RGB,GL_UNSIGNED_BYTE,data);
    data[imageSize-1]=0;
    data[imageSize-2]=0;
    glReadBuffer(lastBuffer);
    file=fopen(fileName,"wb");
    bmih.biSize=40;
    bmih.biWidth=viewPort[2];
    bmih.biHeight=viewPort[3];
    bmih.biPlanes=1;
    bmih.biBitCount=24;
    bmih.biCompression=0;
    bmih.biSizeImage=imageSize;
    bmih.biXPelsPerMeter=45089;
    bmih.biYPelsPerMeter=45089;
    bmih.biClrUsed=0;
    bmih.biClrImportant=0;
    fwrite(&bmfh,sizeof(bmfh),1,file);
    fwrite(&bmih,sizeof(bmih),1,file);
    fwrite(data,imageSize,1,file);
    free(data);
    fclose(file);
}

void readFile( fstream& afile , char* filename)
{
// read the textfile to determine the filename of picture to be saved
	afile.open ( filename , ios:: in) ;
	afile >> qty ;
	afile.close();
}	     

void writeFile( fstream& afile , char* filename)
{
// write to textfile the total number of picture taken
	afile.open ( filename , ios:: out) ;
	afile << qty ;
	afile.close();
}	

int main(int argc, char* argv[])
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_ACCUM);      //requests properties for the window (sets up the rendering context)
  glutInitWindowSize(800, 600);			//set window size in pixels
  glutInitWindowPosition(50, 50);       //set window position from top-left corner of display
  glutCreateWindow("Kitchen/ Dinning Area");		//set window title
  init();					            //call function to setup states 
  glutDisplayFunc(drawScene);			//register display callback function
  glutReshapeFunc(resizeWindow);		//register resize callback function
  glutKeyboardFunc(myKeypress);		    //register non-ASCII keypress callback function
  glutSpecialFunc(mySpecialKeys);		//register non-ASCII keypress callback function
  glutIdleFunc(myIdleFunc);
  glutMainLoop();                       //enter event loop
}
