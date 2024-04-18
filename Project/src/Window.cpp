#include "Window.h"

#include "Debug.h"

Window::Window()
    :
    Window(DEFAULT_WIDTH, DEFAULT_HEIGHT, m_Name)
{
}

Window::Window(unsigned short width, unsigned short height, const std::string& name)
    :
    m_Name(name),
    m_Width(width),
    m_Height(height)
{
    /* Initialize the library */
    if (!glfwInit())
        exit(-1);

    /* Window creation hints */
    setWindowHints();

    /* Create a windowed mode window and its OpenGL context */
    m_Window = createWindow(width, height, name);

    if (!m_Window)
        Debug::throwException(*this, "Unable to create GLFWwindow instance!");

    /* Make the window's context current */
    glfwMakeContextCurrent(m_Window);

    Debug::printMessage(*this, "OpenGL " + *glGetString(GL_VERSION), DebugSeverityLevel::OK);

    if (glewInit() != GLEW_OK)
        Debug::throwException(*this, "ERROR: GLEW unable to be initialized!");

    enableFeatures(m_Window);
    setClearColor(0.025f, 0.0f, 0.125f);
}

GLFWwindow* Window::getWindowPointer() const
{
    return m_Window;
}

const unsigned short& Window::getWidth() const
{
    return m_Width;
}

const unsigned short& Window::getHeight() const
{
    return m_Height;
}

GLFWwindow* Window::createWindow(const unsigned short& width, const unsigned short& height, const std::string& name)
{
    GLFWwindow* window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        printf("ERROR: Unable to create window!\n");
        exit(-1);
    }

    return window;
}

void Window::setWindowHints()
{
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
}

void Window::setClearColor(float r, float g, float b)
{
    glClearColor(r, g, b, 1.0f);
}

void Window::enableFeatures(const GLFWwindow* window)
{
    glEnable(GL_DEBUG_OUTPUT);
    // glDebugMessageCallback(MessageCallback, NULL);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSwapInterval(1);
}
