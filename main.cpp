#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

#define sqrt2 (sqrt(2))

typedef struct point
{
	double x,y,z;
}Point;

bool drawAxes = true;
float tyreAngle = 0;
float tyreAngle1 = 90;

float quadAngle = 0;
float quadAngle1 = 0;
float quadAngle2 = 0;
float boxAngle = 0;
float boxScaleFactor = 1;
float tyreScaleFactor = 1;
float tinyBoxAngle = 0;
float background = 0;
float sli=0;
float slidoor1=57;
float slidoor2=-57;
int cntu=0;
int cntd=0;
int flg= 0;


float x=600;
float y=600;
float z=120;


Point pos, u, r, l;

void posit()
{
    pos = {x, y, z};
}

void init(){
    glClearColor(background, background, background,0); 	//sets background color

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity(); // sets the current matrix to identity
    gluPerspective(80,	1,	1,	1000.0);

	// to understand the following values, read the specification pdf
    double d = 1 / sqrt2;
    posit();
    u = {0, 0, 1};
    r = {-d, d, 0};
    l = {-d, -d, 0};
}

void displayAxes()
{
	if(drawAxes)
	{
		glBegin(GL_LINES);
		{
		    glColor3f(1.0, 0, 0);

			glVertex3f( 1000,0,0); // a point on pos x axis
			glVertex3f(-1000,0,0); // a point on neg x axis

			glColor3f(0, 1.0, 0);

			glVertex3f(0,-1000,0); // a point on pos y axis
			glVertex3f(0, 1000,0); // a point on neg y axis

			glColor3f(0, 0, 1.0);

			glVertex3f(0,0, 1000);  // a point on pos z axis
			glVertex3f(0,0,-1000);   // a point on neg z axis
		}
		glEnd();
	}
}

Point func(Point vect, Point perp, int dir)
{
    double c = cos(pi/180);
    double s = dir * sin(pi/180);
    Point point;
    point.x = c * vect.x + s * perp.x;
    point.y = c * vect.y + s * perp.y;
    point.z = c * vect.z + s * perp.z;
    c = sqrt(point.x*point.x + point.y*point.y + point.z*point.z);
    point.x /= c;
    point.y /= c;
    point.z /= c;
    return point;
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){
		case '1': {
            Point l1 = func(l, r, -1);
            r = func(r, l, 1);
            l = l1;
            break;
		}
		case '2': {
            Point l1 = func(l, r, 1);
            r = func(r, l, -1);
            l = l1;
            break;
		}

		case '3': {
            Point u1 = func(u, l, -1);
            l = func(l, u, 1);
            u = u1;
            break;
        }
        case '4': {
            Point u1 = func(u, l, 1);
            l = func(l, u, -1);
            u = u1;
            break;
        }
        case '5': {
            Point r1 = func(r, u, -1);
            u = func(u, r, 1);
            r = r1;
            break;
        }
        case '6':{
            Point r1 = func(r, u, 1);
            u = func(u, r, -1);
            r = r1;
            break;
        }
        ///rotating window open
        case '9': {
            if (quadAngle< 12)
            {quadAngle += 1;
		        printf("Quad Angle %f\n", quadAngle);

            break;
            }
            else
                break;
        }

        ///rotating window close
        case '0': {
            if (quadAngle> 0)
            {
            quadAngle -= 1;
            printf("Quad Angle %f\n", quadAngle);
            break;

            }
            else
             break;
        }
        ///rotate anticlockwise
        case 'r': {
           boxAngle += 4;
            printf("Box Angle %f\n", boxAngle);
            break;
        }///rotate clockwise
        case 'l':{
            boxAngle -= 4;
            printf("Box Angle %f\n", boxAngle);
            break;
        }
        ///scale up
        case 'u':{
           boxScaleFactor += 0.2;
           cntu++;

                break;
        }///scale down
        case 'd':{
            if(boxScaleFactor>=0.2)
            {
             boxScaleFactor -= 0.2;
             cntd++;
            }
            break;
        }
		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN: // down arrow
		    {
                boxScaleFactor-=.02;
                break;

		    }

		case GLUT_KEY_UP:   // up arrow
		    {
		        boxScaleFactor+=.02;
                break;

		    }

        ///camera moves to right
		case GLUT_KEY_RIGHT:    // right arrow
		    {

                Point l1 = func(l, r, 1);
            r = func(r, l, 0);
            l = l1;
            boxAngle-=1.5;

            break;
		    }

        ///camera moves to left
		case GLUT_KEY_LEFT:     // left arrow
		    {
		        Point l1 = func(l, r, -1);
            r = func(r, l, 0);
            l = l1;
            boxAngle+=1.5;
            break;
		    }
        ///camera moves up
		case GLUT_KEY_PAGE_UP:
		    {
                Point u1 = func(u, l, -1);
            l = func(l, u,1);
            u = u1;


            break;
		    }

        ///camera moves down
		case GLUT_KEY_PAGE_DOWN:
		    {
		      Point u1 = func(u, l, 1);
            l = func(l, u, -1);
            u = u1;

            break;
		    }

        ///Slide door opens
		case GLUT_KEY_HOME:
		    {
		        if(slidoor1<100)
                {
                 slidoor1 += 30;
		        slidoor2 -= 30;
                }



		         break;
		    }
        ///Slide door close
        case GLUT_KEY_END:
            {
                if(slidoor1>57)
                {
                slidoor1 -= 30;
		        slidoor2 += 30;
                }

		        break;
            }

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN) // 2 times?? in ONE click? -- solution is checking DOWN or UP
            {
                printf("Mouse Left Button Clicked\n");
			}
			else if(state == GLUT_UP)
            {
                printf("Mouse Left Button Released\n");
            }
            break;
		default:
			break;
	}
}

