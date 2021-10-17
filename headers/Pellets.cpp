#include "Pellets.h"

/**
*   Creates pellets with coordinates from the file   
*/
GLuint Pellet::CreatePellets(GLuint squareShaderProgram, int i, int j)
{

    GLfloat diamond[4 * 3] =
    {
        i - 0.55,       j - 0.15,         0.0f,
        i - 0.35,       j - 0.55,         0.0f,
        i - 0.55,       j - 0.95,         0.0f,
        i - 0.75,       j - 0.55,         0.0f,
    };

    GLuint indices[6] = { 0,1,2,0,2,3 };

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(diamond), diamond, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (const void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    return vao;
}


