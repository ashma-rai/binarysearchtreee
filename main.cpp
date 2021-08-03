//initial
#include<iostream>
#include<GL/glut.h>
#include "bstClass.h"
#include "keyboardEventHandler.h"
//#include "drawTree.h"
#include "drawing.h"
#include"log.h"
#include<math.h>
#define RADNODE 50
using namespace std;
bstClass bstobj;
//drawTree drawobj;
keyboardEventHandler keyboardobj;
int choice, num,numofelements,menuVal,val;
bool inputKeyboardVal=false;
bool enterNotPressed=true;
int i=0,keyX=-80,keyY=-30;
//extern char keyPressed[5];
int rootDepth,rootPos;
int searchedIndex=-1;
int deltaX=-1050,deltaY=450;
int prevTreePos,prevTreeDepth;
bool displayDrawNode=false;
bool callTimer=false;
bool finalPos=false;
bool displaySearchedNode=false;
bool inputNodeToSearch=false;
bool searchedNodeFound=false;

void init();
void display();
void reshape(int ,int);
void timer (int);

void renderBitmap(float x, float y, void *font, char *str)
    {
        char *c;
        glRasterPos2f(x,y);
        for(c=str; *c!='\0';c++)
        {
            glutBitmapCharacter(font, *c);
        }

    }

void returnVal(int val,int counter,int prevPosX)
{
    rootPos=val;
    rootDepth=counter;

    arrayNode[arrayIndex].prevposX=prevPosX;
    arrayNode[arrayIndex].prevposY=300-200*(counter-1);
    cout<<"rootPos ="<<rootPos<<", rootDepth ="<<rootDepth<<", prevPos="<<prevTreePos<<endl;
}

void resetKeyPressed()
{
    while(i>=0)
            {
            keyPressed[i]='\0';
           // arrayNode[arrayIndex].value[i]='\0';
            i--;

            }
            i=0;
}

void updateTree()
{
    if(!enterNotPressed)
    {
        if(val==1)
           {
            bstobj.insertElement(bstobj.tree,num);
            cout<<num<<" inserted successfully"<<endl;

            }
        if(val==5)
            {bstobj.searchElement(bstobj.tree,num);
            for(int l=0;l<=arrayIndex;l++)
            {
                if(arrayNode[l].val==num)
                {
                    searchedIndex=l;
                    searchedNodeFound=true;
                    break;
                }


            }
            cout<<"Search for "<<num<<" completed"<<endl;
            }
        resetKeyPressed();
        keyboardobj.closeKeyboard();
        //cout<<"Keyboard Closed"<<endl;
    }
    enterNotPressed=true;
    inputKeyboardVal=false;
    displayDrawNode=true;

     //if(!displaySearchedNode)
     {callTimer=true;
    glutTimerFunc(100, timer,0);
     }
     //else glutPostRedisplay();

}

void keyboard(unsigned char key, int x,int y)
{   if(inputKeyboardVal)
    {
        if(!inputNodeToSearch)
        {if(key>='0'&&key<='9')
               {
                keyPressed[i]=key;
                arrayNode[arrayIndex].value[i]=key;
                i++;
                glutPostRedisplay();
                }
        }
        else
        {if(key>='0'&&key<='9')
               {
                keyPressed[i]=key;
                i++;
                glutPostRedisplay();
                }

        }

        if(key==8)//backspace delete all
               {
                resetKeyPressed();
                cout<<"Backspace Called: keyPressed reset"<<endl;
                glutPostRedisplay();
                }
        if(key==10 ||key==13)//enter
            {  if(keyPressed[0]!='\0')
                {   num=atoi(keyPressed);
                    cout<<"Node val entered ="<<num<<endl;
                    if(!displaySearchedNode)
                        arrayNode[arrayIndex].val=num;
                    //cout<<"arraynode["<<arrayIndex<<"]->val= "<<arrayNode[arrayIndex].value<<endl;
                    //erase screen
                    keyX=-80;
                    enterNotPressed=false;
                    glutPostRedisplay();
                    updateTree();
                    //cout<<"TREE UPDATED"<<endl;
                }

            }
            //glFlush();
            glutSwapBuffers();
    }
}