void displayTyre(float tyreRadius, float tyreWidth)
{
    int tyreSlices = 36;
    float sliceWidth = (2 * M_PI * tyreRadius) / 12;
    float sliceAngle = 360 / 12;

    float halfTyreWidth = tyreWidth / 2, quartTyreWidth = halfTyreWidth / 2;
    float halfSliceWidth = sliceWidth / 2;

    /*glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(halfTyreWidth, tyreRadius, 0);
        glVertex3f(-halfTyreWidth, tyreRadius, 0);
        glVertex3f(-halfTyreWidth, -tyreRadius, 0);
        glVertex3f(halfTyreWidth, -tyreRadius, 0);
    }
    glEnd();*/

glRotatef(30, 1, 0, 0);
    glColor3f(0.25, 0.5, 1);
    for(int i=1; i<tyreSlices; i++)
    {
        if ((i%2)==0)
         {glColor3f(0.92, .50, .20);
         glPushMatrix();
        //  glRotatef(30, 1, 0, 0);
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, -45);
        glBegin(GL_QUADS);
        {
            glVertex3f(halfTyreWidth, -90, halfSliceWidth/2);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, -90, halfSliceWidth/2);

        }
        glEnd();
        glPopMatrix();}

        else
            {glColor3f(0.92, .50, .20);
        glPushMatrix();
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, -45);
        glBegin(GL_QUADS);
        {
            glVertex3f(halfTyreWidth, -90, halfSliceWidth/2);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, -90, halfSliceWidth/2);
        }
        glEnd();
        glPopMatrix();}
    }
}
void displayTyre2(float tyreRadius, float tyreWidth)
{
    int tyreSlices = 36;
    float sliceWidth = (2 * M_PI * tyreRadius) / 12;
    float sliceAngle = 360 / 12;

    float halfTyreWidth = tyreWidth / 2, quartTyreWidth = halfTyreWidth / 2;
    float halfSliceWidth = sliceWidth / 2;

    /*glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(halfTyreWidth, tyreRadius, 0);
        glVertex3f(-halfTyreWidth, tyreRadius, 0);
        glVertex3f(-halfTyreWidth, -tyreRadius, 0);
        glVertex3f(halfTyreWidth, -tyreRadius, 0);
    }
    glEnd();*/

glRotatef(30, 1, 0, 0);
    glColor3f(0.25, 0.5, 1);
    for(int i=1; i<=tyreSlices; i++)
    {
        if ((i%2)==0)
         {glColor3f(1, 0, 0);
         glPushMatrix();
        //  glRotatef(30, 1, 0, 0);
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, 0);
        glBegin(GL_QUADS);
        {
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
        }
        glEnd();
        glPopMatrix();}

        else
            {glColor3f(0, 0, 1);
        glPushMatrix();
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, 0);
        glBegin(GL_QUADS);
        {
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
        }
        glEnd();
        glPopMatrix();}
    }
}
void displayTyre3(float tyreRadius, float tyreWidth)
{
    int tyreSlices = 36;
    float sliceWidth = (2 * M_PI * tyreRadius) / 12;
    float sliceAngle = 360 / 12;

    float halfTyreWidth = tyreWidth / 2, quartTyreWidth = halfTyreWidth / 2;
    float halfSliceWidth = sliceWidth / 2;

    /*glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(halfTyreWidth, tyreRadius, 0);
        glVertex3f(-halfTyreWidth, tyreRadius, 0);
        glVertex3f(-halfTyreWidth, -tyreRadius, 0);
        glVertex3f(halfTyreWidth, -tyreRadius, 0);
    }
    glEnd();*/

glRotatef(30, 1, 0, 0);
    glColor3f(0.25, 0.5, 1);
    for(int i=1; i<=tyreSlices; i++)
    {
        if ((i%2)==0)
         {glColor3f(1, 0, 0);
         glPushMatrix();
        //  glRotatef(30, 1, 0, 0);
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, 0);
        glBegin(GL_QUADS);
        {
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
        }
        glEnd();
        glPopMatrix();}

        else
            {glColor3f(0, 0, 1);
        glPushMatrix();
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, 0);
        glBegin(GL_QUADS);
        {
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
        }
        glEnd();
        glPopMatrix();}
    }
}

