#include <iostream>
using namespace std;
// ������Ӧ�Ŀ�
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main() {
	// ͼ����Ⱦ���ߵĽ׶�
	// ������ɫ��---װ���ָ��ͼԪ����״---������ɫ��---��դ���׶�---Ƭ����ɫ��

	// �������̣����һ��������
	// һ.��д����λ��

	// ��Ҫָ���������㣬ÿһ������Ҫ��һ��3Dλ��
	// �� OpenGL ��ָ�����������궼�� 3D ����
	// ����3D������3���ᣨx,y,z)�϶���-1.0��1.0�ķ�Χ�ڲ��ܴ����������Ǳ�׼���豸����

	GLfloat vertices_1[] = {
		// x y z
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.05f, 0.0f,
	};


	// ���嶥������֮�󣬻Ὣ����Ϊ���뵽ͼ����Ⱦ���ߵĵ�һ������׶Σ�������ɫ��

	// ��.��д������ɫ��,��Ҫ�õ� ����ɫ������GLSL(OpenGL Shading Language) ��
	// Ϊ�����ö�����ɫ�����������Ҫ��λ�����ݸ�ֵ��Ԥ�����gl_Position������vec4���ͣ�
	// ���������������ʹ��in�ؼ��֣�����������3 �������������������ת��Ϊ 4 ����������
	//  ��vec3 ��������Ϊ vec4 �������Ĳ�����ͬʱ�� ��͸��ֵ������ ����Ϊ1.0f�������һ����

	const GLchar* vertexCode_1 = "#version 330 core\n"		// ����3.30�汾
		"layout(location = 0) in vec3 position_1;\n"		// 3��������vector������ʾλ�ã�position�Ǳ��������洢������������
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position_1, 1.0f);\n"			// ͸��ֵΪ1.0f
		"}\n";

	// ������������������ɫ������ 
	// �ڴ�����ɫ������ʱ��ע��Ҫ�� ID ������,�������ö�����ɫ��Ϊ unsigned int �������ͣ�GLuint��
	// ʹ��glCreateShader����������ɫ��
	// glCreateShader�Ǵ���һ�� ����ɫ���� ͨ�õĺ������ܴ���Ƭ����ɫ���Ͷ�����ɫ���ȣ�ֻ��Ҫ������Ӧ�ı�ʶ����Ϊ����
	// ������ɫ���ı�ʶ���� GL_VERTEX_SHADER 

	GLuint vertexShader_1 = glCreateShader(GL_VERTEX_SHADER);
	// ����ɫ��Դ�븽�ӵ���ɫ������Ȼ����б���
	// ��������ɫ�������ݴ�����  
	// glShaderSource ����
	// ��һ�������� Ҫ�������ɫ������
	// �ڶ��������� ָ�����ݵ�Դ���ַ�������
	// ������������ ������ɫ��������Դ�룬������ǵ�ַ
	// ���ĸ������� ������ʱ����ʼ��
	glShaderSource(vertexShader_1, 1, &vertexCode_1, NULL);
	glCompileShader(vertexShader_1);


	// ���glCompileShader�Ƿ����ɹ�
	GLint flag;					// �����жϱ����Ƿ�ɹ��ı�ʶ��
	GLchar infoLog[512];		// ���õ�512���ַ���װ������Ϣ(��������˵Ļ�)
	glGetShaderiv(vertexShader_1, GL_COMPILE_STATUS, &flag); 		// ��ȡ����״̬
	if (!flag)
	{
		glGetShaderInfoLog(vertexShader_1, 512, NULL, infoLog);   	// ��������� glGetShaderInfoLog���� ����ȡ������Ϣ  
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// ��.��дƬ����ɫ��
	// Ƭ����ɫ���������Ǵ����դ���׶����ɵ�ÿһ��ƬԪ�����ռ����ÿ�����ص�������ɫ
	// Ƭ����ɫ��ֻ��Ҫһ������������ñ�����һ��4������������ʾ���յ������ɫ
	// ���������������ʹ��out�ؼ���
	// ����AlphaֵΪ1.0��1.0������ȫ��͸������ī��ɫ��vec4��ֵ����ɫ���

	const GLchar* fragmentCode_1 = "#version 330 core\n"
		"out vec4 FragColor_1;\n"
		"void main()\n"
		"{\n"
		"FragColor_1 = vec4(0.5f, 0.75f, 0.25f, 1.0f);\n"			// AlphaֵΪ1.0f��������ȫ��͸��
		"}\n";
	// ����Ƭ����ɫ����ʹ��GL_FRAGMENT_SHADER ������Ϊ��ɫ������

	GLuint fragmentShader_1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_1, 1, &fragmentCode_1, NULL);
	glCompileShader(fragmentShader_1);

	glGetShaderiv(fragmentShader_1, GL_COMPILE_STATUS, &flag);
	if (!flag) {
		glGetProgramInfoLog(fragmentShader_1, 512, NULL, infoLog);
		cout << "ERROR::SHADER::Fragment::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// ��.��д��ɫ������
	// ��ɫ���������(Shader Program Object)�Ƕ����ɫ���ϲ�֮������������ɵĶ���
	// ����һ�����̣����ǰ���ǰ������ ����ɫ��ģ�ӡ� ƴ����һ��� ������ģ�ӡ������Խ��� ��һ��������,��ˮ��
	// ���Ҫʹ�ñ������ɫ������Ҫ��������������Ϊһ����ɫ���������Ȼ������Ⱦ�����ʱ�򼤻������ɫ������
	// �Ѽ�����ɫ���������ɫ�����ڷ�����Ⱦ���õ�ʱ��ʹ��
	// ��������ɫ����һ�������ʱ�򣬻��ÿ����ɫ����������ӵ���һ����ɫ�������롣����������벻ƥ���ʱ�򣬻�õ�һ�����Ӵ���

	// ������ɫ�����򣬴�ʱ����Ҫ�����κβ���
	// glCreateProgram �����ᴴ��һ����ɫ�����򣬲������´����������� ID ���á�
	GLuint shaderProgram_1 = glCreateProgram();
	// �� glLinkProgram ��֮ǰ����� ��ɫ�� ���θ��ӵ����������
	glAttachShader(shaderProgram_1, vertexShader_1);
	glAttachShader(shaderProgram_1, fragmentShader_1);
	// ����� glLinkProgram ����
	glLinkProgram(shaderProgram_1);

	// ���������ɫ�������Ƿ�ɹ�������ȡ��Ӧ����־
	glGetProgramiv(shaderProgram_1, GL_LINK_STATUS, &flag);
	if (!flag)
	{
		glGetProgramInfoLog(shaderProgram_1, 512, NULL, infoLog);   // ��������� glGetProgramInfoLog���� ����ȡ������Ϣ  
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}

	// �ڰ���ɫ���������ӵ���ɫ����������Ժ�ɾ����ɫ������(�ͷ���Դ����ʡ�ռ�)
	glDeleteShader(vertexShader_1);
	glDeleteShader(fragmentShader_1);

	// ���� glUseProgram ����,������ɫ�����������Ϊ����������ó��������ʹ��
	glUseProgram(shaderProgram_1);

	// ��.�������Ӷ�������
	// ������ɫ�����������κ���ʽ�Ķ�������
	// �����ֶ�ָ���������ݵ���һ�����ֶ�Ӧ������ɫ������һ���������ԣ�����������Ⱦǰָ��OPenGL����Ρ����͡�����Ķ�������
	// һ������λ����x,y,z��������4�ֽڵĸ���ֵ��һ������������Ĳ���Ϊ12����3 * sizeof(GLfloat)��x,y,z��3��ֵ֮��û�з�϶�����������н������У������е�һ��ֵ�ڻ��忪����λ��

	// ʹ��glVertexAttribPointer����������Ӧ�õ��������������
	// glVertexAttribPointer����
	// ��һ���������������ԣ��ڶ�����ɫ����ʹ��"layout(location = 0)"����position�������Ե�λ��ֵ
	// �ڶ����������������ԵĴ�С������������һ��vec3����3��ֵ��ɣ�������3
	// ���������������ݵ����ͣ�GLSL�� vec* �����ɸ�����ֵGL_FLOAT��ɵ�
	// ���ĸ��������Ƿ����ݱ���׼����Normalize��������ΪGL_TRUE���������ݶ��ᱻӳ�䵽0��1֮�䣬�������з�����signed������-1��������ΪGL_FALSE�򲻻�
	// ��������������ò����������������Ķ���������֮��ļ���������¸���λ��������3��float֮�󣬲�������Ϊ3 * sizeof(float)
	// ��������������ʼλ�õ�ƫ������Offset��������λ������������Ŀ�ͷ��������0����Ϊ���һ��������������"void"��������Ҫ����ǿ������ת��
	glVertexAttribPointer(0, 3, GL_FLAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	// ���ö������ԣ�Ĭ�϶��������ǽ��ã�
	glEnableVertexAttribArray(0);

	// ��.���ö��㻺�����VBO��			��������VAOһ����֣�
	// ͨ�����㻺����������������������ڴ棬�����һ���Խ�һ�������ݷ��͵��Կ�
	// ���㻺�������һ����Ҫ��OpenGL����ӵ��һ��ID��ʹ��glGenBuffers������һ������ID����һ��VBO����

	// ���嶥�㻺�����
	GLuint VBO;
	// VBO��Ҫ���������ݣ���VBO
	glGenBuffers(1, &VBO);

	// OpenGL �кܶ໺���������
	// ���㻺�����Ļ���������GL_ARRAY_BUFFER
	// ʹ�� glBindBuffer �����Ѵ����Ķ��㻺�����󶨵� GL_ARRAY_BUFFER Ŀ��

	glBindBuffer(GL_ARRAY_BUFFER, VBO);



	return 0;
}
