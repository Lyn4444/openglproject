#include <iostream>
using namespace std;
#define GLEW_STATIC	
#include "Shader.h"
#include "Camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <SOIL2/SOIL2.h>
#include <SOIL2/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


float vertices[] = {
    // x、y、z 坐标				// color
    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	// red 红色面
     0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,	// green 绿色面
     0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,	// blue 蓝色面
    -0.5f,  0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,

     0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,	// yellow 黄色面
     0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	// purple 紫色面
     0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,	// cyan 青色面
     0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,
};

const GLint WIDTH = 800, HEIGHT = 600;

// 缓冲渲染两帧之差 的时间
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// 初始化摄像机的位置
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));

//初始化鼠标光标的位置在屏幕中心
GLdouble lastX = WIDTH / 2.0f;
GLdouble lastY = HEIGHT / 2.0f;

// 判断是否是第一次进入程序
GLboolean firstMouse = true;

// 当用户改变窗口的大小的时候，视口也应该被调整。
// 对窗口注册一个回调函数(Callback Function)，它会在每次窗口大小被调整的时候被调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // glViewport函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）
    glViewport(0, 0, width, height);
}


// 响应鼠标事件 创建鼠标的回调函数
// 鼠标的位置posX, posY
void mouse_callback(GLFWwindow* window, double posX, double posY)
{
    // 第一次进入,记录当前鼠标位置作为初始化鼠标位置
    if (firstMouse)
    {
        lastX = posX;
        lastY = posY;
        firstMouse = false;
    }

    double xoffset = posX - lastX;
    // 这里如果不反过来 实际操作过程中向上移动摄像机 物体也会跟着向上移动 实际应该向下
    double yoffset = lastY - posY;

    lastX = posX;
    lastY = posY;

    camera.ProcessMouseMovement(xoffset, yoffset);

}

// 响应鼠标滚动
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}


int main()
{
    //初始化GLFW
    glfwInit();

    //声明版本与核心
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);              //主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);              //次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);                   // 缩放关闭 

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "camera test", nullptr, nullptr);
    if (window == nullptr)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    // 创建完毕之后，需要让当前窗口的环境在当前线程上成为当前环境，就是接下来的画图都会画在刚刚创建的窗口上
    glfwMakeContextCurrent(window);
    // 当窗口调整大小的时候调用这个函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //监听鼠标移动事件 回调鼠标响应函数
    glfwSetCursorPosCallback(window, mouse_callback);
    //监听鼠标滚轮的移动 回调鼠标滚轮函数
    glfwSetScrollCallback(window, scroll_callback);

    // 隐藏鼠标光标，光标一直停留在窗口
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // 使用glad寻找opengl函数地址，调用opengl函数前需要初始化glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glewInit();
    glEnable(GL_DEPTH_TEST);

    Shader myShader("shader_camera_v.txt", "shader_camera_f.txt");

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 复制顶点数据到缓冲内存中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);





}

