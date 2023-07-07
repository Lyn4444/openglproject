#include <iostream>
using namespace std;
// 引入相应的库
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main() {
	// 图形渲染管线的阶段
	// 顶点着色器---装配成指定图元的形状---几何着色器---光栅化阶段---片段着色器

	// 绘制流程，输出一个三角形
	// 一.编写顶点位置

	// 先要指定三个顶点，每一个顶点要有一个3D位置
	// 在 OpenGL 中指定的所有坐标都是 3D 坐标
	// 仅当3D坐标在3个轴（x,y,z)上都在-1.0和1.0的范围内才能处理它，这是标准化设备坐标

	GLfloat vertices_1[] = {
		// x y z
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.05f, 0.0f,
	};


	// 定义顶点数据之后，会将其作为输入到图形渲染管线的第一个处理阶段：顶点着色器

	// 二.编写顶点着色器,需要用到 “着色器语言GLSL(OpenGL Shading Language) ”
	// 为了设置顶点着色器的输出，需要把位置数据赋值给预定义的gl_Position变量（vec4类型）
	// 声明输入变量可以使用in关键字，由于输入是3 分量的向量，必须把其转换为 4 分量的向量
	//  把vec3 的数据作为 vec4 构造器的参数，同时把 “透视值分量” 设置为1.0f来完成这一任务

	const GLchar* vertexCode_1 = "#version 330 core\n"		// 申明3.30版本
		"layout(location = 0) in vec3 position_1;\n"		// 3个浮点数vector向量表示位置，position是变量，并存储了这三个向量
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position_1, 1.0f);\n"			// 透视值为1.0f
		"}\n";

	// 在主函数创建顶点着色器对象 
	// 在创建着色器对象时，注意要用 ID 来引用,所以设置顶点着色器为 unsigned int 数据类型（GLuint）
	// 使用glCreateShader创建顶点着色器
	// glCreateShader是创建一个 “着色器” 通用的函数，能创建片段着色器和顶点着色器等，只需要传入相应的标识符作为参数
	// 顶点着色器的标识符是 GL_VERTEX_SHADER 

	GLuint vertexShader_1 = glCreateShader(GL_VERTEX_SHADER);
	// 把着色器源码附加到着色器对象，然后进行编译
	// 将顶点着色器的内容传进来  
	// glShaderSource 函数
	// 第一个参数： 要编译的着色器对象
	// 第二个参数： 指定传递的源码字符串数量
	// 第三个参数： 顶点着色器真正的源码，传入的是地址
	// 第四个参数： 读数据时的起始点
	glShaderSource(vertexShader_1, 1, &vertexCode_1, NULL);
	glCompileShader(vertexShader_1);


	// 检测glCompileShader是否编译成功
	GLint flag;					// 用于判断编译是否成功的标识符
	GLchar infoLog[512];		// 我用的512个字符来装错误信息(如果出错了的话)
	glGetShaderiv(vertexShader_1, GL_COMPILE_STATUS, &flag); 		// 获取编译状态
	if (!flag)
	{
		glGetShaderInfoLog(vertexShader_1, 512, NULL, infoLog);   	// 如果出错，用 glGetShaderInfoLog函数 来获取错误消息  
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// 三.编写片段着色器
	// 片段着色器的作用是处理光栅化阶段生成的每一个片元，最终计算出每个像素的最终颜色
	// 片段着色器只需要一个输出变量，该变量是一个4分量向量，表示最终的输出颜色
	// 声明输出变量可以使用out关键字
	// 设置Alpha值为1.0（1.0代表完全不透明）的墨绿色的vec4赋值给颜色输出

	const GLchar* fragmentCode_1 = "#version 330 core\n"
		"out vec4 FragColor_1;\n"
		"void main()\n"
		"{\n"
		"FragColor_1 = vec4(0.5f, 0.75f, 0.25f, 1.0f);\n"			// Alpha值为1.0f，代表完全不透明
		"}\n";
	// 编译片段着色器，使用GL_FRAGMENT_SHADER 常量作为着色器类型

	GLuint fragmentShader_1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_1, 1, &fragmentCode_1, NULL);
	glCompileShader(fragmentShader_1);

	glGetShaderiv(fragmentShader_1, GL_COMPILE_STATUS, &flag);
	if (!flag) {
		glGetProgramInfoLog(fragmentShader_1, 512, NULL, infoLog);
		cout << "ERROR::SHADER::Fragment::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// 四.编写着色器程序
	// 着色器程序对象(Shader Program Object)是多个着色器合并之后并最终链接完成的东西
	// 它是一个流程，它是把先前创建的 “着色器模子” 拼接在一起的 “超级模子”，可以进行 “一条龙服务”,流水线
	// 如果要使用编译的着色器，需要将其连接起来作为一个着色器程序对象，然后在渲染对象的时候激活这个着色器程序
	// 已激活着色器程序的着色器将在发送渲染调用的时候被使用
	// 当连接着色器至一个程序的时候，会把每个着色器的输出连接到下一个着色器的输入。当输出和输入不匹配的时候，会得到一个连接错误。

	// 创建着色器程序，此时不需要传递任何参数
	// glCreateProgram 函数会创建一个着色器程序，并返回新创建程序对象的 ID 引用。
	GLuint shaderProgram_1 = glCreateProgram();
	// 用 glLinkProgram 把之前编译的 着色器 依次附加到程序对象上
	glAttachShader(shaderProgram_1, vertexShader_1);
	glAttachShader(shaderProgram_1, fragmentShader_1);
	// 最后用 glLinkProgram 链接
	glLinkProgram(shaderProgram_1);

	// 检测链接着色器程序是否成功，并获取相应的日志
	glGetProgramiv(shaderProgram_1, GL_LINK_STATUS, &flag);
	if (!flag)
	{
		glGetProgramInfoLog(shaderProgram_1, 512, NULL, infoLog);   // 如果出错，用 glGetProgramInfoLog函数 来获取错误消息  
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}

	// 在把着色器对象链接到着色器程序对象以后，删除着色器对象(释放资源，节省空间)
	glDeleteShader(vertexShader_1);
	glDeleteShader(fragmentShader_1);

	// 调用 glUseProgram 函数,传递着色器程序对象作为参数，激活该程序对象以使用
	glUseProgram(shaderProgram_1);

	// 五.设置链接顶点属性
	// 顶点着色器允许输入任何形式的顶点属性
	// 必须手动指定输入数据的哪一个部分对应顶点着色器的哪一个顶点属性，即必须在渲染前指定OPenGL该如何“解释”输入的顶点数据
	// 一个顶点位置有x,y,z三个都是4字节的浮点值，一个顶点属性组的步长为12，即3 * sizeof(GLfloat)，x,y,z这3个值之间没有缝隙，并在数组中紧密排列，数据中第一个值在缓冲开启的位置

	// 使用glVertexAttribPointer将顶点数据应用到逐个顶点属性上
	// glVertexAttribPointer参数
	// 第一个参数：顶点属性，在顶点着色器中使用"layout(location = 0)"定义position顶点属性的位置值
	// 第二个参数：顶点属性的大小，顶点属性是一个vec3，由3个值组成，所以是3
	// 第三个参数：数据的类型，GLSL中 vec* 都是由浮点数值GL_FLOAT组成的
	// 第四个参数：是否将数据被标准化（Normalize），设置为GL_TRUE则所有数据都会被映射到0和1之间，（对于有符号型signed数据是-1），设置为GL_FALSE则不会
	// 第五个参数：设置步长，设置在连续的顶点属性组之间的间隔，由于下个组位置数据在3个float之后，步长设置为3 * sizeof(float)
	// 第六个参数：起始位置的偏移量（Offset），由于位置数据在数组的开头，所以是0，因为最后一个参数的类型是"void"，所以需要进行强制类型转换
	glVertexAttribPointer(0, 3, GL_FLAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	// 启用顶点属性（默认顶点属性是禁用）
	glEnableVertexAttribArray(0);

	// 六.设置顶点缓冲对象（VBO）			（与后面的VAO一起出现）
	// 通过顶点缓冲对象管理含有这三个顶点的内存，这可以一次性将一大批数据发送到显卡
	// 顶点缓冲对象是一个重要的OpenGL对象，拥有一个ID，使用glGenBuffers函数和一个缓冲ID生成一个VBO对象

	// 定义顶点缓存对象
	GLuint VBO;
	// VBO主要负责传输数据，绑定VBO
	glGenBuffers(1, &VBO);

	// OpenGL 有很多缓冲对象类型
	// 顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER
	// 使用 glBindBuffer 函数把创建的顶点缓冲对象绑定到 GL_ARRAY_BUFFER 目标

	glBindBuffer(GL_ARRAY_BUFFER, VBO);



	return 0;
}
