// 典型的着色器类的模板
//
//#pragma once					// 为了避免同一个头文件被包含（include）多次
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//using namespace std;
//
//// 自定义的着色器类
//class Shader
//{
//private:
//	GLuint vertex, fragment;	// 顶点着色器 和 片段着色器 
//public:
//	GLuint Program;				// 着色器程序的ID
//
//	// Constructor(着色器构造函数)
//	Shader(const GLchar* vertexPath, const GLchar* fragmentPath)		// 分别是主函数传进来的关于顶点/片段着色器GLSL的路径
//	{
//		// 文件读取系列的变量定义
//		......
//
//			// 异常机制处理：保证ifstream对象可以抛出异常：
//			......
//
//			try
//		{
//			// 打开文件
//			......
//
//				// 读取文件的缓冲内容到数据流中
//				......
//
//				// 关闭文件处理器
//				......
//
//				// 转换数据流到string
//				......
//
//		} catch (ifstream::failure e) {	// 发生异常时输出
//			cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
//		}
//
//		/* 将 string 类型的字符串转化为 char数组 类型 */
//		......
//
//			/* 顶点着色器 */
//			......
//
//			/* 片段着色器 */
//			......
//
//			/* 着色器程序对象 */
//			......
//	}
//
//	// Deconstructor(着色器的析构函数)
//	~Shader()
//	{
//		glDetachShader(this->Program, vertex);
//		glDetachShader(this->Program, fragment);
//		glDeleteShader(vertex);
//		glDeleteShader(fragment);
//		glDeleteProgram(this->Program);
//	}
//
//	// 渲染的时候调用
//	void Use()
//	{
//		// glUseProgram使用程序对象program作为当前渲染状态的一部分
//		glUseProgram(this->Program);
//	}
//};


#pragma once					// 为了避免同一个头文件被包含（include）多次
#include <string>
#include <fstream>				// 包含的多个文件流类
#include <sstream>				// 使用string对象来代替字符数组,用来进行流的输入输出操作
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

	// 着色器构造函数
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath) 
	{
		// 文件读取的变量定义
		string vertexCode;
		string fragmentCode;
		ifstream vShaderFile;
		ifstream fShaderFile;

		// 异常机制处理，使得ifstream对象可以抛出异常
		vShaderFile.exceptions(ifstream::badbit);
		fShaderFile.exceptions(ifstream::badbit);

		try
		{
			// 打开文件
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);

			stringstream vShaderStream, fShaderStream;

			// 读取文件的缓冲内容到数据流中
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			// 关闭文件处理器
			vShaderFile.close();
			fShaderFile.close();

			// 转换数据流到string对象
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (ifstream:: failure e) {
			cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
		}


		// 将string类型的字符串转化成char数组类型
		const GLchar *vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();

		// 顶点着色器
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

		// 片段着色器
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &flag);
		if (!flag) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
		}

		// 着色器程序对象
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

	// 着色器析构函数
	~Shader()
	{
		// 调用glDetachShader函数来清除每个shader对象
		// OpenGL保存着由它产生的多数对象的引用计数，如果一个shader对象被创建后又被删除的话驱动程序也会同时清除掉它
		// 如果他被绑定在程序上，只调用glDeleteShader函数只是会标记它等待删除，只有等你调用glDetachShader后它的引用计数才会被置零然后被移除掉。
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