void displayQuad(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;

    glBegin(GL_QUADS);
    {
        /** Solid Fill Quad **/

        //glColor3f(1, 1, 0);

        //glVertex3f(halfQuadWidth, 0, halfQuadLength);
        //glVertex3f(halfQuadWidth, 0, -halfQuadLength);
        //glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        //glVertex3f(-halfQuadWidth, 0, halfQuadLength);

        /** Gradient Fill Quad **/


        glColor3f(1,0,1);

        glVertex3f(halfQuadWidth, 0, halfQuadLength);
        glVertex3f(halfQuadWidth, 0, -halfQuadLength);

        glColor3f(0, 0, 1);

        glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, halfQuadLength);


    }
    glEnd();
}

void displayBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.78, 0.1, 0.1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);



        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.58, 0.13, 0.13);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);


        glColor3f(0.78, 0.1, 0.1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayBox2(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.20, 0.92, 0.88);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.20, 0.92, 0.88);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.20, 0.92, 0.88);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}
void displayBox3(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.90, 0.92, 0.20);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.90, 0.92, 0.20);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.90, 0.92, 0.20);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}
//*******************************************************************
void displayBox1(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.21, 0.69, 0.09);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.16, 0.54, 0.07);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);


        glColor3f(0.21, 0.69, 0.09);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}
void displayBox4(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.20, 0.57, 0.92);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.20, 0.57, 0.92);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);


        glColor3f(0.20, 0.57, 0.92);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}
//************************************************************************
void displayBox5(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0, 0, 0.1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glColor3f(0.20, 0.92, 0.88);

        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);



        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glColor3f(0, 0, 0.1);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.20, 0.92, 0.88);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glColor3f(0, 0, 0.1);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glColor3f(0, 0, 0.1);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.20, 0.92, 0.88);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glColor3f(0, 0, 0.1);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glColor3f(0, 0, 0.1);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}
//************************************************************************
void displayBox6(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.1,0,0);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glColor3f(0.8, 0.4, 0.9);

        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glColor3f(.1,0,0);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.7, 0.4, 0.9);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glColor3f(.1,0,0);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glColor3f(.1,0,0);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);


        glColor3f(0.7, 0.4, 0.9);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glColor3f(.1,0,0);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glColor3f(.1,0,0);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}


