// Name : Lau Yan Chen Daryl
// Student Number : 4033747
// Course : BMMF
// Title : Assessment1
// fileName : A1.cpp
//
// Declaration : This assessment is strictly done on an individual basis
// no parts of the program is passed to my schoolmate.

#include <iostream>
#include <string>
#include <math.h>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include <gl/glut.h>    //include glut library (automatically includes gl and glu libraries)
using namespace std;

GLint gMainWindow, gInfoWindow, gLineChart, 
      gBarChart, gPieChartZoo1, gPieChartZoo2; // the different subwindows
      
GLint winWidth, winHeight ;      // the heigth and width of respective subwindows

int currentZoo = 0;              // which zoo the current "pointer" at
int currentYear = 0;             // which year the current "pointer" at

int lineChartX = 40;             // the origin x coordinate of the lineChart
int lineChartY = 40;             // the origin y coordinate of the lineChart

int barChartX = 50;              // the origin x coordinate of the barchart
int barChartY = 40;              // the origin y coordinate of the barchart

int zoo[2][7];                   // the 2d array to store the data

int colourPalette[13][3];        // the 2d array to store the different colours for the graph/chart
   
static int xStart = 0;           // the x coordinate of the mouse position
static int yStart = 0;           // the y coordinate of the mouse position
bool isPoint = false;            // whether any point or bar is selected

void initData ( int x[][7])      
{
// to random the number of banana the zoo used     
     for ( int i = 0 ; i < 2 ; i ++ )
     {
           for ( int j = 0 ; j < 7 ; j ++ )
           {
               x[i][j] = rand()%500 ;
           }
    }
}

void initColour ( int x[][3])
{
// to random the colour of the graph and chart
     for ( int i = 0 ; i < 13 ; i ++ )
     {
           for ( int j = 0 ; j < 3 ; j++ )
           {
               x[i][j] = rand()%256 ;
           }
     }
}
char* currentZooStr(int no)
{
// changes the number of the current zoo to the zoo it represent      
       char* str;
       switch(no)
       {
                  case 0 : str = "Zoo 1" ;
                           break;
                           
                  case 1 : str = "Zoo 2" ;
                           break;
       }
       return str;
}

char* currentYearStr(int no)
{
// changse the number of the current year to the year it represent
      char* str;
      switch(no)
      {
                case 0 : str = "2005" ;
                         break;
                
                case 1 : str = "2006" ;
                         break;
                
                case 2 : str = "2007" ;
                         break;
                         
                case 3 : str = "2008" ;
                         break;
                         
                case 4 : str = "2009" ;
                         break;
                
                case 5 : str = "2010" ;
                         break;
                
                case 6 : str = "2011" ;
                         break;
      }
      return str;
}
      
