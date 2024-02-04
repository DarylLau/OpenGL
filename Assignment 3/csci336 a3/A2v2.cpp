// Name : Lau Yan Chen Daryl
// Student Number : 4033747
// Course : BMMF
// Title : Assessment2
// fileName : A2v2.cpp
//
// Declaration : This assessment is strictly done on an individual basis
// no parts of the program is passed to my schoolmate.



#include <iostream>
#include <gl/glut.h>
#include <Vector>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;


struct Point
{
    float x;
    float y;
};

typedef vector <Point> Points;    // vector to store the points
Points points;

vector <Point> myPointFill;       //vector to store the fill points

struct Fill
{
       Points pt;
       int colour[3];
};

vector <Fill> myFill;             // vector to store the fill
Fill f;

struct Shape
{
       int type;
       int colour[3];
       int lineWidth;
       int ptSize;
       Points pt;
};

vector <Shape> myShape;           //vector to store the shape
Shape s;

float main_window_x;
float main_window_y;
char *window_title = "Paint";
int main_window;
int subwindow_1;
int subwindow_2;
int currTool = 0;                 //current tool selection 
int currColour = 0;               //current colour selection
int currPtSize = 1;               //current point size
int currLineWidth = 1;            //current line width
int colourPalette[8][3];          //the colour palette
static int noOfShape = 0;

float main_window_w = 1000;
float main_window_h = 600;
float subwindow1_w = 200;
float subwindow1_h = 600;
float subwindow2_w = 800;
float subwindow2_h = 600;

void initColour( int x[][3]);
char* currStr ( int );
int determineColour ( unsigned char [3]);
void display_str(GLint, GLint, void*, char*);
void main_display ();
void main_reshape (int w, int h);
void drawRect(int,int,int, Point, Point, int);
void drawQuad(int, int, int, Point, Point);
void drawTriBorder(int, int, int, Point, Point, Point, int);
void drawTriFill(int, int, int, Point, Point, Point);
void drawPoint( int, int, int, Point, int);
void drawLine ( int, int, int, Point, Point, int);
void drawCircleBorder ( float, float, float, Point, Point, int);
void drawCircleFill ( float, float, float, Point, Point);
void drawIconBorder ( int);
void myMouseSelect ( int, int, int, int );
void subwindow1_display ();
void resize1(int, int);
void subwindow2_display ();
void floodfill(int ,int,int [3],int [3]);
void mouseDraw (int, int, int, int );
void displayMenu();
void myMenu(int);

char* currStr ( int no)
{
      char* str ;
      switch(no)
      {
                case 1 : str = "1";
                         break;
                case 2 : str = "2" ;
                         break;
                case 3 : str = "3" ;
                         break;
                case 4 : str = "4" ;
                         break;
                case 5 : str = "5" ;
                         break;
                case 6 : str = "6" ;
                         break;
      }
      return str;
}



