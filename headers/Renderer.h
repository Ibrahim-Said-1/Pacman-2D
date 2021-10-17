


class Render
{
public:


 // -----------------------------------------------------------------------------
 // COMPILE SHADER
 // -----------------------------------------------------------------------------
    GLuint CompileShader(const std::string& vertexShaderSrc,
                          const std::string& fragmentShaderSrc)
    {

        auto vertexSrc = vertexShaderSrc.c_str();
        auto fragmentSrc = fragmentShaderSrc.c_str();

        auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
        glCompileShader(vertexShader);

        auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
        glCompileShader(fragmentShader);

        auto shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);

        glBindFragDataLocation(shaderProgram, 0, "outColor");
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
    }


    // -----------------------------------------------------------------------------
    // Clean VAO
    // -----------------------------------------------------------------------------
    void CleanVAO(GLuint& vao)
    {
        GLint nAttr = 0;
        std::set<GLuint> vbos;

        GLint eboId;
        glGetVertexArrayiv(vao, GL_ELEMENT_ARRAY_BUFFER_BINDING, &eboId);
        glDeleteBuffers(1, (GLuint*)&eboId);

        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAttr);
        glBindVertexArray(vao);

        for (int iAttr = 0; iAttr < nAttr; ++iAttr)
        {
            GLint vboId = 0;
            glGetVertexAttribiv(iAttr, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &vboId);
            if (vboId > 0)
            {
                vbos.insert(vboId);
            }

            glDisableVertexAttribArray(iAttr);
        }

        for (auto vbo : vbos)
        {
            glDeleteBuffers(1, &vbo);
        }

        glDeleteVertexArrays(1, &vao);
    }


// -----------------------------------------------------------------------------
//  Transformation of pacman, using rotation
// -----------------------------------------------------------------------------
    void Transform(float time, float timeY, const char direction, const GLuint shaderprogram)
    {

        glm::mat4 translation = glm::translate(glm::mat4(1.f), glm::vec3(-0.5f, -17.5f, 0.f));
        glm::mat4 translationMove = glm::translate(glm::mat4(1.f), glm::vec3(time+0.5f, timeY+17.5f, 0.f));

        //                                 base matrix      degrees to rotate        axis to rotate around
        glm::mat4 rotation;
        switch (direction) {
        case 'U':  rotation = glm::rotate(glm::mat4(1.f), glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));  break;
        case 'D':  rotation = glm::rotate(glm::mat4(1.f), glm::radians(-90.f), glm::vec3(0.f, 0.f, 1.f));  break;
        case 'L':  rotation = glm::rotate(glm::mat4(1.f), glm::radians(180.f), glm::vec3(0.f, 0.f, 1.f)); break;
        case 'R':  rotation = glm::rotate(glm::mat4(1.f), glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));  break;
        }

        //Create transformation matrix
        glm::mat4 transformation = translationMove * rotation * translation;


        //Get uniform to place transformation matrix in
        GLuint transformationmat = glGetUniformLocation(shaderprogram, "u_TransformationMat");

        //Send data from matrices to uniform
        glUniformMatrix4fv(transformationmat, 1, false, glm::value_ptr(transformation));
     }

// -----------------------------------------------------------------------------
//  Transformation of ghosts, without the use of rotation
// -----------------------------------------------------------------------------
    void Transform(float time, float timeY, const GLuint shaderprogram)
    {
        glm::mat4 translation = glm::translate(glm::mat4(1.f), glm::vec3(time, timeY, 0.f));

        //Create transformation matrix 
        glm::mat4 transformation = translation;


        //Get uniform to place transformation matrix in
        GLuint transformationmat = glGetUniformLocation(shaderprogram, "u_TransformationMat");

        //Send data from matrices to uniform
        glUniformMatrix4fv(transformationmat, 1, false, glm::value_ptr(transformation));
    }
    

    // -----------------------------------------------------------------------------
    // Camera 
    // -----------------------------------------------------------------------------
    void Camera(const float time, const GLuint shaderprogram)
    {

        glm::mat4 projection = glm::ortho(0.0f, 28.0f, 0.0f, 36.0f);

        //Get unforms to place our matrices into
        GLuint projmat = glGetUniformLocation(shaderprogram, "u_ProjectionMat");

         //Send data from matrices to uniform
        glUniformMatrix4fv(projmat, 1, false, glm::value_ptr(projection));
    }

};