void displayScene()
{
    //Primitive Object dimensions

    float quadLength = 250, quadWidth = 150;
    float largeBoxLength = 450, largeBoxWidth = 230, largeBoxHeight = 400;
    float smallBoxLength = 480, smallBoxWidth = 250, smallBoxHeight = 20;
    float lbBoxLength = 480, lbBoxWidth = 250, lbBoxHeight = 40;
    float tinyBoxLength = 10, tinyBoxWidth = 10, tinyBoxHeight = 10;
    float tyreRadius = 140, tyreWidth = 50;


    /** Principal Axes **/



    /**/

    /** Quad **/


    /*glRotatef(quadAngle, 1, 0, 0); // rotates with respect to x axis
    glRotatef(quadAngle, 0, 1, 0); // rotates with respect to y axis
    glRotatef(quadAngle, 0, 0, 1); // rotates with respect to z axis

    displayQuad(quadLength, quadWidth);
    glTranslatef(0, 0, 50);*/



    /**/

    /** Single Box **/

    //glTranslatef(150, 0, 0); // rotation applied first, translation applied second
    //glRotatef(boxAngle, 1, 0, 0); // rotates with respect to x axis
    //glRotatef(boxAngle, 0, 1, 0); // rotates with respect to y axis
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    //glTranslatef(150, 0, 0);    // translation applied first, rotation applied second
    //displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight);

    /**/

    /** Double Box Stack **/

    //glRotatef(boxAngle, 0, 0, 1); // rotation applied to both boxes
    //glTranslatef(-300, 100, 100); // translation applied to both boxes
    //displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    //glRotatef(boxAngle, 0, 0, 1);   // rotation applied only on the small box
    //glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    //displayBox(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box

    /**/

    /** Double Box Stack - Push Pop Matrix **/
    glRotatef(boxAngle, 0, 0, 1);
    //glRotatef(quadAngle2, 0, 0, 1);
    glRotatef(boxScaleFactor,1,.5,.5);
     // rotation applied to both boxes
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    displayAxes();
    glPushMatrix(); // saves the matrix just before scaling, to prevent scale effect to anything other than the large box
    // without push-pop, scale will be applied to both boxes
    glTranslatef(0, 0, 0);
    displayBox(largeBoxLength+20, largeBoxWidth+10, largeBoxHeight+10); // large box
    //top
    glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    displayBox2(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box



    //base
    glTranslatef(0, 0, -(smallBoxHeight/2) - 2*(largeBoxHeight/2)); // places the small box on top of the large box
    displayBox1(smallBoxLength+10, smallBoxWidth, smallBoxHeight*3); // small box
    glPopMatrix();
    //roof
    glTranslatef(0, -20,(smallBoxHeight/2) +1.9* (largeBoxHeight/2)); // places the small box on top of the large box
    displayBox1(tinyBoxLength*35, tinyBoxWidth*5, tinyBoxHeight*35); // small box
//stair
    glPushMatrix();
    glTranslatef(0, (smallBoxWidth-25),-30*smallBoxHeight); // places the small box on top of the large box
    displayBox2(smallBoxLength/1.5, (smallBoxWidth-50), smallBoxHeight); // small box
    glTranslatef(0, (-smallBoxWidth/10),smallBoxHeight); // places the small box on top of the large box
    displayBox3(smallBoxLength/2, (smallBoxWidth-100), smallBoxHeight); // small box
    glTranslatef(0, (-smallBoxWidth/20),smallBoxHeight); // places the small box on top of the large box
    displayBox4(smallBoxLength/2.5, (smallBoxWidth-150), smallBoxHeight); // small box
    glPopMatrix();
    //door
glPushMatrix();
    glTranslatef(slidoor1, 150, -(smallBoxHeight/2) - 2*(largeBoxHeight/2)-10);
    displayBox6(largeBoxLength/4,1,largeBoxHeight/1.5);
glPopMatrix();
glPushMatrix();
    glTranslatef(slidoor2, 150, -(smallBoxHeight/2) - 2*(largeBoxHeight/2)-10);
    displayBox6(largeBoxLength/4,1,largeBoxHeight/1.5);
glPopMatrix();
//door-bar
glPushMatrix();
    glTranslatef(0, 150, -29*(smallBoxHeight/2));
    displayBox2(largeBoxLength/2,30,10);
glPopMatrix();
//window-left
glPushMatrix();
    glTranslatef(250, 0, -(smallBoxHeight/2) -350);
    glTranslatef(largeBoxLength/8,0,largeBoxHeight/5);
    glRotated(quadAngle,0,-1,0);
    glTranslatef(-largeBoxLength/8,0,-largeBoxHeight/5);
    glRotated(90,0,0,1);
    displayBox3(largeBoxLength/4,1,largeBoxHeight/2.5);
glPopMatrix();
//window-left-bar
glPushMatrix();
    glTranslatef(250, 0, -(smallBoxHeight/2) -275);
    glRotated(90,0,0,1);
    displayBox2(largeBoxLength/4,30,10);
glPopMatrix();

 //back-door
glPushMatrix();

    glTranslatef(57, -100, -(smallBoxHeight/2) - 2*(largeBoxHeight/2)-10);
    glTranslatef(largeBoxLength/8,0,largeBoxHeight/3);
    glRotated(quadAngle1,0,0,1);
    glTranslatef(-largeBoxLength/8,0,-largeBoxHeight/3);
    displayBox5(largeBoxLength/4,1,largeBoxHeight/1.5);
glPopMatrix();

glPushMatrix();
    glTranslatef(-57, -100, -(smallBoxHeight/2) - 2*(largeBoxHeight/2)-10);
    glTranslatef(-largeBoxLength/8,0,largeBoxHeight/3);
    glRotated(quadAngle1,0,0,-1);


    glTranslatef(largeBoxLength/8,0,-largeBoxHeight/3);
    displayBox5(largeBoxLength/4,1,largeBoxHeight/1.5);
glPopMatrix();

//back-door-bar
glPushMatrix();
    glTranslatef(0, -100, -29*(smallBoxHeight/2));
    displayBox2(largeBoxLength/2,30,10);
glPopMatrix();
//window-right
glPushMatrix();

    glTranslatef(-250, 0, -(smallBoxHeight/2) -350);
    glTranslatef(0,0,sli);
    glRotated(90,0,0,1);
    displayBox3(largeBoxLength/4,1,largeBoxHeight/2.5);
glPopMatrix();
//window-right-bar
glPushMatrix();
    glTranslatef(-250, 0, -(smallBoxHeight/2) -275);
    glRotated(90,0,0,1);
    displayBox2(largeBoxLength/4,30,10);
glPopMatrix();
//exhaust-fan
    // roates the tyre w.r.t z axis
    glPushMatrix();
    glTranslatef(0, tyreWidth, tyreWidth/10); // places the tyre on top of both boxes
    glRotatef(tyreAngle1, 0, 0, 1); // check what happens to the tyre after exchanging the order of translation and roation
    //glScalef(tyreScaleFactor, tyreScaleFactor, tyreScaleFactor);
     glRotatef(tyreAngle, 1, 0, 0);
     displayTyre2(tyreRadius+20, tyreWidth);
    displayTyre3((tyreRadius/2)-10, tyreWidth);
     // roates the tyre w.r.t x axis
    displayTyre(tyreRadius, tyreWidth);
    //displaytyre1(tyreRadius, tyreWidth);


    glPopMatrix();


    /**/

    /** Tyre **/

    /*glRotatef(tyreAngle, 1, 0, 0); // roates the tyre w.r.t x axis
    glRotatef(tyreAngle, 0, 1, 0); // roates the tyre w.r.t y axis
    glRotatef(tyreAngle, 0, 0, 1); // roates the tyre w.r.t z axis
    displayTyre(tyreRadius, tyreWidth);
    */
    /**/

    /** Tyre Double Box Stack **/

    /*glPushMatrix();
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    displayBox(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 0, tyreRadius+smallBoxHeight+(largeBoxHeight/2)); // places the tyre on top of both boxes
    glRotatef(tyreAngle, 1, 0, 0); // check what happens to the tyre after exchanging the order of translation and roation
    glScalef(tyreScaleFactor, tyreScaleFactor, tyreScaleFactor);
    displayTyre(tyreRadius, tyreWidth);
    glPopMatrix();
    */

    /** Animate Function **/
   /* glPushMatrix();
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    displayBox(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 0, tyreRadius+smallBoxHeight+(largeBoxHeight/2)); // places the tyre on top of both boxes
    glRotatef(tyreAngle, 1, 0, 0); // check what happens to the tyre after exchanging the order of translation and roation
    glScalef(tyreScaleFactor, tyreScaleFactor, tyreScaleFactor);
    displayTyre(tyreRadius, tyreWidth); // tyre
    glPopMatrix();

    glPushMatrix();
    glRotatef(tinyBoxAngle, 0, 0, 1); // angle is updated in animate function
    glTranslatef(250, 40, 50);
    displayBox(tinyBoxLength, tinyBoxWidth, tinyBoxHeight);
    glPopMatrix();*/
}

void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(background, background, background,0);	//sets background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // sets the current matrix to identity
    gluLookAt(pos.x, pos.y, pos.z, pos.x+l.x, pos.y+l.y, pos.z+l.z, u.x, u.y, u.z); // sets camera position and direction

    displayScene();

	glutSwapBuffers();
}



