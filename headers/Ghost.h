#include "Libraries.h"


class Ghost
{
private:

    //Prevents data leaking from one transformation to the next
    bool resetTransformationValues = true;

    //Direction of ghost
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    //Coordinates for transforming ghost
    float transformGhostX = 0.f;
    float transformGhostY = 0.f;

    //Speed of ghost  (higher = slower)
    float ghostTime = 01.6f; 

    //Starting coordinates of ghost
    int ghostX;
    int ghostY;

    //Coordinates used to detect collision with pacman
    float startPosX;
    float startPosY;

    //Direction of ghosts, initialized with something (other than u/d/l/r) to prevent program from crashing
    char currentDirection = 'S';

    //For moving ghosts in a random direction every so often 
    float tempTime = 0.0;
    float frameCounter = 0.f;


public:
    GLuint  createGhost(GLuint squareShaderProgram, int i, int j, char ab, char udlr);
    void    newMove(float time, std::vector<std::pair<int, int>> walls, GLuint shaderProgram);
    bool    pacmanGhostCollision(float pTransformX, float pTransformY);
    std::pair<int, int>  randomizeStartGhost(std::vector<std::pair<int, int>> pellets);
    char    returnCurDir();
   
    
    

};