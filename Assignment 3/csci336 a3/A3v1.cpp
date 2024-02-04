#include <gl/glut.h>    //include glut library (automatically includes gl and glu libraries)
#include <math.h>

#define MY_PI 		(3.14159265359)    //declare PI value
#define DEG2RAD(a) 	(MY_PI/180*(a))    //convert degrees into radians

//camera variables
GLfloat gCameraPosition[] = { 0.0f, 10.0f, 18.0f };
GLfloat gCameraLookAt[] = { 0.0f, 10.0f, 14.0f };
GLfloat gCameraUp[] = { 0.0f, 1.0f, 0.0f };

GLfloat gCameraYaw = 0.0f;     //camera yaw
GLfloat gMoveForward = 0.0f;   //camera forward/backward movement variable

GLfloat gMovementSensitivity = 1;      //movement sensitivity
GLfloat gRotationSensitivity = 2;      //rotational sensitivity

// material properties
GLfloat gAmbientMaterial[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat gSpecularMaterial[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLint gShininessMaterial = 50;

GLfloat gDiffuseBlue[] = {0.0f, 0.0f, 1.0f, 1.0f};
GLfloat gDiffuseRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
GLfloat gDiffuseGray[] = { 0.9f, 0.9f, 0.9f , 1.0f };
GLfloat gDiffuseLightBlue[] = { 0.4f, 0.4f, 0.5f, 1.0f};
GLfloat gDiffuseYellow[] = { 1.0f, 1.0f , 0.0f, 1.0f};
GLfloat gDiffuseDarkBrown[] = {0.65f, 0.18f, 0.18f, 1.0f};
GLfloat gDiffuseLightBrown[] = { 0.80f, 0.52f, 0.25f, 1.0f};

GLfloat gYellowEmission[] = {1.0f, 1.0f, 0.0f, 1.0f};
GLfloat gWhiteEmission[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat gNone[] = {0.0f, 0.0f, 0.0f, 1.0f};

//light properties
GLfloat gAmbientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };	  //ambient light
GLfloat gDiffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };	  //diffuse light
GLfloat gLightPosition[] = { 0.0f, 29.0f, -29.0f, 0.0f }; //light position

GLfloat gLightPosition1[] = { 0.0f, 29.0f, 29.0f, 0.0f }; //light1 position


GLfloat gLightPosition2[] = { 0.0f, 29.0f, 0.0f, 1.0f}; // light2 position
GLfloat gLightSpecular2[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat gLightDirection2[] = { 0.0f, -1.0f, 0.0f};

//set up states that are going to be used
void init()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //set clear background colour to black

  glEnable(GL_DEPTH_TEST);	//enable depth test

  //set material properties
  glMaterialfv(GL_FRONT, GL_AMBIENT, gAmbientMaterial);        //set material ambient component
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
  //glEnable(GL_COLOR_MATERIAL);
  glShadeModel(GL_SMOOTH);	//set shading model
  //glEnable(GL_DEPTH_TEST);
}

void resizeWindow(int width, int height)   //window width and height
{
  GLfloat range = 5.0;
     
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
  glLoadIdentity();		         //set projection matrix to identity matrix (analogous to clearing the modelview matrix)

  gluLookAt(0.0f, 0.0f, 10.0f,   //set camera position
            0.0f, 0.0f, 0.0f,    //set position where eye/camera is looking at
	        0.0f, 1.0f, 0.0f);   //set 'up' vector
}


//called whenever the window is resized (also called once when window is first drawn)
void resizeWindow2(int width, int height)   //window width and height
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

//draw the scene here
void drawScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clear the colour buffer to the colour previously set in glClearColor 

  glLightfv(GL_LIGHT0, GL_POSITION, gLightPosition);	//set light0's position
  //draw the light
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, gYellowEmission);  //set material emission component
    glTranslatef(0.0f, 29.0f, -29.0f);
    glutSolidSphere(0.5f, 16, 16);
    glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
  glPopMatrix();
  
  glLightfv(GL_LIGHT1, GL_POSITION, gLightPosition1);
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, gYellowEmission);  //set material emission component
    glTranslatef(0.0f, 29.0f, 29.0f);
    glutSolidSphere(0.5f, 16, 16);
    glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
  glPopMatrix();  
 
   
  glLightfv(GL_LIGHT2, GL_POSITION, gLightPosition2);
  glPushMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, gWhiteEmission);  //set material emission component
    glTranslatef(0.0f, 29.0f, 0.0f);
    glutSolidSphere(0.5f, 16, 16);
    glMaterialfv(GL_FRONT, GL_EMISSION, gNone);            //reset material emission component
  glPopMatrix();  

  //draw floor
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseRed);        //set material diffuse component
  glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(30.0f, 0.0f, 30.0f);	
    glVertex3f(30.0f, 0.0f, -30.0f);
    glVertex3f(-30.0f, 0.0f, -30.0f);
    glVertex3f(-30.0f, 0.0f, 30.0f);
  glEnd();
  
  //draw ceiling
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseGray);
  glBegin (GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f( 30.0f , 30.0f, 30.0f);
    glVertex3f(30.0f, 30.0f, -30.0f);
    glVertex3f(-30.0f, 30.0f , - 30.0f);
    glVertex3f(-30.0f, 30.0f, 30.0f);
  glEnd();
  
  
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseLightBlue);
  glBegin(GL_QUADS);
  //draw left wall
    glVertex3f(-30.0f, 0.0f, -30.0f);
    glVertex3f(-30.0f, 30.0f, -30.0f);
    glVertex3f(-30.0f, 30.0f, 30.0f);
    glVertex3f(-30.0f, 0.0f, 30.0f);
  //draw right wall
    glVertex3f(30.0f, 0.0f, -30.0f);
    glVertex3f(30.0f, 30.0f, -30.0f);
    glVertex3f(30.0f, 30.0f, 30.0f);
    glVertex3f(30.0f, 0.0f, 30.0f); 
  glEnd();
  
  glMaterialfv ( GL_FRONT, GL_DIFFUSE, gDiffuseYellow);
  glBegin(GL_QUADS);
  //draw back wall
    glVertex3f(-30.0f, 0.0f, -30.0f);
    glVertex3f(-30.0f, 30.0f, -30.0f);
    glVertex3f(30.0f, 30.0f, -30.0f);
    glVertex3f(30.0f, 0.0f , -30.0f);
 
  //draw front wall
    glVertex3f(-30.0f, 0.0f, 30.0f);
    glVertex3f(-30.0f, 30.0f, 30.0f);
    glVertex3f(30.0f, 30.0f, 30.0f);
    glVertex3f(30.0f, 0.0f , 30.0f);         
  glEnd();
  

  
  
  //draw table
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseDarkBrown);        //set material diffuse component
  glNormal3f(1.0f, 1.0f, 1.0f);
  glPushMatrix();
    glTranslatef(0.0f, 6.5f, 0.0f);
    glScalef(1.5f, 0.1f, 1.0f);
    glutSolidCube(10);
  glPopMatrix();
  //draw four legs of table
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightBrown);
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
  glNormal3f(1.0f, 1.0f, 1.0f);
  glPushMatrix();
    glTranslatef(-8.0f, 3.5f, 0.0f);
    glScalef(1.0f, 0.1f, 1.0f);
    glutSolidCube(5);
  glPopMatrix();  
  //draw four legs of chair1
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightBrown);
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
    glTranslatef(-10.2f, 6.5f, 0.0f);
    glScalef(0.1f, 1.2f, 1.0f);
    glutSolidCube(5);
  glPopMatrix();    
 
  //draw chair 2
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseDarkBrown);        //set material diffuse component
  glNormal3f(1.0f, 1.0f, 1.0f);
  glPushMatrix();
    glTranslatef(8.0f, 3.5f, 0.0f);
    glScalef(1.0f, 0.1f, 1.0f);
    glutSolidCube(5);
  glPopMatrix();  
  //draw four legs of chair 2
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseLightBrown);
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
    glTranslatef(10.2f, 6.5f, 0.0f);
    glScalef(0.1f, 1.2f, 1.0f);
    glutSolidCube(5);
  glPopMatrix();   
 
  
  
  //draw cone
  glMaterialfv(GL_FRONT, GL_DIFFUSE, gDiffuseBlue); 
  glPushMatrix();
    glTranslatef(-2.5f, 7.0f, -2.5f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(2.0f, 4.0f, 16, 8);
  glPopMatrix();
  
  //draw sphere
  glPushMatrix();
    glTranslatef(-2.0f, 8.0f, 2.5f);
    glutSolidSphere(1.0f, 16, 16); 
  glPopMatrix();
  
  //draw torus
  glPushMatrix();
    glTranslatef(2.0f, 9.5f, -2.5f);
    glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);
    glutSolidTorus(0.5f, 2.0f, 8, 16);
  glPopMatrix();

  //draw teapot
  glPushMatrix();
    glTranslatef(1.0f, 8.1f, 1.0f);
    glRotatef(135.0f, 0.0f, 1.0f, 0.0f);
    glutSolidTeapot(1.5f);
  glPopMatrix();

  //draw dodecahedron
  glPushMatrix();
    glTranslatef(5.0f, 8.1f, 1.0f);
    glutSolidDodecahedron();
  glPopMatrix();  
  
  //draw octahedron
  glPushMatrix();
    glTranslatef(-5.0f, 8.1f, 4.0f);
    glutSolidOctahedron();
  glPopMatrix();
  
  //draw tetrahedron
  glPushMatrix();
    glTranslatef(-3.0f, 8.1f, 4.0f);
    //glRotatef(135.0f, 0.0f, 1.0f, 0.0f);
    glutSolidTetrahedron();
  glPopMatrix();  
  
  //draw Icosahedron
  glPushMatrix();
    glTranslatef(5.0f, 8.1f, 5.0f);
    //glRotatef(135.0f, 0.0f, 1.0f, 0.0f);
    glutSolidIcosahedron();
  glPopMatrix();

  
  
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
    
  gCameraPosition[0] += sin(DEG2RAD(gCameraYaw))*gMoveForward;    //calculate movement along x axis
  gCameraPosition[2] += -cos(DEG2RAD(gCameraYaw))*gMoveForward;   //calculate movement along z axis
  gMoveForward = 0;     //reset forward/backward movement

  gCameraLookAt[0] = gCameraPosition[0] + sin(DEG2RAD(gCameraYaw));   //rotate camera lookat direction
  gCameraLookAt[2] = gCameraPosition[2] -cos(DEG2RAD(gCameraYaw));

  glLoadIdentity();     //load modelview matrix with identity matrix
  gluLookAt(gCameraPosition[0], gCameraPosition[1], gCameraPosition[2],   //set position
            gCameraLookAt[0], gCameraLookAt[1], gCameraLookAt[2],         //set where eye/camera is looking at
	        gCameraUp[0], gCameraUp[1], gCameraUp[2]);                    //set 'up' vector

  glutPostRedisplay();  //refresh display
}