string toString(int a)
{
// changes int value to string value
       stringstream value1;
       value1<<a;
       string str = value1.str();
       return str ;
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

void myMenu(int value)
{
// show what each of the different case in the menu does     
  switch(value)
  {
    case 1: exit(1);     //quit
            break;
    case 2: initData(zoo); //random data
            break;
    case 3: initColour(colourPalette);//random colour
            break;
    case 'q': currentZoo = 0 ;               // changes the "pointer"
              currentYear = 0;
              break;
    case 'w': currentZoo = 0 ;
              currentYear = 1;
              break;
    case 'e': currentZoo = 0 ;
              currentYear = 2;
              break;
    case 'r': currentZoo = 0 ;
              currentYear = 3;
              break;
    case 't': currentZoo = 0 ;
              currentYear = 4;
              break;
    case 'y': currentZoo = 0 ;
              currentYear = 5;
              break;
    case 'u': currentZoo = 0 ;
              currentYear = 6;
              break;
    case 'a': currentZoo = 1 ;
              currentYear = 0;
              break;
    case 's': currentZoo = 1 ;
              currentYear = 1;
              break;
    case 'd': currentZoo = 1 ;
              currentYear = 2;
              break;
    case 'f': currentZoo = 1 ;
              currentYear = 3;
              break;
    case 'g': currentZoo = 1 ;
              currentYear = 4;
              break;
    case 'h': currentZoo = 1 ;
              currentYear = 5;
              break;
    case 'i': currentZoo = 1 ;
              currentYear = 6;
              break;

    default: break;
  };
  
// redisplay the sub window
  glutPostWindowRedisplay(gInfoWindow);
  glutPostWindowRedisplay(gLineChart);
  glutPostWindowRedisplay(gBarChart);
  glutPostWindowRedisplay(gPieChartZoo1);
  glutPostWindowRedisplay(gPieChartZoo2);
}


void reshape(int width, int height) 
{
  winWidth = width;
  winHeight = height;   
     
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, width, 0, height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void main_display()
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glFlush();
}

//called when ASCII key pressed
void myKeypress(unsigned char key, int x, int y)
{
  switch(key)
  {
    case 'r' : initData(zoo);             // random data
               break;
    case 'c' : initColour(colourPalette); // random colour
               break;
    case '1' : currentYear = 0 ;          // changes the pointer
               break;
    case '2' : currentYear = 1;
               break;
    case '3' : currentYear = 2;
               break;
    case '4' : currentYear = 3;
               break;
    case '5' : currentYear = 4;
               break;
    case '6' : currentYear = 5;
               break;
    case '7' : currentYear = 6;
               break;
    
    case 27: exit(1);     //quit
		     break;
  };
//redisplay
  glutPostWindowRedisplay(gInfoWindow);
  glutPostWindowRedisplay(gLineChart);
  glutPostWindowRedisplay(gBarChart);
  glutPostWindowRedisplay(gPieChartZoo1);
  glutPostWindowRedisplay(gPieChartZoo2);
}
void mySpecialKeys(int key, int x, int y)
{
  switch(key)
  {
    //if arrow up pressed
    case GLUT_KEY_UP: zoo[currentZoo][currentYear] ++;	   // increment value
                      if ( zoo[currentZoo][currentYear] >= 500 )
                         zoo[currentZoo][currentYear] = 500 ;
                      else if ( zoo[currentZoo][currentYear] < 0 )
                           zoo[currentZoo][currentYear] = 0 ;
    	  
		              break;
    //if arrow down pressed
    case GLUT_KEY_DOWN: zoo[currentZoo][currentYear]--;     // decrement value
                        if ( zoo[currentZoo][currentYear] >= 500 )
                           zoo[currentZoo][currentYear] = 500 ;
                        else if ( zoo[currentZoo][currentYear] < 0 )
                           zoo[currentZoo][currentYear] = 0 ;
        
                        break;
    // if f1 key pressed
    case GLUT_KEY_F1 : currentZoo = 0;
                       break;
    // if f2 key pressed
    case GLUT_KEY_F2 : currentZoo = 1;
                       break;
  };
// redisplay
  glutPostWindowRedisplay(gInfoWindow);
  glutPostWindowRedisplay(gLineChart);
  glutPostWindowRedisplay(gBarChart);
  glutPostWindowRedisplay(gPieChartZoo1);
  glutPostWindowRedisplay(gPieChartZoo2);  
  
}

void myMotionFuncBar(int x, int y)
{
// when drag left , decrease value
// when drag right , increase value
   if ( x > 0 && x < 400 && isPoint )
           zoo[currentZoo][currentYear] += ( x- xStart);

   if ( zoo[currentZoo][currentYear] < 0 )
      zoo[currentZoo][currentYear] = 0;
   else if ( zoo[currentZoo][currentYear] > 500)
      zoo[currentZoo][currentYear] = 500;

// redisplay
  glutPostWindowRedisplay(gInfoWindow);
  glutPostWindowRedisplay(gLineChart);
  glutPostWindowRedisplay(gBarChart);
  glutPostWindowRedisplay(gPieChartZoo1);
  glutPostWindowRedisplay(gPieChartZoo2);      
  
// reposition the mouse value
  xStart = x;
}

void myMouseBar(int button, int state, int x, int y)
{
  isPoint = false;   
     
  int yInvert = 300 - y ;
  int yPos = yInvert - barChartY   ; 
  //if left mouse button pressed
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
  // when it is within the coordinate of the bar chart
            if ( yPos > 5 && yPos < 15 )
            {
               if ( x > barChartX && x < barChartX + zoo[1][0]/2 )
               {
                    currentYear = 0;
                    currentZoo = 1;
                    isPoint = true;
               }
            }
            else if ( yPos > 15 && yPos < 25)
            {
                 if ( x > barChartX && x < barChartX + zoo[0][0]/2)
                 {
                      currentYear = 0;
                      currentZoo = 0;
                      isPoint = true;
                 }
            }
            else if ( yPos > 35 && yPos < 45)
            {
                 if ( x > barChartX && x < barChartX + zoo[1][1]/2)
                 {
                      currentYear = 1;
                      currentZoo = 1;
                      isPoint = true;
                 }
            }
            else if ( yPos > 45 && yPos < 55)
            {
                 if ( x > barChartX && x < barChartX + zoo[0][1]/2)
                 {
                      currentYear = 1;
                      currentZoo = 0;
                      isPoint = true;
                 }
            }
            else if ( yPos > 65 && yPos < 75)
            {
                 if ( x > barChartX && x < barChartX + zoo[1][2]/2)
                 {
                      currentYear = 2;
                      currentZoo = 1;
                      isPoint = true;
                 }
            }
            else if ( yPos > 75 && yPos < 85)
            {
                 if ( x > barChartX && x < barChartX + zoo[0][2]/2)
                 {
                      currentYear = 2;
                      currentZoo = 0;
                      isPoint = true;
                 }
            }
            else if ( yPos > 95 && yPos < 105)
            {
                 if ( x > barChartX && x < barChartX + zoo[1][3]/2)
                 {
                      currentYear = 3;
                      currentZoo = 1;
                      isPoint = true;
                 }
            }
            else if ( yPos > 105 && yPos < 115)
            {
                 if ( x > barChartX && x < barChartX + zoo[0][3]/2)
                 {
                      currentYear = 3;
                      currentZoo = 0;
                      isPoint = true;
                 }
            }
            else if ( yPos > 125 && yPos < 135)
            {
                 if ( x > barChartX && x < barChartX + zoo[1][4]/2)
                 {
                      currentYear = 4;
                      currentZoo = 1;
                      isPoint = true;
                 }
            }
            else if ( yPos > 135 && yPos < 145)
            {
                 if ( x > barChartX && x < barChartX + zoo[0][4]/2)
                 {
                      currentYear = 4;
                      currentZoo = 0;
                      isPoint = true;
                 }
            }
            else if ( yPos > 155 && yPos < 165)
            {
                 if ( x > barChartX && x < barChartX + zoo[1][5]/2)
                 {
                      currentYear = 5;
                      currentZoo = 1;
                      isPoint = true;
                 }
            }
            else if ( yPos > 165 && yPos < 175)
            {
                 if ( x > barChartX && x < barChartX + zoo[0][5]/2)
                 {
                      currentYear = 5;
                      currentZoo = 0;
                      isPoint = true;
                 }
            }
            else if ( yPos > 185 && yPos < 195)
            {
                 if ( x > barChartX && x < barChartX + zoo[1][6]/2)
                 {
                      currentYear = 6;
                      currentZoo = 1;
                      isPoint = true;
                 }
            }
            else if ( yPos > 195 && yPos < 205)
            {
                 if ( x > barChartX && x < barChartX + zoo[0][6]/2)
                 {
                      currentYear = 6;
                      currentZoo = 0;
                      isPoint = true;
                 }
            }
            else
            {
                isPoint = false;
            }
  }
  
// reposition the mouse value  
  xStart = x; 

// redisplay
  glutPostWindowRedisplay(gInfoWindow);
  glutPostWindowRedisplay(gLineChart);
  glutPostWindowRedisplay(gBarChart);
  glutPostWindowRedisplay(gPieChartZoo1);
  glutPostWindowRedisplay(gPieChartZoo2); 
}

