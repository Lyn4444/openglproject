// 着色器这是一种把输入转化为输出的程序，彼此之间不进行通信，唯一的沟通是通过输入输出
// 着色器使用GLSL的类C语言，GLSL包含一些针对向量和矩阵操作的有用特性
// 着色器要依次声明版本，输入输出变量，uniform和mian函数


// 着色器典型模板
//#version version_number
//
//in vector_type in_variable_name;
//out vector_type out_variable_name;
//
//uniform type uniform_name;
//
//void main()
//{
//  // 处理输入并进行一些图形操作
//  ...
//  // 将处理过的结果送到输出变量
//  out_variable_name = 处理过的结果;
//}



// GLSL 中的向量是一个可以包含有1，2，3或者4个分量的容器
// 分量的类型可以是前面默认基础类型的任意一个，也可以是下面的形式（n代表分量的数量）
// vec+n	包含n个float分量的向量（多数时候使用）
// bvec+n	包含n个bool分量的向量
// ivec+n	包含n个int分量的向量
// uvec+n	包含n个unsigned int分量的向量
// dvec+n	包含n个double分量的向量
// 
// 向量的分量获取方式
// 一个向量的分量可以通过 vec.x 这种方式获取，这里 x 是指这个向量的第一个分量,可以分别使用 “ .x、.y、.z 和 .w ” 来获取它们的第 1、2、3、4 个分量。
// GLSL 也允许你对颜色使用 rgba ，或是对纹理坐标使用 stpq 访问相同的分量。


// 一.顶点/片段着色器（txt）
// 顶点着色器与片段着色器的联系：
// 1）通过顶点着色器在输入端获取颜色作为顶点属性，再传到片段着色器进行处理输出
// 2）着色器是各自独立，但是都是一个整体，GLSL定义in和out使得着色器使用这个关键字设定输入输出，同时一个输出变量与下一个着色器的输入匹配就会传递下出
// 3）顶点着色器接受一种特殊形式的输入，从顶点数据中直接接受输入。使用location指定输入变量定义顶点数据如何管理,书写格式：
//    layout(location = 0)。顶点着色器需要为其输入提供一个额外的layout标识，才能连接到顶点数据


// 二.创建着色器类（Shader.h)
// 创建一个着色器类使得每个独立的着色器有机地联合


// 三.绘制一个彩色三角形
//#include <iostream>
//using namespace std;
//#define GLEW_STATIC	
//#include <GL/glew.h>	
//#include <GLFW/glfw3.h> 
//#include "Shader.h"
//
//
//GLfloat vertices_1[] = {
//	// position				color
//	0.0f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
//	-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
//	0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f
//};
//
//const GLint WIDTH = 800, HEIGTH = 600;
//
//int main()
//{
//	// 初始化
//	glfwInit();
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGTH, "uniform test for a beautiful triangle", nullptr, nullptr);
//	int screenWidth, screenHeight;
//	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
//	glfwMakeContextCurrent(window);
//	glewInit();
//
//	// 使用自定义的Shader类，将自定义的着色器文件传进来
//	Shader myShader = Shader("shader_v.txt", "shader_f.txt");
//
//	// 设置顶点缓冲对象 + 顶点数组对象（VBO + VAO）
//	GLuint VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
//
//	// 设置链接顶点属性
//	// 顶点着色器中使用 “layout(location = 0)” 定义 position 顶点属性的位置值(Location)。
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
//	// 通道 0 打开
//	glEnableVertexAttribArray(0);
//	// 顶点着色器中使用 “layout(location = 1)” 定义 color 顶点属性的位置值(Location)。
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	// 通道 1 打开
//	glEnableVertexAttribArray(1);
//
//	// draw loop 画画循环
//	while (!glfwWindowShouldClose(window)) {
//		glViewport(0, 0, screenWidth, screenHeight);
//		glfwPollEvents();
//		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// 绘制三角形
//		myShader.Use();
//		// 绑定 VAO
//		glBindVertexArray(VAO);
//		// 画三角形  从第0个顶点开始 一共画3次
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		// 解绑定
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//
//
//	}
//
//	// 释放资源	
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//
//	// 结束
//	glfwTerminate();
//
//	return 0;
//
//}


