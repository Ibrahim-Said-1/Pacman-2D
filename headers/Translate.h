#include "Libraries.h"

class Translate
{
private:

    //Temporary variables used to keep hold of transforming coordinates
    float tempTransformX = 0.f;
    float tempTransformY = 0.f;

    //Frame variables to keep track of smooth object movement
    
    float frameAmount = 0.f;
    float frameXY = 0.f;
    float frameSec = 0.f;

public:

    //For return values of x and y coordinates of object
    int rObjX = 0;
    int rObjY = 0;
    float rTraObjX = 0.f;
    float rTraObjY = 0.f;
    float frameCounter = 0.f;

    //Moving an object 1 unit
    bool translateUp(bool up, bool reset, int objX, int objY, float transformObjX, float transformObjY, float objTime, int fraCount, GLuint shaderProgram, bool ghost);
    bool translateDown(bool down, bool reset, int objX, int objY, float transformObjX, float transformObjY, float objTime, int fraCount, GLuint shaderProgram, bool ghost);
    bool translateLeft(bool left, bool reset, int objX, int objY, float transformObjX, float transformObjY, float objTime, int fraCount, GLuint shaderProgram, bool ghost);
    bool translateRight(bool right, bool reset, int objX, int objY, float transformObjX, float transformObjY, float objTime, int fraCount, GLuint shaderProgram, bool ghost);
    
    //Detecs walls before moving
    bool wallHitUp(std::vector<std::pair<int, int>> walls, int objX, int objY);
    bool wallHitDown(std::vector<std::pair<int, int>> walls, int objX, int objY);
    bool wallHitLeft(std::vector<std::pair<int, int>> walls, int objX, int objY);
    bool wallHitRight(std::vector<std::pair<int, int>> walls, int objX, int objY);

};