void myMotionFuncLine(int x, int y)
{
// when mouse is drag up, increment value
// when mouse is drag down, decrement value
   if ( y > 0 && y < 300 && isPoint )
      zoo[currentZoo][currentYear] += (  yStart - y);

   if ( zoo[currentZoo][currentYear] < 0 )
      zoo[currentZoo][currentYear] = 0;
   else if ( zoo[currentZoo][currentYear] > 500)
      zoo[currentZoo][currentYear] = 500;

// redisplay
  glutPostWindowRedisplay(gInfoWindow);
  glutPostWindowRedisplay(gLineChart);
  glutPostWindowRedisplay(gBarChart);
  glutPostWindowRedisplay(gPieChartZoo1);
  glutPostWindowRedisplay(gPieChartZoo2);      
// reposition the y value  
  yStart = y;
}

void myMouseLine(int button, int state, int x, int y)
{
  int yInvert = 300 - y ;
  int yPos = yInvert - lineChartY   ; 
  int pixDiff = 8;
  isPoint = false;
  //if left mouse button pressed
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
  // when it is within the coordinate of the line chart.
            if ( x > lineChartX + 20 - pixDiff && x < lineChartX + 20 + pixDiff )
            {

                 if ( yPos > (zoo[0][0]/2.27) - pixDiff && yPos < (zoo[0][0]/2.27) + pixDiff)
                 {
                      currentYear = 0;
                      currentZoo = 0;
                      isPoint = true;
                 }
                 else if ( yPos > zoo[1][0]/2.27 - pixDiff && yPos < zoo[1][0]/2.27 + pixDiff)
                 {
                      currentYear = 0;
                      currentZoo = 1;
                      isPoint = true;
                 }     
                 else
                     isPoint = false;
            }
            else if ( x > lineChartX + 55 - pixDiff && x < lineChartX + 55 + pixDiff )
            {
                 if ( yPos > zoo[0][1]/2.27 - pixDiff && yPos < zoo[0][1]/2.27 + pixDiff)
                 {
                      currentYear = 1;
                      currentZoo = 0;
                      isPoint = true;
                 }
                 else if ( yPos > zoo[1][1]/2.27 - pixDiff && yPos < zoo[1][1]/2.27 + pixDiff)
                 {
                      currentYear = 1;
                      currentZoo = 1;
                      isPoint = true;
                 }
                 else
                     isPoint = false;     
            }
            else if ( x > lineChartX + 90 - pixDiff && x < lineChartX + 90 + pixDiff )
            {
                 if ( yPos > zoo[0][2]/2.27 - pixDiff && yPos < zoo[0][2]/2.27 + pixDiff)
                 {
                      currentYear = 2;
                      currentZoo = 0;
                      isPoint = true;
                 }
                 else if ( yPos > zoo[1][2]/2.27 - pixDiff && yPos < zoo[1][2]/2.27 + pixDiff)
                 {
                      currentYear = 2;
                      currentZoo = 1;
                      isPoint = true;
                 }   
                 else
                     isPoint = false;  
            }
            else if ( x > lineChartX + 125 - pixDiff && x < lineChartX + 125 + pixDiff )
            {
                 if ( yPos > zoo[0][3]/2.27 - pixDiff && yPos < zoo[0][3]/2.27 + pixDiff)
                 {
                      currentYear = 3;
                      currentZoo = 0;
                      isPoint = true;
                 }
                 else if ( yPos > zoo[1][3]/2.27 - pixDiff && yPos < zoo[1][3]/2.27 + pixDiff)
                 {
                      currentYear = 3;
                      currentZoo = 1;
                      isPoint = true;
                 } 
                 else
                     isPoint = false;    
            }
            else if ( x > lineChartX + 160 - pixDiff && x < lineChartX + 160 + pixDiff )
            {
                 if ( yPos > zoo[0][4]/2.27 - pixDiff && yPos < zoo[0][4]/2.27 + pixDiff)
                 {
                      currentYear = 4;
                      currentZoo = 0;
                      isPoint = true;
                 }
                 else if ( yPos > zoo[1][4]/2.27 - pixDiff && yPos < zoo[1][4]/2.27 + pixDiff)
                 {
                      currentYear = 4;
                      currentZoo = 1;
                      isPoint = true;
                 }  
                 else
                     isPoint = false;   
            }
            else if ( x > lineChartX + 195 - pixDiff && x < lineChartX + 195 + pixDiff )
            {
                 if ( yPos > zoo[0][5]/2.27 - pixDiff && yPos < zoo[0][5]/2.27 + pixDiff)
                 {
                      currentYear = 5;
                      currentZoo = 0;
                      isPoint = true;
                 }
                 else if ( yPos > zoo[1][5]/2.27 - pixDiff && yPos < zoo[1][5]/2.27 + pixDiff)
                 {
                      currentYear = 5;
                      currentZoo = 1;
                      isPoint = true;
                 } 
                 else
                     isPoint = false;    
            }
            else if ( x > lineChartX + 230 - pixDiff && x < lineChartX + 230 + pixDiff )
            {
                 if ( yPos > zoo[0][6]/2.27 - pixDiff && yPos < zoo[0][6]/2.27 + pixDiff)
                 {
                      currentYear = 6;
                      currentZoo = 0;
                      isPoint = true;
                 }
                 else if ( yPos > zoo[1][6]/2.27 - pixDiff && yPos < zoo[1][6]/2.27 + pixDiff)
                 {
                      currentYear = 6;
                      currentZoo = 1;
                      isPoint = true;
                 } 
                 else
                     isPoint = false;    
            }
            else
            {
                isPoint = false;
            }
  }
  
