#include "Ghost.h"
#include "Translate.h"

/**
*   Creates a ghost with coordinates and texture
*/
GLuint Ghost::createGhost(GLuint squareShaderProgram, int i, int j, char ab, char udrl)
{
    float x = 4.0f, y = 0.f; // coordinates of sub picture

    if (ab == 'A') {
        switch (udrl) {
        case 'U': x = 4.f, y = 1.f; break;
        case 'D': x = 4.f, y = 0.f; break;
        case 'R': x = 4.f, y = 3.f; break;
        case 'L': x = 4.f, y = 2.f; break;
        }
    }
    if (ab == 'B') {
        switch (udrl) {
        case 'U': x = 5.f, y = 1.f; break;
        case 'D': x = 5.f, y = 0.f; break;
        case 'R': x = 5.f, y = 3.f; break;
        case 'L': x = 5.f, y = 2.f; break;
        }
    }

   
    float sheetWidth = 440.f, sheetHeight = 290.f;  // whole picture
    float spriteWidth = 73.f, spriteHeight = 73.f;   // sub picture
    float a = (x * spriteWidth) / sheetWidth;
    float b = (y * spriteHeight) / sheetHeight;
    float c = ((x + 1.f) * spriteWidth) / sheetWidth;
    float d = ((y + 1.f) * spriteHeight) / sheetHeight;

    GLfloat diamond[4 * 7] =
    {
        /*
      |position              |color             |texture coord*/
       i ,       j,         1.0f, 1.0f, 1.0f,    c,   b,     // top right
       i ,       j - 1,     1.0f, 1.0f, 1.0f,    c,   d,     // bottom right
       i - 1,    j - 1,     1.0f, 1.0f, 1.0f,    a,   d,     // bottom left
       i - 1,    j,         1.0f, 1.0f, 1.0f,    a,   b,     // top left
    };

    GLuint indices[6] = { 0,1,2,0,2,3 };

    // blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(diamond), diamond, GL_STATIC_DRAW);

    // Specify the layout of the vertex data, including the texture coordinates
    GLint posAttribb = glGetAttribLocation(squareShaderProgram, "aPosition");
    GLint colorAttribb = glGetAttribLocation(squareShaderProgram, "aColor");
    GLint texAttribb = glGetAttribLocation(squareShaderProgram, "aTexcoord");

    glVertexAttribPointer(posAttribb, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (const void*)0);
    glVertexAttribPointer(colorAttribb, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (const void*)8);
    glVertexAttribPointer(texAttribb, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (const void*)20);
    glEnableVertexAttribArray(posAttribb);
    glEnableVertexAttribArray(colorAttribb);
    glEnableVertexAttribArray(texAttribb);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    startPosX = static_cast<float>(i);
    startPosY = static_cast<float>(j);
    ghostX = i;
    ghostY = j;

    return vao;
  
}