//called when ASCII key pressed
void myKeypress(unsigned char key, int x, int y)
{
  switch(key)
  {
    //if ESC pressed, quit program
    case '\e': exit(1);     //quit
		       break;
    case 'w':  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    //wireframe mode
		       break;
    case 's':  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //fill mode
		       break;
    default: break;
  };
  
  glutPostRedisplay();  //refresh display
}

//called when non-ASCII key pressed
void mySpecialKeys(int key, int x, int y)
{
  switch(key)
  {
    //if home pressed
    case GLUT_KEY_HOME: gCameraPosition[1] += gMovementSensitivity;       //increment camera height
                        gCameraLookAt[1] += gMovementSensitivity;
		                break;
    //if end pressed
    case GLUT_KEY_END:  gCameraPosition[1] -= gMovementSensitivity;       //decrement camera height
                        gCameraLookAt[1] -= gMovementSensitivity;
		                break;
    //if arrow up pressed
    case GLUT_KEY_UP:   gMoveForward += gMovementSensitivity;             //increment forward movement
		                break;
    //if arrow down pressed
    case GLUT_KEY_DOWN: gMoveForward -= gMovementSensitivity;             //increment backward movement
		                break;
    //if left pressed
    case GLUT_KEY_LEFT: gCameraYaw -= gRotationSensitivity;               //increment camera yaw
    	                break;
    //if right pressed
    case GLUT_KEY_RIGHT: gCameraYaw += gRotationSensitivity;              //decrement camera yaw
    	                break;
    default: break;
  };
  
  updateCamera();       //call function to update camera and refresh the scene
}

int main(int argc, char* argv[])
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);      //requests properties for the window (sets up the rendering context)
  glutInitWindowSize(800, 600);			//set window size in pixels
  glutInitWindowPosition(50, 50);       //set window position from top-left corner of display
  glutCreateWindow("Simple Scene");		//set window title
  init();					            //call function to setup states 
  glutDisplayFunc(drawScene);			//register display callback function
  glutReshapeFunc(resizeWindow2);		//register resize callback function
  glutKeyboardFunc(myKeypress);		    //register non-ASCII keypress callback function
  glutSpecialFunc(mySpecialKeys);		//register non-ASCII keypress callback function

  glutMainLoop();                       //enter event loop
}