// redisplay
  glutPostWindowRedisplay(gInfoWindow);
  glutPostWindowRedisplay(gLineChart);
  glutPostWindowRedisplay(gBarChart);
  glutPostWindowRedisplay(gPieChartZoo1);
  glutPostWindowRedisplay(gPieChartZoo2); 

// reposition the mouse value
  yStart = y;
}


void info_display()
{
 // the side bar    
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.0f, 0.0f, 0.0f);
  winHeight = 600;

  glBegin(GL_LINES);
    glVertex2f(200.0f, 0.0f);  
    glVertex2f(200.0f, 600.0f);
    glVertex2f(0.0f, winHeight - 150);
    glVertex2f(winWidth, winHeight-150);
  glEnd();
  

  display_str(10, winHeight-20, GLUT_BITMAP_8_BY_13, "Currently Selected: ");
  display_str(10, winHeight-60, GLUT_BITMAP_8_BY_13, "Zoo: ");
  display_str(60, winHeight-60, GLUT_BITMAP_8_BY_13, currentZooStr(currentZoo) );
  display_str(10, winHeight-90, GLUT_BITMAP_8_BY_13, "Year: ");
  display_str(60, winHeight-90, GLUT_BITMAP_8_BY_13, currentYearStr(currentYear) );
  
  display_str(65, winHeight-180, GLUT_BITMAP_8_BY_13, "Zoo 1");
  display_str(135, winHeight-180, GLUT_BITMAP_8_BY_13, "Zoo 2");
    
  
  display_str(10, winHeight-210, GLUT_BITMAP_8_BY_13, "2005");
  display_str(75, winHeight-210, GLUT_BITMAP_8_BY_13, (char*)toString(zoo[0][0]).c_str());
  display_str(145, winHeight-210, GLUT_BITMAP_8_BY_13, (char*)toString(zoo[1][0]).c_str()); 
  display_str(10, winHeight-240, GLUT_BITMAP_8_BY_13, "2006");
  display_str(75, winHeight-240, GLUT_BITMAP_8_BY_13, (char*)toString(zoo[0][1]).c_str());
  display_str(145, winHeight-240, GLUT_BITMAP_8_BY_13, (char*)toString(zoo[1][1]).c_str()); 
  display_str(10, winHeight-270, GLUT_BITMAP_8_BY_13, "2007");
  display_str(75, winHeight-270, GLUT_BITMAP_8_BY_13, (char*)toString(zoo[0][2]).c_str());
  display_str(145, winHeight-270, GLUT_BITMAP_8_BY_13, (char*)toString(zoo[1][2]).c_str()); 
  display_str(10, winHeight-300, GLUT_BITMAP_8_BY_13, "2008");
  display_str(75, winHeight-300, GLUT_BITMAP_8_BY_13, (char*)toString(zoo[0][3]).c_str());
  display_str(145, winHeight-300, GLUT_BITMAP_8_BY_13, (char*)toString(zoo[1][3]).c_str()); 
  display_str(10, winHeight-330, GLUT_BITMAP_8_BY_13, "2009");
  display_str(75, winHeight-330, GLUT_BITMAP_8_BY_13, (char*)toString(zoo[0][4]).c_str());
  display_str(145, winHeight-330, GLUT_BITMAP_8_BY_13, (char*)toString(zoo[1][4]).c_str()); 
  display_str(10, winHeight-360, GLUT_BITMAP_8_BY_13, "2010");
  display_str(75, winHeight-360, GLUT_BITMAP_8_BY_13, (char*)toString(zoo[0][5]).c_str());
  display_str(145, winHeight-360, GLUT_BITMAP_8_BY_13, (char*)toString(zoo[1][5]).c_str()); 
  display_str(10, winHeight-390, GLUT_BITMAP_8_BY_13, "2011");
  display_str(75, winHeight-390, GLUT_BITMAP_8_BY_13, (char*)toString(zoo[0][6]).c_str());
  display_str(145, winHeight-390, GLUT_BITMAP_8_BY_13, (char*)toString(zoo[1][6]).c_str()); 

  glFlush();
}