void initColour ( int x[][3])
{
 // to initialise the colour    
     x[0][0] = 255;
     x[0][1] = 0;
     x[0][2] = 0;     // red
     x[1][0] = 0;
     x[1][1] = 255;
     x[1][2] = 0;     // green
     x[2][0] = 0;
     x[2][1] = 0;
     x[2][2] = 255;   // blue
     x[3][0] = 255;
     x[3][1] = 255;
     x[3][2] = 0;     // yellow
     x[4][0] = 238;
     x[4][1] = 130;
     x[4][2] = 238;   // violet
     x[5][0] = 0;
     x[5][1] = 255;
     x[5][2] = 255;   // cyan
     x[6][0] = 112;
     x[6][1] = 138;
     x[6][2] = 144;   //grey
     x[7][0] = 46;
     x[7][1] = 139;
     x[7][2] = 87;   //sea green
     x[8][0] = 255;
     x[8][1] = 255;
     x[8][2] = 255; // white
}
int determineColour ( unsigned char colour[3])
{
// function to determine what colour is the pixel based on the default colour
    int colourCode = 8;
    
    int a = colour[0];
    int b = colour[1];
    int c = colour[2];

    for ( int i = 0 ; i < 8 ; i ++ )
    {
        if ( colourPalette[i][0] == colour[0] &&
             colourPalette[i][1] == colour[1] &&
             colourPalette[i][2] == colour[2] )
        {
             colourCode = i ;
        }
    }
    return colourCode;
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

void main_display ()
{
	//  Set background color to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	//  Swap front and back buffers
    glutSwapBuffers();
}

void main_reshape (int width, int height) 
{
// reshape the subwindow     
     
	subwindow1_w = (subwindow1_w * (width))/(main_window_w);
	subwindow1_h = (subwindow1_h * (height))/(main_window_h);

	//  Set subwindow 1 as current window and then reposition and resize it
    glutSetWindow (subwindow_1);
    glutReshapeWindow (subwindow1_w, subwindow1_h);
	
	//  Change the subwindow 2 dimensions as window dimensions change
	subwindow2_w = (subwindow2_w * (width))/(main_window_w);
	subwindow2_h = (subwindow2_h * (height))/(main_window_h);

	//  Set subwindow 2 as current window and then reposition and resize it
    glutSetWindow (subwindow_2);
    glutPositionWindow (subwindow1_w,0);
    glutReshapeWindow (subwindow2_w, subwindow2_h);

	//  Stay updated with the window width and height
	main_window_w = width;
	main_window_h = height;

}

void drawRect(int red, int green,int blue, Point pt1, Point pt2, int lineWidth)
{
  glLineWidth(lineWidth);         
  glColor3ub(static_cast<char>(red), static_cast<char>(green),static_cast<char>(blue));
  glBegin(GL_LINE_LOOP);
    glVertex2f(pt1.x, pt1.y);
    glVertex2f(pt2.x, pt1.y);
    glVertex2f(pt2.x, pt2.y );
    glVertex2f(pt1.x ,pt2.y);
  glEnd();          
}

void drawQuad(int red, int green, int blue, Point pt1, Point pt2)
{
  glColor3ub(static_cast<char>(red), static_cast<char>(green),static_cast<char>(blue));
  glBegin(GL_QUADS);
    glVertex2f(pt1.x, pt1.y);
    glVertex2f(pt2.x, pt1.y);
    glVertex2f(pt2.x, pt2.y );
    glVertex2f(pt1.x ,pt2.y);
  glEnd();          
} 

void drawTriBorder(int red, int green, int blue, Point pt1, Point pt2, Point pt3, int lineWidth)
{
  glLineWidth(lineWidth);       
  glColor3ub(static_cast<char>(red), static_cast<char>(green),static_cast<char>(blue));
  glBegin(GL_LINE_LOOP);
    glVertex2f(pt1.x, pt1.y);
    glVertex2f(pt2.x, pt2.y);
    glVertex2f(pt3.x, pt3.y);
  glEnd();         
}

void drawTriFill(int red, int green, int blue, Point pt1, Point pt2, Point pt3)
{
  glColor3ub(static_cast<char>(red), static_cast<char>(green),static_cast<char>(blue));
  glBegin(GL_TRIANGLES);
    glVertex2f(pt1.x, pt1.y);
    glVertex2f(pt2.x, pt2.y);
    glVertex2f(pt3.x, pt3.y);
  glEnd();     
}    

void drawPoint( int red, int green, int blue, Point pt1, int ptSize)
{
  glPointSize(ptSize);
  glEnable ( GL_POINT_SMOOTH); 
  glColor3ub(static_cast<char>(red), static_cast<char>(green),static_cast<char>(blue));    
  glBegin (GL_POINTS);
        glVertex2f (pt1.x, pt1.y);
  glEnd ();   
  glDisable ( GL_POINT_SMOOTH);
}

void drawLine ( int red, int green, int blue, Point pt1, Point pt2, int lineWidth)
{
  glLineWidth(lineWidth);       
  glColor3ub(static_cast<char>(red), static_cast<char>(green),static_cast<char>(blue));
  glBegin(GL_LINES);
    glVertex2f(pt1.x, pt1.y);
    glVertex2f(pt2.x, pt2.y);
  glEnd();        
}

void drawCircleBorder ( float red, float green, float blue, Point pt1, Point pt2, int lineWidth)
{
    float r;
    float a;
    float b;
// using the concept of a^2 + b^2 = c^2 to find the radius
    
    a = (float)( pt1.x - pt2.x ) * (float)( pt1.x - pt2.x);
    b = (float)(pt1.y - pt2.y) * (float)(pt1.y - pt2.y);
    r = sqrt( a + b ) ;

    glLineWidth(lineWidth);  
	glBegin(GL_LINE_LOOP);
	glColor3ub(static_cast<char>(red), static_cast<char>(green),static_cast<char>(blue));
	for ( int n=0; n<=60; ++n)
	{
		float const t = 2*M_PI*(float) n/(float) 60;
		glVertex2f(pt1.x + sin(t) * r, pt1.y + cos(t) *r );
	}	
	glEnd(); 
}


void drawCircleFill ( float red, float green, float blue, Point pt1, Point pt2)
{

    float r;
    float a;
    float b;
    
    a = (float)( pt1.x - pt2.x ) * (float)( pt1.x - pt2.x);
    b = (float)(pt1.y - pt2.y) * (float)(pt1.y - pt2.y);
    r = sqrt( a + b ) ;

	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(static_cast<char>(red), static_cast<char>(green),static_cast<char>(blue));
	glVertex2f (pt1.x,pt1.y);
	for ( int n=0; n<=60; ++n)
	{
		float const t = 2*M_PI*(float) n/(float) 60;
		glVertex2f(pt1.x + sin(t) * r, pt1.y + cos(t) *r );
	}	
	glEnd();
}

void drawIconBorder ( int tool)
{
// when select it will appear pop - down     
  int startingX = 5;
  int startingY = 575;
  int gap = 5;
  Point pt1;
  Point pt2;   
     
  for ( int i = 0 ; i < 3 ; i++ )
  {
      for ( int j = 0 ; j < 3 ; j++ )
      {

          pt1.x = startingX + ( (60 + gap) * j );
          pt1.y = startingY - ( (60 +gap) * i );
          
          pt2.x = startingX + 60 + ( (60 +gap) * j );
          pt2.y = startingY - 60 - ( (60+gap) * i );
          drawRect(0, 0 ,0, pt1, pt2 , 3 );    
      }
  }   
  switch ( tool )
  {
         case 0 : 
                  pt1.x = 5;
                  pt1.y = 575;
                  pt2.x = 65;
                  pt2.y = 515;
                  drawRect(220, 220 ,220, pt1, pt2 , 3 ); 
                  break;  
         
         case 1 :
                  pt1.x = 70;
                  pt1.y = 575;
                  pt2.x = 130;
                  pt2.y = 515;
                  drawRect(220, 220,220 , pt1, pt2 , 3 );  
                  break;
        case 2 :
                  pt1.x = 135;
                  pt1.y = 575;
                  pt2.x = 195;
                  pt2.y = 515;
                  drawRect(220, 220,220 , pt1, pt2 , 3 ); 
                  break;
        case 3 :
                  pt1.x = 5;
                  pt1.y = 510;
                  pt2.x = 65;
                  pt2.y = 450;
                  drawRect(220, 220,220 , pt1, pt2 , 3 ); 
                  break;
        case 4 :
                  pt1.x = 70;
                  pt1.y = 510;
                  pt2.x = 130;
                  pt2.y = 450;
                  drawRect(220, 220,220 , pt1, pt2 , 3 ); 
                  break;
        
        case 5 :
                  pt1.x = 135;
                  pt1.y = 510;
                  pt2.x = 195;
                  pt2.y = 450;
                  drawRect(220, 220,220 , pt1, pt2 , 3 ); 
                  break;
        
        case 6 :
                  pt1.x = 5;
                  pt1.y = 445;
                  pt2.x = 65;
                  pt2.y = 385;
                  drawRect(220, 220,220 , pt1, pt2 , 3 ); 
                  break;
        
        case 7 :
                  pt1.x = 70;
                  pt1.y = 445;
                  pt2.x = 130;
                  pt2.y = 385;
                  drawRect(220, 220,220 , pt1, pt2 , 3 ); 
                  break;
        case 8 :
                  pt1.x = 135;
                  pt1.y = 445;
                  pt2.x = 195;
                  pt2.y = 385;
                  drawRect(220, 220,220 , pt1, pt2 , 3 ); 
                  break;   
        case 9 :
                  pt1.x = 100;
                  pt1.y = 100;
                  pt2.x = 180;
                  pt2.y = 50;
                  drawRect( 250, 150, 150, pt1, pt2, 15);
                  break;      
  }
       
}


void myMouseSelect (int button, int state, int x, int y)
{
// based on the coordinate determine which tool and colour is chosen
  y = subwindow1_h - y ;
  
  float xPos;
  float yPos;
  xPos = x / ((float) subwindow1_w / 200.0);
  yPos = y / ((float) subwindow1_h / 600.0);
  bool changed = false;
  
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {        
    if ( xPos > 5 &&  xPos < 65 )
    {
         if ( yPos > 515 && yPos < 575 )
         {
              currTool = 0 ;
              changed = true;
              
         }
         else if ( yPos > 450 && yPos < 510 )
         {
              currTool = 3;
              changed = true;
         }
         else if ( yPos > 385 && yPos < 445 )
         {
              currTool = 6;
              changed = true;
         }
    }
    else if ( xPos > 70 && xPos < 130 )
    {
         if ( yPos > 515 && yPos < 575 )
         {
              currTool = 1 ;
              changed = true;
         }
         else if ( yPos > 450 && yPos < 510 )
         {
              currTool = 4;
              changed = true;
         }
         else if ( yPos > 385 && yPos < 445 )
         {
              currTool = 7;
              changed = true;
         }
    }    
    else if ( xPos > 135 && xPos < 195 )  
    {
         if ( yPos > 515 && yPos < 575 )
         {
              currTool = 2 ;
              changed = true;
         }
         else if ( yPos > 450 && yPos < 510 )
         {
              currTool = 5;
              changed = true;
         }
         else if ( yPos > 385 && yPos < 445 )
         {
              currTool = 8;
              changed = true;
         }
    }

    
    if ( yPos > 260 && yPos < 300 )
    {
         if ( xPos > 10 && xPos < 50 )
         {
              currColour = 0;
              changed = true;
         }
         else if ( xPos > 55 && xPos < 95)
         {
              currColour = 1;
              changed = true;
         }
         else if (xPos > 100 && xPos < 140)
         {
              currColour = 2;
              changed = true;
         }
         else if ( xPos > 145 && xPos < 185)
         {
              currColour = 3;
              changed = true;
         }
    }
    else if ( yPos > 215 && yPos < 255 )
    {
         if ( xPos > 10 && xPos < 50 )
         {
              currColour = 4;
              changed = true;
         }
         else if ( xPos > 55 && xPos < 95)
         {
              currColour = 5;
              changed = true;
         }
         else if (xPos > 100 && xPos < 140)
         {
              currColour = 6;
              changed = true;
         }
         else if ( xPos > 145 && xPos < 185)
         {
              currColour = 7;
              changed = true;
         }    
    }  
    
    if ( xPos > 10 && xPos < 90 )
    {
         if ( yPos > 50 && yPos < 100 )
         {
              myShape.clear();
              myFill.clear();
         }
    }
    
    if ( xPos > 100 && xPos < 180)
    {
         if ( yPos > 50 && yPos < 100 )
         {
              currTool = 9;
              changed = true;
         }
    }
    
    if ( xPos > 45 && xPos < 125 )
    {
         if ( yPos > 5 && yPos < 45 )
         {
              exit (1);
         }
    }
         
// when there is any extra changes, the points will reset              
    if ( changed )
    {
         points.clear();
    }       
  }
  glutPostWindowRedisplay(subwindow_1);
  glutPostWindowRedisplay(subwindow_2);   
              
}


void subwindow1_display ()
{
// the user interface
  glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  
  glColor3f(0.0f, 1.0f, 0.0f);

  int startingX;
  int startingY;
  int gap;
  Point pt1;
  Point pt2;
  Point pt3;
  drawIconBorder( currTool);
  pt1.x = 35;
  pt1.y = 540;
  
  drawPoint ( colourPalette[currColour][0], colourPalette[currColour][1],
              colourPalette[currColour][2], pt1 , 5);
              
  pt1.x = 80;
  pt1.y = 555;
  pt2.x = 120;
  pt2.y = 530;
  
  drawLine ( colourPalette[currColour][0], colourPalette[currColour][1],
              colourPalette[currColour][2], pt1, pt2 , 2);
              
  pt1.x = 165;
  pt1.y = 560;
  pt2.x = 150;
  pt2.y = 530;
  pt3.x = 180;
  pt3.y = 530;
  
  drawTriBorder( colourPalette[currColour][0], colourPalette[currColour][1],
              colourPalette[currColour][2], pt1, pt2, pt3, 2);
  
  pt1.x = 35;
  pt1.y = 495;
  pt2.x = 20;
  pt2.y = 465;
  pt3.x = 50;
  pt3.y = 465;
  
  drawTriFill ( colourPalette[currColour][0], colourPalette[currColour][1],
              colourPalette[currColour][2], pt1, pt2, pt3);
  
  pt1.x = 82;
  pt1.y = 495;
  pt2.x = 118;
  pt2.y = 465;
  drawRect (colourPalette[currColour][0], colourPalette[currColour][1],
              colourPalette[currColour][2], pt1, pt2, 2);
  
  pt1.x = 147;
  pt1.y = 495;
  pt2.x = 180;
  pt2.y = 465;
  drawQuad (colourPalette[currColour][0], colourPalette[currColour][1],
              colourPalette[currColour][2], pt1, pt2);
              
  pt1.x = 35;
  pt1.y = 415;
  pt2.x = 35;
  pt2.y = 430;
  drawCircleBorder (colourPalette[currColour][0], colourPalette[currColour][1],
              colourPalette[currColour][2], pt1, pt2 , 2);
              
  pt1.x = 100;
  pt1.y = 415;
  pt2.x = 100;
  pt2.y = 432;
  drawCircleFill (colourPalette[currColour][0], colourPalette[currColour][1],
              colourPalette[currColour][2], pt1, pt2);  
              
  /* === drawing of the colour picker tool ==== */
  pt1.x = 180;
  pt1.y = 440;
  pt2.x = 190;
  pt2.y = 430;
  pt3.x = 170;
  pt3.y = 420;
  drawTriFill ( 0, 0, 0, pt1, pt2, pt3);
  pt1.x = 160;
  pt1.y = 430;
  pt2.x = 179;
  pt2.y = 412;
  drawLine ( 0,0,0, pt1, pt2, 8);
  glColor3ub(static_cast<char>(colourPalette[currColour][0]), static_cast<char>(colourPalette[currColour][1]),
                  static_cast<char>(colourPalette[currColour][2]));
  glBegin(GL_QUADS);
    glVertex2f(164, 423);
    glVertex2f(155, 415);
    glVertex2f(155, 400 );
    glVertex2f(172 ,416);
  glEnd();
  glLineWidth(2.0);
  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_LINE_LOOP);
    glVertex2f(164, 423);
    glVertex2f(155, 415);
    glVertex2f(155, 400 );
    glVertex2f(172 ,416);
  glEnd();
  

  
    startingY = 300;
    startingX = 10;    
    gap = 40;
    int x = 0;
    for ( int i = 0 ; i < 2 ; i++ )
    {
        for ( int j = 0 ; j < 4 ; j++ )
        {
            Point pt1;
            Point pt2;
            pt1.x = startingX + ( (5 + gap) * j);
            pt1.y = startingY - ( (5 + gap) * i);
            pt2.x = startingX + 40 + ( (5 + gap) * j );
            pt2.y = startingY - 40 - ( (5 + gap) * i) ;
            int red = colourPalette[x][0];
            int green = colourPalette[x][1];
            int blue = colourPalette[x][2];
            drawRect(0,0,0,pt1,pt2,3);
            drawQuad(red, green, blue, pt1, pt2);
            x++;
         }
    }
    
    display_str( 5, 180, GLUT_BITMAP_HELVETICA_10, "Current Pt Size : ");
    display_str( 120, 180, GLUT_BITMAP_HELVETICA_10,  currStr(currPtSize));
    display_str( 5, 150, GLUT_BITMAP_HELVETICA_10, "Current Line Width : ");
    display_str( 120, 150, GLUT_BITMAP_HELVETICA_10,  currStr(currLineWidth));

    pt1.x = 100;
    pt1.y = 100;
    pt2.x = 180;
    pt2.y = 50;
    drawRect (0, 0, 0, pt1, pt2, 3);
    drawQuad( 193, 205, 193 , pt1, pt2);
    glColor3f(0.0f, 0.0f, 0.0f);
    display_str(120,65 , GLUT_BITMAP_HELVETICA_18 , "FILL");
    
    pt1.x = 10;
    pt1.y = 100;
    pt2.x = 90;
    pt2.y = 50;
    drawRect (0, 0, 0, pt1, pt2,3);
    drawQuad ( 193, 205, 193, pt1, pt2);
    glColor3f( 0.0f, 0.0f, 0.0f);
    display_str(20,65, GLUT_BITMAP_HELVETICA_18 , "CLEAR" );
    
    pt1.x = 45;
    pt1.y = 45;
    pt2.x = 125;
    pt2.y = 5;
    drawRect ( 0, 0 ,0, pt1, pt2, 3);
    drawQuad ( 193, 205, 193 , pt1, pt2);
    glColor3f ( 0.0f , 0.0f , 0.0f);
    display_str(55,15, GLUT_BITMAP_HELVETICA_18 , "QUIT" );
    
    glLineWidth(1.0);
    
    glutSwapBuffers();   
}

