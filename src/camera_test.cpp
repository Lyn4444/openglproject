#include <iostream>
using namespace std;
#define GLEW_STATIC	
#include "Shader.h"
#include "Camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// #include <SOIL2/stb_image.h>
// #include <SOIL2/SOIL2.h>


float vertices[] = {
    // x��y��z ����				// color
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

const GLint WIDTH = 800, HEIGHT = 600;

// ������Ⱦ��֮֡�� ��ʱ��
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// ��ʼ���������λ��
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));

//��ʼ��������λ������Ļ����
GLdouble lastX = WIDTH / 2.0f;
GLdouble lastY = HEIGHT / 2.0f;

// �ж��Ƿ��ǵ�һ�ν������
GLboolean firstMouse = true;

// ���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ�������
// �Դ���ע��һ���ص�����(Callback Function)��������ÿ�δ��ڴ�С��������ʱ�򱻵���
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // glViewport����ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�
    glViewport(0, 0, width, height);
}


// ��Ӧ����¼� �������Ļص�����
// ����λ��posX, posY
void mouse_callback(GLFWwindow* window, double posX, double posY)
{
    // ��һ�ν���,��¼��ǰ���λ����Ϊ��ʼ�����λ��
    if (firstMouse)
    {
        lastX = posX;
        lastY = posY;
        firstMouse = false;
    }

    double xoffset = posX - lastX;
    // ��������������� ʵ�ʲ��������������ƶ������ ����Ҳ����������ƶ� ʵ��Ӧ������
    double yoffset = lastY - posY;

    lastX = posX;
    lastY = posY;

    camera.ProcessMouseMovement(xoffset, yoffset);

}

// ��Ӧ������
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}


void processKeyInput(GLFWwindow* window)
{
    // esc�˳�����
    // ʹ��glfwGetKey�жϼ��Ƿ��£���һ�β�������Ӧ�Ĵ��ڣ��ڶ�����������Ӧ�ļ���glfw����ĳ�����
    // �ü����£�glfeGetKey����GLFW_PRESS(ֵΪ1)
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    // WS��ǰ��   QE������  AD������
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(UPWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(DOWNWARD, deltaTime);
    }
}


int main()
{
    //��ʼ��GLFW
    glfwInit();

    //�����汾�����
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);              //���汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);              //�ΰ汾��
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);                   // ���Źر� 

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "camera test", nullptr, nullptr);
    if (window == nullptr)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    // �������֮����Ҫ�õ�ǰ���ڵĻ����ڵ�ǰ�߳��ϳ�Ϊ��ǰ���������ǽ������Ļ�ͼ���ử�ڸոմ����Ĵ�����
    glfwMakeContextCurrent(window);
    // �����ڵ�����С��ʱ������������
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // �������Ĺ�� ����һֱͣ���ڴ�����
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //��������ƶ��¼� �ص������Ӧ����
    glfwSetCursorPosCallback(window, mouse_callback);
    //���������ֵ��ƶ� �ص������ֺ���
    glfwSetScrollCallback(window, scroll_callback);


    // ��������꣬���һֱͣ���ڴ���
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // ʹ��gladѰ��opengl������ַ������opengl����ǰ��Ҫ��ʼ��glad
    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //{
    //    cout << "Failed to initialize GLAD" << endl;
    //    return -1;
    //}

    glewInit();
    glEnable(GL_DEPTH_TEST);

    Shader myShader("shader_camera_v.txt", "shader_camera_f.txt");

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // ���ƶ������ݵ������ڴ���
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {
        // ����������֡����Ⱦʱ���
        GLfloat currentTime = GLfloat(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = deltaTime;

        processKeyInput(window);

        // �������
        glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // ����
        myShader.Use();
        glBindVertexArray(VAO);

        glm::mat4 projection;

        glm::mat4 viewMatrix = camera.GetViewMatrix();

        // glm::perspective��������͸��ͶӰ����ͨ���ѹ۲�ռ�ͶӰ������ռ�õ��Ĳü��ռ䣩
        // ��һ���������۲�ռ�Ĵ�С����Ұ��С��
        // �ڶ�����������߱ȡ����ɴ��ڵĿ���Ը����á�
        // ������������ƽ��ͷ��Ľ�ƽ�棬ͨ������Ϊ 0.1f
        // ���ĸ�������ƽ��ͷ���Զƽ�棬ͨ������Ϊ 100.0f
        // ͨ�����ݱ仯��Zoomֵ��Ϊ�ӽǽǶȣ�ʵ�����Ź���
        projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

        

        for (int i = 0; i < 2; i++) {
            glm::mat4 transform;
            if (i == 0)
            {
                transform = glm::rotate(transform, currentTime, glm::vec3(0.2f, 1.0f, 0.0f));
                transform = glm::scale(transform, glm::vec3(0.6f, 0.6f, 0.6f));
            }
            else
            {
                transform = glm::translate(transform, glm::vec3(0.8f * cos(currentTime), 0.8f * sin(currentTime), 0.0f));
                transform = glm::scale(transform, glm::vec3(0.15f * (abs(cos(currentTime * 0.5 + 0.25 * acos(-1.0))) + 0.5),
                    0.15f * (abs(cos(currentTime * 0.5 + 0.25 * acos(-1.0))) + 0.5),
                    0.15f * (abs(cos(currentTime * 0.5 + 0.25 * acos(-1.0))) + 0.5)));
                transform = glm::rotate(transform, currentTime, glm::vec3(0.5f, 0.5f, 0.0f));
            }

            glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
            glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
