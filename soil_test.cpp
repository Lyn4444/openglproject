// 绘制纹理映射场景时，每个顶点要定义几何坐标和OpenGL纹理坐标，几何坐标：决定顶点在屏幕上的绘制位置，OpenGL纹理坐标：决定纹理图像中的哪一个纹理赋予该顶点
// 顶点之间的纹理坐标插值与平滑着色插值方法相同。
// 纹理图像是方形数组，纹理坐标成为s，t，r和q坐标，分别对应几何坐标（x，y，z，w）和其他坐标，q是一个缩放因子，相当于w
// 实际在纹理读取中的坐标应该分别是s/q，t/q，r/q，默认q是1.0（产生纹理坐标的高级算法比如阴影贴图中有用）
// window的计算机图像坐标系与OpenGL纹理坐标系是相反的，在通过 “计算机方式” 读取图像后，再通过OpenGL绘出时，会出现图像倒着的情况


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
	//position			// color			// texture coords(纹理坐标)
	0.5f, 0.5f, 0.0f,	0.0f, 0.0f, 0.0f,	1.0f, 1.0f,			// 右上顶点
	0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f,			// 右下顶点
	-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,			// 左下顶点
	-0.5f, 0.5f, 0.0f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f			// 左上顶点
};

GLfloat vertices_2[] =
{
	//position				// color				// texture coords(纹理坐标)
	1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		2.0f, 2.0f,		// 右上顶点		编号0
	1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		2.0f, 0.0f,		// 右下顶点		编号1
	-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		// 左下顶点		编号2
	-1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 2.0f		// 左上顶点		编号3
};

// 读取纹理
// SOIL_load_image函数需要文件路径，两个int指针获取返回图片的宽度和高度，第四个参数指定图片的通道数量，第五个参数决定如何加载图片，并存储为一个char/byte数组
unsigned char* image = SOIL_load_image("texture_image.jpg", &width, &height, 0, SOIL_LOAD_RGBA);

GLuint indices[] =
{
	0, 1, 3,		// 序号为 0、1、3 的顶点组合成一个三角形
	1, 2, 3			// 序号为 1、2、3 的顶点组合成一个三角形
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

	// 设置VBO，VAO，EBO
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 设置链接顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// 生成纹理
	GLuint texture;
	// glGenTexture函数：将一个命名的纹理绑定到一个纹理目标上
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// 2D纹理生成
	// 第一个参数：指定纹理目标
	// 第二个参数：为纹理指定多级渐远纹理级别，0（基本级别）
	// 第三个参数：将纹理存储为何种格式
	// 第四个参数：设置最终纹理的宽度
	// 第五个参数：设置最终纹理的高度
	// 第六个参数：总是设置为0
	// 第七个参数：定义原图的格式，使用RGBA
	// 第八个参数：设置原图的数据类型
	// 第九个参数：源图像数据
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	// glGenerateMipmap：为当前绑定的纹理自动生成所有需要的多级渐远纹理（当站在远处看图像时，很多像素点就可以“凑”成一个主要的像素点；当站在进除看图像时，像素点就需要“铺开”，让图像变得清晰）
	glGenerateMipmap(GL_TEXTURE_2D);
	// 完成后，释放图像的内存并解绑纹理对象
	SOIL_free_image_data(image);

	// 纹理环绕方式,2D是s坐标和t坐标,3D是s坐标,t坐标和r坐标
	// 纹理坐标范围（0，0）到（1，1），纹理环绕方式：
	// GL_REPEAT：重复纹理图像
	// GL_MIRRORED_REPEAT：和GL_REPEAT一样，但每次重复图片是镜像放置的。
	// GL_CLAMP_TO_EDGE：纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。
	// GL_CLAMP_TO_BORDER：超出的坐标为用户指定的边缘颜色。
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// 设置纹理过滤
	// GL_NEAREST(邻近过滤) 产生了颗粒状的图案，我们能够清晰看到组成纹理的像素，而 GL_LINEAR(线性过滤) 能够产生更平滑的图案，很难看出单个的纹理像素。
	// 当纹理被放大时, 用 GL_LINEAR 方式过滤;当纹理被缩小时, 用 GL_NEAREST 方式过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
	myShader.Use();
	int textureLocation = glGetUniformLocation(myShader.Program, "myTexture");
	// 告诉 OpenGL 的着色器采样器属于哪个纹理单元,只需要设置一次,放在渲染循环的前面
	glUniform1i(textureLocation, 0);

	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();

		// 渲染+清除颜色缓冲
		glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 显卡中有 N 个纹理单元，纹理单元使得在着色器中可以使用多于一个的纹理，通过把纹理单元赋值给采样器，可以一次绑定多个纹理
		// 激活 0 号纹理单元(这条语句可以省略，因为纹理单元GL_TEXTURE0默认总是被激活)。OpenGL最多 32 个,不过要考虑显卡.
		glActiveTexture(GL_TEXTURE0);
		// 绑定这个纹理到当前激活的纹理目标
		glBindTexture(GL_TEXTURE_2D, texture);

		myShader.Use();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// 交换缓冲
		glfwSwapBuffers(window);

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();

	return 0;

}


