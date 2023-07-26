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
#include <glm/gtx/rotate_vector.hpp>



// �򻯵Ĺ���ģ�ͣ����Ϲ���ģ��(�ѹ�Դ����ɫ���������ɫֵ��ˣ��õ��������������ɫ,����Դ��ʾΪ�ɼ�������(Ͷ����)����Ҫ��Ͷ���ﵥ������һ��������ɫ����һ��ƬԪ��ɫ����)
// 
// ���Ϲ���ģ���� 3 ���������:����(Ambient)����,������(Diffuse)����,����(Specular)����
// ����(Ambient)����:���弸����Զ��������ȫ�ڰ�,��Ҫʹ�û������ճ�������Զ������һЩ��ɫ
// ������(Diffuse)����:ģ���Դ������ķ�����Ӱ�죬�����ĳ����Խ�������Ź�Դ�����ͻ�Խ������Ҫ������Դ��������ʲô�ǶȽӴ�������棩
// ����(Specular)����:ģ���й�������������ֵ����㣬������յ���ɫ���������ı�����ɫ��������ڹ����ɫ�������������һ�����������Ҳ�����ݹ�ķ�������������ķ������������ģ�������Ҳ�����ڹ۲췽����������Ǵ�ʲô���������Ƭ�εġ�ͨ�����䷨������Χ��ķ��������㷴��������Ȼ����㷴�����������߷���ĽǶȲ����н�ԽС����ô������Ӱ��ͻ�Խ��


float vertices[] = {
    // x��y��z ����				// color				// normal
    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,	// red ��ɫ��
     0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	// green ��ɫ��
     0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f, 	// blue ��ɫ��(����ͼ��������)
    -0.5f,  0.5f, -0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,

     0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,	// yellow ��ɫ��
     0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f, 	// purple ��ɫ��
     0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,	// cyan ����ɫ��
     0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f
};

/*  �ɣ�ֻ���ƶ������λ�ã������ƶ��������Σ��ѹ۲�*/


