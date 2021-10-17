#include "Translate.h"
#include "Renderer.h"

//------------UP------------//
/**
*   Translates pacman and ghosts upwards
*/
bool Translate::translateUp(bool up, bool reset, int objX, int objY, float transformObjX, float transformObjY, 
                            float objTime, int fraCount, GLuint shaderProgram, bool ghost)
{   
    //Resets or sets new values for necessary variables involved in transforming objects smoothly
    if (reset) {
        tempTransformY = transformObjY + 1.0; //Sets the neighbouring coordinate value for later use

        //Calculates movement for pacman in 30FPS 
        fraCount = 0;
        reset = false; //Reset done, start moving
    }
    frameAmount = 30.0 * objTime;       //Amount of frames object will move based on 'objTime'
    frameXY = 1.0 / frameAmount;        //Distance for transformation per frame object will move
    frameSec = (objTime) / frameAmount; //Amount of time, in seconds, every frame will be

    //Transforms object based on time, frames and distance
    if (fraCount < frameAmount) {
        fraCount++;
        transformObjY += frameXY;
        Render transform;
        //Checks if we are transforming a ghost or pacman
        if (ghost) {
            transform.Transform(transformObjX, transformObjY, shaderProgram);
        }
        else {
            transform.Transform(transformObjX, transformObjY, 'U', shaderProgram);
        }
        
    }
    //When object has reached the next coordinate, open up for new transformation
    else {
        reset = true;
        objY++;
        transformObjY = tempTransformY;
    }
    rObjX = objX;
    rObjY = objY;
    rTraObjX = transformObjX;
    rTraObjY = transformObjY;
    frameCounter = fraCount;
    return reset;
}

//------------DOWN------------//
/**
*   Translates pacman and ghosts downwards
*/
bool Translate::translateDown(bool down, bool reset, int objX, int objY, float transformObjX, float transformObjY, 
                              float objTime, int fraCount, GLuint shaderProgram, bool ghost)
{
    //Resets or sets new values for necessary variables involved in transforming object smoothly
    if (reset) {
        tempTransformY = transformObjY - 1; //Sets the neighbouring coordinate value for later use

        //Calculates movement for object in 30FPS 
        fraCount = 0;
        reset = false; //Reset done, start moving
    }
    frameAmount = 30.0 * objTime;       //Amount of frames object will move based on 'objTime'
    frameXY = 1.0 / frameAmount;        //Distance for transformation per frame object will move
    frameSec = (objTime) / frameAmount; //Amount of time, in seconds, every frame will be

    //Transforms object based on time, frames and distance
    if (fraCount < frameAmount) {
        fraCount++;
        transformObjY -= frameXY;
        Render transform;
        //Pacman or ghost transformation
        if (ghost) {
            transform.Transform(transformObjX, transformObjY, shaderProgram);
        }
        else {
            transform.Transform(transformObjX, transformObjY, 'D', shaderProgram);
        }
    }
    //When object has reached the next coordinate, open up for new transformation
    else {
        reset = true;
        objY--;
        transformObjY = tempTransformY;
    }
    rObjX = objX;
    rObjY = objY;
    rTraObjX = transformObjX;
    rTraObjY = transformObjY;
    frameCounter = fraCount;
    return reset;
}