void drawDiamond(float red, float green, float blue, float x, float y)
{
// drawing the diamond to indicate the point for line chart
  glColor3ub(static_cast<char>(red), static_cast<char>(green),static_cast<char>(blue));
  glBegin(GL_QUADS);
    glVertex2f(x, y+6);
    glVertex2f(x+6, y);
    glVertex2f(x , y -6 );
    glVertex2f ( x-6 , y);
  glEnd();
}    

void lineChart_display()
{
// the line chart
  winHeight = 300;  
     
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
  glClear (GL_COLOR_BUFFER_BIT);   
  glColor3f(0.0f, 0.0f, 0.0f);
 
  glBegin(GL_LINE_LOOP);
    glVertex2f ( 5.0f, 5.0f);
    glVertex2f ( 395.0f, 5.0f);
    glVertex2f ( 395.0f , 295.0f);
    glVertex2f ( 5.0f , 295.0f);
  glEnd();

  glColor3f( 0.0f, 0.0f, 0.0f);
  glBegin( GL_LINES);
  for ( int i = 0 ; i < 11 ; i ++ )
  {
      glVertex2f ( lineChartX - 5, lineChartY + ( i * 22) );
      glVertex2f ( 300, lineChartY + ( i * 22 ) );
  }
  glVertex2f ( lineChartX, lineChartY-5);
  glVertex2f ( lineChartX, 260);
  for ( int i = 1 ; i < 8 ; i ++ )
  {
      glVertex2f ( lineChartX + (i * 35), lineChartY-5);
      glVertex2f ( lineChartX + (i * 35), lineChartY);
  }
  glEnd();
 
  display_str(lineChartX-14, lineChartY, GLUT_BITMAP_8_BY_13, "0"); 
  display_str(lineChartX, lineChartY-17, GLUT_BITMAP_8_BY_13, "2005"); 
  display_str(lineChartX+35, lineChartY-17, GLUT_BITMAP_8_BY_13, "2006"); 
  display_str(lineChartX+70, lineChartY-17, GLUT_BITMAP_8_BY_13, "2007"); 
  display_str(lineChartX+105, lineChartY-17, GLUT_BITMAP_8_BY_13, "2008"); 
  display_str(lineChartX+140, lineChartY-17, GLUT_BITMAP_8_BY_13, "2009"); 
  display_str(lineChartX+175, lineChartY-17, GLUT_BITMAP_8_BY_13, "2010");
  display_str(lineChartX+210, lineChartY-17, GLUT_BITMAP_8_BY_13, "2011");  
  
  display_str(lineChartX-22, lineChartY+20, GLUT_BITMAP_8_BY_13, "50"); 
  display_str(lineChartX-30, lineChartY+42, GLUT_BITMAP_8_BY_13, "100"); 
  display_str(lineChartX-30, lineChartY+63, GLUT_BITMAP_8_BY_13, "150"); 
  display_str(lineChartX-30, lineChartY+85, GLUT_BITMAP_8_BY_13, "200"); 
  display_str(lineChartX-30, lineChartY+107, GLUT_BITMAP_8_BY_13, "250"); 
  display_str(lineChartX-30, lineChartY+128, GLUT_BITMAP_8_BY_13, "300"); 
  display_str(lineChartX-30, lineChartY+150, GLUT_BITMAP_8_BY_13, "350"); 
  display_str(lineChartX-30, lineChartY+172, GLUT_BITMAP_8_BY_13, "400"); 
  display_str(lineChartX-30, lineChartY+194, GLUT_BITMAP_8_BY_13, "450"); 
  display_str(lineChartX-30, lineChartY+216, GLUT_BITMAP_8_BY_13, "500"); 
  
  display_str(350, 160, GLUT_BITMAP_8_BY_13, "Zoo 1"); 
  display_str(350, 140, GLUT_BITMAP_8_BY_13, "Zoo 2"); 
 
  int red[4], green[4], blue[4] ;
  
  for ( int i = 0 ; i < 4 ; i ++ )
  {
      red[i] = colourPalette[i+9][0];
      green[i] = colourPalette[i+9][1];
      blue[i] = colourPalette[i+9][2];
  }

  glLineWidth(3.0);               // set the width of the line
  
  /*---- for zoo1 ------ */
  glColor3ub(static_cast<char>(red[1]), static_cast<char>(green[1]),static_cast<char>(blue[1]));
  glBegin( GL_LINES);
    glVertex2f(325, 165);
    glVertex2f(345, 165);
  glEnd();

  for ( int i = 0 ; i < 6 ; i ++ )
  {
      glBegin(GL_LINES);
        glVertex2f( barChartX + 15 + ( i * 35) , barChartY + zoo[0][i]/2.27 );
        glVertex2f( barChartX + 15 + ( (i+1)*35) , barChartY + zoo[0][i+1]/2.27);
      glEnd();
  }
  
  drawDiamond(red[0], green[0],blue[0], 335 , 165);
  for ( int i = 0 ; i < 7 ; i ++ )
  {
      drawDiamond( red[0],green[0],blue[0], barChartX + 15 + ( i *35 ) , barChartY + zoo[0][i]/2.27);
  }
  
  /*------ for zoo 2 ------ */
  glColor3ub(static_cast<char>(red[2]), static_cast<char>(green[2]),static_cast<char>(blue[2]));
  glBegin( GL_LINES);
    glVertex2f(325, 145);
    glVertex2f(345, 145);
  glEnd();  

  for ( int i = 0 ; i < 6 ; i ++ )
  {
      glBegin(GL_LINES);
        glVertex2f( barChartX + 15 + ( i * 35) , barChartY + zoo[1][i]/2.27 );
        glVertex2f( barChartX + 15 + ( (i+1)*35) , barChartY + zoo[1][i+1]/2.27);
      glEnd();
  }

  glPointSize(8.0);
  glColor3ub(static_cast<char>(red[3]), static_cast<char>(green[3]),static_cast<char>(blue[3]));
  glBegin(GL_POINTS);
    glVertex2f( 335, 145); 
    for ( int i = 0 ; i < 7 ; i ++ )
    {
          glVertex2f ( barChartX + 15 + ( i * 35), barChartY + zoo[1][i]/2.27);
    }
  glEnd();  

  glLineWidth(1.0);    // change back the width 

  
  glFlush();
}   
 
     
void barChart_display()
{  
// the bar chart
  winHeight = 300;   
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
  glClear (GL_COLOR_BUFFER_BIT);
     
  glColor3f(0.0f, 0.0f, 0.0f);
     
  glBegin(GL_LINE_LOOP);
    glVertex2f ( 5.0f, 5.0f);
    glVertex2f ( 395.0f, 5.0f);
    glVertex2f ( 395.0f , 295.0f);
    glVertex2f ( 5.0f , 295.0f);
  glEnd();
  
  glColor3f( 0.0f, 0.0f, 0.0f);
  
  glBegin( GL_LINES);
   glVertex2f ( barChartX-5, barChartY);
   glVertex2f ( winWidth-100, barChartY);  
   for ( int i = 0 ; i < 6 ; i++ )
   {
       glVertex2f ( barChartX + ( i * 50) , barChartY - 5 );
       glVertex2f ( barChartX + ( i * 50) , 250 );
   }
   for ( int i = 1 ; i < 8 ; i ++ )
   {
       glVertex2f ( barChartX , barChartY + ( i * 30 ) ) ;
       glVertex2f ( barChartX -5 , barChartY + ( i * 30 ) );
   }

  glEnd();
  
  display_str(barChartX-37, barChartY+13, GLUT_BITMAP_8_BY_13, "2005"); 
  display_str(barChartX-37, barChartY+43, GLUT_BITMAP_8_BY_13, "2006"); 
  display_str(barChartX-37, barChartY+73, GLUT_BITMAP_8_BY_13, "2007");
  display_str(barChartX-37, barChartY+103, GLUT_BITMAP_8_BY_13, "2008");
  display_str(barChartX-37, barChartY+133, GLUT_BITMAP_8_BY_13, "2009");
  display_str(barChartX-37, barChartY+163, GLUT_BITMAP_8_BY_13, "2010");
  display_str(barChartX-37, barChartY+193, GLUT_BITMAP_8_BY_13, "2011");
  
  display_str(barChartX-5, barChartY-20, GLUT_BITMAP_8_BY_13, "0");
  display_str(barChartX+40, barChartY-20, GLUT_BITMAP_8_BY_13, "100");
  display_str(barChartX+90, barChartY-20, GLUT_BITMAP_8_BY_13, "200");
  display_str(barChartX+140, barChartY-20, GLUT_BITMAP_8_BY_13, "300");
  display_str(barChartX+190, barChartY-20, GLUT_BITMAP_8_BY_13, "400");
  display_str(barChartX+240, barChartY-20, GLUT_BITMAP_8_BY_13, "500");
  
  display_str(350, 160, GLUT_BITMAP_8_BY_13, "Zoo 1"); 
  display_str(350, 140, GLUT_BITMAP_8_BY_13, "Zoo 2"); 
  
  int red1 = colourPalette[7][0];
  int green1 = colourPalette[7][1];
  int blue1 = colourPalette[7][2];
  
  glPointSize(10.0);
  glColor3ub(static_cast<char>(red1), static_cast<char>(green1),static_cast<char>(blue1));
  glBegin(GL_POINTS);
    glVertex2f( 340, 165); 
  glEnd();  
  /*--- for zoo 1 --- */
  for ( int i = 0 ; i < 7 ; i ++ )
  {
        glBegin(GL_QUADS);
          glVertex2f ( barChartX, barChartY + 25 + (i * 30) ) ;
          glVertex2f ( zoo[0][i]/2 + barChartX , barChartY + 25 + ( i * 30) );
          glVertex2f ( zoo[0][i]/2 + barChartX , barChartY + 15 + ( i * 30) ) ;
          glVertex2f ( barChartX, barChartY + 15 + ( i * 30 ) );
        glEnd();
  }
  
  int red2 = colourPalette[8][0];
  int green2 = colourPalette[8][1];
  int blue2 = colourPalette[8][2];
  
  glColor3ub(static_cast<char>(red2), static_cast<char>(green2),static_cast<char>(blue2));
  glBegin(GL_POINTS);
    glVertex2f( 340, 145); 
  glEnd(); 
  /* --- for zoo 2 --- */
  for ( int i = 0 ; i < 7 ; i ++ )
  {
        glBegin(GL_QUADS);
          glVertex2f ( barChartX, barChartY + 15 + (i * 30) ) ;
          glVertex2f ( zoo[1][i]/2 + barChartX , barChartY + 15 + ( i * 30) );
          glVertex2f ( zoo[1][i]/2 + barChartX , barChartY + 5 + ( i * 30) ) ;
          glVertex2f ( barChartX, barChartY + 5 + ( i * 30 ) );
        glEnd();
  } 
  
  glFlush();
}

