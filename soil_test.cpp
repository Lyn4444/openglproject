// ��������ӳ�䳡��ʱ��ÿ������Ҫ���弸�������OpenGL�������꣬�������꣺������������Ļ�ϵĻ���λ�ã�OpenGL�������꣺��������ͼ���е���һ��������ö���
// ����֮������������ֵ��ƽ����ɫ��ֵ������ͬ��
// ����ͼ���Ƿ������飬���������Ϊs��t��r��q���꣬�ֱ��Ӧ�������꣨x��y��z��w�����������꣬q��һ���������ӣ��൱��w
// ʵ���������ȡ�е�����Ӧ�÷ֱ���s/q��t/q��r/q��Ĭ��q��1.0��������������ĸ߼��㷨������Ӱ��ͼ�����ã�
// window�ļ����ͼ������ϵ��OpenGL��������ϵ���෴�ģ���ͨ�� ���������ʽ�� ��ȡͼ�����ͨ��OpenGL���ʱ�������ͼ���ŵ����


#include <iostream>
using namespace std;
#define GLEW_STATIC	
#include <SOIL2/SOIL2.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <SOIL2/stb_image.h>

int width, height;

GLfloat vertices_1[] =
{
	//position			// color			// texture coords(��������)
	0.5f, 0.5f, 0.0f,	0.0f, 0.0f, 0.0f,	1.0f, 1.0f,			// ���϶���
	0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f,			// ���¶���
	-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,			// ���¶���
	-0.5f, 0.5f, 0.0f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f			// ���϶���
};

GLfloat vertices_2[] =
{
	//position				// color				// texture coords(��������)
	1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		2.0f, 2.0f,		// ���϶���		���0
	1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		2.0f, 0.0f,		// ���¶���		���1
	-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		// ���¶���		���2
	-1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 2.0f		// ���϶���		���3
};

// ��ȡ����
// SOIL_load_image������Ҫ�ļ�·��������intָ���ȡ����ͼƬ�Ŀ�Ⱥ͸߶ȣ����ĸ�����ָ��ͼƬ��ͨ�����������������������μ���ͼƬ�����洢Ϊһ��char/byte����
unsigned char* image = SOIL_load_image("texture_image.jpg", &width, &height, 0, SOIL_LOAD_RGBA);

GLuint indices[] =
{
	0, 1, 3,		// ���Ϊ 0��1��3 �Ķ�����ϳ�һ��������
	1, 2, 3			// ���Ϊ 1��2��3 �Ķ�����ϳ�һ��������
};

const GLint WIDTH = 600, HEIGHT = 600;

int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "texture test", nullptr, nullptr);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glfwMakeContextCurrent(window);
	glewInit();

	Shader myShader = Shader("shader_soil_v.txt", "shader_soil_f.txt");

	// ����VBO��VAO��EBO
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// �������Ӷ�������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// ��������
	GLuint texture;
	// glGenTexture��������һ������������󶨵�һ������Ŀ����
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// 2D��������
	// ��һ��������ָ������Ŀ��
	// �ڶ���������Ϊ����ָ���༶��Զ������0����������
	// ������������������洢Ϊ���ָ�ʽ
	// ���ĸ�������������������Ŀ��
	// �����������������������ĸ߶�
	// ��������������������Ϊ0
	// ���߸�����������ԭͼ�ĸ�ʽ��ʹ��RGBA
	// �ڰ˸�����������ԭͼ����������
	// �ھŸ�������Դͼ������
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	// glGenerateMipmap��Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ������վ��Զ����ͼ��ʱ���ܶ����ص�Ϳ��ԡ��ա���һ����Ҫ�����ص㣻��վ�ڽ�����ͼ��ʱ�����ص����Ҫ���̿�������ͼ����������
	glGenerateMipmap(GL_TEXTURE_2D);
	// ��ɺ��ͷ�ͼ����ڴ沢����������
	SOIL_free_image_data(image);

	// �����Ʒ�ʽ,2D��s�����t����,3D��s����,t�����r����
	// �������귶Χ��0��0������1��1���������Ʒ�ʽ��
	// GL_REPEAT���ظ�����ͼ��
	// GL_MIRRORED_REPEAT����GL_REPEATһ������ÿ���ظ�ͼƬ�Ǿ�����õġ�
	// GL_CLAMP_TO_EDGE����������ᱻԼ����0��1֮�䣬�����Ĳ��ֻ��ظ���������ı�Ե������һ�ֱ�Ե�������Ч����
	// GL_CLAMP_TO_BORDER������������Ϊ�û�ָ���ı�Ե��ɫ��
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// �����������
	// GL_NEAREST(�ڽ�����) �����˿���״��ͼ���������ܹ��������������������أ��� GL_LINEAR(���Թ���) �ܹ�������ƽ����ͼ�������ѿ����������������ء�
	// �������Ŵ�ʱ, �� GL_LINEAR ��ʽ����;��������Сʱ, �� GL_NEAREST ��ʽ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
	myShader.Use();
	int textureLocation = glGetUniformLocation(myShader.Program, "myTexture");
	// ���� OpenGL ����ɫ�������������ĸ�����Ԫ,ֻ��Ҫ����һ��,������Ⱦѭ����ǰ��
	glUniform1i(textureLocation, 0);

	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();

		// ��Ⱦ+�����ɫ����
		glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// �Կ����� N ������Ԫ������Ԫʹ������ɫ���п���ʹ�ö���һ��������ͨ��������Ԫ��ֵ��������������һ�ΰ󶨶������
		// ���� 0 ������Ԫ(����������ʡ�ԣ���Ϊ����ԪGL_TEXTURE0Ĭ�����Ǳ�����)��OpenGL��� 32 ��,����Ҫ�����Կ�.
		glActiveTexture(GL_TEXTURE0);
		// �����������ǰ���������Ŀ��
		glBindTexture(GL_TEXTURE_2D, texture);

		myShader.Use();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// ��������
		glfwSwapBuffers(window);

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();

	return 0;

}