void resize1 (int width, int height)
{
// to keep the aspect ratio the same for window 1
    subwindow1_w = width;
    subwindow1_h = height;
    
    glViewport (0, 0, width, height);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0, 200, 0, 600);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}
void resize2 (int width, int height)
{
// to keep the aspect ratio the same for window 2
    subwindow2_w = width;
    subwindow2_h = height;
    
    glViewport (0, 0, width, height);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0, 800, 0, 600);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void floodfill(int x ,int y,int colourToFill[3],int colourClicked[3])
{
// algorithm for the flood fill
  unsigned char screenColour[3] = {0};
  glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,screenColour);
  int rClicked = screenColour[0];
  int gClicked = screenColour[1];
  int bClicked = screenColour[2];

  if ( rClicked == colourClicked[0] && gClicked == colourClicked[1] &&
                   bClicked == colourClicked[2] )
  {
   
   glBegin(GL_POINTS);
     glColor3ub(static_cast<char>(colourToFill[0]), static_cast<char>(colourToFill[1]),
                       static_cast<char>(colourToFill[2]));
     glVertex2f(x,y);
     Point pt;
     pt.x = x ;
     pt.y = y;
     myPointFill.push_back(pt);
   glEnd();
   glutSwapBuffers ();
   
   floodfill(x+1,y,colourToFill,colourClicked);
   floodfill(x,y+1,colourToFill,colourClicked);
   floodfill(x-1,y,colourToFill,colourClicked);
   floodfill(x,y-1,colourToFill,colourClicked);
   }
} 

