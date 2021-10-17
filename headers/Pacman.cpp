#include "Pacman.h"

/**
*   Creates pacman with texture and coordinates
*/
GLuint Pacman::createPacman(GLuint squareShaderProgram, int i, int j, char animation)
{
    float x = 0.f, y=0.f;
    if (animation == 'A') {
        x = 0.1f; y = 0.f; // coordinates of sub picture
    }
    if (animation == 'B') {
        x = 1.1f; y = 0.f;
    }
    if (animation == 'C') {
        x = 2.1f; y = 0.f;
    }
    if (animation == 'D') {
        x = 3.1f; y = 0.f;
    }
    
    float sheetWidth = 440.f, sheetHeight = 290.f;
    float spriteWidth = 70.f, spriteHeight = 73.f;
    float a = (x * spriteWidth) / sheetWidth;
    float b = (y * spriteHeight) / sheetHeight;
    float c = ((x + 1.f) * spriteWidth) / sheetWidth;
    float d = ((y + 1.f) * spriteHeight) / sheetHeight;

    GLfloat diamond[4 * 7] =
    {
        /*
      |position              |color             |texture coord*/
       i ,       j,           1.0f, 1.0f, 1.0f,    a,   d,     // top right
       i ,       j - 1.f,     1.0f, 1.0f, 1.0f,    c,   d,     // bottom right
       i - 1.f,  j - 1.f,     1.0f, 1.0f, 1.0f,    c,   b,     // bottom left
       i - 1.f,  j,           1.0f, 1.0f, 1.0f,    a,   b,     // top left
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
    GLint posAttrib = glGetAttribLocation(squareShaderProgram, "aPosition");
    GLint colorAttrib = glGetAttribLocation(squareShaderProgram, "aColor");
    GLint texAttrib = glGetAttribLocation(squareShaderProgram, "aTexcoord");

    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (const void*)0);
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (const void*)8);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (const void*)20);
    glEnableVertexAttribArray(posAttrib);
    glEnableVertexAttribArray(colorAttrib);
    glEnableVertexAttribArray(texAttrib);



    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    return vao;
}
