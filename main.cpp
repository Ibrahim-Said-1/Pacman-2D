

/*Author: Ibrahim Said and Anders Hagen*/

#include "headers/Libraries.h"

#include "shaders/shader.h"
#include "shaders/shaderpac.h"
#include "headers/Window.h"
#include "headers/Renderer.h"
#include "headers/Map.h"
#include "headers/Wall.h"
#include "headers/Pellets.h"
#include "headers/Pacman.h"
#include "headers/translate.h"
#include "headers/Ghost.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Window win("Pacman2D", 1200, 1200);
Render app;
Map map;
Wall wall;
Pellet pellet;
Pacman pacman;
Ghost* ghostOne;
Ghost* ghostTwo;
Ghost* ghostThree;
Ghost* ghostFour;
Translate translate;

GLuint load_opengl_texture(const std::string& filepath, GLuint slot);


// Entry point
int main(void)
{
    win.setUpWindow();

    

    std::map<int, GLuint> ghostShaderMap; 

    auto gameShaderProgram = app.CompileShader(squareVertexShaderSrc, squareFragmentShaderSrc);
    auto pacShaderProgram = app.CompileShader(squareVertexShaderSrcPac, squareFragmentShaderSrcPac);

    
    auto ghostShaderProgramOne = app.CompileShader(squareVertexShaderSrcPac,
        squareFragmentShaderSrcPac);
    auto ghostShaderProgramTwo = app.CompileShader(squareVertexShaderSrcPac,
        squareFragmentShaderSrcPac);
    auto ghostShaderProgramThree = app.CompileShader(squareVertexShaderSrcPac,
        squareFragmentShaderSrcPac);
    auto ghostShaderProgramFour = app.CompileShader(squareVertexShaderSrcPac,
        squareFragmentShaderSrcPac);

    // Clear the background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glfwSetTime(0.0);

    map.LoadMap("level0");

    float currentTime = 0.0;
    std::cout << "Debug is disabled!" << std::endl;

    //Creates all the objects for walls and pellets, to be re-used in while loop
    //Walls
    std::vector <GLuint> wallVAO;
    for (int i = 0; i < map.walls.size(); i++) {
        wallVAO.push_back(wall.CreateWalls(gameShaderProgram, map.walls[i].first, map.walls[i].second));
    }

    //Pellets
    //Vector consisting of  <PelletVAO, eaten/not eaten, x value, y value>
    std::vector<std::pair<std::pair<GLuint, bool>, std::pair<int, int>>> pelletVAO;

    for (auto val : map.pellets) {
        pelletVAO.push_back(std::make_pair(std::make_pair((pellet.CreatePellets(gameShaderProgram, val.first, val.second)), false),
            std::make_pair(val.first, val.second)));
    }

    
    
    //Ghosts
    std::pair<int, int> ghostStartXY;

    ghostOne = new Ghost();
    ghostStartXY = ghostOne->randomizeStartGhost(map.pellets);

    GLuint ghostOneAU = ghostOne->createGhost(ghostShaderProgramOne, ghostStartXY.first, ghostStartXY.second, 'A', 'U'); //up
    GLuint ghostOneBU = ghostOne->createGhost(ghostShaderProgramOne, ghostStartXY.first, ghostStartXY.second, 'B', 'U');
    GLuint ghostOneAD = ghostOne->createGhost(ghostShaderProgramOne, ghostStartXY.first, ghostStartXY.second, 'A', 'D'); //down
    GLuint ghostOneBD = ghostOne->createGhost(ghostShaderProgramOne, ghostStartXY.first, ghostStartXY.second, 'B', 'D');
    GLuint ghostOneAL = ghostOne->createGhost(ghostShaderProgramOne, ghostStartXY.first, ghostStartXY.second, 'A', 'L'); //left
    GLuint ghostOneBL = ghostOne->createGhost(ghostShaderProgramOne, ghostStartXY.first, ghostStartXY.second, 'B', 'L');
    GLuint ghostOneAR = ghostOne->createGhost(ghostShaderProgramOne, ghostStartXY.first, ghostStartXY.second, 'A', 'R'); //right
    GLuint ghostOneBR = ghostOne->createGhost(ghostShaderProgramOne, ghostStartXY.first, ghostStartXY.second, 'B', 'R');

    ghostTwo = new Ghost();
    ghostStartXY = ghostTwo->randomizeStartGhost(map.pellets);

    GLuint ghostTwoAU = ghostTwo->createGhost(ghostShaderProgramTwo, ghostStartXY.first, ghostStartXY.second, 'A', 'U'); //up
    GLuint ghostTwoBU = ghostTwo->createGhost(ghostShaderProgramTwo, ghostStartXY.first, ghostStartXY.second, 'B', 'U');
    GLuint ghostTwoAD = ghostTwo->createGhost(ghostShaderProgramTwo, ghostStartXY.first, ghostStartXY.second, 'A', 'D'); //down
    GLuint ghostTwoBD = ghostTwo->createGhost(ghostShaderProgramTwo, ghostStartXY.first, ghostStartXY.second, 'B', 'D');
    GLuint ghostTwoAL = ghostTwo->createGhost(ghostShaderProgramTwo, ghostStartXY.first, ghostStartXY.second, 'A', 'L'); //left
    GLuint ghostTwoBL = ghostTwo->createGhost(ghostShaderProgramTwo, ghostStartXY.first, ghostStartXY.second, 'B', 'L');
    GLuint ghostTwoAR = ghostTwo->createGhost(ghostShaderProgramTwo, ghostStartXY.first, ghostStartXY.second, 'A', 'R'); //right
    GLuint ghostTwoBR = ghostTwo->createGhost(ghostShaderProgramTwo, ghostStartXY.first, ghostStartXY.second, 'B', 'R');

    ghostThree = new Ghost();
    ghostStartXY = ghostThree->randomizeStartGhost(map.pellets);

    GLuint ghostThreeAU = ghostThree->createGhost(ghostShaderProgramThree, ghostStartXY.first, ghostStartXY.second, 'A', 'U'); //up
    GLuint ghostThreeBU = ghostThree->createGhost(ghostShaderProgramThree, ghostStartXY.first, ghostStartXY.second, 'B', 'U');
    GLuint ghostThreeAD = ghostThree->createGhost(ghostShaderProgramThree, ghostStartXY.first, ghostStartXY.second, 'A', 'D'); //down
    GLuint ghostThreeBD = ghostThree->createGhost(ghostShaderProgramThree, ghostStartXY.first, ghostStartXY.second, 'B', 'D');
    GLuint ghostThreeAL = ghostThree->createGhost(ghostShaderProgramThree, ghostStartXY.first, ghostStartXY.second, 'A', 'L'); //left
    GLuint ghostThreeBL = ghostThree->createGhost(ghostShaderProgramThree, ghostStartXY.first, ghostStartXY.second, 'B', 'L');
    GLuint ghostThreeAR = ghostThree->createGhost(ghostShaderProgramThree, ghostStartXY.first, ghostStartXY.second, 'A', 'R'); //right
    GLuint ghostThreeBR = ghostThree->createGhost(ghostShaderProgramThree, ghostStartXY.first, ghostStartXY.second, 'B', 'R');

    ghostFour = new Ghost();
    ghostStartXY = ghostFour->randomizeStartGhost(map.pellets);

    GLuint ghostFourAU = ghostFour->createGhost(ghostShaderProgramFour, ghostStartXY.first, ghostStartXY.second, 'A', 'U'); //up
    GLuint ghostFourBU = ghostFour->createGhost(ghostShaderProgramFour, ghostStartXY.first, ghostStartXY.second, 'B', 'U');
    GLuint ghostFourAD = ghostFour->createGhost(ghostShaderProgramFour, ghostStartXY.first, ghostStartXY.second, 'A', 'D'); //down
    GLuint ghostFourBD = ghostFour->createGhost(ghostShaderProgramFour, ghostStartXY.first, ghostStartXY.second, 'B', 'D');
    GLuint ghostFourAL = ghostFour->createGhost(ghostShaderProgramFour, ghostStartXY.first, ghostStartXY.second, 'A', 'L'); //left
    GLuint ghostFourBL = ghostFour->createGhost(ghostShaderProgramFour, ghostStartXY.first, ghostStartXY.second, 'B', 'L');
    GLuint ghostFourAR = ghostFour->createGhost(ghostShaderProgramFour, ghostStartXY.first, ghostStartXY.second, 'A', 'R'); //right
    GLuint ghostFourBR = ghostFour->createGhost(ghostShaderProgramFour, ghostStartXY.first, ghostStartXY.second, 'B', 'R');
    
 

    //Pacman 
    GLuint pacmanVAOA = pacman.createPacman(pacShaderProgram, map.pacStart.first, map.pacStart.second, 'A');
    GLuint pacmanVAOB = pacman.createPacman(pacShaderProgram, map.pacStart.first, map.pacStart.second, 'B');
    GLuint pacmanVAOC = pacman.createPacman(pacShaderProgram, map.pacStart.first, map.pacStart.second, 'C');
    GLuint pacmanVAOD = pacman.createPacman(pacShaderProgram, map.pacStart.first, map.pacStart.second, 'D');
    //Load the texture image, create OpenGL texture, and bind it to the current context
    auto texture0 = load_opengl_texture("/resources/textures/pacman.png", 0);

    //GAME OVER bool, if not changed from true, all pellets are eaten and game is over
    bool gameOver = true;
    
    //Freezes the game when pacman wins/loses
    bool stopGame = false;


    //-------------------------------------------PACMAN-------------------------------------------//
    //Prevents data leaking from one transformation to the next
    bool resetTransformationValues = true;

    //Direction of pacman
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    //Frame counters
    float frameCounter = 0.f;

    //Coordinates for transforming pacman
    float transformPacmanX = 0.f;
    float transformPacmanY = 0.f;

    //Speed of pacman  (higher = slower)
    float pacTime = 0.8f; //0.8f default value

    //Starting coordinates of pacman
    int pacmanX = map.pacStart.first;
    int pacmanY = map.pacStart.second;

    //Keeps time for pacman animation
    float pacmanAniTime = 0.f;

    //State of pacman animation
    int pacmanAniState = 0;
    bool pacmanAniClosing = false; //direction of animation (open/close mouth)

    char currentDirection = 'S';

    //-------------------------------------------GHOSTS-------------------------------------------//

    //Set to true when player starts the game
    bool startGame = false;

    //Delays ghosts to not start at the same time
    float tempGhostTime = 0.f;
    bool triggerGhosts = false;
    bool startOne = false;
    bool startTwo = false;
    bool startThree = false;
    bool startFour = false;

    //animation of ghosts
    bool ghostOneAniState = false;
    bool ghostTwoAniState = false;
    bool ghostThreeAniState = false;
    bool ghostFourAniState = false;
    float ghostOneAniTime = 0.f;
    float ghostTwoAniTime = 0.f;
    float ghostThreeAniTime = 0.f;
    float ghostFourAniTime = 0.f;


    char ghostOneDir;
    char ghostTwoDir;
    char ghostThreeDir;
    char ghostFourDir;
    

    
    // Main loop
    while (!glfwWindowShouldClose(win.myWindow))
    {
        glfwPollEvents();

        // Time management
        currentTime = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);
        


        // Draw Walls
        for (auto val : wallVAO) {
            auto vertexColorLocation = glGetUniformLocation(gameShaderProgram, "u_Color");
            glUseProgram(gameShaderProgram);
            glBindVertexArray(val);
            glUniform4f(vertexColorLocation, 0.0, 0.372, 0.847, 1.0f);
            app.Camera(currentTime, gameShaderProgram);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
        }

        gameOver = true; //If all pellets are eaten, this should make it past the pellet for loop
        // Draw Pellets
        for (auto& val : pelletVAO) {
            auto vertexColorLocation = glGetUniformLocation(gameShaderProgram, "u_Color");
            glUseProgram(gameShaderProgram);
            glBindVertexArray(val.first.first);

            //When pacman is over a pellet, "eat" pellet and make it invisible
            if ((pacmanX == val.second.first && pacmanY == val.second.second) || val.first.second) {
                glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f); //Blue
                val.first.second = true;
            }
            //If pellet has not been eaten, display the pellet
            else {
                gameOver = false; //at least one pellet left
                glUniform4f(vertexColorLocation, 0.3f, 0.5f, 0.0f, 1.0f); //red
            }
            app.Camera(currentTime, gameShaderProgram);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
        }

        //Draw pacman
        auto vertexColorLocation = glGetUniformLocation(pacShaderProgram, "u_Color");
        auto samplerSlotLocation = glGetUniformLocation(pacShaderProgram, "uTextureA");
        

        glUseProgram(pacShaderProgram);

        //Animation of pacman
        if (currentTime > pacmanAniTime + 0.1f) {
            pacmanAniTime = currentTime;

            if (pacmanAniClosing) {
                pacmanAniState--;
            }
            else {
                pacmanAniState++;
            }

            if (pacmanAniState == 3 || pacmanAniState == 0) {
                pacmanAniClosing = !pacmanAniClosing;
            }
        }

        switch (pacmanAniState) {
        case 0: glBindVertexArray(pacmanVAOA); break;
        case 1: glBindVertexArray(pacmanVAOB); break;
        case 2: glBindVertexArray(pacmanVAOC); break;
        case 3: glBindVertexArray(pacmanVAOD); break;
        }
        
        glUniform1i(samplerSlotLocation, 0);
       
        //If pacman is currently moving inbetween two coordinates, movement is disabled 
        if (resetTransformationValues) {
            if (glfwGetKey(win.myWindow, GLFW_KEY_UP) == GLFW_PRESS) {
                up = true;
            }
            else if (glfwGetKey(win.myWindow, GLFW_KEY_DOWN) == GLFW_PRESS) {
                down = true;
            }
            else if (glfwGetKey(win.myWindow, GLFW_KEY_LEFT) == GLFW_PRESS) {
                left = true;
            }
            else if (glfwGetKey(win.myWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                right = true;
            }
        }

        //------------------------CONTROLS PACMAN------------------------//

        //Checks for walls when the player tries changing direction
        //If there is a wall, the player input is cancelled

        //Control pacman
        if (up && currentDirection != 'U') {
            //Wall detection
            bool wallHit = translate.wallHitUp(map.walls, pacmanX, pacmanY);
            //If no wall found, move
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
            bool wallHit = translate.wallHitDown(map.walls, pacmanX, pacmanY);
            //If no wall found, move
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
            bool wallHit = translate.wallHitLeft(map.walls, pacmanX, pacmanY);
            //If no wall found, move
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
            bool wallHit = translate.wallHitRight(map.walls, pacmanX, pacmanY);
            //If no wall found, move
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

        //Special case teleport pacman
        //Right to left
        if (pacmanX == 29 && pacmanY == 18) {
            pacmanX = 1;
            transformPacmanX = 0;
        }
        //Left to right
        else if (pacmanX == 0 && pacmanY == 18) {
            pacmanX = 28;
            transformPacmanX = 27;
        }
        
        //------------------------MOVE PACMAN------------------------//

        //------------UP------------//
        if (up) {
            //Wall collision prevention
            bool wallHit = translate.wallHitUp(map.walls,pacmanX, pacmanY);

            //If wall is found, dont move that direction
            if (wallHit) { 
                up = false;
            }
            //If there is no wall, pacman can move
            if (!wallHit) {
                resetTransformationValues = translate.translateUp(up, resetTransformationValues, pacmanX, pacmanY, transformPacmanX,
                                                                  transformPacmanY, pacTime, frameCounter, pacShaderProgram, 0);
                pacmanX = translate.rObjX;
                pacmanY = translate.rObjY;
                transformPacmanX = translate.rTraObjX;
                transformPacmanY = translate.rTraObjY;
                frameCounter = translate.frameCounter;
            }
        }
        //------------DOWN------------//
        if (down) {
            //Wall collision prevention
            bool wallHit = translate.wallHitDown(map.walls, pacmanX, pacmanY);

            //If no wall found, move
            if (wallHit) {
                down = false;
            }

            //If there is no wall, pacman can move
            if (!wallHit) {
                resetTransformationValues = translate.translateDown(down, resetTransformationValues, pacmanX, pacmanY, transformPacmanX,
                                                                    transformPacmanY, pacTime, frameCounter, pacShaderProgram, 0);
                pacmanX = translate.rObjX;
                pacmanY = translate.rObjY;
                transformPacmanX = translate.rTraObjX;
                transformPacmanY = translate.rTraObjY;
                frameCounter = translate.frameCounter;
            }
        }
        //------------LEFT------------//
        if (left) {
            //Wall collision prevention
            bool wallHit = translate.wallHitLeft(map.walls, pacmanX, pacmanY);

            //If no wall found, move
            if (wallHit) {
                left = false;
            }
            //If there is no wall, pacman can move
            if (!wallHit) {
                resetTransformationValues = translate.translateLeft(left, resetTransformationValues, pacmanX, pacmanY, transformPacmanX,
                                                                    transformPacmanY, pacTime, frameCounter, pacShaderProgram, 0);
                pacmanX = translate.rObjX;
                pacmanY = translate.rObjY;
                transformPacmanX = translate.rTraObjX;
                transformPacmanY = translate.rTraObjY;
                frameCounter = translate.frameCounter;
            }
        }
        //------------RIGHT------------//
        if (right) {
            //Wall collision prevention
            bool wallHit = translate.wallHitRight(map.walls, pacmanX, pacmanY);

            //If no wall found, move
            if (wallHit) {
                right = false;
            }

            //If there is no wall, pacman can move
            if (!wallHit) {
                resetTransformationValues = translate.translateRight(right, resetTransformationValues, pacmanX, pacmanY, transformPacmanX, 
                                                                     transformPacmanY, pacTime, frameCounter, pacShaderProgram, 0);
                pacmanX = translate.rObjX;
                pacmanY = translate.rObjY;
                transformPacmanX = translate.rTraObjX;
                transformPacmanY = translate.rTraObjY;
                frameCounter = translate.frameCounter;
            }
        }

        //Camera for the pacman object
        app.Camera(currentTime, pacShaderProgram);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);


        //---------------GHOSTS---------------------//
        
        //Releases ghosts when player starts the game
        if (right || left || startGame) {
            
            //Zeros out a timer to use when spawning ghosts one at a time
            if (!startGame) {
                tempGhostTime = currentTime;
            }

            startGame = true;
            
            //Ghost One
            if (currentTime > tempGhostTime + 3.f) {

                auto gVertexColorLocationOne = glGetUniformLocation(ghostShaderProgramOne, "u_Color");
                auto slotLocation1 = glGetUniformLocation(ghostShaderProgramOne, "uTextureA");

                glUseProgram(ghostShaderProgramOne);

                startOne = true;
                ghostOne->newMove(currentTime, map.walls, ghostShaderProgramOne);
                ghostOneDir = ghostOne->returnCurDir();
                if (currentTime > ghostOneAniTime + 0.4f) {
                    ghostOneAniTime = currentTime;
                    ghostOneAniState = !ghostOneAniState;
                }

                switch(ghostOneDir) {
                    case 'U': (ghostOneAniState) ? glBindVertexArray(ghostOneAU) : glBindVertexArray(ghostOneBU); break;
                    case 'D': (ghostOneAniState) ? glBindVertexArray(ghostOneAD) : glBindVertexArray(ghostOneBD); break;
                    case 'L': (ghostOneAniState) ? glBindVertexArray(ghostOneAL) : glBindVertexArray(ghostOneBL); break;
                    case 'R': (ghostOneAniState) ? glBindVertexArray(ghostOneAR) : glBindVertexArray(ghostOneBR); break;
                }
                
                glUniform1i(slotLocation1, 0);

                app.Camera(currentTime, ghostShaderProgramOne);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);        
            }
            
            

            //Ghost Two
            if (currentTime > tempGhostTime + 6.f) {

                auto gVertexColorLocationTwo = glGetUniformLocation(ghostShaderProgramTwo, "u_Color");
                auto slotLocation2 = glGetUniformLocation(ghostShaderProgramTwo, "uTextureA");

                glUseProgram(ghostShaderProgramTwo);

                startTwo = true;
                ghostTwo->newMove(currentTime, map.walls, ghostShaderProgramTwo);
                ghostTwoDir = ghostTwo->returnCurDir();
                if (currentTime > ghostTwoAniTime + 0.4f) {
                    ghostTwoAniTime = currentTime;
                    ghostTwoAniState = !ghostTwoAniState;
                }

                switch (ghostTwoDir) {
                case 'U': (ghostTwoAniState) ? glBindVertexArray(ghostTwoAU) : glBindVertexArray(ghostTwoBU); break;
                case 'D': (ghostTwoAniState) ? glBindVertexArray(ghostTwoAD) : glBindVertexArray(ghostTwoBD); break;
                case 'L': (ghostTwoAniState) ? glBindVertexArray(ghostTwoAL) : glBindVertexArray(ghostTwoBL); break;
                case 'R': (ghostTwoAniState) ? glBindVertexArray(ghostTwoAR) : glBindVertexArray(ghostTwoBR); break;
                }

                glUniform1i(slotLocation2, 0);

                app.Camera(currentTime, ghostShaderProgramTwo);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
            }
            

            //Ghost Three
            if (currentTime > tempGhostTime + 9.f) {

                auto gVertexColorLocationThree = glGetUniformLocation(ghostShaderProgramThree, "u_Color");
                auto slotLocation3 = glGetUniformLocation(ghostShaderProgramThree, "uTextureA");

                glUseProgram(ghostShaderProgramThree);

                startThree = true;
                ghostThree->newMove(currentTime, map.walls, ghostShaderProgramThree);
                ghostThreeDir = ghostThree->returnCurDir();
                if (currentTime > ghostThreeAniTime + 0.4f) {
                    ghostThreeAniTime = currentTime;
                    ghostThreeAniState = !ghostThreeAniState;
                }

                switch (ghostThreeDir) {
                case 'U': (ghostThreeAniState) ? glBindVertexArray(ghostThreeAU) : glBindVertexArray(ghostThreeBU); break;
                case 'D': (ghostThreeAniState) ? glBindVertexArray(ghostThreeAD) : glBindVertexArray(ghostThreeBD); break;
                case 'L': (ghostThreeAniState) ? glBindVertexArray(ghostThreeAL) : glBindVertexArray(ghostThreeBL); break;
                case 'R': (ghostThreeAniState) ? glBindVertexArray(ghostThreeAR) : glBindVertexArray(ghostThreeBR); break;
                }

                glUniform1i(slotLocation3, 0);

                app.Camera(currentTime, ghostShaderProgramThree);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
            }
            

            
            //Ghost Four 
            if (currentTime > tempGhostTime + 12.f) {

                auto gVertexColorLocationFour = glGetUniformLocation(ghostShaderProgramFour, "u_Color");
                auto slotLocation4 = glGetUniformLocation(ghostShaderProgramFour, "uTextureA");

                glUseProgram(ghostShaderProgramFour);

                startFour = true;
                ghostFour->newMove(currentTime, map.walls, ghostShaderProgramFour);
                ghostFourDir = ghostFour->returnCurDir();
                if (currentTime > ghostFourAniTime + 0.4f) {
                    ghostFourAniTime = currentTime;
                    ghostFourAniState = !ghostFourAniState;
                }

                switch (ghostFourDir) {
                case 'U': (ghostFourAniState) ? glBindVertexArray(ghostFourAU) : glBindVertexArray(ghostFourBU); break;
                case 'D': (ghostFourAniState) ? glBindVertexArray(ghostFourAD) : glBindVertexArray(ghostFourBD); break;
                case 'L': (ghostFourAniState) ? glBindVertexArray(ghostFourAL) : glBindVertexArray(ghostFourBL); break;
                case 'R': (ghostFourAniState) ? glBindVertexArray(ghostFourAR) : glBindVertexArray(ghostFourBR); break;
                }

                glUniform1i(slotLocation4, 0);

                app.Camera(currentTime, ghostShaderProgramFour);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
            }
            

            
            //Makes sure ghosts have spawned before we check collision with pacman
            if (ghostOne->pacmanGhostCollision(transformPacmanX, transformPacmanY) && startOne) {
                gameOver = true;
            }
            if (ghostTwo->pacmanGhostCollision(transformPacmanX, transformPacmanY) && startTwo) {
                gameOver = true;
            }
            if (ghostThree->pacmanGhostCollision(transformPacmanX, transformPacmanY) && startThree) {
                gameOver = true;
            }
            if (ghostFour->pacmanGhostCollision(transformPacmanX, transformPacmanY) && startFour) {
                gameOver = true;
            }

        }


       

        //Freezes the screen if pacman wins or dies
        if (!stopGame) {
            glfwSwapBuffers(win.myWindow);
        }
        if (gameOver) {
            stopGame = true;
        }
        // Exit the loop if escape is pressed
        if (glfwGetKey(win.myWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            
           break;
        }
        

    }

    glUseProgram(0);
    glDeleteProgram(gameShaderProgram);
    glDeleteProgram(pacShaderProgram);
    glDeleteProgram(ghostShaderProgramOne);
    glDeleteProgram(ghostShaderProgramTwo);
    glDeleteProgram(ghostShaderProgramThree);
    glDeleteProgram(ghostShaderProgramFour);
    glDeleteTextures(1, &texture0);


    for (auto val : wallVAO) {
        app.CleanVAO(val);
    }
    for (auto val : pelletVAO) {
        app.CleanVAO(val.first.first);
    }
    app.CleanVAO(pacmanVAOA);
    app.CleanVAO(pacmanVAOB);
    app.CleanVAO(pacmanVAOC);
    app.CleanVAO(pacmanVAOD);

    app.CleanVAO(ghostOneAU); app.CleanVAO(ghostTwoAU); app.CleanVAO(ghostThreeAU); app.CleanVAO(ghostFourAU);
    app.CleanVAO(ghostOneBU); app.CleanVAO(ghostTwoBU); app.CleanVAO(ghostThreeBU); app.CleanVAO(ghostFourBU);
    app.CleanVAO(ghostOneAD); app.CleanVAO(ghostTwoAD); app.CleanVAO(ghostThreeAD); app.CleanVAO(ghostFourAD);
    app.CleanVAO(ghostOneBD); app.CleanVAO(ghostTwoBD); app.CleanVAO(ghostThreeBD); app.CleanVAO(ghostFourBD);
    app.CleanVAO(ghostOneAL); app.CleanVAO(ghostTwoAL); app.CleanVAO(ghostThreeAL); app.CleanVAO(ghostFourAL);
    app.CleanVAO(ghostOneBL); app.CleanVAO(ghostTwoBL); app.CleanVAO(ghostThreeBL); app.CleanVAO(ghostFourBL);
    app.CleanVAO(ghostOneAR); app.CleanVAO(ghostTwoAR); app.CleanVAO(ghostThreeAR); app.CleanVAO(ghostFourAR);
    app.CleanVAO(ghostOneBR); app.CleanVAO(ghostTwoBR); app.CleanVAO(ghostThreeBR); app.CleanVAO(ghostFourBR);

    glfwTerminate();

    return EXIT_SUCCESS;
}




GLuint load_opengl_texture(const std::string& filepath, GLuint slot)
{
    /**
     *  - Use the STB Image library to load a texture in here
     *  - Initialize the texture into an OpenGL texture
     *    - This means creating a texture with glGenTextures or glCreateTextures (4.5)
     *    - And transferring the loaded texture data into this texture
     *    - And setting the texture format
     *  - Finally return the valid texture
     */

     /** Image width, height, bit depth */
    int w, h, bpp;
    auto pixels = stbi_load(filepath.c_str(), &w, &h, &bpp, 0);

    /*Generate a texture object and upload the loaded image to it.*/
    GLuint tex;
    glGenTextures(1, &tex);
    glActiveTexture(GL_TEXTURE0 + slot);//Texture Unit
    glBindTexture(GL_TEXTURE_2D, tex);

    if (pixels)
    {

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {           
        std::cout << stbi_failure_reason();
        std::cout << "\nFailed to load texture" << std::endl;
    }

    /** Set parameters for the texture */
    //Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //Filtering 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /** Very important to free the memory returned by STBI, otherwise we leak */
    if (pixels)
        stbi_image_free(pixels);

    return tex;
}