void mouseDraw (int button, int state, int x, int y )
{
// depending on the tools selected, will decide what action will be carried out
  y = subwindow2_h - y ;
  
  float xPos;
  float yPos;
  Point pt;
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
     xPos = x / ((float) subwindow1_w / 200.0);
     yPos = y / ((float) subwindow1_h / 600.0);
     pt.x = xPos;
     pt.y = yPos;
     points.push_back (pt);
     
     if ( currTool == 8 )  // colour droplet
     {
       unsigned char colour[3] = {0};
       glReadPixels ( x , y , 1, 1, GL_RGB, GL_UNSIGNED_BYTE, colour);
       currColour = determineColour ( colour );
     }
     
     if ( currTool == 9 )          // flood fill
     {    
          unsigned char colour[3] = {0};
          glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,colour);
          int colourClicked[3] = {0};
          colourClicked[0] = colour[0];
          colourClicked[1] = colour[1];
          colourClicked[2] = colour[2];
          floodfill(pt.x,pt.y, colourPalette[currColour], colourClicked);
          f.colour[0] = colourPalette[currColour][0]; 
          f.colour[1] = colourPalette[currColour][1];
          f.colour[2] = colourPalette[currColour][2];
          f.pt = myPointFill;
          myFill.push_back(f);
          myPointFill.clear();       
     }
     
     
  }    
  s.colour[0] = colourPalette[currColour][0]; 
  s.colour[1] = colourPalette[currColour][1];
  s.colour[2] = colourPalette[currColour][2];
  s.ptSize = currPtSize;
  s.lineWidth = currLineWidth;
  if ( currTool == 0 )        // point
  {
       if ( points.size() == 1 )
       {
          s.type = 0;
          s.pt = points;
          myShape.push_back(s);
          points.clear();
       }
  }
  else if ( currTool == 1)     // line
  {
       if ( points.size() == 2)
       {
            s.type = 1;
            s.pt = points;
            myShape.push_back(s);
            points.clear();
       }
  }
  else if ( currTool == 2)       //triangle border
  {
       if ( points.size () == 3)
       {
            s.type = 2;
            s.pt = points;
            myShape.push_back(s);
            points.clear();
       }
  }
  else if ( currTool == 3)       // triangle fill
  {
       if ( points.size() == 3)
       {
            s.type = 3;
            s.pt=points;
            myShape.push_back(s);
            points.clear();
       }
  }
  else if ( currTool == 4)       //rectangle border
  {
       if ( points.size() == 2)
       {
            s.type = 4;
            s.pt=points;
            myShape.push_back(s);
            points.clear();
       }
  }
  else if ( currTool == 5 )      // rectangle fill
  {
       if ( points.size() == 2)
       {
            s.type = 5;
            s.pt = points;
            myShape.push_back(s);
            points.clear();
       }
  }
  else if ( currTool == 6 )      // circle border
  {
       if ( points.size() == 2)
       {
            s.type = 6;
            s.pt = points;
            myShape.push_back(s);
            points.clear();
       }
  }
  else if ( currTool == 7 )      // circle filled
  {
       if ( points.size() == 2)
       {
            s.type = 7;
            s.pt = points;
            myShape.push_back(s);
            points.clear();
       }
  }

  glutPostWindowRedisplay(subwindow_2);  
  glutPostWindowRedisplay(subwindow_1);
     
}

