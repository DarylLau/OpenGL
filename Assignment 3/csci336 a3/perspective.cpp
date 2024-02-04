#include <gl/glut.h>    //include glut library (automatically includes gl and glu libraries)

//set up states that are going to be used
void init()
{
  glClearColor(1.0, 1.0, 1.0, 1.0); //set clear background colour
}

//called whenever the window is resized (also called once when window is first drawn)
void resizeWindow(int width, int height)   //window width and height
{
  if(height == 0)				 //just in case, to prevent divide by zero when calculating aspect ratio
    height = 1;
  
  glViewport(0, 0, width, height);  //set the viewport

  glMatrixMode(GL_PROJECTION);	 //set matrix mode to projection matrix
  glLoadIdentity();		         //set projection matrix to identity matrix (analogous to clearing the projection matrix)
  gluPerspective(60.0f, 	     //set up perspective projection with 60 degrees field of view
		(GLfloat) width/(GLfloat) height, //set aspect ratio
        1.0f, 		             //set near clipping plane to 1.0
		100.0f);	             //set far clipping plane to 100.0
		
  glMatrixMode(GL_MODELVIEW);	 //set matrix mode to modelview matrix
  glLoadIdentity();		         //set projection matrix to identity matrix (analogous to clearing the modelview matrix)

  gluLookAt(0.0f, 0.0f, 10.0f,   //set camera position
            0.0f, 0.0f, 0.0f,    //set position where eye/camera is looking at
	        0.0f, 1.0f, 0.0f);   //set 'up' vector
}

//draws a unit cube
void drawCube()
{
  glBegin(GL_QUADS);
    //top face
    glVertex3f(0.5f, 0.5f, 0.5f);	
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    //front face
    glVertex3f(0.5f, 0.5f, 0.5f);	
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    //right face
    glVertex3f(0.5f, 0.5f, 0.5f);	
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    //left face
    glVertex3f(-0.5f, 0.5f, 0.5f);	
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    //bottom face
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);	

    //back face
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);	
  glEnd();
}

//draw the scene here
void drawScene()
{
  glClear(GL_COLOR_BUFFER_BIT); //clear the colour buffer

  glColor3f(1.0f, 0.0f, 0.0f);	//set colour
  drawCube();

  glFlush();
}

int main(int argc, char* argv[])
{
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);      //requests properties for the window (sets up the rendering context)
  glutInitWindowSize(512, 512);			            //set window size in pixels
  glutInitWindowPosition(50, 100);                  //set window position from top-left corner of display
  glutCreateWindow("3D Perspective Projection");	//set window title
  init();					                        //call function to setup states 
  glutDisplayFunc(drawScene);			            //register display callback function
  glutReshapeFunc(resizeWindow);			        //register resize callback function

  glutMainLoop();                                   //enter event loop
}
