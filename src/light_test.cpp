#include <iostream>
using namespace std;
#define GLEW_STATIC	
#include "Shader.h"
#include "Camera.h"
#include "LightPoint.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// 简化的光照模型：冯氏光照模型(把光源的颜色与物体的颜色值相乘，得到物体所反射的颜色,将光源显示为可见的物体(投光物)，需要给投光物单独设置一个顶点着色器和一个片元着色器。)
// 
// 冯氏光照模型由 3 个分量组成:环境(Ambient)光照,漫反射(Diffuse)光照,镜面(Specular)光照
// 环境(Ambient)光照:物体几乎永远不会是完全黑暗,需要使用环境光照常量，永远给物体一些颜色
// 漫反射(Diffuse)光照:模拟光源对物体的方向行影响，物体的某部分越是正对着光源，它就会越亮（需要测量光源光线是以什么角度接触物体表面）
// 镜面(Specular)光照:模拟有光泽物体上面出现的亮点，镜面光照的颜色相比于物体的本身颜色会更倾向于光的颜色（和漫反射光照一样，镜面光照也是依据光的方向向量和物体的法向量来决定的，但是它也依赖于观察方向，例如玩家是从什么方向看着这个片段的。通过反射法向量周围光的方向来计算反射向量。然后计算反射向量和视线方向的角度差，如果夹角越小，那么镜面光的影响就会越大）


float vertices[] = {
    // x、y、z 坐标				// color				// normal
    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,	// red 红色面
     0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	// green 绿色面
     0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f, 	// blue 蓝色面(不是图中那种蓝)
    -0.5f,  0.5f, -0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,

     0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,	// yellow 黄色面
     0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f, 	// purple 紫色面
     0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,	// cyan 青蓝色面
     0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f
};

const GLint WIDTH = 800, HEIGHT = 600;

// 缓冲渲染两帧之差 的时间
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// 初始化摄像机的位置    position                        Up_Y
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 5.0f, 0.0f));

//初始化鼠标光标的位置在屏幕中心
GLdouble lastX = WIDTH / 2.0f;
GLdouble lastY = HEIGHT / 2.0f;

// 判断是否是第一次进入程序
GLboolean firstMouse = true;

// 光源位置初始化
glm::vec3 LightPos = glm::vec3(0.0f, 0.0f, 1.0f);

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


void processKeyInput(GLFWwindow* window)
{
    // esc退出窗口
    // 使用glfwGetKey判断键是否按下，第一次参数：对应的窗口，第二个参数：对应的键（glfw定义的常量）
    // 该键按下，glfeGetKey返回GLFW_PRESS(值为1)
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    // WS：前后   QE：左右  AD：上下
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
    //初始化GLFW
    glfwInit();

    //声明版本与核心
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);              //主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);              //次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);                   // 缩放关闭 

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "light point test", nullptr, nullptr);
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

    // 隐藏鼠标的光标 光标会一直停留在窗口中
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //监听鼠标移动事件 回调鼠标响应函数
    glfwSetCursorPosCallback(window, mouse_callback);
    //监听鼠标滚轮的移动 回调鼠标滚轮函数
    glfwSetScrollCallback(window, scroll_callback);


    // 隐藏鼠标光标，光标一直停留在窗口
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // 使用glad寻找opengl函数地址，调用opengl函数前需要初始化glad
    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //{
    //    cout << "Failed to initialize GLAD" << endl;
    //    return -1;
    //}

    glewInit();

    // 新建一个光源(必须在 glew 初始化后才行)
    LightPoint light = LightPoint();


    glEnable(GL_DEPTH_TEST);

    Shader myShader("shader_light_v.txt", "shader_light_f.txt");
    Shader lightShader("light_v.txt", "light_f.txt");

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 复制顶点数据到缓冲内存中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 顶点位置
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // 顶点颜色
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // 顶点法线
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    while (!glfwWindowShouldClose(window))
    {
        // 计算上下两帧的渲染时间差
        GLfloat currentTime = GLfloat(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = deltaTime;

        processKeyInput(window);

        // 清除缓存
        glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);

        glm::mat4 projection;

        glm::mat4 viewMatrix = camera.GetViewMatrix();

        // glm::perspective函数创建透视投影矩阵（通过把观察空间投影到世界空间得到的裁剪空间）
        // 第一个参数：观察空间的大小（视野大小）
        // 第二个参数：宽高比。可由窗口的宽除以高所得。
        // 第三个参数：平截头体的近平面，通常设置为 0.1f
        // 第四个参数：平截头体的远平面，通常设置为 100.0f
        // 通过传递变化的Zoom值作为视角角度，实现缩放功能
        projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

        // 光照绘制,光源旋转
        lightShader.Use();
        glm::mat4 transform_light = glm::translate(transform_light, glm::vec3(1.8f * cos(currentTime), 1.8f * sin(currentTime), 0.0f));
        transform_light = glm::scale(transform_light, glm::vec3(0.15f * (abs(cos(currentTime * 0.5 + 0.25 * acos(-1.0))) + 0.5),
            0.15f * (abs(cos(currentTime * 0.5 + 0.25 * acos(-1.0))) + 0.5),
            0.15f * (abs(cos(currentTime * 0.5 + 0.25 * acos(-1.0))) + 0.5)));
        transform_light = glm::rotate(transform_light, currentTime, glm::vec3(0.5f, 0.5f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "transform_light"), 1, GL_FALSE, glm::value_ptr(transform_light));
        glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "project_light"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "view_light"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        light.draw(lightShader);

        // 中间正方形绘制
        myShader.Use();
        glm::mat4 transform = glm::rotate(transform, currentTime, glm::vec3(0.2f, 1.0f, 0.0f));
        transform = glm::scale(transform, glm::vec3(0.6f, 0.6f, 0.6f));
        glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
        glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

        int lightPosLocation = glGetUniformLocation(myShader.Program, "LightPos");
        glUniform3f(lightPosLocation, LightPos.x, LightPos.y, LightPos.z);
        int cameraPosLocation = glGetUniformLocation(myShader.Program, "CameraPos");
        glUniform3f(cameraPosLocation, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


        glDrawArrays(GL_TRIANGLES, 0, 36);



        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}











