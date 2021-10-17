#pragma once

#include "Libraries.h"

class Window
{
public:
    GLFWwindow* myWindow = nullptr;
    GLuint windowWidth, windowHeight;
    const char* windowTitle;


public:

    Window::Window(const char* title, GLuint width, GLuint height)
    {
        windowWidth = width;
        windowHeight = height;
        windowTitle = title;
    }
    
    bool setUpWindow();

};