//------------LEFT------------//
/**
*   Translates pacman and ghosts left
*/
bool Translate::translateLeft(bool left, bool reset, int objX, int objY, float transformObjX, float transformObjY, 
                              float objTime, int fraCount, GLuint shaderProgram, bool ghost)
{   
    //Resets or sets new values for necessary variables involved in transforming object smoothly
    if (reset) {
        tempTransformX = transformObjX - 1; //Sets the neighbouring coordinate value for later use

        //Calculates movement for object in 30FPS 
        fraCount = 0;
        reset = false; //Reset done, start moving
    }
    frameAmount = 30.0 * objTime;       //Amount of frames object will move based on 'objTime'
    frameXY = 1.0 / frameAmount;        //Distance for transformation per frame object will move
    frameSec = (objTime) / frameAmount; //Amount of time, in seconds, every frame will be

    //Transforms object based on time, frames and distance
    if (fraCount < frameAmount) {
        fraCount++;
        transformObjX -= frameXY;
        Render transform;
        //Pacman/ghost transformation
        if (ghost) {
            transform.Transform(transformObjX, transformObjY, shaderProgram);
        }
        else {
            transform.Transform(transformObjX, transformObjY, 'L', shaderProgram);
        }
    }
    //When object has reached the next coordinate, open up for new transformation
    else {
        reset = true;
        objX--;
        transformObjX = tempTransformX;
    }
    rObjX = objX;
    rObjY = objY;
    rTraObjX = transformObjX;
    rTraObjY = transformObjY;
    frameCounter = fraCount;
    return reset;
}
//------------RIGHT------------//
/**
*   Translates pacman and ghosts right
*/
bool Translate::translateRight(bool right, bool reset, int objX, int objY, float transformObjX, float transformObjY, 
                               float objTime, int fraCount, GLuint shaderProgram, bool ghost)
{
    
    //Resets or sets new values for necessary variables involved in transforming object smoothly
    if (reset) {
        tempTransformX = transformObjX + 1; //Sets the neighbouring coordinate value for later use

        //Calculates movement for object in 30FPS 
        fraCount = 0;
        reset = false; //Reset done, start moving
    }
    frameAmount = 30.0 * objTime;       //Amount of frames object will move based on 'objTime'
    frameXY = 1.0 / frameAmount;        //Distance for transformation per frame object will move
    frameSec = (objTime) / frameAmount; //Amount of time, in seconds, every frame will be

    //Transforms object based on time, frames and distance
    if (fraCount < frameAmount) {
        fraCount++;
        transformObjX += frameXY;
        Render transform;
        //Pacman/ghost transformation
        if (ghost) {
            transform.Transform(transformObjX, transformObjY, shaderProgram);
        }
        else {
            transform.Transform(transformObjX, transformObjY, 'R', shaderProgram);
        }
    }
    //When object has reached the next coordinate, open up for new transformation
    else {
        reset = true;
        objX++;
        transformObjX = tempTransformX;
    }
    rObjX = objX;
    rObjY = objY;
    rTraObjX = transformObjX;
    rTraObjY = transformObjY;
    frameCounter = fraCount;
    return reset;
}

/**
*   Checks for collision with walls in the different directions, using the coordinates of pacman/ghosts and
*   comparing them to the coordinates in the vector of wall coordinates
*/

//-----UP-----//
bool Translate::wallHitUp(std::vector<std::pair<int,int>> walls, int objX, int objY) {
    bool hit = false;
    for (auto val : walls) {
        if (val.first == objX) {
            if ((val.second) == (objY + 1)) {
                hit = true;
            }
        }
    }
    return hit;
}

//-----DOWN-----//
bool Translate::wallHitDown(std::vector<std::pair<int, int>> walls, int objX, int objY) {
    bool hit = false;
    for (auto val : walls) {
        if (val.first == objX) {
            if ((val.second) == (objY - 1)) {
                hit = true;
            }
        }
    }
    return hit;
}

//-----LEFT-----//
bool Translate::wallHitLeft(std::vector<std::pair<int, int>> walls, int objX, int objY) {
    bool hit = false;
    for (auto val : walls) {
        if (val.second == objY) {
            if ((val.first) == (objX - 1)) {
                hit = true;
            }
        }
    }
    return hit;
}

//-----RIGHT-----//
bool Translate::wallHitRight(std::vector<std::pair<int, int>> walls, int objX, int objY) {
    bool hit = false;
    for (auto val : walls) {
        if (val.second == objY) {
            if ((val.first) == (objX + 1)) {
                hit = true;
            }
        }
    }
    return hit;
}