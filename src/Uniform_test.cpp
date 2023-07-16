// ��ɫ������һ�ְ�����ת��Ϊ����ĳ��򣬱˴�֮�䲻����ͨ�ţ�Ψһ�Ĺ�ͨ��ͨ���������
// ��ɫ��ʹ��GLSL����C���ԣ�GLSL����һЩ��������;����������������
// ��ɫ��Ҫ���������汾���������������uniform��mian����


// ��ɫ������ģ��
//#version version_number
//
//in vector_type in_variable_name;
//out vector_type out_variable_name;
//
//uniform type uniform_name;
//
//void main()
//{
//  // �������벢����һЩͼ�β���
//  ...
//  // ��������Ľ���͵��������
//  out_variable_name = ������Ľ��;
//}



// GLSL �е�������һ�����԰�����1��2��3����4������������
// ���������Ϳ�����ǰ��Ĭ�ϻ������͵�����һ����Ҳ�������������ʽ��n���������������
// vec+n	����n��float����������������ʱ��ʹ�ã�
// bvec+n	����n��bool����������
// ivec+n	����n��int����������
// uvec+n	����n��unsigned int����������
// dvec+n	����n��double����������
// 
// �����ķ�����ȡ��ʽ
// һ�������ķ�������ͨ�� vec.x ���ַ�ʽ��ȡ������ x ��ָ��������ĵ�һ������,���Էֱ�ʹ�� �� .x��.y��.z �� .w �� ����ȡ���ǵĵ� 1��2��3��4 ��������
// GLSL Ҳ���������ɫʹ�� rgba �����Ƕ���������ʹ�� stpq ������ͬ�ķ�����


// һ.����/Ƭ����ɫ����txt��
// ������ɫ����Ƭ����ɫ������ϵ��
// 1��ͨ��������ɫ��������˻�ȡ��ɫ��Ϊ�������ԣ��ٴ���Ƭ����ɫ�����д������
// 2����ɫ���Ǹ��Զ��������Ƕ���һ�����壬GLSL����in��outʹ����ɫ��ʹ������ؼ����趨���������ͬʱһ�������������һ����ɫ��������ƥ��ͻᴫ���³�
// 3��������ɫ������һ��������ʽ�����룬�Ӷ���������ֱ�ӽ������롣ʹ��locationָ������������嶥��������ι���,��д��ʽ��
//    layout(location = 0)��������ɫ����ҪΪ�������ṩһ�������layout��ʶ���������ӵ���������


// ��.������ɫ���ࣨShader.h)
// ����һ����ɫ����ʹ��ÿ����������ɫ���л�������


// ��.����һ����ɫ������
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
//	// ��ʼ��
//	glfwInit();
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGTH, "uniform test for a beautiful triangle", nullptr, nullptr);
//	int screenWidth, screenHeight;
//	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
//	glfwMakeContextCurrent(window);
//	glewInit();
//
//	// ʹ���Զ����Shader�࣬���Զ������ɫ���ļ�������
//	Shader myShader = Shader("shader_v.txt", "shader_f.txt");
//
//	// ���ö��㻺����� + �����������VBO + VAO��
//	GLuint VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
//
//	// �������Ӷ�������
//	// ������ɫ����ʹ�� ��layout(location = 0)�� ���� position �������Ե�λ��ֵ(Location)��
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
//	// ͨ�� 0 ��
//	glEnableVertexAttribArray(0);
//	// ������ɫ����ʹ�� ��layout(location = 1)�� ���� color �������Ե�λ��ֵ(Location)��
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	// ͨ�� 1 ��
//	glEnableVertexAttribArray(1);
//
//	// draw loop ����ѭ��
//	while (!glfwWindowShouldClose(window)) {
//		glViewport(0, 0, screenWidth, screenHeight);
//		glfwPollEvents();
//		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// ����������
//		myShader.Use();
//		// �� VAO
//		glBindVertexArray(VAO);
//		// ��������  �ӵ�0�����㿪ʼ һ����3��
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		// ���
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//
//
//	}
//
//	// �ͷ���Դ	
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//
//	// ����
//	glfwTerminate();
//
//	return 0;
//
//}


// ��.�����������EBO��
// VBO��VAO��EBO����ϵ������
// 1.���㻺�����VBO���Դ��е�һ���洢����,�洢�����Ķ���������Ϣ��ÿ��VBO��Ψһ��ʶID��Ӧ�����VBO�Դ��ַ
// 2.VAO�Ǳ������ж����������Ե�״̬��ϣ��洢�������ݸ�ʽ�Ͷ������������VBO�������ã�VAOû�д洢������ص��������ݣ�
//   ��Щ��Ϣ�洢��VBO�У�VAO�൱���Ƕ��VBO�����ã���һЩVBO�����һ����Ϊһ������ͳһ����
// 3.EBO��OpenGL���൱�ڶ������飬��Ϊ�˽��ͬһ�����ε��õ����⡣����Ҫʹ���ظ��Ķ�����ͨ�������λ�����������ö��㣬
//   �����Ƕ��ظ��Ķ�����Ϣ�ظ���¼���ã�EBO�洢�������Ƕ���λ�õ�����indices����VBO���ƣ����Դ��е�һ���ڴ滺����



// ��.����һ����ɫ��ʱ��仯��������,������Ϊ��������������ƴ��
// Uniform����һ�ִ�CPU�е�Ӧ����GPU�е���ɫ���������ݵķ�ʽ����uniform�Ͷ������Բ�ͬ
//          uniform��ȫ�ֵģ���ζ��uniform����������ÿ����ɫ����������ж��Ƕ�һ�޶��ģ����Ա���ɫ�������������ɫ��������׶η��ʣ�
//          uniform��һֱ��������ֱ������ֱ�����
// �����uniform������ʼΪ�գ���Ҫ��ʹ��glGetUniformLocationѰ����ɫ���е�uniform���Ե���������λ��ֵ������ʹ��glUniform��() ��غ���������ֵ


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

// �����ĸ������������Ϣ
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


	// ���������������
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	while (!glfwWindowShouldClose(window_1)) 
	{
		// �ӿ� + ʱ�� 
		glViewport(0, 0, screenWidth_1, screenHeight_1);
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ����ͼ��
		myShader.Use();
		float time = glfwGetTime();
		// ��ɫ��ֵ�ļ��㣬��Χ��[0��1]
		float redValue = sin(time) / 2.0f + 0.5f;
		// ��ɫ��ֵ���㣬��Χ[0.1]�������� ��redValue + greenValue = 1��
		float greenValue = 1 - redValue;
		// �ҵ���time������
		int vertexColorLocation = glGetUniformLocation(myShader.Program, "time");
		// ������ɫ
		glUniform4f(vertexColorLocation, redValue, greenValue, 0.0f, 1.0f);


		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
		// ������������ �ӵ�0�����㿪ʼ һ����6��
		// glDrawElements����˵��
		// 1)��һ������������ģʽ
		// 2)�ڶ������������ƵĶ�����Ŀ
		// 3)�������������������������ͣ�uint��unsign int
		// 4)���ĸ���������ѡ��EBO�е�ƫ�����趨
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// ���
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// ��������
		glfwSwapBuffers(window_1);

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();

	return 0;
}