void animate(){
    if(flg == 1)
    {
     tyreAngle -= 1.5;

    }
    else if(flg == 2 )
    {
    tyreAngle += 0.5;

    }
    glutPostRedisplay();

}



void subMenu(int id)
{
     if(id == 3)
    {

         sli=140;


    }
     else if(id == 4)
    {

         sli=0;


    }
    else if(id == 5)
    {
            {quadAngle1 =100;
		        printf("Quad Angle %f\n", quadAngle1);


            }


    }
      else if(id == 6)
    {

            {quadAngle1 = 0;
		        printf("Quad Angle %f\n", quadAngle1);


            }

    }
    else if(id == 7)
    {
         flg=1;
    }
    else if(id == 8)
    {
         flg=2;
    }
    else if (id==10)
    {
        flg=0;
    }
}

void mainMenu(int id)
{
   /* if(id == 1)
    {
        drawAxes = true;
    }
    else if(id == 2)
    {
        drawAxes = false;
    }
*/
      if(id == 9)
    {
        float sf=cntu-cntd;
        if(sf>0)
        {
            boxScaleFactor=boxScaleFactor-(0.2*sf);
        }
        else if(sf<0)
        {
           sf=sf*(-1.0);
            boxScaleFactor=boxScaleFactor+(0.2*sf);
        }

    }



}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	int subMenuNo = glutCreateMenu(subMenu);
    glutAddMenuEntry("Slide Up", 3);
	glutAddMenuEntry("Slide Down", 4);
    int subMenuNo1= glutCreateMenu(subMenu);
    glutAddMenuEntry("Open", 5);
	glutAddMenuEntry("Close", 6);
	int subMenuNo2= glutCreateMenu(subMenu);
	glutAddMenuEntry("Clockwise", 7);
	glutAddMenuEntry("Anticlockwise", 8);
	glutAddMenuEntry("Stop",10);
    glutCreateMenu(mainMenu);
	//glutAddMenuEntry("Axes On", 1);
	//glutAddMenuEntry("Axes Off", 2);
    //glutAddSubMenu("Background", subMenuNo);
    glutAddSubMenu("Sliding Window",subMenuNo);

	glutAddSubMenu("Rotating Door",subMenuNo1);
    glutAddMenuEntry("Original Size",9);
    glutAddSubMenu("Exhaust Fan",subMenuNo2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();		//The main loop of OpenGL, this function never returns

	return 0;
}
