#include <iostream>
using namespace std;
#define GLEW_STATIC	
#include "Shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>								// OpenGL Mathematics,ʹ�þ�������
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL2/SOIL2.h>
#include <SOIL2/stb_image.h>


GLfloat vertices[] =
{
	//position				// color				// texture coords(��������)
	1.0f, 3.0f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 2.0f,			// ���϶���		���0
	1.0f, -3.0, 0.0f,		0.0f, 1.0f, 0.0f,		1.0f, -1.0f,		// ���¶���		���1
	-1.0f, -3.0f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, -1.0f,		// ���¶���		���2
	-1.0f, 3.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 2.0f			// ���϶���		���3
	// ������������ķ�Χ���� (0, 0) �� (1, 1) �Ĳ��ֻᱻ���� �������ơ� ��������
};

GLuint indices[] =
{
	0, 1, 3,
	1, 2, 3
};

const GLint WIDTH = 600, HEIGHT = 600;

int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "soil test 2", nullptr, nullptr);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glfwMakeContextCurrent(window);
	glewInit();

	Shader myShader = Shader("shader_soil_v_2.txt", "shader_soil_f_2.txt");

	// ����VAO,VBO,EBO
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// �������Ӷ�������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// ��ȡ����
	int width, height;
	unsigned char* image_1 = SOIL_load_image("texture_image_1.png", &width, &height, 0, SOIL_LOAD_RGBA);
	unsigned char* image_2 = SOIL_load_image("texture_image_2.png", &width, &height, 0, SOIL_LOAD_RGBA);

	// ��������
	GLuint texture_1, texture_2;
	glGenTextures(1, &texture_1);
	glBindTexture(GL_TEXTURE_2D, texture_1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_1);
	glGenerateMipmap(GL_TEXTURE_2D);

	glGenTextures(1, &texture_2);
	glBindTexture(GL_TEXTURE_2D, texture_2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_2);
	glGenerateMipmap(GL_TEXTURE_2D);

	// �ͷ�ͼ���ڴ�
	SOIL_free_image_data(image_1);
	SOIL_free_image_data(image_2);

	// ���������Ʒ�ʽ��s�����t����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �����������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// ���ð�uninform����
	myShader.Use();
	// ֻ��Ҫ����һ��,������Ⱦѭ��֮ǰ
	// ������Ϊ��myTexture_1������ɫ��������(�ؼ���ΪSampler2D) ��������Ԫ0
	glUniform1i(glGetUniformLocation(myShader.Program, "myTexture_1"), 0);
	// ������Ϊ��myTexture_2������ɫ��������(�ؼ���ΪSampler2D) ��������Ԫ1
	glUniform1i(glGetUniformLocation(myShader.Program, "myTexture_2"), 1);

	// ������
	int cnt = 0;
	// �����л���־
	int flag = 1;
	// N Խ��λ��/������ٶȶ������
	int N = 200;

	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();

		glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// �����0��1����Ԫ
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_2);

		// ÿһ��ѭ���ı仯
		cnt += 1;
		// �����ظ�ѭ�������ٶ�����ʱ���¿�ʼ
		if (cnt >= 2 * N)
		{
			cnt = 0;
		}
		// ��������ѭ�������־
		if (cnt == 0 || cnt == N)
		{
			flag = -flag;
		}

		// ƽ�Ʊ仯ʵ��
		// ��ʼ����λ����
		glm::mat4 startMatrix = glm::mat4(1.0f);
		// ��λ�����һ��λ���������ݸ�glm::translate()����,�õ�������Ӧ����(startMatrix.x + 0.0f, startMatrix.y + 1.0f - cnt*1.0/N, startMatrix.z + 0.0f)
		// ��(ԭʼ�����x+x�����ϵ�ƫ����ԭʼ�����y+y�����ϵ�ƫ����ԭʼ�����z+z�����ϵ�ƫ��)
		glm::mat4 transform = glm::translate(startMatrix, glm::vec3(0.0f, 1.0f - cnt * 1.0 / N, 0.0f));

		// ����任��ʵ��
		int vextexLocation = glGetUniformLocation(myShader.Program, "time");
		if (flag == 1)
		{
			// ������1 �𽥽��浽����2
			glUniform1i(vextexLocation, cnt * 1.0 / N);
		}
		else
		{
			// ������2 �𽥽��浽����1
			glUniform1i(vextexLocation, 2.0 - cnt * 1.0 / N);
		}

		unsigned int transformLocation = glGetUniformLocation(myShader.Program, "transform");
		// ��transform��ֵ���ݵ�uniform ��transform����
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

		// ����ͼ��
		glBindVertexArray(VAO);									
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);				
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	
		glBindVertexArray(0);									
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);				
		glBindTexture(GL_TEXTURE_2D, 0);

		glfwSwapBuffers(window);

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;


}





