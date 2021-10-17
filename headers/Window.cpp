#include "Window.h"


/**
*   Creates fixed aspect ratio when fullscreen and gives resizable window functionality.
*
*  @param window - glfw window for resizing.
*  @param width  - recieves width of the window.
*  @param height - recieves height of the window.
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    int a = 28;
    int b = 36;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // The "Graphics" width and height contain the desired pixel resolution to keep.
    glOrtho(0.0, a, b, 0.0, 1.0, -1.0);
    // Calculate the proper aspect ratio to use based on window ratio
    auto ratioX = width / (float)a;
    auto ratioY = height / (float)b;
    auto ratio = ratioX < ratioY ? ratioX : ratioY;
    // Calculate the width and height that the will be rendered to
    auto viewWidth = a * ratio;
    auto viewHeight = b * ratio;
    // Calculate the position
    auto viewX = ((width - a * ratio) / 2);
    auto viewY = ((height - b * ratio) / 2);
    // Apply the viewport and switch back to the GL_MODELVIEW matrix mode
    glViewport(viewX, viewY, viewWidth, viewHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



bool Window::setUpWindow()
{
  

    // Initialization of GLFW
    if (!glfwInit())
    {
        std::cerr << "GLFW initialization failed." << '\n';

        std::cin.get();

        return EXIT_FAILURE;
    }

    // Setting window hints
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    myWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);

    if (myWindow == nullptr)
    {
        std::cerr << "GLFW failed on window creation." << '\n';
        std::cin.get();

        glfwTerminate();

        return EXIT_FAILURE;
    }

    //Set the OpenGL context
    glfwMakeContextCurrent(myWindow);

    glfwSetFramebufferSizeCallback(myWindow, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }


    

    // Error function for OpenGL
    auto GLAPIENTRY
        MessageCallback = [](GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* userParam)
    {
        std::cerr << "GL CALLBACK:" << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") <<
            "type = 0x" << type <<
            ", severity = 0x" << severity <<
            ", message =" << message << "\n";
    };

    // Eanable capture of debug output.
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, 0);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    return 1;
}