void drawCircle( float red, float green, float blue, float x, float y, float r, float segmentation, int totalSegment)
{
// draw the circle for the pie chart
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(static_cast<char>(red), static_cast<char>(green),static_cast<char>(blue));
	glVertex2f (x,y);
	for ( int n=0; n<=segmentation; ++n)
	{
		float const t = 2*M_PI*(float) n/(float) totalSegment;
		glVertex2f(x + sin(t) * r, y + cos(t) *r );
	}	
	glEnd();
}


void pieChartZoo1_display()
{
// zoo1 pie chart
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
  glClear (GL_COLOR_BUFFER_BIT);
     
  glColor3f(0.0f, 0.0f, 0.0f);
     
  glBegin(GL_LINE_LOOP);
    glVertex2f ( 5.0f, 5.0f);
    glVertex2f ( 395.0f, 5.0f);
    glVertex2f ( 395.0f , 295.0f);
    glVertex2f ( 5.0f , 295.0f);
  glEnd();
  
  display_str(180, 270, GLUT_BITMAP_TIMES_ROMAN_24, "Zoo 1"); 
  display_str(350, 200, GLUT_BITMAP_8_BY_13, "2005");
  display_str(350, 180, GLUT_BITMAP_8_BY_13, "2006");
  display_str(350, 160, GLUT_BITMAP_8_BY_13, "2007");
  display_str(350, 140, GLUT_BITMAP_8_BY_13, "2008");
  display_str(350, 120, GLUT_BITMAP_8_BY_13, "2009");
  display_str(350, 100, GLUT_BITMAP_8_BY_13, "2010");
  display_str(350, 80, GLUT_BITMAP_8_BY_13, "2011");
  
  int yPos = 82;
  int temp = 0;
  int sumOfBanana = 0;
  for ( int i = 0 ; i < 7 ; i++ )
  {
      sumOfBanana = sumOfBanana + zoo[0][i] ;
  }
  for ( int i = 0 ; i < 7 ; i ++  )
  {
      glPointSize(10.0);
      int red = colourPalette[i][0];
      int green = colourPalette[i][1];
      int blue = colourPalette[i][2];
      glColor3ub(static_cast<char>(red), static_cast<char>(green),static_cast<char>(blue));
      glBegin(GL_POINTS);
        glVertex2f( 330, yPos); 
      glEnd(); 
      yPos += 20;
      
      float abc = (sumOfBanana-temp)/1.0;
      float angle = abc / (sumOfBanana*1.0) * 360.0 ;    // calculate the angle needed
      drawCircle ( red, green, blue, 200, 140 , 100 ,  angle    , 360 );

      temp = temp + zoo[0][6-i];     // adding up those value which used before in calculation
  }     
  glFlush();
}

