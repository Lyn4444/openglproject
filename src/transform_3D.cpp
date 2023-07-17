// 要渲染立方体，一共需要36个顶点（6面*一个面有2个三角形*一个三角形有3个顶点）
// 因为计算机坐标系与OpenGl坐标系不同，所以使用左手坐标系并且z为-0.5f时将显示在正面

#include <iostream>
using namespace std;
#define GLEW_STATIC	
#include "Shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL2/stb_image.h>
#include <SOIL2/SOIL2.h>

GLfloat vertices[] =
{
    // position                 // r, g, b
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

const GLint width = 600, height = 600;

int main()
{
    glfwInit();
    // 版本设置，支持3.0系列版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 兼容mac
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // 关闭缩放
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(width, height, "3D transform test", nullptr, nullptr);
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glfwMakeContextCurrent(window);
    glewInit();

    // 开启深度测试（默认关闭）
    // 深度缓冲(Z 缓冲)：允许 OpenGL 决定何时覆盖一个像素而何时不覆盖
    // 深度值存储在每个片段里面（作为片段的 z 值）,当片段想要输出它的颜色时，OpenGL 会将它的深度值和 z 缓冲进行比较，如果当前的片段在其它片段之后，它将会被丢弃，否则将会覆盖。
    glEnable(GL_DEPTH_TEST);

    Shader myShader = Shader("shader_transform_3D_v.txt", "shader_transform_3D_f.txt");

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {
        
        glViewport(0, 0, screenWidth, screenHeight);
        glfwPollEvents();

        glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
        // 清除颜色缓冲和深度测试缓冲
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // 绘制
        myShader.Use();
        // 使用for 循环，n = 2,同时绘制2个图形
        glBindVertexArray(VAO);

        for (int i = 0; i < 2; i++)
        {
            GLfloat time = glfwGetTime();
            // 初始化矩阵
            glm::mat4 transform_matrix;

            // glm:scale：纹理缩放
            // 第一个参数：原始矩阵
            // 第二个参数：沿x，y，z的缩放程度（标准大小为1.0f）的vec3
            // 
            // glm::rotate：纹理旋转
            // 第一个参数：原始矩阵
            // 第二个参数：旋转角度（随着time变化），自转的旋转角度
            // 第三个参数：旋转轴指向方向（旋转是左手原则，并沿着y轴的方向进行旋转）
            if (i == 0)
            {
                transform_matrix = glm::scale(transform_matrix, glm::vec3(0.6f, 0.6f, 0.6f));
                transform_matrix = glm::rotate(transform_matrix, time, glm::vec3(0.2f, 1.0f, 0.0f));
            }
            else
            {
                // glm::translate：纹理平移
                // 圆公式：x^2 + y^2 = 1，且cos(t)^2 + sin(t)^2=1
                // 因此要让沿着圆旋转，只要x=cos(time),y=sin(time)
                transform_matrix = glm::translate(transform_matrix, glm::vec3(0.8f * cos(time), 0.8f * sin(time), 0.0f));
                transform_matrix = glm::scale(transform_matrix, glm::vec3(0.15f * (abs(cos(time * 0.5 + 0.25 * acos(-1.0))) + 0.5), 
                    0.15f * (abs(cos(time * 0.5 + 0.25 * acos(-1.0))) + 0.5),
                    0.15f * (abs(cos(time * 0.5 + 0.25 * acos(-1.0))) + 0.5)));
                transform_matrix = glm::rotate(transform_matrix, time, glm::vec3(0.5f, 0.5f, 0.0f));
            }

            int transform = glGetUniformLocation(myShader.Program, "transform");
            glUniformMatrix4fv(transform, 1, GL_FALSE, glm::value_ptr(transform_matrix));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