void subwindow2_display ()
{
// to display the canvas
	//  Set background color to white
	glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    for ( int i =0 ; i < myShape.size(); i++)
    {
        if ( myShape[i].type == 0 )
        {
               drawPoint ( myShape[i].colour[0], myShape[i].colour[1],
                         myShape[i].colour[2], myShape[i].pt[0] , myShape[i].ptSize);
        }
        else if ( myShape[i].type == 1)
        {
             drawLine ( myShape[i].colour[0], myShape[i].colour[1], myShape[i].colour[2],
                        myShape[i].pt[0], myShape[i].pt[1], myShape[i].lineWidth);
        }
        else if ( myShape[i].type == 2)
        {
             drawTriBorder ( myShape[i].colour[0], myShape[i].colour[1], myShape[i].colour[2],
                        myShape[i].pt[0], myShape[i].pt[1], myShape[i].pt[2], myShape[i].lineWidth);
        }
        else if ( myShape[i].type == 3)
        {
             drawTriFill ( myShape[i].colour[0], myShape[i].colour[1], myShape[i].colour[2],
                        myShape[i].pt[0], myShape[i].pt[1], myShape[i].pt[2]);
        }
        else if ( myShape[i].type == 4)
        {
             drawRect( myShape[i].colour[0], myShape[i].colour[1], myShape[i].colour[2],
                        myShape[i].pt[0], myShape[i].pt[1], myShape[i].lineWidth);
        }
        else if ( myShape[i].type == 5)
        {
             drawQuad( myShape[i].colour[0], myShape[i].colour[1], myShape[i].colour[2],
                        myShape[i].pt[0], myShape[i].pt[1]);
        }
        else if ( myShape[i].type == 6 )
        {
            drawCircleBorder( myShape[i].colour[0], myShape[i].colour[1], myShape[i].colour[2],
                        myShape[i].pt[0], myShape[i].pt[1], myShape[i].lineWidth);
        }
        else if ( myShape[i].type == 7)
        {
             drawCircleFill( myShape[i].colour[0], myShape[i].colour[1], myShape[i].colour[2],
                        myShape[i].pt[0], myShape[i].pt[1]);             
        }
    }
                         
    for ( int i = 0 ; i < myFill.size(); i++)
    {
        for ( int j = 0 ; j < myFill[i].pt.size(); j++ )
        {
            drawPoint ( myFill[i].colour[0], myFill[i].colour[1], myFill[i].colour[2],
                        myFill[i].pt[j], 1);
        }
    }

	
	glutSwapBuffers ();
}


