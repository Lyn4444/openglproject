#include <iostream>
using namespace std;
#define GLEW_STATIC	
#include "Shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>								// OpenGL Mathematics,使用矩阵运算
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL2/SOIL2.h>
#include <SOIL2/stb_image.h>


GLfloat vertices[] =
{
	//position				// color				// texture coords(纹理坐标)
	1.0f, 3.0f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 2.0f,			// 右上顶点		编号0
	1.0f, -3.0, 0.0f,		0.0f, 1.0f, 0.0f,		1.0f, -1.0f,		// 右下顶点		编号1
	-1.0f, -3.0f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, -1.0f,		// 左下顶点		编号2
	-1.0f, 3.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 2.0f			// 左上顶点		编号3
	// 这里纹理坐标的范围超过 (0, 0) 到 (1, 1) 的部分会被进行 “纹理环绕” 处理！！！
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

	// 设置VAO,VBO,EBO
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 设置链接顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// 读取纹理
	int width, height;
	unsigned char* image_1 = SOIL_load_image("texture_image_1.png", &width, &height, 0, SOIL_LOAD_RGBA);
	unsigned char* image_2 = SOIL_load_image("texture_image_2.png", &width, &height, 0, SOIL_LOAD_RGBA);

	// 生成纹理
	GLuint texture_1, texture_2;
	glGenTextures(1, &texture_1);
	glBindTexture(GL_TEXTURE_2D, texture_1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_1);
	glGenerateMipmap(GL_TEXTURE_2D);

	glGenTextures(1, &texture_2);
	glBindTexture(GL_TEXTURE_2D, texture_2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_2);
	glGenerateMipmap(GL_TEXTURE_2D);

	// 释放图形内存
	SOIL_free_image_data(image_1);
	SOIL_free_image_data(image_2);

	// 设置纹理环绕方式，s坐标和t坐标
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 设置纹理过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 设置绑定uninform变量
	myShader.Use();
	// 只需要设置一次,放在渲染循环之前
	// 告诉名为“myTexture_1”的着色器采样器(关键字为Sampler2D) 属于纹理单元0
	glUniform1i(glGetUniformLocation(myShader.Program, "myTexture_1"), 0);
	// 告诉名为“myTexture_2”的着色器采样器(关键字为Sampler2D) 属于纹理单元1
	glUniform1i(glGetUniformLocation(myShader.Program, "myTexture_2"), 1);

	// 计数器
	int cnt = 0;
	// 纹理切换标志
	int flag = 1;
	// N 越大，位移/交替的速度都会变慢
	int N = 200;

	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();

		glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 激活绑定0和1纹理单元
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_2);

		// 每一次循环的变化
		cnt += 1;
		// 设置重复循环，在速度最慢时重新开始
		if (cnt >= 2 * N)
		{
			cnt = 0;
		}
		// 设置纹理循环交替标志
		if (cnt == 0 || cnt == N)
		{
			flag = -flag;
		}

		// 平移变化实现
		// 初始化单位矩阵
		glm::mat4 startMatrix = glm::mat4(1.0f);
		// 单位矩阵和一个位移向量传递给glm::translate()函数,得到的向量应该是(startMatrix.x + 0.0f, startMatrix.y + 1.0f - cnt*1.0/N, startMatrix.z + 0.0f)
		// 即(原始矩阵的x+x方向上的偏量，原始矩阵的y+y方向上的偏量，原始矩阵的z+z方向上的偏量)
		glm::mat4 transform = glm::translate(startMatrix, glm::vec3(0.0f, 1.0f - cnt * 1.0 / N, 0.0f));

		// 交替变换的实现
		int vextexLocation = glGetUniformLocation(myShader.Program, "time");
		if (flag == 1)
		{
			// 从纹理1 逐渐交替到纹理2
			glUniform1i(vextexLocation, cnt * 1.0 / N);
		}
		else
		{
			// 从纹理2 逐渐交替到纹理1
			glUniform1i(vextexLocation, 2.0 - cnt * 1.0 / N);
		}

		unsigned int transformLocation = glGetUniformLocation(myShader.Program, "transform");
		// 将transform的值传递到uniform 的transform变量
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

		// 绘制图形
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