void goMenu(int menuVal)
{   val=menuVal;
    switch (menuVal)
    {
        case 1:inputKeyboardVal=true;
        inputNodeToSearch=false;
        displaySearchedNode=false;
               keyboardobj.displayKeyboard();
               keyboardobj.displayInsert();


               break;
        case 2:
                bstobj.inorder(bstobj.tree);
                cout<<endl;
                break;
        case 3:
                bstobj.preorder(bstobj.tree);
                cout<<endl;
                break;
        case 4:
                bstobj.postorder(bstobj.tree);
                cout<<endl;
                break;
        case 5:
                inputKeyboardVal=true;
                inputNodeToSearch=true;
                keyboardobj.displayKeyboard();
                keyboardobj.displaySearch();
                break;
        case 6:
                exit(0);
                break;
    }
    glutPostRedisplay();

}

void menuDetails()
{
    glutCreateMenu(goMenu);

    int subMenuTraversal=glutCreateMenu(goMenu);

    glutAddMenuEntry("INORDER",2);
    glutAddMenuEntry("PREORDER",3);
    glutAddMenuEntry("POSTORDER",4);
    glutCreateMenu(goMenu);
    glutAddSubMenu("TRAVERSAL",subMenuTraversal);
    glutAddMenuEntry("INSERT",1);
    glutAddMenuEntry("SEARCH",5);
    glutAddMenuEntry("EXIT", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void timer(int val)
{

    if(callTimer)
    {glutPostRedisplay();


    //identify final pos of node
    if(!displaySearchedNode)
    {glutTimerFunc(1000/60,timer,0);
        if(deltaX<=-650)
        {deltaX+=10;
        return;
        }
    //if(deltaY<=450 ){

            //identify where to stop acc to the nodenum
            if(deltaY>300-rootDepth*200){deltaY-=10;}
            else{
                    if (deltaX<rootPos)
                            {deltaX+=10;
                            }
                    else{
                        displayDrawNode=true;
                        callTimer=false;
                        finalPos=true;
                        arrayNode[arrayIndex].posX=deltaX;
                        arrayNode[arrayIndex].posY=deltaY;


                        cout<<"Node["<<arrayIndex<<"]"<<"position =("<<deltaX<<" , "<<deltaY<<")";
                        //cout<<"Node["<<arrayIndex<<"]"<<"char value =";

                        //for(int j=0;j<i;j++)
                           // cout<<arrayNode[arrayIndex].value[j];
                        cout<<endl<<"**************"<<endl;
                        deltaX=-1000;deltaY=450;
                        arrayIndex++;
                        }
                }

    }
    else{
        glutTimerFunc(1000,timer,0);
        if(searchedBlinkRed) searchedBlinkRed=false;
        else searchedBlinkRed=true;

    }
    }


    }



int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowPosition(50,10);
    glutInitWindowSize(960,540);
    glutCreateWindow("BST");


    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

      // glutTimerFunc(2000, timer,0);
    menuDetails();
    init();

    glutMainLoop();

}
void init()
{
    glClearColor(0.8,0.7,0.9,1);

}

void reshape(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-960,960,-540,540);
    glMatrixMode(GL_MODELVIEW);

}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if(displayDrawNode)
    {int i=0;
    while(i<(arrayIndex))
    {
        drawBranch(arrayNode[i].posX,arrayNode[i].posY,i);
        i++;

    }
i=0;
    while(i<(arrayIndex))
    {
        drawNodeAndText(arrayNode[i].posX,arrayNode[i].posY,i);
        i++;

    }
    }

    if(displaySearchedNode)
    {
        if(searchedNodeFound)
        {
        drawSearchedNode(arrayNode[searchedIndex].posX,arrayNode[searchedIndex].posY);
        drawNodeText(arrayNode[searchedIndex].posX,arrayNode[searchedIndex].posY,searchedIndex);
        }
        printSearchLog(searchedNodeFound,arrayNode[searchedIndex].value);

    }



    if(displayDrawNode)
    {
    glColor3f(1,0.5,1);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2f(-960,390);
    glVertex2f(-700,390);
    glEnd();
     glLineWidth(1);
     glBegin(GL_LINES);

    glVertex2f(-960,0);
    glVertex2f(960,0);
    glVertex2f(0,540);
    glVertex2f(0,-540);
    glEnd();
    if(!displaySearchedNode)
    drawNodeAndText(deltaX,deltaY,arrayIndex);

    }

    if(inputKeyboardVal)
    {keyboardobj.displayKeyboard();
    keyboardobj.displayInsert();
    }
    if(enterNotPressed)
    {   glColor3f(0,0,0);
        i=0;
        while(keyPressed[i]!='\0')
        {
            glRasterPos2i(keyX,keyY);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,keyPressed[i]);
            keyX+=18;
            i++;
        }

        keyX=-80;

    }



    //glFlush();
    glutSwapBuffers();
    //glutKeyboardFunc(keyboard);
}
