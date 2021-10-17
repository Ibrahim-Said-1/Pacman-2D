#include "Wall.h"

/**
*   Creates a wall using the vector of wall coordinates
*/
GLuint Wall::CreateWalls(GLuint squareShaderProgram, int i, int j)
{

    GLfloat square[4 * 3] =
    {
        i ,       j,       0.0f,
        i ,       j - 1,   0.0f,
        i - 1,    j - 1,   0.0f,
        i - 1,    j,       0.0f,
    };

    GLuint square_indices[6] = { 0,1,2,0,2,3 };

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (const void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_DYNAMIC_DRAW);

    return vao;
}