// 四.索引缓冲对象（EBO）
// VBO，VAO与EBO的联系与区别
// 1.顶点缓冲对象VBO是显存中的一个存储区域,存储大量的顶点属性信息，每个VBO有唯一标识ID对应具体的VBO显存地址
// 2.VAO是保存所有顶点数据属性的状态结合，存储顶点数据格式和顶点数据所需的VBO对象引用，VAO没有存储顶点相关的属性数据，
//   这些信息存储在VBO中，VAO相当于是多个VBO的引用，把一些VBO组合在一起作为一个对象统一管理
// 3.EBO在OpenGL中相当于顶点数组，是为了解决同一顶点多次调用的问题。当需要使用重复的顶点是通过顶点的位置索引来调用顶点，
//   而不是对重复的顶点信息重复记录调用，EBO存储的内容是顶点位置的索引indices，与VBO类似，是显存中的一块内存缓冲器



// 五.绘制一个颜色随时间变化的正方形,可以认为是两个三角形来拼凑
// Uniform：是一种从CPU中的应用向GPU中的着色器发送数据的方式，但uniform和顶点属性不同
//          uniform是全局的，意味着uniform变量必须在每个着色器程序对象中都是独一无二的，可以被着色器程序的任意着色器在任意阶段访问，
//          uniform会一直保存数据直到被垂直或更新
// 定义的uniform变量开始为空，需要先使用glGetUniformLocation寻找着色器中的uniform属性的索引（即位置值），再使用glUniform…() 相关函数来更新值


#include <iostream>
using namespace std;
#define GLEW_STATIC	
#include<GL/glew.h>	
#include<GLFW/glfw3.h> 
#include"Shader.h"


GLfloat vertices[] =
{
	0.5f, 0.5f, 0.0f,				// 0
	0.5f, -0.5f, 0.0f,				// 1
	-0.5f, -0.5f, 0.0f,				// 2
	-0.5f, 0.5f, 0.0f,				// 3
};

// 给出四个顶点的连接信息
GLuint indices[] =
{
	0, 1, 3,
	1, 2, 3
};


const GLint WIDTH = 600, HEIGHT = 800;

int main()
{
	glfwInit();
	GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "uniform test for a beautiful square", nullptr, nullptr);
	int screenWidth_1, screenHeight_1;
	glfwGetFramebufferSize(window_1, &screenWidth_1, &screenHeight_1);
	glfwMakeContextCurrent(window_1);
	glewInit();


	Shader myShader = Shader("shader_uniform_v.txt", "shader_uniform_f.txt");

	GLuint VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);


	// 设置索引缓冲对象
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	while (!glfwWindowShouldClose(window_1)) 
	{
		// 视口 + 时间 
		glViewport(0, 0, screenWidth_1, screenHeight_1);
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 绘制图形
		myShader.Use();
		float time = glfwGetTime();
		// 红色数值的计算，范围在[0，1]
		float redValue = sin(time) / 2.0f + 0.5f;
		// 绿色数值计算，范围[0.1]。且满足 “redValue + greenValue = 1”
		float greenValue = 1 - redValue;
		// 找到“time”索引
		int vertexColorLocation = glGetUniformLocation(myShader.Program, "time");
		// 更新颜色
		glUniform4f(vertexColorLocation, redValue, greenValue, 0.0f, 1.0f);


		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
		// 画两个三角形 从第0个顶点开始 一共画6次
		// glDrawElements函数说明
		// 1)第一个参数：绘制模式
		// 2)第二个参数：绘制的顶点数目
		// 3)第三个参数：索引的数据类型，uint即unsign int
		// 4)第四个参数：可选的EBO中的偏移量设定
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// 解绑定
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// 交换缓冲
		glfwSwapBuffers(window_1);

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();

	return 0;
}