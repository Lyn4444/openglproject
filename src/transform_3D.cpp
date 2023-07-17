// Ҫ��Ⱦ�����壬һ����Ҫ36�����㣨6��*һ������2��������*һ����������3�����㣩
// ��Ϊ���������ϵ��OpenGl����ϵ��ͬ������ʹ����������ϵ����zΪ-0.5fʱ����ʾ������

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
    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	// red ��ɫ��
     0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,	// green ��ɫ��
     0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,	// blue ��ɫ��
    -0.5f,  0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,

     0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,	// yellow ��ɫ��
     0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	// purple ��ɫ��
     0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,	// cyan ��ɫ��
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
    // �汾���ã�֧��3.0ϵ�а汾
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // ����mac
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // �ر�����
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(width, height, "3D transform test", nullptr, nullptr);
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glfwMakeContextCurrent(window);
    glewInit();

    // ������Ȳ��ԣ�Ĭ�Ϲرգ�
    // ��Ȼ���(Z ����)������ OpenGL ������ʱ����һ�����ض���ʱ������
    // ���ֵ�洢��ÿ��Ƭ�����棨��ΪƬ�ε� z ֵ��,��Ƭ����Ҫ���������ɫʱ��OpenGL �Ὣ�������ֵ�� z ������бȽϣ������ǰ��Ƭ��������Ƭ��֮�������ᱻ���������򽫻Ḳ�ǡ�
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
        // �����ɫ�������Ȳ��Ի���
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // ����
        myShader.Use();
        // ʹ��for ѭ����n = 2,ͬʱ����2��ͼ��
        glBindVertexArray(VAO);

        for (int i = 0; i < 2; i++)
        {
            GLfloat time = glfwGetTime();
            // ��ʼ������
            glm::mat4 transform_matrix;

            // glm:scale����������
            // ��һ��������ԭʼ����
            // �ڶ�����������x��y��z�����ų̶ȣ���׼��СΪ1.0f����vec3
            // 
            // glm::rotate��������ת
            // ��һ��������ԭʼ����
            // �ڶ�����������ת�Ƕȣ�����time�仯������ת����ת�Ƕ�
            // ��������������ת��ָ������ת������ԭ�򣬲�����y��ķ��������ת��
            if (i == 0)
            {
                transform_matrix = glm::scale(transform_matrix, glm::vec3(0.6f, 0.6f, 0.6f));
                transform_matrix = glm::rotate(transform_matrix, time, glm::vec3(0.2f, 1.0f, 0.0f));
            }
            else
            {
                // glm::translate������ƽ��
                // Բ��ʽ��x^2 + y^2 = 1����cos(t)^2 + sin(t)^2=1
                // ���Ҫ������Բ��ת��ֻҪx=cos(time),y=sin(time)
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