/**
*   Controls all the ghosts movement individually. Movements are random, except that they are
*   not allowed to turn 180 degrees. 
*/
void Ghost::newMove(float time, std::vector<std::pair<int,int>> walls,  GLuint shaderProgram) {
    
    Translate gTranslate;
    if (resetTransformationValues) {

        int dirNumber = rand() % 4; //random number for random direction        

        //Randomly picks a new direction for the ghosts, but does not allow 180 degree turns 
        if (dirNumber == 0 && currentDirection != 'D') {
            up = true;
        }
        else if (dirNumber == 1 && currentDirection != 'U') {
            down = true;
        }
        else if (dirNumber == 2 && currentDirection != 'R') {
            left = true;
        }
        else if (dirNumber == 3 && currentDirection != 'L') {
            right = true;
        }
    }
    if (up && currentDirection != 'U') {
        //Wall detection
        bool wallHit = gTranslate.wallHitUp(walls, ghostX, ghostY);

        //If no wall found, move ghost
        if (wallHit) {
            up = false;
        }
        else {
            down = false;
            left = false;
            right = false;
            currentDirection = 'U';
        }
    }
    if (down && currentDirection != 'D') {
        //Wall detection
        bool wallHit = gTranslate.wallHitDown(walls, ghostX, ghostY);

        //If no wall found, move ghost
        if (wallHit) {
            down = false;
        }
        else {
            up = false;
            left = false;
            right = false;

            currentDirection = 'D';
        }
    }
    if (left && currentDirection != 'L') {
        //Wall detection
        bool wallHit = gTranslate.wallHitLeft(walls, ghostX, ghostY);

        //If no wall found, move ghost
        if (wallHit) {
            left = false;
        }
        else {
            up = false;
            down = false;
            right = false;

            currentDirection = 'L';
        }
    }
    if (right && currentDirection != 'R') {
        //Wall detection
        bool wallHit = gTranslate.wallHitRight(walls, ghostX, ghostY);
        
        //If no wall found, move ghost
        if (wallHit) {
            right = false;
        }
        else {
            up = false;
            down = false;
            left = false;

            currentDirection = 'R';
        }
    }

    //Special case teleport ghost
    //Right to left
    if (ghostX == 29 && ghostY == 18) {
        ghostX = 1;
        transformGhostX -= 28.f; 
    }
    //Left to right
    else if (ghostX == 0 && ghostY == 18) {
        ghostX = 28;
        transformGhostX += 28.f;
    }

    //------------UP------------//
    if (up) {
        //Wall collision prevention
        bool wallHit = gTranslate.wallHitUp(walls, ghostX, ghostY);

        //If wall is found, dont move that direction
        if (wallHit) {
            up = false;
        }
        //If there is no wall, pacman can move
        if (!wallHit) {
            resetTransformationValues = gTranslate.translateUp(up, resetTransformationValues, ghostX, ghostY, transformGhostX,
                transformGhostY, ghostTime, frameCounter, shaderProgram, 1);
            ghostX = gTranslate.rObjX;
            ghostY = gTranslate.rObjY;
            //Makes sure rTraObjX is not 0 and resets the progress of the next frame
            if (gTranslate.rTraObjY != 0) {
                transformGhostX = gTranslate.rTraObjX;
                transformGhostY = gTranslate.rTraObjY;
            }
            frameCounter = gTranslate.frameCounter;
          }
    }
    //------------DOWN------------//
    if (down) {
        //Wall collision prevention
        bool wallHit = gTranslate.wallHitDown(walls, ghostX, ghostY);

        //If no wall found, move
        if (wallHit) {
            down = false;
        }

        //If there is no wall, pacman can move
        if (!wallHit) {
            resetTransformationValues = gTranslate.translateDown(down, resetTransformationValues, ghostX, ghostY, transformGhostX,
                transformGhostY, ghostTime, frameCounter, shaderProgram, 1);
            ghostX = gTranslate.rObjX;
            ghostY = gTranslate.rObjY;
            if (gTranslate.rTraObjY != 0) {
                transformGhostX = gTranslate.rTraObjX;
                transformGhostY = gTranslate.rTraObjY;
            }
            frameCounter = gTranslate.frameCounter;
        }
    }
    //------------LEFT------------//
    if (left) {
        //Wall collision prevention
        bool wallHit = gTranslate.wallHitLeft(walls, ghostX, ghostY);

        //If no wall found, move
        if (wallHit) {
            left = false;
        }
        //If there is no wall, pacman can move
        if (!wallHit) {
            resetTransformationValues = gTranslate.translateLeft(left, resetTransformationValues, ghostX, ghostY, transformGhostX,
                transformGhostY, ghostTime, frameCounter, shaderProgram, 1);
            ghostX = gTranslate.rObjX;
            ghostY = gTranslate.rObjY;
            if (gTranslate.rTraObjX != 0) {
                transformGhostX = gTranslate.rTraObjX;
                transformGhostY = gTranslate.rTraObjY;
            }
            frameCounter = gTranslate.frameCounter;
        }
    }
    //------------RIGHT------------//
    if (right) {
        //Wall collision prevention
        bool wallHit = gTranslate.wallHitRight(walls, ghostX, ghostY);

        //If wall found, stop
        if (wallHit) {
            right = false;
        }

        //If there is no wall, pacman can move
        if (!wallHit) {
            resetTransformationValues = gTranslate.translateRight(right, resetTransformationValues, ghostX, ghostY, transformGhostX,
                transformGhostY, ghostTime, frameCounter, shaderProgram, 1);
            ghostX = gTranslate.rObjX;
            ghostY = gTranslate.rObjY;

            if (gTranslate.rTraObjX != 0) {
                transformGhostX = gTranslate.rTraObjX;
                transformGhostY = gTranslate.rTraObjY;
            }
            frameCounter = gTranslate.frameCounter;
            
        }
    }
}

/**
*   Checks for collision with pacman. It adjusts for the different starting positions, then 
*   it checks if the ghost ann pacman is withing 0.5 coordinates of each other in either direction 
*/
bool Ghost::pacmanGhostCollision(float pTransformX, float pTransformY) {

    //Starting coordinates of pacman
    float pacX = 1.f;
    float pacY = 18.f;

    //Finds the difference in starting postitions between the ghost and pacman
    float tempX = startPosX - pacX;
    float tempY = startPosY - pacY;

    //Accounts for the different starting positions between ghosts and pacman
    pTransformX -= tempX;
    pTransformY -= tempY;
    
    if ((pTransformX < transformGhostX + 0.5 && pTransformX > transformGhostX - 0.5) && 
        (pTransformY < transformGhostY + 0.5 && pTransformY > transformGhostY - 0.5)) {
        return true;
    }
    return false;
}

/**
*   Randomizes the starting positions of the ghosts, but makes sure they start in or right next to a tunnel,
*   to prevent ghosts being stuck within a wall
*/
std::pair<int, int> Ghost::randomizeStartGhost(std::vector<std::pair<int, int>> pellets) {
    bool validStartX = false;
    bool validStartY = false;
    int ghostStartX;
    int ghostStartY;


    //Validates and re-randomizes starting positions
    while (!validStartX && !validStartY) {
        if (!validStartX)ghostStartX = ((rand() % 28) + 1); //Random number 1-28
        if (!validStartY)ghostStartY = ((rand() % 33) + 5); //Random number 5-33

        for (auto val : pellets) {
            if (ghostStartX == val.first) validStartX = true;
            if (ghostStartY == val.second) validStartY = true;
        }
    }
    std::pair<int, int> startXY;
    startXY.first = ghostStartX; startXY.second = ghostStartY;
    return startXY;
}

/**
*   Returns the current direction of the ghost
*/
char Ghost::returnCurDir() {
    return currentDirection;
}