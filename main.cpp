//initial
#include<iostream>
#include<GL/glut.h>
#include "bstClass.h"
#include "keyboardEventHandler.h"
#include "drawing.h"
#include"log.h"
#include<math.h>
#include<string>
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
char tempKeyPressed[5];
int positionsInArrayNode[15];
int kIndex=-1;//k for positionsInArrayNode

bool displayDrawNodeMotion=false;
bool callTimer=false;
bool finalPos=false;
bool displaySearchedNode=false;
bool inputNodeToSearch=false;
bool searchedNodeFound=false;
bool displayAllNodes=true;
bool insertedNode=false;
bool searchedNode=false;
bool preorderedNode=false;
bool postorderedNode=false;
bool inorderedNode=false;
bool traversalRequired=false;
bool displayTraversedNodes=false;

void init();
void display();
void reshape(int ,int);
void timer (int);
void goMenu(int);
void menuDetails();
void returnVal(int,int,int);
void updateTree();
void renderBitmap(float,float, void*,char*);
void resetKeyPressed();
void keyboard(unsigned char, int, int);


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
            //arrayNode[arrayIndex].value[i]='\0';
            i--;

            }
            i=0;
}

void resetTraversalDetails()
{
    for(int k=0;k<=arrayIndex;k++){
    for(int j=0;j<5;j++) bstobj.orderedArray[k].value[j]='\0';
    positionsInArrayNode[k]=-1;
    }
    bstobj.traversedIndex=0;
    kIndex=-1;


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


void goMenu(int menuVal)
{   val=menuVal;
    resetTraversalDetails();
    preorderedNode=false;
    postorderedNode=false;
    inorderedNode=false;
    inputKeyboardVal=false;
    inputNodeToSearch=false;
    displaySearchedNode=false;
    displayTraversedNodes=false;
    traversalRequired=false;
    searchedNode=false;
    insertedNode=false;
    switch (menuVal)
    {
        case 1:

                inputKeyboardVal=true;
               keyboardobj.displayKeyboard();
               keyboardobj.displayInsert();


               break;
        case 2:
                traversalRequired=true;
                bstobj.inorder(bstobj.tree);
                updateTree();
                cout<<endl;
                break;
        case 3:
                traversalRequired=true;
                bstobj.preorder(bstobj.tree);
                updateTree();
                cout<<endl;
                break;
        case 4:
                traversalRequired=true;
                bstobj.postorder(bstobj.tree);
                updateTree();
                cout<<endl;
                break;
        case 5:
                inputKeyboardVal=true;
                keyboardobj.displayKeyboard();
                keyboardobj.displaySearch();
                break;
        case 6:
                exit(0);
                break;
    }
    glutPostRedisplay();

}

void keyboard(unsigned char key, int x,int y)
{   if(inputKeyboardVal)
    {
        if (inputNodeToSearch)
        {if(key>='0'&&key<='9')
               {
                keyPressed[i]=key;
                i++;
                glutPostRedisplay();
                }

        }
        else
        {if(key>='0'&&key<='9')
               {
                keyPressed[i]=key;
                arrayNode[arrayIndex].value[i]=key;
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
                    if(!inputNodeToSearch)
                        {arrayNode[arrayIndex].val=num;
                        searchedNode=false;
                        }
                    else insertedNode=false;



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


void updateTree()
{
    if(!enterNotPressed)
    {
        if(val==1)
           {
            bstobj.insertElement(bstobj.tree,num);
            displayDrawNodeMotion=true;
            insertedNode=true;
            strcpy(tempKeyPressed,keyPressed);
            cout<<num<<" inserted successfully"<<endl;

            }

        if(val==5)
            {bstobj.searchElement(bstobj.tree,num);
            displayDrawNodeMotion=false;
            displaySearchedNode=true;
            searchedNode=true;
            for(int l=0;l<=arrayIndex;l++)
            {
                if(arrayNode[l].val==num)
                {
                    searchedIndex=l;
                    searchedNodeFound=true;

                    break;
                }
                else searchedNodeFound=false;


            }
            strcpy(tempKeyPressed,keyPressed);

            cout<<"Search for "<<num<<" completed"<<endl;
            }
        resetKeyPressed();
        keyboardobj.closeKeyboard();
    }

    if(traversalRequired){
        if(val==3||val==4||val==2)
            {cout<<endl;
                if(val==2) cout<<"In-";
                else if (val==3) cout<<"Pre-";
                else cout<<"Post-";
            cout<<"orderedArray= ";
            for(int k=0;k<bstobj.traversedIndex;k++)
            {sprintf(bstobj.orderedArray[k].value,"%ld", bstobj.orderedArray[k].val);
            cout<<bstobj.orderedArray[k].value<<" ";
            }

            displayDrawNodeMotion=false;
            displaySearchedNode=false;

            for(int l=0;l<=bstobj.traversedIndex;l++){
                for(int j=0; j<=arrayIndex;j++){
                    if( bstobj.orderedArray[l].val==arrayNode[j].val)
                       {positionsInArrayNode[l]=j;
                       }
                }
            }
            cout<<endl<<"positionsInArrayNode= ";
            for(int k=0;k<arrayIndex;k++){
                cout<<positionsInArrayNode[k]<<" ";
            }
            cout<<endl;
            if(val==2) inorderedNode=true;
                else if (val==3) preorderedNode=true;
                else postorderedNode=true;
            displayTraversedNodes=true;
            searchedBlinkRed=true;
            }

    }
    enterNotPressed=true;
    inputKeyboardVal=false;
    callTimer=true;
    glutTimerFunc(100, timer,0);

}

void timer(int val)
{

    if(callTimer)
    {glutPostRedisplay();


    //identify final pos of node
    if(displaySearchedNode){
        glutTimerFunc(1000,timer,0);
        if(searchedNodeFound){
            if(searchedBlinkRed) searchedBlinkRed=false;
            else searchedBlinkRed=true;
            }


    }
    else if(traversalRequired)
    {
        glutTimerFunc(1000,timer,0);
        kIndex++;
        if(kIndex>(arrayIndex-1))
        {
            displayTraversedNodes=false;
            searchedBlinkRed=false;
            traversalRequired=false;
            //preorderedNode=true;
            //resetTraversalDetails();
            //glutPostRedisplay()
            //return;
        }

    }
    else if(displayDrawNodeMotion)
    {glutTimerFunc(1000/60,timer,0);
        if(deltaX<=-650)
        {deltaX+=5;
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
                        //displayDrawNodeMotion=true;
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

    if(displayAllNodes)
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
    }
    else if(displayTraversedNodes)
    {
        if(kIndex<=arrayIndex)
        {drawSearchedNode(arrayNode[positionsInArrayNode[kIndex]].posX, arrayNode[positionsInArrayNode[kIndex]].posY);
        drawNodeText(arrayNode[positionsInArrayNode[kIndex]].posX,arrayNode[positionsInArrayNode[kIndex]].posY,positionsInArrayNode[kIndex]);
        }
        else return;
    }


    //if(val==3) preorderedNode=true;
    displayLogBackground();
    if(insertedNode) printInsertLog(tempKeyPressed);
    else if(searchedNode) printSearchLog(searchedNodeFound,tempKeyPressed);
    else if(inorderedNode) printInorderLog();
    else if(preorderedNode) printPreorderLog();
    else if(postorderedNode) printPostorderLog();
    else printInitialLog();

//plank
    glColor3f(0,0,0);
    glLineWidth(100);
    glBegin(GL_LINES);
    glVertex2f(-960,380);
    glVertex2f(-700,380);
    glEnd();
    glColor3ub(93,93,93);
    glLineWidth(15);
    glBegin(GL_LINES);
    glVertex2f(-960,390);
    glVertex2f(-705,390);
    glEnd();
    glColor3ub(212,208,199);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2f(-960,390);
    glVertex2f(-710,390);
    glEnd();

    if(displayDrawNodeMotion)
    {
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
