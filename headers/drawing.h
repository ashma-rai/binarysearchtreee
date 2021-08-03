#ifndef DRAWING_H_INCLUDED
#define DRAWING_H_INCLUDED
#include<GL/glut.h>
#define RADNODE 50
#include<math.h>
#include<stdlib.h>
float theta;
char keyPressed[5];
void drawNodeText(int,int,int);
void drawNode(int,int,int);
void drawBranch(int,int,int);
void drawSearchedNode(int,int);
bool searchedBlinkRed=false;
struct arrayNodeStruct{
    int posX,posY;
    char value[5];
    int val;
    int prevposX,prevposY;
    };
arrayNodeStruct arrayNode[100];
int arrayIndex=0;

void drawNodeAndText(int posX,int posY,int index)
{
    drawNode(posX,posY,index);
    drawNodeText(posX,posY,index);
    //if(boolDrawBranch) drawBranch(posX,posY,index);
}

void drawSearchedNode(int posX,int posY){
 {   if(searchedBlinkRed)
        glColor3f(0.9,0,0);
    else glColor3f(0,0,0);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i++)
        {   theta = i;
            glVertex2f(posX+5 +(RADNODE)*cos(theta),posY-5 +(RADNODE)*sin(theta));
        }
        glEnd();
    }
    //dark
    {   glColor3ub(22,68,90);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i++)
        {   theta = i;
            glVertex2f(posX +(RADNODE-3)*cos(theta),posY +(RADNODE-3)*sin(theta));
        }
        glEnd();
    }
    //skyblue
    {   glColor3ub(162,210,232);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i++)
        {   theta = i;
            glVertex2f(posX +(RADNODE-8)*cos(theta),posY +(RADNODE-8)*sin(theta));
        }
        glEnd();
    }
    //white
    {   glColor3ub(255,255,255);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i++)
        {   theta = i;
            glVertex2f(posX +(RADNODE-15)*cos(theta),posY +(RADNODE-15)*sin(theta));
        }
        glEnd();
    }

}
void drawBranch(int posX,int posY,int index)
{   if(index!=0)
{   glLineWidth(5);
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(posX,posY);
    glVertex2f(arrayNode[index].prevposX,arrayNode[index].prevposY);
    glEnd();
    /*glLineWidth(2);
    glColor3ub(162,210,232);
    glBegin(GL_LINES);
    glVertex2f(posX,posY);
    glVertex2f(arrayNode[index].prevposX,arrayNode[index].prevposY);
    glEnd();
    */
}

}


void drawNode(int posX,int posY,int index)//draws ball
{
   /* {   glColor3ub(58,62,78);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i++)
        {   theta = i;
            glVertex2f(posX+10 +RADNODE*cos(theta),posY -10+RADNODE*sin(theta));
        }
        glEnd();
    }
    */

    {   glColor3f(0,0,0);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i++)
        {   theta = i;
            glVertex2f(posX+5 +(RADNODE)*cos(theta),posY-5 +(RADNODE)*sin(theta));
        }
        glEnd();
    }
    //dark
    {   glColor3ub(22,68,90);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i++)
        {   theta = i;
            glVertex2f(posX +(RADNODE-3)*cos(theta),posY +(RADNODE-3)*sin(theta));
        }
        glEnd();
    }
    //skyblue
    {   glColor3ub(162,210,232);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i++)
        {   theta = i;
            glVertex2f(posX +(RADNODE-8)*cos(theta),posY +(RADNODE-8)*sin(theta));
        }
        glEnd();
    }
    //white
    {   glColor3ub(255,255,255);
        glBegin(GL_POLYGON);
        for(int i=0; i<360; i++)
        {   theta = i;
            glVertex2f(posX +(RADNODE-15)*cos(theta),posY +(RADNODE-15)*sin(theta));
        }
        glEnd();
    }


}

void drawNodeText(int posX,int posY,int index)
{
    //arrayNode[arrayIndex].value=itoa(arrayNode[arrayIndex].val,arrayNode[arrayIndex].value,10);
    //std::cout<<"converted int val to char *value"<<endl;
    int tempX=posX;
    int i=0;
    glColor3f(0,0,0);
        while(arrayNode[index].value[i]!='\0')
        {
            glRasterPos2i(tempX-20,posY-10);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,arrayNode[index].value[i]);
            tempX+=18;
            i++;
        }
}

#endif // DRAWING_H_INCLUDED