//const GLint WIDTH = 800, HEIGHT = 600;
//
//// ������Ⱦ��֮֡�� ��ʱ��
//GLfloat deltaTime = 0.0f;
//GLfloat lastTime = 0.0f;
//
//// ��ʼ���������λ��    position                        Up_Y
//Camera camera = Camera(glm::vec3(4.0f, 5.0f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//
////��ʼ��������λ������Ļ����
//GLdouble lastX = WIDTH / 2.0f;
//GLdouble lastY = HEIGHT / 2.0f;
//
//// �ж��Ƿ��ǵ�һ�ν������
//GLboolean firstMouse = true;
//
//// ��Դλ�ó�ʼ��
//glm::vec3 LightPos = glm::vec3(0.0f, 0.0f, 1.0f);
//
//// ���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ�������
//// �Դ���ע��һ���ص�����(Callback Function)��������ÿ�δ��ڴ�С��������ʱ�򱻵���
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // glViewport����ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�
//    glViewport(0, 0, width, height);
//}
//
//
//// ��Ӧ����¼� �������Ļص�����
//// ����λ��posX, posY
//void mouse_callback(GLFWwindow* window, double posX, double posY)
//{
//    // ��һ�ν���,��¼��ǰ���λ����Ϊ��ʼ�����λ��
//    if (firstMouse)
//    {
//        lastX = posX;
//        lastY = posY;
//        firstMouse = false;
//    }
//
//    double xoffset = posX - lastX;
//    // ��������������� ʵ�ʲ��������������ƶ������ ����Ҳ����������ƶ� ʵ��Ӧ������
//    double yoffset = lastY - posY;
//
//    lastX = posX;
//    lastY = posY;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//
//}
//
//// ��Ӧ������
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(yoffset);
//}
//
//
//void processKeyInput(GLFWwindow* window)
//{
//    // esc�˳�����
//    // ʹ��glfwGetKey�жϼ��Ƿ��£���һ�β�������Ӧ�Ĵ��ڣ��ڶ�����������Ӧ�ļ���glfw����ĳ�����
//    // �ü����£�glfeGetKey����GLFW_PRESS(ֵΪ1)
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//    {
//        glfwSetWindowShouldClose(window, GL_TRUE);
//    }
//    // WS��ǰ��   QE������  AD������
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//    {
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    }
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//    {
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    }
//    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
//    {
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    }
//    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
//    {
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//    }
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//    {
//        camera.ProcessKeyboard(UPWARD, deltaTime);
//    }
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//    {
//        camera.ProcessKeyboard(DOWNWARD, deltaTime);
//    }
//}
//
//
//int main()
//{
//    //��ʼ��GLFW
//    glfwInit();
//
//    //�����汾�����
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);              //���汾��
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);              //�ΰ汾��
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);                   // ���Źر� 
//
//    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "light point test", nullptr, nullptr);
//    if (window == nullptr)
//    {
//        cout << "Failed to create GLFW window" << endl;
//        glfwTerminate();
//        return -1;
//    }
//    // �������֮����Ҫ�õ�ǰ���ڵĻ����ڵ�ǰ�߳��ϳ�Ϊ��ǰ���������ǽ������Ļ�ͼ���ử�ڸոմ����Ĵ�����
//    glfwMakeContextCurrent(window);
//    // �����ڵ�����С��ʱ������������
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    // �������Ĺ�� ����һֱͣ���ڴ�����
//    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    //��������ƶ��¼� �ص������Ӧ����
//    glfwSetCursorPosCallback(window, mouse_callback);
//    //���������ֵ��ƶ� �ص������ֺ���
//    glfwSetScrollCallback(window, scroll_callback);
//
//
//    // ��������꣬���һֱͣ���ڴ���
//    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    // ʹ��gladѰ��opengl������ַ������opengl����ǰ��Ҫ��ʼ��glad
//    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    //{
//    //    cout << "Failed to initialize GLAD" << endl;
//    //    return -1;
//    //}
//
//    glewInit();
//
//    // �½�һ����Դ(������ glew ��ʼ�������)
//    LightPoint light = LightPoint();
//
//
//    glEnable(GL_DEPTH_TEST);
//
//    Shader myShader("shader_light_v.txt", "shader_light_f.txt");
//    Shader lightShader("light_v.txt", "light_f.txt");
//
//    GLuint VAO, VBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    // ���ƶ������ݵ������ڴ���
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    // ����λ��
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(0);
//    // ������ɫ
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
//    // ���㷨��
//    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(2);
//
//    while (!glfwWindowShouldClose(window))
//    {
//        // ����������֡����Ⱦʱ���
//        GLfloat currentTime = GLfloat(glfwGetTime());
//        deltaTime = currentTime - lastTime;
//        lastTime = deltaTime;
//
//        processKeyInput(window);
//
//        // �������,ʹ�ô��ڱ�����ɺ�ɫ
//        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//
//        glm::mat4 projection;
//
//        glm::mat4 viewMatrix = camera.GetViewMatrix();
//
//        // glm::perspective��������͸��ͶӰ����ͨ���ѹ۲�ռ�ͶӰ������ռ�õ��Ĳü��ռ䣩
//        // ��һ���������۲�ռ�Ĵ�С����Ұ��С��
//        // �ڶ�����������߱ȡ����ɴ��ڵĿ���Ը����á�
//        // ������������ƽ��ͷ��Ľ�ƽ�棬ͨ������Ϊ 0.1f
//        // ���ĸ�������ƽ��ͷ���Զƽ�棬ͨ������Ϊ 100.0f
//        // ͨ�����ݱ仯��Zoomֵ��Ϊ�ӽǽǶȣ�ʵ�����Ź���
//        projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
//
//        // ���ջ���,��Դ��ת
//        lightShader.Use();
//        glm::mat4 transform_light = glm::mat4(1.0f);
//        transform_light = glm::translate(transform_light, glm::vec3(1.0f * cos(currentTime), 1.0f * sin(currentTime), 1.0f * sin(currentTime)));
//        transform_light = glm::scale(transform_light, glm::vec3(0.15f, 0.15f, 0.15f));
//        // transform_light = glm::rotate(transform_light, currentTime, glm::vec3(0.5f, 0.5f, 0.0f));
//        glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "transform_light"), 1, GL_FALSE, glm::value_ptr(transform_light));
//        glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "project_light"), 1, GL_FALSE, glm::value_ptr(projection));
//        glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "view_light"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
//        light.draw(lightShader);
//
//        // �м������λ���
//        myShader.Use();
//        glm::mat4 transform;
//        glBindVertexArray(VAO);
//        transform = glm::rotate(transform, currentTime * 0.15f, glm::vec3(0.2f, 0.6f, 0.4f));
//        transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
//        glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
//        glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//        glUniformMatrix4fv(glGetUniformLocation(myShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
//
//        int lightPosLocation = glGetUniformLocation(myShader.Program, "LightPos");
//        glUniform3f(lightPosLocation, LightPos.x, LightPos.y, LightPos.z);
//        int cameraPosLocation = glGetUniformLocation(myShader.Program, "CameraPos");
//        glUniform3f(cameraPosLocation, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
//
//        //cout << camera.GetPosition().x << endl;
//        //cout << camera.GetPosition().y << endl;
//        //cout << camera.GetPosition().z << endl;
//        //cout << "__________________________________" << endl;
//
//
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
//
//        glBindVertexArray(0);
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//
//
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//
//    glfwTerminate();
//    return 0;
//}