void displayMenu()
{
// what is to be shown in the menu when right click     

  int sub_menu = glutCreateMenu(myMenu);
  glutAddMenuEntry("red", 'q');
  glutAddMenuEntry("green", 'w');
  glutAddMenuEntry("blue", 'e');
  glutAddMenuEntry("yellow", 'r');
  glutAddMenuEntry("violet", 't');
  glutAddMenuEntry("cyan", 'y');
  glutAddMenuEntry("gray", 'u');
  glutAddMenuEntry("sea green", 'i');
  
  int sub_menu2 = glutCreateMenu(myMenu);
  glutAddMenuEntry("1", 'a');
  glutAddMenuEntry("2", 's');
  glutAddMenuEntry("3", 'd');
  glutAddMenuEntry("4", 'f');
  glutAddMenuEntry("5", 'g');
  glutAddMenuEntry("6", 'h');
  
  int sub_menu3 = glutCreateMenu(myMenu);
  glutAddMenuEntry("1", 'z');
  glutAddMenuEntry("2", 'x');
  glutAddMenuEntry("3", 'c');
  glutAddMenuEntry("4", 'v');
  glutAddMenuEntry("5", 'b');
  glutAddMenuEntry("6", 'n');

  int main_menu = glutCreateMenu(myMenu);
  glutAddMenuEntry("Main Menu", 0);
  glutAddMenuEntry("", 0);
  glutAddSubMenu("Colour", sub_menu);
  glutAddSubMenu("Point Size", sub_menu2);
  glutAddSubMenu("line Width", sub_menu3);
  glutAddMenuEntry("Clear" , 2 );
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
    case 2: myShape.clear();
            myFill.clear();
            break;
    case 'q': currColour = 0;
              break;
    case 'w': currColour = 1;
              break;
    case 'e': currColour = 2;
              break;
    case 'r': currColour = 3;
              break;
    case 't': currColour = 4;
              break;
    case 'y': currColour = 5;
              break;
    case 'u': currColour = 6;
              break;
    case 'i': currColour = 7;
              break;
    case 'a': currPtSize = 1;
              break;
    case 's': currPtSize = 2;
              break;
    case 'd': currPtSize = 3;
              break;
    case 'f': currPtSize = 4;
              break;
    case 'g': currPtSize = 5;
              break;
    case 'h': currPtSize = 6;
              break;
    case 'z': currLineWidth = 1;
              break;
    case 'x': currLineWidth = 2;
              break;
    case 'c': currLineWidth = 3;
              break;
    case 'v': currLineWidth = 4;
              break;
    case 'b': currLineWidth = 5;
              break;
    case 'n': currLineWidth = 6;
              break;

    default: break;
  };
  glutPostWindowRedisplay(subwindow_1);
  glutPostWindowRedisplay(subwindow_2);  
}

int main (int argc, char **argv)
{

	glutInitWindowSize (main_window_w, main_window_h);
	glutInitWindowPosition (main_window_x, main_window_y);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE);
	initColour(colourPalette);
	main_window = glutCreateWindow (window_title);

    glutDisplayFunc (main_display);
	glutReshapeFunc  (main_reshape);

    
	/**** Subwindow 1 *****/
    subwindow_1 = glutCreateSubWindow (main_window, 0, 0, subwindow1_w, subwindow1_h);
	glutDisplayFunc (subwindow1_display);
	glutReshapeFunc  (resize1);
	glutMouseFunc (myMouseSelect);
	displayMenu();
	/**** Subwindow 2 *****/
    subwindow_2 = glutCreateSubWindow (main_window, 200, 0, subwindow2_w, subwindow2_h);
	glutDisplayFunc (subwindow2_display);
	glutReshapeFunc ( resize2);
	glutMouseFunc ( mouseDraw);
	displayMenu();

	glutMainLoop();
}