void pieChartZoo2_display()
{
// zoo2 pie chart
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
  glClear (GL_COLOR_BUFFER_BIT);
     
  glColor3f(0.0f, 0.0f, 0.0f);
     
  glBegin(GL_LINE_LOOP);
    glVertex2f ( 5.0f, 5.0f);
    glVertex2f ( 395.0f, 5.0f);
    glVertex2f ( 395.0f , 295.0f);
    glVertex2f ( 5.0f , 295.0f);
  glEnd();
  
  display_str(180, 270, GLUT_BITMAP_TIMES_ROMAN_24, "Zoo 2"); 
  display_str(350, 200, GLUT_BITMAP_8_BY_13, "2005");
  display_str(350, 180, GLUT_BITMAP_8_BY_13, "2006");
  display_str(350, 160, GLUT_BITMAP_8_BY_13, "2007");
  display_str(350, 140, GLUT_BITMAP_8_BY_13, "2008");
  display_str(350, 120, GLUT_BITMAP_8_BY_13, "2009");
  display_str(350, 100, GLUT_BITMAP_8_BY_13, "2010");
  display_str(350, 80, GLUT_BITMAP_8_BY_13, "2011");
  
  int yPos = 82;
  
  int sumOfBanana = 0;
  for ( int i = 0 ; i < 7 ; i++ )
  {
      sumOfBanana = sumOfBanana + zoo[1][i] ;
  }
  int temp = 0;
  for ( int i = 0 ; i < 7 ; i ++ )
  {
      glPointSize(10.0);
      int red = colourPalette[i][0];
      int green = colourPalette[i][1];
      int blue = colourPalette[i][2];
      glColor3ub(static_cast<char>(red), static_cast<char>(green),static_cast<char>(blue));
      glBegin(GL_POINTS);
        glVertex2f( 330, yPos); 
      glEnd(); 
      yPos += 20;
      
      float abc = (sumOfBanana-temp)/1.0;
      float angle = abc / (sumOfBanana*1.0) * 360.0 ;     // calculate the angle needed
      drawCircle ( red, green, blue, 200, 140 , 100 ,  angle    , 360 );

      temp = temp + zoo[1][6-i];     // adding up those value which used before in calculation
  }    
  
  glFlush();
}

