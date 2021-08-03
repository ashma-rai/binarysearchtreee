#include "keyboardEventHandler.h"
void keyboardEventHandler::closeKeyboard()
{

}

void keyboardEventHandler::displayKeyboard()
{   //menu drawn
    glColor3ub(58,62,78);
    glRectf(x+10,y-10,x+400+10,y+250-15);
    glColor3ub(73,77,98);
    glRectf(x,y,x+400,y+250);

    glColor3ub(135,122,186);
    glRectf(x+10,y+10,x+400-10,y+250-10);
    glColor3ub(22,68,90);
    glRectf(x+20+10,y+20,x+400-20,y+150);
    glColor3ub(162,210,232);
    glRectf(x+20,y+30,x+400-30,y+160);
    glColor3ub(255,255,255);
    glRectf(x+30,y+40,x+400-40,y+150);

}
/*
void renderBitmap(float x, float y, void *font, char *str)
    {
        char *c;
        glRasterPos2f(x,y);
        for(c=str; *c!='\0';c++)
        {
            glutBitmapCharacter(font, *c);
        }

    }
    */
void keyboardEventHandler::displayInsert()
{   glColor3f(0,0,0);
    char buffer[100]={};
    sprintf_s(buffer,"INSERT NODE VALUE:");
    renderBitmap(x+40,y+180,GLUT_BITMAP_HELVETICA_18,buffer);

}

void keyboardEventHandler::displaySearch()
{   glColor3f(0,0,0);
    char buffer[100]={};
    sprintf_s(buffer,"SEARCH NODE VALUE: ");
    renderBitmap(x+40,y+180, GLUT_BITMAP_HELVETICA_18,buffer);


}

keyboardEventHandler::keyboardEventHandler()
{
    //ctor
}

keyboardEventHandler::~keyboardEventHandler()
{
    //dtor
}
