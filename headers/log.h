#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED
#define PRINTPOSX -900
#define PRINTPOSY -500
extern void renderBitmap(float ,float,void*,char*);
void printSearchLog(bool searchedNodeFound, char* value)
{
    char buffer[100]={};
    glColor3f(0,0,0);
    sprintf_s(buffer,value);
    renderBitmap(PRINTPOSX,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);
    if(searchedNodeFound)
    {
    sprintf_s(buffer," is present in tree.");
    renderBitmap(PRINTPOSX+100,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);

    }
    else{
    sprintf_s(buffer," is not present in tree.");
    renderBitmap(PRINTPOSX+100,PRINTPOSY, GLUT_BITMAP_HELVETICA_18,buffer);

    }
}

#endif // LOG_H_INCLUDED