const GLint WIDTH = 800, HEIGHT = 600;

bool keys[1024];				// ר�Ŵ洢�����ļ�
Camera camera(glm::vec3(1.0f, 1.0f, 5.0f), glm::vec3(5.0f, -1.0f, 5.0f));
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void Key_Movement();
void square_Movement(GLfloat&, GLfloat&, GLfloat&);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 1.0f);
const double Shift_pix = 0.05;					// �������ƶ��ٶ�
int main()
{
	/* ��ʼ�� glfw */
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);		// ���Źر�

	/* ���ڲ����봦�� */
	GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL Light Test", nullptr, nullptr);
	int screenWidth_1, screenHeight_1;
	glfwGetFramebufferSize(window_1, &screenWidth_1, &screenHeight_1);
	glfwMakeContextCurrent(window_1);
	glfwSetKeyCallback(window_1, KeyCallback);

	/* ��ʼ�� glew + �������� */
	glewInit();
	LightPoint my_light = LightPoint();

	/* ��Ȳ��Կ��� */
	glEnable(GL_DEPTH_TEST);

	/* �������Լ����õ���ɫ���ı������� */
	Shader ourShader = Shader("shader_light_v.txt", "shader_light_f.txt");		// ���·��
	Shader lightShader = Shader("light_v.txt", "light_f.txt");		// ���·��

	/* ���ö��㻺�����(VBO) + ���ö����������(VAO) */
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* �������Ӷ������� */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);		// ͨ�� 0 ��
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);		// ͨ�� 1 ��
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);		// ͨ�� 2 ��

	GLfloat up_down_move = 0.0f;		// �����ƶ��ı���
	GLfloat left_right_move = 0.0f;		// �����ƶ��ı���
	GLfloat front_back_move = 0.0f;	// ǰ���ƶ��ı���

	/* draw loop ��ͼѭ�� */
	while (!glfwWindowShouldClose(window_1))
	{
		/* ʱ���ȡ */
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = (float)currentTime;

		/* �ӿ� +  ���󲶻� */
		glViewport(0, 0, screenWidth_1, screenHeight_1);
		glfwPollEvents();		// ��ȡ�������
		Key_Movement();			// ��ȡ����
		square_Movement(up_down_move, left_right_move, front_back_move);		// �������ƶ�

		/* ��Ⱦ + �����ɫ���� */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* ���ջ��� */
		lightShader.Use();
		glm::mat4 my_transform = glm::mat4(1.0f);
		lightPos = glm::rotate(lightPos, glm::radians(1.0f), glm::vec3(0.0f, -1.0f, 0.0f));		// ��ת
		my_transform = glm::translate(my_transform, lightPos);									// ƽ��
		my_transform = glm::scale(my_transform, glm::vec3(0.1f, 0.1f, 0.1f));					// ����
		glm::mat4 my_projection = glm::perspective(glm::radians(45.0f), (float)screenWidth_1 / (float)screenHeight_1, 0.1f, 100.0f);
		glm::mat4 my_view = camera.GetViewMatrix();	// ��ù۲����
		int my_transform_Location = glGetUniformLocation(lightShader.Program, "transform_light");
		glUniformMatrix4fv(my_transform_Location, 1, GL_FALSE, glm::value_ptr(my_transform));
		int my_projection_Location = glGetUniformLocation(lightShader.Program, "project_light");
		glUniformMatrix4fv(my_projection_Location, 1, GL_FALSE, glm::value_ptr(my_projection));
		int my_view_Location = glGetUniformLocation(lightShader.Program, "view_light");
		glUniformMatrix4fv(my_view_Location, 1, GL_FALSE, glm::value_ptr(my_view));
		my_light.draw(lightShader);

		/* ��������� */
		my_transform = glm::mat4(1.0f);		// ��ʼ���Ǳ�Ҫ��
		ourShader.Use();					// ������ɫ������
		glBindVertexArray(VAO);				// �� VAO
		my_transform = glm::translate(my_transform, glm::vec3(left_right_move, up_down_move, front_back_move));
		my_transform = glm::scale(my_transform, glm::vec3(0.5, 0.5, 0.5));
		my_projection = glm::perspective(glm::radians(45.0f), (float)screenWidth_1 / (float)screenHeight_1, 0.1f, 100.0f);
		my_view = camera.GetViewMatrix();
		my_transform_Location = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(my_transform_Location, 1, GL_FALSE, glm::value_ptr(my_transform));
		my_projection_Location = glGetUniformLocation(ourShader.Program, "projection");
		glUniformMatrix4fv(my_projection_Location, 1, GL_FALSE, glm::value_ptr(my_projection));
		my_view_Location = glGetUniformLocation(ourShader.Program, "view");
		glUniformMatrix4fv(my_view_Location, 1, GL_FALSE, glm::value_ptr(my_view));
		int LightPos_Location = glGetUniformLocation(ourShader.Program, "LightPos");
		glUniform3f(LightPos_Location, lightPos.x, lightPos.y, lightPos.z);
		int CameraPos_Location = glGetUniformLocation(ourShader.Program, "CameraPos");
		glUniform3f(CameraPos_Location, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

		glDrawArrays(GL_TRIANGLES, 0, 36);	// ���� 36 ����(������)
		glBindVertexArray(0);				// ��� VAO
		glfwSwapBuffers(window_1);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)	// ��������(�̶�������ʽ)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key <= 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void Key_Movement()		// Camera 
{
	if (keys[GLFW_KEY_Q])		// ��ǰ
		camera.ProcessKeyboard(FORWARD, deltaTime);

	if (keys[GLFW_KEY_E])		// ���
		camera.ProcessKeyboard(BACKWARD, deltaTime);

	if (keys[GLFW_KEY_A])		// ����
		camera.ProcessKeyboard(LEFT, deltaTime);

	if (keys[GLFW_KEY_D])		// ����
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (keys[GLFW_KEY_W])		// ����
		camera.ProcessKeyboard(UPWARD, deltaTime);

	if (keys[GLFW_KEY_S])		// ����
		camera.ProcessKeyboard(DOWNWARD, deltaTime);
}

void square_Movement(GLfloat& up_down_move, GLfloat& left_right_move, GLfloat& front_back_move)	 // Square
{

	if (keys[GLFW_KEY_UP])		// ����
	{
		up_down_move += Shift_pix;
	}

	if (keys[GLFW_KEY_DOWN])	// ����
	{
		up_down_move -= Shift_pix;
	}

	if (keys[GLFW_KEY_LEFT])	// ����
	{
		left_right_move += Shift_pix;
	}

	if (keys[GLFW_KEY_RIGHT])	// ����
	{
		left_right_move -= Shift_pix;
	}

	if (keys[GLFW_KEY_F])		// ��ǰ(�� F ��)
	{
		front_back_move += Shift_pix;
	}

	if (keys[GLFW_KEY_B])		// ���(�� B ��)
	{
		front_back_move -= Shift_pix;
	}
}