void displayMenu()
{
// what is to be shown in the menu when right click     

  int sub_menu = glutCreateMenu(myMenu);
  glutAddMenuEntry("Year", 0);
  glutAddMenuEntry("", 0);
  glutAddMenuEntry("2005", 'q');
  glutAddMenuEntry("2006", 'w');
  glutAddMenuEntry("2007", 'e');
  glutAddMenuEntry("2008", 'r');
  glutAddMenuEntry("2009", 't');
  glutAddMenuEntry("2010", 'y');
  glutAddMenuEntry("2011", 'u');
  
  int sub_menu2 = glutCreateMenu(myMenu);
  glutAddMenuEntry("Year", 0);
  glutAddMenuEntry("", 0);
  glutAddMenuEntry("2005", 'a');
  glutAddMenuEntry("2006", 's');
  glutAddMenuEntry("2007", 'd');
  glutAddMenuEntry("2008", 'f');
  glutAddMenuEntry("2009", 'g');
  glutAddMenuEntry("2010", 'h');
  glutAddMenuEntry("2011", 'j');

  int main_menu = glutCreateMenu(myMenu);
  glutAddMenuEntry("Main Menu", 0);
  glutAddMenuEntry("", 0);
  glutAddSubMenu("Zoo 1", sub_menu);
  glutAddSubMenu("Zoo 2", sub_menu2);
  glutAddMenuEntry("Random Data" , 2 );
  glutAddMenuEntry("Random Colour" , 3);
  glutAddMenuEntry("Quit", 1);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char* argv[])
{       
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);      //requests properties for the window (sets up the rendering context)
  glutInitWindowSize(1000, 600);			            //set window size in pixels
  glutInitWindowPosition(50, 100);                  //set window position from top-left corner of display
  gMainWindow = glutCreateWindow("Statistic");	//set window title
  glutReshapeFunc(reshape);
  glutDisplayFunc(main_display);
  srand(time(NULL));
  initData(zoo);
  initColour(colourPalette);
  glutKeyboardFunc(myKeypress);
  glutSpecialFunc(mySpecialKeys);

  
  
  gInfoWindow = glutCreateSubWindow(gMainWindow, 0, 0, 200, 600);
  glutReshapeFunc(reshape);
  glutDisplayFunc(info_display);
  displayMenu();
  
  
  gLineChart = glutCreateSubWindow(gMainWindow, 200, 0, 400, 300);
  glutReshapeFunc(reshape);
  glutDisplayFunc(lineChart_display);
  displayMenu();
  glutMouseFunc(myMouseLine);
  glutMotionFunc(myMotionFuncLine);   
  
  gBarChart = glutCreateSubWindow(gMainWindow, 600, 0 , 400, 300);
  glutReshapeFunc(reshape);
  glutDisplayFunc(barChart_display);
  displayMenu();
  glutMouseFunc(myMouseBar);
  glutMotionFunc(myMotionFuncBar);  
  
  
  gPieChartZoo1 = glutCreateSubWindow(gMainWindow, 200, 300 , 400, 300);
  glutReshapeFunc(reshape);
  glutDisplayFunc(pieChartZoo1_display);  
  displayMenu();
  
  
  gPieChartZoo2 = glutCreateSubWindow(gMainWindow, 600, 300 , 400, 300);
  glutReshapeFunc(reshape);
  glutDisplayFunc(pieChartZoo2_display);    
  displayMenu();
 

  glutMainLoop();                                   //enter event loop
}
