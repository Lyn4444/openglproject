// ���͵���ɫ�����ģ��
//
//#pragma once					// Ϊ�˱���ͬһ��ͷ�ļ���������include�����
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//using namespace std;
//
//// �Զ������ɫ����
//class Shader
//{
//private:
//	GLuint vertex, fragment;	// ������ɫ�� �� Ƭ����ɫ�� 
//public:
//	GLuint Program;				// ��ɫ�������ID
//
//	// Constructor(��ɫ�����캯��)
//	Shader(const GLchar* vertexPath, const GLchar* fragmentPath)		// �ֱ����������������Ĺ��ڶ���/Ƭ����ɫ��GLSL��·��
//	{
//		// �ļ���ȡϵ�еı�������
//		......
//
//			// �쳣���ƴ�����֤ifstream��������׳��쳣��
//			......
//
//			try
//		{
//			// ���ļ�
//			......
//
//				// ��ȡ�ļ��Ļ������ݵ���������
//				......
//
//				// �ر��ļ�������
//				......
//
//				// ת����������string
//				......
//
//		} catch (ifstream::failure e) {	// �����쳣ʱ���
//			cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
//		}
//
//		/* �� string ���͵��ַ���ת��Ϊ char���� ���� */
//		......
//
//			/* ������ɫ�� */
//			......
//
//			/* Ƭ����ɫ�� */
//			......
//
//			/* ��ɫ��������� */
//			......
//	}
//
//	// Deconstructor(��ɫ������������)
//	~Shader()
//	{
//		glDetachShader(this->Program, vertex);
//		glDetachShader(this->Program, fragment);
//		glDeleteShader(vertex);
//		glDeleteShader(fragment);
//		glDeleteProgram(this->Program);
//	}
//
//	// ��Ⱦ��ʱ�����
//	void Use()
//	{
//		// glUseProgramʹ�ó������program��Ϊ��ǰ��Ⱦ״̬��һ����
//		glUseProgram(this->Program);
//	}
//};


#pragma once					// Ϊ�˱���ͬһ��ͷ�ļ���������include�����
#include <string>
#include <fstream>				// �����Ķ���ļ�����
#include <sstream>				// ʹ��string�����������ַ�����,�����������������������
#include <iostream>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader
{
private:
	GLuint vertex, fragment;
public:
	GLuint Program;

	// ��ɫ�����캯��
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath) 
	{
		// �ļ���ȡ�ı�������
		string vertexCode;
		string fragmentCode;
		ifstream vShaderFile;
		ifstream fShaderFile;

		// �쳣���ƴ���ʹ��ifstream��������׳��쳣
		vShaderFile.exceptions(ifstream::badbit);
		fShaderFile.exceptions(ifstream::badbit);

		try
		{
			// ���ļ�
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);

			stringstream vShaderStream, fShaderStream;

			// ��ȡ�ļ��Ļ������ݵ���������
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			// �ر��ļ�������
			vShaderFile.close();
			fShaderFile.close();

			// ת����������string����
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (ifstream:: failure e) {
			cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
		}


		// ��string���͵��ַ���ת����char��������
		const GLchar *vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();

		// ������ɫ��
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		GLint flag;
		GLchar infoLog[512];
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &flag);
		if (!flag) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
		}

		// Ƭ����ɫ��
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &flag);
		if (!flag) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
		}

		// ��ɫ���������
		this->Program = glCreateProgram();
		glAttachShader(this->Program, vertex);
		glAttachShader(this->Program, fragment);
		glLinkProgram(this->Program);
		if (!flag) {
			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
			cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	// ��ɫ����������
	~Shader()
	{
		// ����glDetachShader���������ÿ��shader����
		// OpenGL���������������Ķ�����������ü��������һ��shader���󱻴������ֱ�ɾ���Ļ���������Ҳ��ͬʱ�������
		// ����������ڳ����ϣ�ֻ����glDeleteShader����ֻ�ǻ������ȴ�ɾ����ֻ�е������glDetachShader���������ü����Żᱻ����Ȼ���Ƴ�����
		glDetachShader(this->Program, vertex);
		glDetachShader(this->Program, fragment);
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		glDeleteProgram(this->Program);
	}

	void use()
	{
		glUseProgram(this->Program);
	}
};